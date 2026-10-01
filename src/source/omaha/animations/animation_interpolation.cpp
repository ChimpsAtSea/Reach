#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\animation_interpolation.cpp"
/* ---------- headers */

#include "omaha\animations\animation_interpolation.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game_time.h"
#include "omaha\math\real_math.h"

#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

float const k_standard_interpolation_time = 8.0f / 30.0f;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// float const k_standard_interpolation_time; // "?k_standard_interpolation_time@@3MB"

// public: c_interpolator_control::c_interpolator_control(void);
// public: c_interpolator_control::c_interpolator_control(class c_interpolator_control const &);
// public: void c_interpolator_control::set_status(bool, float, bool, bool);
// public: void c_interpolator_control::set_interpolation_type(class c_enum<enum e_interpolation_type, unsigned short, 0, 5, struct s_default_enum_string_resolver>);
// public: void c_interpolator_control::pause_update(bool);
// public: void c_interpolator_control::disable(void);
// public: bool c_interpolator_control::update(void);
// public: bool c_interpolator_control::enabled(void) const;
// public: bool c_interpolator_control::finished(void) const;
// public: bool c_interpolator_control::interpolating_forward(void) const;
// public: bool c_interpolator_control::active(void) const;
// public: bool c_interpolator_control::animated_source(void) const;
// public: bool c_interpolator_control::paused(void) const;
// public: bool c_interpolator_control::force_original_root_replacement(void) const;
// public: float c_interpolator_control::get_ratio(void) const;
// public: float c_interpolator_control::get_time_remaining(void) const;
// public: void c_interpolator_control::interpolate_node_orientations(long, class c_big_flags_typed_no_init<long, 256> const *, struct real_orientation const *, struct real_orientation *) const;
// public: void c_interpolator_control::approximate_interpolate_node_orientations(long, class c_big_flags_typed_no_init<long, 256> const *, struct real_orientation const *, struct real_orientation *) const;
// public: c_enum<enum e_interpolation_type, unsigned short, 0, 5, struct s_default_enum_string_resolver>::c_enum<enum e_interpolation_type, unsigned short, 0, 5, struct s_default_enum_string_resolver>(void);
// public: enum e_interpolation_type c_enum_no_init<enum e_interpolation_type, unsigned short, 0, 5, struct s_default_enum_string_resolver>::operator enum e_interpolation_type(void) const;
// public: void c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::test(enum e_interpolator_flags) const;
// public: void c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::set(enum e_interpolator_flags, bool);
// public: c_flags<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::c_flags<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>(void);
// public: bool c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::is_clear(void) const;
// public: static bool c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::valid_bit(enum e_interpolator_flags);
// private: static unsigned short c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::flag_size_type(enum e_interpolator_flags);
// private: static unsigned short c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned short c_flags_no_init<enum e_interpolator_flags, unsigned short, 5, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_interpolator_flags);

c_interpolator_control::c_interpolator_control() :
    m_seconds_elapsed(0.0f),
    m_seconds_total(0.0f),
    m_interpolation_type(),
    m_flags()
{
    mangled_ppc("??0c_interpolator_control@@QAA@XZ");

    m_interpolation_type = k_linear_interpolation;
    m_flags.clear();
};

c_interpolator_control::c_interpolator_control(c_interpolator_control const & other) :
    m_seconds_elapsed(other.m_seconds_elapsed),
    m_seconds_total(other.m_seconds_total),
    m_interpolation_type(other.m_interpolation_type),
    m_flags(other.m_flags)
{
    mangled_ppc("??0c_interpolator_control@@QAA@ABV0@@Z");
};

void c_interpolator_control::set_status(bool forward, float duration_seconds, bool animated_source, bool force_original_root_replacement)
{
    mangled_ppc("?set_status@c_interpolator_control@@QAAX_NM00@Z");

    if (duration_seconds > k_real_epsilon)
    {
        if (!enabled() || forward != interpolating_forward() || !realcmp(duration_seconds, m_seconds_total))
        {
            float seconds_elapsed = forward ? 0.0f : duration_seconds;
            if (enabled())
            {
                float current_ratio = get_ratio();
                seconds_elapsed = duration_seconds * current_ratio;
            }

            m_seconds_elapsed = seconds_elapsed;
            m_seconds_total = duration_seconds;
            m_flags.clear();
            m_flags.set(_interpolator_forward_bit, forward);
            m_flags.set(_interpolator_animated_source_bit, animated_source);
            m_flags.set(_interpolator_force_original_root_replacement_bit, force_original_root_replacement);

            if (!update())
            {
                disable();
            }
        }
    }
    else
    {
        disable();
    }
};

void c_interpolator_control::set_interpolation_type(c_enum<e_interpolation_type, unsigned short, k_linear_interpolation, k_total_interpolation_control_types> interpolation_type)
{
    mangled_ppc("?set_interpolation_type@c_interpolator_control@@QAAXV?$c_enum@W4e_interpolation_type@@G$0A@$04Us_default_enum_string_resolver@@@@@Z");

    m_interpolation_type = interpolation_type;
};

void c_interpolator_control::pause_update(bool pause)
{
    mangled_ppc("?pause_update@c_interpolator_control@@QAAX_N@Z");

    m_flags.set(_interpolator_paused_bit, pause);
};

void c_interpolator_control::disable()
{
    mangled_ppc("?disable@c_interpolator_control@@QAAXXZ");

    m_seconds_elapsed = 0.0f;
    m_seconds_total = 0.0f;
    m_flags.clear();
};

bool c_interpolator_control::update()
{
    mangled_ppc("?update@c_interpolator_control@@QAA_NXZ");

    bool awake = false;
    if (active() && !paused())
    {
        if (m_flags.test(_interpolator_forward_bit))
        {
            m_seconds_elapsed += game_tick_length();
            if (m_seconds_elapsed >= m_seconds_total - k_real_epsilon)
            {
                m_seconds_elapsed = m_seconds_total;
                m_flags.set(_interpolator_finished_bit, true);
            }
        }
        else
        {
            m_seconds_elapsed -= game_tick_length();
            if (m_seconds_elapsed <= k_real_epsilon)
            {
                m_seconds_elapsed = 0.0f;
                m_flags.set(_interpolator_finished_bit, true);
            }
        }

        awake = true;
    }

    return awake;
};

bool c_interpolator_control::enabled() const
{
    mangled_ppc("?enabled@c_interpolator_control@@QBA_NXZ");

    return m_seconds_total != 0.0f;
};

bool c_interpolator_control::finished() const
{
    mangled_ppc("?finished@c_interpolator_control@@QBA_NXZ");

    return m_flags.test(_interpolator_finished_bit);
};

bool c_interpolator_control::interpolating_forward() const
{
    mangled_ppc("?interpolating_forward@c_interpolator_control@@QBA_NXZ");

    return m_flags.test(_interpolator_forward_bit);
};

bool c_interpolator_control::active() const
{
    mangled_ppc("?active@c_interpolator_control@@QBA_NXZ");

    return enabled() && !finished();
};

bool c_interpolator_control::animated_source() const
{
    mangled_ppc("?animated_source@c_interpolator_control@@QBA_NXZ");

    return m_flags.test(_interpolator_animated_source_bit);
};

bool c_interpolator_control::paused() const
{
    mangled_ppc("?paused@c_interpolator_control@@QBA_NXZ");

    return m_flags.test(_interpolator_paused_bit);
};

bool c_interpolator_control::force_original_root_replacement() const
{
    mangled_ppc("?force_original_root_replacement@c_interpolator_control@@QBA_NXZ");

    return m_flags.test(_interpolator_force_original_root_replacement_bit);
};

float c_interpolator_control::get_ratio() const
{
    mangled_ppc("?get_ratio@c_interpolator_control@@QBAMXZ");

    float ratio = 0.0f;
    if (enabled())
    {
        ratio = m_seconds_total > k_real_epsilon ? m_seconds_elapsed / m_seconds_total : 0.0f;

        switch (m_interpolation_type)
        {
        case k_light_ease_in_out_interpolation:
        {
            ratio = ease_in_ease_out(ratio);
        }
        break;
        case k_heavy_ease_in_out_interpolation:
        {
            ratio = ease_in_ease_out_heavy(ratio);
        }
        break;
        case k_light_deceleration_interpolation:
        {
            ratio = 1.0f - (ratio - 1.0f) * (ratio - 1.0f);
        }
        break;
        case k_heavy_deceleration_interpolation:
        {
            ratio = 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
        }
        break;
        }

        ratio = MIN(MAX(ratio, 0.0f), 1.0f);
    }

    return ratio;
};

float c_interpolator_control::get_time_remaining() const
{
    mangled_ppc("?get_time_remaining@c_interpolator_control@@QBAMXZ");

    float time_remaining = 0.0f;
    if (enabled())
    {
        if (m_flags.test(_interpolator_forward_bit))
        {
            time_remaining = m_seconds_total - m_seconds_elapsed;
        }
        else
        {
            time_remaining = m_seconds_elapsed;
        }
    }

    return time_remaining;
};

void c_interpolator_control::interpolate_node_orientations(long node_count, c_big_flags_typed_no_init<long, 256> const * node_mask, real_orientation const * original_node_orientations, real_orientation * target_node_orientations) const
{
    mangled_ppc("?interpolate_node_orientations@c_interpolator_control@@QBAXJPBV?$c_big_flags_typed_no_init@J$0BAA@@@PBUreal_orientation@@PAU3@@Z");

    if (enabled())
    {
        float ratio = get_ratio();
        if (fabs(ratio - 1.0f) >= k_real_epsilon)
        {
            for (short node_index = 0; node_index < node_count; node_index++)
            {
                if (node_mask == NULL || node_mask->test(node_index))
                {
                    orientations_interpolate(original_node_orientations, target_node_orientations, ratio, target_node_orientations);
                }

                original_node_orientations++;
                target_node_orientations++;
            }
        }
    }
};

void c_interpolator_control::approximate_interpolate_node_orientations(long node_count, c_big_flags_typed_no_init<long, 256> const * node_mask, real_orientation const * original_node_orientations, real_orientation * target_node_orientations) const
{
    mangled_ppc("?approximate_interpolate_node_orientations@c_interpolator_control@@QBAXJPBV?$c_big_flags_typed_no_init@J$0BAA@@@PBUreal_orientation@@PAU3@@Z");

    if (false)
    {
        float ratio = get_ratio();
        for (short node_index = 0; node_index < node_count; node_index++)
        {
            if (node_mask == NULL || node_mask->test(node_index))
            {
                approximate_orientations_interpolate(original_node_orientations, target_node_orientations, ratio, target_node_orientations);
            }

            original_node_orientations++;
            target_node_orientations++;
        }
    }
};
