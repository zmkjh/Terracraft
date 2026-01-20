// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_BUTTON_C
#define PROPERTIES_BUTTON_C

#include "button.h"

ztream_property_t property_button;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_button_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    ztream_region_t*   src; ZTREAM_DATA_GET(src, src_data);

    *dst = ztream_button(*src);
    ztream_button_activate(dst);
}

static void dtor(ztream_data_t dst_data) {

}

void property_init_button() {
    property_button = ztream_property(ZTREAM_TYPE_SINGLE(property_button_t), ctor, dtor);
}

#endif