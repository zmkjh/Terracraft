// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_FGPAINTER_C
#define SYSTEMS_FGPAINTER_C

#include "fg_painter.h"
#include "../properties/foreground.h"

ztream_system_t system_fg_painter;

static void handler(ztream_data_t data) {
    property_foreground_t* foreground; ZTREAM_DATA_GET(foreground, data);
    ztream_render_color_front(foreground->color, foreground->region);
}

void system_init_fg_painter() {
    system_fg_painter = ztream_property_system(property_foreground, handler);
}

#endif