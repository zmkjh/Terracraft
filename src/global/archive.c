// copyright. wwd 2510801129 2025/12/28 - --

#ifndef ARCHIVE_C
#define ARCHIVE_C

#include <stdio.h>
#include <string.h>
#include "archive.h"
#include "../setting.h"

typedef struct {
    int  id;
    char name[32];
    char pssw[32];
} user_info_t;

struct {
    int          count;
    user_info_t* info;
} users;

int loaded_landscopes;

void archive_load_users() {
    FILE* users_file = fopen(ARCHIVE_USERS_PATH, "rb");
    if (!users_file) {
        users.count = 0;
    } else {
        fread(&users.count, sizeof(users.count), 1, users_file);
        users.info = (user_info_t*)malloc(users.count * sizeof(user_info_t));
        fread(users.info, sizeof(user_info_t), users.count, users_file);
        fclose(users_file);
    }
}

void archive_save_users() {
    FILE* users_file = fopen(ARCHIVE_USERS_PATH, "wb");
    fwrite(&users.count, sizeof(users.count), 1, users_file);
    fwrite(users.info, sizeof(user_info_t), users.count, users_file);
    fclose(users_file);
}

void archive_load() {
    loaded_landscopes = 0;
    landscopes = (land_scope_t**)malloc(2 * sizeof(land_scope_t*));
    landscopes[0] = (land_scope_t*)malloc(2 * sizeof(land_scope_t));
    landscopes[1] = (land_scope_t*)malloc(2 * sizeof(land_scope_t));
    archive_load_users();
}

void archive_save() {
    archive_save_users();
    save_user_info();
    save_landscopes();
}

int archive_login_user(char* name, char* pssw) {
    user_info_t info;
    strcpy(info.name, name);
    strcpy(info.pssw, pssw);

    // find user
    int id = 0;
    for (; id < users.count; id++) {
        if (strcmp(users.info[id].name, info.name) == 0) {
            break;
        }
    }

    // not found
    if (id == users.count) {
        users.info = realloc(users.info, (users.count + 1) * sizeof(user_info_t));
        users.info[info.id = users.count++] = info;
        archive_save_users();
        return info.id;
    }

    if (strcmp(users.info[id].pssw, info.pssw) == 0) {
        return id;
    } else {
        return -1; // wrong password
    }
}

void archive_save_land_scope(land_scope_t* scope, ztream_coord_t left_down, int user_id) {
    char path_buff[128];
    sprintf(path_buff, "%s%d(%ld,%ld)", ARCHIVE_LANDS_PATH, user_id, left_down.x, left_down.y);

    FILE* file = fopen(path_buff, "wb");
    fwrite(scope, sizeof(land_scope_t), 1, file);
    fclose(file);
}

// generate a landscope when not found
void archive_load_land_scope(land_scope_t* dst, ztream_coord_t left_down, int user_id) {
    char path_buff[128];
    sprintf(path_buff, "%s%d(%ld,%ld)", ARCHIVE_LANDS_PATH, user_id, left_down.x, left_down.y);

    FILE* file = fopen(path_buff, "rb");
    if (file) {
        fread(dst, sizeof(land_scope_t), 1, file);
        fclose(file);
    } else {
        land_scope_generate(dst, left_down);
    }
}

void user_info_generate() {
    user_info.coord = (ztream_coord_t ){0, 0};
}

void load_user_info() {
    char path_buff[80];
    sprintf(path_buff, "%s%d", ARCHIVE_USER_INFO_PATH, user_id);

    FILE* file = fopen(path_buff, "rb");
    if (file) {
        fread(&user_info, sizeof(user_info), 1, file);
        fclose(file);
    } else {
        user_info_generate();
    }
}

void save_user_info() {
    char path_buff[80];
    sprintf(path_buff, "%s%d", ARCHIVE_USER_INFO_PATH, user_id);

    FILE* file = fopen(path_buff, "wb");
    fwrite(&user_info, sizeof(user_info), 1, file);
    fclose(file);
}

void load_landscopes() {
    int64_t near_x = (landscopes_init_coord.x / LAND_SCOPE_WIDTH) * LAND_SCOPE_WIDTH;
    int64_t near_y = (landscopes_init_coord.y / LAND_SCOPE_HEIGHT) * LAND_SCOPE_HEIGHT;

    archive_load_land_scope(
        &landscopes[1][0],
        (ztream_coord_t){
            near_x,
            near_y
        },
        user_id
    );

    archive_load_land_scope(
        &landscopes[0][0],
        (ztream_coord_t){
            near_x - LAND_SCOPE_WIDTH,
            near_y
        },
        user_id
    );

    archive_load_land_scope(
        &landscopes[0][1],
        (ztream_coord_t){
            near_x - LAND_SCOPE_WIDTH,
            near_y - LAND_SCOPE_HEIGHT
        },
        user_id
    );

    archive_load_land_scope(
        &landscopes[1][1],
        (ztream_coord_t){
            near_x,
            near_y - LAND_SCOPE_HEIGHT
        },
        user_id
    );

    loaded_landscopes = 1;
}

void save_landscopes() {
    if (!loaded_landscopes)
        return;

    int64_t near_x = (landscopes_init_coord.x / LAND_SCOPE_WIDTH) * LAND_SCOPE_WIDTH;
    int64_t near_y = (landscopes_init_coord.y / LAND_SCOPE_HEIGHT) * LAND_SCOPE_HEIGHT;

    archive_save_land_scope(
        &landscopes[1][0],
        (ztream_coord_t){
            near_x,
            near_y
        },
        user_id
    );

    archive_save_land_scope(
        &landscopes[0][0],
        (ztream_coord_t){
            near_x - LAND_SCOPE_WIDTH,
            near_y
        },
        user_id
    );

    archive_save_land_scope(
        &landscopes[0][1],
        (ztream_coord_t){
            near_x - LAND_SCOPE_WIDTH,
            near_y - LAND_SCOPE_HEIGHT
        },
        user_id
    );

    archive_save_land_scope(
        &landscopes[1][1],
        (ztream_coord_t){
            near_x,
            near_y - LAND_SCOPE_HEIGHT
        },
        user_id
    );
}

#define ABS(x) ((x) > 0 ? (x) : (-(x)))

int update_landscopes() {
    int64_t near_x = (landscopes_init_coord.x / LAND_SCOPE_WIDTH) * LAND_SCOPE_WIDTH;
    int64_t near_y = (landscopes_init_coord.y / LAND_SCOPE_HEIGHT) * LAND_SCOPE_HEIGHT;

    int64_t offset_x  = user_info.coord.x - near_x;
    int64_t offset_y  = user_info.coord.y - near_y;

    if (ABS(offset_x) <= LAND_SCOPE_WIDTH/2 && ABS(offset_y) <= LAND_SCOPE_HEIGHT/2)
        return 0;

    save_landscopes();
    
    if (ABS(offset_x) > LAND_SCOPE_WIDTH/2) {
        if (offset_x > 0) {
            landscopes_init_coord.x = near_x + LAND_SCOPE_WIDTH;
        } else {
            landscopes_init_coord.x = near_x - LAND_SCOPE_WIDTH;
        }
    }

    if (ABS(offset_y) > LAND_SCOPE_HEIGHT/2) {
        if (offset_y > 0) {
            landscopes_init_coord.y = near_y + LAND_SCOPE_HEIGHT;
        } else {
            landscopes_init_coord.y = near_y - LAND_SCOPE_HEIGHT;
        }
    }

    load_landscopes();

    return 1;
}

land_tex_t* landscopes_get(ztream_coord_t coord) {
    int64_t near_x = (landscopes_init_coord.x / LAND_SCOPE_WIDTH) * LAND_SCOPE_WIDTH;
    int64_t near_y = (landscopes_init_coord.y / LAND_SCOPE_HEIGHT) * LAND_SCOPE_HEIGHT;
    
    if (coord.x < near_x - LAND_SCOPE_WIDTH ||
        coord.x >= near_x + LAND_SCOPE_WIDTH ||
        coord.y < near_y - LAND_SCOPE_HEIGHT ||
        coord.y >= near_y + LAND_SCOPE_HEIGHT
    ) {
        return NULL;
    }

    int64_t offset_x  = coord.x - near_x;
    int64_t offset_y  = coord.y - near_y;

    if (offset_x >= 0 && offset_y >= 0) {
        return &landscopes[1][0].scope[offset_x][offset_y];
    }

    if (offset_x < 0 && offset_y < 0) {
        return &landscopes[0][1].scope[LAND_SCOPE_WIDTH + offset_x][LAND_SCOPE_HEIGHT + offset_y];
    }

    if (offset_x >= 0 && offset_y < 0) {
        return &landscopes[1][1].scope[offset_x][LAND_SCOPE_HEIGHT + offset_y];
    }

    if (offset_x < 0 && offset_y >= 0) {
        return &landscopes[0][0].scope[LAND_SCOPE_WIDTH + offset_x][offset_y];
    }

    return NULL;
}

#endif