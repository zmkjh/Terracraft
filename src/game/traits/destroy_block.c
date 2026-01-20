// copyright. wwd 2510801129 2025/12/30 - --
#ifndef TRAIT_DESTROY_BLOCK_C
#define TRAIT_DESTROY_BLOCK_C

#include "destroy_block.h"
#include "../properties/motion.h"

ztream_trait_t trait_destroy_block;

void trait_init_destroy_block() {
    ztream_property_t properties[] = {property_motion};
    trait_destroy_block = ztream_trait(properties, 1);
}

#endif