// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_BACKGROUND_C
#define PROPERTIES_BACKGROUND_C

#include "background.h"

ztream_property_t property_background;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_background_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_background_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_background() {
    property_background = ztream_property(ZTREAM_TYPE_SINGLE(property_background_t), ctor, dtor);
}

#endif