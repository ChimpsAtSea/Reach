/* ---------- headers */

#include "omaha\profiler\profiler_summary.h"
#include "foundation\baselib\errors\output\output_globals.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const profile_dump_directory = "profiling";
char const * k_profile_summary_names[k_profile_summary_count] =
{
    "all",
    "objects",
    "object memory",
    "graphics",
    "occlusion",
    "effects",
    "ai",
    "game-state",
    "environment artist"
};
e_profile_summary_objects_mode profile_summary_objects_profile_mode = _profile_summary_objects_mode_detailed;
bool profile_summary_effects_enabled = true;
bool profile_summary_ai_enabled = true;
bool profile_summary_enabled;
bool profile_summary_graphics_enabled;
bool profile_summary_occlusion_enabled;
bool profile_summary_environment_artist_enabled;
e_profile_summary_modes g_profile_summary_mode;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const profile_dump_directory; // "?profile_dump_directory@@3PBDB"
// char const **k_profile_summary_names; // "?k_profile_summary_names@@3PAPBDA"
// enum e_profile_summary_objects_mode profile_summary_objects_profile_mode; // "?profile_summary_objects_profile_mode@@3W4e_profile_summary_objects_mode@@A"
// bool profile_summary_effects_enabled; // "?profile_summary_effects_enabled@@3_NA"
// bool profile_summary_ai_enabled; // "?profile_summary_ai_enabled@@3_NA"
// bool profile_summary_enabled; // "?profile_summary_enabled@@3_NA"
// bool profile_summary_graphics_enabled; // "?profile_summary_graphics_enabled@@3_NA"
// bool profile_summary_occlusion_enabled; // "?profile_summary_occlusion_enabled@@3_NA"
// bool profile_summary_environment_artist_enabled; // "?profile_summary_environment_artist_enabled@@3_NA"
// enum e_profile_summary_modes g_profile_summary_mode; // "?g_profile_summary_mode@@3W4e_profile_summary_modes@@A"

// void profile_summary_cycle(void);

void profile_summary_cycle(void)
{
    mangled_ppc("?profile_summary_cycle@@YAXXZ");

    if (!profile_summary_enabled)
    {
        profile_summary_enabled = true;
        g_profile_summary_mode = k_profile_summary_first;
    }
    else
    {
        g_profile_summary_mode = static_cast<e_profile_summary_modes>(g_profile_summary_mode + 1);
    }

    switch (g_profile_summary_mode)
    {
    case _profile_summary_all:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_detailed;
        profile_summary_graphics_enabled = true;
        profile_summary_occlusion_enabled = true;
        profile_summary_effects_enabled = true;
        profile_summary_ai_enabled = true;
        break;
    case _profile_summary_objects:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_detailed;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = false;
        break;
    case _profile_summary_object_memory:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_brief;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = false;
        break;
    case _profile_summary_graphics:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_none;
        profile_summary_graphics_enabled = true;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = false;
        break;
    case _profile_summary_occlusion:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_none;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = true;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = false;
        break;
    case _profile_summary_effects:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_brief;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = true;
        profile_summary_ai_enabled = false;
        break;
    case _profile_summary_ai:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_brief;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = true;
        break;
    case _profile_summary_game_state:
        profile_summary_environment_artist_enabled = false;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_brief;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = true;
        break;
    case _profile_summary_environment_artist:
        profile_summary_environment_artist_enabled = true;
        profile_summary_objects_profile_mode = _profile_summary_objects_mode_brief;
        profile_summary_graphics_enabled = false;
        profile_summary_occlusion_enabled = false;
        profile_summary_effects_enabled = false;
        profile_summary_ai_enabled = false;
        break;
    default:
        profile_summary_enabled = false;
        break;
    }

    output_message("summary: %s", profile_summary_enabled ? k_profile_summary_names[g_profile_summary_mode] : "disabled");
};

