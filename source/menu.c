#include "main.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "level.h"
#include "custom_mp3player.h"
#include "oggplayer.h"
#include "playSound_01_ogg.h"

#include <fat.h>
#include <dirent.h>
#include <sys/types.h>
#include "filesystem.h"
#include "math.h"

#include "menu.h"

#include <stdio.h>

int main_levels();
int sdcard_levels();
void game_folder_not_found();

int level_id = 0;

char sd_level_paths[MAX_SD_LEVELS][MAX_PATH_LEN];
int sd_level_count = 0;

char current_level_name[255];

int level_mode = 0;

size_t outsize;

#define NUM_LVL_COLORS 18
const int default_lvl_colors[NUM_LVL_COLORS] = {
  RGBA(0, 0, 232, 255), // Stereo Madness
  RGBA(227, 0, 229, 255), // Back on Track
  RGBA(233, 0, 115, 255), // Polargeist
  RGBA(233, 0, 0, 255), // Dry Out
  RGBA(231, 112, 0, 255), // Base After Base
  RGBA(233, 232, 0, 255), // Cant Let Go
  RGBA(0, 231, 0, 255), // Jumper
  RGBA(0, 227, 228, 255), // Time Machine
  RGBA(0, 112, 0xE5, 255), // Cycles
  RGBA(0, 0, 0xE9, 255), // XStep
  RGBA(0xE6, 0, 0xE8, 255), // Clutterfunk
  RGBA(231, 0, 115, 255), // ToE
  RGBA(231, 0, 0, 255), // EA
  RGBA(231, 113, 0, 255), // Clubstep
  RGBA(231, 231, 0, 255), // Electrodynamix
  RGBA(0, 231, 0, 255), // HF
  RGBA(0, 228, 228, 255), // BP
  RGBA(0, 112, 231, 255), // ToE2
};

int menu_loop() {
    if (!fatInitDefault()) {
		printf("fatInitDefault failure\n");
	}
    
	struct dirent *pent;
	struct stat statbuf;
    
    DIR *pdir = opendir(launch_dir);

	if (!pdir){
		game_folder_not_found();
        return TRUE;
	}

    char usr_lvl_dir[268];
    snprintf(usr_lvl_dir, sizeof(usr_lvl_dir), "%s/%s", launch_dir, USER_LEVELS_FOLDER);

    DIR *level_dir = opendir(usr_lvl_dir);
    
    sd_level_count = 0;
    if (level_dir) {
        while ((pent=readdir(level_dir))!=NULL) {
            stat(pent->d_name,&statbuf);

            if(strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
                continue;

            const char *ext = strrchr(pent->d_name, '.');
            if (ext && strcmp(ext, ".gmd") == 0) {
                snprintf(sd_level_paths[sd_level_count], MAX_PATH_LEN, "%s/%s", usr_lvl_dir, pent->d_name);
                
                sd_level_count++;
                if (sd_level_count >= MAX_SD_LEVELS) break;

                printf("Found GMD file: %s %llu\n", pent->d_name, pent->d_stat.st_size);
            }
        }
        closedir(level_dir);
    }

	closedir(pdir);
    
    // Read first gmd
    char *level_data = read_file(sd_level_paths[level_id], &outsize);
    if (level_data) {
        snprintf(current_level_name, 255, "%s", get_level_name(level_data));
        free(level_data);
    }

    size_t size;
    char *menuLoop = load_song("menuLoop.mp3", &size);

    while (1) {
        update_input();

        if (!MP3Player_IsPlaying() && menuLoop) {
            MP3Player_PlayBuffer(menuLoop, size, NULL);
        }
                    
        if (state.input.pressed1orX) {
            level_id = 0;
            level_mode ^= 1;

            if (level_mode == 1) {
                // Read first gmd
                char *level_data = read_file(sd_level_paths[level_id], &outsize);
                if (level_data) {
                    snprintf(current_level_name, 255, "%s", get_level_name(level_data));
                    free(level_data);
                }
            }
        }
        
        if (level_mode == 0) {
            if (main_levels()) break;
        } else {
            if (sdcard_levels()) break;
        }

        
        if (state.input.pressedHome) {
            if (menuLoop) free(menuLoop);

            return TRUE;
        }

        GRRLIB_Render();
    }
    
    if (menuLoop) free(menuLoop);

    return FALSE;
}

void game_folder_not_found() {
    char path[256];
    snprintf(path, sizeof(path), "%s", launch_dir);

    while (1) {
        update_input();

        GRRLIB_FillScreen(RGBA(0, 127, 255, 255));

        
        GRRLIB_Printf(0, 20, font, RGBA(255,255,255,255), 0.75, "Couldn't find the game folder.");
        GRRLIB_Printf(0, 45, font, RGBA(255,255,255,255), 0.75, "Make sure the resources folder");
        GRRLIB_Printf(0, 70, font, RGBA(255,255,255,255), 0.75, "and boot.dol is in the following");
        GRRLIB_Printf(0, 95, font, RGBA(255,255,255,255), 0.75, "path:");
        GRRLIB_Printf(0, 120, font, RGBA(255,255,255,255), 0.75, path);
        GRRLIB_Printf(0, 155, font, RGBA(255,255,255,255), 0.75, "Press home to exit.");
                
        if (state.input.pressedHome) {
            break;
        }

        GRRLIB_Render();
    }
}

int sdcard_levels() {
    GRRLIB_FillScreen(RGBA(0, 127, 0, 255));
            
    GRRLIB_Printf(0, 400, font, RGBA(255,255,255,255), 0.75, "Press 1 to switch to main levels.");
    
    if (sd_level_count > 0) {
        char text[269];
        snprintf(text, 269, "%d - %s", level_id + 1, current_level_name);
        GRRLIB_Printf(0, 20, font, RGBA(255,255,255,255), 0.75, text);

        if (state.input.pressedDir & INPUT_LEFT) {
            level_id--;
            if (level_id < 0) level_id = sd_level_count - 1; 
            
            memset(current_level_name, 0, 255);

            char *level_data = read_file(sd_level_paths[level_id], &outsize);
            if (level_data) {
                snprintf(current_level_name, 255, "%s", get_level_name(level_data));
                free(level_data);
            }
        }

        if (state.input.pressedDir & INPUT_RIGHT) {
            level_id++;
            if (level_id >= sd_level_count) level_id = 0;
                
            memset(current_level_name, 0, 255);
            
            char *level_data = read_file(sd_level_paths[level_id], &outsize);
            if (level_data) {
                snprintf(current_level_name, 255, "%s", get_level_name(level_data));
                free(level_data);
            }
        }

        if (state.input.pressedA) {
            // Start level
            gameRoutine = ROUTINE_GAME;
            MP3Player_Stop();
            PlayOgg(playSound_01_ogg, playSound_01_ogg_size, 0, OGG_ONE_TIME);
            for (int i = 0; i < 90; i++) {
                update_input();
                VIDEO_WaitVSync();
            }
            
            char *level = read_file(sd_level_paths[level_id], &outsize);
            load_level(level);
            free(level);
            return 1;
        }
    } else {
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", launch_dir, USER_LEVELS_FOLDER);
        GRRLIB_Printf(0, 20, font, RGBA(255,255,255,255), 0.75, "Put levels in:");
        GRRLIB_Printf(0, 45, font, RGBA(255,255,255,255), 0.75, path);
        GRRLIB_Printf(0, 70, font, RGBA(255,255,255,255), 0.75, "For getting levels, use the mod");
        GRRLIB_Printf(0, 95, font, RGBA(255,255,255,255), 0.75, "\"GDShare\" for exporting.");
    }
    return 0;
}

int main_levels() {
    if (level_id < NUM_LVL_COLORS) {
        GRRLIB_FillScreen(default_lvl_colors[level_id]);
    } else {
        GRRLIB_FillScreen(RGBA(0, 127, 255, 255));
    }
            
    GRRLIB_Printf(0, 400, font, RGBA(255,255,255,255), 0.75, "Press 1 to switch to custom levels.");
    
    custom_rectangle((screenWidth) / 2 - 200, 100, 400, 160, RGBA(0, 0, 0, 127), 1);
    int textOffset = (strlen(levels[level_id].level_name) * 18) / 2;
    GRRLIB_Printf(screenWidth/2 - textOffset, 160, font, RGBA(255,255,255,255), 0.75, levels[level_id].level_name);

    int dotsStartX = (screenWidth / 2) - ((LEVEL_NUM * 16) / 2);
    int selectedColor = RGBA(255, 255, 255, 255);
    int otherColor = RGBA(127, 127, 127, 255);
    for (int i = 0; i < LEVEL_NUM; i++) {
        custom_circle(dotsStartX + i * 16, screenHeight - 32, 4, level_id == i?selectedColor:otherColor, 1);
    }

    if (state.input.pressedDir & INPUT_LEFT) {
        level_id--;
        if (level_id < 0) level_id = LEVEL_NUM - 1; 
    }

    if (state.input.pressedDir & INPUT_RIGHT) {
        level_id++;
        if (level_id >= LEVEL_NUM) level_id = 0;
    }
    
    if (state.input.pressedA) {
        // Start level
        gameRoutine = ROUTINE_GAME;
        MP3Player_Stop();
        PlayOgg(playSound_01_ogg, playSound_01_ogg_size, 0, OGG_ONE_TIME);
        for (int i = 0; i < 90; i++) {
            update_input();
            VIDEO_WaitVSync();
        }
        
        load_level((char *) levels[level_id].data_ptr);
        return 1;
    }
    return 0;
}
