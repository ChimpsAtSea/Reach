#pragma once
#ifndef __HS_UNIT_SEATS_H__
#define __HS_UNIT_SEATS_H__

/* ---------- headers */

#include "omaha\memory\static_arrays.h"
#include "omaha\units\unit_scripting.h"

/* ---------- constants */

enum e_unit_seat_occupancy_type
{
    _unit_seat_dont_care = 0,
    _unit_seat_occupied,
    _unit_seat_empty,

    k_number_of_unit_seat_occupancy_types
};

enum
{
    k_hs_unit_seat_count_bits = 16,
};

/* ---------- definitions */

struct unit_seat_source;

/* ---------- prototypes */

long hs_get_unit_seats(long object_index, long hs_unit_seat_designator, e_vehicle_seat_desire seat_desire_type, e_unit_seat_occupancy_type occupancy_type, unit_seat_source * out_unit_seats, long maximum_seat_count);
bool hs_unit_in_seat(long unit_index, long hs_unit_seat_designator);
long hs_encode_unit_seat_mapping(long unit_seat_start_index, long unit_seat_mapping_count);
bool hs_get_unit_seats_from_substring(long unit_definition_index, char const * seat_substring, c_big_flags_typed_no_init<long, 64> * out_unit_seats);

/* ---------- globals */

/* ---------- public code */

#endif // __HS_UNIT_SEATS_H__

