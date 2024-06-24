typedef struct intro_scene {
    u32 id;
    const char *title;
} intro_scene_t;

static intro_scene_t *intro_scene;

b8 intro_init(app_state_t *game_state) {
    if (intro_scene != NULL) {
        ERROR("tried to allocate the intro scene twice");
        return false;
    }
    intro_scene = malloc(sizeof(intro_scene_t));
    memset(intro_scene, 0, sizeof(intro_scene_t));
    INFO("intro_scene allocated");
    intro_scene->id = INTRO;
    intro_scene->title = "intro";
    return true;
}

b8 intro_shutdown(app_state_t *game_state) {
    if (intro_scene == NULL) {
        ERROR("tried to free null intro_scene pointer");
        return false;
    }
    free(intro_scene);
    return true;
}

b8 intro_update(app_state_t *game_state) {
    // do some cool cinematic intro stuff
    // re-initialize the scene especially on dl reload
    if (intro_scene == NULL) {
        if (!intro_init(game_state)) {
            ERROR("failed to initialize the intro scene");
            return false;
        }
    }
    scene_transition(game_state, INTRO, MENU);
    return true;
}

b8 intro_render(app_state_t *game_state) {
    // do some cool cinematic intro stuff
    return true;
}
