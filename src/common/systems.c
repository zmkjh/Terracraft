// copyright. wwd 2510801129 2025/11/27 - --
#ifndef COMMON_SYSTEMS_C
#define COMMON_SYSTEMS_C

#include "systems.h"
#include "systems/listener.h"
#include "systems/bg_painter.h"
#include "systems/fg_painter.h"
#include "systems/text_painter.h"
#include "systems/unicode_painter.h"
#include "systems/entry_listener.h"
#include "systems/button_listener.h"
#include "systems/cursor_painter.h"
#include "systems/entry_alpha_listener.h"
#include "systems/action_box_listener.h"

void systems_init_common() {
    system_init_listener();
    system_init_bg_painter();
    system_init_fg_painter();
    system_init_text_painter();
    system_init_unicode_painter();
    system_init_entry_listener();
    system_init_button_listener();
    system_init_cursor_painter();
    system_init_entry_alpha_listener();
    system_init_action_box_listener();

    system_dependency_text_painter();
    system_dependency_cursor_painter();
    system_dependency_entry_alpha_listener();
    system_dependency_action_box_listener();
}

#endif