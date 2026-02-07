// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_GAME_C
#define SYSTEMS_GAME_C

#include "systems/motion_system.h"
#include "systems/tex_block_system.h"
#include "systems/fluid_system.h"
#include "systems/liquid_system.h"
#include "systems/explode_system.h"

void systems_init_game() {
    system_init_motion_system();
    system_init_tex_block_system();
    system_init_fluid_system();
    system_init_liquid_system();
    system_init_explode_system();

    system_dependency_tex_block_system();
    system_dependency_fluid_system();
    system_dependency_liquid_system();
    system_dependency_motion_system();
    system_dependency_explode_system();
}

#endif
