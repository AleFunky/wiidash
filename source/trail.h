// Adapted from OpenGD

#ifndef MOTION_TRAIL_H
#define MOTION_TRAIL_H

#include <gccore.h>
#include "../GRRLIB/GRRLIB/GRRLIB/grrlib.h"

#include "objects.h"

#define MAX_TRAIL_POINTS 128
#define TRAIL_CLEAR_DISTANCE 30.f

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    float u, v;
} Tex2F;

typedef struct {
    bool appendNewPoints;
    bool startingPositionInitialized;
    bool waveTrail;

    int nuPoints;
    int previousNuPoints;
    int actualNuPoints;
    int maxPoints;
    int offscreenCount;

    float opacity;
    float fadeDelta;
    float minSeg;
    float stroke;

    Vec2 positionR;
    Color displayedColor;

    GRRLIB_texImg *texture;

    float pointState[MAX_TRAIL_POINTS];
    Vec2 pointVertexes[MAX_TRAIL_POINTS];
    Vec2 vertices[MAX_TRAIL_POINTS * 2];
    u8 colorPointer[MAX_TRAIL_POINTS * 8]; // RGBA * 2 per point
    Tex2F texCoords[MAX_TRAIL_POINTS * 2];
    
    Vec2 centerVertices[MAX_TRAIL_POINTS * 2];

    Vec2 lastStopPosition;
    bool wasStopped;

} MotionTrail;

extern MotionTrail trail;
extern MotionTrail trail_p1;
extern MotionTrail trail_p2;

extern MotionTrail wave_trail;
extern MotionTrail wave_trail_p1;
extern MotionTrail wave_trail_p2;


void MotionTrail_Init(MotionTrail* trail, float fade, float minSeg, float stroke, bool waveTrail, Color color, GRRLIB_texImg *tex);
void MotionTrail_UpdateWaveTrail(MotionTrail *trail, float delta);
void MotionTrail_Update(MotionTrail* trail, float delta);
void MotionTrail_ResumeStroke(MotionTrail* trail);
void MotionTrail_Clear(MotionTrail *trail);
void MotionTrail_StopStroke(MotionTrail* trail);
void MotionTrail_Draw(MotionTrail* trail);
void MotionTrail_DrawWaveTrail(MotionTrail *trail);

void MotionTrail_AddWavePoint(MotionTrail* trail);

#endif