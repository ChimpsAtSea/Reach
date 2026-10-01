#pragma once
#ifndef __FUNCTION_DEFINITIONS_H__
#define __FUNCTION_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\wrapped_arrays.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_function_definition
{
public:
    enum e_function_type
    {
        _function_type_identity = 0,
        _function_type_constant,
        _function_type_transition,
        _function_type_periodic,
        _function_type_linear,
        _function_type_linear_key,
        _function_type_multi_linear_key,
        _function_type_spline,
        _function_type_multi_spline,
        _function_type_exponent,
        _function_type_spline2,
        k_function_type_count
    };

    enum e_color_graph_type
    {
        _function_color_graph_type_scalar = 0,
        _function_color_graph_type_one_color,
        _function_color_graph_type_two_color,
        _function_color_graph_type_three_color,
        _function_color_graph_type_four_color,
        k_function_color_graph_type_count
    };

    float evaluate_scalar(float input, float range) const;
    void clone(c_function_definition const & source);

private:
    s_tag_data m_data; // 0x0
};
static_assert(sizeof(c_function_definition) == 0x14, "c_function_definition");

class c_function_definition_editor
{
public:
    c_function_definition_editor(c_function_definition * function) :
        m_function(function)
    {
    }

    void calc_default_values();
    void set_function_type(c_function_definition::e_function_type function_type);
    void set_color_graph_type(c_function_definition::e_color_graph_type color_graph_type);
    void set_color(unsigned char color_index, unsigned long color);
    void set_control_point_y(unsigned char function_index, unsigned char point_index, float y);
    void set_clamp_range_min(float clamp_range_min);
    void set_clamp_range_max(float clamp_range_max);
    void set_ranged(bool ranged);
    void set_function_index(unsigned char function_index, unsigned char function_type_index);
    void set_amplitude_range_min(unsigned char function_index, float amplitude_range_min);
    void set_amplitude_range_max(unsigned char function_index, float amplitude_range_max);
    void set_constant(unsigned char function_index, float value);

private:
    c_function_definition * m_function; // 0x0
};
static_assert(sizeof(c_function_definition_editor) == 0x4, "c_function_definition_editor");

struct s_scalar_function_named_struct
{
    c_opaque_data<c_function_definition, 20, 4> function; // 0x0
};
static_assert(sizeof(s_scalar_function_named_struct) == 0x14, "s_scalar_function_named_struct");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FUNCTION_DEFINITIONS_H__

