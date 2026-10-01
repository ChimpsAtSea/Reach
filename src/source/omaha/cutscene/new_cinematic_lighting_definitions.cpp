/* ---------- headers */

#include "omaha\cutscene\new_cinematic_lighting_definitions.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\lights.h"
#include "omaha\objects\objects.h"
#include "omaha\tag_files\tag_groups.h"

#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_reference_definition global_light_definition_reference; // "?global_light_definition_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_new_cinematic_lighting_vtable; // "?legacy_new_cinematic_lighting_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_block_definition new_cinematic_lighting_block; // "?new_cinematic_lighting_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_new_cinematic_lighting_reference; // "?global_new_cinematic_lighting_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group new_cinematic_lighting_group; // "?new_cinematic_lighting_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_new_cinematic_lighting_stream_definition; // "?legacy_new_cinematic_lighting_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_new_cinematic_lighting_xsync_declaration; // "?legacy_new_cinematic_lighting_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_new_cinematic_lighting_vtable_shim; // "?legacy_new_cinematic_lighting_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_cinematic_lighting::initialize_on_new(void *);
// public: static bool s_cinematic_lighting::postprocess(long, bool);
// public: void s_cinematic_light_direction::get_direction(struct real_matrix4x3const *, union vector3d *, union vector3d *) const;
// public: long s_cinematic_dynamic_light::create(union real_point3d const *, struct real_matrix4x3const *, long, long);

bool s_cinematic_lighting::initialize_on_new(void * data)
{
    mangled_ppc("?initialize_on_new@s_cinematic_lighting@@SA_NPAX@Z");

    s_cinematic_lighting * lighting = static_cast<s_cinematic_lighting *>(data);
    lighting->sampled_vmf_light_weight = 1.0f;
    lighting->sampled_analytical_light_weight = 1.0f;
    lighting->vmf_light_scale = 1.0f;
    lighting->analytical_light_scale = 1.0f;

    return true;
};

bool s_cinematic_lighting::postprocess(long tag_index, bool for_editor)
{
    mangled_ppc("?postprocess@s_cinematic_lighting@@SA_NJ_N@Z");

    s_cinematic_lighting * cinematic_lighting = static_cast<s_cinematic_lighting *>(tag_get(_tag, tag_index));
    bool success = true;

    if (cinematic_lighting->vmf_light_scale == 0.0f &&
        cinematic_lighting->analytical_light_scale == 0.0f &&
        cinematic_lighting->ambient_scale == 0.0f &&
        cinematic_lighting->directional_scale == 0.0f &&
        cinematic_lighting->analytical_scale == 0.0f)
    {
        cinematic_lighting->analytical_scale = 1.0f;
        cinematic_lighting->directional_scale = 1.0f;
        cinematic_lighting->ambient_scale = 1.0f;
        cinematic_lighting->vmf_light_scale = 1.0f;
        cinematic_lighting->analytical_light_scale = 1.0f;
    }

    return success;
};

void s_cinematic_light_direction::get_direction(real_matrix4x3 const * camera_matrix, vector3d * light_forward, vector3d * light_up) const
{
    mangled_ppc("?get_direction@s_cinematic_light_direction@@QBAXPBUreal_matrix4x3@@PATvector3d@@1@Z");

    real direction_radians = screen_angle * k_degrees_to_radians;
    real front_back_radians = front_back_angle * k_degrees_to_radians;
    real sin_fb = sin(front_back_radians);

    vector3d light_to_subject_screenspace;
    light_to_subject_screenspace.k = -sin_fb * cos(direction_radians);
    light_to_subject_screenspace.j = sin_fb * sin(direction_radians);
    light_to_subject_screenspace.i = cos(front_back_radians);

    matrix3x3_transform_vector(&camera_matrix->matrix3x3, &light_to_subject_screenspace, light_forward);
    if (light_up)
    {
        *light_up = camera_matrix->up;
    }
};

long s_cinematic_dynamic_light::create(real_point3d const * subject_point, real_matrix4x3 const * camera_matrix, long object_index, long marker_id)
{
    mangled_ppc("?create@s_cinematic_dynamic_light@@QAAJPBTreal_point3d@@PBUreal_matrix4x3@@JJ@Z");

    long light_datum_index = NONE;
    if (light_definition.index == NONE)
    {
        goto function_end;
    }

    object_marker marker;
    bool valid_marker = object_index != NONE
        && marker_id != 0
        && object_try_and_get_and_verify_type(object_index, 0xFFFFFFFF) != NULL
        && object_get_markers_by_string_id(object_index, marker_id, &marker, 1) > 0;

    vector3d light_forward_world;
    real_point3d light_position_world;
    vector3d light_up_world;
    if (TEST_BIT(flags, _move_to_marker_bit) && valid_marker)
    {
        light_position_world = marker.matrix.position;
        light_forward_world = marker.matrix.forward;
        light_up_world = marker.matrix.up;
    }
    else
    {
        direction.get_direction(camera_matrix, &light_forward_world, &light_up_world);
        point_from_line3d(subject_point, &light_forward_world, -distance, &light_position_world);
    }

    vector3d light_left_world;
    real_vector3d_build_axes_from_vectors(&light_forward_world, &light_up_world, &light_forward_world, &light_left_world, &light_up_world);

    if (TEST_BIT(flags, _follow_object_bit))
    {
        long parent_node_index = 0;
        if (valid_marker)
        {
            parent_node_index = marker.node_index;
        }

        real_matrix4x3 const * node_world_matrix = object_get_node_matrix(object_index, static_cast<short>(parent_node_index));
        real_matrix4x3 inverse_matrix;
        matrix4x3_inverse(node_world_matrix, &inverse_matrix);
        real_point3d position_node_local;
        matrix4x3_transform_point(&inverse_matrix, &light_position_world, &position_node_local);
        vector3d forward_node_local;
        matrix4x3_transform_normal(&inverse_matrix, &light_forward_world, &forward_node_local);
        vector3d up_node_local;
        matrix4x3_transform_normal(&inverse_matrix, &light_up_world, &up_node_local);
        light_datum_index = light_new_unattached(light_definition.index, object_index, static_cast<short>(parent_node_index), &position_node_local, &forward_node_local, &up_node_local, 1.0f, 0, 0);
    }
    else
    {
        light_datum_index = light_new_unattached(light_definition.index, NONE, NONE, &light_position_world, &light_forward_world, &light_left_world, 1.0f, 0, 0);
    }

function_end:
    return light_datum_index;
};

