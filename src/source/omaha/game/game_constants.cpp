#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_constants.cpp"
/* ---------- headers */

#include "omaha\game\game_constants.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char const * g_multiplayer_team_designator_strings[] =
{
    "none",
    "defenders",
    "attackers",
    "3rd_party",
    "4th_party",
    "5th_party",
    "6th_party",
    "7th_party",
    "8th_party",
    "neutral"
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **global_multiplayer_team_designator_enum_definition_strings; // "?global_multiplayer_team_designator_enum_definition_strings@@3PAPBDA"
// struct s_string_list_definition global_multiplayer_team_designator_enum_definition; // "?global_multiplayer_team_designator_enum_definition@@3Us_string_list_definition@@A"

// public: static void s_multiplayer_team_designator_string_resolver::to_string(enum e_multiplayer_team_designator, class c_static_string<64> *);

void s_multiplayer_team_designator_string_resolver::to_string(e_multiplayer_team_designator value, c_static_string<64> * string)
{
    mangled_ppc("?to_string@s_multiplayer_team_designator_string_resolver@@SAXW4e_multiplayer_team_designator@@PAV?$c_static_string@$0EA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(38, VALID_INDEX(value-NONE, NUMBEROF(g_multiplayer_team_designator_strings)));
    string->print("%s", g_multiplayer_team_designator_strings[value - NONE]);
};

