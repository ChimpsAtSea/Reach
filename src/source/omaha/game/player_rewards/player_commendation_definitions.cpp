#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\player_commendation_definitions.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\player_commendation_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\game_globals.h"
#include "omaha\game\incidents\incident_definitions.h"
#include "omaha\memory\crc.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\text\text_group.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition commendation_globals_definition_block; // "?commendation_globals_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group commendation_globals_definition_group; // "?commendation_globals_definition_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_commendation_globals_definition_vtable; // "?legacy_commendation_globals_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_commendation_globals_definition_stream_definition; // "?legacy_commendation_globals_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_commendation_globals_definition_xsync_declaration; // "?legacy_commendation_globals_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_commendation_globals_definition_vtable_shim; // "?legacy_commendation_globals_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long commendation_globals_get_commendation_definition_index_by_name(struct s_commendation_globals_definition const *, long);
// struct s_commendation_definition const * commendation_globals_get_commendation_definition_by_name(struct s_commendation_globals_definition const *, long);
// struct s_commendation_definition const * commendation_globals_try_and_get_commendation_definition_by_name(struct s_commendation_globals_definition const *, long);
// enum e_commendation_progression_level commendation_definition_get_progress_level(struct s_commendation_definition const *, long);
// enum e_commendation_progression_level commendation_definition_get_next_progress_level(struct s_commendation_definition const *, long);
// long commendation_definition_get_progress_level_minimum(struct s_commendation_definition const *, enum e_commendation_progression_level);
// unsigned long commendation_globals_generate_checksum(void);
// struct s_commendation_globals_definition const * commendation_globals_try_and_get(void);
// bool commendation_globals_get_game_type_color(union argb_color *);
// union argb_color const * commendation_globals_get_game_type_color_reference(void);
// bool commendation_globals_get_level_color(enum e_commendation_progression_level, union argb_color *);
// union argb_color const * commendation_globals_get_level_color_reference(enum e_commendation_progression_level);
// bool commendation_globals_get_commendation_text(struct s_commendation_globals_definition const *, long, class c_static_wchar_string<256> *);

long commendation_globals_get_commendation_definition_index_by_name(s_commendation_globals_definition const * commendation_globals, long name)
{
    mangled_ppc("?commendation_globals_get_commendation_definition_index_by_name@@YAJPBUs_commendation_globals_definition@@J@Z");

    long commendation_index = NONE;
    assert_tag_debug_untracked_jul_11_2011(36, commendation_globals);

    for (long index = 0; index < commendation_globals->commendations.count; index++)
    {
        s_commendation_definition const * commendation_definition = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, index, sizeof(s_commendation_definition)));
        if (commendation_definition->name == name)
        {
            commendation_index = index;
        }
    }

    return commendation_index;
};

s_commendation_definition const * commendation_globals_get_commendation_definition_by_name(s_commendation_globals_definition const * commendation_globals, long name)
{
    mangled_ppc("?commendation_globals_get_commendation_definition_by_name@@YAPBUs_commendation_definition@@PBUs_commendation_globals_definition@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(58, commendation_globals);

    return static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, commendation_globals_get_commendation_definition_index_by_name(commendation_globals, name), sizeof(s_commendation_definition)));
};

s_commendation_definition const * commendation_globals_try_and_get_commendation_definition_by_name(s_commendation_globals_definition const * commendation_globals, long name)
{
    mangled_ppc("?commendation_globals_try_and_get_commendation_definition_by_name@@YAPBUs_commendation_definition@@PBUs_commendation_globals_definition@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(69, commendation_globals);

    s_commendation_definition const * commendation_definition = NULL;
    long commendation_definition_index = commendation_globals_get_commendation_definition_index_by_name(commendation_globals, name);
    if (commendation_globals && VALID_INDEX(commendation_definition_index, commendation_globals->commendations.count))
    {
        commendation_definition = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, commendation_definition_index, sizeof(s_commendation_definition)));
    }

    return commendation_definition;
};

e_commendation_progression_level commendation_definition_get_progress_level(s_commendation_definition const * commendation_definition, long value)
{
    mangled_ppc("?commendation_definition_get_progress_level@@YA?AW4e_commendation_progression_level@@PBUs_commendation_definition@@J@Z");

    e_commendation_progression_level level = _commendation_progression_level_clear;
    assert_tag_debug_untracked_jul_11_2011(91, commendation_definition);

    for (long level_index = 0; level_index < k_commendation_progression_level_count - 1; level_index++)
    {
        if (value >= commendation_definition->level_minimum[level_index])
        {
            level = static_cast<e_commendation_progression_level>(level_index + 1);
        }
    }

    return level;
};

e_commendation_progression_level commendation_definition_get_next_progress_level(s_commendation_definition const * commendation_definition, long value)
{
    mangled_ppc("?commendation_definition_get_next_progress_level@@YA?AW4e_commendation_progression_level@@PBUs_commendation_definition@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(111, commendation_definition);

    e_commendation_progression_level level = commendation_definition_get_progress_level(commendation_definition, value);
    e_commendation_progression_level next_level = static_cast<e_commendation_progression_level>(level + 1);
    if (!VALID_INDEX(next_level, k_commendation_progression_level_count))
    {
        next_level = k_commendation_progression_level_none;
    }

    return next_level;
};

long commendation_definition_get_progress_level_minimum(s_commendation_definition const * commendation_definition, e_commendation_progression_level level)
{
    mangled_ppc("?commendation_definition_get_progress_level_minimum@@YAJPBUs_commendation_definition@@W4e_commendation_progression_level@@@Z");

    long level_minimum = 0;
    assert_tag_debug_untracked_jul_11_2011(131, commendation_definition);

    if (VALID_INDEX(level - 1, NUMBEROF(commendation_definition->level_minimum)))
    {
        level_minimum = commendation_definition->level_minimum[level - 1];
    }

    return level_minimum;
};

unsigned long commendation_globals_generate_checksum(void)
{
    mangled_ppc("?commendation_globals_generate_checksum@@YAKXZ");

    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    unsigned long checksum = crc_new();
    if (commendation_globals)
    {
        checksum = fast_checksum(checksum, &commendation_globals->commendations.count);
        for (long index = 0; index < commendation_globals->commendations.count; index++)
        {
            s_commendation_definition const * commendation_definition = static_cast<s_commendation_definition const *>(tag_block_get_element_with_size(&commendation_globals->commendations, index, sizeof(s_commendation_definition)));
            checksum = fast_checksum(checksum, &commendation_definition->name);
        }
    }

    return checksum;
};

s_commendation_globals_definition const * commendation_globals_try_and_get(void)
{
    mangled_ppc("?commendation_globals_try_and_get@@YAPBUs_commendation_globals_definition@@XZ");

    s_commendation_globals_definition const * commendation_globals = NULL;
    if (global_scenario_game_globals_index_get() != NONE)
    {
        s_game_globals const * game_globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()));
        if (game_globals && game_globals->incident_global_properties.index != NONE)
        {
            s_incident_global_properties_definition const * incident_globals = static_cast<s_incident_global_properties_definition const *>(tag_get(game_globals->incident_global_properties.group_tag, game_globals->incident_global_properties.index));
            if (incident_globals && incident_globals->commendation_globals.index != NONE)
            {
                commendation_globals = static_cast<s_commendation_globals_definition const *>(tag_get(COMMENDATION_GLOBALS_DEFINITION_TAG, incident_globals->commendation_globals.index));
            }
        }
    }

    return commendation_globals;
};

bool commendation_globals_get_game_type_color(argb_color * out_color)
{
    mangled_ppc("?commendation_globals_get_game_type_color@@YA_NPATargb_color@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(212, out_color);

    s_commendation_globals_definition const * commendation_globals = commendation_globals_try_and_get();
    if (commendation_globals)
    {
        if (game_is_campaign())
        {
            *out_color = commendation_globals->campaign_color;
        }
        else if (game_is_survival())
        {
            *out_color = commendation_globals->firefight_color;
        }
        else if (game_is_multiplayer())
        {
            *out_color = commendation_globals->multiplayer_color;
        }
        result = true;
    }

    return result;
};

argb_color const * commendation_globals_get_game_type_color_reference(void)
{
    mangled_ppc("?commendation_globals_get_game_type_color_reference@@YAPBTargb_color@@XZ");

    argb_color const * color = NULL;
    s_commendation_globals_definition const * commendation_globals_definition = commendation_globals_try_and_get();
    if (commendation_globals_definition)
    {
        if (game_is_campaign())
        {
            color = &commendation_globals_definition->campaign_color;
        }
        else if (game_is_survival())
        {
            color = &commendation_globals_definition->firefight_color;
        }
        else if (game_is_multiplayer())
        {
            color = &commendation_globals_definition->multiplayer_color;
        }
    }

    return color;
};

bool commendation_globals_get_level_color(e_commendation_progression_level level, argb_color * out_color)
{
    mangled_ppc("?commendation_globals_get_level_color@@YA_NW4e_commendation_progression_level@@PATargb_color@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(271, out_color);

    s_commendation_globals_definition const * commendation_globals_definition = commendation_globals_try_and_get();
    if (commendation_globals_definition)
    {
        assert_tag_debug_untracked_jul_11_2011(278, VALID_INDEX(level, NUMBEROF(commendation_globals_definition->level_color)));

        *out_color = commendation_globals_definition->level_color[level];
        result = true;
    }

    return result;
};

argb_color const * commendation_globals_get_level_color_reference(e_commendation_progression_level level)
{
    mangled_ppc("?commendation_globals_get_level_color_reference@@YAPBTargb_color@@W4e_commendation_progression_level@@@Z");

    argb_color const * color = NULL;
    s_commendation_globals_definition const * commendation_globals_definition = commendation_globals_try_and_get();
    if (commendation_globals_definition)
    {
        assert_tag_debug_untracked_jul_11_2011(298, VALID_INDEX(level, NUMBEROF(commendation_globals_definition->level_color)));

        color = &commendation_globals_definition->level_color[level];
    }

    return color;
};

bool commendation_globals_get_commendation_text(s_commendation_globals_definition const * commendation_globals, long name, c_static_wchar_string<256> * out_string)
{
    mangled_ppc("?commendation_globals_get_commendation_text@@YA_NPBUs_commendation_globals_definition@@JPAV?$c_static_wchar_string@$0BAA@@@@Z");

    bool result = false;
    if (commendation_globals->commendation_text.index != NONE && name != _string_id_invalid && name != _string_id_empty_string)
    {
        result = string_list_get_normal_string(commendation_globals->commendation_text.index, name, out_string, NULL);
    }

    return result;
};

