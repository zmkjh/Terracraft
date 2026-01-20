// copyright. wwd 2510801129 2025/11/28 - --
#ifndef ENTITIES_LOGIN_ENTITIES_C
#define ENTITIES_LOGIN_ENTITIES_C

#include "login_entities.h"
#include "../../../common/properties/background.h"
#include "../../../common/properties/foreground.h"
#include "../../../common/properties/button.h"
#include "../../../common/properties/entry.h"
#include "../../../common/properties/text.h"
#include "../../../common/properties/unicode.h"
#include "../../../common/properties/cursor.h"
#include "../../../common/properties/action.h"
#include "../../../common/traits/entry_with_cursor.h"
#include "../../../common/traits/entry_listening.h"
#include "../../../common/traits/entry_alpha.h"
#include "../../../common/traits/action_box.h"
#include "../../../setting.h"
#include "../../../global/archive.h"
#include "../../../global/global.h"
#include "../../../scenes/login.h"
#include "../../../scenes/game.h"
#include "../../../scenes/game/entities/game_entities.h"

ztream_entity_t entity_login_background;
static void entity_init_login_background();

ztream_entity_t entity_login_title;
static void entity_init_login_title();

ztream_entity_t entity_login_username_label;
static void entity_init_login_username_label();

ztream_entity_t entity_login_username_textbox;
static void entity_init_login_username_textbox();

ztream_entity_t entity_login_password_label;
static void entity_init_login_password_label();

ztream_entity_t entity_login_password_textbox;
static void entity_init_login_password_textbox();

ztream_entity_t entity_login_button;
static void entity_init_login_button();

void entity_init_login() {
    entity_init_login_background();
    entity_init_login_title();
    entity_init_login_username_label();
    entity_init_login_password_label();
    entity_init_login_username_textbox();
    entity_init_login_password_textbox();
    entity_init_login_button();
}

static void entity_init_login_username_label() {
    entity_login_username_label = ztream_entity();

    property_unicode_t text = (property_unicode_t) {
        .content = LOGIN_USERNAME_LABEL_CONTENT,
        .region  = LOGIN_USERNAME_LABEL_REGION
    };

    property_foreground_t fg = (property_foreground_t) {
        .color  = LOGIN_USERNAME_LABEL_COLOR_FG,
        .region = LOGIN_USERNAME_LABEL_REGION
    };

    ztream_entity_add_property(&entity_login_username_label, property_unicode, &text);
    ztream_entity_add_property(&entity_login_username_label, property_foreground, &fg);
}

static void entity_init_login_password_label() {
    entity_login_password_label = ztream_entity();

    property_unicode_t text = (property_unicode_t) {
        .content = LOGIN_PASSWORD_LABEL_CONTENT,
        .region  = LOGIN_PASSWORD_LABEL_REGION
    };

    property_foreground_t fg = (property_foreground_t) {
        .color  = LOGIN_PASSWORD_LABEL_COLOR_FG,
        .region = LOGIN_PASSWORD_LABEL_REGION
    };

    ztream_entity_add_property(&entity_login_password_label, property_unicode, &text);
    ztream_entity_add_property(&entity_login_password_label, property_foreground, &fg);
}

static void entity_init_login_background() {
    entity_login_background = ztream_entity();
    property_background_t login_background = (property_background_t) {
        .color  = LOGIN_PAGE_COLOR,
        .region = LOGIN_PAGE_REGION
    };
    ztream_entity_add_property(&entity_login_background, property_background, &login_background);
}

static void entity_init_login_title() {
    entity_login_title = ztream_entity();

    property_text_t text = (property_text_t) {
        .content = TITLE,
        .region  = LOGIN_TITLE_REGION
    };

    ztream_entity_add_property(&entity_login_title, property_text, &text);
}

static void entity_init_login_username_textbox() {
    entity_login_username_textbox = ztream_entity();

    property_background_t background = (property_background_t) {
        .color  = LOGIN_TEXTBOX_COLOR,
        .region = LOGIN_USERNAME_TEXTBOX_REGION
    };

    property_entry_info_t entry_info = (property_entry_info_t) {
        .size = 800,
        .zone = LOGIN_USERNAME_TEXTBOX_REGION
    };

    ztream_entity_add_property(&entity_login_username_textbox, property_background, &background);
    ztream_entity_add_property(&entity_login_username_textbox, property_button, &LOGIN_USERNAME_TEXTBOX_REGION);
    ztream_entity_add_property(&entity_login_username_textbox, property_entry, &entry_info);

    property_entry_t* textbox_entry;
    ZTREAM_DATA_GET(textbox_entry, ztream_entity_get(&entity_login_username_textbox, property_entry));

    property_text_t text = (property_text_t) {
        .content = textbox_entry->buffer,
        .region  = LOGIN_USERNAME_TEXTBOX_REGION
    };

    property_cursor_t cursor = (property_cursor_t) {
        .bg = LOGIN_TEXTBOX_CURSOR_COLOR_BG,
        .fg = LOGIN_TEXTBOX_CURSOR_COLOR_FG
    };

    ztream_entity_add_property(&entity_login_username_textbox, property_text, &text);
    ztream_entity_add_property(&entity_login_username_textbox, property_cursor, &cursor);

    ztream_entity_check_trait(&entity_login_username_textbox, trait_entry_alpha);
}

static void entity_init_login_password_textbox() {
    entity_login_password_textbox = ztream_entity();

    property_background_t background = (property_background_t) {
        .color  = LOGIN_TEXTBOX_COLOR,
        .region = LOGIN_PASSWORD_TEXTBOX_REGION
    };

    property_entry_info_t entry_info = (property_entry_info_t) {
        .size = 800,
        .zone = LOGIN_PASSWORD_TEXTBOX_REGION
    };

    ztream_entity_add_property(&entity_login_password_textbox, property_background, &background);
    ztream_entity_add_property(&entity_login_password_textbox, property_button, &LOGIN_PASSWORD_TEXTBOX_REGION);
    ztream_entity_add_property(&entity_login_password_textbox, property_entry, &entry_info);

    property_entry_t* textbox_entry;
    ZTREAM_DATA_GET(textbox_entry, ztream_entity_get(&entity_login_password_textbox, property_entry));

    property_text_t text = (property_text_t) {
        .content = textbox_entry->buffer,
        .region  = LOGIN_PASSWORD_TEXTBOX_REGION
    };

    property_cursor_t cursor = (property_cursor_t) {
        .bg = LOGIN_TEXTBOX_CURSOR_COLOR_BG,
        .fg = LOGIN_TEXTBOX_CURSOR_COLOR_FG
    };

    ztream_entity_add_property(&entity_login_password_textbox, property_text, &text);
    ztream_entity_add_property(&entity_login_password_textbox, property_cursor, &cursor);

    ztream_entity_check_trait(&entity_login_password_textbox, trait_entry_alpha);
}

static void action_login() {
    char* name = ((property_entry_t*)ztream_entity_get(&entity_login_username_textbox, property_entry))->buffer;
    char* pssw = ((property_entry_t*)ztream_entity_get(&entity_login_password_textbox, property_entry))->buffer;

    user_id = archive_login_user(name, pssw);
    if (user_id == -1) {
        return;
    }
    
    ztream_scene_erase(&scene_login);
    ztream_resize(GAME_PAGE_REGION.width, GAME_PAGE_REGION.height);

    load_user_info();
    landscopes_init_coord = user_info.coord;
    load_landscopes();

    ztream_scene_launch(&scene_game);
}

static void entity_init_login_button() {
    entity_login_button = ztream_entity();

    property_unicode_t text = (property_unicode_t) {
        .content = LOGIN_BUTTON_CONTENT,
        .region  = LOGIN_BUTTON_REGION
    };

    property_foreground_t fg = (property_foreground_t) {
        .color  = LOGIN_BUTTON_COLOR_FG,
        .region = LOGIN_BUTTON_REGION
    };

    property_background_t bg = (property_background_t) {
        .color  = LOGIN_BUTTON_COLOR_BG,
        .region = LOGIN_BUTTON_REGION
    };

    ztream_entity_add_property(&entity_login_button, property_unicode, &text);
    ztream_entity_add_property(&entity_login_button, property_foreground, &fg);
    ztream_entity_add_property(&entity_login_button, property_background, &bg);
    ztream_entity_add_property(&entity_login_button, property_button, &LOGIN_BUTTON_REGION);
    
    property_action_t action = action_login;
    ztream_entity_add_property(&entity_login_button, property_action, &action);

    ztream_entity_check_trait(&entity_login_button, trait_action_box);
}

#endif