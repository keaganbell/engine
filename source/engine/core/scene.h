#pragma once
#include "defines.h"
#include "core/ui.h"

typedef struct app_state app_state_t;

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
    u64 sceneid;
    void *scene_data;
} scene_t;

void create_scene(scene_t *scene);
//void *push_struct(ELMT_ID id, const void *strct, u32 stride);
