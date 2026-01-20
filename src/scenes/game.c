// copyright. wwd 2510801129 2025/12/28 - --
#ifndef SCENE_LOGIN_C
#define SCENE_LOGIN_C

#include "game.h"
#include "game/entities/game_entities.h"
#include "game/systems/motion_system.h"
#include "game/systems/tex_block_system.h"
#include "game/systems/destroy_block_system.h"
#include "game/systems/fluid_system.h"
#include "game/systems/liquid_system.h"
#include "game/systems/garbage_collector.h"

ztream_scene_t scene_game;

void scene_init_game() {
    scene_game = ztream_scene();
    ztream_scene_relate_entity(&scene_game, &entity_game_background);
    ztream_scene_relate_entity(&scene_game, &entity_game_player);
    ztream_scene_relate_entity(&scene_game, &entity_game_updater);
    ztream_scene_relate_system(&scene_game, &system_motion_system);
    ztream_scene_relate_system(&scene_game, &system_tex_block_system);
    ztream_scene_relate_system(&scene_game, &system_destroy_block_system);
    ztream_scene_relate_system(&scene_game, &system_fluid_system);
    ztream_scene_relate_system(&scene_game, &system_liquid_system);
    ztream_scene_relate_system(&scene_game, &system_garbage_collector);

    ztream_scene_pause(&scene_game);
}

#endif