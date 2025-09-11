#pragma once

#include <ogc/lwp_watchdog.h>
#include <ogc/lwp.h>
#include <ogc/lwp_mutex.h>

#include "math.h"

#define STEPS_HZ 240
#define STEPS_DT ((1.f + frame_skipped) / STEPS_HZ) // 1/240 seconds per physics step
#define STEPS_DT_UNMOD (1.f / STEPS_HZ) // 1/240 seconds per physics step

#define INPUT_BUFFER_SIZE 8
#define INPUT_BUFFER_MASK (INPUT_BUFFER_SIZE-1)

#define ticks_to_secs_float(ticks) (((float)(ticks)/(float)(TB_TIMER_CLOCK*1000)))

extern bool enable_info;
extern float amplitude;
extern float dt;
extern float death_timer;

extern float completion_timer;
extern bool completion_shake;

extern u64 start_frame;

#define MAX_RAYS 8

typedef struct {
    float x, y;
    float angle;
    float startWidth, endWidth;
    float length;
    float elapsed;
    float duration;
    u32 color;
    bool active;
} Ray;

int game_loop();

void draw_rays();
void create_ray(float x, float y, float angle, float length, float startWidth, float endWidth, float duration, u32 color);
void erase_rays();

extern int frame_skipped;

int output_log(const char *fmt, ...);