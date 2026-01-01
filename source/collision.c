#include "collision.h"
#include "player.h"
#include <stdbool.h>
#include <math.h>
#include <grrlib.h>
#include "math.h"

void get_corners(float cx, float cy, float w, float h, float angle, Vec2D out[4]) {
    float hw = w / 2.0f, hh = h / 2.0f;
    angle = -angle; // Make it clockwise
    float rad = DegToRad(angle);
    float cos_a = cosf(rad), sin_a = sinf(rad);
    

    float local[4][2] = {
        { -hw, -hh },
        {  hw, -hh },
        {  hw,  hh },
        { -hw,  hh }
    };
    for (int i = 0; i < 4; ++i) {
        out[i].x = cx + local[i][0] * cos_a - local[i][1] * sin_a;
        out[i].y = cy + local[i][0] * sin_a + local[i][1] * cos_a;
    }
}

static bool sat_overlap(const Vec2D a[4], const Vec2D b[4]) {
    // Test all axes (normals of edges)
    for (int shape = 0; shape < 2; ++shape) {
        const Vec2D *verts = (shape == 0) ? a : b;
        for (int i = 0; i < 4; ++i) {
            // Edge from verts[i] to verts[(i+1)%4]
            float dx = verts[(i+1)%4].x - verts[i].x;
            float dy = verts[(i+1)%4].y - verts[i].y;
            // Normal axis
            float ax = -dy, ay = dx;

            // Project both shapes onto axis
            float minA = INFINITY, maxA = -INFINITY;
            float minB = INFINITY, maxB = -INFINITY;
            for (int j = 0; j < 4; ++j) {
                float projA = a[j].x * ax + a[j].y * ay;
                float projB = b[j].x * ax + b[j].y * ay;
                if (projA < minA) minA = projA;
                if (projA > maxA) maxA = projA;
                if (projB < minB) minB = projB;
                if (projB > maxB) maxB = projB;
            }
            // If projections do not overlap, there is a separating axis
            if (maxA <= minB || maxB <= minA) return false;
        }
    }
    return true;
}

bool intersect(float x1, float y1, float w1, float h1, float angle1,
               float x2, float y2, float w2, float h2, float angle2) {
    float big = maxf(w1, h1) + maxf(w2, h2);
    if (fabsf(x1 - x2) > big || fabsf(y1 - y2) > big) {
        return false;
    }
    
    Vec2D rect1[4], rect2[4];
    get_corners(x1, y1, w1, h1, angle1, rect1);
    get_corners(x2, y2, w2, h2, angle2, rect2);
    return sat_overlap(rect1, rect2);
}

bool intersect_rect_circle(float rx, float ry, float rw, float rh, float rangle,
                          float cx, float cy, float cradius) {
    // If centers are too far apart, no collision
    float max_dim = fmaxf(rw, rh);
    float max_dist = (max_dim / 2.0f) + cradius;
    if (fabsf(rx - cx) > max_dist || fabsf(ry - cy) > max_dist) {
        return false;
    }

    // Transform circle center into rectangle's local space
    float rad = -DegToRad(rangle); // negative for inverse rotation
    float cos_a = cosf(rad), sin_a = sinf(rad);

    float local_cx = cos_a * (cx - rx) - sin_a * (cy - ry) + rx;
    float local_cy = sin_a * (cx - rx) + cos_a * (cy - ry) + ry;

    // Rectangle bounds
    float left   = rx - rw / 2.0f;
    float right  = rx + rw / 2.0f;
    float top    = ry - rh / 2.0f;
    float bottom = ry + rh / 2.0f;

    // Find closest point on rectangle to circle center
    float closest_x = fmaxf(left, fminf(local_cx, right));
    float closest_y = fmaxf(top,  fminf(local_cy, bottom));

    // Distance from circle center to closest point
    float dx = local_cx - closest_x;
    float dy = local_cy - closest_y;
    float dist_sq = dx * dx + dy * dy;

    return dist_sq <= cradius * cradius;
}
// Dot product helper
float dot(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y1 * y2;
}

bool circle_rect_collision(float cx, float cy, float radius,
                           float x1, float y1, float x2, float y2) {
    // Vector from point 1 to circle center
    float dx = x2 - x1;
    float dy = y2 - y1;
    float fx = cx - x1;
    float fy = cy - y1;

    float len_sq = dx * dx + dy * dy;
    float t = dot(fx, fy, dx, dy) / len_sq;

    // Clamp t to the [0,1] range to stay within the segment
    if (t < 0.0f) t = 0.0f;
    else if (t > 1.0f) t = 1.0f;

    // Closest point on segment
    float closestX = x1 + t * dx;
    float closestY = y1 + t * dy;

    // Distance from circle center to closest point
    float distX = cx - closestX;
    float distY = cy - closestY;
    float distSq = distX * distX + distY * distY;

    return distSq <= radius * radius;
}