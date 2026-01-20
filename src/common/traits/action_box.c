// copyright. wwd 2510801129 2025/11/28 - --
#ifndef ACTION_BOX_C
#define ACTION_BOX_C

#include "action_box.h"
#include "../properties/button.h"
#include "../properties/action.h"

ztream_trait_t trait_action_box;

void trait_init_action_box() {
    ztream_property_t properties[] = {property_button, property_action};
    trait_action_box = ztream_trait(properties, 2);
}

#endif