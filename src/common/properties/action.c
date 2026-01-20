// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_ACTION_C
#define PROPERTIES_ACTION_C

#include "../../ztream/ztream.h"
#include "action.h"

ztream_property_t property_action;

static void ctor(ztream_data_t dst_data, ztream_data_t src_data) {
    property_action_t* dst; ZTREAM_DATA_GET(dst, dst_data);
    property_action_t* src; ZTREAM_DATA_GET(src, src_data);

    *dst = *src;
}

static void dtor(ztream_data_t data) {

}

void property_init_action() {
    property_action = ztream_property(ZTREAM_TYPE_SINGLE(property_action_t), ctor, dtor);
}

#endif