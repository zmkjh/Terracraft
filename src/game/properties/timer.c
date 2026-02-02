// copyright. wwd 2510801129 2025/12/30 - --
#ifndef PROPERTIES_TIMER_C
#define PROPERTIES_TIMER_C

#include "timer.h"

ztream_property_t property_timer;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_timer_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_timer_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_timer() {
    property_timer = ztream_property(ZTREAM_TYPE_SINGLE(property_timer_t), ctor, dtor);
}

#endif
