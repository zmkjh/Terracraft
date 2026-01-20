// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_ENTRY_C
#define PROPERTIES_ENTRY_C

#include "entry.h"

ztream_property_t property_entry;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_entry_t*       dst;  ZTREAM_DATA_GET(dst, dst_data);
    property_entry_info_t*  src;  ZTREAM_DATA_GET(src, src_data);

    dst->buffer = (char*)malloc((src->size) * sizeof(char));
    dst->entry  = ztream_entry(dst->buffer, src->size);
    dst->zone   = src->zone;

    ztream_entry_activate(&dst->entry);
}

static void dtor(ztream_data_t data) {
    property_entry_t* entry; ZTREAM_DATA_GET(entry, data);

    free(entry->buffer);
}

void property_init_entry() {
    property_entry = ztream_property(ZTREAM_TYPE_SINGLE(property_entry_t), ctor, dtor);
}

#endif