// copyright. wwd 2510801129 2025/11/28 - --
#ifndef SYSTEMS_ENTRY_LISTENER_C
#define SYSTEMS_ENTRY_LISTENER_C

#include "entry_alpha_listener.h"
#include "../properties/entry.h"
#include "../properties/button.h"
#include "../traits/entry_alpha.h"
#include "../traits/entry_listening.h"
#include "../traits/entry_with_cursor.h"
#include "button_listener.h"

ztream_system_t system_entry_alpha_listener;

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);

    property_entry_t*  entry;  ZTREAM_DATA_GET(entry, ztream_entity_get(entity, property_entry));
    property_button_t* button; ZTREAM_DATA_GET(button, ztream_entity_get(entity, property_button));
    
    if (ztream_button_meet_count(button)) {
        ztream_button_clear(button);

        ztream_entity_check_trait(entity, trait_entry_listening);
        ztream_entity_check_trait(entity, trait_entry_with_cursor);
    }
    if (ztream_button_miss_count(button)) {
        ztream_button_clear(button);

        ztream_entity_throw_trait(entity, trait_entry_listening);
        ztream_entity_throw_trait(entity, trait_entry_with_cursor);
    }
}

void system_init_entry_alpha_listener() {
    system_entry_alpha_listener = ztream_trait_system(trait_entry_alpha, handler);
}

void system_dependency_entry_alpha_listener() {
    ztream_system_add_dependency(system_entry_alpha_listener, system_button_listener);
}

#endif