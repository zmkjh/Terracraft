// copyright. wwd 2510801129 2025/12/30 - --
#ifndef PROPERTIES_MOTION_H
#define PROPERTIES_MOTION_H

#include "../../ztream/header.h"
#include "../../global/land.h"

typedef struct {
    land_tex_t tex;

    struct {
        float x;
        float y;
    } displacement;

    struct {
        float x;
        float y;
    } velocity;

    struct {
        float x;
        float y;
    } acceleration;
} property_motion_t;

extern ztream_property_t property_motion;

void property_init_motion();

#endif