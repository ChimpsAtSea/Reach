#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\campaign_metagame_definitions.cpp"
/* ---------- headers */

#include "omaha\game\campaign_metagame_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\game\campaign_metagame.h"
#include "omaha\game\game.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **k_campaign_metagame_bucket_class_enum_strings; // "?k_campaign_metagame_bucket_class_enum_strings@@3PAPBDA"
// struct s_string_list_definition campaign_metagame_bucket_type_enum; // "?campaign_metagame_bucket_type_enum@@3Us_string_list_definition@@A"
// char const **k_campaign_metagame_bucket_type_enum_strings; // "?k_campaign_metagame_bucket_type_enum_strings@@3PAPBDA"
// struct s_string_list_definition campaign_metagame_bucket_class_enum; // "?campaign_metagame_bucket_class_enum@@3Us_string_list_definition@@A"
// char const **campaign_metagame_bucket_type_enum_strings; // "?campaign_metagame_bucket_type_enum_strings@@3PAPBDA"
// char const **campaign_metagame_bucket_class_enum_strings; // "?campaign_metagame_bucket_class_enum_strings@@3PAPBDA"
// struct s_string_list_definition campaign_metagame_bucket_type_with_none_enum; // "?campaign_metagame_bucket_type_with_none_enum@@3Us_string_list_definition@@A"
// char const **campaign_metagame_bucket_type_with_none_enum_strings; // "?campaign_metagame_bucket_type_with_none_enum_strings@@3PAPBDA"
// char const **campaign_metagame_bucket_class_with_none_enum_strings; // "?campaign_metagame_bucket_class_with_none_enum_strings@@3PAPBDA"
// struct s_string_list_definition campaign_metagame_bucket_class_with_none_enum; // "?campaign_metagame_bucket_class_with_none_enum@@3Us_string_list_definition@@A"
// struct s_tag_struct_definition campaign_metagame_bucket_block_struct_definition; // "?campaign_metagame_bucket_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition campaign_metagame_bucket_block; // "?campaign_metagame_bucket_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition campaign_metagame_scenario_block_struct_definition; // "?campaign_metagame_scenario_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition campaign_metagame_scenario_block; // "?campaign_metagame_scenario_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition campaign_metagame_globals_block_struct_definition; // "?campaign_metagame_globals_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition campaign_metagame_globals_block; // "?campaign_metagame_globals_block@@3Us_tag_block_definition@@A"

// char * campaign_metagame_difficulty_format(long, __int64, struct s_tag_block *, long, char *, long);
// char * campaign_metagame_skull_format(long, __int64, struct s_tag_block *, long, char *, long);
// struct s_campaign_metagame_globals * campaign_metagame_globals_get(void);

char * campaign_metagame_difficulty_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?campaign_metagame_difficulty_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(151, VALID_INDEX(element_index, k_campaign_difficulty_levels_count));
    csnzprintf(buffer, buffer_size, "difficulty: %s", global_campaign_difficulty_level_names[element_index]);

    return buffer;
};

char * campaign_metagame_skull_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?campaign_metagame_skull_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(174, VALID_INDEX(element_index, k_game_skull_count));
    csnzprintf(buffer, buffer_size, "Skull: %s", global_skull_names[element_index]);

    return buffer;
};

s_campaign_metagame_globals * campaign_metagame_globals_get()
{
    mangled_ppc("?campaign_metagame_globals_get@@YAPAUs_campaign_metagame_globals@@XZ");

    s_game_globals * game_globals = scenario_try_and_get_game_globals();
    s_campaign_metagame_globals * result = NULL;
    if (game_globals != NULL && game_globals->campaign_metagame_block.count == 1)
    {
        result = static_cast<s_campaign_metagame_globals *>(tag_block_get_element_with_size(&game_globals->campaign_metagame_block, 0, sizeof(s_campaign_metagame_globals)));
    }

    return result;
};

