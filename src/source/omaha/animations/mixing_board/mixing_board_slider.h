#pragma once
#ifndef __MIXING_BOARD_SLIDER_H__
#define __MIXING_BOARD_SLIDER_H__

/* ---------- headers */

#include "omaha\memory\static_arrays.h"
#include "omaha\math\fixed_point_math.h"

/* ---------- constants */

enum e_slider_movement_pattern
{
    _movement_pattern_linear = 0,
    _movement_pattern_light_ease_in,
    _movement_pattern_full_ease_in,
    _movement_pattern_light_ease_out,
    _movement_pattern_full_ease_out,
    _movement_pattern_light_ease_in_and_out,
    _movement_pattern_full_ease_in_and_out,

    k_total_slider_movement_patterns
};

// Reach: c_enum<e_slider_target_positions, unsigned char, 0, 4>; names per H3 not verified
enum e_slider_target_positions
{
    _slider_target_position_unknown0 = 0, // $TODO name
    _slider_target_position_unknown1, // $TODO name
    _slider_target_position_unknown2, // $TODO name
    _slider_target_position_unknown3, // $TODO name (c_channel_base::initialize snaps to 3)

    k_number_of_slider_target_positions
};

// Reach: c_enum<e_mixing_board_parent_slider_type, unsigned char, 0, 3>
enum e_mixing_board_parent_slider_type
{
    _mixing_board_parent_slider_type_unknown0 = 0, // $TODO name
    _mixing_board_parent_slider_type_unknown1, // $TODO name
    _mixing_board_parent_slider_type_unknown2, // $TODO name

    k_number_of_mixing_board_parent_slider_types
};

/* ---------- definitions */

typedef c_enum<e_slider_target_positions, unsigned char, 0, k_number_of_slider_target_positions> c_slider_target_positions;
typedef c_enum<e_mixing_board_parent_slider_type, unsigned char, 0, k_number_of_mixing_board_parent_slider_types> c_parent_slider_types;

// layout per c_mixing_board_slider::initialize (channel_base.obj); H3 member names
class c_mixing_board_slider
{
public:
    void initialize();
    void move_to_target(e_slider_target_positions target, long pattern, c_short_fixed seconds);
    void move_to_target(e_slider_target_positions target, long pattern, float seconds);
    void snap_to_target(e_slider_target_positions target);
    void snap_to_position(c_short_fixed_unit position);
    void snap_to_position(float position);
    bool update();
    void set_parent_slider(long index, e_mixing_board_parent_slider_type slider_type);

    // f i, instance owned by mixing_board_slider.obj
    void freeze()
    {
        mangled_ppc("?freeze@c_mixing_board_slider@@QAAXXZ");

        m_starting_value = m_value;
        m_total_seconds.raw_bits = 0;
        m_seconds_remaining.raw_bits = 0;
        m_slider_target = _slider_target_position_unknown0;
    };

private:
    c_short_fixed_unit m_value; // 0x0
    c_short_fixed_unit m_starting_value; // 0x2
    c_short_fixed m_total_seconds; // 0x4
    c_short_fixed m_seconds_remaining; // 0x6
    unsigned char m_slider_pattern; // 0x8
    c_slider_target_positions m_slider_target; // 0x9
    c_parent_slider_types m_parent_slider_type; // 0xA
    char m_parent_slider_index; // 0xB
};
static_assert(sizeof(c_mixing_board_slider) == 0xC, "c_mixing_board_slider");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MIXING_BOARD_SLIDER_H__

