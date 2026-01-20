// copyright. wwd 2510801129 2025/12/30 - --
#ifndef PROPERTIES_MOTION_C
#define PROPERTIES_MOTION_C

#include "motion.h"

ztream_property_t property_motion;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_motion_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_motion_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_motion() {
    property_motion = ztream_property(ZTREAM_TYPE_SINGLE(property_motion_t), ctor, dtor);
}

#endif