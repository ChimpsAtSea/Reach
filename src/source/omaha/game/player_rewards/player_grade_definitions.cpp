#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\player_grade_definitions.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\player_grade_definitions.h"
#include "omaha\game\game_globals.h"
#include "omaha\main\main_game.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition player_grade_globals_definition_block; // "?player_grade_globals_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_group player_grade_globals_definition_group; // "?player_grade_globals_definition_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_player_grade_globals_definition_vtable; // "?legacy_player_grade_globals_definition_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_player_grade_globals_definition_stream_definition; // "?legacy_player_grade_globals_definition_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_player_grade_globals_definition_xsync_declaration; // "?legacy_player_grade_globals_definition_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_player_grade_globals_definition_vtable_shim; // "?legacy_player_grade_globals_definition_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// struct s_player_grade_globals_definition const * player_grade_globals_try_and_get(void);
// char * format_player_sub_grade_definition_block(long, __int64, struct s_tag_block *, long, char *, long);
// char * format_player_grade_definition_block(long, __int64, struct s_tag_block *, long, char *, long);
// bool pggd_postprocess(long, struct s_player_grade_globals_definition *, bool);

s_player_grade_globals_definition const * player_grade_globals_try_and_get()
{
    mangled_ppc("?player_grade_globals_try_and_get@@YAPBUs_player_grade_globals_definition@@XZ");

    s_player_grade_globals_definition const * player_grade_globals = NULL;
    if (main_game_loaded_map())
    {
        c_game_tag_defense_push_scope game_tag_defense_scope(false);
        s_game_globals const * game_globals = scenario_try_and_get_game_globals();
        if (game_globals)
        {
            long player_grade_globals_index = game_globals->player_grade_globals.index;
            if (player_grade_globals_index != NONE)
            {
                player_grade_globals = static_cast<s_player_grade_globals_definition const *>(tag_get(PLAYER_GRADE_GLOBALS_DEFINITION_TAG, player_grade_globals_index));
            }
        }
    }

    return player_grade_globals;
};

char * format_player_sub_grade_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_player_sub_grade_definition_block@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_player_sub_grade_definition * sub_grade = static_cast<s_player_sub_grade_definition *>(tag_block_get_element_with_size(block, element_index, sizeof(s_player_sub_grade_definition)));
    csnzprintf(buffer, buffer_size, "%d cookies: %s", sub_grade->cookie_threshold, string_id_get_string_const(sub_grade->name));

    return buffer;
};

char * format_player_grade_definition_block(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_player_grade_definition_block@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_player_grade_definition * grade = static_cast<s_player_grade_definition *>(tag_block_get_element_with_size(block, element_index, sizeof(s_player_grade_definition)));
    long sub_grade_count = grade->sub_grades.count;
    s_player_sub_grade_definition * first_sub_grade = sub_grade_count ? static_cast<s_player_sub_grade_definition *>(tag_block_get_element_with_size(&grade->sub_grades, 0, sizeof(s_player_sub_grade_definition))) : NULL;
    if (first_sub_grade)
    {
        csnzprintf(buffer, buffer_size, "%d+: %s, etc. (%i sub_grades)", first_sub_grade->cookie_threshold, string_id_get_string_const(first_sub_grade->name), sub_grade_count);
    }
    else
    {
        csnzprintf(buffer, buffer_size, "???: no sub_grades");
    }

    return buffer;
};

bool pggd_postprocess(long element_index, s_player_grade_globals_definition * definition, bool for_editor)
{
    mangled_ppc("?pggd_postprocess@@YA_NJPAUs_player_grade_globals_definition@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(126, definition);

    return true;
};

