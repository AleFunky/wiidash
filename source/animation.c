#include <mxml.h>

#include <string.h>
#include <ctype.h>
#include <grrlib.h>
#include "animation.h"
#include "player.h"
#include "main.h"
#include <math.h>
#include "game.h"
#include "object_includes.h"

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

void playObjAnimation(GameObject *obj, AnimationDefinition definition, float time) 
{
    Animation *anim = definition.anim;

    if (!anim) {
        printf("Animation is null\n");
        return;
    }

    float frameTime = time * definition.fps;
    int currentFrame = (int)frameTime % anim->frameCount;
    int nextFrame = (currentFrame + 1) % anim->frameCount;
    
    // Get fractional part for interpolation
    float frameLerp = frameTime - (int)frameTime; 
    
    AnimationFrame* frame = &anim->frames[currentFrame];
    AnimationFrame* nextFrameData = &anim->frames[nextFrame];

    float rotationRad = DegToRad(-obj->rotation);
    float cosRot = cosf(rotationRad);
    float sinRot = sinf(rotationRad);

    int x_flip_mult = (obj->flippedH ? -1 : 1);
    int y_flip_mult = (obj->flippedV ? -1 : 1);

    SpritePart interpolatedPart;

    for (int i = 0; i < definition.part_count; i++) {
        AnimationPart part = definition.parts[i];
        SpritePart* currentPart = &frame->parts[part.part_id];
        SpritePart* nextPart = &nextFrameData->parts[part.part_id];
        
        // Interpolate between current and next frame
        lerpSpritePart(&interpolatedPart, currentPart, nextPart, frameLerp);
        
        float part_x = interpolatedPart.x * x_flip_mult;
        float part_y = interpolatedPart.y * y_flip_mult;

        float rotated_x = (part_x * cosRot - part_y * sinRot) * obj->object.scale_x;
        float rotated_y = (part_x * sinRot + part_y * cosRot) * obj->object.scale_y;

        float calc_x = ((*soa_x(obj) + rotated_x - state.camera_x) * SCALE) - widthAdjust;
        float calc_y = screenHeight - ((*soa_y(obj) + rotated_y - state.camera_y) * SCALE);

        float rotation = interpolatedPart.rotation;
        if (obj->flippedH) rotation = -rotation;
        if (obj->flippedV) rotation = -rotation;
        float final_rotation = (rotation + obj->rotation) * state.mirror_mult;
        
        // Put layer
        GRRLIB_texImg *tex = part.texture;
        u8 color_type = part.color_channel_type;
        
        int col_channel = part.default_col_channel;

        // 2.0+ color channels
        if (obj->object.main_col_channel > 0) {
            if (color_type == COLOR_MAIN) {
                col_channel = obj->object.main_col_channel;  
            } else {
                if (!definition.has_main) col_channel = obj->object.main_col_channel; 
            }
        }
        if (obj->object.detail_col_channel > 0) {
            if (color_type == COLOR_DETAIL) {
                if (definition.has_main) col_channel = obj->object.detail_col_channel;  
            }    
        }

        int blending;
        if (channels[col_channel].blending) {
            blending = GRRLIB_BLEND_ADD;
        } else {
            blending = GRRLIB_BLEND_ALPHA;
        }

        int opacity = get_fade_value(calc_x, screenWidth);
        int unmodified_opacity = opacity;

        u32 color = get_layer_color(obj, color_type, col_channel, opacity);

        // If it is invisible because of blending, skip
        if ((blending == GRRLIB_BLEND_ADD && !(color & ~0xff)) || opacity == 0) continue;

        int fade_x = 0;
        int fade_y = 0;

        float fade_scale = 1.f;

        get_fade_vars(obj, calc_x, &fade_x, &fade_y, &fade_scale);

        // Handle special fade types
        if (obj->transition_applied == FADE_DOWN_STATIONARY || obj->transition_applied == FADE_UP_STATIONARY) {
            if (unmodified_opacity < 255) {
                if (calc_x > screenWidth / 2) {
                    calc_x = screenWidth - FADE_WIDTH;
                } else {
                    calc_x = FADE_WIDTH;
                }
            }
        }
        
        if (tex) {
            set_texture(tex); 
            GRRLIB_SetBlend(blending);
            GRRLIB_SetHandle(tex, tex->w / 2, tex->h / 2);
            custom_drawImg(
                /* X        */ get_mirror_x(calc_x, state.mirror_factor) + 6 - (tex->w) / 2 + fade_x,
                /* Y        */ calc_y + 6 - (tex->h) / 2 + fade_y,
                /* Texture  */ tex, 
                /* Rotation */ final_rotation, 
                /* Scale X  */ BASE_SCALE * x_flip_mult * interpolatedPart.sx * fade_scale * state.mirror_mult * obj->object.scale_x, 
                /* Scale Y  */ BASE_SCALE * y_flip_mult * interpolatedPart.sy * fade_scale * obj->object.scale_y, 
                /* Color    */ color
            );
        }
    }
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
    float frameTimeFrom = time * 30;
    int curFrameFrom = (int)frameTimeFrom % fromAnim->frameCount;
    int nextFrameFrom = (curFrameFrom + 1) % fromAnim->frameCount;
    float frameLerpFrom = frameTimeFrom - (int)frameTimeFrom;

    AnimationFrame* frameFrom = &fromAnim->frames[curFrameFrom];
    AnimationFrame* nextFrameFromData = &fromAnim->frames[nextFrameFrom];

    // This anim
    float frameTimeTo = time * 30;
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

AnimationLibrary monster_1_library;
AnimationLibrary black_sludge_library;
AnimationDefinition prepare_monster_1_animation() {
    char monster_plist_path[282];
    snprintf(monster_plist_path, sizeof(monster_plist_path), "%s/%s/%s", launch_dir, RESOURCES_FOLDER, "monster1.plist");
    parsePlist(monster_plist_path, &monster_1_library);
    
    int part_index = 0;
    
    AnimationDefinition animation = { 0 };
    animation.anim = getAnimation(&monster_1_library, "GJBeast01_bite");

    AnimationPart part1;
    part1.texture = GRRLIB_LoadTexture(GJBeast01_01_glow_001_png);
    part1.color_channel_type = COLOR_GLOW;
    part1.default_col_channel = LBG_NO_LERP;
    part1.part_id = 1;
    animation.parts[part_index++] = part1;
    
    AnimationPart part2;
    part2.texture = GRRLIB_LoadTexture(GJBeast01_02_glow_001_png);
    part2.color_channel_type = COLOR_GLOW;
    part2.default_col_channel = LBG_NO_LERP;
    part2.part_id = 0;
    animation.parts[part_index++] = part2;

    AnimationPart part3;
    part3.texture = GRRLIB_LoadTexture(GJBeast01_01_001_png);
    part3.color_channel_type = COLOR_MAIN;
    part3.default_col_channel = BLACK;
    part3.part_id = 1;
    animation.parts[part_index++] = part3;

    AnimationPart part4;
    part4.texture = GRRLIB_LoadTexture(GJBeast01_03_001_png);
    part4.color_channel_type = COLOR_DETAIL;
    part4.default_col_channel = WHITE;
    part4.part_id = 1;
    animation.parts[part_index++] = part4;

    AnimationPart part5;
    part5.texture = GRRLIB_LoadTexture(GJBeast01_02_001_png);
    part5.color_channel_type = COLOR_MAIN;
    part5.default_col_channel = BLACK;
    part5.part_id = 0;
    animation.parts[part_index++] = part5;
    
    animation.part_count = part_index;
    animation.has_main = TRUE;
    animation.has_detail = TRUE;
    animation.fps = 38;

    return animation;
};

AnimationDefinition prepare_black_sludge_animation() {
    char black_sludge_plist_path[285];
    snprintf(black_sludge_plist_path, sizeof(black_sludge_plist_path), "%s/%s/%s", launch_dir, RESOURCES_FOLDER, "black_sludge.plist");
    parsePlist(black_sludge_plist_path, &black_sludge_library);
    
    int part_index = 0;
    
    AnimationDefinition animation = { 0 };
    animation.anim = getAnimation(&black_sludge_library, "BlackSludge_loop");

    AnimationPart part1;
    part1.texture = GRRLIB_LoadTexture(dA_blackSludge_01_001_png);
    part1.color_channel_type = COLOR_DETAIL;
    part1.default_col_channel = BLACK;
    part1.part_id = 0;
    animation.parts[part_index++] = part1;

    GRRLIB_texImg *triangle_tex = GRRLIB_LoadTexture(dA_blackSludge_02_001_png);

    AnimationPart part2;
    part2.texture = triangle_tex;
    part2.color_channel_type = COLOR_DETAIL;
    part2.default_col_channel = BLACK;
    part2.part_id = 1;
    animation.parts[part_index++] = part2;

    AnimationPart part3;
    part3.texture = triangle_tex;
    part3.color_channel_type = COLOR_DETAIL;
    part3.default_col_channel = BLACK;
    part3.part_id = 2;
    animation.parts[part_index++] = part3;

    animation.part_count = part_index;
    animation.has_detail = TRUE;
    animation.fps = 20;

    return animation;
}
