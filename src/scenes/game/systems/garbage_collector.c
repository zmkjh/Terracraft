// copyright. wwd 2510801129 2026/1/11 - --
#ifndef SYSTEMS_GARBAGE_COLLECTOR_C
#define SYSTEMS_GARBAGE_COLLECTOR_C

#include "garbage_collector.h"
#include "../../../game/traits/garbage_collective.h"
#include "tex_block_system.h"
#include "fluid_system.h"
#include "liquid_system.h"
#include "destroy_block_system.h"

ztream_system_t system_garbage_collector;

// not available now :(

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);
    //ztream_entity_erase(entity);
}

void system_init_garbage_collector() {
    system_garbage_collector = ztream_trait_system(trait_garbage_collective, handler);
}

void system_dependency_garbage_collector() {
    ztream_system_add_dependency(system_garbage_collector, system_tex_block_system);
    ztream_system_add_dependency(system_garbage_collector, system_fluid_system);
    ztream_system_add_dependency(system_garbage_collector, system_liquid_system);   
    ztream_system_add_dependency(system_garbage_collector, system_destroy_block_system);
}

#endif