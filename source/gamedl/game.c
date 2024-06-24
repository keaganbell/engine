#include "logger.h"
#include "core/application.h"
#include "core/scene.h"
#include "core/ui.h"

#include "containers/darray.h"

#include <stdlib.h>
#include <string.h>

// this static pointer goes null on reload
// if this is null, I can reallocate scene data and validate the function pointers
#include "gamedl/intro.inl"
#include "gamedl/menu.inl"
#include "gamedl/play.inl"

// this variable gets set to 0 when the game library gets reloaded
// this global variable acts as a signal to validate the library data
static b8 hasnt_reloaded;
b8 on_reload(app_state_t *game_state) {
    get_scene(game_state, INTRO)->init = &intro_init;
    get_scene(game_state, INTRO)->update = &intro_update;
    get_scene(game_state, INTRO)->render = &intro_render;
    get_scene(game_state, INTRO)->shutdown = &intro_shutdown;

    get_scene(game_state, MENU)->init = &menu_init;
    get_scene(game_state, MENU)->update = &menu_update;
    get_scene(game_state, MENU)->render = &menu_render;
    get_scene(game_state, MENU)->shutdown = &menu_shutdown;

    get_scene(game_state, PLAY)->init = &play_init;
    get_scene(game_state, PLAY)->update = &play_update;
    get_scene(game_state, PLAY)->render = &play_render;
    get_scene(game_state, PLAY)->shutdown = &play_shutdown;
    return true;
}

b8 game_init(application_t *game) {
    create_darray(game->state->rects);
    hasnt_reloaded = true;
    on_reload(game->state);
    intro_init(game->state);
    return true;
}

b8 game_update(application_t *game) {
    b8 result = true;
    // update input
    // advance the game state
    app_state_t *game_state = game->state;
    if (!current_scene(game_state)->update(game_state)) {
        INFO("game is no longer updating");
        result = false;
    }
    if (!hasnt_reloaded) {
        hasnt_reloaded = true;
        on_reload(game->state);
    }
    // update coroutines
    return result;
}

b8 game_render(application_t *game) {
    // can setup a pipeline?
    b8 result = true;
    app_state_t *game_state = game->state;
    if (!current_scene(game_state)->render(game_state)) {
        result = false;
    }
    // added shader effects?
    // bloom etc
    return result;
}

b8 game_shutdown(app_state_t *game) {
    return true;
}
