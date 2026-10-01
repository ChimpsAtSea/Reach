#pragma once
#ifndef __SOUND_SCENERY_H__
#define __SOUND_SCENERY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_definitions.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_definitions.h"

/* ---------- constants */

enum
{
    SOUND_SCENERY_TAG = 'ssce',
};

/* ---------- definitions */

struct s_object_placement_data;
struct s_game_cluster_bit_vectors;

struct _sound_scenery_definition
{
    float runtime_minimum_distance; // 0x0 (YJNXHAWAO1)
    float runtime_maximum_distance; // 0x4 (YJNXHAWAO2)
    float runtime_inner_cone_angle; // 0x8 (YJNXHAWAO3)
    float runtime_outer_cone_angle; // 0xC (YJNXHAWAO4)
};
static_assert(sizeof(_sound_scenery_definition) == 0x10, "_sound_scenery_definition");

// Reach layout from sound_scenery_struct_definition (tag json), size 0x188
struct s_sound_scenery_definition
{
    _object_definition object; // 0x0
    _sound_scenery_definition scenery; // 0x178
};
static_assert(sizeof(s_sound_scenery_definition) == 0x188, "s_sound_scenery_definition");

// Reach layout from sound_scenery_datum_struct (tag json), size 0x34
struct s_scenario_sound_scenery_datum
{
    e_sound_volume_type volume_type; // 0x0
    float height; // 0x4
    real_bounds override_cone_angle_bounds; // 0x8
    real_decibel override_outer_cone_gain_db; // 0x10
    s_sound_distance_parameters override_distance_parameters; // 0x14
};
static_assert(sizeof(s_scenario_sound_scenery_datum) == 0x34, "s_scenario_sound_scenery_datum");

// Reach layout from scenario_sound_scenery_block (tag json), size 0x8C
struct s_scenario_sound_scenery
{
    short type; // 0x0
    short name; // 0x2
    unsigned char object_data[0x54]; // 0x4 $TODO scenario_object_datum_struct
    s_scenario_sound_scenery_datum sound_scenery; // 0x58
};
static_assert(sizeof(s_scenario_sound_scenery) == 0x8C, "s_scenario_sound_scenery");

// field order verified in sound_scenery_place
struct _sound_scenery_datum
{
    e_sound_volume_type volume_type; // 0x0
    float height; // 0x4
    s_sound_distance_parameters override_distance_parameters; // 0x8
    real_bounds override_cone_angle_bounds; // 0x28
    real_decibel override_outer_cone_gain_db; // 0x30
};
static_assert(sizeof(_sound_scenery_datum) == 0x34, "_sound_scenery_datum");

// $TODO: offsets are from the start of the datum; _object_datum is only partially reversed
struct sound_scenery_datum
{
    long definition_index; // 0x0
    _object_datum object; // 0x4
    unsigned char unknown_after_object[0x1A8 - 0x4 - sizeof(_object_datum)];
    _sound_scenery_datum sound_scenery; // 0x1A8
};
static_assert(OFFSETOF(sound_scenery_datum, sound_scenery) == 0x1A8, "sound_scenery_datum::sound_scenery");

/* ---------- prototypes */

bool sound_scenery_new(long object_index, s_object_placement_data * data, bool * out_of_memory);
void sound_scenery_place(long object_index, s_scenario_sound_scenery const * scenario_sound_scenery);
void sound_scenery_render_debug(long sound_scenery_index);
void sound_scenery_render_debug_direct(long sound_scenery_index);
float sound_scenery_compute_bounding_sphere_radius(long sound_scenery_index);
bool sound_scenery_compute_activation(long sound_scenery_index, s_game_cluster_bit_vectors const * cluster_activation, bool * out_active);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_SCENERY_H__
