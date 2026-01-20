// copyright. wwd 2510801129 2025/12/28 - --

#ifndef LAND_H
#define LAND_H

#include "../ztream/header.h"
#include "../setting.h"

#define LAND_TEX_NUM 10

// liquid has two state, floating tex should be the normal tex + 1

typedef enum {
    ANIMAL  = -2,
    AIR     = -1,
    LEAF    = 0,
    GRASS,
    SOIL,
    ROCK,
    ANTI,
    SAND,
    WATER,
    WATER_FLOAT,
} land_tex_t;

#define LAND_TEX_TOBE_FLOATING(tex) ((tex) + 1)
#define LAND_TEX_TONOT_FLOATING(tex) ((tex) - 1)
extern int land_tex_is_floating(land_tex_t tex);

// without air
extern const ztream_color_t land_tex_color[LAND_TEX_NUM-2];

typedef struct {
    land_tex_t scope[LAND_SCOPE_WIDTH][LAND_SCOPE_HEIGHT];
} land_scope_t;

void land_scope_generate(land_scope_t* dst, ztream_coord_t left_down);

#endif