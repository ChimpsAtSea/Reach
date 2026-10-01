#ifndef __OBJECTS_H__
#define __OBJECTS_H__
#pragma once

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\location.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\objects\object_types.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

// verified in c_camera::set_target (assert text "object_get(object_index)!=NULL", call object_get_and_verify_type(object_index, -1))
#define object_get(OBJECT_INDEX) object_get_and_verify_type(OBJECT_INDEX, NONE)

union real_point3d;
union vector3d;
struct real_matrix4x3;

struct object_marker
{
    short node_index; // 0x0
    real_matrix4x3 node_matrix; // 0x4
    real_matrix4x3 matrix; // 0x38
    real radius; // 0x6C
};
static_assert(sizeof(object_marker) == 0x70, "object_marker");

class c_object_identifier
{
public:
    e_object_type get_type() const
    {
        return static_cast<e_object_type>(m_type);
    }

    void create_from_sky(e_object_type type, long scenario_sky_index);
    long find_object_index() const;
    long get_sky_identifier() const;

private:
    long m_unique_id; // 0x0
    short m_origin_bsp_index; // 0x4
    char m_type; // 0x6
    char m_source; // 0x7
};
static_assert(sizeof(c_object_identifier) == 0x8, "c_object_identifier");

struct object_header_block_reference
{
    short size; // 0x0
    short offset; // 0x2
};
static_assert(sizeof(object_header_block_reference) == 0x4, "object_header_block_reference");

// names from H3 (bit 21 is H3's _object_static_pathfinding_bit, one lower than in H3: Reach dropped a bit before it); only bit 21 and the count (32, from ?test@?$c_flags_no_init@W4e_object_data_flags@@K$0CA@...) are verified
enum e_object_data_flags
{
    _object_hidden_bit = 0,
    _object_always_active_bit,
    _object_being_created_bit,
    _object_wholly_under_media_bit,
    _object_has_attached_lights_bit,
    _object_has_attached_looping_sounds_bit,
    _object_has_unattached_lights_bit,
    _object_in_limbo_bit,
    _object_connected_to_map_bit,
    _object_uses_collidable_list_bit,
    _object_mirrored_bit,
    _object_render_model_has_instances_bit,
    _object_static_lighting_recompute_bit,
    _object_static_lighting_raycast_sideways_bit,
    _object_render_time_node_matrices_complete_bit,
    _object_clip_plane_bit,
    _object_shadowless_bit,
    _object_deleted_when_deactivated_bit,
    _object_outside_of_map_bit,
    _object_cinematic_lod_bit,
    _object_cinematic_collision_bit,
    _object_static_pathfinding_bit, // 21 (user_get_look_at_point)
    _object_data_flags_unknown22_bit,
    _object_data_flags_unknown23_bit,
    _object_data_flags_unknown24_bit,
    _object_data_flags_unknown25_bit,
    _object_data_flags_unknown26_bit,
    _object_data_flags_unknown27_bit,
    _object_data_flags_unknown28_bit,
    _object_data_flags_unknown29_bit,
    _object_data_flags_unknown30_bit,
    _object_data_flags_unknown31_bit,

    k_object_data_flags_count
};

struct s_object_data_flags_string_resolver;

// names from H3 object_constants.h
enum e_object_source
{
    _object_source_structure_object = 0,
    _object_source_editor,
    _object_source_dynamic,
    _object_source_legacy,
    _object_source_sky,
    _object_source_parent,

    k_number_of_object_sources,

    _object_source_none = -1
};

// names from H3 objects.h; Reach has 25 bits (c_flags_no_init<e_object_damage_flags, unsigned long, 25>::test), bits 3-24 not reversed
enum e_object_damage_flags
{
    _object_passed_body_damage_threshold_bit = 0,
    _object_passed_shield_damage_threshold_bit,
    _object_dead_bit, // verified: object_get_default_material picks the dead collision material

    k_object_damage_flags_count = 25
};

// $TODO: layout only partially reversed (offsets verified in watch_object_describe_internal); total size unknown
struct _object_datum
{
    c_flags_no_init<e_object_data_flags, unsigned long, k_object_data_flags_count, s_object_data_flags_string_resolver> flags; // 0x0 (user_get_look_at_point)
    unsigned char unknown4[0x10 - 0x4]; // 0x4
    long parent_object_index; // 0x10 (hs_unit_in_seat)
    unsigned char unknown14[0x16 - 0x14]; // 0x14
    short scenario_datum_index; // 0x16 (area_set_compare_by_order_index)
    short map_variant_index; // 0x18 (area_set_compare_by_order_index)
    unsigned char unknown1A[0x4C - 0x1A]; // 0x1A
    vector3d forward; // 0x4C (object_get_orientation)
    vector3d up; // 0x58 (object_get_orientation)
    vector3d translational_velocity; // 0x64 (character_physics_flying_update_turning)
    vector3d angular_velocity; // 0x70 (character_physics_flying_update_turning)
    real scale; // 0x7C (sound_scenery_compute_bounding_sphere_radius)
    unsigned char unknown80[0x4]; // 0x80
    c_object_identifier object_identifier; // 0x84
    short name_index; // 0x8C
    unsigned char unknown8E[0xC8 - 0x8E]; // 0x8E
    long havok_component_index; // 0xC8 (c_grounded_friction_component::update)
    unsigned char unknownCC[0x138 - 0xCC]; // 0xCC
    c_flags_no_init<e_object_damage_flags, unsigned long, k_object_damage_flags_count> damage_flags; // 0x138 (object_get_default_material)
    unsigned char unknown13C[0x190 - 0x13C]; // 0x13C
    object_header_block_reference multiplayer; // 0x190 (location_names_get_name_index_for_player)
};

struct object_datum
{
    long definition_index; // 0x0
    _object_datum object; // 0x4
};

struct object_header_datum
{
    short identifier; // 0x0
    unsigned char flags; // 0x2
    unsigned char type; // 0x3
    s_cluster_reference cluster_reference; // 0x4
    short data_size; // 0x6
    long datum_handle; // 0x8
    object_datum * datum; // 0xC
};
static_assert(sizeof(object_header_datum) == 0x10, "object_header_datum");

// names after H3 _new_object_*_bit; bits 8-11 unknown
enum e_object_placement_flags
{
    _object_placement_mirrored_bit = 0,
    _object_placement_disable_automatic_deletion_bit,
    _object_placement_disable_automatic_deletion_outside_map_bit,
    _object_placement_at_rest_bit,
    _object_placement_exact_placement_bit,
    _object_placement_in_local_physics_bit,
    _object_placement_sky_visibility_bit,
    _object_placement_editor_sync_bit,
    _object_placement_unknown8_bit,
    _object_placement_unknown9_bit,
    _object_placement_unknown10_bit,
    _object_placement_unknown11_bit,

    k_object_placement_flags_count
};

// $TODO: only the leading fields are reversed; size 0x1A4 from create_sky_object's stack frame
struct s_object_placement_data
{
    // inline in the target (f i, simulation_game_bipeds.obj); bodies not reversed yet
    s_object_placement_data(void);
    ~s_object_placement_data(void);

    long definition_index; // 0x0
    c_object_identifier object_identifier; // 0x4
    long variant_name; // 0xC
    long scenario_datum_index; // 0x10
    unsigned char bsp_placement_policy; // 0x14 $TODO c_object_bsp_placement_policy
    unsigned char pad15[3]; // 0x15
    c_flags_no_init<e_object_placement_flags, unsigned long, k_object_placement_flags_count> flags; // 0x18
    unsigned char unknown1C[0x1A4 - 0x1C]; // 0x1C
};
static_assert(sizeof(s_object_placement_data) == 0x1A4, "s_object_placement_data");

class c_object_iterator_base
{
public:
    long get_index() const
    {
        mangled_ppc("?get_index@c_object_iterator_base@@QBAJXZ");

        return m_iterator.index;
    };

protected:
    object_datum * get_datum_internal();
    void object_iterator_begin_internal(unsigned long type_flags, unsigned long header_flags, unsigned long iteration_match_flags, long next_absolute_index);
    bool object_iterator_next_with_match_flags_internal();

private:
    struct s_object_iterator
    {
        unsigned long type_flags; // 0x0
        unsigned long header_flags; // 0x4
        unsigned long iteration_match_flags; // 0x8
        long next_absolute_index; // 0xC
        long index; // 0x10
        unsigned long signature; // 0x14
    };
    static_assert(sizeof(s_object_iterator) == 0x18, "s_object_iterator");

    object_datum * m_object; // 0x0
    s_object_iterator m_iterator; // 0x4
};
static_assert(sizeof(c_object_iterator_base) == 0x1C, "c_object_iterator_base");

template<typename t_type>
class c_multiplayer_object_iterator :
    public c_object_iterator_base
{
public:
    void begin(unsigned long type_flags, unsigned char header_flags, unsigned long iteration_match_flags)
    {
        object_iterator_begin_internal(type_flags, header_flags, iteration_match_flags | 1, -1);
    };

    bool next()
    {
        return object_iterator_next_with_match_flags_internal();
    };

    t_type * get_datum()
    {
        return get_datum_internal();
    };
};

struct s_multiplayer_object_properties;
struct s_collision_hierarchy_element_cluster_iterator;

// Reach: wraps c_opaque_data<s_collision_hierarchy_element_cluster_iterator, 4, 4> (object_get_first_cluster)
struct object_cluster_iterator
{
    c_opaque_data<s_collision_hierarchy_element_cluster_iterator, 4, 4> iterator; // 0x0
    unsigned char unknown4[0x8]; // 0x4 $TODO size from the sound_scenery_compute_activation stack frame
};
static_assert(sizeof(object_cluster_iterator) == 0xC, "object_cluster_iterator");

/* ---------- prototypes */

void objects_initialize_for_saved_game(long game_state_proc_flags);
void game_state_after_load_objects_setup_structure_bsp_fake_lightprobes(long game_state_proc_flags);
void * object_get_and_verify_type(long object_index, unsigned long object_type_mask);
e_object_source object_get_root_source(long object_index);
long object_new(s_object_placement_data * data);
void object_set_object_index_for_name_index(short name_index, long object_index);
void * object_try_and_get_and_verify_type(long object_index, unsigned long object_type_mask);
real_point3d * object_get_center_of_mass(long object_index, real_point3d * center);
real_point3d * object_get_center_of_mass_interpolated(long object_index, real_point3d * center);
void object_get_bounding_sphere(long object_index, real_point3d * center, real * radius);
bool object_get_function_value(long object_index, long function, long function_owner_tag_index, float * function_value);
float object_get_function_value_simple(long object_index, long function, long function_owner_tag_index);
short object_get_markers_by_string_id(long object_index, long marker_name, object_marker * markers, short maximum_marker_count);
real_matrix4x3 const * object_get_node_matrix(long object_index, short node_index);
long object_get_ultimate_parent(long object_index);
void object_get_velocities(long object_index, vector3d * linear_velocity, vector3d * angular_velocity);
void object_set_velocities(long object_index, vector3d const * linear_velocity, vector3d const * angular_velocity);
bool object_get_localized_velocities(long object_index, vector3d * linear_velocity, vector3d * angular_velocity, vector3d * local_linear_velocity, vector3d * local_angular_velocity);
s_multiplayer_object_properties * object_try_and_get_multiplayer(long object_index);
s_multiplayer_object_properties * object_get_multiplayer(long object_index);
void * object_header_block_get(long object_index, object_header_block_reference const * reference);
real_point3d * object_get_origin_interpolated(long object_index, real_point3d * origin);
real_point3d * object_get_origin(long object_index, real_point3d * origin);
e_object_type object_get_type(long object_index); // $TODO inline in the target (f i, render_information.obj); body not reversed yet
void object_get_interpolated_version_of_world_space_position(long object_index, real_point3d const * position, real_point3d * interpolated_position);
void object_get_orientation(long object_index, vector3d * forward, vector3d * up);
s_cluster_reference object_get_first_cluster(object_cluster_iterator * iterator, long object_index);
s_cluster_reference object_get_next_cluster(object_cluster_iterator * iterator, long object_index);

/* ---------- globals */

extern __declspec(thread) s_data_array * object_header_data;
extern bool debug_objects_sound_spheres;
extern bool debug_objects_vehicle_physics;

/* ---------- public code */

#endif // __OBJECTS_H__

