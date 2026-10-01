/* ---------- headers */

#include "omaha\sound\sound_preferences.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\game_sound_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_half_circle = k_pi;
static float oo_speed_of_sound = 1.0f / k_speed_of_sound * 1000.0f;

static s_sound_preferences default_sound_preferences =
{
    {
        42, // _sound_channel_source_mono
        42, // _sound_channel_source_stereo
        21, // _sound_channel_source_quad
        14, // _sound_channel_source_5_dot_1
        0, // _sound_channel_source_codec
    }, // physical_source_counts
    {
        36, // _sound_channel_source_mono
        36, // _sound_channel_source_stereo
        18, // _sound_channel_source_quad
        12, // _sound_channel_source_5_dot_1
        0, // _sound_channel_source_codec
    }, // virtual_source_counts
    128, // physical_3d_voice_count
    k_speed_of_sound, // speed_of_sound
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void read_sound_preferences(struct s_sound_preferences const **);
// void write_sound_preferences(void);

// $TODO nonmatching: relocation only (the target references default_sound_preferences without a symbol)
void read_sound_preferences(s_sound_preferences const ** preferences)
{
    mangled_ppc("?read_sound_preferences@@YAXPAPBUs_sound_preferences@@@Z");

    *preferences = &default_sound_preferences;
};

void write_sound_preferences()
{
    mangled_ppc("?write_sound_preferences@@YAXXZ");
};
