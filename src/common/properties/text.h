// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_TEXT_H
#define PROPERTIES_TEXT_H

#include "../../ztream/header.h"

typedef struct {
    char*           content;
    ztream_region_t region;
} property_text_t;

extern ztream_property_t property_text;

void property_init_text();

#endif