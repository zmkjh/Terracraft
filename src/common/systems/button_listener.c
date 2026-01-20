// copyright. wwd 2510801129 2025/11/28 - --
#ifndef SYSTEMS_ENTRY_BUTTON_LISTENER_C
#define SYSTEMS_ENTRY_BUTTON_LISTENER_C

#include "button_listener.h"
#include "../properties/button.h"
#include <stdlib.h>

ztream_system_t system_button_listener;

static void handler(ztream_data_t data) {
    property_button_t* button; ZTREAM_DATA_GET(button, data);

    ztream_button_listen(button);
}

void system_init_button_listener() {
    system_button_listener = ztream_property_system(property_button, handler);
}

#endif