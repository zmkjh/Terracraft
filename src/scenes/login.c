// copyright. wwd 2510801129 2025/12/26 - --
#ifndef SCENE_LOGIN_C
#define SCENE_LOGIN_C

#include "login.h"
#include "login/entities/login_entities.h"

ztream_scene_t scene_login;

void scene_init_login() {
    scene_login = ztream_scene();
    ztream_scene_relate_entity(&scene_login, &entity_login_background);
    ztream_scene_relate_entity(&scene_login, &entity_login_title);
    ztream_scene_relate_entity(&scene_login, &entity_login_username_label);
    ztream_scene_relate_entity(&scene_login, &entity_login_username_textbox);
    ztream_scene_relate_entity(&scene_login, &entity_login_password_label);
    ztream_scene_relate_entity(&scene_login, &entity_login_password_textbox);
    ztream_scene_relate_entity(&scene_login, &entity_login_button);
}

#endif