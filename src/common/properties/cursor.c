// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_CURSOR_C
#define PROPERTIES_CURSOR_C

#include "cursor.h"
#include "entry.h"

ztream_property_t property_cursor;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_cursor_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_cursor_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t dst_data) {

}

void property_init_cursor() {
    property_cursor = ztream_property(ZTREAM_TYPE_SINGLE(property_cursor_t), ctor, dtor);
}

#endif