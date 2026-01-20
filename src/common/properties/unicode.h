// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_UNICODE_H
#define PROPERTIES_UNICODE_H

#include "../../ztream/header.h"

typedef struct {
    ztream_text_t   content;
    ztream_region_t region;
} property_unicode_t;

extern ztream_property_t property_unicode;

void property_init_unicode();

#endif