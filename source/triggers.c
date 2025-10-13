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

void handle_copy_channels() {
    for (int chan = 0; chan < COL_CHANNEL_COUNT; chan++) {
        int copy_color_id = channels[chan].copy_color_id;
        if (copy_color_id > 0) {
            Color color = channels[copy_color_id].color;
            color = HSV_combine(color, channels[chan].hsv);
            channels[chan].color = color;
            channels[chan].non_pulse_color = color;
        }
    }
}

void update_triggers() {
    handle_spawn_triggers();
    handle_col_triggers();
    handle_copy_channels();
    handle_pulse_triggers();
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
            if (buffer->pulse_mode == PULSE_MODE_HSV) {
                int id = buffer->copied_color_id;
                if (id == 0) {
                    id = buffer->target_color_id;
                }
                Color copy_color = channels[id].non_pulse_color;
                if (!colors_equal(copy_color, buffer->color)) {
                    buffer->color = HSV_combine(copy_color, buffer->copied_hsv);
                }
            }

            struct ColorChannel *channel = &channels[buffer->target_color_id];
            if (buffer->pulse_target_type == PULSE_TARGET_TYPE_CHANNEL) {
                if (buffer->time_run <= buffer->fade_in) {
                    // Fade in
                    float fade_time = 1.f;

                    if (buffer->fade_in > 0) {
                        fade_time = buffer->time_run / buffer->fade_in;
                    }

                    Color channel_color = channels[buffer->target_color_id].non_pulse_color;

                    if (buffer->pulse_index > 0) {
                        channel_color = channels[buffer->target_color_id].pulses[buffer->pulse_index - 1];
                    }
                    
                    float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                    float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                    float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                    channels[buffer->target_color_id].color.r = r;
                    channels[buffer->target_color_id].color.g = g;
                    channels[buffer->target_color_id].color.b = b;

                    channels[buffer->target_color_id].pulses[buffer->pulse_index] = channels[buffer->target_color_id].color;
                } else if (buffer->time_run >= buffer->fade_in + buffer->hold) {
                    // Fade out
                    float fade_time = 1.f;

                    if (buffer->fade_out > 0) {
                        fade_time = (buffer->time_run - buffer->hold - buffer->fade_in) / buffer->fade_out;
                    }

                    Color channel_color = channels[buffer->target_color_id].non_pulse_color;

                    if (buffer->pulse_index > 0) {
                        channel_color = channels[buffer->target_color_id].pulses[buffer->pulse_index - 1];
                    }
                    
                    float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                    float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                    float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                    channels[buffer->target_color_id].color.r = r;
                    channels[buffer->target_color_id].color.g = g;
                    channels[buffer->target_color_id].color.b = b;

                    channels[buffer->target_color_id].pulses[buffer->pulse_index] = channels[buffer->target_color_id].color;
                } else {
                    channels[buffer->target_color_id].color = buffer->color;
                    channels[buffer->target_color_id].pulses[buffer->pulse_index] = buffer->color;
                }
            } else { // PULSE_TARGET_TYPE_GROUP
                bool both = !buffer->main_only && !buffer->detail_only;
                if (buffer->time_run <= buffer->fade_in) {
                    float fade_time = 1.f;

                    if (buffer->fade_in > 0) {
                        fade_time = buffer->time_run / buffer->fade_in;                
                    }
                    int index = 0;
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (both || buffer->main_only) {
                            int main_pulse_index = buffer->main_pulse_index[index];

                            Color channel_color = obj->object.main_non_pulse_color;
                            if (main_pulse_index > 0) {
                                channel_color = obj->object.main_pulses[main_pulse_index - 1];
                            }
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                            obj->object.main_pulses[main_pulse_index].r = r;
                            obj->object.main_pulses[main_pulse_index].g = g;
                            obj->object.main_pulses[main_pulse_index].b = b;

                            obj->object.main_color = obj->object.main_pulses[main_pulse_index];
                            
                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            int detail_pulse_index = buffer->detail_pulse_index[index];

                            Color channel_color = obj->object.detail_non_pulse_color;
                            if (detail_pulse_index > 0) {
                                channel_color = obj->object.detail_pulses[detail_pulse_index - 1];
                            }

                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (1.f - fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (1.f - fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (1.f - fade_time));

                            obj->object.detail_pulses[detail_pulse_index].r = r;
                            obj->object.detail_pulses[detail_pulse_index].g = g;
                            obj->object.detail_pulses[detail_pulse_index].b = b;
                            
                            obj->object.detail_color = obj->object.detail_pulses[detail_pulse_index];

                            obj->object.detail_being_pulsed = TRUE;
                        }

                        index++;
                    }
                } else if (buffer->time_run >= buffer->fade_in + buffer->hold) {
                    // Fade out
                    float fade_time = 1.f;

                    if (buffer->fade_out > 0) {
                        fade_time = (buffer->time_run - buffer->hold - buffer->fade_in) / buffer->fade_out;
                    }
                    int index = 0;
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (both || buffer->main_only) {
                            int main_pulse_index = buffer->main_pulse_index[index];
                            
                            Color channel_color = obj->object.main_non_pulse_color;
                            if (main_pulse_index > 0) {
                                channel_color = obj->object.main_pulses[main_pulse_index - 1];
                            }
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                            obj->object.main_pulses[main_pulse_index].r = r;
                            obj->object.main_pulses[main_pulse_index].g = g;
                            obj->object.main_pulses[main_pulse_index].b = b;

                            obj->object.main_color = obj->object.main_pulses[main_pulse_index];

                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            int detail_pulse_index = buffer->detail_pulse_index[index];
                            
                            Color channel_color = obj->object.detail_non_pulse_color;
                            if (detail_pulse_index > 0) {
                                channel_color = obj->object.detail_pulses[detail_pulse_index - 1];
                            }
                            
                            float r = (buffer->color.r - (buffer->color.r - channel_color.r) * (fade_time));
                            float g = (buffer->color.g - (buffer->color.g - channel_color.g) * (fade_time));
                            float b = (buffer->color.b - (buffer->color.b - channel_color.b) * (fade_time));

                            obj->object.detail_pulses[detail_pulse_index].r = r;
                            obj->object.detail_pulses[detail_pulse_index].g = g;
                            obj->object.detail_pulses[detail_pulse_index].b = b;

                            obj->object.detail_color = obj->object.detail_pulses[detail_pulse_index];

                            obj->object.detail_being_pulsed = TRUE;
                        }

                        index++;
                    }
                } else {
                    // Hold
                    int index = 0;
                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;

                        if (both || buffer->main_only) {
                            int main_pulse_index = buffer->main_pulse_index[index];

                            obj->object.main_pulses[main_pulse_index] = buffer->color;
                            obj->object.main_color = buffer->color;

                            obj->object.main_being_pulsed = TRUE;
                        }

                        if (both || buffer->detail_only) {
                            int detail_pulse_index = buffer->detail_pulse_index[index];

                            obj->object.detail_pulses[detail_pulse_index] = buffer->color;
                            obj->object.detail_color = buffer->color;

                            obj->object.detail_being_pulsed = TRUE;
                        }
                        index++;
                    }
                }
            }
            
            buffer->time_run += STEPS_DT;
            if (buffer->time_run > buffer->seconds) {
                if (buffer->pulse_target_type == PULSE_TARGET_TYPE_GROUP) {
                    //printf("End of pulse at slot %d\n", i);
                    bool both = !buffer->main_only && !buffer->detail_only;

                    for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                        GameObject *obj = p->obj;
                        if (both || buffer->main_only) {
                            obj->object.num_main_pulses--;

                            if (!obj->object.num_main_pulses) obj->object.main_being_pulsed = FALSE;
                        }

                        if (both || buffer->detail_only) {
                            obj->object.num_detail_pulses--;

                            if (!obj->object.num_detail_pulses) obj->object.detail_being_pulsed = FALSE;
                        }
                    }
                    free(buffer->main_pulse_index);
                    free(buffer->detail_pulse_index);
                    
                    buffer->main_pulse_index = NULL;
                    buffer->detail_pulse_index = NULL;
                } else {
                    //printf("End of pulse for channel %d, %d at slot %d\n", buffer->target_color_id, buffer->pulse_index, i);
                    for (int j = MAX_PULSE_CHANNELS - 1; j > i; j--) {
                        struct PulseTriggerBuffer *target_buffer = &pulse_trigger_buffer[j];
                        if (target_buffer->active && target_buffer->pulse_target_type == PULSE_TARGET_TYPE_CHANNEL) {
                            if (buffer->target_color_id == target_buffer->target_color_id) {
                                int idx = target_buffer->pulse_index - 1; // index to remove
                                //printf("Pulse removed from slot %d\n", j);
                                
                                // Shift pulses down
                                for (int k = idx; k < channels[target_buffer->target_color_id].num_pulses - 1 && k < MAX_PULSES_PER_CHANNEL; k++) {
                                    channel->pulses[k] = channel->pulses[k + 1];
                                    //printf("%d <- %d\n", k, k + 1);
                                }
                                
                                target_buffer->pulse_index--;
                            }
                        }
                    }
                    Color channel_color = channels[buffer->target_color_id].non_pulse_color;

                    if (buffer->pulse_index > 0) {
                        channel_color = channels[buffer->target_color_id].pulses[buffer->pulse_index - 1];
                    }

                    channels[buffer->target_color_id].color = channel_color;
                    channels[buffer->target_color_id].num_pulses--;
                }
                for (int j = i; j < MAX_PULSE_CHANNELS - 1; j++) {
                    // Shift buffer array
                    if (pulse_trigger_buffer[j].active) {
                        pulse_trigger_buffer[j] = pulse_trigger_buffer[j + 1];
                        //printf("Setting %d to %d\n", j, j+1);
                    }
                }

                // If last slot, nothing is gonna move into the slot so just disable it
                pulse_trigger_buffer[MAX_PULSE_CHANNELS - 1].active = FALSE;
                
                // Make the game run the pulse moved into the current slot
                i--;
            }
        }
    }

    //for (int i = 0; i < MAX_PULSE_CHANNELS; i++) {
    //    struct PulseTriggerBuffer *buffer = &pulse_trigger_buffer[i];
    //    
    //    if (buffer->active && buffer->pulse_target_type == PULSE_TARGET_TYPE_CHANNEL && buffer->target_color_id == GROUND) {
    //        Color channel_color = channels[buffer->target_color_id].non_pulse_color;
    //
    //        if (buffer->pulse_index > 0) {
    //            channel_color = channels[buffer->target_color_id].pulses[buffer->pulse_index - 1];
    //        }
    //        printf("Slot %d - color %d, %d, %d pulse %d\n", i, channel_color.r, channel_color.g, channel_color.b, buffer->pulse_index);
    //    }
    //}
}

void upload_to_pulse_buffer(GameObject *obj) {
    //for (int i = 0; i < 10; i++) {
    //    printf("%d - %s\n", i, (pulse_trigger_buffer[i].active) ? "used" : "empty");
    //}

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
            int objects = 0;
            for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                objects++;
            }

            buffer->main_pulse_index = malloc(sizeof(int) * objects);
            buffer->detail_pulse_index = malloc(sizeof(int) * objects);

            bool both = !buffer->main_only && !buffer->detail_only;
            int index = 0;
            for (Node *p = get_group(buffer->target_group); p; p = p->next) {
                GameObject *obj = p->obj;

                if (both || buffer->main_only) {
                    if (obj->object.num_main_pulses >= MAX_PULSES_PER_GROUP) {
                        free(buffer->main_pulse_index);
                        free(buffer->detail_pulse_index);

                        buffer->main_pulse_index = NULL;
                        buffer->detail_pulse_index = NULL;
                        return;
                    }

                    buffer->main_pulse_index[index] = obj->object.num_main_pulses++;
                }

                if (both || buffer->detail_only) {
                    if (obj->object.num_detail_pulses >= MAX_PULSES_PER_GROUP) {
                        free(buffer->main_pulse_index);
                        free(buffer->detail_pulse_index);
                        
                        buffer->main_pulse_index = NULL;
                        buffer->detail_pulse_index = NULL;
                        return;
                    }
                    
                    buffer->detail_pulse_index[index] = obj->object.num_detail_pulses++;
                }
                index++;
            }
        } else {
            // If ran out of pulses for this channel, return
            if (channels[buffer->target_color_id].num_pulses >= MAX_PULSES_PER_CHANNEL) return;

            buffer->pulse_index = channels[buffer->target_color_id].num_pulses++;
            //printf("New pulse for channel %d, %d at slot %d\n", buffer->target_color_id, buffer->pulse_index, slot);
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
    
    if (obj->trigger.trig_duration == 0) {
        int chan = channel;
        Color color_to_lerp = buffer->new_color;
        float alpha_to_lerp = buffer->new_alpha;

        if (buffer->copy_channel_id) {
            channels[chan].hsv = buffer->copy_channel_HSV;
            channels[chan].copy_color_id = buffer->copy_channel_id;
        } else {
            channels[chan].copy_color_id = 0;
        }
        channels[chan].color = color_to_lerp;
        channels[chan].non_pulse_color = color_to_lerp;
        channels[chan].alpha = alpha_to_lerp;
        return;
    }
    
    buffer->seconds = obj->trigger.trig_duration;
    buffer->time_run = 0;
    buffer->active = TRUE;
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
    GameObject **objects = malloc(count * sizeof(GameObject*));
    if (!objects) return;

    // Fill the cache
    int i = 0;
    for (Node* p = get_group(group_id); p; p = p->next) {
        objects[i] = p->obj;
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

        *soa_delta_x(obj) = 0;
        *soa_delta_y(obj) = 0;
    }

    dirty_count = 0; // reset list
}

int obtain_free_move_slot() {
    for (int i = 0; i < MAX_MOVING_CHANNELS; i++) {
        if (!move_trigger_buffer[i].active) return i;
    }
    return -1;
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
    }

    // Process active move triggers
    for (int slot = 0; slot < MAX_MOVING_CHANNELS; slot++) {
        struct MoveTriggerBuffer* buffer = &move_trigger_buffer[slot];
        
        if (!buffer->active) continue;

        MovingGroup* group = &move_groups[buffer->target_group];
        if (!group->objects) {
            buffer->active = FALSE;
            continue;
        }

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
            delta_y = state.player.delta_y;
        } else {
            float before_y = buffer->move_last_y;
            float after_y = buffer->offsetY * easing;
            delta_y = after_y - before_y;
            buffer->move_last_y = after_y;
        }
        

        // Update all objects in group
        for (int i = 0; i < group->count; i++) {
            GameObject* obj = group->objects[i];

            if (LIKELY(*soa_type(obj) == TYPE_NORMAL_OBJECT)) *soa_delta_x(obj) += delta_x;
            *soa_delta_y(obj) += delta_y;

            mark_object_dirty(obj);

            // Handle player collision
            if (UNLIKELY(*soa_touching_player(obj))) {
                Player* player = (*soa_touching_player(obj) == 1) ? 
                               &state.player : &state.player2;

                float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                if (grav_delta_y >= -MOVE_SPEED_DIVIDER) {
                    player->y += delta_y;
                }
            } else if (UNLIKELY(*soa_prev_touching_player(obj))) {
                Player* player = (*soa_prev_touching_player(obj) == 1) ?
                               &state.player : &state.player2;

                float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                if (grav_delta_y > MOVE_SPEED_DIVIDER) {
                    player->vel_y = grav_delta_y;
                }
            }
        }
        
        number_of_moving_objects += group->count;

        // Update timer and check completion
        buffer->time_run += STEPS_DT;
        if (buffer->time_run > buffer->seconds) {
            buffer->active = FALSE;

            // Clear final deltas
            for (int i = 0; i < group->count; i++) {
                GameObject* obj = group->objects[i];

                if (*soa_touching_player(obj)) {
                    Player* player = (*soa_touching_player(obj) == 1) ?
                                   &state.player : &state.player2;

                    float delta_y = *soa_delta_y(obj);
                    float grav_delta_y = grav(player, delta_y * STEPS_HZ);
                    if (grav_delta_y > MOVE_SPEED_DIVIDER) {
                        player->vel_y = grav_delta_y;
                    }
                }
            }
        }
    }
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

void cleanup_move_triggers() {
    for (int i = 0; i < MAX_GROUPS; i++) {
        if (move_groups[i].objects) free(move_groups[i].objects);
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
                    // For it to be spawned, the following must be met:
                    // - Spawn trigger checkbox is tick
                    // - Object is a trigger
                    // - Either the object is multi trigger or not activated
                    // - The object is not toggled off
                    if (obj->trigger.spawn_triggered && *soa_type(obj) != TYPE_NORMAL_OBJECT && (obj->trigger.multi_triggered || !obj->activated[0]) && !obj->toggled) {
                        printf("Spawned trigger %d group %d\n", obj->soa_index, buffer->target_group);
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
    Node *p = get_group(obj->trigger.alpha_trigger.target_group);
    
    if (!p) return;

    if (obj->trigger.trig_duration == 0) {
        p->opacity = obj->trigger.alpha_trigger.opacity;
        return;
    }

    int slot = obtain_free_alpha_slot();
    int target_group = obj->trigger.alpha_trigger.target_group;
    
    // Replace old triggers of the same group
    for (int i = 0; i < MAX_ALPHA_CHANNELS; i++) {
        if (target_group == alpha_trigger_buffer[i].target_group) {
            slot = i;
            break;
        }
    }

    if (slot >= 0) {
        struct AlphaTriggerBuffer *buffer = &alpha_trigger_buffer[slot];
        
        buffer->new_alpha = obj->trigger.alpha_trigger.opacity;
        buffer->target_group = target_group;

        buffer->time_run = 0;
        buffer->seconds = obj->trigger.trig_duration;

        buffer->old_alpha = p->opacity;
        
        buffer->active = TRUE;
    }
}

void handle_alpha_triggers() {
    for (int slot = 0; slot < MAX_ALPHA_CHANNELS; slot++) {
        struct AlphaTriggerBuffer *buffer = &alpha_trigger_buffer[slot];
        
        if (buffer->active) {
            Node *p = get_group(buffer->target_group);
            if (!p) continue;

            float lerped_alpha;

            if (buffer->seconds > 0) {
                float multiplier = buffer->time_run / buffer->seconds;
                lerped_alpha = (buffer->new_alpha - buffer->old_alpha) * multiplier + buffer->old_alpha;
            } else {
                lerped_alpha = buffer->new_alpha;
            }

            p->opacity = lerped_alpha;
    
            buffer->time_run += STEPS_DT;

            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;
                p->opacity = buffer->new_alpha;
            }
        }
    }
}

void run_trigger(GameObject *obj) {
    if (obj->toggled) return;

    switch (*soa_id(obj)) {
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
    int obj_id = *soa_id(obj);
    Player *player = &state.player;
    Player *player_2 = &state.player2;
    
    if ((objects[obj_id].is_trigger) && !obj->activated[0]) {
        if (obj->trigger.touch_triggered) {
            // Try p1
            if (intersect(
                player->x, player->y, player->width, player->height, 0, 
                *soa_x(obj), *soa_y(obj), obj->width, obj->height, obj->rotation
            )) {
                run_trigger(obj);
            } else
            // Try now p2
            if (intersect(
                player_2->x, player_2->y, player_2->width, player_2->height, 0, 
                *soa_x(obj), *soa_y(obj), obj->width, obj->height, obj->rotation
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