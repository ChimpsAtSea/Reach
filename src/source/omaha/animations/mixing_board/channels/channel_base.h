#ifndef __CHANNEL_BASE_H__
#define __CHANNEL_BASE_H__
#pragma once

/* ---------- headers */

#include "omaha\animations\animation_constants.h"
#include "omaha\animations\animation_id.h"
#include "omaha\animations\mixing_board\mixing_board_slider.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct render_model_definition;
struct real_orientation;
union real_point3d;

class c_animation_data;
class c_model_animation;
class c_model_animation_graph;

// Reach layout per c_channel_base::get_base_channel_settings / setup_channel_base (channel_base.obj)
class c_base_channel_settings
{
public:
    long graph_index; // 0x0
    long impulse_name; // 0x4
    c_animation_id primary_animation_id; // 0x8
    c_animation_playback_flags playback_flags; // 0xC
    c_animation_graph_location graph_location; // 0x10
};
static_assert(sizeof(c_base_channel_settings) == 0x14, "c_base_channel_settings");

// Reach layout per channel_base.obj (reset / initialize / set_parent_slider)
class c_channel_base
{
public:
    c_channel_base();
    ~c_channel_base();

    void initialize();
    void reset();
    bool initialized() const;
    bool valid() const;
    c_model_animation const * get_animation() const;
    c_model_animation * get_writable_animation();
    c_animation_id get_animation_id() const;
    c_animation_playback_flags const & get_playback_flags() const;
    long get_node_count() const;
    long get_frame_count() const;
    float get_authored_duration() const;
    static float get_authored_rate();
    c_model_animation_graph const * get_graph() const;
    c_model_animation_graph * get_writable_graph();
    void get_base_channel_settings(c_base_channel_settings * settings) const;
    void append_debug_string(char const * prefix, char const * suffix, char * debug_string, int string_size) const;
    void set_parent_slider(long index, e_mixing_board_parent_slider_type slider_type);

protected:
    void set_animation_id(c_animation_id animation_id);
    bool setup_channel_base(c_base_channel_settings const * settings);
    void internal_apply_weighted_node_orientations(c_animation_id animation_id, float frame_index, render_model_definition const * model, float weight, c_big_flags_typed_no_init<long, 256> const * node_mask, long node_orientations_count, real_orientation * out_node_orientations, void (*profile_callback)(long, c_model_animation_graph const *, c_animation_id, unsigned long const *, float), long profile_user_data, bool force_subframe_interpolation);

    long m_graph_index; // 0x0
    long m_impulse_name; // 0x4
    c_animation_id m_animation_id; // 0x8
    c_animation_playback_flags m_playback_flags; // 0xC
    c_animation_graph_location m_graph_location; // 0x10
    c_mixing_board_slider m_slider; // 0x12 $TODO name
    char m_initialized; // 0x1E
};
static_assert(sizeof(c_channel_base) == 0x20, "c_channel_base");

/* ---------- prototypes */

/* ---------- globals */

// internal-linkage copy per TU (auxilary_channel.obj reads its own .rdata copy)
static float const k_animation_frames_per_second = 30.0f;

/* ---------- public code */

#endif // __CHANNEL_BASE_H__

