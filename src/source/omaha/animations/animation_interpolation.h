#pragma once
#ifndef __ANIMATION_INTERPOLATION_H__
#define __ANIMATION_INTERPOLATION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_interpolation_type
{
    k_linear_interpolation = 0,
    k_light_ease_in_out_interpolation,
    k_heavy_ease_in_out_interpolation,
    k_light_deceleration_interpolation,
    k_heavy_deceleration_interpolation,

    k_total_interpolation_control_types
};

enum e_interpolator_flags
{
    _interpolator_forward_bit = 0,
    _interpolator_finished_bit,
    _interpolator_paused_bit,
    _interpolator_animated_source_bit,
    _interpolator_force_original_root_replacement_bit,

    k_interpolator_flags_count
};

/* ---------- definitions */

struct real_orientation;

class c_interpolator_control
{
public:
    c_interpolator_control();
    c_interpolator_control(c_interpolator_control const & other);

    void set_status(bool forward, float duration_seconds, bool animated_source, bool force_original_root_replacement);
    void set_interpolation_type(c_enum<e_interpolation_type, unsigned short, k_linear_interpolation, k_total_interpolation_control_types> interpolation_type);
    void pause_update(bool pause);
    void disable();
    bool update();
    bool enabled() const;
    bool finished() const;
    bool interpolating_forward() const;
    bool active() const;
    bool animated_source() const;
    bool paused() const;
    bool force_original_root_replacement() const;
    float get_ratio() const;
    float get_time_remaining() const;
    void interpolate_node_orientations(long node_count, c_big_flags_typed_no_init<long, 256> const * node_mask, real_orientation const * original_node_orientations, real_orientation * target_node_orientations) const;
    void approximate_interpolate_node_orientations(long node_count, c_big_flags_typed_no_init<long, 256> const * node_mask, real_orientation const * original_node_orientations, real_orientation * target_node_orientations) const;

private:
    float m_seconds_elapsed; // 0x0
    float m_seconds_total; // 0x4
    c_enum<e_interpolation_type, unsigned short, k_linear_interpolation, k_total_interpolation_control_types> m_interpolation_type; // 0x8
    c_flags<e_interpolator_flags, unsigned short, k_interpolator_flags_count> m_flags; // 0xA
};
static_assert(sizeof(c_interpolator_control) == 0xC, "c_interpolator_control");

/* ---------- prototypes */

/* ---------- globals */

extern float const k_standard_interpolation_time;

/* ---------- public code */

#endif // __ANIMATION_INTERPOLATION_H__
