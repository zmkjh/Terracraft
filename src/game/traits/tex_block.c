// copyright. wwd 2510801129 2025/12/30 - --
#ifndef TRAIT_TEX_BLOCK_C
#define TRAIT_TEX_BLOCK_C

#include "tex_block.h"
#include "../../common/properties/background.h"
#include "../properties/motion.h"

ztream_trait_t trait_tex_block;

void trait_init_tex_block() {
    ztream_property_t properties[] = {property_background, property_motion};
    trait_tex_block = ztream_trait(properties, 2);
}

#endif