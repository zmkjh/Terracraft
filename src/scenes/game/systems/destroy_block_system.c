// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_DESTROY_BLOCK_SYSTEM_C
#define SYSTEMS_DESTROY_BLOCK_SYSTEM_C

#include "motion_system.h"
#include "../../../setting.h"
#include "../../../game/properties/motion.h"
#include "../../../game/traits/destroy_block.h"
#include "../../../global/archive.h"

ztream_system_t system_destroy_block_system;

#define DESTROY_SPACE_NUM 4
const int destroy_space[DESTROY_SPACE_NUM][2] = {
    {0, 1}, {0, -1}, {-1, 0}, {1, 0}
};

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);
    property_motion_t* motion; ZTREAM_DATA_GET(motion, ztream_entity_get(entity, property_motion));

    land_tex_t* tex = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});

    if (!tex)
        return;

    for (int i = 0; i < DESTROY_SPACE_NUM; i++) {
        land_tex_t* space = landscopes_get((ztream_coord_t){motion->displacement.x + destroy_space[i][0], motion->displacement.y + destroy_space[i][1]});
        if (space && *space != *tex && *space != ANTI) {
            *space = AIR;
        }
    }
}

void system_init_destroy_block_system() {
    system_destroy_block_system = ztream_trait_system(trait_destroy_block, handler);
}

#endif