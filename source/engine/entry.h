#pragma once
#include "core/platform.h"
#include "core/application.h"
#include "logger.h"

#include <raylib.h>

b8 init_app(application_t *app_out);

int main(void) {
    application_t app = {};
    if (!init_app(&app)) {
        FATAL("failed to initialize application");
        return 1;
    }
    if (!app.init()) {
        FATAL("application failed to initialize");
        return 1;
    }
    InitWindow(app.default_width, app.default_height, app.name);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
#ifdef HOTRELOAD
        // need to wait a second before calling to reload the library
        // I guess this is to give the OS time to finish writing the lib file
        if (platform_watch_applib(&app)) {
            static f32 timer = 0;
            if (timer >= 1.0f) {
                platform_hot_reload(&app);
                timer = 0;
            }
            timer += GetFrameTime();
        }
#endif
        if (!app.update(&app)) {
            WARN("application is shutting down");
            break;
        }
    }
    if (!app.shutdown(&app)) {
        ERROR("application did not shut down gracefully");
        return 1;
    }
    CloseWindow();
    return 0;
}
