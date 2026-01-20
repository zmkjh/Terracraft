// copyright. wwd 2510801129 2025/12/28 - --

#ifndef LAND_C
#define LAND_C

#include "land.h"

const ztream_color_t land_tex_color[LAND_TEX_NUM-2] = {
    {90, 190, 110},     // leaf
    {70, 170, 90},      // grass
    {90, 40, 30},       // soil
    {50, 30, 20},       // rock
    {255, 70, 255},     // anti
    {240, 240, 170},    // sand
    {110, 120, 255},    // water
    {100, 100, 255},    // floating water
};

extern int land_tex_is_floating(land_tex_t tex) {
    if (tex == WATER_FLOAT)
        return 1;

    // if ... return 1; ...

    return 0;
}

void land_scope_generate_plain(land_scope_t* dst, ztream_coord_t left_down) {
    for (int i = 0; i < LAND_SCOPE_WIDTH; i++) {
        for (int j = 0; j < LAND_SCOPE_HEIGHT; j++) {
            int64_t x = left_down.x + i;
            int64_t y = left_down.y + j;

            if (y >= 0) {
                dst->scope[i][j] = AIR;
            } else if (y == -1) {
                if (rand()%100 >= 9)
                    dst->scope[i][j] = GRASS;
                else
                    dst->scope[i][j] = SOIL;
            } else if (y >= -4) {
                dst->scope[i][j] = SOIL;
            } else if (y == -5) {
                if (rand()%100 >= 49)
                    dst->scope[i][j] = ROCK;
                else
                    dst->scope[i][j] = SOIL;
            } else {
                dst->scope[i][j] = ROCK;
            }
        }
    }
}

void land_scope_generate_lake(land_scope_t* dst, ztream_coord_t left_down) {
    for (int i = 0; i < LAND_SCOPE_WIDTH; i++) {
        for (int j = 0; j < LAND_SCOPE_HEIGHT; j++) {
            int64_t x = left_down.x + i;
            int64_t y = left_down.y + j;

            if (y >= 0) {
                dst->scope[i][j] = AIR;
            } else if (y >= -20) {
                dst->scope[i][j] = WATER;
            } else if (y == -21 || y == -22) {
                if (rand()%100 >= 49)
                    dst->scope[i][j] = SAND;
                else
                    dst->scope[i][j] = WATER;
            } else if (y < -22 && y >= -35) {
                dst->scope[i][j] = SAND;
            } else {
                dst->scope[i][j] = ROCK;
            }
        }
    }
}

void land_scope_generate(land_scope_t* dst, ztream_coord_t left_down) {
    if (rand()%100 >= 20) {
        land_scope_generate_plain(dst, left_down);
    } else {
        land_scope_generate_lake(dst, left_down);
    }
}

#endif