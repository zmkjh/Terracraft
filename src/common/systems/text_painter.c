// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_TEXT_PAINTER_C
#define SYSTEMS_TEXT_PAINTER_C

#include "text_painter.h"
#include "../properties/text.h"
#include "button_listener.h"
#include "entry_listener.h"

ztream_system_t system_text_painter;

static void handler(ztream_data_t data) {
    property_text_t* text; ZTREAM_DATA_GET(text, data);

    ztream_tex_t buffer[1024];
    ztream_trans_text(text->content, buffer);
    ztream_render_text_axis_x(buffer, text->region, (ztream_coord_t){0, 0}, 1);
}

void system_init_text_painter() {
    system_text_painter = ztream_property_system(property_text, handler);
}

void system_dependency_text_painter() {
    ztream_system_add_dependency(system_text_painter, system_button_listener);
    ztream_system_add_dependency(system_text_painter, system_entry_listener);
}

#endif