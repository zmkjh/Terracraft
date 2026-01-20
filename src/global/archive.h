// copyright. wwd 2510801129 2025/12/28 - --

#ifndef ARCHIVE_H
#define ARCHIVE_H

#include "global.h"

void archive_load();
void archive_save();

void archive_save_users();

// @return -1: password wrong
// @return id: new account or login successfully
int archive_login_user(char* name, char* pssw);

// generate a landscope when not found
void archive_load_land_scope(land_scope_t* dst, ztream_coord_t left_down, int user_id);
void archive_save_land_scope(land_scope_t* scope, ztream_coord_t left_down, int user_id);

void load_user_info();
void save_user_info();

void load_landscopes();
void save_landscopes();

// @return updated or not
int         update_landscopes();
// @return return NULL when coord not in current landscopes
land_tex_t* landscopes_get(ztream_coord_t coord);

#endif