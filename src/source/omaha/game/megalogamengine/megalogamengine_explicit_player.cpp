#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_player.cpp"
/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_explicit_player.h"
#include "blamlib\megalogamengine.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "networkinglib\simulation_game_action_megalo.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine_megalo.h"
#include "omaha\game\players.h"
#include "omaha\game\megalogamengine\megalogamengine_variable_metadata.h"
#include "omaha\game\megalogamengine\megalogamengine_variable_values.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: long c_explicit_player::get_player_index(void) const;
// private: bool c_explicit_player::is_global_player_variable(void) const;
// private: long c_explicit_player::get_global_player_variable_index(void) const;
// public: void c_explicit_player::set_value(long) const;
// public: void c_explicit_player::initialize_from_absolute_player_index(long);
// public: bool c_explicit_player::is_writeable(void) const;
// public: bool c_explicit_player::is_networked(struct s_custom_game_engine_definition const *) const;
// public: void c_explicit_player::initialize_from_global_variable(long);
// public: void c_explicit_player::encode(class c_bitstream *) const;
// public: void c_explicit_player::decode(class c_bitstream *);
// public: class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver> & c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>::operator=(enum c_explicit_player::e_explicit_player_type);
// public: void s_variable_values<struct s_global_variable_traits>::set_player_variable(long, long);
// public: void c_bitstream::write_enum<class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver> *);
// public: bool c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>::set_raw_value(char);
// long required_encoding_bits_for_enum<class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver> >(class c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>);
// public: static enum c_explicit_player::e_explicit_player_type c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum c_explicit_player::e_explicit_player_type, char, 0, 29, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

long c_explicit_player::get_player_index(void) const
{
    mangled_ppc("?get_player_index@c_explicit_player@@QBAJXZ");

    long player_index = NONE;
    if (m_explicit_player_type == _explicit_player_type_none)
    {
        player_index = NONE;
    }
    else if (is_global_player_variable())
    {
        long variable_index = get_global_player_variable_index();
        player_index = get_custom_game_engine_globals()->global_variables.get_player_variable(variable_index);
    }
    else if (m_explicit_player_type == _explicit_player_type_current_player)
    {
        player_index = get_custom_game_engine_globals()->current_player_index;
    }
    else if (m_explicit_player_type == _explicit_player_type_hud_player)
    {
        player_index = get_custom_game_engine_globals()->hud_player_index;
    }
    else if (m_explicit_player_type == _explicit_player_type_hud_target_player)
    {
        player_index = get_custom_game_engine_globals()->hud_target_player_index;
    }
    else if (m_explicit_player_type == _explicit_player_type_killer_player)
    {
        player_index = get_custom_game_engine_globals()->killer_player_index;
    }
    else if (is_absolute_player_index())
    {
        player_index = player_index_from_absolute_player_index(m_explicit_player_type - _explicit_player_type_player_0);
    }

    return player_index;
};

void c_explicit_player::set_value(long player_index) const
{
    mangled_ppc("?set_value@c_explicit_player@@QBAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(62, is_writeable());
    assert_tag_debug_untracked_jul_11_2011(63, game_is_authoritative() || !is_networked(get_custom_game_engine_definition()));

    if (is_global_player_variable())
    {
        long variable_index = get_global_player_variable_index();
        get_custom_game_engine_globals()->global_variables.set_player_variable(variable_index, player_index);
        simulation_update_global_megalo_variable(_variable_type_player, variable_index);
    }
};

void c_explicit_player::initialize_from_absolute_player_index(long absolute_player_index)
{
    mangled_ppc("?initialize_from_absolute_player_index@c_explicit_player@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(78, absolute_player_index==NONE || VALID_INDEX(absolute_player_index, k_maximum_multiplayer_players));

    m_explicit_player_type = static_cast<e_explicit_player_type>(absolute_player_index + _explicit_player_type_player_0);
};

bool c_explicit_player::is_writeable(void) const
{
    mangled_ppc("?is_writeable@c_explicit_player@@QBA_NXZ");

    return is_global_player_variable();
};

bool c_explicit_player::is_networked(s_custom_game_engine_definition const * definition) const
{
    mangled_ppc("?is_networked@c_explicit_player@@QBA_NPBUs_custom_game_engine_definition@@@Z");

    bool networked = false;
    if (is_global_player_variable())
    {
        networked = definition->global_variable_metadata.get_variable_network_state(_variable_type_player, static_cast<unsigned char>(get_global_player_variable_index())) != _megalo_variable_network_state_none;
    }

    return networked;
};

void c_explicit_player::initialize_from_global_variable(long variable_index)
{
    mangled_ppc("?initialize_from_global_variable@c_explicit_player@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(109, VALID_INDEX(variable_index, s_global_variable_traits::k_number_of_player_variables));

    m_explicit_player_type = static_cast<e_explicit_player_type>(variable_index + _explicit_player_type_global_player_0);
};

void c_explicit_player::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_explicit_player@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("explicit-player-type", m_explicit_player_type);
};

void c_explicit_player::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_explicit_player@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("explicit-player-type", &m_explicit_player_type);
};
