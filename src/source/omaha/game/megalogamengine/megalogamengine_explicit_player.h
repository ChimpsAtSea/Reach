#ifndef __MEGALOGAMENGINE_EXPLICIT_PLAYER_H__
#define __MEGALOGAMENGINE_EXPLICIT_PLAYER_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;
struct s_custom_game_engine_definition;

class c_explicit_player
{
public:
    // $TODO enumerator names unverified (values from c_explicit_player::get_player_index)
    enum e_explicit_player_type
    {
        _explicit_player_type_none = 0,
        _explicit_player_type_player_0,
        _explicit_player_type_player_1,
        _explicit_player_type_player_2,
        _explicit_player_type_player_3,
        _explicit_player_type_player_4,
        _explicit_player_type_player_5,
        _explicit_player_type_player_6,
        _explicit_player_type_player_7,
        _explicit_player_type_player_8,
        _explicit_player_type_player_9,
        _explicit_player_type_player_10,
        _explicit_player_type_player_11,
        _explicit_player_type_player_12,
        _explicit_player_type_player_13,
        _explicit_player_type_player_14,
        _explicit_player_type_player_15,
        _explicit_player_type_global_player_0,
        _explicit_player_type_global_player_1,
        _explicit_player_type_global_player_2,
        _explicit_player_type_global_player_3,
        _explicit_player_type_global_player_4,
        _explicit_player_type_global_player_5,
        _explicit_player_type_global_player_6,
        _explicit_player_type_global_player_7,
        _explicit_player_type_current_player,
        _explicit_player_type_hud_player,
        _explicit_player_type_hud_target_player,
        _explicit_player_type_killer_player,

        k_explicit_player_type_count
    };

    long get_player_index(void) const;
    void set_value(long player_index) const;
    void initialize_from_absolute_player_index(long absolute_player_index);
    bool is_writeable(void) const;
    bool is_networked(s_custom_game_engine_definition const * definition) const;
    void initialize_from_global_variable(long variable_index);
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

    // f i (megalogamengine_player_reference.obj)
    bool is_absolute_player_index(void) const
    {
        return m_explicit_player_type >= _explicit_player_type_none && m_explicit_player_type <= _explicit_player_type_player_15;
    };

private:
    bool is_global_player_variable(void) const
    {
        return m_explicit_player_type >= _explicit_player_type_global_player_0 && m_explicit_player_type <= _explicit_player_type_global_player_7;
    };

    long get_global_player_variable_index(void) const
    {
        assert_decomp(is_global_player_variable(), "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_player.h", 48);

        return m_explicit_player_type - _explicit_player_type_global_player_0;
    };

    c_enum_no_init<e_explicit_player_type, char, _explicit_player_type_none, k_explicit_player_type_count> m_explicit_player_type; // 0x0
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_EXPLICIT_PLAYER_H__
