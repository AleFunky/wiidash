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

typedef struct Animation {
    char name[64];
    AnimationFrame frames[64];
    int frameCount;
} Animation;

typedef struct {
    Animation animations[16];
    int animCount;
} AnimationLibrary;


typedef struct {
    GRRLIB_texImg *texture;
    int default_col_channel;
    u8 color_channel_type;
    u8 part_id;
} AnimationPart;

typedef struct {
    AnimationPart parts[10];
    Animation *anim;
    float fps;
    u8 part_count;
    u8 has_main;
    u8 has_detail;
} AnimationDefinition;

typedef struct {
    GRRLIB_texImg *texture;
    int layer_num;
    float scale;
} FrameLayer;

typedef struct {
    FrameLayer layers[MAX_OBJECT_LAYERS];
    int layer_count;
} Frame;

typedef struct {
    Frame frames[11];
    int frame_count;
    float fps;
} FramesDefinition;

FramesDefinition prepare_fire_1_animation();
FramesDefinition prepare_fire_2_animation();
FramesDefinition prepare_fire_3_animation();
FramesDefinition prepare_fire_4_animation();

AnimationDefinition prepare_monster_1_animation();
AnimationDefinition prepare_black_sludge_animation();

void unload_animation_definition(AnimationDefinition def);
void unload_frame_definition(FramesDefinition def);

void playAnimation(Animation* anim, float time);
void playObjAnimation(GameObject *obj, AnimationDefinition definition, float time);
void playRobotAnimation(Player *player, 
                               Animation* fromAnim, 
                               Animation* toAnim,
                               float time, 
                               float scale, 
                               float rotation,
                               float blendFactor);
void parsePlist(const char* filename, AnimationLibrary* lib);
Animation* getAnimation(AnimationLibrary* lib, const char* name);
GRRLIB_texImg *get_frame(FramesDefinition definition, int layer_num, float time, float *scale_out);