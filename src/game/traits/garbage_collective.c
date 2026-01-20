// copyright. wwd 2510801129 2026/1/11 - --
#ifndef TRAIT_GARBAGE_COLLECTIVE_C
#define TRAIT_GARBAGE_COLLECTIVE_C

#include "garbage_collective.h"

ztream_trait_t trait_garbage_collective;

void trait_init_garbage_collective() {
    ztream_property_t properties[0] = {};
    trait_garbage_collective = ztream_trait(properties, 0);
}

#endif