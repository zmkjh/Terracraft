// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_TEXT_C
#define PROPERTIES_TEXT_C

#include "text.h"

ztream_property_t property_text;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_text_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_text_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_text() {
    property_text = ztream_property(ZTREAM_TYPE_SINGLE(property_text_t), ctor, dtor);
}

#endif