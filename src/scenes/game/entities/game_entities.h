// copyright. wwd 2510801129 2025/12/28 - --
#ifndef ENTITIES_GAME_ENTITIES_H
#define ENTITIES_GAME_ENTITIES_H

#include "../../../ztream/header.h"
#include "../../../common/properties/foreground.h"

extern ztream_entity_t      entity_game_background;
extern ztream_entity_t      entity_game_player;
extern ztream_entity_t      entity_game_player_entity;
extern ztream_entity_t      entity_game_updater;

void entity_init_game();
void entity_init_player();
void entity_reload_game();

#endif