// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_ACTION_BOX_LISTENER_C
#define SYSTEMS_ACTION_BOX_LISTENER_C

#include "../properties/button.h"
#include "../properties/action.h"
#include "../traits/action_box.h"
#include "entry_listener.h"
#include "button_listener.h"
#include "action_box_listener.h"

ztream_system_t system_action_box_listener;

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);

    property_button_t* button; ZTREAM_DATA_GET(button, ztream_entity_get(entity, property_button));
    property_action_t* action; ZTREAM_DATA_GET(action, ztream_entity_get(entity, property_action));

    if (ztream_button_meet_count(button)) {
        ztream_button_clear(button);

        (*action)();
    }
}

void system_init_action_box_listener() {
    system_action_box_listener = ztream_trait_system(trait_action_box, handler);
}

void system_dependency_action_box_listener() {
    ztream_system_add_dependency(system_action_box_listener, system_button_listener);
    ztream_system_add_dependency(system_action_box_listener, system_entry_listener);
}

#endif