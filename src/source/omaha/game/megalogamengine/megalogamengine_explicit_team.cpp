#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_team.cpp"
/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_explicit_team.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_default.h"
#include "omaha\game\game_engine_megalo.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\multiplayer_game_objects.h"
#include "blamlib\megalogamengine.h"
#include "networkinglib\simulation_game_action_megalo.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: enum e_multiplayer_team_designator c_explicit_team::get_team_designator(void) const;
// public: bool c_explicit_team::is_global_team_variable(void) const;
// private: long c_explicit_team::get_global_team_variable_index(void) const;
// public: void c_explicit_team::set_value(enum e_multiplayer_team_designator) const;
// public: bool c_explicit_team::is_writeable(void) const;
// public: bool c_explicit_team::is_networked(struct s_custom_game_engine_definition const *) const;
// public: void c_explicit_team::initialize_from_global_variable(long);
// public: void c_explicit_team::initialize_from_team_designator(enum e_multiplayer_team_designator);
// public: void c_explicit_team::encode(class c_bitstream *) const;
// public: void c_explicit_team::decode(class c_bitstream *);
// public: class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver> & c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>::operator=(enum c_explicit_team::e_explicit_team_type);
// public: void c_bitstream::write_enum<class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver> *);
// public: bool c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>::set_raw_value(char);
// long required_encoding_bits_for_enum<class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver> >(class c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>);
// public: static enum c_explicit_team::e_explicit_team_type c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum c_explicit_team::e_explicit_team_type, char, -1, 20, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

e_multiplayer_team_designator c_explicit_team::get_team_designator(void) const
{
    mangled_ppc("?get_team_designator@c_explicit_team@@QBA?AW4e_multiplayer_team_designator@@XZ");

    e_multiplayer_team_designator team_designator = _multiplayer_team_designator_none;
    if (is_named_team())
    {
        team_designator = static_cast<e_multiplayer_team_designator>(static_cast<e_explicit_team_type>(m_explicit_team_type));
    }
    else if (is_global_team_variable())
    {
        long variable_index = get_global_team_variable_index();
        team_designator = get_custom_game_engine_globals()->global_variables.team_variables[variable_index];
    }
    else if (m_explicit_team_type == _explicit_team_type_current_team)
    {
        team_designator = static_cast<e_multiplayer_team_designator>(get_custom_game_engine_globals()->current_team);
    }
    else if (m_explicit_team_type == _explicit_team_type_hud_player_team)
    {
        if (get_custom_game_engine_globals()->hud_player_index != NONE)
        {
            team_designator = current_game_engine()->get_player_team_designator(get_custom_game_engine_globals()->hud_player_index);
        }
    }
    else if (m_explicit_team_type == _explicit_team_type_hud_target_team)
    {
        if (get_custom_game_engine_globals()->hud_target_player_index != NONE)
        {
            team_designator = current_game_engine()->get_player_team_designator(get_custom_game_engine_globals()->hud_target_player_index);
        }
        else if (get_custom_game_engine_globals()->target_object_index != NONE)
        {
            team_designator = object_get_multiplayer(get_custom_game_engine_globals()->target_object_index)->get_team_designator();
        }
    }
    else
    {
        dassert_tag_debug_untracked_jul_11_2011(65, false, "unreachable");
    }

    return team_designator;
};

void c_explicit_team::set_value(e_multiplayer_team_designator team_designator) const
{
    mangled_ppc("?set_value@c_explicit_team@@QBAXW4e_multiplayer_team_designator@@@Z");

    assert_tag_debug_untracked_jul_11_2011(74, is_writeable());
    assert_tag_debug_untracked_jul_11_2011(75, game_is_authoritative() || !is_networked(get_custom_game_engine_definition()));

    if (is_global_team_variable())
    {
        long variable_index = get_global_team_variable_index();
        get_custom_game_engine_globals()->global_variables.team_variables[variable_index] = team_designator;
        simulation_update_global_megalo_variable(_variable_type_team, variable_index);
    }
};

bool c_explicit_team::is_writeable(void) const
{
    mangled_ppc("?is_writeable@c_explicit_team@@QBA_NXZ");

    return is_global_team_variable();
};

bool c_explicit_team::is_networked(s_custom_game_engine_definition const * definition) const
{
    mangled_ppc("?is_networked@c_explicit_team@@QBA_NPBUs_custom_game_engine_definition@@@Z");

    bool networked = false;
    if (is_global_team_variable())
    {
        networked = definition->global_variable_metadata.get_variable_network_state(_variable_type_team, static_cast<unsigned char>(get_global_team_variable_index())) != _megalo_variable_network_state_none;
    }
    else if (m_explicit_team_type == _explicit_team_type_hud_player_team)
    {
        networked = true;
    }

    return networked;
};

void c_explicit_team::initialize_from_global_variable(long variable_index)
{
    mangled_ppc("?initialize_from_global_variable@c_explicit_team@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(126, VALID_INDEX(variable_index, s_global_variable_traits::k_number_of_team_variables));

    m_explicit_team_type = static_cast<e_explicit_team_type>(variable_index + _explicit_team_type_global_team_0);
};

void c_explicit_team::initialize_from_team_designator(e_multiplayer_team_designator team_designator)
{
    mangled_ppc("?initialize_from_team_designator@c_explicit_team@@QAAXW4e_multiplayer_team_designator@@@Z");

    m_explicit_team_type = static_cast<e_explicit_team_type>(team_designator);
};

void c_explicit_team::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_explicit_team@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("explicit-team-type", m_explicit_team_type);
};

void c_explicit_team::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_explicit_team@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("explicit-team-type", &m_explicit_team_type);
};
