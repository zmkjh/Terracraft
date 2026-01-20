// copyright. wwd 2510801129 2025/12/28 - --
#ifndef ENTITIES_GAME_ENTITIES_C
#define ENTITIES_GAME_ENTITIES_C

#include "game_entities.h"
#include "../../../common/properties/background.h"
#include "../../../common/properties/foreground.h"
#include "../../../common/properties/listener.h"
#include "../../../common/properties/unicode.h"
#include "../../../setting.h"
#include "../../../global/global.h"
#include "../../../game/properties/motion.h"
#include "../../../game/traits/tex_block.h"
#include "../../../game/traits/destroy_block.h"
#include "../../../game/traits/fluid.h"
#include "../../../game/traits/liquid.h"
#include "../../../game/traits/garbage_collective.h"
#include "../../../global/archive.h"
#include "../../../global/land.h"
#include "../systems/tex_block_system.h"
#include "../systems/garbage_collector.h"
#include <math.h>

#define TEX_BLOCK_IN_ROW_MAX 16
#define LOG(x) { FILE* log = fopen("log.txt", "a+"); fprintf(log, x"\n"); fclose(log); }

ztream_entity_t     entity_game_background;
ztream_entity_t     entity_game_player;
ztream_entity_t     entity_game_player_entity;
ztream_entity_t     entity_game_updater;

static ztream_container_t left_down_coords;

ztream_coord_t cursor;

static void background_init() {
    property_background_t bg = (property_background_t) {
        .color = GAME_PAGE_COLOR,
        .region = GAME_PAGE_REGION
    };

    entity_game_background = ztream_entity();
    ztream_entity_add_property(&entity_game_background, property_background, &bg);
}

static void set_tex_water(float x, float y, float v_x, float v_y) {
    ztream_entity_t new = ztream_entity();
    property_motion_t motion;
    motion.tex            = WATER;
    motion.displacement.x = x;
    motion.displacement.y = y;
    motion.velocity.x     = 0;
    motion.velocity.y     = 0;
    motion.acceleration.x = 0;
    motion.acceleration.y = 0;

    property_background_t bg;
    bg.region.x = 0;
    bg.region.y = 0;
    bg.region.height = 0;
    bg.region.width = 0;
    bg.color.r = 0;
    bg.color.g = 0;
    bg.color.b = 0;

    ztream_entity_add_property(&new, property_motion, &motion);
    ztream_entity_add_property(&new, property_background, &bg);
    ztream_entity_check_trait(&new, trait_tex_block);
    ztream_entity_check_trait(&new, trait_liquid);
    //ztream_entity_check_trait(&new, trait_garbage_collective);
}

static void set_tex_water_float(float x, float y, float v_x, float v_y) {
    ztream_entity_t new = ztream_entity();
    property_motion_t motion;
    motion.tex            = WATER_FLOAT;
    motion.displacement.x = x;
    motion.displacement.y = y;
    motion.velocity.x     = 0;
    motion.velocity.y     = 0;
    motion.acceleration.x = 0;
    motion.acceleration.y = 0;

    property_background_t bg;
    bg.region.x = 0;
    bg.region.y = 0;
    bg.region.height = 0;
    bg.region.width = 0;
    bg.color.r = 0;
    bg.color.g = 0;
    bg.color.b = 0;

    ztream_entity_add_property(&new, property_motion, &motion);
    ztream_entity_add_property(&new, property_background, &bg);
    ztream_entity_check_trait(&new, trait_tex_block);
    ztream_entity_check_trait(&new, trait_liquid);
    //ztream_entity_check_trait(&new, trait_garbage_collective);
}

static void set_tex_sand(float x, float y, float v_x, float v_y) {
    ztream_entity_t new = ztream_entity();
    property_motion_t motion;
    motion.tex            = SAND;
    motion.displacement.x = x;
    motion.displacement.y = y;
    motion.velocity.x     = v_x;
    motion.velocity.y     = v_y;
    motion.acceleration.x = 0;
    motion.acceleration.y = GRAVITY;

    property_background_t bg;
    bg.region.x = 0;
    bg.region.y = 0;
    bg.region.height = 0;
    bg.region.width = 0;
    bg.color.r = 0;
    bg.color.g = 0;
    bg.color.b = 0;

    ztream_entity_add_property(&new, property_motion, &motion);
    ztream_entity_add_property(&new, property_background, &bg);
    ztream_entity_check_trait(&new, trait_tex_block);
    ztream_entity_check_trait(&new, trait_fluid);
    //ztream_entity_check_trait(&new, trait_garbage_collective);
}

static void set_tex_normal(land_tex_t tex, float x, float y, float v_x, float v_y) {
    ztream_entity_t new = ztream_entity();
    property_motion_t motion;
    motion.tex            = tex;
    motion.displacement.x = x;
    motion.displacement.y = y;
    motion.velocity.x     = v_x;
    motion.velocity.y     = v_y;
    motion.acceleration.x = 0;
    motion.acceleration.y = GRAVITY;

    property_background_t bg;
    bg.region.x = 0;
    bg.region.y = 0;
    bg.region.height = 0;
    bg.region.width = 0;
    bg.color.r = 0;
    bg.color.g = 0;
    bg.color.b = 0;

    ztream_entity_add_property(&new, property_motion, &motion);
    ztream_entity_add_property(&new, property_background, &bg);
    ztream_entity_check_trait(&new, trait_tex_block);
    //ztream_entity_check_trait(&new, trait_garbage_collective);
}

static void set_tex_rock(float x, float y, float v_x, float v_y) {
    set_tex_normal(ROCK, x, y, v_x, v_y);
}

static void set_tex_grass(float x, float y, float v_x, float v_y) {
    set_tex_normal(GRASS, x, y, v_x, v_y);
}

static void set_tex_soil(float x, float y, float v_x, float v_y) {
    set_tex_normal(SOIL, x, y, v_x, v_y);
}

static void set_tex_anti(float x, float y, float v_x, float v_y) {
    ztream_entity_t new = ztream_entity();
    property_motion_t motion;
    motion.tex            = ANTI;
    motion.displacement.x = x;
    motion.displacement.y = y;
    motion.velocity.x     = v_x;
    motion.velocity.y     = v_y;
    motion.acceleration.x = 0;
    motion.acceleration.y = 0;

    property_background_t bg;
    bg.region.x = 0;
    bg.region.y = 0;
    bg.region.height = 0;
    bg.region.width = 0;
    bg.color.r = 0;
    bg.color.g = 0;
    bg.color.b = 0;

    ztream_entity_add_property(&new, property_motion, &motion);
    ztream_entity_add_property(&new, property_background, &bg);
    ztream_entity_check_trait(&new, trait_tex_block);
    //ztream_entity_check_trait(&new, trait_garbage_collective);
}

static void load_tex(land_tex_t tex, float x, float y, float v_x, float v_y) {
    switch (tex) {
    case ROCK:
        set_tex_rock(x, y, v_x, v_y);
        break;
    case ANTI:
        set_tex_anti(x, y, v_x, v_y);
        break;
    case SAND:
        set_tex_sand(x, y, v_x, v_y);
        break;
    case GRASS:
        set_tex_grass(x, y, v_x, v_y);
        break;
    case SOIL:
        set_tex_soil(x, y, v_x, v_y);
        break;
    case WATER:
        set_tex_water(x, y, v_x, v_y);
    case WATER_FLOAT:
        set_tex_water_float(x, y, v_x, v_y);
    }
}

static void update_tex(land_tex_t tex, float x, float y, float v_x, float v_y) {
    land_tex_t* dst = landscopes_get((ztream_coord_t){x, y});

    if (!dst || *dst == tex || land_tex_is_floating(*dst) && LAND_TEX_TONOT_FLOATING(*dst) == tex) {
        return;
    }

    *dst = tex;

    load_tex(tex, x, y, v_x, v_y);
}

static void garbage_collector_callback();

void entity_init_game() {
    background_init();

    entity_game_player = ztream_entity();

    property_unicode_t text = (property_unicode_t) {
        .content = GAME_PLAYER_UNICODE,
        .region  = GAME_PLAYER_REGION
    };

    ztream_entity_add_property(&entity_game_player, property_unicode, &text);

    entity_game_updater = ztream_entity();
    property_listener_t update_listener = &entity_reload_game;
    ztream_entity_add_property(&entity_game_updater, property_listener, &update_listener);

    // not available now
    //ztream_system_set_callback(system_garbage_collector, &garbage_collector_callback);
}

void player_action_listener() {
    // event
    property_motion_t* motion; ZTREAM_DATA_GET(motion, ztream_entity_get(&entity_game_player_entity, property_motion));

    user_info.coord.x = motion->displacement.x;
    user_info.coord.y = motion->displacement.y;

    static land_tex_t place_type = ROCK;

    // movement
    if (ztream_key_state('A') == ztream_key_state_push) {
        motion->velocity.x -= 1;
    }
    if (ztream_key_state('D') == ztream_key_state_push) {
        motion->velocity.x += 1;
    }
    if (ztream_key_state('W') == ztream_key_state_push) {
        motion->velocity.y += 1;
    }
    if (ztream_key_state('S') == ztream_key_state_push) {
        motion->velocity.y -= 1;
    }

    if (ztream_key_state('R') == ztream_key_state_push) {
        ztream_system_unlock(system_garbage_collector);
    }

    static int ztream_key_shift_state_last = ztream_key_state_release;
    static int ztream_key_shift_state_curr = ztream_key_state_release;
    if ((ztream_key_shift_state_curr = ztream_key_state(ztream_key_cap)) != ztream_key_shift_state_last && ztream_key_shift_state_curr) {
        if (place_type == WATER) {
            place_type = ANTI;
        } else if (place_type == ANTI) {
            place_type = SAND;
        } else if (place_type == SAND) {
            place_type = ROCK;
        } else if (place_type == ROCK) {
            place_type = WATER;
        }
    }
    ztream_key_shift_state_last = ztream_key_shift_state_curr;

    // place block
    if (ztream_key_state(ztream_key_left_button) == ztream_key_state_push) {
        if (!(cursor.x < 0 || cursor.y < 1 || cursor.x >= GAME_PAGE_REGION.width || cursor.y >= GAME_PAGE_REGION.height)) {
            int64_t x = cursor.x  +  user_info.coord.x - GAME_PLAYER_REGION.x;
            int64_t y = - cursor.y  + GAME_PAGE_REGION.height + user_info.coord.y - GAME_PLAYER_REGION.y - 1;

            update_tex(place_type, x, y, motion->velocity.x, motion->velocity.y);
        }
    }

    if (ztream_key_state(ztream_key_middle_button) == ztream_key_state_push) {
        ztream_coord_t cursor = ztream_cursor_coord();
        if (!(cursor.x < 0 || cursor.y < 1 || cursor.x >= GAME_PAGE_REGION.width || cursor.y >= GAME_PAGE_REGION.height)) {
            int64_t x = cursor.x  +  user_info.coord.x - GAME_PLAYER_REGION.x;
            int64_t y = - cursor.y  + GAME_PAGE_REGION.height + user_info.coord.y - GAME_PLAYER_REGION.y - 1;

            land_tex_t* tex = landscopes_get((ztream_coord_t){x, y});
            if (tex && *tex >= 0) {
                if (tex) {
                    *tex = AIR;
                }
            }
        }
    }

    // foreground
    property_foreground_t* player_fg; ZTREAM_DATA_GET(player_fg, ztream_entity_get(&entity_game_player_entity, property_foreground));

    *player_fg = (property_foreground_t) {
        .color  = GAME_PLAYER_COLOR,
        .region = GAME_PLAYER_REGION
    };
}

void entity_init_player() {
    entity_game_player_entity = ztream_entity();

    *landscopes_get((ztream_coord_t){user_info.coord.x, user_info.coord.y}) = ANIMAL;

    property_motion_t motion;
    motion.tex            = ANIMAL;
    motion.displacement.x = user_info.coord.x;
    motion.displacement.y = user_info.coord.y;
    motion.velocity.x     = 0;
    motion.velocity.y     = 0;
    motion.acceleration.x = 0;
    motion.acceleration.y = GRAVITY;

    property_listener_t listener = &player_action_listener;

    property_foreground_t fg = {
        .color  = GAME_PLAYER_COLOR,
        .region = GAME_PLAYER_REGION
    };

    ztream_entity_add_property(&entity_game_player_entity, property_foreground, &fg);
    ztream_entity_add_property(&entity_game_player_entity, property_motion, &motion);
    ztream_entity_add_property(&entity_game_player_entity, property_listener, &listener);
}

void entity_reload_game_scope(land_scope_t* scope, ztream_coord_t left_down) {
    static int reload_game_scope_first = 1;
    if (reload_game_scope_first) {
        reload_game_scope_first = 0;
        entity_init_player();
        left_down_coords = ztream_container_alloc(ZTREAM_TYPE_SINGLE(ztream_coord_t), 4);
    }

    for (int i = 0; i < ztream_container_size(&left_down_coords); i++) {
        ztream_coord_t* saved_coord; ZTREAM_DATA_GET(saved_coord, ztream_container_get(&left_down_coords, i));
        if (saved_coord->x == left_down.x && saved_coord->y == left_down.y) {
            return;
        }
    }

    for (int i = 0; i < LAND_SCOPE_WIDTH; i++) {
        for (int j = 0; j < LAND_SCOPE_HEIGHT; j++) {
            land_tex_t tex = *landscopes_get((ztream_coord_t){left_down.x + i, left_down.y + j});
            load_tex(tex, left_down.x + i, left_down.y + j, 0, 0);
        }
    }

    ztream_container_push_back(&left_down_coords, &left_down);
}

void entity_reload_game() {
    cursor = ztream_cursor_coord();
    tex_block_light = cursor;
    
    static int step = -2;
    tex_block_anti_blue_factor += step;
    if (tex_block_anti_blue_factor < 0 || tex_block_anti_blue_factor > 100) {
        step *= -1;
        tex_block_anti_blue_factor += step;
    }

    if (update_landscopes() || !ztream_container_size(&left_down_coords)) {
        int64_t near_x = (landscopes_init_coord.x / LAND_SCOPE_WIDTH) * LAND_SCOPE_WIDTH;
        int64_t near_y = (landscopes_init_coord.y / LAND_SCOPE_HEIGHT) * LAND_SCOPE_HEIGHT;

        entity_reload_game_scope(&landscopes[1][0], (ztream_coord_t){near_x, near_y});
        entity_reload_game_scope(&landscopes[1][1], (ztream_coord_t){near_x, near_y - LAND_SCOPE_HEIGHT});
        entity_reload_game_scope(&landscopes[0][0], (ztream_coord_t){near_x - LAND_SCOPE_WIDTH, near_y});
        entity_reload_game_scope(&landscopes[0][1], (ztream_coord_t){near_x - LAND_SCOPE_WIDTH, near_y - LAND_SCOPE_HEIGHT});
    }

    /* not available :(
    if (ztream_container_size(&left_down_coords) > TEX_BLOCK_IN_ROW_MAX) {
        ztream_system_unlock(system_garbage_collector);
    }
    */
}

static void garbage_collector_callback() {
    ztream_system_lock(system_garbage_collector);
    ztream_container_clear(&left_down_coords);
}

#endif