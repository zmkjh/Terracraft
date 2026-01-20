// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_ENTRY_H
#define PROPERTIES_ENTRY_H

#include "../../ztream/header.h"

extern ztream_property_t property_entry;

typedef struct {
    ztream_size_t   size;
    ztream_region_t zone;
} property_entry_info_t;

typedef struct {
    char*           buffer;
    ztream_entry_t  entry;
    ztream_region_t zone;
} property_entry_t;

void property_init_entry();

#endif