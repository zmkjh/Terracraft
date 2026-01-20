// copyright. wwd 2510801129 2025/11/27 - --
#ifndef SYSTEMS_ENTRY_LISTENER_C
#define SYSTEMS_ENTRY_LISTENER_C

#include "listener.h"
#include "../properties/entry.h"
#include "../traits/entry_listening.h"

ztream_system_t system_entry_listener;

static void handler(ztream_data_t data) {
    ztream_entity_t*  entity; ZTREAM_DATA_GET(entity, data);
    property_entry_t* entry;  ZTREAM_DATA_GET(entry, ztream_entity_get(entity, property_entry));

    ztream_entry_listen(&entry->entry, (ztream_coord_t){.x = entry->zone.width, .y = entry->zone.height} , 400);
}

void system_init_entry_listener() {
    system_entry_listener = ztream_trait_system(trait_entry_listening, handler);
}

#endif