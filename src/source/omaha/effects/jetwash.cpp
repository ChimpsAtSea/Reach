#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\jetwash.cpp"
/* ---------- headers */

#include "omaha\effects\jetwash.h"
#include "omaha\effects\particle_system.h"
#include "omaha\effects\particle_emitter.h"
#include "omaha\effects\particle_system_definitions.h"
#include "omaha\effects\effects.h"
#include "omaha\effects\effect_definitions.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_definitions.h"
#include "omaha\physics\collisions.h"
#include "omaha\render\render_debug.h"
#include "omaha\math\color_math.h"
#include "omaha\math\matrix_math.h"
#include "omaha\profiler\profiler.h"
#include "omaha\tag_files\tag_groups.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_jetwash_pulse_state
{
    bool valid; // 0x0
    s_jetwash_definition definition; // 0x4
};
static_assert(sizeof(s_jetwash_pulse_state) == 0x28, "s_jetwash_pulse_state");

struct s_jetwash_particle_state
{
    bool valid; // 0x0
    float distance_fraction; // 0x4
    float random_fraction; // 0x8
    real_point3d position; // 0xC
    vector3d normal; // 0x18 collision plane normal
    vector3d velocity; // 0x24
};
static_assert(sizeof(s_jetwash_particle_state) == 0x30, "s_jetwash_particle_state");

/* ---------- prototypes */

/* ---------- globals */

static s_jetwash_pulse_state g_jetwash_pulse_state;
static s_jetwash_particle_state g_jetwash_particle_state;
bool debug_objects_jetwash;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition jetwash_definition_block_struct_definition; // "?jetwash_definition_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition jetwash_definition_block; // "?jetwash_definition_block@@3Us_tag_block_definition@@A"
// bool debug_objects_jetwash; // "?debug_objects_jetwash@@3_NA"

// bool jetwash_emitter_should_pulse(class c_particle_emitter const *, class c_particle_system const *, class c_particle_emitter_definition const *, class c_particle_system_definition const *);
// public: long c_particle_system::get_object_index(void) const;
// bool jetwash_prepare_for_particle_spawn(class c_particle_emitter const *, class c_particle_system const *, class c_particle_emitter_definition const *);
// void jetwash_get_particle_simulation_values(float *);
// bool jetwash_compute_particle_position_and_velocity(long, float, union real_point3d *, union vector3d *);

// $TODO nonmatching (only diff: TLS offset of effect_data, target li r10, 0x1bc)
bool jetwash_emitter_should_pulse(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_definition, c_particle_system_definition const * system_definition)
{
    mangled_ppc("?jetwash_emitter_should_pulse@@YA_NPBVc_particle_emitter@@PBVc_particle_system@@PBVc_particle_emitter_definition@@PBVc_particle_system_definition@@@Z");

    PROFILER_SCOPE_BEGIN(54, jetwash_pulse, profile_instance);

    long object_index = system->get_object_index();
    long effect_index = system->get_effect_index();
    object_datum const * object = static_cast<object_datum const *>(object_try_and_get_and_verify_type(object_index, NONE));
    g_jetwash_pulse_state.valid = false;
    if (effect_index != NONE && object != NULL)
    {
        effect_datum const * effect = static_cast<effect_datum const *>(datum_get(effect_data, effect_index));
        effect_definition const * definition = static_cast<effect_definition const *>(tag_get(EFFECT_DEFINITION_TAG, effect->definition_index));
        long location_index = system_definition->get_location_index();
        if (location_index != NONE)
        {
            _object_definition const * object_definition = static_cast<_object_definition const *>(tag_get(OBJECT_TAG, object->definition_index));
            effect_location_definition const * location = static_cast<effect_location_definition const *>(tag_block_get_element_with_size(&definition->locations, system_definition->get_location_index(), sizeof(effect_location_definition)));
            long jetwash_definition_index = NONE;
            for (long index = 0; index < object_definition->jetwash.count; index++)
            {
                s_jetwash_definition const * jetwash = static_cast<s_jetwash_definition const *>(tag_block_get_element_with_size(&object_definition->jetwash, index, sizeof(s_jetwash_definition)));
                if (jetwash->marker_name == location->marker_name)
                {
                    jetwash_definition_index = index;
                    break;
                }
            }
            if (jetwash_definition_index != NONE)
            {
                s_jetwash_definition const * jetwash_definition = static_cast<s_jetwash_definition const *>(tag_block_get_element_with_size(&object_definition->jetwash, jetwash_definition_index, sizeof(s_jetwash_definition)));
                collision_result collision;
                real_matrix4x3 emitter_matrix = *emitter->get_matrix();
                vector3d collision_vector;
                scale_vector3d(&emitter_matrix.forward, jetwash_definition->maximum_emission_length, &collision_vector);
                collision_test_vector(_collision_test_for_line_of_sight_obstruction_flags, &emitter_matrix.position, &collision_vector, object_index, NONE, &collision);
                g_jetwash_pulse_state.valid = collision.t < 1.0f;
                g_jetwash_pulse_state.definition = *jetwash_definition;
                if (debug_objects_jetwash)
                {
                    argb_color debug_color = collision.t < 1.0f ? *global_real_argb_red : *global_real_argb_yellow;
                    render_debug_vector(true, &emitter_matrix.position, &emitter_matrix.forward, jetwash_definition->maximum_emission_length, &debug_color);
                }
            }
        }
    }

    profile_instance.end();
    return g_jetwash_pulse_state.valid;
};

bool jetwash_prepare_for_particle_spawn(c_particle_emitter const * emitter, c_particle_system const * system, c_particle_emitter_definition const * emitter_definition)
{
    mangled_ppc("?jetwash_prepare_for_particle_spawnYA_NPBVc_particle_emitterPBVc_particle_systemPBVc_particle_emitter_definition@Z");

    PROFILER_SCOPE_BEGIN(122, jetwash_particle_init, jetwash_particle_init_profile_instance);

    long object_index = system->get_object_index();
    g_jetwash_particle_state.valid = false;
    if (object_index != NONE && g_jetwash_pulse_state.valid)
    {
        s_jetwash_definition const * definition = &g_jetwash_pulse_state.definition;
        if (definition->maximum_emission_length > 0.0f)
        {
            real distance_random = system->real_internal_random_range(0.0f, 1.0f);
            real angle_random = system->real_internal_random_range(0.0f, 1.0f);
            real distance = definition->radius * distance_random;
            real yaw_radians = definition->trace_yaw_angle.lower + angle_random * (definition->trace_yaw_angle.upper - definition->trace_yaw_angle.lower);
            real pitch = -(definition->trace_pitch_angle.lower + distance_random * (definition->trace_pitch_angle.upper - definition->trace_pitch_angle.lower));
            real_matrix4x3 emitter_to_world = *emitter->get_matrix();
            real_matrix4x3 inverse_transform;
            matrix4x3_inverse(&emitter_to_world, &inverse_transform);
            real_matrix4x3 trace_matrix = emitter_to_world;
            real_matrix4x3 rot;
            matrix4x3_rotation_from_axis_and_angle(&rot, &trace_matrix.forward, sine(yaw_radians), cosine(yaw_radians));
            matrix3x3_multiply(&rot.matrix3x3, &trace_matrix.matrix3x3, &trace_matrix.matrix3x3);
            real_point3d point;
            point_from_line3d(&emitter_to_world.position, &trace_matrix.up, distance, &point);
            matrix4x3_rotation_from_axis_and_angle(&rot, &trace_matrix.left, sine(pitch), cosine(pitch));
            matrix3x3_multiply(&rot.matrix3x3, &trace_matrix.matrix3x3, &trace_matrix.matrix3x3);
            trace_matrix.position = point;
            if (debug_objects_jetwash)
            {
                render_debug_vector(false, &point, &trace_matrix.forward, definition->maximum_emission_length, global_real_argb_blue);
            }
            s_collision_test_flags collision_flags = _collision_test_for_line_of_sight_obstruction_flags;
            collision_result collision_result_data;
            scale_vector3d(&trace_matrix.forward, definition->maximum_emission_length, &trace_matrix.forward);
            if (collision_test_vector(collision_flags, &trace_matrix.position, &trace_matrix.forward, object_index, NONE, &collision_result_data))
            {
                vector3d tangent;
                cross_product3d(&collision_result_data.plane.n, &trace_matrix.up, &tangent);
                vector3d particle_velocity;
                cross_product3d(&tangent, &collision_result_data.plane.n, &particle_velocity);
                if (debug_objects_jetwash)
                {
                    render_debug_sphere(false, &collision_result_data.point, 0.05f, global_real_argb_red);
                    render_debug_vector(false, &collision_result_data.point, &particle_velocity, 0.3f, global_real_argb_magenta);
                }
                vector3d offset_vector;
                vector_from_points3d(&emitter_to_world.position, &collision_result_data.point, &offset_vector);
                real offset_scale;
                if (definition->particle_offset > 0.0f)
                {
                    offset_scale = 1.0f - definition->particle_offset / definition->maximum_emission_length;
                }
                else
                {
                    offset_scale = 1.0f;
                }
                real_point3d spawn_position;
                point_from_line3d(&emitter_to_world.position, &offset_vector, offset_scale, &spawn_position);
                real_point3d local_position;
                matrix4x3_transform_point(&inverse_transform, &spawn_position, &local_position);
                matrix4x3_transform_vector(&inverse_transform, &particle_velocity, &particle_velocity);
                g_jetwash_particle_state.distance_fraction = magnitude3d(&offset_vector) / definition->maximum_emission_length;
                g_jetwash_particle_state.random_fraction = distance_random;
                g_jetwash_particle_state.position = local_position;
                g_jetwash_particle_state.normal = collision_result_data.plane.n;
                g_jetwash_particle_state.velocity = particle_velocity;
                g_jetwash_particle_state.valid = true;
            }
        }
    }

    jetwash_particle_init_profile_instance.end();
    return g_jetwash_particle_state.valid;
};

// $TODO nonmatching (only diff: target has no relocation for the particle state static, shows subi 0x28e4)
void jetwash_get_particle_simulation_values(float * values)
{
    mangled_ppc("?jetwash_get_particle_simulation_values@@YAXPAM@Z");

    values[0] = g_jetwash_particle_state.distance_fraction;
    values[1] = g_jetwash_particle_state.random_fraction;
};

// $TODO nonmatching (only diff: target has no relocation for the particle state static, shows subi 0x28e4)
bool jetwash_compute_particle_position_and_velocity(long object_index, float emission_angle, real_point3d * position, vector3d * velocity)
{
    mangled_ppc("?jetwash_compute_particle_position_and_velocity@@YA_NJMPATreal_point3d@@PATvector3d@@@Z");

    *position = g_jetwash_particle_state.position;
    *velocity = g_jetwash_particle_state.velocity;
    return g_jetwash_particle_state.valid;
};

