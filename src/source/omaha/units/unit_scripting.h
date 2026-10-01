#pragma once
#ifndef __UNIT_SCRIPTING_H__
#define __UNIT_SCRIPTING_H__

/* ---------- headers */

/* ---------- constants */

// from H3 (verified by the hs_get_unit_seats switch)
enum e_vehicle_seat_desire
{
    _vehicle_seat_desire_any_non_driver = 0,
    _vehicle_seat_desire_gunner,
    _vehicle_seat_desire_passenger,
    _vehicle_seat_desire_driver,
    _vehicle_seat_desire_any,

    k_vehicle_seat_desire_types_count
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __UNIT_SCRIPTING_H__

