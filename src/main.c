// copyright. wwd 2510801129 2025/11/27 - --

#include "ztream/header.h"
#include <minwindef.h>
ztream_t        ztream;
ztream_ecs_t    ztream_ecs;

#include "setting.h"
#include "global/global.h"
#include "global/archive.h"
#include "scenes/login/entities.h"
#include "scenes/game/entities.h"
#include "common/properties.h"
#include "common/systems.h"
#include "common/traits.h"
#include "game/properties.h"
#include "scenes/game/systems.h"
#include "game/traits.h"
#include "scenes.h"
#include "scenes/login.h"

#include <stdlib.h>
#include <time.h>

void quit() {
    archive_save();
}

int main() {
    ztream_init(TITLE, LOGIN_PAGE_REGION.width, LOGIN_PAGE_REGION.height, quit);
    ztream_set_font(FONT_TYPE, 10, 20, FALSE);

    srand((unsigned)time(NULL));

    archive_load();

    ztream_ecs_init();

    properties_init_common();
    traits_init_common();
    systems_init_common();

    properties_init_game();
    traits_init_game();
    systems_init_game();

    entities_init_login();
    entities_init_game();

    scenes_init();

    while(1) {
        ztream_ecs_run();
        ztream_update();
        ztream_render();
        ztream_clear();
        ztream_fps_hold(FPS);
    }

    return 0;
}
