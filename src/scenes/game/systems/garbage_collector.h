// copyright. wwd 2510801129 2026/1/11 - --
#ifndef SYSTEMS_GARBAGE_COLLECTOR_H
#define SYSTEMS_GARBAGE_COLLECTOR_H

#include "../../../ztream/header.h"

extern ztream_system_t system_garbage_collector;

void system_init_garbage_collector();
void system_dependency_garbage_collector();

#endif