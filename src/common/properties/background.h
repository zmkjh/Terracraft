// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_BACKGROUND_H
#define PROPERTIES_BACKGROUND_H

#include "../../ztream/header.h"

typedef struct {
    ztream_color_t  color;
    ztream_region_t region;
} property_background_t;

extern ztream_property_t property_background;

void property_init_background();

#endif