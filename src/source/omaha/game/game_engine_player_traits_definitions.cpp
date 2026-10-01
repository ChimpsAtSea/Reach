/* ---------- headers */

#include "omaha\game\game_engine_player_traits_definitions.h"
#include "omaha\game\game_engine_util.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\string_ids.h"
#include "core\corelib\cseries\cseries_events.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static float const *const const s_shield_multiplier_option_metadata::values; // "?values@s_shield_multiplier_option_metadata@@2QBMB"
// public: static float const *const const s_shield_recharge_rate_option_metadata::values; // "?values@s_shield_recharge_rate_option_metadata@@2QBMB"
// public: static float const *const const s_body_recharge_rate_option_metadata::values; // "?values@s_body_recharge_rate_option_metadata@@2QBMB"
// public: static float const *const const s_vampirism_option_metadata::values; // "?values@s_vampirism_option_metadata@@2QBMB"
// public: static float const *const const s_player_speed_option_metadata::values; // "?values@s_player_speed_option_metadata@@2QBMB"
// public: static float const *const const s_player_gravity_option_metadata::values; // "?values@s_player_gravity_option_metadata@@2QBMB"
// public: static float const *const const s_motion_tracker_range_option_metadata::values; // "?values@s_motion_tracker_range_option_metadata@@2QBMB"
// char const **player_trait_boolean_strings; // "?player_trait_boolean_strings@@3PAPBDA"
// struct s_string_list_definition player_trait_boolean; // "?player_trait_boolean@@3Us_string_list_definition@@A"
// char const **player_trait_damage_resistance_strings; // "?player_trait_damage_resistance_strings@@3PAPBDA"
// struct s_string_list_definition player_trait_damage_resistance; // "?player_trait_damage_resistance@@3Us_string_list_definition@@A"
// char const **player_trait_damage_modifier_strings; // "?player_trait_damage_modifier_strings@@3PAPBDA"
// struct s_string_list_definition player_trait_damage_modifier; // "?player_trait_damage_modifier@@3Us_string_list_definition@@A"
// char const **player_trait_grenade_count_setting_strings; // "?player_trait_grenade_count_setting_strings@@3PAPBDA"
// struct s_string_list_definition player_trait_grenade_count_setting; // "?player_trait_grenade_count_setting@@3Us_string_list_definition@@A"
// struct s_tag_block_definition game_engine_player_traits_block; // "?game_engine_player_traits_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition game_engine_player_traits_block_struct_definition; // "?game_engine_player_traits_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition game_engine_player_traits_list_block_struct_definition; // "?game_engine_player_traits_list_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition game_engine_player_traits_list_block; // "?game_engine_player_traits_list_block@@3Us_tag_block_definition@@A"
// public: static float const *const const s_damage_resistance_option_metadata::values; // "?values@s_damage_resistance_option_metadata@@2QBMB"
// public: static float const *const const s_body_multiplier_option_metadata::values; // "?values@s_body_multiplier_option_metadata@@2QBMB"
// public: static float const *const const s_damage_modifier_option_metadata::values; // "?values@s_damage_modifier_option_metadata@@2QBMB"

// bool postprocess_player_trait_weapons_block(long, void *, bool);

bool postprocess_player_trait_weapons_block(long block_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_player_trait_weapons_block@@YA_NJPAX_N@Z");

    s_player_trait_weapons * weapons = static_cast<s_player_trait_weapons *>(element);
    if (!for_editor)
    {
        long primary_weapon_absolute_index = game_engine_get_multiplayer_weapon_selection_absolute_index(weapons->initial_primary_weapon);
        long secondary_weapon_absolute_index = game_engine_get_multiplayer_weapon_selection_absolute_index(weapons->initial_secondary_weapon);
        long equipment_absolute_index = game_engine_get_multiplayer_equipment_selection_absolute_index(weapons->initial_equipment);
        if (primary_weapon_absolute_index == NONE && weapons->initial_primary_weapon != 333)
        {
            event_wrapped(_event_warning, "multiplayer:player_traits:failed to find initial primary weapon %s in the global multiplayer weapon list", string_id_get_string_const(weapons->initial_primary_weapon));
        }
        if (secondary_weapon_absolute_index == NONE && weapons->initial_secondary_weapon != 333)
        {
            event_wrapped(_event_warning, "multiplayer:player_traits:failed to find initial secondary weapon %s in the global multiplayer weapon list", string_id_get_string_const(weapons->initial_secondary_weapon));
        }
        if (equipment_absolute_index == NONE && weapons->initial_equipment != 333)
        {
            event_wrapped(_event_warning, "multiplayer:player_traits:failed to find initial equipment %s in the global multiplayer equipment list", string_id_get_string_const(weapons->initial_equipment));
        }
    }

    return true;
};

