// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_UNICODE_PAINTER_C
#define SYSTEMS_UNICODE_PAINTER_C

#include "text_painter.h"
#include "../properties/unicode.h"

ztream_system_t system_unicode_painter;

static void handler(ztream_data_t data) {
    property_unicode_t* text; ZTREAM_DATA_GET(text, data);

    ztream_render_text_axis_x(text->content, text->region, (ztream_coord_t){0, 0}, 1);
}

void system_init_unicode_painter() {
    system_unicode_painter = ztream_property_system(property_unicode, handler);
}

#endif