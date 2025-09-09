#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <math.h>

#include <asndlib.h>
#include "objects.h"
#include <stdio.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/lwp.h>
#include <ogc/lwp_mutex.h>

#include <unistd.h>

#include "main.h"
#include "game.h"

#include "custom_mp3player.h"
#include "oggplayer.h"

#include "level_loading.h"
#include "objects.h"

#include "font_png.h"
#include "cursor_png.h"

#include "player.h"
#include "math.h"

#include "game.h"
#include "menu.h"

#include "trail.h"
#include "bigFont_png.h"

#include "animation.h"

#include <fat.h>

// Declare Static Functions
static void ExitGame(void);

int screenWidth = 0;
int screenHeight = 0;
float screen_factor_x = 0;
float screen_factor_y = 0;
int widthAdjust = 0;

int gameRoutine = ROUTINE_MENU;

u64 startTime;
int frameCount = 0;
float fps = 0;

GameState state;

GRRLIB_texImg *font = NULL;
GRRLIB_texImg *cursor = NULL;
GRRLIB_texImg *big_font_text = NULL;

int frame_counter = 0;
int old_frame_counter = 0;

// Profiling
float obj_layer_time = 0;
float physics_time = 0;
float collision_time = 0;
float particles_time = 0;
float triggers_time = 0;
float player_time = 0;
float frame_time = 0;

float obj_particles_time = 0;
float draw_time = 0;
float layer_sorting = 0;
float player_draw_time = 0;

int number_of_collisions = 0;
int number_of_collisions_checks = 0;

char launch_dir[256] = SDCARD_FOLDER;
float ir_x;
float ir_y;

AnimationLibrary robot_animations = {0};

void draw_game() {
    draw_background(state.background_x / 8, -(state.camera_y / 8) + 416);

    u64 t0 = gettime();
    draw_all_object_layers();
    u64 t1 = gettime();
    
    obj_layer_time = ticks_to_microsecs(t1 - t0) / 1000.f;

    draw_end_wall();

    draw_ground(0, FALSE);
    
    if (state.ground_y_gfx > 0) {
        if (state.camera_y + state.ground_y_gfx > 0) draw_ground(state.camera_y + state.ground_y_gfx, FALSE);
        draw_ground(state.camera_y + SCREEN_HEIGHT_AREA - state.ground_y_gfx, TRUE);
    }
    
    // FPS logic
    frameCount++;
    u64 currentTime = gettime();
    float elapsed = ticks_to_millisecs(currentTime - startTime) / 1000.0f;

    if (elapsed >= 1.0f) {
        fps = frameCount / elapsed;
        frameCount = 0;
        startTime = currentTime;
    }
    
    
    char percentage[64];
    snprintf(percentage, sizeof(percentage), "%d%%%%", (int) state.level_progress);
    int textOffset = (get_text_length(big_font, 0.5, percentage)) / 2;
    draw_text(big_font, big_font_text, screenWidth/2 - textOffset, 10, 0.5, percentage);
    

    if (state.noclip) {
        draw_text(big_font, big_font_text, screenWidth - 200, 20, 0.25, "Noclip activated");
    }

    if (enable_info) {    
        t0 = gettime();

        // Render FPS
        char fpsText[64];
        snprintf(fpsText, sizeof(fpsText), "FPS: %.2f Steps: %d Objs: %d Layers: %d", fps, frame_counter - old_frame_counter, level_info.object_count, layersArrayList->count);
        draw_text(big_font, big_font_text, 20, 20, 0.25, fpsText);  // White tex
        
        char layerText[64];
        snprintf(layerText, sizeof(layerText), "Drawn layers: %d", layersDrawn);
        draw_text(big_font, big_font_text, 20, 50, 0.25, layerText);
        old_frame_counter = frame_counter;
        
        char player_x[64];
        snprintf(player_x, sizeof(player_x), "X: %.2f VX: %.2f", state.player.x, state.player.vel_x);
        draw_text(big_font, big_font_text, 20, 80, 0.25, player_x);

        char player_y[64];
        snprintf(player_y, sizeof(player_y), "Y: %.2f VY: %.2f", state.player.y, state.player.vel_y);
        draw_text(big_font, big_font_text, 20, 110, 0.25, player_y);
        
        char obj_layer[64];
        snprintf(obj_layer, sizeof(obj_layer), "GFX: %.2f ms (Pl: %.2f Pt: %.2f, St: %.2f, D: %.2f)", obj_layer_time, player_draw_time, obj_particles_time, layer_sorting, draw_time);
        draw_text(big_font, big_font_text, 20, 140, 0.25, obj_layer);
        
        char physics[128];
        snprintf(physics, sizeof(physics), "Physics: %.2f ms (P: %.2f Obj: %.2f E: %.2f)", physics_time, player_time, triggers_time, particles_time);
        draw_text(big_font, big_font_text, 20, 170, 0.25, physics);

        char collision[128];
        snprintf(collision, sizeof(collision), "Collision: %.2f ms (Checks: %d Succeded: %d)", collision_time, number_of_collisions_checks, number_of_collisions);
        draw_text(big_font, big_font_text, 20, 200, 0.25, collision);

        t1 = gettime();
        float text = ticks_to_microsecs(t1 - t0) / 1000.f;
        
        char text_ms[64];
        snprintf(text_ms, sizeof(text_ms), "Text: %.2f ms", text);
        draw_text(big_font, big_font_text, 20, 230, 0.25, text_ms);

        u64 last_frame = gettime();
        float cpu_time = ticks_to_microsecs(last_frame - start_frame) / 1000.f;
        
        char cpu_usage[64];
        snprintf(cpu_usage, sizeof(cpu_usage), "CPU: %.2f%%%%", (cpu_time / 16.666666) * 100);
        draw_text(big_font, big_font_text, 20, 400, 0.25, cpu_usage);
    }
    
    draw_time = 0;
    obj_particles_time = 0;

    if (state.paused) {
        GRRLIB_FillScreen(RGBA(0, 0, 0, 127));
        textOffset = (get_text_length(big_font, 0.5, "PAUSED")) / 2;
        draw_text(big_font, big_font_text, screenWidth / 2 - textOffset, screenHeight / 2 - 15, 0.5, "PAUSED");
    }
    layersDrawn = 0;

    state.timer += dt;
}

#include <mad.h>

void update_input() {
    update_external_input(&state.input);
}

void update_external_input(KeyInput *input) {
    WPAD_ScanPads();
    PAD_ScanPads();

    input->pressedA = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_BUTTON_A)) > 0;
    input->holdA =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_BUTTON_A)) > 0;

    input->pressedB = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_B) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_BUTTON_B)) > 0;
    input->holdB =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_B) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_BUTTON_B)) > 0;

    input->pressedHome = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_BUTTON_MENU)) > 0;
    
    input->pressed1orX = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_1) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_BUTTON_X)) > 0;
    input->hold1orX =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_1) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_BUTTON_X)) > 0;

    input->pressed2orY = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_2) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_BUTTON_Y)) > 0;
    input->hold2orY =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_2) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_BUTTON_Y)) > 0;
    
    input->pressedPlusOrL = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_PLUS) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_TRIGGER_L)) > 0;
    input->holdPlusOrL =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_PLUS) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_TRIGGER_L)) > 0;

    input->pressedMinusOrR = ((WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_MINUS) | (PAD_ButtonsDown(PAD_CHAN0) & PAD_TRIGGER_R)) > 0;
    input->holdMinusOrR =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_MINUS) | (PAD_ButtonsHeld(PAD_CHAN0) & PAD_TRIGGER_R)) > 0;

    unsigned int const wpad_dir_mask = WPAD_BUTTON_UP | WPAD_BUTTON_DOWN | WPAD_BUTTON_RIGHT | WPAD_BUTTON_LEFT; 
    unsigned int const pad_dir_mask =  PAD_BUTTON_UP  | PAD_BUTTON_DOWN  | PAD_BUTTON_RIGHT  | PAD_BUTTON_LEFT; 

    input->pressedDir = ((WPAD_ButtonsDown(WPAD_CHAN_0) & wpad_dir_mask) >> 8) | (PAD_ButtonsDown(PAD_CHAN0) & pad_dir_mask);
    input->holdDir =    ((WPAD_ButtonsHeld(WPAD_CHAN_0) & wpad_dir_mask) >> 8) | (PAD_ButtonsHeld(PAD_CHAN0) & pad_dir_mask);

    input->pressedJump = input->pressedA || input->pressed2orY || input->pressedB;
    input->holdJump = input->holdA || input->hold2orY || input->holdB;

    WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);

    WPADData* data = WPAD_Data(0);
    ir_x = data->ir.x;
    ir_y = data->ir.y;

}

void set_launch_dir(const char* path) {
    if (!path) return;

    const char *last_slash = strrchr(path, '/');
    if (!last_slash) return;

    size_t dir_len = last_slash - path;
    if (dir_len >= 256) dir_len = 255;

    strncpy(launch_dir, path, dir_len);
    launch_dir[dir_len] = '\0';
}

int main(int argc, char **argv) {
    if (argc > 0) {
        set_launch_dir(argv[0]);
    }

    if (!fatInitDefault()) {
		output_log("fatInitDefault failure\n");
	}

    SYS_STDIO_Report(true);
    // Init GRRLIB & WiiUse
    output_log("grrlib status %d\n", GRRLIB_Init());
    
    WPAD_Init();
    PAD_Init();
    WPAD_SetIdleTimeout( 60 * 10 );
    WPAD_SetDataFormat( WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR );

    srand(time(NULL));

    // Initialise the audio subsystem
	ASND_Init();
    MP3Player_Init();
    
    SetVolumeOgg(255);
    load_spritesheet();

    // Set resolution based on mode
    screenWidth  = GRRLIB_Settings.width;   // Framebuffer width (typically 640)
    screenHeight = GRRLIB_Settings.height; // EFB height (usually 480 or 576)

    widthAdjust = (screenWidth - 640) / 2.f;

    screen_factor_x = (float) screenWidth / 640;
    screen_factor_y = (float) screenHeight / 480;

    output_log("xfb[0]=%p xfb[1]=%p\n", xfb[0], xfb[1]);

    output_log("%d, %d mode %d\n", screenWidth, screenHeight, rmode->viTVMode);

    startTime = gettime();    

    font = GRRLIB_LoadTexturePNG(font_png);
    GRRLIB_InitTileSet(font, 24, 36, 32);
    cursor = GRRLIB_LoadTexturePNG(cursor_png);
    big_font_text = GRRLIB_LoadTexturePNG(bigFont_png);

    // hopefully this fixes the ir position
    WPAD_SetVRes(WPAD_CHAN_0,screenWidth,screenHeight);
    
    char robot_plist_path[278];
    
    snprintf(robot_plist_path, sizeof(robot_plist_path), "%s/%s/%s", launch_dir, RESOURCES_FOLDER, "robot.plist");
    parsePlist(robot_plist_path, &robot_animations);

    output_log("Loaded %d animations\n", robot_animations.animCount);
    for (int i = 0; i < robot_animations.animCount; i++) {
        output_log("Animation %s: %d frames\n",
               robot_animations.animations[i].name,
               robot_animations.animations[i].frameCount);
    }

    full_init_variables();
    while(1) {
        switch (gameRoutine) {
            case ROUTINE_MENU:
                if (menu_loop()) goto Exit;
                break;
            case ROUTINE_GAME:
                if(game_loop()) goto Exit;
                break;
        }
    }
Exit:
	MP3Player_Stop();
    ExitGame();
    return 0;
}

static FILE *log_file = NULL;

static void ensure_log_file(void) {
    if (log_file) return;  // already open

    // Initialize SD/USB filesystem
    if (!fatInitDefault()) return;

    char log_filename[278];
    snprintf(log_filename, sizeof(log_filename), "%s/%s", launch_dir, "output.txt");
    
    log_file = fopen(log_filename, "a");
}

static void close_log_file(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

int output_log(const char *fmt, ...) {
    ensure_log_file();

    if (!log_file) return 0; // failed to open log

    va_list args1, args2;
    int ret;

    va_start(args1, fmt);
    va_copy(args2, args1);  // duplicate args for two outputs

    // Output to log file
    ensure_log_file();
    if (log_file) {
        ret = vfprintf(log_file, fmt, args1);
        fflush(log_file);
    }

    // Output to console (stdout)
    ret = vprintf(fmt, args2);
    
    va_end(args2);
    va_end(args1);

    return ret;
}

static void ExitGame(void) {
    unload_spritesheet();

    close_log_file();

    // Deinitialize GRRLIB & Video
    GRRLIB_Exit();

    // Exit application
    exit(0);
}

