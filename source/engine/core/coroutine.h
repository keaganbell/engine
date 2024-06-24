#pragma once

typedef enum coroutine_id {
    MAX_COROUTINES
} coroutine_id_t;

typedef struct coroutine {
    coroutine_id_t id;
} coroutine_t;
