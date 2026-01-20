// copyright. wwd 2510801129 2025/11/28 - --
#ifndef TRAITS_ENTRY_WITH_CURSOR_C
#define TRAITS_ENTRY_WITH_CURSOR_C

#include "entry_with_cursor.h"
#include "../properties/cursor.h"
#include "../properties/entry.h"

ztream_trait_t trait_entry_with_cursor;

void trait_init_entry_with_cursor() {
    ztream_property_t properties[] = {property_entry, property_cursor};
    trait_entry_with_cursor = ztream_trait(properties, 2);
}

#endif