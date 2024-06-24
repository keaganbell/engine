#include "entry.h"

#include <stdlib.h>
#include <string.h>

// TODO: evaluate the problems and affectiveness with this
// truely global variable
static app_state_t *state_g;
app_state_t *game_state() {
    return state_g;
}


b8 init_app(application_t *app_out) {
    ////////////////////////////////////////////////////////////////////////
    // create the application window
    app_out->name = "testbed";
    app_out->default_width = 800;
    app_out->default_height = 600;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    ////////////////////////////////////////////////////////////////////////
    // create and load the game library
    // NOTE: could abstract out the lib functions and put them in a darray
    app_out->applib = (dynamic_library_t){
        "build/libgame.so", // filename
        NULL,               // pointer to dynamic library
        0,                  // last write time (auto hot reload)
    };
    if (!platform_load_library(app_out)) {
        FATAL("failed to load the application dynamic library");
        return false;
    }
    return true;
}
