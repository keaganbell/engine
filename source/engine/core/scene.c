#include "logger.h"
#include "core/scene.h"
#include "core/application.h"
#include "containers/darray.h"

#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////
// 
//                               header
//
//---------------------------------------------------------------------
//
// [  ui ] 
//      canvas
//          panes
//          buttons
//
// [ pfn ]
//      get_canvas
//
// [ entities ]
//
//
//
//
//
//
//
//---------------------------------------------------------------------
//                              overflow
///////////////////////////////////////////////////////////////////////
void create_scene(scene_t *scene_out) {
    u64 memory_requirement = 32000;
    void *scene_data = malloc(memory_requirement);
    memset(scene_data, 0, memory_requirement);

    scene_out->scene_data = scene_data;
}

scene_t *get_scene(app_state_t *app_state, sceneid_t id) {
    return (scene_t *)darray_get(app_state->scenes, id);
}

void scene_transition(app_state_t *app_state, sceneid_t scene_from, sceneid_t scene_to) {
    get_scene(app_state, scene_from)->shutdown(app_state);
    app_state->sceneid = scene_to;
    get_scene(app_state, scene_to)->init(app_state);
}
