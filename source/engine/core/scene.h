#pragma once
#include "defines.h"
#include "core/ui.h"

typedef struct app_state app_state_t;

typedef enum sceneid {
    INTRO,
    MENU,
    PLAY,

    MAX_SCENES
} sceneid_t;

typedef struct header {
    u32 length;
    u32 stride;
    u32 capacity;
} header_t;

typedef struct data_frame {
    header_t header;
    u64 head;
    u64 tail;
} data_frame_t;

typedef struct scene {
    sceneid_t sceneid;

    void *scene_data;

    b8 (*init)(app_state_t *app_state);
    b8 (*update)(app_state_t *app_state);
    b8 (*render)(app_state_t *app_state);
    b8 (*shutdown)(app_state_t *app_state);
} scene_t;

void create_scene(scene_t *scene);
//void *push_struct(ELMT_ID id, const void *strct, u32 stride);
scene_t *get_scene(app_state_t *app_state, sceneid_t id);
void scene_transition(app_state_t *app_state, sceneid_t scene_from, sceneid_t scene_to);
