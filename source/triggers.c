#include "easing.h"
#include "level_loading.h"
#include "game.h"
#include "objects.h"
#include "main.h"
#include "groups.h"
#include "triggers.h"

#include "collision.h"

#include <stdio.h>

#include "math.h"

#define MAX_DIRTY_OBJECTS 8192

static GameObject *dirty_objects[MAX_DIRTY_OBJECTS];
static int dirty_count = 0;

struct ColTriggerBuffer col_trigger_buffer[COL_CHANNEL_COUNT];
struct MoveTriggerBuffer move_trigger_buffer[MAX_MOVING_CHANNELS];
struct AlphaTriggerBuffer alpha_trigger_buffer[MAX_ALPHA_CHANNELS];
struct SpawnTriggerBuffer spawn_trigger_buffer[MAX_SPAWN_CHANNELS];
struct PulseTriggerBuffer pulse_trigger_buffer[MAX_PULSE_CHANNELS];

void process_dirty_objects();

void update_triggers() {
    handle_spawn_triggers();
    handle_pulse_triggers();
    handle_col_triggers();
    handle_move_triggers();
    handle_alpha_triggers();
    process_dirty_objects();
}

void mark_object_dirty(GameObject *obj) {
    if (!obj->dirty) {
        obj->dirty = TRUE;
        dirty_objects[dirty_count++] = obj;
    }
}

int obtain_free_pulse_slot() {
    for (int i = 0; i < MAX_PULSE_CHANNELS; i++) {
        if (!pulse_trigger_buffer[i].active) return i;
    }
    return -1;
}

void handle_pulse_triggers() {
    for (int i = 0; i < MAX_PULSE_CHANNELS; i++) {
        struct PulseTriggerBuffer *buffer = &pulse_trigger_buffer[i];

        if (buffer->active) {
            if (buffer->pulse_target_type == PULSE_TARGET_TYPE_CHANNEL) {
                if (buffer->pulse_mode == PULSE_MODE_HSV) {
                    Color copy_color = channels[buffer->copied_color_id].color;
                    if (!colors_equal(copy_color, buffer->color)) {
                        buffer->color = HSV_combine(copy_color, buffer->copied_hsv);
                    }
                }
                
                if (buffer->time_run <= buffer->fade_in) {
                    // Fade in
                    float fade_time = 1.f;

                    if (buffer->fade_in > 0) {
                        fade_time = buffer->time_run / buffer->fade_in;
                    }

                    Color channel_color = buffer->prefade_color;
                    
                    float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                    float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                    float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                    channels[buffer->target_color_id].color.r = r;
                    channels[buffer->target_color_id].color.g = g;
                    channels[buffer->target_color_id].color.b = b;
                } else if (buffer->time_run >= buffer->fade_in + buffer->hold) {
                    // Fade out
                    float fade_time = 1.f;

                    if (buffer->fade_out > 0) {
                        fade_time = (buffer->time_run - buffer->hold - buffer->fade_in) / buffer->fade_out;
                    }

                    Color channel_color = channels[buffer->target_color_id].non_pulse_color;
                    
                    float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                    float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                    float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                    channels[buffer->target_color_id].color.r = r;
                    channels[buffer->target_color_id].color.g = g;
                    channels[buffer->target_color_id].color.b = b;
                } else {
                    channels[buffer->target_color_id].color = buffer->color;
                }
            } else { // PULSE_TARGET_TYPE_GROUP
                if (buffer->pulse_mode == PULSE_MODE_HSV) {
                    Color copy_color = channels[buffer->copied_color_id].color;
                    if (!colors_equal(copy_color, buffer->color)) {
                        buffer->color = HSV_combine(copy_color, buffer->copied_hsv);
                    }
                }

                bool both = !buffer->main_only && !buffer->detail_only;
                if (buffer->time_run <= buffer->fade_in) {
                    float fade_time = 1.f;

                    if (buffer->fade_in > 0) {
                        fade_time = buffer->time_run / buffer->fade_in;                
                    }
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (both || buffer->main_only) {
                            Color channel_color = obj->object.main_color;
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                            obj->object.main_col_pulse.r = r;
                            obj->object.main_col_pulse.g = g;
                            obj->object.main_col_pulse.b = b;

                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            Color channel_color = obj->object.detail_color;
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                            obj->object.detail_col_pulse.r = r;
                            obj->object.detail_col_pulse.g = g;
                            obj->object.detail_col_pulse.b = b;

                            obj->object.detail_being_pulsed = TRUE;
                        }
                    }
                } else if (buffer->time_run >= buffer->fade_in + buffer->hold) {
                    // Fade out
                    float fade_time = 1.f;

                    if (buffer->fade_out > 0) {
                        fade_time = (buffer->time_run - buffer->hold - buffer->fade_in) / buffer->fade_out;
                    }
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (!buffer->started_fade_out) {
                            if (obj->object.num_pulses > 1) {
                                obj->object.main_color = obj->object.main_col_pulse;
                                obj->object.detail_color = obj->object.detail_col_pulse;
                            }
                            buffer->started_fade_out = TRUE;
                        }

                        if (both || buffer->main_only) {
                            Color channel_color = obj->object.main_color;
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                            obj->object.main_col_pulse.r = r;
                            obj->object.main_col_pulse.g = g;
                            obj->object.main_col_pulse.b = b;

                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            Color channel_color = obj->object.detail_color;
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                            obj->object.detail_col_pulse.r = r;
                            obj->object.detail_col_pulse.g = g;
                            obj->object.detail_col_pulse.b = b;
                            
                            obj->object.detail_being_pulsed = TRUE;
                        }
                    }
                } else {
                    // Hold
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (both || buffer->main_only) {
                            obj->object.main_col_pulse = buffer->color;

                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            obj->object.detail_col_pulse = buffer->color;

                            obj->object.detail_being_pulsed = TRUE;
                        }
                        
                    }
                }
            }
            
            buffer->time_run += STEPS_DT;
            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;
                if (buffer->pulse_target_type == PULSE_TARGET_TYPE_GROUP) {
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;
                        obj->object.main_being_pulsed = FALSE;
                        obj->object.detail_being_pulsed = FALSE;

                        obj->object.num_pulses--;
                    }
                }
            }
        }
    }
}

void upload_to_pulse_buffer(GameObject *obj) {
    int slot = obtain_free_pulse_slot();

    if (slot >= 0) {
        int channel = obj->trigger.pulse_trigger.target_group; // Pulse uses this for color id
        if (channel == 0) return;

        struct PulseTriggerBuffer *buffer = &pulse_trigger_buffer[slot];
        buffer->target_group = obj->trigger.pulse_trigger.target_group;

        buffer->color = obj->trigger.pulse_trigger.color;

        buffer->copied_color_id = obj->trigger.pulse_trigger.copied_color_id;
        buffer->copied_hsv = obj->trigger.pulse_trigger.copied_hsv;

        buffer->main_only = obj->trigger.pulse_trigger.main_only;
        buffer->detail_only = obj->trigger.pulse_trigger.detail_only;

        buffer->fade_in  = obj->trigger.pulse_trigger.fade_in;
        buffer->hold     = obj->trigger.pulse_trigger.hold;
        buffer->fade_out = obj->trigger.pulse_trigger.fade_out;

        buffer->pulse_mode = obj->trigger.pulse_trigger.pulse_mode;
        buffer->pulse_target_type = obj->trigger.pulse_trigger.pulse_target_type;
        
        buffer->started_fade_out = FALSE;

        buffer->target_color_id = channel;

        if (buffer->pulse_target_type == PULSE_TARGET_TYPE_GROUP) {
            for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                GameObject *obj = p->obj;
                if (obj->object.num_pulses > 0) {
                    if (obj->object.main_being_pulsed) obj->object.main_color = obj->object.main_col_pulse;
                    if (obj->object.detail_being_pulsed) obj->object.detail_color = obj->object.detail_col_pulse;
                }
                obj->object.num_pulses++;
            }
        } else {
            buffer->prefade_color = channels[channel].color;
        }


        //output_log("type %d mode %d\n", buffer->pulse_target_type, buffer->pulse_mode);
        //output_log("fade in %.2f hold %.2f fade out %.2f\n", buffer->fade_in, buffer->hold, buffer->fade_out);
        //output_log("channel %d\n", buffer->target_color_id);

        buffer->time_run = 0;
        buffer->seconds = obj->trigger.pulse_trigger.fade_in + obj->trigger.pulse_trigger.hold + obj->trigger.pulse_trigger.fade_out;   
        
        buffer->active = TRUE;
    }
}

void handle_col_triggers() {
    for (int chan = 0; chan < COL_CHANNEL_COUNT; chan++) {
        struct ColTriggerBuffer *buffer = &col_trigger_buffer[chan];

        if (buffer->active) {
            Color lerped_color;
            Color color_to_lerp = buffer->new_color;
            float alpha_to_lerp = buffer->new_alpha;
            float lerped_alpha;

            if (buffer->copy_channel_id) {
                color_to_lerp = channels[buffer->copy_channel_id].color;
                alpha_to_lerp = channels[buffer->copy_channel_id].alpha;
            }

            if (buffer->seconds > 0) {
                float multiplier = buffer->time_run / buffer->seconds;
                lerped_color = color_lerp(buffer->old_color, color_to_lerp, multiplier);
                lerped_alpha = (alpha_to_lerp - buffer->old_alpha) * multiplier + buffer->old_alpha;
            } else {
                lerped_color = color_to_lerp;
                lerped_alpha = alpha_to_lerp;
            }

            channels[chan].color = lerped_color;
            channels[chan].non_pulse_color = lerped_color;
            channels[chan].alpha = lerped_alpha;

            buffer->time_run += STEPS_DT;

            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;
                if (buffer->copy_channel_id) {
                    channels[chan].hsv = buffer->copy_channel_HSV;
                    channels[chan].copy_color_id = buffer->copy_channel_id;
                } else {
                    channels[chan].copy_color_id = 0;
                }
                channels[chan].color = color_to_lerp;
                channels[chan].non_pulse_color = color_to_lerp;
                channels[chan].alpha = alpha_to_lerp;
            }
        }
    }
}

void upload_to_buffer(GameObject *obj, int channel) {
    if (channel == 0) channel = 1;
    struct ColTriggerBuffer *buffer = &col_trigger_buffer[channel];
    buffer->active = TRUE;
    buffer->old_color = channels[channel].color;
    buffer->old_alpha = channels[channel].alpha;
    if (obj->trigger.col_trigger.p1_color) {
        buffer->new_color.r = p1.r;
        buffer->new_color.g = p1.g;
        buffer->new_color.b = p1.b;
        buffer->new_alpha = 1.f;
    } else if (obj->trigger.col_trigger.p2_color) {
        buffer->new_color.r = p2.r;
        buffer->new_color.g = p2.g;
        buffer->new_color.b = p2.b;
        buffer->new_alpha = 1.f;
    } else {
        buffer->new_color.r = obj->trigger.col_trigger.trig_colorR;
        buffer->new_color.g = obj->trigger.col_trigger.trig_colorG;
        buffer->new_color.b = obj->trigger.col_trigger.trig_colorB;
        buffer->new_alpha   = obj->trigger.col_trigger.opacity;
    }

    int copy_color_id = obj->trigger.col_trigger.copied_color_id;
    if (copy_color_id > 0) {
        buffer->copy_channel_HSV = obj->trigger.col_trigger.copied_hsv;
        buffer->copy_channel_id = copy_color_id;
    } else {
        buffer->copy_channel_id = 0;
    }

    if (channel < BG) {
        channels[channel].blending = obj->trigger.col_trigger.blending;
    }
    buffer->seconds = obj->trigger.trig_duration;
    buffer->time_run = 0;
}

int convert_ease(int easing) {
    switch (easing) {
        case 0: return EASE_LINEAR;

        case 1: return EASE_IN_OUT;
        case 2: return EASE_IN;
        case 3: return EASE_OUT;
        
        case 4: return ELASTIC_IN_OUT;
        case 5: return ELASTIC_IN;
        case 6: return ELASTIC_OUT;
        
        case 7: return BOUNCE_IN_OUT;
        case 8: return BOUNCE_IN;
        case 9: return BOUNCE_OUT;
        
        case 10: return EXPO_IN_OUT;
        case 11: return EXPO_IN;
        case 12: return EXPO_OUT;
        
        case 13: return SINE_IN_OUT;
        case 14: return SINE_IN;
        case 15: return SINE_OUT;
        
        case 16: return BACK_IN_OUT;
        case 17: return BACK_IN;
        case 18: return BACK_OUT;
    }
    return EASE_LINEAR;
}

static MovingGroup move_groups[MAX_GROUPS];

void init_move_triggers() {
    memset(move_groups, 0, sizeof(move_groups));
}

static void cache_move_group(int group_id) {
    if (move_groups[group_id].objects != NULL) {
        return; // Already cached
    }

    // Count objects first
    int count = 0;
    for (Node* p = get_group(group_id); p; p = p->next) {
        count++;
    }

    if (count == 0) return;

    // Allocate exactly what we need
    MovingObject* objects = malloc(count * sizeof(MovingObject));
    if (!objects) return;

    // Fill the cache
    int i = 0;
    for (Node* p = get_group(group_id); p; p = p->next) {
        objects[i].obj = p->obj;
        objects[i].x = *soa_x(p->obj);
        objects[i].y = *soa_y(p->obj);
        objects[i].old_x = *soa_x(p->obj);
        objects[i].old_y = *soa_y(p->obj);
        i++;
    }

    move_groups[group_id].objects = objects;
    move_groups[group_id].count = count;
    move_groups[group_id].capacity = count;
}

void process_dirty_objects() {
    for (int i = 0; i < dirty_count; i++) {
        GameObject *obj = dirty_objects[i];
        obj->dirty = false;
        
        float new_x = *soa_x(obj) + *soa_delta_x(obj);
        float new_y = *soa_y(obj) + *soa_delta_y(obj);
        
        update_object_section(obj, new_x, new_y);
    }

    dirty_count = 0; // reset list
}

void handle_move_triggers() {
    number_of_moving_objects = 0;
    // Reset deltas first
    for (int slot = 0; slot < MAX_MOVING_CHANNELS; slot++) {
        struct MoveTriggerBuffer* buffer = &move_trigger_buffer[slot];
        if (!buffer->active) continue;

        MovingGroup* group = &move_groups[buffer->target_group];
        if (!group->objects) {
            cache_move_group(buffer->target_group);
        }

        for (int i = 0; i < group->count; i++) {
            GameObject *obj = group->objects[i].obj;
            *soa_delta_x(obj) = 0;
            *soa_delta_y(obj) = 0;
        }
    }

    // Process active move triggers
    for (int slot = 0; slot < MAX_MOVING_CHANNELS; slot++) {
        struct MoveTriggerBuffer* buffer = &move_trigger_buffer[slot];
        if (!buffer->active) continue;

        MovingGroup* group = &move_groups[buffer->target_group];
        if (!group->objects) continue;

        // Calculate movement deltas once
        float delta_x, delta_y;
        float easing = easeTime(convert_ease(buffer->easing), 
                              buffer->time_run, buffer->seconds, 2.0f);

        if (buffer->lock_to_player_x) {
            delta_x = state.player.vel_x * STEPS_DT;
        } else {
            float before_x = buffer->move_last_x;
            float after_x = buffer->offsetX * easing;
            delta_x = after_x - before_x;
            buffer->move_last_x = after_x;
        }

        if (buffer->lock_to_player_y) {
            delta_y = state.player.vel_y * STEPS_DT;
        } else {
            float before_y = buffer->move_last_y;
            float after_y = buffer->offsetY * easing;
            delta_y = after_y - before_y;
            buffer->move_last_y = after_y;
        }
        

        // Update all objects in group
        for (int i = 0; i < group->count; i++) {
            MovingObject* mobj = &group->objects[i];
            GameObject* obj = mobj->obj;

            *soa_delta_x(obj) += delta_x;
            *soa_delta_y(obj) += delta_y;

            mark_object_dirty(obj);

            // Handle player collision
            if (obj->object.touching_player) {
                Player* player = (obj->object.touching_player == 1) ? 
                               &state.player : &state.player2;

                float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                if (grav_delta_y >= -MOVE_SPEED_DIVIDER && (player->on_ground || player->on_ceiling || player->slope_data.slope)) {
                    player->y += delta_y;
                }
            } else if (obj->object.prev_touching_player) {
                Player* player = (obj->object.prev_touching_player == 1) ?
                               &state.player : &state.player2;

                float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                if (grav_delta_y > MOVE_SPEED_DIVIDER) {
                    player->vel_y = grav_delta_y;
                }
            }

            number_of_moving_objects++;
        }

        // Update timer and check completion
        buffer->time_run += STEPS_DT;
        if (buffer->time_run > buffer->seconds) {
            buffer->active = FALSE;

            // Clear final deltas
            for (int i = 0; i < group->count; i++) {
                GameObject* obj = group->objects[i].obj;

                if (obj->object.touching_player) {
                    Player* player = (obj->object.touching_player == 1) ?
                                   &state.player : &state.player2;

                    float delta_y = *soa_delta_y(obj);
                    float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                    if (grav_delta_y > MOVE_SPEED_DIVIDER) {
                        player->vel_y = grav_delta_y;
                    }
                }
                *soa_delta_x(obj) = 0;
                *soa_delta_y(obj) = 0;
            }
        }
    }
}

void cleanup_move_triggers() {
    for (int i = 0; i < MAX_GROUPS; i++) {
        free(move_groups[i].objects);
        move_groups[i].objects = NULL;
        move_groups[i].count = 0;
        move_groups[i].capacity = 0;
    }
}

int obtain_free_spawn_slot() {
    for (int i = 0; i < MAX_SPAWN_CHANNELS; i++) {
        if (!spawn_trigger_buffer[i].active) return i;
    }
    return -1;
}

void upload_to_spawn_buffer(GameObject *obj) {
    int slot = obtain_free_spawn_slot();
    if (slot >= 0) {
        struct SpawnTriggerBuffer *buffer = &spawn_trigger_buffer[slot];

        buffer->target_group = obj->trigger.spawn_trigger.target_group;

        buffer->time_run = 0;
        buffer->seconds = obj->trigger.spawn_trigger.spawn_delay;
        
        buffer->active = TRUE;
    }
}

void handle_spawn_triggers() {
    for (int slot = 0; slot < MAX_SPAWN_CHANNELS; slot++) {
        struct SpawnTriggerBuffer *buffer = &spawn_trigger_buffer[slot];
        
        if (buffer->active) {
            buffer->time_run += STEPS_DT;
            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;

                // Set new alpha on all objects
                for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                    GameObject *obj = p->obj;
                    if (obj->type != TYPE_NORMAL_OBJECT) {
                        run_trigger(obj);
                    }
                }
            }
        }
    }
}

int obtain_free_alpha_slot() {
    for (int i = 0; i < MAX_ALPHA_CHANNELS; i++) {
        if (!alpha_trigger_buffer[i].active) return i;
    }
    return -1;
}

void upload_to_alpha_buffer(GameObject *obj) {
    if (obj->trigger.trig_duration == 0) {
        for (Node *p = get_group(obj->trigger.alpha_trigger.target_group); p; p = p->next) {
            p->obj->opacity = obj->trigger.alpha_trigger.opacity;
            if (p->obj->object.child_object) {
                p->obj->object.child_object->opacity = obj->trigger.alpha_trigger.opacity;
            }
        }
        return;
    }
    
    int slot = obtain_free_alpha_slot();

    if (slot >= 0) {
        struct AlphaTriggerBuffer *buffer = &alpha_trigger_buffer[slot];

        buffer->new_alpha = obj->trigger.alpha_trigger.opacity;
        buffer->target_group = obj->trigger.alpha_trigger.target_group;

        buffer->time_run = 0;
        buffer->seconds = obj->trigger.trig_duration;
        
        int count = 0;

        float capacity = 8;
        
        float *opacities = malloc(sizeof(float) * capacity); // Initial 8

        for (Node *p = get_group(buffer->target_group); p; p = p->next) {
            if (count >= capacity) {
                capacity *= 2; // grow exponentially
                float *tmp = realloc(opacities, sizeof(float) * capacity);
                if (!tmp) {
                    free(opacities);
                    output_log("Couldn't allocate alpha values\n");
                    return;
                }
                opacities = tmp;
            }

            GameObject *obj = p->obj;
            opacities[count++] = obj->opacity;
        }
        buffer->initial_opacities = opacities;
        
        buffer->active = TRUE;
    }
}

void handle_alpha_triggers() {
    for (int slot = 0; slot < MAX_ALPHA_CHANNELS; slot++) {
        struct AlphaTriggerBuffer *buffer = &alpha_trigger_buffer[slot];
        
        if (buffer->active) {
            int i = 0;
            for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                GameObject *obj = p->obj;
                float lerped_alpha;

                if (buffer->seconds > 0) {
                    float multiplier = buffer->time_run / buffer->seconds;
                    lerped_alpha = (buffer->new_alpha - buffer->initial_opacities[i]) * multiplier + buffer->initial_opacities[i];
                } else {
                    lerped_alpha = buffer->new_alpha;
                }

                obj->opacity = lerped_alpha;
                if (obj->object.child_object) {
                    obj->object.child_object->opacity = lerped_alpha;
                }

                i++;
            }
            buffer->time_run += STEPS_DT;

            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;

                // Set new alpha on all objects
                for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                    GameObject *obj = p->obj;
                    obj->opacity = buffer->new_alpha;
                    
                    if (obj->object.child_object) {
                        obj->object.child_object->opacity = buffer->new_alpha;
                    }
                }

                free(buffer->initial_opacities);
            }
        }
    }
}


int obtain_free_move_slot() {
    for (int i = 0; i < MAX_MOVING_CHANNELS; i++) {
        if (!move_trigger_buffer[i].active) return i;
    }
    return -1;
}

void upload_to_move_buffer(GameObject *obj) {
    int slot = obtain_free_move_slot();
    if (slot >= 0) {
        struct MoveTriggerBuffer *buffer = &move_trigger_buffer[slot];

        buffer->easing = obj->trigger.move_trigger.easing;

        buffer->offsetX = obj->trigger.move_trigger.offsetX;
        buffer->offsetY = obj->trigger.move_trigger.offsetY;

        buffer->lock_to_player_x = obj->trigger.move_trigger.lock_to_player_x;
        buffer->lock_to_player_y = obj->trigger.move_trigger.lock_to_player_y;

        buffer->target_group = obj->trigger.move_trigger.target_group;

        buffer->time_run = 0;
        buffer->seconds = obj->trigger.trig_duration;

        buffer->move_last_x = 0;
        buffer->move_last_y = 0;
        
        buffer->active = TRUE;
    }
}

void run_trigger(GameObject *obj) {
    if (obj->toggled) return;

    switch (obj->id) {
        case TRIGGER_FADE_NONE:
            current_fading_effect = FADE_NONE;
            break;
            
        case TRIGGER_FADE_UP:
            current_fading_effect = FADE_UP;
            break;
            
        case TRIGGER_FADE_DOWN:
            current_fading_effect = FADE_DOWN;
            break;
            
        case TRIGGER_FADE_RIGHT:
            current_fading_effect = FADE_RIGHT;
            break;
            
        case TRIGGER_FADE_LEFT:
            current_fading_effect = FADE_LEFT;
            break;
            
        case TRIGGER_FADE_SCALE_IN:
            current_fading_effect = FADE_SCALE_IN;
            break;
            
        case TRIGGER_FADE_SCALE_OUT:
            current_fading_effect = FADE_SCALE_OUT;
            break;
        
        case TRIGGER_FADE_INWARDS:
            current_fading_effect = FADE_INWARDS;
            break;

        case TRIGGER_FADE_OUTWARDS:
            current_fading_effect = FADE_OUTWARDS;
            break;
        
        case TRIGGER_FADE_LEFT_SEMICIRCLE:
            current_fading_effect = FADE_CIRCLE_LEFT;
            break;

        case TRIGGER_FADE_RIGHT_SEMICIRCLE:
            current_fading_effect = FADE_CIRCLE_RIGHT;
            break;

        case BG_TRIGGER:
            upload_to_buffer(obj, BG);
            if (!obj->trigger.col_trigger.tintGround) break;
        
        case GROUND_TRIGGER:
            upload_to_buffer(obj, GROUND);
            break;
                    
        case LINE_TRIGGER:
        case V2_0_LINE_TRIGGER: // gd converts 1.4 line trigger to 2.0 one for some reason
            upload_to_buffer(obj, LINE);
            break;
        
        case OBJ_TRIGGER:
            upload_to_buffer(obj, OBJ);
            break;
        
        case OBJ_2_TRIGGER:
            upload_to_buffer(obj, 1);
            break;
        
        case COL2_TRIGGER: // col 2
            upload_to_buffer(obj, 2);
            break;

        case COL3_TRIGGER: // col 3
            upload_to_buffer(obj, 3);
            break;
            
        case COL4_TRIGGER: // col 4
            upload_to_buffer(obj, 4);
            break;
            
        case THREEDL_TRIGGER: // 3DL
            upload_to_buffer(obj, THREEDL);
            break;

        case ENABLE_TRAIL:
            p1_trail = TRUE;
            break;
        
        case DISABLE_TRAIL:
            p1_trail = FALSE;
            break;

        case G_2_TRIGGER:
            upload_to_buffer(obj, G2);
            break;

        case COL_TRIGGER: // 2.0 color trigger
            upload_to_buffer(obj, obj->trigger.col_trigger.target_color_id);
            break;
        
        case MOVE_TRIGGER: // Move trigger
            upload_to_move_buffer(obj);
            break;

        case ALPHA_TRIGGER: // Alpha trigger
            upload_to_alpha_buffer(obj);
            break;
        
        case TOGGLE_TRIGGER:
            for (Node *p = get_group(obj->trigger.toggle_trigger.target_group); p; p = p->next) {
                GameObject *toggled_obj = p->obj;
                toggled_obj->toggled = !obj->trigger.toggle_trigger.activate_group;
            }
            break;
        case SPAWN_TRIGGER:
            upload_to_spawn_buffer(obj);
            break;
        case PULSE_TRIGGER:
            upload_to_pulse_buffer(obj);
            break;
    }
    obj->activated[0] = TRUE;
}

void handle_triggers(GameObject *obj) {
    int obj_id = obj->id;
    Player *player = &state.player;
    
    if ((objects[obj_id].is_trigger || obj->id > OBJECT_COUNT) && !obj->activated[0]) {
        if (obj->trigger.touch_triggered) {
            if (intersect(
                player->x, player->y, player->width, player->height, 0, 
                *soa_x(obj), *soa_y(obj), 30, 30, obj->rotation
            )) {
                run_trigger(obj);
            }
        } else if (!obj->trigger.spawn_triggered) {
            if (*soa_x(obj) < state.player.x) {
                run_trigger(obj);
            }
        }
    }
}