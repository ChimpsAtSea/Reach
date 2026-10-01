#ifndef __MEGALOGAMENGINE_EXPLICIT_TEAM_H__
#define __MEGALOGAMENGINE_EXPLICIT_TEAM_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\game_constants.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;
struct s_custom_game_engine_definition;

class c_explicit_team
{
public:
    // $TODO enumerator names unverified (values from c_explicit_team::get_team_designator / is_named_team)
    enum e_explicit_team_type
    {
        _explicit_team_type_none = -1,
        _explicit_team_type_team_0,
        _explicit_team_type_team_1,
        _explicit_team_type_team_2,
        _explicit_team_type_team_3,
        _explicit_team_type_team_4,
        _explicit_team_type_team_5,
        _explicit_team_type_team_6,
        _explicit_team_type_team_7,
        _explicit_team_type_neutral_team,
        _explicit_team_type_global_team_0,
        _explicit_team_type_global_team_1,
        _explicit_team_type_global_team_2,
        _explicit_team_type_global_team_3,
        _explicit_team_type_global_team_4,
        _explicit_team_type_global_team_5,
        _explicit_team_type_global_team_6,
        _explicit_team_type_global_team_7,
        _explicit_team_type_current_team,
        _explicit_team_type_hud_player_team,
        _explicit_team_type_hud_target_team,

        k_explicit_team_type_count
    };

    e_multiplayer_team_designator get_team_designator(void) const;
    void set_value(e_multiplayer_team_designator team_designator) const;
    bool is_writeable(void) const;
    bool is_networked(s_custom_game_engine_definition const * definition) const;
    void initialize_from_global_variable(long variable_index);
    void initialize_from_team_designator(e_multiplayer_team_designator team_designator);
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    // f i (megalogamengine_team_reference.obj)
    bool is_named_team(void) const
    {
        return m_explicit_team_type >= _explicit_team_type_none && m_explicit_team_type <= _explicit_team_type_neutral_team;
    };

    bool is_global_team_variable(void) const
    {
        return m_explicit_team_type >= _explicit_team_type_global_team_0 && m_explicit_team_type <= _explicit_team_type_global_team_7;
    };

private:
    long get_global_team_variable_index(void) const
    {
        assert_decomp(is_global_team_variable(), "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_team.h", 48);

        return m_explicit_team_type - _explicit_team_type_global_team_0;
    };

    c_enum_no_init<e_explicit_team_type, char, _explicit_team_type_none, k_explicit_team_type_count> m_explicit_team_type; // 0x0
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_EXPLICIT_TEAM_H__
