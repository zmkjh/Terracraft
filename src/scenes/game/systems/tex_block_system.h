// copyright. wwd 2510801129 2025/12/30 - --
#ifndef SYSTEMS_TEX_BLOCK_H
#define SYSTEMS_TEX_BLOCK_H

#include "../../../ztream/header.h"

extern ztream_system_t system_tex_block_system;
extern ztream_coord_t  tex_block_light;
extern int             tex_block_anti_blue_factor;

void system_init_tex_block_system();
void system_dependency_tex_block_system();

#endif