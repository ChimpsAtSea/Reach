#pragma once
#ifndef __VEHICLES_H__
#define __VEHICLES_H__

/* ---------- headers */

#include "omaha\units\vehicle_type_component.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// count (11) from c_flags_no_init<e_vehicle_flags, unsigned short, 11>; names are H3's except where noted, Reach order unverified
enum e_vehicle_flags
{
    _vehicle_blurred_bit = 0,
    _vehicle_e_brake_blurred_bit,
    _vehicle_hovering_bit,
    _vehicle_control_jump_bit,
    _vehicle_control_boost_bit,
    _vehicle_boosting_bit, // Reach: gates unit_compute_boost_fraction in boat_engine_update (name guessed)
    _vehicle_unknown6_bit,
    _vehicle_unknown7_bit,
    _vehicle_unknown8_bit,
    _vehicle_unknown9_bit,
    _vehicle_unknown10_bit,

    k_vehicle_flags_count
};

/* ---------- definitions */

struct s_unit_trick_definition;

// $TODO: layout only partially reversed; total size unknown
struct vehicle_datum
{
    long definition_index; // 0x0 (boat_engine_update: tag_get('vehi', vehicle->definition_index))
    unsigned char unknown4[0x9B8 - 0x4]; // 0x4 $TODO object_datum, unit
    c_flags_no_init<e_vehicle_flags, unsigned short, k_vehicle_flags_count> flags; // 0x9B8
    unsigned char unknown9BA[0x9C8 - 0x9BA]; // 0x9BA
    c_vehicle_type_component type_component; // 0x9C8
};

/* ---------- prototypes */

s_unit_trick_definition const * vehicle_get_current_trick_definition(long vehicle_index);

/* ---------- globals */

/* ---------- public code */

#endif // __VEHICLES_H__

