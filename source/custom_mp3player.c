/***************************************************************************
 *   Low Level MAD Library Implementation for the GameCube                 *
 *   By Daniel "nForce" Bloemendal                                         *
 *   nForce@Sympatico.ca                                                   *
 ***************************************************************************/
// Modified by Hermes to include SNDLIB / ASNDLIB support
// Modified by AleFunky for GDWII

#include <ogc/machine/asm.h>
#include <ogc/machine/processor.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <lwp.h>
#include <pad.h>
#include <limits.h>
#include <system.h>
#include <ogcsys.h>
#include <malloc.h>
#include <unistd.h>

#include "math.h"

#include "asndlib.h"
#include "custom_mp3player.h"

static s32 have_samples = 0;
static u32 mp3_volume = 255;
static volatile float mp3_amplitude = 0.0f;
static volatile int paused = FALSE;
static volatile int preloaded = FALSE;

static int frames_to_skip = 0; // ~1153 frames
static int skipped = 0;


#ifndef __SNDLIB_H__
	#define ADMA_BUFFERSIZE			(4992)
#else
	#define ADMA_BUFFERSIZE			(8192)
#endif
#define STACKSIZE				(32768)

#define DATABUFFER_SIZE			(32768)

typedef struct _eqstate_s
{
	f32 lf;
	f32 f1p0;
	f32 f1p1;
	f32 f1p2;
	f32 f1p3;
	
	f32 hf;
	f32 f2p0;
	f32 f2p1;
	f32 f2p2;
	f32 f2p3;
	
	f32 sdm1;
	f32 sdm2;
	f32 sdm3;
	
	f32 lg;
	f32 mg;
	f32 hg;
} EQState;

struct _outbuffer_s
{
	void *bs;
	u32 *put,*get;
	s32 buf_filled;
	u8 buffer[DATABUFFER_SIZE];
};

static u8 InputBuffer[DATABUFFER_SIZE+MAD_BUFFER_GUARD];
static u8 OutputBuffer[3][ADMA_BUFFERSIZE] ATTRIBUTE_ALIGN(32);
static struct _outbuffer_s OutputRingBuffer;
	
static u32 init_done = 0;
static u32 CurrentBuffer = 0;
static f32 VSA = (1.0/4294967295.0);
static bool thr_running = false;
static bool MP3Playing = false;
static void *mp3cb_data = NULL;

static void* StreamPlay(void *);
static u8 StreamPlay_Stack[STACKSIZE];
static lwp_t hStreamPlay;
static lwpq_t thQueue;

static struct mad_stream Stream;
static struct mad_frame Frame;

static int mp3_voice = 1;  // Default voice is 1, but changeable

static s32 (*mp3read)(void*,void *,s32);
typedef bool (*mp3filter_t)(struct mad_stream *, struct mad_frame *);
mp3filter_t mp3filterfunc = NULL;

static void DataTransferCallback(s32);
static void Init3BandState(EQState *es,s32 lowfreq,s32 highfreq,s32 mixfreq);
static s16 Do3Band(EQState *es,s16 sample);
static void Resample(struct mad_pcm *Pcm,EQState eqs[2],u32 stereo,u32 src_samplerate);

typedef struct {
    u8 *frame_start;
    size_t frame_size;
    u8 frame_data[DATABUFFER_SIZE];  // enough to hold next frame + padding
    size_t byte_offset;
	bool valid;
} CachedMP3Start;

static CachedMP3Start cached_start = {0};

struct _rambuffer
{
	const void *buf_addr;
	s32 len,pos;
} rambuffer;

void MP3Player_SetVoice(int voice) {
    if (voice < 0 || voice >= MAX_VOICES) return; // or clamp, or log error
    mp3_voice = voice;
}

static __inline__ s16 FixedToShort(mad_fixed_t Fixed)
{
	/* Clipping */
	if(Fixed>=MAD_F_ONE)
		return(SHRT_MAX);
	if(Fixed<=-MAD_F_ONE)
		return(-SHRT_MAX);

	Fixed=Fixed>>(MAD_F_FRACBITS-15);
	return((s16)Fixed);
}

static __inline__ void buf_init(struct _outbuffer_s *buf)
{
	buf->buf_filled = 0;
	buf->bs = buf->buffer;
	buf->put = buf->get = buf->bs;
}

static __inline__ s32 buf_used(struct _outbuffer_s *buf)
{
	return ((DATABUFFER_SIZE + ((u32)buf->put - (u32)buf->get)) % DATABUFFER_SIZE);
}

static __inline__ s32 buf_space(struct _outbuffer_s *buf)
{
	return ((DATABUFFER_SIZE - ((u32)buf->put - (u32)buf->get) - 1) % DATABUFFER_SIZE);
}

static __inline__ s32 buf_get(struct _outbuffer_s *buf,void *data,s32 len)
{
	u32 *p;
	s32 cnt,i;

	if(len>buf_used(buf))
		len = buf_used(buf);

	if(len==0) {
		LWP_ThreadSignal(thQueue);
		return 0;
	}
	
	p = data;
	cnt = ((u32)buf->bs + DATABUFFER_SIZE - (u32)buf->get);
	if(len>cnt) {
		for(i=0;i<(cnt>>2);i++)
			*p++ = *buf->get++;
		buf->get = buf->bs;
		for(i=0;i<((len-cnt)>>2);i++)
			*p++ = *buf->get++;
	} else {
		for(i=0;i<(len>>2);i++)
			*p++ = *buf->get++;
	}

#ifndef __SNDLIB_H__
	DCFlushRangeNoSync(data,len);
#endif
	LWP_ThreadSignal(thQueue);
#ifndef __SNDLIB_H__
	_sync();
#endif
	return len;
}

static __inline__ s32 buf_put(struct _outbuffer_s *buf,void *data,s32 len)
{
	u32 *p;
	s32 cnt,i;

	while(len>buf_space(buf))
		LWP_ThreadSleep(thQueue);

	p = data;
	cnt = ((u32)buf->bs + DATABUFFER_SIZE - (u32)buf->put);
	if(len>cnt) {
		for(i=0;i<(cnt>>2);i++)
			*buf->put++ = *p++;
		buf->put = buf->bs;
		for(i=0;i<((len-cnt)>>2);i++)
			*buf->put++ = *p++;
	} else {
		for(i=0;i<(len>>2);i++)
			*buf->put++ = *p++;
	}

	if(buf->buf_filled==0 && buf_used(buf)>=(DATABUFFER_SIZE>>1)) {
		buf->buf_filled = 1;
		memset(OutputBuffer[CurrentBuffer],0,ADMA_BUFFERSIZE);

#ifndef __SNDLIB_H__
		DCFlushRange(OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE);
		AUDIO_InitDMA((u32)OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE);
		AUDIO_StartDMA();
#else
		have_samples = 0;
		SND_SetVoice(mp3_voice,VOICE_STEREO_16BIT,48000,0,(void*)OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE,mp3_volume,mp3_volume,DataTransferCallback);
#endif

		CurrentBuffer = (CurrentBuffer+1)%3;
	}

	return len;
}

static s32 _mp3ramcopy(void *usr_data,void *buffer,s32 len)
{
	struct _rambuffer *ram = (struct _rambuffer*)usr_data;
	const void *ptr = ((u8*)ram->buf_addr+ram->pos);

	if((ram->pos+len)>ram->len) {
		len = (ram->len - ram->pos);
	}
	if(len<=0) return 0;

	memcpy(buffer,ptr,len);
	ram->pos += len;

	return len;
}

void MP3Player_Init(void)
{
	if(!init_done) {
		init_done = 1;
#ifndef __SNDLIB_H__
		AUDIO_Init(NULL);
		AUDIO_SetDSPSampleRate(AI_SAMPLERATE_48KHZ);
#else
		SND_Pause(0);
		SND_StopVoice(mp3_voice);
#endif
	}
}

s32 MP3Player_PlayBuffer(const void *buffer,s32 len,bool (*filterfunc)(struct mad_stream *,struct mad_frame *))
{
	if(thr_running) return -1;

	rambuffer.buf_addr = buffer;
	rambuffer.len = len;
	rambuffer.pos = 0;

	mp3cb_data = &rambuffer;
	mp3read = _mp3ramcopy;
	mp3filterfunc = filterfunc;
	if(LWP_CreateThread(&hStreamPlay,StreamPlay,NULL,StreamPlay_Stack,STACKSIZE,80)<0) {
		return -1;
	}
	return 0;
}

s32 MP3Player_PlayFile(void *cb_data,s32 (*reader)(void *,void *,s32),bool (*filterfunc)(struct mad_stream *,struct mad_frame *))
{
	if(thr_running) return -1;

	mp3cb_data = cb_data;
	mp3read = reader;
	mp3filterfunc = filterfunc;
	if(LWP_CreateThread(&hStreamPlay,StreamPlay,NULL,StreamPlay_Stack,STACKSIZE,80)<0) {
		return -1;
	}
	return 0;
}

void MP3Player_Stop(void)
{
	skipped = 0;
	frames_to_skip = 0;
	memset(&cached_start,0,sizeof(cached_start));
	preloaded = FALSE;
    MP3Player_Unpause();
	MP3Player_Reset();
}

void MP3Player_Reset(void)
{
	if(!thr_running) return;

	thr_running = false;
	LWP_JoinThread(hStreamPlay,NULL);
}

bool MP3Player_IsPlaying(void)
{
	return thr_running;
}

static void *StreamPlay(void *arg)
{
	bool atend;
	u8 *GuardPtr = NULL;
	struct mad_synth Synth;
	mad_timer_t Timer;
	EQState eqs[2];

	thr_running = true;

	CurrentBuffer = 0;
	memset(OutputBuffer[0],0,ADMA_BUFFERSIZE);
	memset(OutputBuffer[1],0,ADMA_BUFFERSIZE);
	memset(OutputBuffer[2],0,ADMA_BUFFERSIZE);

	buf_init(&OutputRingBuffer);
	LWP_InitQueue(&thQueue);
	Init3BandState(&eqs[0],880,5000,48000);
	Init3BandState(&eqs[1],880,5000,48000);

#ifndef __SNDLIB_H__
	AUDIO_RegisterDMACallback(DataTransferCallback);
#endif

	if (!preloaded)  {
		mad_stream_init(&Stream);
		mad_frame_init(&Frame);
	}
	mad_synth_init(&Synth);
	mad_timer_reset(&Timer);

	atend = false;
	MP3Playing = true;
	bool using_cache = false;

	if (cached_start.valid) {
		mad_stream_buffer(&Stream, cached_start.frame_data, cached_start.frame_size);
		using_cache = true;
	} else {
		MP3Playing = false;
	}

	while (!atend && thr_running) {
		if (!paused && (Stream.buffer == NULL || Stream.error == MAD_ERROR_BUFLEN) && !using_cache) {
			u8 *ReadStart;
			s32 ReadSize, Remaining;

			if (Stream.next_frame != NULL) {
				Remaining = Stream.bufend - Stream.next_frame;
				memmove(InputBuffer, Stream.next_frame, Remaining);
				ReadStart = InputBuffer + Remaining;
				ReadSize = DATABUFFER_SIZE - Remaining;
			} else {
				ReadSize = DATABUFFER_SIZE;
				ReadStart = InputBuffer;
				Remaining = 0;
			}

			ReadSize = mp3read(mp3cb_data, ReadStart, ReadSize);
			if (ReadSize <= 0) {
				GuardPtr = ReadStart;
				memset(GuardPtr, 0, MAD_BUFFER_GUARD);
				ReadSize = MAD_BUFFER_GUARD;
				atend = true;
			}

			mad_stream_buffer(&Stream, InputBuffer, ReadSize + Remaining);
		}
		
		while (!paused && !mad_frame_decode(&Frame, &Stream) && thr_running) {
			if (mp3filterfunc && mp3filterfunc(&Stream, &Frame)) {
				if (skipped == frames_to_skip && !cached_start.valid) {
					cached_start.frame_size = Stream.bufend - Stream.this_frame;
					memcpy(cached_start.frame_data, Stream.this_frame, cached_start.frame_size);
					cached_start.valid = true;
					struct _rambuffer *rb = (struct _rambuffer *)mp3cb_data;
					s32 remaining_bytes = Stream.bufend - Stream.this_frame;
					cached_start.byte_offset = rb->pos - remaining_bytes;
				}
				continue;
			}

			if (!paused) {
				mad_timer_add(&Timer, Frame.header.duration);
				mad_synth_frame(&Synth, &Frame);
				Resample(&Synth.pcm, eqs, (MAD_NCHANNELS(&Frame.header) == 2), Frame.header.samplerate);
			}
		}
		
		if (MAD_RECOVERABLE(Stream.error)) {
			if (Stream.error != MAD_ERROR_LOSTSYNC || Stream.this_frame != GuardPtr)
				continue;
		} else {
			if (Stream.error != MAD_ERROR_BUFLEN)
				break;
		}

		// If we were using cache and finished it, resume file reading
		if (using_cache) {
			using_cache = false;
			Stream.buffer = NULL;
			struct _rambuffer *rb = (struct _rambuffer *)mp3cb_data;
			rb->pos += cached_start.byte_offset + cached_start.frame_size;
		}
	}

	mad_synth_finish(&Synth);
	mad_frame_finish(&Frame);
	mad_stream_finish(&Stream);

	while(MP3Playing)
		LWP_ThreadSleep(thQueue);

#ifndef __SNDLIB_H__
	AUDIO_StopDMA();
	AUDIO_RegisterDMACallback(NULL);
#else
	SND_StopVoice(mp3_voice);
#endif

	LWP_CloseQueue(thQueue);

	thr_running = false;

	return 0;
}

typedef union {
	struct {
		u16 hi;
		u16 lo;
	} aword;
	u32 adword;
} dword;

float update_pulse(float current_amp) {
    static float prev = 0.0f;
    static float pulse = 0.0f;
    float decay = 0.05f;
    float delta = current_amp - prev;

    if (delta > 0.02f) {
        pulse += powf(delta, 0.6f) * 4.0f;
    }

    pulse *= (1.0f - decay);
    if (pulse > 1.0f) pulse = 1.0f;
    if (pulse < 0.0f) pulse = 0.0f;
    prev = current_amp;

    return pulse;
}

static void Resample(struct mad_pcm *Pcm,EQState eqs[2],u32 stereo,u32 src_samplerate)
{
	u32 val32;
	dword pos;
	s32 incr;

	pos.adword = 0;
	incr = (u32)(((f32)src_samplerate/48000.0F)*65536.0F);
	u64 sum_squares = 0;
	u32 sample_count = 0;

	while(pos.aword.hi < Pcm->length) {
		s16 left = Do3Band(&eqs[0], FixedToShort(Pcm->samples[0][pos.aword.hi]));
		s16 right = stereo ? Do3Band(&eqs[1], FixedToShort(Pcm->samples[1][pos.aword.hi])) : left;

		// Average stereo to mono
		s16 mono = (left + right) / 2;

		// Accumulate square of sample
		sum_squares += mono * mono;
		sample_count++;

		val32 = ((u16)left << 16) | ((u16)right & 0xFFFF);
		buf_put(&OutputRingBuffer, &val32, sizeof(u32));

		pos.adword += incr;
	}

	if (sample_count > 0) {
		// RMS amplitude normalized to 0.0–1.0 (16-bit audio)
		float rms = sqrtf((float)sum_squares / sample_count) / 32768.0f;

		mp3_amplitude = update_pulse(rms);
		
	}
}

static void Init3BandState(EQState *es,s32 lowfreq,s32 highfreq,s32 mixfreq)
{
	memset(es,0,sizeof(EQState));

	es->lg = 1.0;
	es->mg = 1.0;
	es->hg = 1.0;
	
	es->lf = 2.0F*sinf(M_PI*((f32)lowfreq/(f32)mixfreq));
	es->hf = 2.0F*sinf(M_PI*((f32)highfreq/(f32)mixfreq));
}

static s16 Do3Band(EQState *es,s16 sample)
{
	f32 l,m,h;

	es->f1p0 += (es->lf*((f32)sample - es->f1p0))+VSA;
	es->f1p1 += (es->lf*(es->f1p0 - es->f1p1));
	es->f1p2 += (es->lf*(es->f1p1 - es->f1p2));
	es->f1p3 += (es->lf*(es->f1p2 - es->f1p3));
	l = es->f1p3;

	es->f2p0 += (es->hf*((f32)sample - es->f2p0))+VSA;
	es->f2p1 += (es->hf*(es->f2p0 - es->f2p1));
	es->f2p2 += (es->hf*(es->f2p1 - es->f2p2));
	es->f2p3 += (es->hf*(es->f2p2 - es->f2p3));
	h = es->sdm3 - es->f2p3;

	m = es->sdm3 - (h+l);

	l *= es->lg;
	m *= es->mg;
	h *= es->hg;

	es->sdm3 = es->sdm2;
	es->sdm2 = es->sdm1;
	es->sdm1 = (f32)sample;

	return (s16)(l+m+h);
}

static void DataTransferCallback(s32 voice)
{
#ifndef __SNDLIB_H__
	AUDIO_InitDMA((u32)OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE);

	CurrentBuffer = (CurrentBuffer+1)%3;
	MP3Playing = (buf_get(&OutputRingBuffer,OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE)>0);
#else
	if(!thr_running) {
		MP3Playing = (buf_get(&OutputRingBuffer,OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE)>0);
		return;
	}

	if(have_samples==1) {
		if(SND_AddVoice(mp3_voice,(void*)OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE)==SND_OK) {
			have_samples = 0;
			CurrentBuffer = (CurrentBuffer+1)%3;
		}
	}
	if(!(SND_TestPointer(mp3_voice,(void*)OutputBuffer[CurrentBuffer]) && SND_StatusVoice(mp3_voice)!=SND_UNUSED)) {
		if(have_samples==0) {
			MP3Playing = (buf_get(&OutputRingBuffer,OutputBuffer[CurrentBuffer],ADMA_BUFFERSIZE)>0);
			have_samples = 1;
		}
	}
#endif
}

void MP3Player_Pause() {
	if (!paused) {
		paused = TRUE;
		SND_PauseVoice(mp3_voice, 1);
		AUDIO_StopDMA();
	}
}

void MP3Player_Unpause() {
	if (paused) {
		paused = FALSE;
		AUDIO_StartDMA();
		SND_PauseVoice(mp3_voice, 0); // resume
	}
}

void MP3Player_SetSeconds(float seconds) {
	if (!cached_start.valid) skipped = 0;
	frames_to_skip = seconds * 38.28125;
}

bool seek_filter(struct mad_stream *stream, struct mad_frame *frame) {
    if (skipped < frames_to_skip) {
        skipped++;
        return true;  // Skip this frame
    } else {
        return false;
    }
}

void MP3Player_PreloadOffset(const void *buffer, s32 len, float seconds) {
	MP3Player_SetSeconds(seconds);
	if (seconds == 0) return;
	
	rambuffer.buf_addr = buffer;
	rambuffer.len = len;
	rambuffer.pos = 0;

	mp3cb_data = &rambuffer;
	mp3read = _mp3ramcopy;

	mad_stream_init(&Stream);
	mad_frame_init(&Frame);
	
	u8 *GuardPtr = NULL;

	bool exit = FALSE;
	bool atend = FALSE;
	while (!exit && !atend) {
		if ((Stream.buffer == NULL || Stream.error == MAD_ERROR_BUFLEN)) {
			u8 *ReadStart;
			s32 ReadSize, Remaining;

			if (Stream.next_frame != NULL) {
				Remaining = Stream.bufend - Stream.next_frame;
				memmove(InputBuffer, Stream.next_frame, Remaining);
				ReadStart = InputBuffer + Remaining;
				ReadSize = DATABUFFER_SIZE - Remaining;
			} else {
				ReadSize = DATABUFFER_SIZE;
				ReadStart = InputBuffer;
				Remaining = 0;
			}

			ReadSize = mp3read(mp3cb_data, ReadStart, ReadSize);
			if (ReadSize <= 0) {
				GuardPtr = ReadStart;
				memset(GuardPtr, 0, MAD_BUFFER_GUARD);
				ReadSize = MAD_BUFFER_GUARD;
				atend = true;
			}

			mad_stream_buffer(&Stream, InputBuffer, ReadSize + Remaining);
		}
		
		while (!mad_frame_decode(&Frame, &Stream)) {
			if (seek_filter(&Stream, &Frame)) {
				if (skipped == frames_to_skip && !cached_start.valid) {
					cached_start.frame_size = Stream.bufend - Stream.this_frame;
					memcpy(cached_start.frame_data, Stream.this_frame, cached_start.frame_size);
					cached_start.valid = true;
					struct _rambuffer *rb = (struct _rambuffer *)mp3cb_data;
					s32 remaining_bytes = Stream.bufend - Stream.this_frame;
					cached_start.byte_offset = rb->pos - remaining_bytes;
					exit = TRUE;
					break;
				}
				continue;
			}
		}
	}
	preloaded = TRUE;
}


float MP3Player_GetAmplitude(void)
{
	return mp3_amplitude;
}

void MP3Player_Volume(u32 volume)
{
	if(volume>255) volume = 255;

	mp3_volume = volume;
#ifdef __SNDLIB_H__
	SND_ChangeVolumeVoice(mp3_voice,volume,volume);
#endif
}