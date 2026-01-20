// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_ENTRY_CURSOR_PAINTER_C
#define SYSTEMS_ENTRY_CURSOR_PAINTER_C

#include "cursor_painter.h"
#include "../properties/cursor.h"
#include "../properties/entry.h"
#include "../traits/entry_with_cursor.h"
#include "button_listener.h"
#include "entry_listener.h"

ztream_system_t system_cursor_painter;

static void handler(ztream_data_t data) {
    ztream_entity_t*    entity; ZTREAM_DATA_GET(entity, data);
    property_cursor_t*  cursor; ZTREAM_DATA_GET(cursor, ztream_entity_get(entity, property_cursor));
    property_entry_t*   entry;  ZTREAM_DATA_GET(entry, ztream_entity_get(entity, property_entry));

    ztream_coord_t cursor_coord = ztream_entry_cursor_coord(&entry->entry);

    ztream_render_color_back(cursor->bg, (ztream_region_t){
        .x = entry->zone.x + cursor_coord.x,
        .y = entry->zone.y + cursor_coord.y,
        .width = 1, .height = 1
    });
    ztream_render_color_front(cursor->fg, (ztream_region_t){
        .x = entry->zone.x + cursor_coord.x,
        .y = entry->zone.y + cursor_coord.y,
        .width = 1, .height = 1
    });
}

void system_init_cursor_painter() {
    system_cursor_painter = ztream_trait_system(trait_entry_with_cursor, handler);
}

void system_dependency_cursor_painter() {
    ztream_system_add_dependency(system_cursor_painter, system_button_listener);
    ztream_system_add_dependency(system_cursor_painter, system_entry_listener);
}

#endif