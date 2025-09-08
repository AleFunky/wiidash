#pragma once
#include <mxml.h>
#include "player.h"

typedef struct {
    float x, y;
    float sx, sy;
    float rotation;
    int z;
} SpritePart;

typedef struct {
    char frameName[64];
    SpritePart parts[16];
    int partCount;
} AnimationFrame;

typedef struct {
    char name[64];
    AnimationFrame frames[64];
    int frameCount;
    float fps;
} Animation;

typedef struct {
    Animation animations[16];
    int animCount;
} AnimationLibrary;

void playAnimation(Animation* anim, float time);
void playRobotAnimation(Player *player, Animation* anim, float time);
void parsePlist(const char* filename, AnimationLibrary* lib);
Animation* getAnimation(AnimationLibrary* lib, const char* name);