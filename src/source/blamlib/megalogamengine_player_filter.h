#pragma once
#ifndef __MEGALOGAMENGINE_PLAYER_FILTER_H__
#define __MEGALOGAMENGINE_PLAYER_FILTER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game_constants.h"
#include "omaha\game\megalogamengine\megalogamengine_custom_variable_reference.h"
#include "omaha\game\megalogamengine\megalogamengine_player_reference.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_player_filter_type
{
    _player_filter_type_no_one = 0,
    _player_filter_type_everyone,
    _player_filter_type_allies,
    _player_filter_type_enemies,
    _player_filter_type_player_mask,
    _player_filter_type_default,

    k_player_filter_type_count
};

/* ---------- definitions */

class c_bitstream;
class c_string_builder;
class c_player_filter_modifier;

class c_player_filter
{
public:
    void initialize(e_player_filter_type filter_type);
    bool operator==(c_player_filter const & other) const;
    bool operator!=(c_player_filter const & other) const;
    c_string_builder describe(void) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
    bool player_matches_filter(long player_index, e_multiplayer_team_designator team_designator) const;
    bool team_matches_filter(e_multiplayer_team_designator team_designator, e_multiplayer_team_designator other_team_designator) const;

protected:
    friend class c_player_filter_modifier;

    c_enum<e_player_filter_type, unsigned char, _player_filter_type_no_one, k_player_filter_type_count> m_filter_type; // 0x0
    c_flags_no_init<long, unsigned long, 16> m_player_mask; // 0x4
};
static_assert(sizeof(c_player_filter) == 0x8, "c_player_filter");

class c_player_filter_modifier
{
public:
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
    void apply_to(c_player_filter * filter) const;

protected:
    c_enum<e_player_filter_type, unsigned char, _player_filter_type_no_one, k_player_filter_type_count> m_filter_type; // 0x0
    c_player_reference m_player; // 0x1
    c_custom_variable_reference m_value; // 0x4
};
static_assert(sizeof(c_player_filter_modifier) == 0x7, "c_player_filter_modifier"); // $TODO real size unverified (offsets 0x0/0x1/0x4 are)

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_PLAYER_FILTER_H__

