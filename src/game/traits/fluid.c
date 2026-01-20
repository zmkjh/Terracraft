// copyright. wwd 2510801129 2025/12/30 - --
#ifndef TRAIT_FLUID_C
#define TRAIT_FLUID_C

#include "fluid.h"
#include "../properties/motion.h"

ztream_trait_t trait_fluid;

void trait_init_fluid() {
    ztream_property_t properties[] = {property_motion};
    trait_fluid = ztream_trait(properties, 1);
}

#endif