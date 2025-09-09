#include "objects.h"

// Big file incoming

const ObjectHitbox gamemode_portal_hitbox = {
    .width = 34,
    .height = 86,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox gravity_portal_hitbox = {
    .width = 25,
    .height = 75,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox mirror_portal_hitbox = {
    .width = 44,
    .height = 92,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox size_portal_hitbox = {
    .width = 31,
    .height = 90,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox dual_portal_hitbox = {
    .width = 41,
    .height = 91,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox tp_portal_hitbox = {
    .x_off = 12,
    .width = 25,
    .height = 90,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox no_hitbox = {
    .width = 0,
    .height = 0,
    .type = HITBOX_NONE
};

const ObjectDefinition unknown = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
};

const ObjectDefinition trigger = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
    .is_trigger = TRUE
};


const struct ObjectLayer player_layer = {
    .col_channel = WHITE,
    .zlayer_offset = 0,
    .texture = NULL
};

const ObjectDefinition player_object = {
    .layers = { player_layer },
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = LAYER_T1-1,
    .def_zorder = 9999999,
    .num_layers = 1,  
    .is_trigger = TRUE
};

const struct ObjectLayer secret_coin_layer[] = {
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_01_001.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_01_002.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_01_003.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_01_004.png"
    }
};

const struct ObjectLayer user_coin_layer[] = {
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_2_01_001.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_2_01_002.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_2_01_003.png"
    },
    {
        .x_offset = 0,
        .y_offset = 0,
        .col_channel = WHITE,
        .zlayer_offset = 0,
        .texture = "textures/secretCoin_2_01_004.png"
    }
};

const ObjectDefinition objects[OBJECT_COUNT] = {
    player_object,
    { // Basic block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_07_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/spike_01_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_03_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 10.8,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Blue portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_01_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_01_front_001.png"
            }
        },
        .hitbox = gravity_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Yellow portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_02_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_02_front_001.png"
            }
        },
        .hitbox = gravity_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Cube portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_03_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_03_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Ship portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_04_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_04_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 14
    { // Big rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/rod_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 3,
                .color_type = COLOR_DETAIL,
                .texture = "textures/rod_ball_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 3,
                .color_type = COLOR_DETAIL,
                .texture = "textures/rod_ball_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 3,
                .color_type = COLOR_DETAIL,
                .texture = "textures/rod_ball_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Medium rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/rod_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = -40,
                .col_channel = P1,
                .zlayer_offset = 3,
                .color_type = COLOR_DETAIL,
                .texture = "textures/rod_ball_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Small rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/rod_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = -30,
                .col_channel = P1,
                .zlayer_offset = 3,
                .color_type = COLOR_DETAIL,
                .texture = "textures/rod_ball_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Deco Spikes big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikes_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes medium 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikes_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes small 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikes_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes tiny 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikes_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    trigger, // 22
    trigger, // 23
    trigger, // 24
    trigger, // 25
    trigger, // 26
    trigger, // 27
    trigger, // 28
    trigger, // 29
    trigger, // 30
    unknown, // 31
    trigger, // 32
    trigger, // 33
    unknown, // 34
    { // Yellow pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/bump_01_001.png"
            }
        },
        .hitbox = {
            .width = 25,
            .height = 4,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Yellow orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/ring_01_001.png"
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    unknown, // 37
    unknown, // 38
    { // Half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/spike_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/chain_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 42 REMOVE, ONLY FOR TESTING
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_MAIN,
                .texture = "textures/lightsquare_01_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    unknown, // 43
    unknown, // 44
    { // Orange mirror portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_05_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_05_front_001.png"
            }
        },
        .hitbox = mirror_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Blue mirror portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_06_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_06_front_001.png"
            }
        },
        .hitbox = mirror_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Ball portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_07_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_07_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Deco Cloud big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cloud_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Cloud small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cloud_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing circle
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing circunference
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing heart
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing diamond
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing star
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    trigger, //55
    trigger, //56
    trigger, //57
    trigger, //58
    trigger, //59
    { // Pulsing note
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 7.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Slab 1.3
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Slab 1.3 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab 1.3 inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab 1.3 right edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Slab 1.3 left edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Blue pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/gravbump_01_001.png"
            }
        },
        .hitbox = {
            .width = 25,
            .height = 6,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Slab 1.3 unit
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_b_06_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.3 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_c_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 78
    { // 1.4 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.4 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_d_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Checker full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_08_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Blue orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/gravring_01_001.png"
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Saw deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cogwheel_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Saw deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cogwheel_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Saw deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cogwheel_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/sawblade_01_001.png"
            }
        },
        .hitbox = {
            .radius = 32.3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/sawblade_02_001.png"
            }
        },
        .hitbox = {
            .radius = 21.6,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Black tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Black tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Saw deco tiny
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cogwheel_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/sawblade_03_001.png"
            }
        },
        .hitbox = {
            .radius = 12,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Big portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_08_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_08_front_001.png"
            }
        },
        .hitbox = size_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 100
    { // Mini portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_09_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_09_front_001.png"
            }
        },
        .hitbox = size_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 102
    { // Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/spike_03_001.png"
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    trigger,
    trigger,
    { // 1.5 Big P2 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_02_chain_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.5 Small P2 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_02_chain_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    unknown, // 108
    unknown, // 109
    { // 1.5 Small P1 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_chain_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Ufo portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_10_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_10_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 112
    { // Square Deco Spikes big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_brick_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Square Deco Spikes medium 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_brick_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Square Deco Spikes small 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_brick_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.5 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_f_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_f_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_f_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_f_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.5 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_f_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.5 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_f_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_f_07_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Thorn 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Cloud deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cloud_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Cloud deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cloud_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Cloud deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cloud_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Arrow
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_arrow_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Exclamation mark
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_exmark_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Diamond deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_art_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Bush ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_b_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_b_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_b_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_b_04_001.png"
            }
        },
        .hitbox = {
            .width = 14.1,
            .height = 20,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Question mark
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_qmark_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Wheel deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wheel_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wheel deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wheel_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wheel deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wheel_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Pink pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/bump_03_001.png"
            }
        },
        .hitbox = {
            .width = 25,
            .height = 5,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Pink orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/ring_03_001.png"
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Coin
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/secretCoin_01_001.png"
            }
        },
        .hitbox = {
            .width = 40,
            .height = 40,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Breakable block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/brick_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/brick_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_BREAKABLE_BLOCK
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_01_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_03_001.png"
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_square_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_plank_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_plank_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
   },
   { // Pulsing square
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing triangle
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_08_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing cross
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cross_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Spikeart big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikeart_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikeart medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikeart_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikeart small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikeart_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikewheel big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikewheel_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spikewheel medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikewheel_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spikewheel small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = "textures/d_spikewheel_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wave center
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wave_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wave left
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wave_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wave right
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_wave_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.6 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset edge without line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_06_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_07_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset double inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_08_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_002.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset block alt 1
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_09_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset block alt 2
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_10_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 edge 2
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 corner
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 inside corner
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_05_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_05_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 slab block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 small slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_07_001.png"
            }
        },
        .hitbox = {
            .width = 14,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_01_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Half Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 6.4,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/iceSpike_03_001.png"
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Cartwheel big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cartwheel_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Cartwheel medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cartwheel_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Cartwheel small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_cartwheel_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spike blade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_01_001.png"
            }
        },
        .hitbox = {
            .radius = 15.48,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_02_001.png"
            }
        },
        .hitbox = {
            .radius = 20.4,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_b_03_001.png"
            }
        },
        .hitbox = {
            .radius = 3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_01_001.png"
            }
        },
        .hitbox = {
            .radius = 32.3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_02_001.png"
            }
        },
        .hitbox = {
            .radius = 21.96,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_03_001.png"
            }
        },
        .hitbox = {
            .radius = 12.6,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    unknown, // 189
    { // Diamond deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_art_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Fake spike big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/fakeSpike_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // 1.6 slab single
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_08_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_11_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 slab inside corner small
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_09_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_09_001.png"
            }
        },
        .hitbox = {
            .width = 21,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_01_small_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Mini slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_small_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 slab medium
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_10_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_h_10_001.png"
            }
        },
        .hitbox = {
            .width = 22,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fake half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/fakeSpike_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // Fake medium spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/fakeSpike_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // Slow speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/boost_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/boost_01_001.png"
            },
        },
        .hitbox = {
            .width = 34,
            .height = 44,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_SPEED_PORTALS,
        .def_zlayer = LAYER_T1-1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Normal speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/boost_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/boost_02_001.png"
            },
        },
        .hitbox = {
            .width = 33,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_SPEED_PORTALS,
        .def_zlayer = LAYER_T1-1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Fast speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/boost_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/boost_03_001.png"
            },
        },
        .hitbox = {
            .width = 51,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_SPEED_PORTALS,
        .def_zlayer = LAYER_T1-1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Faster speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/boost_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/boost_04_001.png"
            },
        },
        .hitbox = {
            .width = 65,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_SPEED_PORTALS,
        .def_zlayer = LAYER_T1-1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Fading Mini Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_plank_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_plank_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading half spike
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_square_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_square_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Colored tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 214
    { // Colored slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorPlank_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorSpike_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorSpike_01_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorSpike_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorSpike_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored medium spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorSpike_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorSpike_03_001.png"
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored mini slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorPlank_01_small_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorPlank_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorSquare_01_small_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorSquare_01_small_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    trigger, 
    { // Round cloud big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_roundCloud_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round cloud medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_roundCloud_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round cloud small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_roundCloud_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round swirve line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_swirve_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Round swirve corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_swirve_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_bar_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_bar_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Hexagon line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_bar_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Hexagon corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_bar_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_smallbar_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_smallbar_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG bricks block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_03_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_03_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_03_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Big pulsing circunference
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_circle_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_bar_07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wavy pit right
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 7.2,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Wavy pit left
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_03_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 6.8,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_f_brick01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/square_f_brick02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored checker block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_05_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_06_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_07_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_07_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker double inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_02_08_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_08_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored 1.3 pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_03_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_07_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 162
    { // Colored 1.4 block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored 1.4 pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_04_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05_001_alt.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001_alt.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_05_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored brick pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_06_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_06_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightsquare_05_07_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightsquare_02_07_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 276
    { // Colored brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_03_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_03_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG plain
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG checker
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG 1.4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG 1.3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_square_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_smallbar_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_smallbar_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon single
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_smallbar_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Dual portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_11_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_11_front_001.png"
            }
        },
        .hitbox = dual_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Divorce portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_12_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_12_front_001.png"
            }
        },
        .hitbox = dual_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 288
    { // Checker slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_a_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 290
    { // Checker slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_a_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 292
    unknown, // 293
    { // 1.3 slab slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/triangle_b_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 slab slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/triangle_b_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 slab slope 45 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/triangle_b_square_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.3 slab slope 22/66 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/triangle_b_square_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_08_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    unknown, // 298
    { // 1.3 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_c_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 300
    { // 1.3 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_c_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 302
    unknown, // 303
    unknown, // 304
    { // 1.4 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_16_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_d_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_16_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 306
    { // 1.4 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_17_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_d_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_17_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 308
    { // Black tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 310
    { // Black tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 312
    unknown, // 313
    unknown, // 314
    { // 1.5 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_f_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 316
    { // 1.5 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_f_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 318
    unknown, // 319
    unknown, // 320
    { // 1.6 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 322
    { // 1.6 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset slope 45 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_square_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 tileset slope 22/66 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_square_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 slab slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 slab slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_02_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 slab slope 45 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_square_01_001.png"
            }
        },
        .hitbox = {
            .width = 22,
            .height = 22,
            .type = HITBOX_SOLID,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.6 slab slope 22/66 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_h_square_02_001.png"
            }
        },
        .hitbox = {
            .width = 43,
            .height = 22,
            .type = HITBOX_SOLID,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    unknown, // 330
    { // Colored slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_01_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 332
    { // Colored slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_01_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 334
    unknown, // 335
    unknown, // 336
    { // Colored checker slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_02_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 338
    { // Colored checker slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_02_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 340
    unknown, // 341
    unknown, // 342
    { // Colored 1.3 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_03_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 344
    { // Colored 1.3 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_03_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 346
    unknown, // 347
    unknown, // 348
    { // Colored 1.4 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_16_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_04_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_16_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 350
    { // Colored 1.4 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_17_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_04_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_17_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 352
    { // Colored 1.5 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_05_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 354
    { // Colored 1.5 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lighttriangle_05_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 356
    unknown, // 357
    { // 1.6 tileset slope 22/66 connector 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_square_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    unknown, // 359
    unknown, // 360
    unknown, // 361
    unknown, // 362
    { // Ground spike slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_01_slope_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Ground spike slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_01_slope_02_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Ground spike no gradient
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_01_low_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 6,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Wavy ground spike slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_slope_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Wavy ground spike slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_slope_02_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Wavy ground spike no gradient
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_04_low_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 4,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Continuous slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Continuous slab edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.0 slab slope 45
        .layers = {
             {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.0 slab slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_slope_02_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.0 slab slope 45 connector
        .layers = {
             {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.0 slab slope 22/66 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_square_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Rotating ball big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_rotatingBall_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Rotating ball medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_rotatingBall_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Rotating ball small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_rotatingBall_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Rotating ball tiny
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_rotatingBall_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    unknown, // 379
    unknown, // 380
    unknown, // 381
    unknown, // 382
    unknown, // 383
    unknown, // 384
    unknown, // 385
    unknown, // 386
    unknown, // 387
    unknown, // 388
    unknown, // 389
    unknown, // 390
    unknown, // 391
    { // Mini Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/spike_04_001.png"
            }
        },
        .hitbox = {
            .width = 2.6,
            .height = 4.8,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fake Mini Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/fakeSpike_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // Rotating hexagon big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_geometric_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Rotating hexagon medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_geometric_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Rotating hexagon tiny
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_geometric_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Darkblade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/darkblade_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/darkblade_01_color_001.png"
            }
        },
        .hitbox = {
            .radius = 28.9,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Darkblade medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/darkblade_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/darkblade_02_color_001.png"
            }
        },
        .hitbox = {
            .radius = 17.6,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Darkblade small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/darkblade_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/darkblade_03_color_001.png"
            }
        },
        .hitbox = {
            .radius = 12.9,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    unknown, // 400
    unknown, // 401
    unknown, // 402
    unknown, // 403
    unknown, // 404
    { // Pulsing hexagon
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_ball_09_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Grass 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_grass_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Grass 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_grass_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Grass 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_grass_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Link b line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_b_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link b corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_b_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link b triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_b_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link b full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_b_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link b end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_b_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Grass 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_grass_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    unknown, // 415
    unknown, // 416
    unknown, // 417
    unknown, // 418
    { // Spike wave
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikeWave_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spike wave end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_spikeWave_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spike pit
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_05_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 5.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Spike pit end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_05_02_001.png"
            }
        },
        .hitbox = {
            .width = 6,
            .height = 4.4,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    unknown, // 423
    unknown, // 424
    unknown, // 425
    unknown, // 426
    unknown, // 427
    unknown, // 428
    unknown, // 429
    unknown, // 430
    unknown, // 431
    unknown, // 432
    unknown, // 433
    unknown, // 434
    unknown, // 435
    unknown, // 436
    unknown, // 437
    unknown, // 438
    unknown, // 439
    unknown, // 440
    unknown, // 441
    unknown, // 442
    unknown, // 443
    unknown, // 444
    unknown, // 445
    { // Semicircle pit
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_06_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 7.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Semicircle pit end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_06_2_001.png"
            }
        },
        .hitbox = {
            .width = 5.2,
            .height = 7.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Semicircle wave
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_pit06wave_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Semicircle wave end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_pit06wave_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pillar big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_pillar_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pillar medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_pillar_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pillar small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_pillar_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link c line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_c_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_link_c_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link c corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_c_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_link_c_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link c triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_c_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_link_c_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link c full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_c_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_link_c_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Link c end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_link_c_05_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_link_c_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 2
    },
    { // Colored mini Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/spike_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/colorSpike_04_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/colorSpike_04_001.png"
            }
        },
        .hitbox = {
            .width = 2.6,
            .height = 4.8,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Fading Mini Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_spike_04_001.png"
            }
        },
        .hitbox = {
            .width = 2.6,
            .height = 4.8,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Pulsing arrow 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_arrow_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Colored Thorn 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored Thorn 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored Thorn 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored Thorn 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored Thorn 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored Thorn 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_thorn_06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Layout block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_02_alt_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_02_alt_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 1.5,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_03_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_06_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_04_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_05b_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout slope 45 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_07_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout slope 22 65 connector
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_08_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_08_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Layout dented line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_09_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_09_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 1.5,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // 1.8 tileset 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.8 tileset 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_03_001.png"
            },
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_03_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_05_001.png"
            },
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_05_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_06_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_06_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 7
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_07_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_07_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_slope_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // 1.8 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_slope_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // 1.8 tileset 2 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_01_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_03_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_05_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_06_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_06_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 7
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_07_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_07_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_slope_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // 1.8 tileset 2 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_slope_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // Pulsing arrow 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_arrow_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Pulsing big square
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_largeSquare_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Pulsing big square outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_largeSquare_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Pulsing big circle
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_circle_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Chain
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_03_chain_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Chain holder
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_03_chain_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Swirve line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_swirve_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Swirve corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_swirve_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Checker outside corner no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_09_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Glow
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_gradient_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Glow corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_gradient_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Glow inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/d_gradient_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = 9,
        .num_layers = 1
    },

    { // Persp outline 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 7
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 8
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_08_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp outline 9
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = THREEDL,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/persp_outline_09_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 01 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 01 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_01_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 02 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_02_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 03 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_03_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 04 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_04_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 05 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_05_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 06 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_06_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 07 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_07_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 08 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 08 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_08_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 09 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_09_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 10 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_10_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 11 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_11_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 12 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 3,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/persp_12_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Persp 13 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 13 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_13_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_01.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_02.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_03.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_04.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_05.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_06.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_07.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_08.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Persp 14 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/persp_14_09.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.9 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part03_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_02_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 3
    },
    { // 1.9 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_03_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 3
    },
    { // 1.9 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part06_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_04_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part05_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_05_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part03_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_06_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset corner edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part03_003.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_005.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_02_002.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 4
    },
    { // 1.9 tileset inside full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_004.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_01_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset inside triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_003.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_01_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 3
    },
    { // 1.9 tileset inside double
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part01_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part02_002.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_01_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 3
    },
    { // 1.9 tileset not full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part05_002.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.9 tileset slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block003_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_slope_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // 1.9 tileset slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block003_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_slope_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 4
    },
    { // Block04 piece 01
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 02
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 03
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece03_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 04
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 05
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece05_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 06
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece06_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 07
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece07_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Wave portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_13_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_13_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Outline mini block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_01_small_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_10_001.png"
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Outline slab
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/square_h_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_11_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Outline slab center
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_12_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Outline slab edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/plank_01_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_13_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Outline slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Outline slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 3,
        .num_layers = 2
    },
    { // Square pit
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_07_001.png"
            }
        },
        .hitbox = {
            .width = 9,
            .height = 6,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Pixelart 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_001_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Pixelart 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_002_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Pixelart 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_003_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Pixelart 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_004_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Pixelart 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_005_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Fading slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_triangle_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_triangle_02_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .fades = TRUE,
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/invis_triangle_04_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/invis_triangle_04_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .fades = TRUE,
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Darkcogwheel big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_01_001.png"
            }
        },
        .hitbox = {
            .radius = 32,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Darkcogwheel medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/blackCogwheel_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_02_001.png"
            }
        },
        .hitbox = {
            .radius = 17.68,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Darkcogwheel small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/blackCogwheel_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blackCogwheel_03_001.png"
            }
        },
        .hitbox = {
            .radius = 12.48,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Lightblade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightBlade_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_01_001.png"
            }
        },
        .hitbox = {
            .radius = 30.4,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 0,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Lightblade medium
        .layers = {
                        {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightBlade_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_02_001.png"
            }
        },
        .hitbox = {
            .radius = 18.72,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 0,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Lightblade small
        .layers = {
                        {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/lightBlade_03_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/lightBlade_03_001.png"
            }
        },
        .hitbox = {
            .radius = 10.8,
            .type = HITBOX_SPIKE,
            .is_circular = TRUE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 0,
        .is_saw = TRUE,
        .num_layers = 3
    },
    { // Checker slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_a_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Checker slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_a_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.3 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_c_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.3 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_c_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.4 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_d_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.4 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_d_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Black slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Black slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // 1.5 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_f_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.5 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_f_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/triangle_g_04_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_01_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color checker slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_02_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color checker slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_02_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.3 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_03_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.3 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_03_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.4 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_04_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.4 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_04_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.5 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_05_02_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Color 1.5 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/lighttriangle_05_04_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.8 tileset slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_slope_01_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block001_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block001_slope_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_slope_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.8 tileset 2 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block002_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block002_slope_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block003_slope_01_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_slope_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // 1.9 tileset slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .color_type = COLOR_DETAIL,
                .texture = "textures/block003_slope_02_color_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_slope_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 2
    },
    { // Block04 1 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 1 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 1 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01b_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 1 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02b_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 1 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 1 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 2 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01b_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 2 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02b_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    trigger,
    trigger,
    { // Square pit shine
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/pit_07_shine_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Square pit edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/pit_07_2_001.png"
            }
        },
        .hitbox = {
            .width = 2.4,
            .height = 3.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Square pit edge shine
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/pit_07_2_shine_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Block04 piece 08
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece08_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 09
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece09_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 10
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece10_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Ball
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/d_link_b_01_color_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Block04 3 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01c_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 3 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02c_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 4 slope 45
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01d_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_14_001.png"
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 4 slope 22/66
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02d_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blockOutline_15_001.png"
            }
        },
        .hitbox = {
            .width = 60,
            .height = 30,
            .type = HITBOX_SOLID,
        },
        .is_slope = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Block04 3 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01c_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 3 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02c_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 4 slope 45 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_01d_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 4 slope 22/66 no outline
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block004_slope_02d_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 11
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece11_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 12
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece12_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Block04 piece 13
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/d_block04_piece13_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 tileset edge corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/square_g_12_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Pixelart 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = "textures/d_pixelArt01_006_002.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.9 tileset corner 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part04_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/block003_part01_003.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .color_type = COLOR_DETAIL,
                .zlayer_offset = 0,
                .texture = "textures/block003_color_03_001.png"
            },
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 3
    },
    { // Fading blade alt big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_01_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_01_001.png"
            }
        },
        .hitbox = {
            .radius = 32.3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .fades = TRUE,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Fading blade alt medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_02_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_02_001.png"
            }
        },
        .hitbox = {
            .radius = 21.96,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .fades = TRUE,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Fading blade alt small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = "textures/blade_03_glow_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = "textures/blade_03_001.png"
            }
        },
        .hitbox = {
            .radius = 12.6,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .fades = TRUE,
        .is_saw = TRUE,
        .num_layers = 2
    },
    trigger,
    trigger,

    // 2.0 objects
    
    [BLUE_TP_PORTAL] = { 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_15_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_15_front_001.png"
            }
        },
        .hitbox = tp_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    [ORANGE_TP_PORTAL] = { 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_16_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_16_front_001.png"
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    [ROBOT_PORTAL] = { 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = "textures/portal_14_back_001.png"
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/portal_14_front_001.png"
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    [COL_TRIGGER] = trigger,
    [MOVE_TRIGGER] = trigger,
    [V2_0_LINE_TRIGGER] = trigger,
    [PULSE_TRIGGER] = trigger,
    [ALPHA_TRIGGER] = trigger,
    [GREEN_ORB] = {
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = "textures/gravJumpRing_01_001.png"
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    [TOGGLE_TRIGGER] = trigger,
    [SPAWN_TRIGGER] = trigger,
};