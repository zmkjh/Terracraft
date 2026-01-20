// copyright. wwd 2510801129 2025/11/28 - --
#ifndef PROPERTIES_TEXT_C
#define PROPERTIES_TEXT_C

#include "unicode.h"

ztream_property_t property_unicode;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_unicode_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_unicode_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_unicode() {
    property_unicode = ztream_property(ZTREAM_TYPE_SINGLE(property_unicode_t), ctor, dtor);
}

#endif