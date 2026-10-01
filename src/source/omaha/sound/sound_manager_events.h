#pragma once
#ifndef __SOUND_MANAGER_EVENTS_H__
#define __SOUND_MANAGER_EVENTS_H__

/* ---------- headers */

/* ---------- constants */

enum sound_manager_event_type
{
    _sound_event_stopped = 0,
    _sound_event_started,
    _sound_event_suppressed,
    k_number_of_sound_event_types
};

enum e_sound_event_stop_reason
{
    _sound_stopped_unknown = 0,
    _sound_stopped_scripting,
    _sound_stopped_ended,
    _sound_stopped_refresh_stopped,
    _sound_stopped_fade_out,
    _sound_stopped_too_many_same_attached_to_object,
    _sound_stopped_too_many_same_class_attached_to_object,
    _sound_stopped_too_many_same_class_attached_to_object_and_too_many_same_playing,
    _sound_stopped_too_many_same_playing,
    _sound_stopped_too_many_same_class_playing,
    _sound_stopped_no_free_channel,
    _sound_stopped_killed_by_loop,
    _sound_stopped_preempted_less_important,
    _sound_stopped_all,
    _sound_stopped_dialogue_game_over,
    _sound_stopped_dialogue_game_over_to_player,
    _sound_stopped_preempted_speech,
    _sound_stopped_preempted_speech_and_too_many_same_playing,
    _sound_stopped_not_cached,
    _sound_stopped_promotion_suppressed,
    _sound_stopped_not_valid_for_platform,
    _sound_stopped_mismatched_format_for_loop,
    _sound_stopped_unplayable,
    _sound_stopped_failed_to_initiate_read,
    _sound_stopped_cinematic_skipped,
    k_number_of_sound_stop_reasons
};

/* ---------- definitions */

struct s_sound_permutation;

/* ---------- prototypes */

void sound_manager_event_fire(long sound_definition_index, s_sound_permutation const * permutation, short chunk_index, sound_manager_event_type event_type, long event_reason);

/* ---------- globals */

extern char const * k_suppressed_sound_reasons[7];
extern char const * k_stopped_sound_reasons[k_number_of_sound_stop_reasons];
extern char const * k_started_sound_reasons[4];

/* ---------- public code */

#endif // __SOUND_MANAGER_EVENTS_H__

