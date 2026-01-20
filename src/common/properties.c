// copyright. wwd 2510801129 2025/11/27 - --
#ifndef COMMON_PROPERTIES_C
#define COMMON_PROPERTIES_C

#include "properties.h"
#include "properties/listener.h"
#include "properties/background.h"
#include "properties/foreground.h"
#include "properties/entry.h"
#include "properties/button.h"
#include "properties/text.h"
#include "properties/unicode.h"
#include "properties/cursor.h"
#include "properties/action.h"

void properties_init_common() {
    property_init_listener();
    property_init_background();
    property_init_foreground();
    property_init_entry();
    property_init_button();
    property_init_text();
    property_init_unicode();
    property_init_cursor();
    property_init_action();
}

#endif