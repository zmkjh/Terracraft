// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_EXPLODE_SYSTEM_C
#define SYSTEMS_EXPLODE_SYSTEM_C

#include "../../../setting.h"
#include "../../../game/properties/motion.h"
#include "../../../game/properties/timer.h"
#include "../../../game/traits/tnt_block.h"
#include "../../../global/archive.h"
#include "motion_system.h"

#include <time.h>

ztream_system_t system_explode_system;

#define DESTROY_SPACE_NUM 21
static const int destroy_space[DESTROY_SPACE_NUM][2] = {
    {0, 0},
    {0, 1}, {0, -1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
    {-1, 2}, {0, 2}, {1, 2}, {2, -1}, {2, 0}, {2, 1}, {-2, -1}, {-2, 0}, {-2, 1}, {-1, -2}, {0, -2}, {1, -2}
};

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);
    property_timer_t* timer; ZTREAM_DATA_GET(timer, ztream_entity_get(entity, property_timer));
    property_motion_t* motion; ZTREAM_DATA_GET(motion, ztream_entity_get(entity, property_motion));

    time_t cur;
    cur = time(&cur);
    if (timer->end > cur)
        return;

    land_tex_t* tex = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});

    if (!tex)
        return;

    for (int i = 0; i < DESTROY_SPACE_NUM; i++) {
        land_tex_t* space = landscopes_get((ztream_coord_t){motion->displacement.x + destroy_space[i][0], motion->displacement.y + destroy_space[i][1]});
        if (space && *space != ANTI) {
            *space = AIR;
        }
    }
}

void system_init_explode_system() {
    system_explode_system = ztream_trait_system(trait_tnt_block, handler);
}

void system_dependency_explode_system() {
    ztream_system_add_dependency(system_explode_system, system_motion_system);
}

#endif
