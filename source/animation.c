#include <mxml.h>

#include <string.h>
#include <ctype.h>
#include <grrlib.h>
#include "animation.h"
#include "player.h"
#include "main.h"
#include <math.h>
#include "game.h"

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
        output_log("Failed to open %s\n", filename);
        return;
    }
    mxml_node_t* tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
    fclose(fp);
    if (!tree) return;

    // Top-level <dict>
    mxml_node_t* rootDict = mxmlFindElement(tree, tree, "dict", NULL, NULL, MXML_DESCEND_FIRST);
    if (!rootDict) {
        output_log("No top-level <dict> found\n");
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
        output_log("No animationContainer key found\n");
        mxmlDelete(tree);
        return;
    }


    // Get the dict that follows the animationContainer key
    mxml_node_t* animDict = mxmlGetNextSibling(animKey);
    while (animDict && mxmlGetType(animDict) != MXML_ELEMENT) {
        animDict = mxmlGetNextSibling(animDict);
    }

    if (!animDict || strcmp(mxmlGetElement(animDict), "dict") != 0) {
        output_log("No dict found after animationContainer key\n");
        mxmlDelete(tree);
        return;
    }

    // Loop over all frame <key> elements
    for (mxml_node_t* frameKey = mxmlFindElement(animDict, animDict, "key", NULL, NULL, MXML_DESCEND);
         frameKey;
         frameKey = mxmlFindElement(frameKey, animDict, "key", NULL, NULL, MXML_NO_DESCEND)) {

        const char* frameName = mxmlGetOpaque(frameKey);
        if (!frameName) continue;

        //output_log("Processing frame: %s\n", frameName);  // Debug print

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
            output_log("No dict found for frame %s\n", frameName);
            continue;
        }

        // Process each sprite
        for (mxml_node_t* spriteKey = mxmlFindElement(frameDict, frameDict, "key", NULL, NULL, MXML_DESCEND_FIRST);
             spriteKey;
             spriteKey = mxmlFindElement(spriteKey, frameDict, "key", NULL, NULL, MXML_NO_DESCEND)) {

            const char* spriteKeyText = mxmlGetOpaque(spriteKey);
            if (!spriteKeyText) continue;

            //output_log("  Processing sprite: %s\n", spriteKeyText);  // Debug print

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

                //output_log("    Property: %s = %s\n", keyText, valText);  // Debug print

                if (strcmp(keyText, "position") == 0) {
                    // Skip leading whitespace
                    while (*valText && isspace(*(unsigned char *) valText)) valText++;
                    if (sscanf(valText, "{%f,%f}", &part->x, &part->y) != 2) {
                        // Try with space after comma
                        if (sscanf(valText, "{%f, %f}", &part->x, &part->y) != 2) {
                            output_log("Failed to parse position: %s\n", valText);
                        }
                    }
                }
                else if (strcmp(keyText, "scale") == 0) {
                    // Skip leading whitespace
                    while (*valText && isspace(*(unsigned char *) valText)) valText++;
                    if (sscanf(valText, "{%f,%f}", &part->sx, &part->sy) != 2) {
                        // Try with space after comma
                        if (sscanf(valText, "{%f, %f}", &part->sx, &part->sy) != 2) {
                            output_log("Failed to parse scale: %s\n", valText);
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

            //output_log("  Loaded sprite: pos(%.2f,%.2f) scale(%.2f,%.2f) rot=%.2f z=%d\n",
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

bool robotAnimFinished(Animation *anim, float time) {
    int frameIndex = (int)(time * anim->fps);
    return frameIndex >= anim->frameCount;
}

#include "math.h"

void lerpSpritePart(SpritePart* out, SpritePart* a, SpritePart* b, float t) {
    out->x = a->x + (b->x - a->x) * t;
    out->y = a->y + (b->y - a->y) * t;
    out->sx = a->sx + (b->sx - a->sx) * t;
    out->sy = a->sy + (b->sy - a->sy) * t;
    
    // Handle rotation interpolation to prevent flipping
    float angleDiff = b->rotation - a->rotation;
    if (angleDiff > 180.0f) angleDiff -= 360.0f;
    if (angleDiff < -180.0f) angleDiff += 360.0f;
    out->rotation = a->rotation + angleDiff * t;
    
    out->z = a->z;
}

void playRobotAnimation(Player *player, 
                        Animation* fromAnim, 
                        Animation* toAnim,
                        float time, 
                        float scale, 
                        float rotation,
                        float blendFactor) 
{
    // Animation textures
    GRRLIB_texImg *robot_textures[] = {
        robot_3_l2, robot_3_l1,
        robot_2_l2, robot_2_l1,
        robot_4_l2, robot_4_l1,
        robot_1_l2, robot_1_l1,
        robot_3_l2, robot_3_l1,
        robot_2_l2, robot_2_l1,
        robot_4_l2, robot_4_l1,
    };

    // Prev anim
    float frameTimeFrom = time * fromAnim->fps;
    int curFrameFrom = (int)frameTimeFrom % fromAnim->frameCount;
    int nextFrameFrom = (curFrameFrom + 1) % fromAnim->frameCount;
    float frameLerpFrom = frameTimeFrom - (int)frameTimeFrom;

    AnimationFrame* frameFrom = &fromAnim->frames[curFrameFrom];
    AnimationFrame* nextFrameFromData = &fromAnim->frames[nextFrameFrom];

    // This anim
    float frameTimeTo = time * toAnim->fps;
    int curFrameTo = (int)frameTimeTo % toAnim->frameCount;
    int nextFrameTo = (curFrameTo + 1) % toAnim->frameCount;
    float frameLerpTo = frameTimeTo - (int)frameTimeTo;

    if (curFrameTo == toAnim->frameCount - 2) {
        switch (player->curr_robot_animation_id) {
            case ROBOT_JUMP_START:
                player->curr_robot_animation_id = ROBOT_JUMP;
                nextFrameTo = toAnim->frameCount - 1;
                break;
            case ROBOT_FALL_START:
                player->curr_robot_animation_id = ROBOT_FALL;
                nextFrameTo = toAnim->frameCount - 1;
                break;
        }
    }

    AnimationFrame* frameTo = &toAnim->frames[curFrameTo];
    AnimationFrame* nextFrameToData = &toAnim->frames[nextFrameTo];

    float rotationRad = DegToRad(-rotation);
    float cosRot = cosf(rotationRad);
    float sinRot = sinf(rotationRad);

    int upside_down_mult = (player->upside_down ? -1 : 1);

    for (int i = 0; i < frameFrom->partCount; i++) {
        SpritePart partFromInterp;
        SpritePart partToInterp;
        SpritePart finalPart;

        lerpSpritePart(&partFromInterp, &frameFrom->parts[i], &nextFrameFromData->parts[i], frameLerpFrom);
        lerpSpritePart(&partToInterp, &frameTo->parts[i], &nextFrameToData->parts[i], frameLerpTo);

        finalPart.x        = lerp(partFromInterp.x,        partToInterp.x,        blendFactor);
        finalPart.y        = lerp(partFromInterp.y,        partToInterp.y,        blendFactor);
        finalPart.rotation = lerp(partFromInterp.rotation, partToInterp.rotation, blendFactor);
        finalPart.sx       = lerp(partFromInterp.sx,       partToInterp.sx,       blendFactor);
        finalPart.sy       = lerp(partFromInterp.sy,       partToInterp.sy,       blendFactor);

        float part_y = finalPart.y * upside_down_mult;

        float rotated_x = (finalPart.x * cosRot - part_y * sinRot) * scale;
        float rotated_y = (finalPart.x * sinRot + part_y * cosRot) * scale;

        float calc_x = ((player->x + rotated_x - state.camera_x) * SCALE) - widthAdjust;
        float calc_y = screenHeight - ((player->y + rotated_y - state.camera_y) * SCALE);

        float final_rotation = (finalPart.rotation + rotation) * state.mirror_mult;

        GRRLIB_texImg *tex;

        // First part
        tex = robot_textures[i * 2];
        set_texture(tex); 
        GRRLIB_SetHandle(tex, tex->w / 2, tex->h / 2);
        custom_drawImg(get_mirror_x(calc_x, state.mirror_factor) + 6 - (tex->w) / 2, 
                       calc_y + 6 - (tex->h) / 2, 
                       tex, 
                       final_rotation, 
                       BASE_SCALE * finalPart.sx * scale * state.mirror_mult, 
                       BASE_SCALE * finalPart.sy * scale * upside_down_mult, 
                       RGBA(p2.r, p2.g, p2.b, 255));

        // Second part
        tex = robot_textures[i * 2 + 1];
        set_texture(tex); 
        GRRLIB_SetHandle(tex, tex->w / 2, tex->h / 2);
        custom_drawImg(get_mirror_x(calc_x, state.mirror_factor) + 6 - (tex->w) / 2, 
                       calc_y + 6 - (tex->h) / 2, 
                       tex, 
                       final_rotation, 
                       BASE_SCALE * finalPart.sx * scale * state.mirror_mult, 
                       BASE_SCALE * finalPart.sy * scale * upside_down_mult, 
                       RGBA(p1.r, p1.g, p1.b, 255));
    }
}

