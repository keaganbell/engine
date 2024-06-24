typedef struct play_scene {
    u32 id;
    const char *title;
    ui_context_t ui_context;
} play_scene_t;

static play_scene_t *play_scene;

b8 play_init(app_state_t *game_state) {
    if (play_scene != NULL) {
        ERROR("tried to allocate the play scene twice");
        return false;
    }
    play_scene = malloc(sizeof(play_scene_t));
    memset(play_scene, 0, sizeof(play_scene_t));
    INFO("play_scene allocated");
    play_scene->id = PLAY;
    play_scene->title = "Game On!";
    return true;
}

b8 play_shutdown(app_state_t *game_state) {
    if (play_scene == NULL) {
        ERROR("tried to free null play_scene pointer");
        return false;
    }
    free(play_scene);
    return true;
}

b8 play_update(app_state_t *game_state) {
    return true;
}

b8 play_render(app_state_t *game_state) {
    return true;
}
