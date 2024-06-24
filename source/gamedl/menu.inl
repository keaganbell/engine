#define STARTBUTTON 1
#define QUITBUTTON 2

typedef struct menu_scene {
    u32 id;
    const char *title;
    ui_context_t ui_context;
    button_t start_button;
    button_t quit_button;
} menu_scene_t;

static menu_scene_t *menu_scene;

b8 menu_init(app_state_t *game_state) {
    if (menu_scene != NULL) {
        ERROR("tried to allocate the menu scene twice");
        return false;
    }
    menu_scene = malloc(sizeof(menu_scene_t));
    memset(menu_scene, 0, sizeof(menu_scene_t));
    INFO("menu_scene allocated");
    menu_scene->id = MENU;
    menu_scene->title = "Main Menu";
    return true;
}

b8 menu_shutdown(app_state_t *game_state) {
    if (menu_scene == NULL) {
        ERROR("tried to free null menu_scene pointer");
        return false;
    }
    free(menu_scene);
    return true;
}

b8 menu_update(app_state_t *game_state) {
    if (menu_scene == NULL) {
        if (!menu_init(game_state)) {
            ERROR("failed to initialize the menu scene");
        }
    }

    menu_scene->start_button.uiid.id = STARTBUTTON;
    menu_scene->start_button.rect = (Rectangle){GetScreenWidth()/2, GetScreenHeight()/2, 100, 35},
    menu_scene->start_button.text = "Start Button";
    menu_scene->start_button.color = LIGHTGRAY;
    if (button(&menu_scene->ui_context, &menu_scene->start_button)) {
        DEBUG("starting the game!!!!!!!!!!");
    }

    menu_scene->quit_button.uiid.id = QUITBUTTON;
    menu_scene->quit_button.rect = (Rectangle){GetScreenWidth()/2, GetScreenHeight()/2 + 50, 100, 35},
    menu_scene->quit_button.text = "Quit Button";
    menu_scene->quit_button.color = LIGHTGRAY;
    if (button(&menu_scene->ui_context, &menu_scene->quit_button)) {
        DEBUG("quit button clicked!!!!!!!!!!!!!");
        return false;
    }
    return true;
}

b8 menu_render(app_state_t *game_state) {
    BeginDrawing();
    DrawFPS(10, 10);
    ClearBackground(DARKGRAY);
    // render screen based on game state
    DrawText(menu_scene->title, 200, 150, 48, LIGHTGRAY);

    // draw the buttons /////////////////////////////////////////////////
    DrawRectangleRec(menu_scene->start_button.rect, 
            menu_scene->start_button.color);
    DrawText(menu_scene->start_button.text,
            menu_scene->start_button.rect.x + 13, 
            menu_scene->start_button.rect.y + 6, 14,
            BLACK);

    DrawRectangleRec(menu_scene->quit_button.rect, 
            menu_scene->quit_button.color);
    DrawText(menu_scene->quit_button.text,
            menu_scene->quit_button.rect.x + 13, 
            menu_scene->quit_button.rect.y + 6, 14,
            BLACK);
    EndDrawing();
    return true;
}
