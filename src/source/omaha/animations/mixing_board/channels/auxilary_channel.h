#pragma once
#ifndef __AUXILARY_CHANNEL_H__
#define __AUXILARY_CHANNEL_H__

/* ---------- headers */

#include "omaha\animations\mixing_board\channels\channel_base.h"

/* ---------- constants */

/* ---------- definitions */

class c_auxilary_channel_settings : public c_base_channel_settings
{
public:
    float frame_position; // 0x14
};
static_assert(sizeof(c_auxilary_channel_settings) == 0x18, "c_auxilary_channel_settings");

class c_auxilary_channel : public c_channel_base
{
public:
    c_auxilary_channel();
    ~c_auxilary_channel();

    void initialize();
    void reset();
    void set_frame_time_to_last_frame();
    void set_frame_position(float frame_time);
    void set_frame_position_from_authored_time(float animation_time);
    void set_frame_position_from_playback_ratio(float playback_ratio);
    float get_playback_ratio() const;
    float get_authored_time() const;
    void append_debug_string(char const * prefix, char const * suffix, char * debug_string, int string_size) const;
    float get_frame_time() const;
    void apply_node_orientations(render_model_definition const * model, float weight, c_big_flags_typed_no_init<long, 256> const * node_mask, long node_orientations_count, real_orientation * out_node_orientations, void (*profile_callback)(long, c_model_animation_graph const *, c_animation_id, unsigned long const *, float), long profile_user_data);
    void get_channel_settings(c_auxilary_channel_settings * settings) const;

private:
    bool setup_channel(c_auxilary_channel_settings const * settings);

    float m_frame_time; // 0x20
};
static_assert(sizeof(c_auxilary_channel) == 0x24, "c_auxilary_channel");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __AUXILARY_CHANNEL_H__

