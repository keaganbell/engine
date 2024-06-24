#include "defines.h"
#include "logger.h"
#include "core/ui.h"
#include "core/application.h"

#if 0
// event-based "retained" mode
static inline b8 button_hover(ui_context_t *ui, button_t *button) {
    if (!button->hot) {
        button->hot = true;
        ui->keyboard_mode = false;
        event_context_t context = {};
        context.data = {(u64)ui, (u64)button};
        fire_event(MOUSEOVER_EVENT, data);
    }
    return (GetMouseX() >= button->rect.x &&
            GetMouseX() <= button->rect.x + button->rect.width &&
            GetMouseY() >= button->rect.y &&
            GetMouseY() <= button->rect.y + button->rect.height);
}

static inline b8 pressed() {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
        || IsKeyPressed(KEY_SPACE)
        || IsKeyPressed(KEY_ENTER)
        || IsKeyPressed(KEY_KP_ENTER);
}

static inline b8 released() {
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON)
        || IsKeyReleased(KEY_SPACE)
        || IsKeyReleased(KEY_ENTER)
        || IsKeyReleased(KEY_KP_ENTER);
}

void ui_update(app_state_t *app_state) {
    event_context_t context = {};
    context.data = {(u64)ui, (u64)button};
    if (button_hover(button) || (ui->keyboard_mode && ui->hot.id != 0)) {
        if (pressed()) {
            fire_event(BUTTON_PRESS_EVENT, context); 
        }
        else if (released()) {
            fire_event(BUTTON_RELEASE_EVENT, context); 
        }
    }
    else {
        if (button->hot) {
            button->hot = false;
            fire_event(UNMOUSEOVER_EVENT, context);
        }
    }
}
#else
static inline b8 button_hover(button_t *button) {
    return (GetMouseX() >= button->rect.x &&
            GetMouseX() <= button->rect.x + button->rect.width &&
            GetMouseY() >= button->rect.y &&
            GetMouseY() <= button->rect.y + button->rect.height);
}

static inline b8 button_pressed() {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
        || IsKeyPressed(KEY_SPACE)
        || IsKeyPressed(KEY_ENTER)
        || IsKeyPressed(KEY_KP_ENTER);
}

static inline b8 button_released() {
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON)
        || IsKeyReleased(KEY_SPACE)
        || IsKeyReleased(KEY_ENTER)
        || IsKeyReleased(KEY_KP_ENTER);
}

// old immediate mode
b8 button(ui_context_t *ui, button_t *button) {
    b8 result = false;
    // check if button is active ///////////////////////////////////////
    if (ui->active.id == button->uiid.id) {
        if (button_released()) {
            if (ui->hot.id == button->uiid.id) {
                INFO("button %lld was clicked!", button->uiid.id);
                result = true;
            }
            ui->active.id = 0;
        }
        button->color = GREEN;
    }
    // check if button is hot //////////////////////////////////////////
    else if (ui->hot.id == button->uiid.id) {
        if (button_pressed()) {
            TRACE("button %lld is active!", button->uiid.id);
            ui->active.id = button->uiid.id;
        }
        button->color = RAYWHITE;
    }
    // set the hot button ///////////////////////////////////////////////
    if (button_hover(button)) {
        ui->hot.id = button->uiid.id;
        if (!button->hot) {
            button->hot = true;
        }
    }
    else {
        if (button->hot) {
            ui->hot.id = 0;
            button->hot = false;
        }
    }
    return result;
}
#endif
