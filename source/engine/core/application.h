#pragma once
#include "defines.h"
#include "core/platform.h"
#include "core/scene.h"
#include "core/ui.h"

#include <raylib.h>

typedef struct app_state {
    sceneid_t sceneid;
    scene_t *scenes; // darray
} app_state_t;

typedef struct application {
    const char *name;
    u32 default_width;
    u32 default_height;
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
