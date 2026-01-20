// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_ACTION_H
#define PROPERTIES_ACTION_H

#include "../../ztream/header.h"

typedef void(*property_action_t)();

extern ztream_property_t property_action;

void property_init_action();

#endif