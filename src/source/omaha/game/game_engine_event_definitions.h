#pragma once
#ifndef __GAME_ENGINE_EVENT_DEFINITIONS_H__
#define __GAME_ENGINE_EVENT_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

enum
{
    k_maximum_game_engine_event_responses = 1000,
};

// game_engine_event_audience_enum_definition
enum e_game_engine_event_audience
{
    _game_engine_event_audience_cause_player = 0,
    _game_engine_event_audience_cause_team,
    _game_engine_event_audience_effect_player,
    _game_engine_event_audience_effect_team,
    _game_engine_event_audience_all,

    k_number_of_game_engine_event_audiences
};

// game_engine_event_response_context_enum_definition
enum e_game_engine_event_response_context
{
    _game_engine_event_response_context_self = 0,
    _game_engine_event_response_context_friendly,
    _game_engine_event_response_context_enemy,
    _game_engine_event_response_context_neutral,

    k_number_of_game_engine_event_response_contexts
};

// game_engine_event_splitscreen_suppression_enum_definition
enum e_game_engine_event_splitscreen_suppression
{
    _game_engine_event_splitscreen_suppression_none = 0,
    _game_engine_event_splitscreen_suppression_audio,
    _game_engine_event_splitscreen_suppression_audio_if_overlapping,
    _game_engine_event_splitscreen_suppression_text,
    _game_engine_event_splitscreen_suppression_text_and_audio,

    k_number_of_game_engine_event_splitscreen_suppressions
};

// game_engine_event_flags_definition
enum e_game_engine_event_flags
{
    _game_engine_event_always_play_sound_bit = 0,
    _game_engine_event_always_play_sound_in_mp_bit,

    k_number_of_game_engine_event_flags
};

// game_engine_event_input_enum_definition
enum e_game_engine_event_input
{
    _game_engine_event_input_none = 0,
    _game_engine_event_input_cause_player,
    _game_engine_event_input_cause_team,
    _game_engine_event_input_effect_player,
    _game_engine_event_input_effect_team,

    k_number_of_game_engine_event_inputs
};

/* ---------- definitions */

// sound_response_definition_struct (Reach tag json)
struct s_game_engine_event_sound_response_definition
{
    unsigned char sound_flags; // 0x0
    unsigned char pad1[3]; // 0x1
    s_tag_reference sound; // 0x4
    real probability; // 0x14
};
static_assert(sizeof(s_game_engine_event_sound_response_definition) == 0x18, "s_game_engine_event_sound_response_definition");

// game_engine_event_block_v1 (upgraded by c_game_engine_event_block_vtable::fixup_old_struct_proc)
struct s_game_engine_event_response_definition_v1
{
    long name; // 0x0 string_id
    c_enum_no_init<e_game_engine_event_audience, char, 0, k_number_of_game_engine_event_audiences> audience; // 0x4
    c_enum_no_init<e_game_engine_event_response_context, char, 0, k_number_of_game_engine_event_response_contexts> display_context; // 0x5
    unsigned char pad6[2]; // 0x6
    long display_string; // 0x8 string_id
    c_enum_no_init<e_game_engine_event_input, char, 0, k_number_of_game_engine_event_inputs> required_field; // 0xC
    c_enum_no_init<e_game_engine_event_input, char, 0, k_number_of_game_engine_event_inputs> excluded_audience; // 0xD
    c_enum_no_init<e_game_engine_event_splitscreen_suppression, char, 0, k_number_of_game_engine_event_splitscreen_suppressions> splitscreen_suppression; // 0xE
    c_flags_no_init<e_game_engine_event_flags, unsigned char, k_number_of_game_engine_event_flags> flags; // 0xF
    long primary_string; // 0x10 string_id
    long primary_string_duration; // 0x14 seconds
    real sound_delay; // 0x18 announcer only
    s_game_engine_event_sound_response_definition default_sound; // 0x1C
    long category_for_prioritization; // 0x34 string_id
    long sound_priority; // 0x38
    real priority_suppression_age_max_seconds; // 0x3C
    s_tag_block sound_permutations; // 0x40 s_game_engine_event_sound_response_definition
};
static_assert(sizeof(s_game_engine_event_response_definition_v1) == 0x4C, "s_game_engine_event_response_definition_v1");

// game_engine_event_block_struct (Reach tag json)
struct s_game_engine_event_response_definition
{
    long name; // 0x0 string_id
    c_enum_no_init<e_game_engine_event_audience, char, 0, k_number_of_game_engine_event_audiences> audience; // 0x4
    c_enum_no_init<e_game_engine_event_response_context, char, 0, k_number_of_game_engine_event_response_contexts> display_context; // 0x5
    unsigned char pad6[2]; // 0x6
    long display_string; // 0x8 string_id
    c_enum_no_init<e_game_engine_event_input, char, 0, k_number_of_game_engine_event_inputs> required_field; // 0xC
    c_flags_no_init<e_game_engine_event_input, unsigned char, k_number_of_game_engine_event_inputs> excluded_audience; // 0xD
    c_enum_no_init<e_game_engine_event_splitscreen_suppression, char, 0, k_number_of_game_engine_event_splitscreen_suppressions> splitscreen_suppression; // 0xE
    c_flags_no_init<e_game_engine_event_flags, unsigned char, k_number_of_game_engine_event_flags> flags; // 0xF
    long primary_string; // 0x10 string_id
    long primary_string_duration; // 0x14 seconds
    real sound_delay; // 0x18 announcer only
    s_game_engine_event_sound_response_definition default_sound; // 0x1C
    long category_for_prioritization; // 0x34 string_id
    long sound_priority; // 0x38
    real priority_suppression_age_max_seconds; // 0x3C
    long category_for_pair_culling; // 0x40 string_id
    long pair_id; // 0x44
    real delay_before_considering_sound_seconds; // 0x48
    s_tag_block sound_permutations; // 0x4C s_game_engine_event_sound_response_definition
};
static_assert(sizeof(s_game_engine_event_response_definition) == 0x58, "s_game_engine_event_response_definition");

/* ---------- prototypes */

char * game_engine_event_definition_format(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size);

/* ---------- globals */

// $TODO file-static in the target (0x85313F98, not in the map); tag definition data not reconstructed yet
extern s_tag_block_definition game_engine_event_block_v1;

/* ---------- definitions */

class c_game_engine_event_block_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static char * format_proc(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
    {
        mangled_ppc("?format_proc@c_game_engine_event_block_vtable@@SAPADJ_JPAUs_tag_block@@JPADJ@Z");

        return game_engine_event_definition_format(tag_index, field_id, block, element_index, buffer, buffer_size);
    }

    static s_tag_struct_definition * get_fixup_source_definition_proc(void)
    {
        mangled_ppc("?get_fixup_source_definition_proc@c_game_engine_event_block_vtable@@SAPAUs_tag_struct_definition@@XZ");

        return const_cast<s_tag_struct_definition *>(game_engine_event_block_v1.struct_definition);
    }

    static bool fixup_old_struct_proc(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        mangled_ppc("?fixup_old_struct_proc@c_game_engine_event_block_vtable@@SA_NAAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@01PAVc_tag_allocator@@_N@Z");

        s_game_engine_event_response_definition_v1 * old_response = old_buffer.checked_cast();
        s_game_engine_event_response_definition * new_response = new_buffer.checked_cast();
        new_response->name = old_response->name;
        new_response->audience = old_response->audience;
        new_response->display_context = old_response->display_context;
        new_response->display_string = old_response->display_string;
        new_response->required_field = old_response->required_field;
        new_response->splitscreen_suppression = old_response->splitscreen_suppression;
        new_response->flags = old_response->flags;
        new_response->primary_string = old_response->primary_string;
        new_response->primary_string_duration = old_response->primary_string_duration;
        new_response->sound_delay = old_response->sound_delay;
        new_response->default_sound = old_response->default_sound;
        new_response->category_for_prioritization = old_response->category_for_prioritization;
        new_response->sound_priority = old_response->sound_priority;
        new_response->priority_suppression_age_max_seconds = old_response->priority_suppression_age_max_seconds;
        duplicate_recursive_tag_block_elements(&old_response->sound_permutations, &new_response->sound_permutations);
        new_response->excluded_audience.set(old_response->excluded_audience, true);
        return true;
    }
};

/* ---------- globals */

extern c_tag_struct_vtable<c_game_engine_event_block_vtable> game_engine_event_block_struct_struct_vtable;

/* ---------- public code */

#endif // __GAME_ENGINE_EVENT_DEFINITIONS_H__

