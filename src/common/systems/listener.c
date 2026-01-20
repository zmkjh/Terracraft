// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_LISTENER_C
#define SYSTEMS_LISTENER_C

#include "listener.h"
#include "../properties/listener.h"

ztream_system_t system_listener;

static void handler(ztream_data_t data) {
    property_listener_t* listener; ZTREAM_DATA_GET(listener, data);
    (*listener)();
}

void system_init_listener() {
    system_listener = ztream_property_system(property_listener, handler);
}

#endif