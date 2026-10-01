#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_manager_events.cpp"
/* ---------- headers */

#include "omaha\sound\sound_manager_events.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\system_time_xenon.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * k_suppressed_sound_reasons[7] =
{
    "no_failure",
    "skipped",
    "promotion_suppressed",
    "datum_new_failed",
    "silent",
    "spatialization_suppressed",
    "unknown"
};

char const * k_stopped_sound_reasons[k_number_of_sound_stop_reasons] =
{
    "unknown",
    "scripting",
    "ended",
    "refresh_stopped",
    "fade_out",
    "too_many_same_attached_to_object",
    "too_many_same_class_attached_to_object",
    "too_many_same_class_attached_to_object_and_too_many_same_playing",
    "too_many_same_playing",
    "too_many_same_class_playing",
    "no_free_channel",
    "killed_by_loop",
    "preempted_less_important",
    "all",
    "dialogue_game_over",
    "dialogue_game_over_to_player",
    "preempted_speech",
    "preempted_speech_and_too_many_same_playing",
    "not_cached",
    "promotion",
    "not_valid_for_platform",
    "wrong_format_for_loop",
    "not_playable_anymore",
    "io_failure",
    "cinematic_skipped"
};

char const * k_started_sound_reasons[4] =
{
    "nothing_special",
    "promoted",
    "delayed_for_cache",
    "new_loop"
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **k_suppressed_sound_reasons; // "?k_suppressed_sound_reasons@@3PAPBDA"
// char const **k_stopped_sound_reasons; // "?k_stopped_sound_reasons@@3PAPBDA"
// char const **k_started_sound_reasons; // "?k_started_sound_reasons@@3PAPBDA"

// void sound_manager_event_fire(long, struct s_sound_permutation const *, short, enum sound_manager_event_type, long);

void sound_manager_event_fire(long sound_definition_index, s_sound_permutation const * permutation, short chunk_index, sound_manager_event_type event_type, long event_reason)
{
    mangled_ppc("?sound_manager_event_fire@@YAXJPBUs_sound_permutation@@FW4sound_manager_event_type@@J@Z");

    switch (event_type)
    {
    case _sound_event_stopped:
    {
        if (event_reason != _sound_stopped_ended && event_reason != _sound_stopped_all)
        {
            assert_tag_debug_untracked_jul_11_2011(76, VALID_INDEX(event_reason, NUMBEROF(k_stopped_sound_reasons)));
            event_wrapped(_event_message, "sound:event:stop:[%08x] %s '%s:%s'", system_milliseconds(), k_stopped_sound_reasons[event_reason], tag_get_name(sound_definition_index), string_id_get_string_const(sound_permutation_get_name(static_cast<sound_definition const *>(tag_get(SOUND_TAG, sound_definition_index)), permutation)));
        }
    }
    break;
    case _sound_event_started:
    {
        assert_tag_debug_untracked_jul_11_2011(82, VALID_INDEX(event_reason, NUMBEROF(k_started_sound_reasons)));
        event_wrapped(_event_message, "sound:event:started:[%08x] %s '%s:%s'", system_milliseconds(), k_started_sound_reasons[event_reason], tag_get_name(sound_definition_index), string_id_get_string_const(sound_permutation_get_name(static_cast<sound_definition const *>(tag_get(SOUND_TAG, sound_definition_index)), permutation)));
    }
    break;
    case _sound_event_suppressed:
    {
        assert_tag_debug_untracked_jul_11_2011(87, VALID_INDEX(event_reason, NUMBEROF(k_suppressed_sound_reasons)));
        event_wrapped(_event_message, "sound:event:suppressed:[%08x] %s '%s'", system_milliseconds(), k_suppressed_sound_reasons[event_reason], tag_get_name(sound_definition_index));
    }
    break;
    }
};
