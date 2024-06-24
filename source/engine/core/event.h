#pragma once
#include "defines.h"

typedef enum EVENT_CODE {
    BUTTON_PRESS_EVENT,
    BUTTON_RELEASE_EVENT,
    MOUSEOVER_EVENT,
    UNMOUSEOVER_EVENT,

    MAX_EVENT_CODE
} event_code_t;

typedef struct listener {
    event_code_t event_code;
    void (*callback)();
} listener_t;

typedef struct event {
    event_code_t event_code;
    listener_t *listeners; // darray
} event_t;

typedef struct event_system {
    b8 initialized;

} event_system_t;


// event_data can be 128 bits (16 bytes)
// enough for a vec4 or 2 pointers
typedef struct event_context {
    union {
        u64 u64[2];
        i64 i64[2];
        f64 f64[2];

        u32 u32[4];
        i32 i32[4];
        f32 b32[4];

        b8  b8[16];
        i8  i8[16];
        u8  u8[16];
        char c[16];
    } data;
} event_context_t;

b8 register_event(event_code_t event_code, listener_t *listener);
b8 unregister_event(listener_t *listener);
b8 fire_event(event_code_t event_code, event_context_t context);
