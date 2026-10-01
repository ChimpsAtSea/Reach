#ifndef __MIXING_BOARD_H__
#define __MIXING_BOARD_H__
#pragma once

/* ---------- headers */

#include "omaha\animations\mixing_board\mixing_board_definition.h"

/* ---------- constants */

/* ---------- definitions */

class c_channel_base;
class c_mixing_board_slider;

class c_mixing_board_component_iterator
{
public:
    c_mixing_board_component_iterator();
    ~c_mixing_board_component_iterator();

    bool setup(long base_address, c_mixing_board_definition const * definition, e_mixing_board_component_type type);
    bool next();
    bool get(c_mixing_board_slider ** component);
    bool get(c_channel_base ** component);

private:
    bool get(unsigned char ** component);

    unsigned char * m_array;
    e_mixing_board_component_type m_type;
    long m_component_size;
    long m_array_count;
    long m_array_index;
};
static_assert(sizeof(c_mixing_board_component_iterator) == 0x14, "c_mixing_board_component_iterator");

/* ---------- prototypes */

extern void reset_mixing_board(c_animation_manager * animation_manager, long starting_address, c_mixing_board_definition const * definition);
extern long mixing_board_get_component(long starting_address, c_mixing_board_definition const * definition, long component_type, long component_index);

/* ---------- globals */

/* ---------- public code */

#endif // __MIXING_BOARD_H__

