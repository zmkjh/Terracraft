// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_CURSOR_H
#define PROPERTIES_CURSOR_H

#include "../../ztream/header.h"
#include "entry.h"

extern ztream_property_t property_cursor;

typedef struct {
    ztream_color_t      bg;
    ztream_color_t      fg;
} property_cursor_t;

void property_init_cursor();

#endif