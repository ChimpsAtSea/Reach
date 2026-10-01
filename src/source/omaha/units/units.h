#pragma once
#ifndef __UNITS_H__
#define __UNITS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\target_tracking.h"

/* ---------- constants */

/* ---------- definitions */

struct s_unit_camera;

struct s_unit_weapon_set
{
    short set_identifier; // 0x0
    char weapon_indices[2]; // 0x2
};
static_assert(sizeof(s_unit_weapon_set) == 0x4, "s_unit_weapon_set");

// $TODO: Reach layout differs from H3; offsets from the recorded animation unit control maps, members past 0x54 not reversed
struct unit_control_data
{
    long animation_seat; // 0x0
    short aiming_speed; // 0x4
    s_unit_weapon_set weapon_set; // 0x6
    short grenade_index; // 0xA
    short zoom_level; // 0xC
    unsigned __int64 control_flags; // 0x10
    vector3d throttle; // 0x18
    real primary_trigger; // 0x24
    real secondary_trigger; // 0x28
    unsigned char unknown2C[0x4]; // 0x2C
    vector3d facing_vector; // 0x30
    vector3d aiming_vector; // 0x3C
    vector3d looking_vector; // 0x48
    unsigned char unknown54[0x3C]; // 0x54
};
static_assert(sizeof(unit_control_data) == 0x90, "unit_control_data");

struct s_unit_camera_info
{
    long unit_index; // 0x0
    short seat_index; // 0x4
    s_unit_camera const * unit_camera; // 0x8
    real_point3d unit_origin; // 0xC
    long support_weapon_index; // 0x18
};
static_assert(sizeof(s_unit_camera_info) == 0x1C, "s_unit_camera_info");

// Reach layout (0x18, H3 was 0x10); offsets verified in unit_update_attackers and c_dead_camera::set_target
struct unit_attacker
{
    unsigned long game_time_stamp; // 0x0
    float damage_inflicted; // 0x4
    float __unknown8; // 0x8 $TODO reset to 0.0f by unit_update_attackers
    long damage_owner_object_index; // 0xC
    long damage_owner_player_index; // 0x10
    unsigned char damage_reporting_info[0x4]; // 0x14 $TODO s_damage_reporting_info (0x2) + padding
};
static_assert(sizeof(unit_attacker) == 0x18, "unit_attacker");

// $TODO: layout only partially reversed (mover/unit sub-structures not split yet); offsets are from the start of the datum
struct unit_datum
{
    long definition_index; // 0x0
    _object_datum object; // 0x4
    unsigned char unknown_after_object[0x1CC - 0x4 - sizeof(_object_datum)];
    long player_index; // 0x1CC (player_index_from_unit_index)
    long last_player_index; // 0x1D0 (c_dead_camera::set_target)
    unsigned char unknown1D4[0x1E4 - 0x1D4]; // 0x1D4
    vector3d unknown1E4; // 0x1E4 name unknown (c_sandbox_camera::update: camera forward, pitch from arcsine(k))
    unsigned char unknown1F0[0x208 - 0x1F0]; // 0x1F0
    vector3d desired_aiming_vector; // 0x208 (aiming_vector follows at 0x214, see unit_get_aiming_vector)
    unsigned char unknown214[0x2DC - 0x214]; // 0x214
    c_opaque_data<c_target_tracking_system, 60, 4> target_tracking; // 0x2DC
    unsigned char unknown318[0x32E - 0x318]; // 0x318
    short parent_seat_index; // 0x32E (hs_unit_in_seat)
    unsigned char unknown330[0x4E4 - 0x330]; // 0x330
    unit_attacker attackers[4]; // 0x4E4 (unit_update_attackers, c_dead_camera::set_target)
};
static_assert(OFFSETOF(unit_datum, player_index) == 0x1CC, "unit_datum::player_index");
static_assert(OFFSETOF(unit_datum, unknown1E4) == 0x1E4, "unit_datum::unknown1E4");
static_assert(OFFSETOF(unit_datum, attackers) == 0x4E4, "unit_datum::attackers");
static_assert(OFFSETOF(unit_datum, desired_aiming_vector) == 0x208, "unit_datum::desired_aiming_vector");
static_assert(OFFSETOF(unit_datum, target_tracking) == 0x2DC, "unit_datum::target_tracking");
static_assert(OFFSETOF(unit_datum, parent_seat_index) == 0x32E, "unit_datum::parent_seat_index");

struct unit_seat;

struct unit_seat_source
{
    long unit_index; // 0x0
    short seat_index; // 0x4
    unit_seat const * seat; // 0x8
};
static_assert(sizeof(unit_seat_source) == 0xC, "unit_seat_source");

/* ---------- prototypes */

void unit_get_camera_info(long unit_index, s_unit_camera_info * camera_info);
void unit_get_camera_position(long unit_index, real_point3d * position);
short unit_get_all_seats(long unit_index, unit_seat_source * seat_array, short max_number_of_seats, bool allow_dead_vehicles);
bool unit_seat_filled(long parent_object_index, short seat_index);
real unit_compute_boost_fraction(long unit_index);
void unit_euler_aiming_update(real_matrix4x3 const * matrix, real dt, vector3d * facing, vector3d const * desired_facing, real ticks, vector3d * angular_velocity, real_rectangle2d const * facing_bounds, real maximum_angular_velocity, real maximum_angular_acceleration, real * final_angular_speed);

/* ---------- globals */

/* ---------- public code */

#endif // __UNITS_H__

