// copyright. wwd 2510801129 2025/12/28 - --

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../ztream/header.h"
#include "land.h"

extern int user_id;

extern struct {
    ztream_coord_t coord;
} user_info;

// x x
// x x
// you are in the middle of it which belong to the right-top scope.
extern land_scope_t**   landscopes;
extern ztream_coord_t   landscopes_init_coord;

#endif