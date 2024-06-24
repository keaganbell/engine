#pragma once
#include "engine/defines.h"

typedef struct dynamic_library {
    const char *name;
    void *lib_ptr;
    u32 last_write_time;
} dynamic_library_t;


typedef struct application application_t;

b8 platform_watch_applib(application_t *app);
b8 platform_load_library(application_t *app);
b8 platform_hot_reload(application_t *app);
