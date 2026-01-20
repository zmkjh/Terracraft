// copyright. wwd 2510801129 2025/11/27 - --
#ifndef COMMON_TRAITS_C
#define COMMON_TRAITS_C

#include "traits.h"
#include "traits/entry_with_cursor.h"
#include "traits/entry_listening.h"
#include "traits/entry_alpha.h"
#include "traits/action_box.h"

void traits_init_common() {
    trait_init_entry_with_cursor();
    trait_init_entry_listening();
    trait_init_entry_alpha();
    trait_init_action_box();
}

#endif