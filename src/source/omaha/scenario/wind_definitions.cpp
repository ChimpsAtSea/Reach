/* ---------- headers */

#include "omaha\scenario\wind_definitions.h"
#include <math.h>
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\main\main_screenshot.h"
#include "omaha\math\function_definitions.h"
#include "omaha\math\real_math.h"
#include "omaha\scenario\wind.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition wind_block; // "?wind_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition wind_block_struct_definition; // "?wind_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_group wind_group; // "?wind_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_wind_reference; // "?global_wind_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_wind_vtable; // "?legacy_wind_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_wind_stream_definition; // "?legacy_wind_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_wind_xsync_declaration; // "?legacy_wind_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_wind_vtable_shim; // "?legacy_wind_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_wind_definition::postprocess(long, void *, bool);
// public: static bool s_wind_definition::initialize_on_new(void *);
// public: void s_wind_definition::update(struct s_wind_values *) const;

bool s_wind_definition::postprocess(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess@s_wind_definition@@SA_NJPAX_N@Z");

    s_wind_definition * wind_definition = static_cast<s_wind_definition *>(data);
    wind_definition->m_decorator_gust_size = PIN(wind_definition->m_decorator_gust_size, k_valid_real_epsilon, 1000.0f);

    return true;
};

bool s_wind_definition::initialize_on_new(void * data)
{
    mangled_ppc("?initialize_on_new@s_wind_definition@@SA_NPAX@Z");

    s_wind_definition * wind_definition = static_cast<s_wind_definition *>(data);
    long default_wind_index = tag_load(WIND_GROUP_TAG, "globals\\default_wind", 15);
    if (default_wind_index != NONE)
    {
        s_wind_definition const * default_wind_definition = s_wind_definition::get(default_wind_index);
        wind_definition->m_direction.function.clone(default_wind_definition->m_direction.function);
        wind_definition->m_speed.function.clone(default_wind_definition->m_speed.function);
        wind_definition->m_decorator_bend.function.clone(default_wind_definition->m_decorator_bend.function);
        wind_definition->m_decorator_oscillation.function.clone(default_wind_definition->m_decorator_oscillation.function);
        wind_definition->m_decorator_frequency.function.clone(default_wind_definition->m_decorator_frequency.function);
        wind_definition->m_decorator_gust_size = default_wind_definition->m_decorator_gust_size;
        tag_reference_copy(&default_wind_definition->m_decorator_gust_bitmap, &wind_definition->m_decorator_gust_bitmap);
        tag_unload(default_wind_index);
    }

    return true;
};

// $TODO nonmatching: only the stack slots of seconds (target 0x70) and time_delta (target 0x7C) are swapped; renames/declaration order tried
void s_wind_definition::update(s_wind_values * values) const
{
    mangled_ppc("?update@s_wind_definition@@QBAXPAUs_wind_values@@@Z");

    real seconds = screenshot_get_frame_update_time_delta();
    seconds = real_min(seconds, 1024.0f);

    values->fractional_wind_time += 65536.0f * seconds;
    if (values->fractional_wind_time > 0x10000)
    {
        long ticks_elapsed = values->fractional_wind_time / 0x10000;
        values->fractional_wind_time %= 0x10000;
        values->wind_time_ticks += ticks_elapsed;
    }

    real time_delta = values->wind_time_ticks + values->fractional_wind_time / 65536.0f;
    real degrees = m_direction.function.evaluate_scalar(time_delta, 0.5f);
    real angle = k_pi * degrees / 180.0f;
    real speed = m_speed.function.evaluate_scalar(time_delta, 0.5f) / 6.818182f;
    vector2d direction;
    direction.i = sin(angle);
    direction.j = cos(angle);
    real speed_input = speed / 200.0f;
    real bend = m_decorator_bend.function.evaluate_scalar(speed_input, 0.5f);
    real oscillation = m_decorator_oscillation.function.evaluate_scalar(speed_input, 0.5f);
    real frequency = m_decorator_frequency.function.evaluate_scalar(speed_input, 0.5f);

    values->wind_x += 1048576.0f - direction.i * frequency * seconds * 1048576.0f;
    values->wind_y += 1048576.0f - direction.j * frequency * seconds * 1048576.0f;
    values->wind_x &= 0xFFFFF;
    values->wind_y &= 0xFFFFF;
    values->wind_data.i = values->wind_x / 1048576.0f;
    values->wind_data.j = values->wind_y / 1048576.0f;
    values->wind_data.k = 1.0f / m_decorator_gust_size;
    values->wind_data.l = 0.0f;
    values->wind_data2.i = direction.i * bend;
    values->wind_data2.j = direction.j * bend;
    values->wind_data2.k = oscillation;
    values->wind_data2.l = time_delta;
};

