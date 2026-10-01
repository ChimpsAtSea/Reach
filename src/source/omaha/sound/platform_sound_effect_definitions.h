#pragma once
#ifndef __PLATFORM_SOUND_EFFECT_DEFINITIONS_H__
#define __PLATFORM_SOUND_EFFECT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\sound\game_sound_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SOUND_EFFECT_COLLECTION_TAG = 'sfx+',
};

// platform_sound_playback_component_flags string list
enum e_platform_sound_playback_component_flag_bits
{
    _platform_sound_playback_component_dont_play_at_start_bit = 0,
    _platform_sound_playback_component_play_on_stop_bit,
    _platform_sound_playback_component_play_alternate_bit,
    _platform_sound_playback_component_sync_with_origin_looping_sound_bit,

    k_platform_sound_playback_component_flag_bits_count
};

/* ---------- definitions */

// Reach layout from platform_sound_playback_component_block_struct (tag json), size 0x18
struct s_platform_sound_playback_component_definition
{
    s_tag_reference sound; // 0x0
    real_decibel gain; // 0x10
    c_flags_no_init<e_platform_sound_playback_component_flag_bits, unsigned long, k_platform_sound_playback_component_flag_bits_count> flags; // 0x14
};
static_assert(sizeof(s_platform_sound_playback_component_definition) == 0x18, "s_platform_sound_playback_component_definition");

// old (v0) component, flags read raw by c_platform_sound_playback_vtable::fixup_old_struct_proc
struct s_platform_sound_playback_component_definition_v0
{
    s_tag_reference sound; // 0x0
    real_decibel gain; // 0x10
    unsigned long flags; // 0x14
};
static_assert(sizeof(s_platform_sound_playback_component_definition_v0) == 0x18, "s_platform_sound_playback_component_definition_v0");

// $TODO old (v0) layout only partially known from c_platform_sound_playback_vtable::fixup_old_struct_proc
struct s_platform_sound_playback_effect_definition_v0
{
    unsigned char unknown0[0x10]; // 0x0
    s_tag_block sound_components; // 0x10 (s_platform_sound_playback_component_definition_v0)
    unsigned char unknown1C[0x2C]; // 0x1C
};
static_assert(sizeof(s_platform_sound_playback_effect_definition_v0) == 0x48, "s_platform_sound_playback_effect_definition_v0");

struct s_platform_sound_playback_definition_v0
{
    s_tag_block sound_effects; // 0x0 (s_platform_sound_playback_effect_definition_v0)
};
static_assert(sizeof(s_platform_sound_playback_definition_v0) == 0xC, "s_platform_sound_playback_definition_v0");

// Reach layout from platform_sound_playback_struct (tag json), size 0x2C
struct s_platform_sound_playback_definition
{
    unsigned long flags; // 0x0
    s_tag_reference radio_effect; // 0x4
    s_tag_block lowpass_effect; // 0x14
    s_tag_block sound_components; // 0x20
};
static_assert(sizeof(s_platform_sound_playback_definition) == 0x2C, "s_platform_sound_playback_definition");

struct s_platform_sound_playback_named_definition
{
    long name; // 0x0
    s_platform_sound_playback_definition playback; // 0x4
};
static_assert(sizeof(s_platform_sound_playback_named_definition) == 0x30, "s_platform_sound_playback_named_definition");

struct s_platform_sound_playback_collection
{
    s_tag_block playback_collection; // 0x0
};
static_assert(sizeof(s_platform_sound_playback_collection) == 0xC, "s_platform_sound_playback_collection");

// Reach: 3 inputs (H3 had c_static_array<float, 4> inputs + local_position); element meanings from
// game_sound_player_effects_update: [0] scale, [1] time elapsed, [2] time since stop requested
struct s_platform_sound_effect_input_parameters
{
    float inputs[3]; // 0x0
};
static_assert(sizeof(s_platform_sound_effect_input_parameters) == 0xC, "s_platform_sound_effect_input_parameters");

class c_platform_sound_playback_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static s_tag_struct_definition * get_fixup_source_definition_proc(void);
    static bool fixup_old_struct_proc(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap);
};

/* ---------- prototypes */

/* ---------- globals */

extern s_tag_struct_definition platform_sound_playback_struct_v0;
extern c_tag_struct_vtable<c_platform_sound_playback_vtable> platform_sound_playback_struct_struct_vtable;

/* ---------- public code */

#endif // __PLATFORM_SOUND_EFFECT_DEFINITIONS_H__

