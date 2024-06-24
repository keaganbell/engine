#include "logger.h"
#include "core/application.h"
#include "core/scene.h"
#include "core/ui.h"

#include "containers/darray.h"

#include <stdlib.h>
#include <string.h>

static app_state_t *game_state_g;

// this variable gets set to 0 when the game library gets reloaded
// this global variable acts as a signal for the application to 
// validate its newly allocated data
static b8 hasnt_reloaded;
b8 on_reload() {
    return true;
}

typedef enum sceneid {
    INTRO_SCENE,
    MENU_SCENE,
    PLAY_SCENE
} sceneid_t;

b8 game_init() {
    hasnt_reloaded = true;
    game_state = malloc(sizeof(app_state_t));
    game_state->scenes[INTRO_SCENE].sceneid = INTRO_SCENE;
    game_state->scenes[MENU_SCENE].sceneid = MENU_SCENE;
    game_state->scenes[PLAY_SCENE].sceneid = MENU_SCENE;
    return true;
}

b8 game_update() {
    if (!game_state) {
    }
    b8 result = true;
    // update input
    // advance the game state
    // update coroutines

    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawFPS(10, 10);
    DrawText("Testbed", GetScreenWidth()/2 - 120, GetScreenHeight()/2 - 100, 64, LIGHTGRAY);
    EndDrawing();
    return result;
}

b8 game_shutdown() {
    return true;
}
