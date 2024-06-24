#include "core/platform.h"

#ifdef PLATFORM_LINUX

#include "logger.h"
#include "core/application.h"
#include "core/coroutine.h"

#include <sys/stat.h>
#include <dlfcn.h>
#include <errno.h>
extern int errno;

static inline u32 last_write_time(application_t *app) {
    struct stat buffer = {};
    stat(app->applib.name, &buffer);
    return buffer.st_mtim.tv_sec;
}

b8 platform_watch_applib(application_t *app) {
    if (!app->applib.lib_ptr) {
        ERROR("application library pointer is null");
        return false;
    }
    if (app->applib.last_write_time - last_write_time(app) != 0) {
//        INFO("aplication library was modified");
        return true;
    }
    return false;
}

b8 platform_load_library(application_t *app) {
    app->applib.lib_ptr = dlopen(app->applib.name, RTLD_NOW);
    if (!app->applib.lib_ptr) {
        ERROR("%s", dlerror());
        return false;
    }
    app->init = dlsym(app->applib.lib_ptr, "game_init");
    app->update = dlsym(app->applib.lib_ptr, "game_update");
    app->render = dlsym(app->applib.lib_ptr, "game_render");
    app->shutdown = dlsym(app->applib.lib_ptr, "game_shutdown");
    if (!app->init) {
        FATAL("couldn't find symbol init");
        return false;
    }
    if (!app->update) {
        FATAL("couldn't find symbol update");
        return false;
    }
    if (!app->render) {
        FATAL("couldn't find symbol render");
        return false;
    }
    if (!app->shutdown) {
        FATAL("couldn't find symbol shutdown");
        return false;
    }
    app->applib.last_write_time = last_write_time(app);
    INFO("game library was successfully loaded");
    return true;
}

b8 platform_hot_reload(application_t *app) {
    if (app->applib.lib_ptr == NULL) {
        ERROR("pointer to application library was null");
        return false;
    }
    if (dlclose(app->applib.lib_ptr)) {
        ERROR("failed to unload game library");
        return false;
    } 
    app->applib.lib_ptr = NULL;
    app->init = NULL;
    app->update = NULL;
    app->render = NULL;
    app->shutdown = NULL;
    platform_load_library(app);
    return true;
}


#endif // PLATFORM_LINUX
