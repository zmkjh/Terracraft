// copyright. wwd 2510801129 2025/12/30 - --
#ifndef TRAIT_LIQUID_C
#define TRAIT_LIQUID_C

#include "liquid.h"
#include "../properties/motion.h"

ztream_trait_t trait_liquid;

void trait_init_liquid() {
    ztream_property_t properties[] = {property_motion};
    trait_liquid = ztream_trait(properties, 1);
}

#endif