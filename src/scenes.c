// copyright. wwd 2510801129 2025/12/26 - --
#ifndef SCENES_C
#define SCENES_C

#include "scenes.h"
#include "scenes/login.h"
#include "scenes/game.h"

void scenes_init() {
    scene_init_login();
    scene_init_game();
}

#endif
