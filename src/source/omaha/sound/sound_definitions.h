#ifndef __SOUND_DEFINITIONS_H__
#define __SOUND_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

enum
{
    SOUND_TAG = 'snd!',
    SOUND_LOOPING_TAG = 'lsnd',
};

// Reach: c_flags_no_init<e_sound_playback_flag, unsigned long, 1> (postprocess_sound_scenery_definition); bit name unknown
enum e_sound_playback_flag
{
    _sound_playback_flag_bit0 = 0,

    k_sound_playback_flag_count
};

enum e_sound_compression
{
    _sound_compression_none_be = 0,
    _sound_compression_xbox_adpcm,
    _sound_compression_ima_adpcm,
    _sound_compression_none_le,
    _sound_compression_wma,
    _sound_compression_endian_agnostic,
    _sound_compression_xma,
    _sound_compression_xma2,
    NUMBER_OF_SOUND_COMPRESSION_TYPES
};

/* ---------- definitions */

struct s_tag_resource_definition;
struct s_platform_sound_playback_definition;
struct s_sound_permutation;
struct s_sound_permutation_chunk;

struct sound_definition;

// Reach layout from sound_distance_parameters_struct (tag json), size 0x20
struct s_sound_distance_parameters
{
    float dont_obstruct_distance; // 0x0
    float dont_play_distance; // 0x4
    float attack_distance; // 0x8
    float minimum_distance; // 0xC
    float sustain_begin_distance; // 0x10
    float sustain_end_distance; // 0x14
    float maximum_distance; // 0x18
    float sustain_db; // 0x1C
};
static_assert(sizeof(s_sound_distance_parameters) == 0x20, "s_sound_distance_parameters");

// Reach layout from sound_playback_parameters_struct (tag json), size 0x54
struct s_sound_definition_playback_parameters
{
    c_flags_no_init<e_sound_playback_flag, unsigned long, k_sound_playback_flag_count> internal_flags; // 0x0
    float skip_fraction; // 0x4
    float maximum_bend_per_second; // 0x8
    s_sound_distance_parameters distance_parameters; // 0xC
    float gain_base; // 0x2C
    float gain_variance; // 0x30
    short random_pitch_bounds[2]; // 0x34
    float inner_cone_angle; // 0x38
    float outer_cone_angle; // 0x3C
    float outer_cone_gain; // 0x40
    unsigned long flags; // 0x44
    float azimuth; // 0x48
    float positional_gain; // 0x4C
    float first_person_gain; // 0x50
};
static_assert(sizeof(s_sound_definition_playback_parameters) == 0x54, "s_sound_definition_playback_parameters");

// $TODO: only the leading fields are reversed; Reach layout from sound_block_struct (tag json), size 0xE0
struct sound_definition
{
    unsigned long flags; // 0x0
    unsigned long import_flags; // 0x4
    unsigned long xsync_flags; // 0x8
    char sound_class; // 0xC
    char sample_rate; // 0xD
    char override_xma_compression; // 0xE
    char import_type; // 0xF
    s_sound_definition_playback_parameters playback; // 0x10
    unsigned char unknown64[0xE0 - 0x64]; // 0x64

    e_sound_compression get_compression() const;
};
static_assert(sizeof(sound_definition) == 0xE0, "sound_definition");

// $TODO: only the fields up to loop_sound are named; Reach layout from looping_sound_track_block (tag json), size 0xB0
struct looping_sound_track
{
    long name; // 0x0
    unsigned short flags; // 0x4
    short output_effect; // 0x6
    float gain; // 0x8
    s_tag_reference start_sound; // 0xC
    s_tag_reference loop_sound; // 0x1C
    unsigned char unknown2C[0xB0 - 0x2C]; // 0x2C
};
static_assert(sizeof(looping_sound_track) == 0xB0, "looping_sound_track");

// Reach layout from sound_looping_struct_definition (tag json), size 0x38
struct looping_sound_definition
{
    unsigned long flags; // 0x0
    real_bounds marty_music_time; // 0x4
    real_bounds runtime_distance_bounds; // 0xC
    float maximum_flyby_range_distance; // 0x14
    short runtime_sound_class; // 0x18
    short pad1A; // 0x1A
    long master_marker_track; // 0x1C
    s_tag_block tracks; // 0x20
    s_tag_block detail_sounds; // 0x2C
};
static_assert(sizeof(looping_sound_definition) == 0x38, "looping_sound_definition");

// Reach layout from sound_globals_block (tag json), size 0x5C
struct s_sound_globals_definition
{
    s_tag_reference sound_classes_reference; // 0x0
    s_tag_reference sound_effect_collection_reference; // 0x10
    s_tag_reference sound_mix_reference; // 0x20
    s_tag_reference sound_combat_dialogue_constants_reference; // 0x30
    s_tag_reference sound_propagation_reference; // 0x40
    s_tag_block campaign_unspatialized_sounds; // 0x50
};
static_assert(sizeof(s_sound_globals_definition) == 0x5C, "s_sound_globals_definition");

/* ---------- prototypes */

s_platform_sound_playback_definition const * sound_definition_try_and_get_platform_playback(sound_definition const * sound);
s_sound_definition_playback_parameters const * sound_definition_get_playback_parameters(sound_definition const * sound);
long sound_permutation_get_name(sound_definition const * sound, s_sound_permutation const * permutation);
char const * sound_permutation_chunk_get_debug_name(s_sound_permutation_chunk * permutation);
long sound_permutation_chunk_get_debug_index(s_sound_permutation_chunk * permutation);

/* ---------- globals */

extern s_tag_resource_definition sound_resource_definition;
extern s_tag_resource_definition facial_animation_resource_definition;

/* ---------- public code */

#endif // __SOUND_DEFINITIONS_H__

