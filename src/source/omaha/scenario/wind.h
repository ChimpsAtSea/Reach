#pragma once
#ifndef __WIND_H__
#define __WIND_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

struct s_wind_definition;

struct s_wind_values
{
    long wind_time_ticks; // 0x0
    long fractional_wind_time; // 0x4
    long wind_x; // 0x8
    long wind_y; // 0xC
    vector4d wind_data; // 0x10
    vector4d wind_data2; // 0x20
};
static_assert(sizeof(s_wind_values) == 0x30, "s_wind_values");

/* ---------- prototypes */

s_wind_definition const * get_wind_definition(real_point3d const * position);
void setup_wind_constants(s_wind_definition const * wind_definition, s_wind_values const * wind_values);

/* ---------- globals */

/* ---------- public code */

#endif // __WIND_H__

