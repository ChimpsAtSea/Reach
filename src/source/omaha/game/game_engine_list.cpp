#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_list.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_list.h"
#include "omaha\game\game_engine_campaign.h"
#include "omaha\game\game_engine_megalo.h"
#include "omaha\game\game_engine_sandbox.h"
#include "omaha\game\game_engine_survival.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * k_game_engine_type_names[k_game_engine_type_count] =
{
    "none",
    "sandbox",
    "megalo",
    "campaign",
    "survival",
};

c_game_engine * game_engines[k_game_engine_type_count] =
{
    NULL,
    sandbox_engine,
    custom_engine,
    campaign_engine,
    survival_engine,
};

static long const k_game_engine_type_string_ids[k_game_engine_type_count] =
{
    312, // unknown
    298,
    299,
    300,
    301,
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **k_game_engine_type_names; // "?k_game_engine_type_names@@3PAPBDA"
// class c_game_engine **game_engines; // "?game_engines@@3PAPAVc_game_engine@@A"

// public: static void s_game_engine_type_string_resolver::to_string(enum e_game_engine_type, class c_static_string<64> *);
// char const * game_engine_type_get_string(enum e_game_engine_type);
// long game_engine_type_get_string_id(enum e_game_engine_type);

void s_game_engine_type_string_resolver::to_string(e_game_engine_type value, c_static_string<64> * string)
{
    mangled_ppc("?to_string@s_game_engine_type_string_resolver@@SAXW4e_game_engine_type@@PAV?$c_static_string@$0EA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(61, (long)value >= (long)c_game_engine_type::k_minimum_value);
    assert_tag_debug_untracked_jul_11_2011(61, (long)value < (long)c_game_engine_type::k_maximum_value_plus_one);
    value = static_cast<e_game_engine_type>(PIN(value, c_game_engine_type::k_minimum_value, c_game_engine_type::k_maximum_value_plus_one - 1));
    string->set(k_game_engine_type_names[value]);
};

char const * game_engine_type_get_string(e_game_engine_type game_engine_type)
{
    mangled_ppc("?game_engine_type_get_string@@YAPBDW4e_game_engine_type@@@Z");

    char const * string = "unknown";
    if (VALID_INDEX(game_engine_type, k_game_engine_type_count))
    {
        string = k_game_engine_type_names[game_engine_type];
    }

    return string;
};

long game_engine_type_get_string_id(e_game_engine_type game_engine_type)
{
    mangled_ppc("?game_engine_type_get_string_id@@YAJW4e_game_engine_type@@@Z");

    long game_engine_string_id = VALID_INDEX(game_engine_type, k_game_engine_type_count) ? k_game_engine_type_string_ids[game_engine_type] : 312;

    return game_engine_string_id;
};

