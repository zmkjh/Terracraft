// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_FOREGROUND_H
#define PROPERTIES_FOREGROUND_H

#include "../../ztream/header.h"

typedef struct {
    ztream_color_t  color;
    ztream_region_t region;
} property_foreground_t;

extern ztream_property_t property_foreground;

void property_init_foreground();

#endif