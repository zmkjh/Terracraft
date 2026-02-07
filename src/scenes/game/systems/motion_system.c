// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_MOTION_SYSTEM_C
#define SYSTEMS_MOTION_SYSTEM_C

#include "motion_system.h"
#include "../../../setting.h"
#include "../../../game/properties/motion.h"
#include "../../../global/archive.h"
#include "../../../common/systems/listener.h"

ztream_system_t system_motion_system;

#define ABS(x) ((x) < 0 ? (-x) : (x))
#define BLOCK_MU 0.8
#define AIR_MU   0.3

const float t = 1;

static inline float xt(float x, float v0, float a) {
    return x + v0*t + 0.5f * a * t*t;
}

static inline float vt(float v0, float a) {
    return v0 + a*t;
}

static void handler(ztream_data_t data) {
    property_motion_t* motion; ZTREAM_DATA_GET(motion, data);

    if (!landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y}))
        return;

    if (*landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y}) != motion->tex) {
        if (motion->tex != ANIMAL)
            return;
    }

    float a_x = motion->acceleration.x;
    float a_y = motion->acceleration.y;
    if (motion->acceleration.x > 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y}) || *landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y}) != AIR)) {
        a_x = 0;
    } else if (motion->acceleration.x < 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y}) || *landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y}) != AIR)) {
        a_x = 0;
    }
    if (motion->acceleration.y > 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1}) || *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1}) != AIR)) {
        a_y = 0;
    } else if (motion->acceleration.y < 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1}) || *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1}) != AIR)) {
        a_y = 0;
    }

    if (motion->velocity.x > 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y}) || *landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y}) != AIR)) {
        motion->velocity.x = 0;
    } else if (motion->velocity.x < 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y}) || *landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y}) != AIR)) {
        motion->velocity.x = 0;
    }
    if (motion->velocity.y > 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1}) || *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1}) != AIR)) {
        motion->velocity.y = 0;
    } else if (motion->velocity.y < 0 && (!landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1}) || *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1}) != AIR)) {
        motion->velocity.y = 0;
    }

    float v_x = motion->velocity.x;
    float v_y = motion->velocity.y;

    int s_x = xt(motion->displacement.x, v_x, a_x);
    int s_y = xt(motion->displacement.y, v_y, a_y);
    v_x = vt(motion->velocity.x, a_x);
    v_y = vt(motion->velocity.y, a_y);

    if (s_x - motion->displacement.x != 0) {
        float k     = (s_y - motion->displacement.y)/(s_x - motion->displacement.x);
        float b     = s_y - k*s_x;
        int   step  = s_x - motion->displacement.x > 0 ? 1 : -1;

        for (int x = motion->displacement.x + step; x != (int)s_x + step; x += step) {
            int y = k*x + b;

            if (!landscopes_get((ztream_coord_t){x, y}) || *landscopes_get((ztream_coord_t){x, y}) != AIR) {
                s_x = x-step;
                s_y = k*(x - step) + b;
                v_x = 0;
                v_y = 0;
                break;
            }
        }
    } else if (s_y - motion->displacement.y != 0) {
        int step  = s_y - motion->displacement.y > 0 ? 1 : -1;

        for (int y = motion->displacement.y + step; y != (int)s_y + step; y += step) {
            int x = s_x;

            if (!landscopes_get((ztream_coord_t){x, y}) || *landscopes_get((ztream_coord_t){x, y}) > 0) {
                s_x = x;
                s_y = y-step;
                v_x = 0;
                v_y = 0;
                break;
            }
        }
    }

    land_tex_t tex = *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});
    *landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y}) = AIR;
    *landscopes_get((ztream_coord_t){s_x, s_y}) = tex;

    motion->displacement.x = (int64_t)s_x;
    motion->velocity.x     = v_x;
    motion->displacement.y = (int64_t)s_y;
    motion->velocity.y     = v_y;

    land_tex_t* tex_down  = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1});
    land_tex_t* tex_up    = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1});

    if (tex_down && *tex_down != AIR && *tex_down != ANTI || tex_up && *tex_up != AIR && *tex_up != ANTI) {
        motion->velocity.x *= 1-BLOCK_MU;
    } else {
        motion->velocity.x *= 1-AIR_MU;
    }

    if (motion->velocity.y < 0) {
        motion->velocity.y *= 1-AIR_MU;
    }

    if (ABS(motion->velocity.x) <= 0.3)
        motion->velocity.x = 0;
    if (ABS(motion->velocity.y) <= 0.3)
        motion->velocity.y = 0;
}

void system_init_motion_system() {
    system_motion_system = ztream_property_system(property_motion, handler);
}

void system_dependency_motion_system() {
    ztream_system_add_dependency(system_motion_system, system_listener);
}

#endif
