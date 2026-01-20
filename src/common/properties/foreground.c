// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_FOREGROUND_C
#define PROPERTIES_FOREGROUND_C

#include "foreground.h"

ztream_property_t property_foreground;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_foreground_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_foreground_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_foreground() {
    property_foreground = ztream_property(ZTREAM_TYPE_SINGLE(property_foreground_t), ctor, dtor);
}

#endif