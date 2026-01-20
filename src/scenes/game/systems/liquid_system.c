// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_LIQUID_SYSTEM_C
#define SYSTEMS_LIQUID_SYSTEM_C

#include "motion_system.h"
#include "../../../setting.h"
#include "../../../game/properties/motion.h"
#include "../../../global/archive.h"
#include "../../../common/systems/listener.h"
#include "../../../game/traits/liquid.h"
#include "tex_block_system.h"

ztream_system_t system_liquid_system;

#define LIQUID_SPACE_NUM 5
const int liquid_space[LIQUID_SPACE_NUM][2] = {
    {0, -1}, {-1, 0}, {1, 0}, {-1, -1}, {1, -1}
};

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);
    property_motion_t* motion; ZTREAM_DATA_GET(motion, ztream_entity_get(entity, property_motion));

    land_tex_t* tex   = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});
    land_tex_t* up    = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1});
    land_tex_t* down  = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1});
    land_tex_t* left  = landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y});
    land_tex_t* right = landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y});

    if (!tex) {
        return;
    }

    // I don't know why
    if (*tex == AIR)
        return;
    
    if (down && *down == AIR) {
        *down  = *tex;
        *tex   = AIR;

        motion->displacement.y -= 1;
        return;
    }

    int should_float = (up && *up != AIR && *up != ANTI) || (left && land_tex_is_floating(*left) || (right && land_tex_is_floating(*right)));

    if (land_tex_is_floating(*tex)) {
        if (!should_float) {
            *tex = LAND_TEX_TONOT_FLOATING(*tex);
            motion->tex = *tex;
            return;
        }

        for (int i = 0; i < LIQUID_SPACE_NUM; i++) {
            land_tex_t* space = landscopes_get((ztream_coord_t){motion->displacement.x + liquid_space[i][0], motion->displacement.y + liquid_space[i][1]});
            if (space && *space == AIR) {
                *tex = LAND_TEX_TONOT_FLOATING(*tex);
                motion->tex = *tex;

                *space  = *tex;
                *tex    = AIR;

                motion->displacement.x = motion->displacement.x + liquid_space[i][0];
                motion->displacement.y = motion->displacement.y + liquid_space[i][1];

                tex   = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});
                up    = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y + 1});
                down  = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y - 1});
                left  = landscopes_get((ztream_coord_t){motion->displacement.x - 1, motion->displacement.y});
                right = landscopes_get((ztream_coord_t){motion->displacement.x + 1, motion->displacement.y});

                should_float = (up && *up != AIR && *up != ANTI) || (left && land_tex_is_floating(*left) || (right && land_tex_is_floating(*right)));
                if (should_float) {
                    *tex = LAND_TEX_TOBE_FLOATING(*tex);
                    motion->tex = *tex;
                }
                break;
            }
        }
        return;
    }

    if (should_float) {
        *tex = LAND_TEX_TOBE_FLOATING(*tex);
        motion->tex = *tex;
    }
}

void system_init_liquid_system() {
    system_liquid_system = ztream_trait_system(trait_liquid, handler);
}

void system_dependency_liquid_system() {
    ztream_system_add_dependency(system_liquid_system, system_listener);
    ztream_system_add_dependency(system_liquid_system, system_tex_block_system);
}

#endif