// copyright. wwd 2510801129 2025/11/28 - --
#ifndef TRAITS_ENTRY_ALPHA_C
#define TRAITS_ENTRY_ALPHA_C

#include "entry_alpha.h"
#include "../properties/cursor.h"
#include "../properties/entry.h"

ztream_trait_t trait_entry_alpha;

void trait_init_entry_alpha() {
    ztream_property_t properties[] = {property_entry, property_cursor};
    trait_entry_alpha = ztream_trait(properties, 2);
}

#endif