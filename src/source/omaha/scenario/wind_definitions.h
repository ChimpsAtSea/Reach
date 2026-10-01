#pragma once
#ifndef __WIND_DEFINITIONS_H__
#define __WIND_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\function_definitions.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    WIND_GROUP_TAG = 'wind',
};

/* ---------- definitions */

struct s_wind_values;

struct s_wind_function
{
    c_function_definition function; // 0x0
};
static_assert(sizeof(s_wind_function) == 0x14, "s_wind_function");

struct s_wind_definition
{
    // f i (instance owned by wind.obj)
    static s_wind_definition const * get(long tag_index)
    {
        mangled_ppc("?get@s_wind_definition@@SAPBU1@J@Z");

        return static_cast<s_wind_definition const *>(tag_get(WIND_GROUP_TAG, tag_index));
    };

    static bool postprocess(long tag_index, void * data, bool for_editor);
    static bool initialize_on_new(void * data);
    void update(s_wind_values * wind_values) const;

    s_wind_function m_direction; // 0x0
    s_wind_function m_speed; // 0x14
    s_wind_function m_decorator_bend; // 0x28
    s_wind_function m_decorator_oscillation; // 0x3C
    s_wind_function m_decorator_frequency; // 0x50
    real m_decorator_gust_size; // 0x64
    s_tag_reference m_decorator_gust_bitmap; // 0x68
};
static_assert(sizeof(s_wind_definition) == 0x78, "s_wind_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __WIND_DEFINITIONS_H__

