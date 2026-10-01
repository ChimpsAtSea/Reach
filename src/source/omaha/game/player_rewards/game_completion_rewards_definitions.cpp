#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\game_completion_rewards_definitions.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\game_completion_rewards_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition game_completion_rewards_globals_block; // "?game_completion_rewards_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group game_completion_rewards_globals_group; // "?game_completion_rewards_globals_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_game_completion_rewards_globals_vtable; // "?legacy_game_completion_rewards_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_game_completion_rewards_globals_stream_definition; // "?legacy_game_completion_rewards_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_game_completion_rewards_globals_xsync_declaration; // "?legacy_game_completion_rewards_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_game_completion_rewards_globals_vtable_shim; // "?legacy_game_completion_rewards_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// char * format_game_completion_rewards_falloff_point_block(long, __int64, struct s_tag_block *, long, char *, long);
// char * format_game_completion_rewards_definition_block(long, __int64, struct s_tag_block *, long, char *, long);
// bool gcrg_postprocess(long, struct s_game_completion_rewards_globals *, bool);

char * format_game_completion_rewards_falloff_point_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_game_completion_rewards_falloff_point_block@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_game_completion_rewards_falloff_point * falloff_point = static_cast<s_game_completion_rewards_falloff_point *>(tag_block_get_element_with_size(block, element_index, sizeof(s_game_completion_rewards_falloff_point)));
    csnzprintf(buffer, buffer_size, "%d min: %d cpm", falloff_point->start_time, falloff_point->cookies_per_minute);

    return buffer;
};

char * format_game_completion_rewards_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_game_completion_rewards_definition_block@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_game_completion_rewards_definition * definition = static_cast<s_game_completion_rewards_definition *>(tag_block_get_element_with_size(block, element_index, sizeof(s_game_completion_rewards_definition)));
    if (definition)
    {
        float cookies_per_minute = definition->initial_cookies_per_minute * definition->hopper_scaling_factor;
        csnzprintf(buffer, buffer_size, "%3.1f cpm %+2.0f%% win/%+2.0f%% place", cookies_per_minute, (definition->winner_scaling_factor - 1.0) * 100.0, (definition->performance_scaling_factor - 1.0) * 100.0);
    }

    return buffer;
};

bool gcrg_postprocess(long element_index, s_game_completion_rewards_globals * definition, bool for_editor)
{
    mangled_ppc("?gcrg_postprocess@@YA_NJPAUs_game_completion_rewards_globals@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(146, definition);

    return true;
};

