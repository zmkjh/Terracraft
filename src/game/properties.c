// copyright. wwd 2510801129 2025/12/28 - --
#ifndef GAME_PROPERTIES_C
#define GAME_PROPERTIES_C

#include "properties.h"
#include "properties/motion.h"
#include "properties/timer.h"

void properties_init_game() {
    property_init_motion();
    property_init_timer();
}

#endif
