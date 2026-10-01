#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\mixing_board\\channels\\auxilary_channel.cpp"
/* ---------- headers */

#include "omaha\animations\mixing_board\channels\auxilary_channel.h"
#include "omaha\animations\animation_definitions.h"
#include "omaha\math\real_math.h"
#include "omaha\profiler\profiler.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_auxilary_channel::c_auxilary_channel(void);
// public: c_auxilary_channel::~c_auxilary_channel(void);
// public: void c_auxilary_channel::initialize(void);
// public: void c_auxilary_channel::reset(void);
// public: void c_auxilary_channel::set_frame_time_to_last_frame(void);
// public: void c_auxilary_channel::set_frame_position(float);
// public: void c_auxilary_channel::set_frame_position_from_authored_time(float);
// public: void c_auxilary_channel::set_frame_position_from_playback_ratio(float);
// public: float c_auxilary_channel::get_playback_ratio(void) const;
// public: float c_auxilary_channel::get_authored_time(void) const;
// public: void c_auxilary_channel::append_debug_string(char const *, char const *, char *, int) const;
// public: float c_auxilary_channel::get_frame_time(void) const;
// public: void c_auxilary_channel::apply_node_orientations(struct render_model_definition const *, float, class c_big_flags_typed_no_init<long, 256> const *, long, struct real_orientation *, void (*)(long, class c_model_animation_graph const *, class c_animation_id, unsigned long const *, float), long);
// public: void c_auxilary_channel::get_channel_settings(class c_auxilary_channel_settings *) const;
// private: bool c_auxilary_channel::setup_channel(class c_auxilary_channel_settings const *);

c_auxilary_channel::c_auxilary_channel()
{
    mangled_ppc("??0c_auxilary_channel@@QAA@XZ");

    initialize();
};

c_auxilary_channel::~c_auxilary_channel()
{
    mangled_ppc("??1c_auxilary_channel@@QAA@XZ");

    initialize();
};

void c_auxilary_channel::initialize()
{
    mangled_ppc("?initialize@c_auxilary_channel@@QAAXXZ");

    c_channel_base::initialize();
    m_frame_time = 0.0f;
};

void c_auxilary_channel::reset()
{
    mangled_ppc("?reset@c_auxilary_channel@@QAAXXZ");

    c_channel_base::reset();
    m_frame_time = 0.0f;
};

void c_auxilary_channel::set_frame_time_to_last_frame()
{
    mangled_ppc("?set_frame_time_to_last_frame@c_auxilary_channel@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(41, valid());

    c_model_animation const * animation = get_animation();
    assert_tag_debug_untracked_jul_11_2011(44, animation);

    m_frame_time = animation->get_frame_position_from_playback_ratio(1.0f);
};

void c_auxilary_channel::set_frame_position(float frame_time)
{
    mangled_ppc("?set_frame_position@c_auxilary_channel@@QAAXM@Z");

    assert_tag_debug_untracked_jul_11_2011(51, valid());

    c_model_animation const * animation = get_animation();
    assert_tag_debug_untracked_jul_11_2011(54, animation);

    m_frame_time = int_pin(frame_time, 0.0f, animation->get_frame_count() - k_real_epsilon);
};

void c_auxilary_channel::set_frame_position_from_authored_time(float animation_time)
{
    mangled_ppc("?set_frame_position_from_authored_time@c_auxilary_channel@@QAAXM@Z");

    assert_tag_debug_untracked_jul_11_2011(62, valid());
    set_frame_position(animation_time * k_animation_frames_per_second);
};

void c_auxilary_channel::set_frame_position_from_playback_ratio(float playback_ratio)
{
    mangled_ppc("?set_frame_position_from_playback_ratio@c_auxilary_channel@@QAAXM@Z");

    assert_tag_debug_untracked_jul_11_2011(70, valid());

    c_model_animation const * animation = get_animation();
    assert_tag_debug_untracked_jul_11_2011(73, animation);

    float frame_time = animation->get_frame_position_from_playback_ratio(playback_ratio);
    set_frame_position(frame_time);
};

float c_auxilary_channel::get_playback_ratio() const
{
    mangled_ppc("?get_playback_ratio@c_auxilary_channel@@QBAMXZ");

    float result = 0.0f;
    if (valid())
    {
        c_model_animation const * animation = get_animation();
        assert_tag_debug_untracked_jul_11_2011(89, animation);

        float frame_count = animation->get_frame_count();
        if (frame_count > 0.0f)
        {
            result = m_frame_time / frame_count;
            result = PIN(result, 0.0f, 1.0f);
        }
    }

    return result;
};

float c_auxilary_channel::get_authored_time() const
{
    mangled_ppc("?get_authored_time@c_auxilary_channel@@QBAMXZ");

    return convert_animation_frame_value_to_time_signature(m_frame_time, c_channel_base::get_authored_rate());
};

void c_auxilary_channel::append_debug_string(char const * prefix, char const * suffix, char * debug_string, int string_size) const
{
    mangled_ppc("?append_debug_string@c_auxilary_channel@@QBAXPBD0PADH@Z");

    if (valid())
    {
        c_model_animation const * current_animation = get_animation();
        csnzappendf(debug_string, string_size, "%s= %s (%.02f) %s", prefix, current_animation->get_name_string(), get_frame_time(), suffix);
    }
};

float c_auxilary_channel::get_frame_time() const
{
    mangled_ppc("?get_frame_time@c_auxilary_channel@@QBAMXZ");

    return m_frame_time;
};

void c_auxilary_channel::apply_node_orientations(render_model_definition const * model, float weight, c_big_flags_typed_no_init<long, 256> const * node_mask, long node_orientations_count, real_orientation * out_node_orientations, void (*profile_callback)(long, c_model_animation_graph const *, c_animation_id, unsigned long const *, float), long profile_user_data)
{
    mangled_ppc("?apply_node_orientations@c_auxilary_channel@@QAAXPBUrender_model_definition@@MPBV?$c_big_flags_typed_no_init@J$0BAA@@@JPAUreal_orientation@@P6AXJPBVc_model_animation_graph@@Vc_animation_id@@PBKM@ZJ@Z");

    PROFILER_SCOPE_BEGIN_CATEGORY(133, aux_channel_apply_orientations, 2, profile_instance);

    if (valid())
    {
        if (!get_playback_flags().test(_animation_playback_acceleration_screen_bit) || fabs(get_playback_ratio() - 0.5f) >= k_real_epsilon)
        {
            internal_apply_weighted_node_orientations(get_animation_id(), m_frame_time, model, weight, node_mask, node_orientations_count, out_node_orientations, profile_callback, profile_user_data, false);
        }
    }
};

void c_auxilary_channel::get_channel_settings(c_auxilary_channel_settings * settings) const
{
    mangled_ppc("?get_channel_settings@c_auxilary_channel@@QBAXPAVc_auxilary_channel_settings@@@Z");

    assert_tag_debug_untracked_jul_11_2011(158, settings);
    get_base_channel_settings(settings);
    settings->frame_position = m_frame_time;
};

bool c_auxilary_channel::setup_channel(c_auxilary_channel_settings const * settings)
{
    mangled_ppc("?setup_channel@c_auxilary_channel@@AAA_NPBVc_auxilary_channel_settings@@@Z");

    assert_tag_debug_untracked_jul_11_2011(166, initialized());
    assert_tag_debug_untracked_jul_11_2011(167, settings);

    reset();

    if (setup_channel_base(settings))
    {
        m_frame_time = settings->frame_position;
    }

    return valid();
};

