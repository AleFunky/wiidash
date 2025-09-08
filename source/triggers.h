#pragma once

#include "objects.h"

#define MAX_MOVING_CHANNELS 50
#define MAX_ALPHA_CHANNELS 50
#define MAX_SPAWN_CHANNELS 100
#define MAX_PULSE_CHANNELS 50

struct ColTriggerBuffer {
    bool active;
    Color old_color;
    float old_alpha;
    Color new_color;
    float new_alpha;
    int copy_channel_id;
    HSV copy_channel_HSV;
    float seconds;
    float time_run;
};

struct PulseTriggerBuffer {
    bool active;

    Color color;           // keys 7, 8 and 9

    int target_color_id;   // key 23

    float fade_in;         // key 45
    float hold;            // key 46
    float fade_out;        // key 47
    int pulse_mode;        // key 48
    
    HSV copied_hsv;        // key 49
    int copied_color_id;   // key 50
    int target_group;      // key 51
    int pulse_target_type; // key 52

    bool main_only;        // key 65
    bool detail_only;      // key 66

    float seconds;
    float time_run;
    float fade_contribution;  // How much this pulse contributes to final color
    bool is_blending;        // Whether this pulse is blending with others
};

enum PulseMode {
    PULSE_MODE_COLOR,
    PULSE_MODE_HSV,
};

enum PulseTargetType {
    PULSE_TARGET_TYPE_CHANNEL,
    PULSE_TARGET_TYPE_GROUP,
};


struct MoveTriggerBuffer {
    bool active;
    int target_group;      // key 51
    int offsetX;           // key 28
    int offsetY;           // key 29
    int easing;            // key 30
    u8 lock_to_player_x:1; // key 58
    u8 lock_to_player_y:1; // key 59

    float move_last_x;
    float move_last_y;

    float seconds;
    float time_run;
};

struct AlphaTriggerBuffer {
    bool active;

    int target_group;         
    float new_alpha;

    float seconds;
    float time_run;

    float *initial_opacities;
};

struct SpawnTriggerBuffer {
    bool active;

    int target_group;  

    float seconds;
    float time_run;
};

extern struct ColTriggerBuffer col_trigger_buffer[COL_CHANNEL_COUNT];
extern struct MoveTriggerBuffer move_trigger_buffer[MAX_MOVING_CHANNELS];
extern struct AlphaTriggerBuffer alpha_trigger_buffer[MAX_ALPHA_CHANNELS];
extern struct SpawnTriggerBuffer spawn_trigger_buffer[MAX_SPAWN_CHANNELS];
extern struct PulseTriggerBuffer pulse_trigger_buffer[MAX_PULSE_CHANNELS];

void update_triggers();
void handle_triggers(GameObject *obj);

void handle_spawn_triggers();
void handle_col_triggers();
void handle_move_triggers();
void handle_alpha_triggers();
void handle_pulse_triggers();