// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_TEX_BLOCK_C
#define SYSTEMS_TEX_BLOCK_C

#include "../../../game/traits/tex_block.h"
#include "../../../common/properties/background.h"
#include "../../../game/properties/motion.h"
#include "../../../global/archive.h"
#include "../../../global/global.h"
#include "../../../setting.h"
#include "../../../common/systems/listener.h"
#include "motion_system.h"
#include "garbage_collector.h"
#include <math.h>

#define PI 3.14159265

#define _NON_LINEAR0(x) (x)
#define _NON_LINEAR1(x) (sin((x) * PI/2.0f))
#define _NON_LINEAR2(x) _NON_LINEAR1(_NON_LINEAR1(x))
#define _NON_LINEAR3(x) _NON_LINEAR2(_NON_LINEAR1(x))
#define _NON_LINEAR4(x) _NON_LINEAR2(_NON_LINEAR2(x))

#define NON_LINEAR _NON_LINEAR1

#define BOUND_NORMAL 0.01
#define BOUND_ANTI   0.5

#define LIGHT_R 0.5
#define LIGHT_G 0.5
#define LIGHT_B 0.5

#define PLAYER_LIGHT_FACTOR 0.2

ztream_system_t system_tex_block_system;
ztream_coord_t  tex_block_light;
int             tex_block_anti_blue_factor;

static inline float L2(float x1, float y1, float x2, float y2) {
    return pow(pow(x1 - x2, 2) + pow((y1 - y2)*2.0f, 2), 0.5);
}

static inline float L1(float x1, float y1, float x2, float y2) {
    return abs(x1 - x2) + abs((y1 - y2)*2.0f);
}

#define L L2

static inline uint32_t color_tune(float c) {
    if (c < 0)
        return 0;
    if (c > 255)
        return 255;
    return c;
}

static inline void brightness_tune(ztream_color_t* color, float k) {
    color->r = color->r * (1-LIGHT_R + LIGHT_R*k);
    color->g = color->g * (1-LIGHT_G + LIGHT_G*k);
    color->b = color->b * (1-LIGHT_B + LIGHT_B*k);
}

static inline float brightness(ztream_color_t* color) {
    return 0.2990 * color->r + 0.7154 * color->g + 0.0721 * color->b;
}

static inline void saturation_tune(ztream_color_t* color, float k) {
    k -= 0.5;

    float B = brightness(color);

    color->r = color_tune(color->r + (color->r - B) * k);
    color->g = color_tune(color->g + (color->g - B) * k);
    color->b = color_tune(color->b + (color->b - B) * k);
}

static void handler(ztream_data_t data) {
    ztream_entity_t*   entity; ZTREAM_DATA_GET(entity, data);

    property_background_t*  bg;     ZTREAM_DATA_GET(bg, ztream_entity_get(entity, property_background));
    property_motion_t*      motion; ZTREAM_DATA_GET(motion, ztream_entity_get(entity, property_motion));

    land_tex_t* tex = landscopes_get((ztream_coord_t){motion->displacement.x, motion->displacement.y});

    if (!tex) {
        bg->region.width = 0;
        bg->region.height = 0;
        return;
    }

    if (*tex != motion->tex) {
        bg->region.width = 0;
        bg->region.height = 0;

        ztream_entity_erase(entity);

        return;
    }

    bg->region.x = motion->displacement.x - (user_info.coord.x - GAME_PLAYER_REGION.x);
    bg->region.y = GAME_PAGE_REGION.height + user_info.coord.y - GAME_PLAYER_REGION.y - motion->displacement.y - 1;
    bg->color = land_tex_color[*tex];

    ztream_coord_t light = tex_block_light;
    //light = (ztream_coord_t){GAME_PLAYER_REGION.x, 0};
    light.x = light.x < 0 ? 0 : light.x;
    light.x = light.x > GAME_PAGE_REGION.width ? GAME_PAGE_REGION.width : light.x;
    light.y = light.y < 0 ? 0 : light.y;
    light.y = light.y > GAME_PAGE_REGION.height ? GAME_PAGE_REGION.height : light.y;

    // get a circle region
    const float R_player  = L(0, 0, GAME_PLAYER_REGION.x, GAME_PLAYER_REGION.y);
    const float R_light   = L(0, 0, GAME_PAGE_REGION.width, GAME_PAGE_REGION.width)/4;
    float L2_player = L(bg->region.x, bg->region.y, GAME_PLAYER_REGION.x, GAME_PLAYER_REGION.y);
    float L2_light  = L(bg->region.x, bg->region.y, light.x, light.y);
    float f_player  = 1 - L2_player / R_player;
    float f_light   = 1 - L2_light / R_light;
    float factor    = PLAYER_LIGHT_FACTOR*f_player + (1-PLAYER_LIGHT_FACTOR)*f_light;

    factor = NON_LINEAR(factor);

    factor = factor < BOUND_NORMAL ? BOUND_NORMAL : factor;
    factor = factor > 1 ? 1 : factor;

    if (*tex == ANTI) {
        factor = factor < BOUND_ANTI ? BOUND_ANTI : factor;
        bg->color.b *= NON_LINEAR(tex_block_anti_blue_factor/100.0f);
    } else {
        brightness_tune(&bg->color, factor);
        saturation_tune(&bg->color, factor);
    }

    bg->region.width = 1;
    bg->region.height = 1;
}

void system_init_tex_block_system() {
    system_tex_block_system = ztream_trait_system(trait_tex_block, handler);
}

void system_dependency_tex_block_system() {
    ztream_system_add_dependency(system_tex_block_system, system_motion_system);
}

#endif