#pragma once
#include "defines.h"
#include "core/platform.h"
#include "core/coroutine.h"
#include "core/scene.h"
#include "core/ui.h"

#include <raylib.h>

typedef struct window {
    b8 fullscreen;
    Vector2 min_size;
    u32 flags;
} window_t;

typedef struct app_state {
    // make these dynamic later
    coroutine_t coroutines[MAX_COROUTINES];
    scene_t *scenes; // darray
    sceneid_t sceneid;

    // test darray
    Rectangle *rects;
} app_state_t;

typedef struct application {
    char *name;
    window_t window;
    dynamic_library_t applib;

    app_state_t *state;

    b8 (*init)(struct application *app);
    b8 (*update)(struct application *app);
    b8 (*render)(struct application *app);
    b8 (*shutdown)(struct application *app);
} application_t;

static inline scene_t *current_scene(app_state_t *app_state) {
    return get_scene(app_state, app_state->sceneid);
}
