#pragma once
#ifndef __ANIMATION_DEFINITIONS_H__
#define __ANIMATION_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\animations\animation_id.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_resource_definition;

// filled from vehicle_suspension_block by c_model_animation_graph::find_next_vehicle_suspension
class suspension_animation_iterator
{
public:
    suspension_animation_iterator()
    {
        mangled_ppc("??0suspension_animation_iterator@@QAA@XZ");

        clear();
    }

    ~suspension_animation_iterator()
    {
        mangled_ppc("??1suspension_animation_iterator@@QAA@XZ");
    }

    void clear();

    long function_name; // 0x0
    long marker_name; // 0x4
    long contact_marker_name; // 0x8
    long region_name; // 0xC
    float offset; // 0x10
    float extension_distance; // 0x14
    float compression_distance; // 0x18
    float destroyed_offset; // 0x1C
    float destroyed_extension_distance; // 0x20
    float destroyed_compression_distance; // 0x24
    long suspension_index; // 0x28
    c_animation_id animation_id; // 0x2C
    short subgraph; // 0x30
    short index; // 0x32
};
static_assert(sizeof(suspension_animation_iterator) == 0x34, "suspension_animation_iterator");

// $TODO layout not reversed; methods called from auxilary_channel.obj
class c_model_animation
{
public:
    short get_frame_count() const; // f i (weapons.obj)
    float get_frame_position_from_playback_ratio(float playback_ratio) const; // animation.obj
    char const * get_name_string() const; // animation.obj
    long get_name() const;
};

/* ---------- prototypes */

extern float convert_animation_frame_value_to_time_signature(float frame_index, float frame_playback_rate);

/* ---------- globals */

extern s_tag_resource_definition model_animation_tag_resource;

/* ---------- public code */

#endif // __ANIMATION_DEFINITIONS_H__

