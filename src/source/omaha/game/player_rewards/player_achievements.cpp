#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_rewards\\player_achievements.cpp"
/* ---------- headers */

#include "omaha\game\player_rewards\player_achievements.h"
#include "omaha\game\game.h"
#include "omaha\game\game_globals.h"
#include "omaha\game\player_mapping.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\input\controllers.h"
#include "omaha\networking\online\online_achievements.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static bool g_achievements_enabled = true;
static bool g_skip_achievement_validation_checks;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **k_achievement_strings; // "?k_achievement_strings@@3PAPBDA"
// struct s_string_list_definition global_achievement_enum; // "?global_achievement_enum@@3Us_string_list_definition@@A"
// struct s_tag_block_definition achievements_block; // "?achievements_block@@3Us_tag_block_definition@@A"
// struct s_tag_group achievements_group; // "?achievements_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_achievements_vtable; // "?legacy_achievements_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_achievements_stream_definition; // "?legacy_achievements_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_achievements_xsync_declaration; // "?legacy_achievements_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_achievements_vtable_shim; // "?legacy_achievements_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool game_achievements_enabled(void);
// void game_achievements_enable(bool);
// bool game_achievements_validation_get_disabled(void);
// void game_achievements_validation_disable(bool);
// struct s_single_achievement_definition * game_achievements_find_achievement(enum e_achievement);
// struct s_single_achievement_definition * game_achievements_find_achievement_by_name(long);
// long achievement_get_name(enum e_achievement);
// enum e_achievement achievement_get_by_name(long);
// bool game_conditions_allow_achievement(enum e_controller_index, enum e_achievement);
// bool achievements_enabled(void);
// void player_grant_achievement(long, enum e_achievement);
// void player_grant_achievement_by_name(long, long);
// public: enum e_achievement c_enum_no_init<enum e_achievement, char, 0, 79, struct s_default_enum_string_resolver>::operator enum e_achievement(void) const;
// public: bool c_enum_no_init<enum e_achievement, char, 0, 79, struct s_default_enum_string_resolver>::operator==(enum e_achievement) const;
// public: bool c_flags_no_init<enum e_campaign_difficulty_level, unsigned char, 4, struct s_default_enum_string_resolver>::test(enum e_campaign_difficulty_level) const;
// public: static bool c_flags_no_init<enum e_campaign_difficulty_level, unsigned char, 4, struct s_default_enum_string_resolver>::valid_bit(enum e_campaign_difficulty_level);
// private: static unsigned char c_flags_no_init<enum e_campaign_difficulty_level, unsigned char, 4, struct s_default_enum_string_resolver>::flag_size_type(enum e_campaign_difficulty_level);

bool game_achievements_enabled(void)
{
    mangled_ppc("?game_achievements_enabled@@YA_NXZ");

    return achievements_enabled();
};

void game_achievements_enable(bool enable)
{
    mangled_ppc("?game_achievements_enable@@YAX_N@Z");

    g_achievements_enabled = enable;
};

bool game_achievements_validation_get_disabled(void)
{
    mangled_ppc("?game_achievements_validation_get_disabled@@YA_NXZ");

    return g_skip_achievement_validation_checks;
};

void game_achievements_validation_disable(bool disable)
{
    mangled_ppc("?game_achievements_validation_disable@@YAX_N@Z");

    g_skip_achievement_validation_checks = disable;
};

s_single_achievement_definition * game_achievements_find_achievement(e_achievement achievement)
{
    mangled_ppc("?game_achievements_find_achievement@@YAPAUs_single_achievement_definition@@W4e_achievement@@@Z");

    s_single_achievement_definition * result = NULL;
    s_game_achievements_definition * achievements = scenario_get_game_globals()->game_achievements.index != NONE ? static_cast<s_game_achievements_definition *>(tag_get(ACHIEVEMENTS_TAG, scenario_get_game_globals()->game_achievements.index)) : NULL;

    if (achievements)
    {
        for (long achievement_index = 0; achievement_index < achievements->achievements.count; achievement_index++)
        {
            s_single_achievement_definition * achievement_definition = static_cast<s_single_achievement_definition *>(tag_block_get_element_with_size(&achievements->achievements, achievement_index, sizeof(s_single_achievement_definition)));
            if (achievement_definition->type == achievement)
            {
                result = achievement_definition;
            }
        }
    }

    return result;
};

s_single_achievement_definition * game_achievements_find_achievement_by_name(long achievement_name)
{
    mangled_ppc("?game_achievements_find_achievement_by_name@@YAPAUs_single_achievement_definition@@J@Z");

    s_single_achievement_definition * result = NULL;
    s_game_achievements_definition * achievements = scenario_get_game_globals()->game_achievements.index != NONE ? static_cast<s_game_achievements_definition *>(tag_get(ACHIEVEMENTS_TAG, scenario_get_game_globals()->game_achievements.index)) : NULL;

    if (achievements)
    {
        for (long achievement_index = 0; achievement_index < achievements->achievements.count; achievement_index++)
        {
            s_single_achievement_definition * achievement_definition = static_cast<s_single_achievement_definition *>(tag_block_get_element_with_size(&achievements->achievements, achievement_index, sizeof(s_single_achievement_definition)));
            if (achievement_definition->name == achievement_name)
            {
                result = achievement_definition;
            }
        }
    }

    return result;
};

long achievement_get_name(e_achievement achievement)
{
    mangled_ppc("?achievement_get_name@@YAJW4e_achievement@@@Z");

    long achievement_name = _string_id_empty_string;
    s_single_achievement_definition * achievement_definition = game_achievements_find_achievement(achievement);
    if (achievement_definition)
    {
        achievement_name = achievement_definition->name;
    }

    return achievement_name;
};

e_achievement achievement_get_by_name(long achievement_name)
{
    mangled_ppc("?achievement_get_by_name@@YA?AW4e_achievement@@J@Z");

    e_achievement result = k_invalid_achievement;
    s_single_achievement_definition * achievement_definition = game_achievements_find_achievement_by_name(achievement_name);
    if (achievement_definition)
    {
        result = achievement_definition->type;
    }

    return result;
};

bool game_conditions_allow_achievement(e_controller_index controller_index, e_achievement achievement)
{
    mangled_ppc("?game_conditions_allow_achievement@@YA_NW4e_controller_index@@W4e_achievement@@@Z");

    bool achievement_allowed = true;
    s_game_achievements_definition * achievements;
    if (VALID_CONTROLLER(controller_index))
    {
        c_game_tag_defense_push_scope game_tag_defense_scope(false);
        s_game_globals * game_globals = scenario_try_and_get_game_globals();
        achievements = game_globals ? (game_globals->game_achievements.index != NONE ? static_cast<s_game_achievements_definition *>(tag_get(ACHIEVEMENTS_TAG, game_globals->game_achievements.index)) : NULL) : NULL;

        if (achievements)
        {
            s_single_achievement_definition * achievement_definition = game_achievements_find_achievement(achievement);
            if (achievement_definition)
            {
                long map_name = global_scenario_get()->map_name;
                if (achievement_definition->restricted_levels.count > 0 && map_name != _string_id_empty_string)
                {
                    bool level_found = false;
                    for (long level_index = 0; level_index < achievement_definition->restricted_levels.count; level_index++)
                    {
                        s_single_achievement_restricted_level_definition * restricted_level = static_cast<s_single_achievement_restricted_level_definition *>(tag_block_get_element_with_size(&achievement_definition->restricted_levels, level_index, sizeof(s_single_achievement_restricted_level_definition)));
                        level_found = level_found || restricted_level->level_name == map_name;
                    }
                    achievement_allowed = achievement_allowed && level_found;
                }

                if (!achievement_definition->difficulty.is_clear())
                {
                    achievement_allowed = achievement_allowed && achievement_definition->difficulty.test(game_difficulty_level_get());
                }
            }
        }

        achievement_allowed = achievement_allowed || g_skip_achievement_validation_checks;
    }

    return achievement_allowed;
};

bool achievements_enabled(void)
{
    mangled_ppc("?achievements_enabled@@YA_NXZ");

    bool result = !game_is_playback();
    result = result && g_achievements_enabled;

    return result;
};

void player_grant_achievement(long player_index, e_achievement achievement)
{
    mangled_ppc("?player_grant_achievement@@YAXJW4e_achievement@@@Z");

    e_controller_index controller_index = player_mapping_get_input_controller(player_index);
    if (VALID_CONTROLLER(controller_index))
    {
        controller_grant_achievement(controller_index, achievement);
    }
};

void player_grant_achievement_by_name(long player_index, long achievement_name)
{
    mangled_ppc("?player_grant_achievement_by_name@@YAXJJ@Z");

    if (player_index != NONE)
    {
        e_controller_index controller_index = player_mapping_get_input_controller(player_index);
        if (VALID_CONTROLLER(controller_index))
        {
            controller_grant_achievement_by_name(controller_index, achievement_name);
        }
    }
};
