#pragma once
#include "defines.h"
#include "core/event.h"

#include <raylib.h>

typedef struct uiid {
    u64 id;
    u64 up;
    u64 down;
    u64 left;
    u64 right;
} uiid_t;

typedef struct ui_context {
    uiid_t active;
    uiid_t hot;
} ui_context_t;

typedef struct button {
    // data for button state ////////////////////////////
    b8 hot;
    uiid_t uiid;
    Rectangle rect;
    b8 (*on_press)();
    b8 (*on_release)();

    // data for rendering ///////////////////////////////
    char *text;
    Color color;
} button_t;

b8 button(ui_context_t *ui, button_t *button);
