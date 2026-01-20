// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_BGPAINTER_C
#define SYSTEMS_BGPAINTER_C

#include "bg_painter.h"
#include "../properties/background.h"

ztream_system_t system_bg_painter;

static void handler(ztream_data_t data) {
    property_background_t* background; ZTREAM_DATA_GET(background, data);
    ztream_render_color_back(background->color, background->region);
}

void system_init_bg_painter() {
    system_bg_painter = ztream_property_system(property_background, handler);
}

#endif