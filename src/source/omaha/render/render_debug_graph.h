#pragma once
#ifndef __RENDER_DEBUG_GRAPH_H__
#define __RENDER_DEBUG_GRAPH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\math\integer_math.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// $TODO enumerator names unknown; the target uses c_flags_no_init<e_graph_column, unsigned short, 4>
enum e_graph_column
{
    _graph_column_0 = 0,
    _graph_column_1,
    _graph_column_2,
    _graph_column_3,

    k_graph_column_count
};

/* ---------- definitions */

class c_render_debug_graph_iterator
{
public:
    c_render_debug_graph_iterator(void); // $TODO inline in the target (render_debug_auto_graph.obj)

    virtual void begin_all_series(void) = 0;
    virtual bool next_series(c_static_string<256> * series_name) = 0;
    virtual bool next_data_point_in_series(real_point2d * point) = 0;
};

struct s_render_debug_graph_config
{
    s_render_debug_graph_config(void); // $TODO inline in the target (render_debug_auto_graph.obj)
    void initialize_to_defaults(void);

    s_static_string<64> name; // 0x0
    s_static_string<64> range_units; // 0x40
    s_static_string<64> domain_units; // 0x80
    rectangle2d bounds; // 0xC0 (text rows/columns)
    real_bounds domain_bounds; // 0xC8
    real_bounds range_bounds; // 0xD0
    real domain_tick_spacing; // 0xD8
    real range_tick_spacing; // 0xDC
    c_flags_no_init<e_graph_column, unsigned short, k_graph_column_count> columns; // 0xE0
    long unknown_E4; // 0xE4 $TODO
    long unknown_E8; // 0xE8 $TODO
    real domain_axis_fraction; // 0xEC $TODO name
    c_render_debug_graph_iterator * iterator; // 0xF0
};

/* ---------- prototypes */

extern void render_debug_graph(s_render_debug_graph_config const * config);

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_DEBUG_GRAPH_H__

