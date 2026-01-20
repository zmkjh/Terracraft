// copyright. wwd 2510801129 2025/11/26 - --
#ifndef SETTING_H
#define SETTING_H

#include "ztream/header.h"

#define TITLE                           "Terracraft"
#define FPS                             120
#define FONT_TYPE                       L"Consolas"
#define FONT_SIZE                       24

#define ARCHIVE_USERS_PATH              "archive/users.bin"
#define ARCHIVE_LANDS_PATH              "archive/lands/"
#define ARCHIVE_USER_INFO_PATH          "archive/info/"

#define LOGIN_PAGE_REGION               (ztream_region_t){.width = 30, .height = 12}
#define LOGIN_PAGE_COLOR                (ztream_color_t){253, 234, 194}
#define LOGIN_TITLE_REGION              (ztream_region_t){.x = LOGIN_PAGE_REGION.width/2 - 5, .y = 3, .width = 10, .height = 1}
#define LOGIN_TEXTBOX_COLOR             (ztream_color_t){255, 255, 255}
#define LOGIN_TEXTBOX_CURSOR_COLOR_BG   (ztream_color_t){250, 50, 50}
#define LOGIN_TEXTBOX_CURSOR_COLOR_FG   (ztream_color_t){255, 255, 255}
#define LOGIN_USERNAME_LABEL_CONTENT    U"账号"
#define LOGIN_PASSWORD_LABEL_CONTENT    U"密码"
#define LOGIN_USERNAME_LABEL_COLOR_FG   (ztream_color_t){100, 100, 100}
#define LOGIN_PASSWORD_LABEL_COLOR_FG   (ztream_color_t){100, 100, 100}
#define LOGIN_USERNAME_LABEL_REGION     (ztream_region_t){.x = 1, .y = 6, .width = 4, .height = 1}
#define LOGIN_PASSWORD_LABEL_REGION     (ztream_region_t){.x = 1, .y = 8, .width = 4, .height = 1}
#define LOGIN_USERNAME_TEXTBOX_REGION   (ztream_region_t){.x = 5, .y = 6, .width = LOGIN_PAGE_REGION.width - 2*5, .height = 1}
#define LOGIN_PASSWORD_TEXTBOX_REGION   (ztream_region_t){.x = 5, .y = 8, .width = LOGIN_PAGE_REGION.width - 2*5, .height = 1}
#define LOGIN_BUTTON_REGION             (ztream_region_t){.x = LOGIN_PAGE_REGION.width/2 - 2, .y = 10, .width = 4, .height = 1}
#define LOGIN_BUTTON_COLOR_BG           (ztream_color_t){100, 100, 100}
#define LOGIN_BUTTON_COLOR_FG           (ztream_color_t){250, 250, 250}
#define LOGIN_BUTTON_CONTENT            U"登录"

#define GAME_PAGE_REGION                (ztream_region_t){.width = 60, .height = 25}
#define GAME_PAGE_COLOR                 (ztream_color_t){230, 250, 255}
#define GAME_PLAYER_REGION              (ztream_region_t){.x = GAME_PAGE_REGION.width/2 - 1, .y = GAME_PAGE_REGION.height/2, .width = 1, .height = 1}
#define GAME_PLAYER_UNICODE             U"🐧"
#define GAME_PLAYER_COLOR               (ztream_color_t){50, 50, 50}

#define LAND_SCOPE_WIDTH                64
#define LAND_SCOPE_HEIGHT               64

#define GRAVITY -1

// path of a land scope = ARCHIVE_LANDS_PATH + userID + (x,y) -- leftDownCoord
// path of a user's info = ARCHIVE_USER_INFO_PATH + userID

#endif