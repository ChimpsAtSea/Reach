#pragma once
#ifndef __SOUND_PREFERENCES_H__
#define __SOUND_PREFERENCES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_sound_channel_type
{
    _sound_channel_source_mono = 0,
    _sound_channel_source_stereo,
    _sound_channel_source_quad,
    _sound_channel_source_5_dot_1,
    _sound_channel_source_codec,

    k_number_of_sound_channel_source_types
};

/* ---------- definitions */

// Reach layout (default_sound_preferences data at 0x852CFB5C), size 0x1C
struct s_sound_preferences
{
    short physical_source_counts[k_number_of_sound_channel_source_types]; // 0x0
    short virtual_source_counts[k_number_of_sound_channel_source_types]; // 0xA
    short physical_3d_voice_count; // 0x14
    float speed_of_sound; // 0x18
};
static_assert(sizeof(s_sound_preferences) == 0x1C, "s_sound_preferences");

/* ---------- prototypes */

void read_sound_preferences(s_sound_preferences const ** preferences);
void write_sound_preferences();

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_PREFERENCES_H__
