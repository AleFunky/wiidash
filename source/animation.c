#include <mxml.h>

#include <string.h>
#include <ctype.h>
#include <grrlib.h>
#include "animation.h"
#include "player.h"
#include "main.h"
void extractAnimName(const char* frameName, char* outAnimName) {
    strcpy(outAnimName, frameName);

    // remove extension
    char* dot = strrchr(outAnimName, '.');
    if (dot) *dot = '\0';

    // remove trailing _### if present
    char* underscore = strrchr(outAnimName, '_');
    if (underscore && isdigit(*(unsigned char *)(underscore + 1))) {
        *underscore = '\0';
    }
}

Animation* getOrCreateAnimation(AnimationLibrary* lib, const char* animName) {
    for (int i = 0; i < lib->animCount; i++) {
        if (strcmp(lib->animations[i].name, animName) == 0) {
            return &lib->animations[i];
        }
    }
    Animation* a = &lib->animations[lib->animCount++];
    strncpy(a->name, animName, sizeof(a->name));
    a->frameCount = 0;
    a->fps = 30.0f;
    return a;
}

void parsePlist(const char* filename, AnimationLibrary* lib) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open %s\n", filename);
        return;
    }
    mxml_node_t* tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
    fclose(fp);
    if (!tree) return;

    // Top-level <dict>
    mxml_node_t* rootDict = mxmlFindElement(tree, tree, "dict", NULL, NULL, MXML_DESCEND_FIRST);
    if (!rootDict) {
        printf("No top-level <dict> found\n");
        mxmlDelete(tree);
        return;
    }

    // Find <key>animationContainer</key> inside that dict
    mxml_node_t* animKey = NULL;
    for (mxml_node_t* node = mxmlFindElement(rootDict, rootDict, "key", NULL, NULL, MXML_DESCEND_FIRST);
         node != NULL;
         node = mxmlFindElement(node, rootDict, "key", NULL, NULL, MXML_NO_DESCEND)) {
        
        const char* keyText = mxmlGetOpaque(node);
        if (keyText && strcmp(keyText, "animationContainer") == 0) {
            animKey = node;
            break;
        }
    }

    if (!animKey) {
        printf("No animationContainer key found\n");
        mxmlDelete(tree);
        return;
    }


    // Get the dict that follows the animationContainer key
    mxml_node_t* animDict = mxmlGetNextSibling(animKey);
    while (animDict && mxmlGetType(animDict) != MXML_ELEMENT) {
        animDict = mxmlGetNextSibling(animDict);
    }

    if (!animDict || strcmp(mxmlGetElement(animDict), "dict") != 0) {
        printf("No dict found after animationContainer key\n");
        mxmlDelete(tree);
        return;
    }

    // Loop over all frame <key> elements
    for (mxml_node_t* frameKey = mxmlFindElement(animDict, animDict, "key", NULL, NULL, MXML_DESCEND);
         frameKey;
         frameKey = mxmlFindElement(frameKey, animDict, "key", NULL, NULL, MXML_NO_DESCEND)) {

        const char* frameName = mxmlGetOpaque(frameKey);
        if (!frameName) continue;

        //printf("Processing frame: %s\n", frameName);  // Debug print

        char animName[64];
        extractAnimName(frameName, animName);
        Animation* anim = getOrCreateAnimation(lib, animName);

        AnimationFrame* frame = &anim->frames[anim->frameCount++];
        strncpy(frame->frameName, frameName, sizeof(frame->frameName));
        frame->partCount = 0;

        // Get the dict containing sprite data
        mxml_node_t* frameDict = mxmlGetNextSibling(frameKey);
        while (frameDict && mxmlGetType(frameDict) != MXML_ELEMENT) {
            frameDict = mxmlGetNextSibling(frameDict);
        }
        
        if (!frameDict || strcmp(mxmlGetElement(frameDict), "dict") != 0) {
            printf("No dict found for frame %s\n", frameName);
            continue;
        }

        // Process each sprite
        for (mxml_node_t* spriteKey = mxmlFindElement(frameDict, frameDict, "key", NULL, NULL, MXML_DESCEND_FIRST);
             spriteKey;
             spriteKey = mxmlFindElement(spriteKey, frameDict, "key", NULL, NULL, MXML_NO_DESCEND)) {

            const char* spriteKeyText = mxmlGetOpaque(spriteKey);
            if (!spriteKeyText) continue;

            //printf("  Processing sprite: %s\n", spriteKeyText);  // Debug print

            // Get sprite dict
            mxml_node_t* spriteDict = mxmlGetNextSibling(spriteKey);
            while (spriteDict && mxmlGetType(spriteDict) != MXML_ELEMENT) {
                spriteDict = mxmlGetNextSibling(spriteDict);
            }

            if (!spriteDict || strcmp(mxmlGetElement(spriteDict), "dict") != 0) continue;

            SpritePart* part = &frame->parts[frame->partCount++];
            
            part->x = 0.0f;
            part->y = 0.0f;
            part->sx = 1.0f;
            part->sy = 1.0f;
            part->rotation = 0.0f;
            part->z = 0;
            // Process sprite properties
            for (mxml_node_t* propKey = mxmlFindElement(spriteDict, spriteDict, "key", NULL, NULL, MXML_DESCEND_FIRST);
                 propKey;
                 propKey = mxmlFindElement(propKey, spriteDict, "key", NULL, NULL, MXML_NO_DESCEND)) {

                const char* keyText = mxmlGetOpaque(propKey);
                if (!keyText) continue;

                // Get value node
                mxml_node_t* valNode = mxmlGetNextSibling(propKey);
                while (valNode && mxmlGetType(valNode) != MXML_ELEMENT) {
                    valNode = mxmlGetNextSibling(valNode);
                }
                if (!valNode) continue;

                const char* valText = mxmlGetOpaque(valNode);
                if (!valText) continue;

                //printf("    Property: %s = %s\n", keyText, valText);  // Debug print

                if (strcmp(keyText, "position") == 0) {
                    // Skip leading whitespace
                    while (*valText && isspace(*(unsigned char *) valText)) valText++;
                    if (sscanf(valText, "{%f,%f}", &part->x, &part->y) != 2) {
                        // Try with space after comma
                        if (sscanf(valText, "{%f, %f}", &part->x, &part->y) != 2) {
                            printf("Failed to parse position: %s\n", valText);
                        }
                    }
                }
                else if (strcmp(keyText, "scale") == 0) {
                    // Skip leading whitespace
                    while (*valText && isspace(*(unsigned char *) valText)) valText++;
                    if (sscanf(valText, "{%f,%f}", &part->sx, &part->sy) != 2) {
                        // Try with space after comma
                        if (sscanf(valText, "{%f, %f}", &part->sx, &part->sy) != 2) {
                            printf("Failed to parse scale: %s\n", valText);
                        }
                    }
                }
                else if (strcmp(keyText, "rotation") == 0) {
                    part->rotation = atof(valText);
                }
                else if (strcmp(keyText, "zValue") == 0) {
                    part->z = atoi(valText);
                }
            }

            //printf("  Loaded sprite: pos(%.2f,%.2f) scale(%.2f,%.2f) rot=%.2f z=%d\n",
            //       part->x, part->y, part->sx, part->sy, part->rotation, part->z);
        }
    }

    mxmlDelete(tree);
}



Animation* getAnimation(AnimationLibrary* lib, const char* name) {
    for (int i = 0; i < lib->animCount; i++) {
        if (strcmp(lib->animations[i].name, name) == 0) {
            return &lib->animations[i];
        }
    }
    return NULL;
}

void playAnimation(Animation* anim, float time) {
    int frameIndex = (int)(time * anim->fps) % anim->frameCount;
    AnimationFrame* frame = &anim->frames[frameIndex];

    for (int i = 0; i < frame->partCount; i++) {
        SpritePart* part = &frame->parts[i];
        printf("Draw %d at (%.2f, %.2f) scale(%.2f,%.2f) rot=%.2f z=%d\n",
               i, part->x, part->y,
               part->sx, part->sy,
               part->rotation, part->z);
    }
}

#include "math.h"

void playRobotAnimation(Player *player, Animation* anim, float time) {
    // I should figure a better way to do it
    GRRLIB_texImg *robot_textures[] = {
        robot_3_l2,
        robot_3_l1,

        robot_2_l2,
        robot_2_l1,

        robot_4_l2,
        robot_4_l1,

        robot_1_l2,
        robot_1_l1,

        robot_3_l2,
        robot_3_l1,

        robot_2_l2,
        robot_2_l1,

        robot_4_l2,
        robot_4_l1,
    };

    int frameIndex = (int)(time * anim->fps) % anim->frameCount;
    AnimationFrame* frame = &anim->frames[frameIndex];

    for (int i = 0; i < frame->partCount; i++) {
        SpritePart* part = &frame->parts[i];
        
        float calc_x = ((player->x + part->x - state.camera_x) * SCALE) - widthAdjust;
        float calc_y = screenHeight - ((player->y + part->y - state.camera_y) * SCALE);

        // First part
        GRRLIB_texImg *tex = robot_textures[i * 2];
        set_texture(tex); 
        GRRLIB_SetHandle(tex, tex->w / 2, tex->h / 2);
        custom_drawImg(calc_x - (tex->w * BASE_SCALE) / 2, calc_y - (tex->h * BASE_SCALE) / 2, tex, part->rotation, BASE_SCALE * part->sx, BASE_SCALE * part->sy, RGBA(p2.r, p2.g, p2.b, 255));
        
        // Second
        tex = robot_textures[i * 2 + 1];
        set_texture(tex); 
        GRRLIB_SetHandle(tex, tex->w / 2, tex->h / 2);
        custom_drawImg(calc_x - (tex->w * BASE_SCALE) / 2, calc_y - (tex->h * BASE_SCALE) / 2, tex, part->rotation, BASE_SCALE * part->sx, BASE_SCALE * part->sy, RGBA(p1.r, p1.g, p1.b, 255));
    }
}
