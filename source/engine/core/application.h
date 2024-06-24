#pragma once
#include "defines.h"
#include "core/platform.h"
#include "core/scene.h"
#include "core/ui.h"

#include <raylib.h>

// NOTE: trying to keep memory local but can remove this
// and make the scene table a dynamic array instead
#define MAX_SCENES 5

typedef struct app_state {
    u64 current_sceneid;
    scene_t scenes[MAX_SCENES]; // darray
} app_state_t;

typedef struct application {
    const char *name;
    u32 default_width;
    u32 default_height;
    dynamic_library_t applib;

    b8 (*init)();
    b8 (*update)();
    b8 (*shutdown)();
} application_t;
