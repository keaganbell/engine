#include "containers/darray.h"
#include "entry.h"

#include <stdlib.h>
#include <string.h>

static app_state_t *state;

b8 init_app(application_t *app_out) {
    ////////////////////////////////////////////////////////////////////////
    // create the application window
    app_out->name = "testbed";
    app_out->default_width = 800;
    app_out->default_height = 600;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    ////////////////////////////////////////////////////////////////////////
    // allocate the state
    state = malloc(sizeof(app_state_t));
    app_out->state = state;
    memset(app_out->state, 0, sizeof(app_state_t));
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
    ////////////////////////////////////////////////////////////////////////
    // allocate the scene stack
    create_darray(state->scenes);
    scene_t intro = {};
    intro.sceneid = INTRO;
    darray_push(state->scenes, intro);

    scene_t menu = {};
    menu.sceneid = MENU;
    darray_push(state->scenes, menu);

    scene_t play = {};
    play.sceneid = PLAY;
    darray_push(state->scenes, play);
    return true;
}
