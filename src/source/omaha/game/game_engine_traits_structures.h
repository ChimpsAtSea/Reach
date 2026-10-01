#pragma once
#ifndef __GAME_ENGINE_TRAITS_STRUCTURES_H__
#define __GAME_ENGINE_TRAITS_STRUCTURES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game_engine.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\saved_games\content\content_item_metadata.h"
#include "omaha\game\game_engine_player_traits_structures.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

// names from the game_engine_group.obj string table
enum e_map_override_option_flags
{
    _grenades_on_map_bit = 0,
    _shortcuts_on_map_bit,
    _equipment_on_map_bit,
    _powerups_on_map_bit,
    _turrets_on_map_bit,
    _indestructible_vehicles_bit,

    k_number_of_map_override_option_flags
};

/* ---------- definitions */

class c_bitstream;

// to_string owned by game_engine_group.obj
struct s_map_override_option_string_resolver
{
    static void to_string(e_map_override_option_flags value, c_static_string<64> * string);
};

// sizes per haloreach_tagtest_x360.json; block element sizes per c_game_engine_base_variant::set
struct s_game_engine_base_variant_definition
{
    long name_string_id; // 0x0
    long description_string_id; // 0x4
    s_tag_block miscellaneous_options; // 0x8 s_game_engine_miscellaneous_options_definition (0x8)
    s_tag_block respawn_options; // 0x14 (0x10)
    s_tag_block social_options; // 0x20 (0x4)
    s_tag_block map_override_options; // 0x2C (0x1C)
    s_tag_block team_options; // 0x38 (0xA4)
    s_tag_block loadout_options; // 0x44 (0x10)
};
static_assert(sizeof(s_game_engine_base_variant_definition) == 0x50, "s_game_engine_base_variant_definition");

// $TODO: data members not yet reversed (size 0x8 from c_game_engine_base_variant::set)
class c_game_engine_miscellaneous_options
{
public:
    void set_round_limit(unsigned char round_limit);
    void set_round_time_limit_minutes(unsigned char round_time_limit_minutes);

private:
    unsigned char m_storage[0x8];
};
static_assert(sizeof(c_game_engine_miscellaneous_options) == 0x8, "c_game_engine_miscellaneous_options");

// $TODO: remaining data members not yet reversed; offsets per the f i getters (game_engine_traits_structures.obj)
class c_game_engine_map_override_options
{
public:
    c_player_traits const * get_red_powerup_traits(void) const
    {
        return &m_red_powerup_traits;
    };

    c_player_traits const * get_blue_powerup_traits(void) const
    {
        return &m_blue_powerup_traits;
    };

    c_player_traits const * get_yellow_powerup_traits(void) const
    {
        return &m_yellow_powerup_traits;
    };

    unsigned char get_red_powerup_duration_seconds(void) const
    {
        return m_red_powerup_duration_seconds;
    };

    unsigned char get_blue_powerup_duration_seconds(void) const
    {
        return m_blue_powerup_duration_seconds;
    };

    unsigned char get_yellow_powerup_duration_seconds(void) const
    {
        return m_yellow_powerup_duration_seconds;
    };

private:
    unsigned char m_unknown0[0x34]; // 0x0
    c_player_traits m_red_powerup_traits; // 0x34
    c_player_traits m_blue_powerup_traits; // 0x60
    c_player_traits m_yellow_powerup_traits; // 0x8C
    unsigned char m_red_powerup_duration_seconds; // 0xB8
    unsigned char m_blue_powerup_duration_seconds; // 0xB9
    unsigned char m_yellow_powerup_duration_seconds; // 0xBA
    unsigned char m_unknownBB[0x1]; // 0xBB
};
static_assert(sizeof(c_game_engine_map_override_options) == 0xBC, "c_game_engine_map_override_options");

// $TODO: data members not yet reversed; vtable order from H3 (initialize @ 0x8, validate @ 0xC and decode @ 0x14 confirmed by megalogamengine_loading)
class c_game_engine_base_variant
{
public:
    virtual long get_game_engine_name_string_id(void) const;
    virtual long get_game_engine_default_description_string_id(void) const;
    virtual void initialize(void);
    virtual void validate(void);
    virtual void encode(c_bitstream * packet) const;
    virtual void decode(c_bitstream * packet);
    // slots 6-12 per the ??_7c_game_engine_base_variant@@6B@ layout (can_be_cast_to @ 0x30 confirmed by c_campaign_engine::initialize_for_new_map)
    virtual bool lossy_compare(c_game_engine_base_variant * other);
    virtual bool can_add_to_recent_list(void) const;
    virtual bool fire_teams_enabled(void) const;
    virtual long get_score_to_win_round(void) const;
    virtual void set_score_to_win_round(long score_to_win_round);
    virtual bool get_rules_are_symmetric(void) const;
    virtual bool can_be_cast_to(e_game_engine_type game_engine_index, void const ** out_variant) const;

    wchar_t const * get_name(void) const;
    void set_name(wchar_t const * name);
    void set(s_game_engine_base_variant_definition const * definition, e_game_engine_type game_engine_index);

    s_content_item_metadata * get_metadata(void)
    {
        return &m_metadata;
    };

    s_content_item_metadata const * get_metadata(void) const
    {
        return &m_metadata;
    };

    c_game_engine_map_override_options const * get_map_override_options(void) const
    {
        return &m_map_override_options;
    };

protected:
    // $TODO: remaining layout per c_game_engine_base_variant::initialize: respawn 0x2BC, social 0x2F4, map override 0x2F8,
    // team 0x3B4, loadout traits 0x678, flags 0x72E, team scoring 0x730
    s_content_item_metadata m_metadata; // 0x4
    c_game_engine_miscellaneous_options m_miscellaneous_options; // 0x2B4
    unsigned char m_respawn_and_social_options[0x3C]; // 0x2BC $TODO respawn options (0x2BC), social options (0x2F4)
    c_game_engine_map_override_options m_map_override_options; // 0x2F8
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_TRAITS_STRUCTURES_H__

