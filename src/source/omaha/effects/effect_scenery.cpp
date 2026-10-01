/* ---------- headers */

#include "omaha\effects\effect_scenery.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool g_debug_objects_effect_scenery = false;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool g_debug_objects_effect_scenery; // "?g_debug_objects_effect_scenery@@3_NA"

// void effect_scenery_initialize_for_new_structure_bsp(long);
// void effect_scenery_place(long, struct s_scenario_effect_scenery *);
// bool effect_scenery_new(long, struct s_object_placement_data *, bool *);
// void effect_scenery_delete(long);
// bool effect_scenery_update(long);
// void effect_scenery_preprocess_root_node_matrix(long, struct real_matrix4x3*);
// void effect_scenery_render_debug(long);

void effect_scenery_initialize_for_new_structure_bsp(long structure_bsp_index)
{
    mangled_ppc("?effect_scenery_initialize_for_new_structure_bsp@@YAXJ@Z");
};

void effect_scenery_place(long effect_scenery_index, s_scenario_effect_scenery * scenario_effect_scenery)
{
    mangled_ppc("?effect_scenery_place@@YAXJPAUs_scenario_effect_scenery@@@Z");
};

bool effect_scenery_new(long effect_scenery_index, s_object_placement_data * placement_data, bool * out_of_memory)
{
    mangled_ppc("?effect_scenery_new@@YA_NJPAUs_object_placement_data@@PA_N@Z");

    return true;
};

void effect_scenery_delete(long effect_scenery_index)
{
    mangled_ppc("?effect_scenery_delete@@YAXJ@Z");
};

bool effect_scenery_update(long effect_scenery_index)
{
    mangled_ppc("?effect_scenery_update@@YA_NJ@Z");

    return true;
};

void effect_scenery_preprocess_root_node_matrix(long effect_scenery_index, real_matrix4x3 * matrix)
{
    mangled_ppc("?effect_scenery_preprocess_root_node_matrix@@YAXJPAUreal_matrix4x3@@@Z");
};

void effect_scenery_render_debug(long effect_scenery_index)
{
    mangled_ppc("?effect_scenery_render_debug@@YAXJ@Z");
};

