#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\mixing_board\\mixing_board_slider.cpp"
/* ---------- headers */

#include "omaha\animations\mixing_board\mixing_board_slider.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_time.h"
#include "omaha\math\fixed_point_math.h"
#include "omaha\math\floating_point_tools.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_short_fixed_unit k_fixed_target_positions[k_number_of_slider_target_positions] = { 0, 0, c_short_fixed_unit::k_fixed_half, c_short_fixed_unit::k_fixed_one };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static short const t_short_fixed<13>::k_fixed_half; // "?k_fixed_half@?$t_short_fixed@$0N@@@2FB"
// float const `public: float __cdecl t_short_fixed<8>::export_real(void) const'::`2'::s_inv_real_one; // "?s_inv_real_one@?1??export_real@?$t_short_fixed@$07@@QBAMXZ@4MB"
// `public: float __cdecl t_short_fixed<8>::export_real(void) const'::`2'::`local static guard'{2}; // "??_B?1??export_real@?$t_short_fixed@$07@@QBAMXZ@51"

// public: void c_mixing_board_slider::move_to_target(enum e_slider_target_positions, long, class t_short_fixed<8>);
// public: void c_mixing_board_slider::move_to_target(enum e_slider_target_positions, long, float);
// public: void c_mixing_board_slider::snap_to_target(enum e_slider_target_positions);
// public: void c_mixing_board_slider::freeze(void);
// public: void c_mixing_board_slider::snap_to_position(class t_short_fixed<13>);
// public: void c_mixing_board_slider::snap_to_position(float);
// public: bool c_mixing_board_slider::update(void);
// public: void c_mixing_board_slider::set_parent_slider(long, enum e_mixing_board_parent_slider_type);
// public: bool t_short_fixed<13>::operator==(class t_short_fixed<13> const &) const;
// public: bool t_short_fixed<13>::operator!=(class t_short_fixed<13> const &) const;
// public: float t_short_fixed<8>::export_real(void) const;
// void k_fixed_target_positions::`dynamic atexit destructor'(void);

void c_mixing_board_slider::move_to_target(e_slider_target_positions target, long pattern, c_short_fixed seconds)
{
    mangled_ppc("?move_to_target@c_mixing_board_slider@@QAAXW4e_slider_target_positions@@JV?$t_short_fixed@$07@@@Z");

    pattern = PIN(pattern, 0, k_total_slider_movement_patterns - 1);
    if (target != _slider_target_position_unknown0)
    {
        if (target != m_slider_target || pattern != m_slider_pattern)
        {
            m_slider_target = target;
            m_slider_pattern = static_cast<unsigned char>(pattern);
            m_total_seconds = seconds;
            m_seconds_remaining = seconds;
            m_starting_value = m_value;
        }
        else
        {
            m_seconds_remaining = CEILING(m_seconds_remaining, seconds);
        }
    }
};

void c_mixing_board_slider::move_to_target(e_slider_target_positions target, long pattern, float seconds)
{
    mangled_ppc("?move_to_target@c_mixing_board_slider@@QAAXW4e_slider_target_positions@@JM@Z");

    pattern = PIN(pattern, 0, k_total_slider_movement_patterns - 1);
    if (target != _slider_target_position_unknown0)
    {
        seconds = PIN(seconds, 0.0f, 127.0f);

        c_short_fixed fixed_seconds;
        fixed_seconds.import_real(seconds);
        move_to_target(target, pattern, fixed_seconds);
    }
};

void c_mixing_board_slider::snap_to_target(e_slider_target_positions target)
{
    mangled_ppc("?snap_to_target@c_mixing_board_slider@@QAAXW4e_slider_target_positions@@@Z");

    if (target != _slider_target_position_unknown0)
    {
        freeze();
        m_slider_target = target;
        m_value = k_fixed_target_positions[target];
    }
};

void c_mixing_board_slider::snap_to_position(c_short_fixed_unit position)
{
    mangled_ppc("?snap_to_position@c_mixing_board_slider@@QAAXV?$t_short_fixed@$0N@@@@Z");

    freeze();
    m_value = position;
};

void c_mixing_board_slider::snap_to_position(float position)
{
    mangled_ppc("?snap_to_position@c_mixing_board_slider@@QAAXM@Z");

    freeze();
    position = clamp_to_unit_space(position);
    m_value.import_real(position);
};

bool c_mixing_board_slider::update()
{
    mangled_ppc("?update@c_mixing_board_slider@@QAA_NXZ");

    bool slider_updated = false;
    if (m_slider_target != _slider_target_position_unknown0)
    {
        c_short_fixed_unit target_value = k_fixed_target_positions[m_slider_target];
        if (m_value != target_value)
        {
            if (m_total_seconds.raw_bits != 0)
            {
                c_short_fixed fixed_tick_length;
                fixed_tick_length.import_real(game_tick_length());
                if (m_seconds_remaining > fixed_tick_length)
                {
                    float seconds_remaining = m_seconds_remaining.export_real();
                    seconds_remaining -= game_tick_length();

                    float starting_value = m_starting_value.export_real();
                    float value_delta = target_value.export_real() - starting_value;
                    float inverse_t = seconds_remaining / m_total_seconds.export_real();
                    float t = PIN(1.0f - inverse_t, k_real_epsilon, 1.0f);
                    float v = 0.0f;

                    switch (m_slider_pattern)
                    {
                    case _movement_pattern_linear:
                    {
                        v = t;
                    }
                    break;
                    case _movement_pattern_light_ease_in:
                    {
                        v = t + (1.0f - t) * t;
                    }
                    break;
                    case _movement_pattern_full_ease_in:
                    {
                        v = t + (1.0f - t) * t * t;
                    }
                    break;
                    case _movement_pattern_light_ease_out:
                    {
                        v = t * t;
                    }
                    break;
                    case _movement_pattern_full_ease_out:
                    {
                        v = t * t * t;
                    }
                    break;
                    case _movement_pattern_light_ease_in_and_out:
                    {
                        if (t < 0.5f)
                        {
                            t = t * 2.0f;
                            v = t * t * t;
                            v = v * 0.5f;
                        }
                        else
                        {
                            t = (t - 0.5f) * 2.0f;
                            v = t + (1.0f - t) * t;
                            v = 0.5f + v * 0.5f;
                        }
                    }
                    break;
                    case _movement_pattern_full_ease_in_and_out:
                    {
                        if (t < 0.5f)
                        {
                            t = t * 2.0f;
                            v = t * t;
                            v = v * 0.5f;
                        }
                        else
                        {
                            t = (t - 0.5f) * 2.0f;
                            v = t + (1.0f - t) * t * t;
                            v = 0.5f + v * 0.5f;
                        }
                    }
                    break;
                    default:
                    {
                        dassert_tag_debug_untracked_jul_11_2011(189, false, "unreachable");
                    }
                    break;
                    }

                    float new_value = starting_value + v * value_delta;
                    c_short_fixed_unit old_value = m_value;
                    m_value.import_real(new_value);

                    short min_raw_value = m_starting_value.raw_bits > target_value.raw_bits ? target_value.raw_bits : m_starting_value.raw_bits;
                    short max_raw_value = MAX(m_starting_value.raw_bits, target_value.raw_bits);
                    m_value.raw_bits = PIN(m_value.raw_bits, min_raw_value, max_raw_value);
                    m_seconds_remaining.import_real(seconds_remaining);

                    if (m_value == old_value)
                    {
                        if (m_value.raw_bits < target_value.raw_bits)
                        {
                            m_value.raw_bits++;
                        }
                        else if (m_value.raw_bits > target_value.raw_bits)
                        {
                            m_value.raw_bits--;
                        }
                        else
                        {
                            snap_to_target(m_slider_target);
                        }
                    }
                }
                else
                {
                    snap_to_target(m_slider_target);
                }
            }
            else
            {
                snap_to_target(m_slider_target);
            }
        }
        else
        {
            freeze();
        }
    }

    return slider_updated;
};

void c_mixing_board_slider::set_parent_slider(long index, e_mixing_board_parent_slider_type slider_type)
{
    mangled_ppc("?set_parent_slider@c_mixing_board_slider@@QAAXJW4e_mixing_board_parent_slider_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(245, index==NONE || (index>=0 && index<=k_char_max));

    if (slider_type == _mixing_board_parent_slider_type_unknown0 || index == NONE)
    {
        m_parent_slider_type = _mixing_board_parent_slider_type_unknown0;
        m_parent_slider_index = NONE;
    }
    else
    {
        m_parent_slider_type = slider_type;
        m_parent_slider_index = static_cast<char>(index);
    }
};

