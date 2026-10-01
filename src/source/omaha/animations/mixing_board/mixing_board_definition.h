#ifndef __MIXING_BOARD_DEFINITION_H__
#define __MIXING_BOARD_DEFINITION_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_mixing_board_definition_list
{
    k_biped_mixing_board_definition = 0,
    k_vehicle_mixing_board_definition,
    k_giant_mixing_board_definition,
    k_data_driven_mixing_board_definition,

    k_total_mixing_board_definitions
};

enum e_mixing_board_constants
{
    k_maximum_components_per_type = 12
};

enum e_mixing_board_component_type
{
    _mixing_board_slider = 0,
    _mixing_board_animation_channel,
    _mixing_board_auxilary_channel,
    _mixing_board_aiming_channel,
    _mixing_board_facial_animation_channel,
    _mixing_board_pose_blend_channel,

    k_total_mixing_board_component_types,

    k_mixing_board_first_component_type = _mixing_board_slider,
    k_mixing_board_last_component_type = _mixing_board_pose_blend_channel
};

/* ---------- definitions */

class c_animation_manager;

class c_mixing_board_component_data
{
public:
    c_mixing_board_component_data(long _offset, long _count);

    long offset;
    long count;
};
static_assert(sizeof(c_mixing_board_component_data) == 0x8, "c_mixing_board_component_data");

struct s_mixing_board_component_titles
{
    char const * title[k_maximum_components_per_type];
};
static_assert(sizeof(s_mixing_board_component_titles) == 0x30, "s_mixing_board_component_titles");

class c_mixing_board_definition
{
public:
    long get_total_size() const;
    long get_component_type_count(long component_type) const;
    long get_component_type_offset(long component_type) const;
    bool validate_component_index(long component_type, long component_index) const;
    long get_component_offset(long component_type, long component_index) const;
    char const * get_component_name(long component_type, long component_index) const;

    char const * m_name;
    long m_total_size;
    void (*setup_function)(c_animation_manager * animation_manager);
    void (*reset_interpolators_function)(long, c_animation_manager * animation_manager);
    void (*locate_auxilary_animations_function)(long, c_animation_manager * animation_manager, void *);
    c_mixing_board_component_data m_component_data[k_total_mixing_board_component_types];
    s_mixing_board_component_titles component_name[k_total_mixing_board_component_types];
};
static_assert(sizeof(c_mixing_board_definition) == 0x164, "c_mixing_board_definition");

/* ---------- prototypes */

extern e_mixing_board_component_type operator++(e_mixing_board_component_type & value, int);
extern c_mixing_board_definition const * get_mixing_board_definition(long index);

/* ---------- globals */

extern long g_mixing_board_component_sizes[k_total_mixing_board_component_types];
extern c_mixing_board_definition g_mixing_board_definition_list[k_total_mixing_board_definitions];

/* ---------- public code */

#endif // __MIXING_BOARD_DEFINITION_H__

