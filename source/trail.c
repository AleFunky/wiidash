// Adapted from OpenGD

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "math.h"
#include "trail.h"

#include "main.h"
#include "game.h"

#include "custom_mp3player.h"

// Adds "thickness" to a line strip by generating a triangle strip
void ccVertexLineToPolygon(const Vec2* points, float stroke, Vec2* outVerts, int offset, int count) {
    if (count <= 0) return;

    float halfStroke = stroke / 2.0f;

    for (int i = offset; i < count; ++i) {
        Vec2 p = points[i];
        Vec2 dir;

        if (i == 0) {
            dir.x = points[i + 1].x - p.x;
            dir.y = points[i + 1].y - p.y;
        } else if (i == count - 1) {
            dir.x = p.x - points[i - 1].x;
            dir.y = p.y - points[i - 1].y;
        } else {
            dir.x = points[i + 1].x - points[i - 1].x;
            dir.y = points[i + 1].y - points[i - 1].y;
        }

        // Normalize direction
        float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
        if (len == 0) len = 1.0f;
        dir.x /= len;
        dir.y /= len;

        // Perpendicular vector
        Vec2 perp;
        perp.x = -dir.y;
        perp.y = dir.x;

        // Offset left and right
        outVerts[i * 2].x     = p.x + perp.x * halfStroke;
        outVerts[i * 2].y     = p.y + perp.y * halfStroke;

        outVerts[i * 2 + 1].x = p.x - perp.x * halfStroke;
        outVerts[i * 2 + 1].y = p.y - perp.y * halfStroke;
    }
}
// Adds "vertical thickness" to a line strip by generating a triangle strip
void ccVertexLineToPolygonWave(const Vec2* points, float stroke, Vec2* outVerts, int offset, int count) {
    if (count <= 0) return;

    float halfStroke = stroke / 2.0f;

    for (int i = offset; i < count; ++i) {
        Vec2 p = points[i];

        // Offset vertically only (same x for both vertices)
        outVerts[i * 2].x     = p.x;
        outVerts[i * 2].y     = p.y + halfStroke;

        outVerts[i * 2 + 1].x = p.x;
        outVerts[i * 2 + 1].y = p.y - halfStroke;
    }
}

static float getDistanceSq(const Vec2* a, const Vec2* b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return dx*dx + dy*dy;
}

void MotionTrail_Clear(MotionTrail *trail) {
    trail->nuPoints = 0;
    trail->previousNuPoints = 0;
}

void MotionTrail_Init(MotionTrail* trail, float fade, float minSeg, float stroke, bool waveTrail, Color color, GRRLIB_texImg *tex) {
    memset(trail, 0, sizeof(MotionTrail));
    trail->texture = tex;  
    trail->maxPoints = MAX_TRAIL_POINTS;
    trail->fadeDelta = 1.0f / fade;
    trail->minSeg = minSeg * minSeg;  // Compare squared distance
    trail->stroke = stroke;
    trail->displayedColor = color;
    trail->waveTrail = waveTrail;
    if (!waveTrail) trail->appendNewPoints = true;
}

void MotionTrail_ResumeStroke(MotionTrail* trail) {
    if (!trail->appendNewPoints && trail->wasStopped) {
        float dx = trail->positionR.x - trail->lastStopPosition.x;
        float dy = trail->positionR.y - trail->lastStopPosition.y;

        if (square_distance(0, 0, dx, dy) > (TRAIL_CLEAR_DISTANCE * TRAIL_CLEAR_DISTANCE)) {
            trail->nuPoints = 0;
            trail->previousNuPoints = 0;
        }
        trail->wasStopped = false;
    }
    trail->appendNewPoints = true;
}

void MotionTrail_StopStroke(MotionTrail* trail) {
    if (trail->appendNewPoints) {
        trail->lastStopPosition = trail->positionR;
        trail->wasStopped = true;
        trail->appendNewPoints = false;
    }
}

void MotionTrail_Update(MotionTrail* trail, float delta) {
    if (trail->waveTrail) return;
    if (!trail->startingPositionInitialized) return;

    delta *= trail->fadeDelta;

    unsigned int newIdx, newIdx2, i, i2;
    unsigned int mov = 0;

    // Fade old points
    for (i = 0; i < trail->nuPoints; i++) {
        trail->pointState[i] -= delta;
        if (trail->pointState[i] <= 0) {
            mov++;
        } else {
            newIdx = i - mov;
            if (mov > 0) {
                trail->pointState[newIdx] = trail->pointState[i];
                trail->pointVertexes[newIdx] = trail->pointVertexes[i];

                i2 = i * 2;
                newIdx2 = newIdx * 2;
                trail->vertices[newIdx2] = trail->vertices[i2];
                trail->vertices[newIdx2 + 1] = trail->vertices[i2 + 1];

                i2 *= 4;
                newIdx2 *= 4;
                memcpy(&trail->colorPointer[newIdx2], &trail->colorPointer[i2], 8);
            }

            newIdx2 = newIdx * 8;
            u8 op = (u8)(trail->pointState[newIdx] * 255.0f);
            trail->colorPointer[newIdx2 + 3] = op;
            trail->colorPointer[newIdx2 + 7] = op;
        }
    }

    trail->nuPoints -= mov;

    // Append new point
    bool append = true;
    if (trail->nuPoints >= trail->maxPoints) {
        append = false;
    } else if (trail->nuPoints > 0) {
        bool a1 = getDistanceSq(&trail->pointVertexes[trail->nuPoints - 1], &trail->positionR) < trail->minSeg;
        bool a2 = (trail->nuPoints == 1) ? false : getDistanceSq(&trail->pointVertexes[trail->nuPoints - 2], &trail->positionR) < (trail->minSeg * 2.0f);
        if (a1 || a2) append = false;
    }

    if (append && trail->appendNewPoints) {
        unsigned int idx = trail->nuPoints;

        trail->pointVertexes[idx] = trail->positionR;
        trail->pointState[idx] = 1.0f;

        unsigned int offset = idx * 8;
        trail->colorPointer[offset + 0] = trail->displayedColor.r;
        trail->colorPointer[offset + 1] = trail->displayedColor.g;
        trail->colorPointer[offset + 2] = trail->displayedColor.b;
        trail->colorPointer[offset + 3] = 255;
        trail->colorPointer[offset + 4] = trail->displayedColor.r;
        trail->colorPointer[offset + 5] = trail->displayedColor.g;
        trail->colorPointer[offset + 6] = trail->displayedColor.b;
        trail->colorPointer[offset + 7] = 255;

        trail->nuPoints++;
        
        if (trail->nuPoints > 1) {
            ccVertexLineToPolygon(trail->pointVertexes, trail->stroke, trail->vertices, 0, trail->nuPoints);
        }

    }

    if (!append || !trail->appendNewPoints) {
        if (trail->nuPoints > 1) {
            ccVertexLineToPolygon(trail->pointVertexes, trail->stroke, trail->vertices, 0, trail->nuPoints);
        }
    }

    // Update tex coords
    if (trail->nuPoints && trail->previousNuPoints != trail->nuPoints) {
        float texDelta = 1.0f / trail->nuPoints;
        for (i = 0; i < trail->nuPoints; i++) {
            trail->texCoords[i * 2].u = 0;
            trail->texCoords[i * 2].v = texDelta * i;
            trail->texCoords[i * 2 + 1].u = 1;
            trail->texCoords[i * 2 + 1].v = texDelta * i;
        }
        trail->previousNuPoints = trail->nuPoints;
    }
}
void MotionTrail_UpdateWaveTrail(MotionTrail* trail, float delta) {
    if (!trail->waveTrail) return;
    if (!trail->startingPositionInitialized) return;

    unsigned int mov = 0;
    unsigned int startIdx = 0;
    trail->offscreenCount = 0;
    
    // Update stroke width
    float size_value = 15.f * map_range(amplitude, 0.f, 1.f, 0.2f, 1.f);
    if (level_info.custom_song_id <= 0) {
        trail->stroke = ease_out(trail->stroke, size_value, 0.25f);
    } else {
        trail->stroke = size_value;
    }
    
    // Get offscreen points
    for (unsigned int i = 0; i < trail->actualNuPoints; i++) {
        float x = trail->pointVertexes[i].x;
        float calc_x = ((x - state.camera_x) * SCALE) + 6 * state.mirror_mult - widthAdjust;  

        if (calc_x < 0) trail->offscreenCount++;
    }

    // Remove the first point if two or more points are offscreen
    if (trail->offscreenCount >= 2 && trail->nuPoints > 1) {
        startIdx = 1;
        mov = 1;
    }

    for (unsigned int i = startIdx; i < trail->nuPoints; ++i) {
        unsigned int newIdx = i - mov;

        if (mov > 0) {
            trail->pointState[newIdx] = trail->pointState[i];
            trail->pointVertexes[newIdx] = trail->pointVertexes[i];

            unsigned int i2 = i * 2;
            unsigned int newIdx2 = newIdx * 2;
            trail->vertices[newIdx2] = trail->vertices[i2];
            trail->vertices[newIdx2 + 1] = trail->vertices[i2 + 1];

            i2 *= 4;
            newIdx2 *= 4;
            memcpy(&trail->colorPointer[newIdx2], &trail->colorPointer[i2], 8);
        }

        // Set opacity
        unsigned int colorIdx = newIdx * 8;
        trail->colorPointer[colorIdx + 3] = 255 * trail->opacity;
        trail->colorPointer[colorIdx + 7] = 255 * trail->opacity;
    }

    trail->nuPoints -= mov;

    trail->actualNuPoints = trail->nuPoints + 1;

    if (trail->actualNuPoints > 0) {
        trail->pointVertexes[trail->nuPoints] = trail->positionR;
    }

    if (trail->actualNuPoints > 1) {
        ccVertexLineToPolygonWave(trail->pointVertexes, trail->stroke, trail->vertices, 0, trail->actualNuPoints);
        ccVertexLineToPolygonWave(trail->pointVertexes, trail->stroke * 0.4f, trail->centerVertices, 0, trail->actualNuPoints);
    }
}

void MotionTrail_AddWavePoint(MotionTrail* trail) {
    if (!trail->waveTrail) return;
    if (trail->actualNuPoints >= trail->maxPoints) return;

    unsigned int idx = trail->nuPoints;

    trail->pointVertexes[idx] = trail->positionR;
    trail->startingPositionInitialized = TRUE;
    trail->pointState[idx] = 1.0f;

    unsigned int offset = idx * 8;
    trail->colorPointer[offset + 0] = trail->displayedColor.r;
    trail->colorPointer[offset + 1] = trail->displayedColor.g;
    trail->colorPointer[offset + 2] = trail->displayedColor.b;
    trail->colorPointer[offset + 3] = 255;
    trail->colorPointer[offset + 4] = trail->displayedColor.r;
    trail->colorPointer[offset + 5] = trail->displayedColor.g;
    trail->colorPointer[offset + 6] = trail->displayedColor.b;
    trail->colorPointer[offset + 7] = 255;

    trail->nuPoints++;

    //output_log("Added 1 - %d / %d\n", trail->nuPoints, trail->maxPoints);

    if (trail->nuPoints > 1) {
        ccVertexLineToPolygonWave(trail->pointVertexes, trail->stroke, trail->vertices, 0, trail->actualNuPoints);
        ccVertexLineToPolygonWave(trail->pointVertexes, trail->stroke * 0.4f, trail->centerVertices, 0, trail->actualNuPoints);
    }

    trail->previousNuPoints = trail->nuPoints;
}

void MotionTrail_Draw(MotionTrail* trail) {
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    GRRLIB_texImg* tex = trail->texture;

    GXTexObj texObj;
    GX_InitTexObj(&texObj, tex->data, tex->w, tex->h, tex->format,
                    GX_CLAMP, GX_CLAMP, GX_FALSE);
    GX_LoadTexObj(&texObj, GX_TEXMAP0);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    
    GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
    
    GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, trail->nuPoints * 2);
    for (int i = 0; i < trail->nuPoints * 2; i++) {
        
        Vec2 pos = trail->vertices[i];
        
        float calc_x = ((pos.x - state.camera_x) * SCALE) + 6 * state.mirror_mult - widthAdjust;  
        float calc_y = screenHeight - ((pos.y - state.camera_y) * SCALE) + 6;

        Tex2F tex = trail->texCoords[i];
        
        u8* color = &trail->colorPointer[i * 4];
        GX_Position3f32(get_mirror_x(calc_x, state.mirror_factor), calc_y, 0.0f);  // Vertex position (X, Y, Z)
        GX_Color4u8(color[0], color[1], color[2], color[3]); // Vertex color (R,G,B,A)
        GX_TexCoord2f32(tex.u, tex.v); // Texture coordinate (U, V)
    }

    GX_End();

    GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);
    GX_SetVtxDesc(GX_VA_POS,  GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
}

void MotionTrail_DrawWaveTrail(MotionTrail *trail) {
    // Outer wide line
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);  // No texture
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, trail->actualNuPoints * 2);
    for (int i = 0; i < trail->actualNuPoints * 2; i++) {
        Vec2 pos = trail->vertices[i];
        float calc_x = ((pos.x - state.camera_x) * SCALE) + 6 * state.mirror_mult - widthAdjust;  
        float calc_y = screenHeight - ((pos.y - state.camera_y) * SCALE) + 6;
        u8* color = &trail->colorPointer[i * 4];

        GX_Position3f32(get_mirror_x(calc_x, state.mirror_factor), calc_y, 0.0f);
        GX_Color4u8(color[0], color[1], color[2], color[3]);
    }
    GX_End();

    // Center thin line
    GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, trail->actualNuPoints * 2);
    for (int i = 0; i < trail->actualNuPoints * 2; i++) {
        Vec2 pos = trail->centerVertices[i];
        float calc_x = ((pos.x - state.camera_x) * SCALE) + 6 * state.mirror_mult - widthAdjust;  
        float calc_y = screenHeight - ((pos.y - state.camera_y) * SCALE) + 6;

        GX_Position3f32(get_mirror_x(calc_x, state.mirror_factor), calc_y, 0.0f);
        GX_Color4u8(165, 165, 165, 255 * trail->opacity);
    }
    GX_End();
}
