// copyright. wwd 2510801129 2025/12/28 - --
#ifndef GAME_TRAITS_C
#define GAME_TRAITS_C

#include "traits.h"
#include "traits/tex_block.h"
#include "traits/fluid.h"
#include "traits/liquid.h"
#include "traits/destroy_block.h"
#include "traits/garbage_collective.h"
#include "traits/tnt_block.h"

void traits_init_game() {
    trait_init_tex_block();
    trait_init_fluid();
    trait_init_liquid();
    trait_init_destroy_block();
    trait_init_garbage_collective();
    trait_init_tnt_block();
}

#endif
