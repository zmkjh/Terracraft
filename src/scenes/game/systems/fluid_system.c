// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_FLUID_SYSTEM_C
#define SYSTEMS_FLUID_SYSTEM_C

#include "motion_system.h"
#include "../../../setting.h"
#include "../../../game/properties/motion.h"
#include "../../../global/archive.h"
#include "../../../game/traits/fluid.h"
#include "../../../common/systems/listener.h"
#include "tex_block_system.h"

ztream_system_t system_fluid_system;

#define FLUID_SPACE_NUM 3
const int fluid_space[FLUID_SPACE_NUM][2] = {
    {0, -1}, {1, -1}, {-1, -1}
};

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);
    property_motion_t* motion; ZTREAM_DATA_GET(motion, ztream_entity_get(entity, property_motion));

    land_tex_t* tex = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});

    if (!tex) {
        return;
    }

    if (*tex != motion->tex) {
        return;
    }

    for (int i = 0; i < FLUID_SPACE_NUM; i++) {
        land_tex_t* space = landscopes_get((ztream_coord_t){motion->displacement.x + fluid_space[i][0], motion->displacement.y + fluid_space[i][1]});
        if (space && *space == AIR) {
            *space  = *tex;
            *tex    = AIR;

            motion->displacement.x = motion->displacement.x + fluid_space[i][0];
            motion->displacement.y = motion->displacement.y + fluid_space[i][1];
            break;
        }
    }
}

void system_init_fluid_system() {
    system_fluid_system = ztream_trait_system(trait_fluid, handler);
}

void system_dependency_fluid_system() {
    ztream_system_add_dependency(system_fluid_system, system_listener);
    ztream_system_add_dependency(system_tex_block_system, system_fluid_system);
}

#endif
