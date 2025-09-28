#pragma once

#include "objects.h"

#define MAX_PARTICLES 512

typedef struct {
    int group_id;
    GameObject *parent_obj;
    float x, y;
    float vx, vy;
    float ax, ay;
    float gravity_x, gravity_y;
    float rotation;
    float life;
    bool active;
    bool rel_gravity;
    ColorAlpha color, start_color, end_color;
    ColorAlpha color_delta;
    float scale, start_scale, end_scale, scale_delta;
    float vscale;
    float velocity_angle; 
    float velocity_magnitude;
    float rotate_per_second;
    int texture_id;
    bool blending;
    bool lock_to_player;
    bool trifading;
    int priority;
    float elapsed;
    int player_id;
} Particle;

typedef struct {
    float angle, angleVar;
    float speed, speedVar;
    float gravity_x, gravity_y;
    bool rel_gravity;
    float life, lifeVar;
    float start_scale, start_scaleVar;
    float end_scale, end_scaleVar;
    ColorAlpha start_color, start_colorVar;
    ColorAlpha end_color, end_colorVar;
    bool blending;
    bool lock_to_player;
    bool trifading;
    float sourcePosVarX, sourcePosVarY;
    float rotatePerSecond;
    float rotatePerSecondVariance;
    float rotationStart;
    float rotationStartVariance;
    float rotationEnd;
    float rotationEndVariance;
    int priority;
    float minRadius;
    float maxRadius;
    int texture_id;
} ParticleTemplate;

enum ParticleTextures {
    PARTICLE_SQUARE,
    PARTICLE_CIRCLE,
    PARTICLE_CIRCUNFERENCE,
    PARTICLE_P1_TRAIL,
    PARTICLE_COIN,
    PARTICLE_KEY,
};

enum ParticleGroupID {
    CUBE_DRAG,
    SHIP_TRAIL,
    HOLDING_SHIP_TRAIL,
    SHIP_DRAG,
    ORB_PARTICLES,
    PAD_PARTICLES,
    GLITTER_EFFECT,
    PORTAL_PARTICLES,
    USE_EFFECT,
    ORB_HITBOX_EFFECT,
    P1_TRAIL,
    UFO_JUMP,
    UFO_TRAIL,
    DEATH_PARTICLES,
    DEATH_CIRCLE,
    BREAKABLE_BRICK_PARTICLES,
    COIN_PARTICLES,
    COIN_OBJ,
    SPEED_PORTAL_AMBIENT,
    SPEEDUP,
    DUAL_BALL_HITBOX_EFFECT,
    END_WALL_PARTICLES,
    END_WALL_COLL_CIRCLE,
    END_WALL_COLL_CIRCUNFERENCE,
    END_WALL_COMPLETE_CIRCLES,
    END_WALL_FIREWORK,
    END_WALL_TEXT_EFFECT,
    ROBOT_JUMP_PARTICLES,
    KEY_OBJ_PART,
    KEY_PARTICLES
};

extern ParticleTemplate particle_templates[];
extern GRRLIB_texImg *particleCircleTex;
extern GRRLIB_texImg *particleTex;

void spawn_particle(int group_id, float x, float y, GameObject *parent_obj);
void update_particles();
void draw_particles(int group_id);
void draw_obj_particles(int group_id, GameObject *parent_obj);
