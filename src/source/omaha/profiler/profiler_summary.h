#pragma once
#ifndef __PROFILER_SUMMARY_H__
#define __PROFILER_SUMMARY_H__

/* ---------- headers */

/* ---------- constants */

// names from k_profile_summary_names
enum e_profile_summary_modes
{
    _profile_summary_all = 0,
    _profile_summary_objects,
    _profile_summary_object_memory,
    _profile_summary_graphics,
    _profile_summary_occlusion,
    _profile_summary_effects,
    _profile_summary_ai,
    _profile_summary_game_state,
    _profile_summary_environment_artist,

    k_profile_summary_count,
    k_profile_summary_first = _profile_summary_all
};

// profile_summary_objects_display prints the detailed breakdown only for _detailed
enum e_profile_summary_objects_mode
{
    _profile_summary_objects_mode_none = 0,
    _profile_summary_objects_mode_brief,
    _profile_summary_objects_mode_detailed,

    k_profile_summary_objects_mode_count
};

/* ---------- definitions */

/* ---------- prototypes */

void profile_summary_cycle(void);

/* ---------- globals */

extern char const * const profile_dump_directory;
extern char const * k_profile_summary_names[k_profile_summary_count];
extern e_profile_summary_objects_mode profile_summary_objects_profile_mode;
extern bool profile_summary_effects_enabled;
extern bool profile_summary_ai_enabled;
extern bool profile_summary_enabled;
extern bool profile_summary_graphics_enabled;
extern bool profile_summary_occlusion_enabled;
extern bool profile_summary_environment_artist_enabled;
extern e_profile_summary_modes g_profile_summary_mode;

/* ---------- public code */

#endif // __PROFILER_SUMMARY_H__

