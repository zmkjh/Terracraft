// copyright. wwd 2510801129 2025/11/28 - --
#ifndef TRAITS_ENTRY_LISTENING_C
#define TRAITS_ENTRY_LISTENING_C

#include "entry_listening.h"
#include "../properties/entry.h"

ztream_trait_t trait_entry_listening;

void trait_init_entry_listening() {
    ztream_property_t properties[1] = {property_entry};
    trait_entry_listening = ztream_trait(properties, 1);
}

#endif