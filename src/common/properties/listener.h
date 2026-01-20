// copyright. wwd 2510801129 2025/11/27 - --
#ifndef PROPERTIES_LISTENER_H
#define PROPERTIES_LISTENER_H

#include "../../ztream/header.h"

typedef void(*property_listener_t)(void);

extern ztream_property_t property_listener;

void property_init_listener();

#endif