// copyright. wwd 2510801129 2025/12/30 - --
#ifndef TRAIT_TNT_BLOCK_C
#define TRAIT_TNT_BLOCK_C

#include "tnt_block.h"
#include "../properties/motion.h"
#include "../properties/timer.h"

ztream_trait_t trait_tnt_block;

void trait_init_tnt_block() {
    ztream_property_t properties[] = {property_motion, property_timer};
    trait_tnt_block = ztream_trait(properties, 2);
}

#endif
