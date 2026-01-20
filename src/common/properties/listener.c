// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_LISTENER_C
#define PROPERTIES_LISTENER_C

#include "listener.h"

ztream_property_t property_listener;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_listener_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_listener_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_listener() {
    property_listener = ztream_property(ZTREAM_TYPE_SINGLE(property_listener_t), ctor, dtor);
}

#endif