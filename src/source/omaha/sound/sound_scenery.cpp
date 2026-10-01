#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_scenery.cpp"
/* ---------- headers */

#include "omaha\sound\sound_scenery.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cseries\location.h"
#include "omaha\game\game.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_types.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_manager.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool sound_scenery_new(long, struct s_object_placement_data *, bool *);
// void sound_scenery_place(long, struct s_scenario_sound_scenery const *);
// void sound_scenery_render_debug(long);
// void sound_scenery_render_debug_direct(long);
// float sound_scenery_compute_bounding_sphere_radius(long);
// bool sound_scenery_compute_activation(long, struct s_game_cluster_bit_vectors const *, bool *);

bool sound_scenery_new(long object_index, s_object_placement_data * data, bool * out_of_memory)
{
    mangled_ppc("?sound_scenery_new@@YA_NJPAUs_object_placement_data@@PA_N@Z");

    return true;
};

void sound_scenery_place(long object_index, s_scenario_sound_scenery const * scenario_sound_scenery)
{
    mangled_ppc("?sound_scenery_place@@YAXJPBUs_scenario_sound_scenery@@@Z");

    sound_scenery_datum * sound_scenery = static_cast<sound_scenery_datum *>(object_get_and_verify_type(object_index, _object_mask_sound_scenery));
    sound_scenery->sound_scenery.volume_type = scenario_sound_scenery->sound_scenery.volume_type;
    sound_scenery->sound_scenery.height = scenario_sound_scenery->sound_scenery.height;
    sound_scenery->sound_scenery.override_distance_parameters = scenario_sound_scenery->sound_scenery.override_distance_parameters;
    sound_scenery->sound_scenery.override_cone_angle_bounds.lower = scenario_sound_scenery->sound_scenery.override_cone_angle_bounds.lower;
    sound_scenery->sound_scenery.override_cone_angle_bounds.upper = scenario_sound_scenery->sound_scenery.override_cone_angle_bounds.upper;
    sound_scenery->sound_scenery.override_outer_cone_gain_db = scenario_sound_scenery->sound_scenery.override_outer_cone_gain_db;
};

void sound_scenery_render_debug(long sound_scenery_index)
{
    mangled_ppc("?sound_scenery_render_debug@@YAXJ@Z");

    if (debug_objects_sound_spheres)
    {
        sound_scenery_render_debug_direct(sound_scenery_index);
    }
};

void sound_scenery_render_debug_direct(long sound_scenery_index)
{
    mangled_ppc("?sound_scenery_render_debug_direct@@YAXJ@Z");

    sound_scenery_datum const * sound_scenery = static_cast<sound_scenery_datum const *>(object_get_and_verify_type(sound_scenery_index, _object_mask_sound_scenery));
    s_sound_scenery_definition const * sound_scenery_definition = static_cast<s_sound_scenery_definition const *>(tag_get(SOUND_SCENERY_TAG, sound_scenery->definition_index));

    float minimum_distance = sound_scenery->sound_scenery.override_distance_parameters.minimum_distance > 0.0f ? sound_scenery->sound_scenery.override_distance_parameters.minimum_distance : sound_scenery_definition->scenery.runtime_minimum_distance;
    float maximum_distance = sound_scenery->sound_scenery.override_distance_parameters.maximum_distance > 0.0f ? sound_scenery->sound_scenery.override_distance_parameters.maximum_distance : sound_scenery_definition->scenery.runtime_maximum_distance;
    float inner_cone_angle = sound_scenery->sound_scenery.override_cone_angle_bounds.lower > 0.0f ? sound_scenery->sound_scenery.override_cone_angle_bounds.lower : sound_scenery_definition->scenery.runtime_inner_cone_angle;
    float outer_cone_angle = sound_scenery->sound_scenery.override_cone_angle_bounds.upper > 0.0f ? sound_scenery->sound_scenery.override_cone_angle_bounds.upper : sound_scenery_definition->scenery.runtime_outer_cone_angle;

    real_point3d sound_point;
    object_get_origin(sound_scenery_index, &sound_point);
    vector3d forward;
    vector3d up;
    object_get_orientation(sound_scenery_index, &forward, &up);
    real_matrix4x3 transform;
    matrix4x3_rotation_from_vectors(&transform, &forward, &up);
    real32_quaternion orientation;
    matrix4x3_rotation_to_quaternion(&transform, &orientation);

    render_debug_sound_at_point(sound_scenery->sound_scenery.volume_type, &sound_point, &orientation, sound_scenery->sound_scenery.height, minimum_distance, maximum_distance, inner_cone_angle, outer_cone_angle, NULL, NULL);
};

float sound_scenery_compute_bounding_sphere_radius(long sound_scenery_index)
{
    mangled_ppc("?sound_scenery_compute_bounding_sphere_radius@@YAMJ@Z");

    float radius = 0.0f;
    if (sound_scenery_index != NONE)
    {
        sound_scenery_datum const * sound_scenery = static_cast<sound_scenery_datum const *>(object_get_and_verify_type(sound_scenery_index, _object_mask_sound_scenery));
        if (sound_scenery->definition_index != NONE)
        {
            s_sound_scenery_definition const * sound_scenery_definition = static_cast<s_sound_scenery_definition const *>(tag_get(SOUND_SCENERY_TAG, sound_scenery->definition_index));
            float maximum_distance = sound_scenery->sound_scenery.override_distance_parameters.maximum_distance > 0.0f ? sound_scenery->sound_scenery.override_distance_parameters.maximum_distance : sound_scenery_definition->scenery.runtime_maximum_distance;
            radius = maximum_distance * sound_scenery->object.scale;
        }
    }

    return radius;
};

bool sound_scenery_compute_activation(long sound_scenery_index, s_game_cluster_bit_vectors const * cluster_activation, bool * out_active)
{
    mangled_ppc("?sound_scenery_compute_activation@@YA_NJPBUs_game_cluster_bit_vectors@@PA_N@Z");

    object_cluster_iterator iterator;

    assert_tag_debug_untracked_jul_11_2011(127, out_active);
    assert_tag_debug_untracked_jul_11_2011(128, cluster_activation);

    bool custom_activation = false;
    for (s_cluster_reference cluster_reference = object_get_first_cluster(&iterator, sound_scenery_index);
        cluster_reference_valid(cluster_reference);
        cluster_reference = object_get_next_cluster(&iterator, sound_scenery_index))
    {
        if (cluster_activation->bit_vectors.element(cluster_reference.bsp_index).test(cluster_reference.cluster_index))
        {
            *out_active = true;
            custom_activation = true;
            break;
        }
    }

    return custom_activation;
};
