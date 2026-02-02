// copyright. wwd 2510801129 2025/12/30 - --
#ifndef PROPERTIES_TIMER_H
#define PROPERTIES_TIMER_H

#include "../../ztream/header.h"
#include "../../global/land.h"
#include <time.h>

typedef struct {
    time_t end;
} property_timer_t;

extern ztream_property_t property_timer;

void property_init_timer();

#endif
