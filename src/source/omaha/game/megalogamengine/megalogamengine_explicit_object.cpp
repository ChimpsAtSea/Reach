#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_object.cpp"
/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_explicit_object.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine_megalo.h"
#include "blamlib\megalogamengine.h"
#include "networkinglib\simulation_game_action_megalo.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: long c_explicit_object::get_object_index(void) const;
// private: bool c_explicit_object::is_global_object_variable(void) const;
// private: long c_explicit_object::get_global_object_variable_index(void) const;
// public: void c_explicit_object::set_value(long) const;
// public: void c_explicit_object::initialize_from_global_variable(long);
// public: bool c_explicit_object::is_writeable(void) const;
// public: bool c_explicit_object::is_networked(struct s_custom_game_engine_definition const *) const;
// public: void c_explicit_object::encode(class c_bitstream *) const;
// public: void c_explicit_object::decode(class c_bitstream *);
// public: class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver> & c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>::operator=(enum c_explicit_object::e_explicit_object_type);
// public: void c_bitstream::write_enum<class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver> >(char const *, class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver> *);
// public: bool c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>::set_raw_value(char);
// long required_encoding_bits_for_enum<class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver> >(class c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>);
// public: static enum c_explicit_object::e_explicit_object_type c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum c_explicit_object::e_explicit_object_type, char, 0, 21, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

long c_explicit_object::get_object_index(void) const
{
    mangled_ppc("?get_object_index@c_explicit_object@@QBAJXZ");

    long object_index = NONE;
    if (m_explicit_object_type == _explicit_object_type_none)
    {
        object_index = NONE;
    }
    else if (is_global_object_variable())
    {
        long variable_index = get_global_object_variable_index();
        object_index = get_custom_game_engine_globals()->global_variables.object_variables[variable_index];
    }
    else if (m_explicit_object_type == _explicit_object_type_current_object)
    {
        object_index = get_custom_game_engine_globals()->current_object_index;
    }
    else if (m_explicit_object_type == _explicit_object_type_target_object)
    {
        object_index = get_custom_game_engine_globals()->target_object_index;
    }
    else if (m_explicit_object_type == _explicit_object_type_killed_object)
    {
        object_index = get_custom_game_engine_globals()->killed_object_index;
    }
    else if (m_explicit_object_type == _explicit_object_type_killer_object)
    {
        object_index = get_custom_game_engine_globals()->killer_object_index;
    }

    return object_index;
};

void c_explicit_object::set_value(long object_index) const
{
    mangled_ppc("?set_value@c_explicit_object@@QBAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(57, is_writeable());
    assert_tag_debug_untracked_jul_11_2011(58, game_is_authoritative() || !is_networked(get_custom_game_engine_definition()));

    if (is_global_object_variable())
    {
        long variable_index = get_global_object_variable_index();
        get_custom_game_engine_globals()->global_variables.object_variables[variable_index] = object_index;
        simulation_update_global_megalo_variable(_variable_type_object, variable_index);
    }
};

void c_explicit_object::initialize_from_global_variable(long variable_index)
{
    mangled_ppc("?initialize_from_global_variable@c_explicit_object@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(75, VALID_INDEX(variable_index, s_global_variable_traits::k_number_of_object_variables));

    m_explicit_object_type = static_cast<e_explicit_object_type>(variable_index + _explicit_object_type_global_object_0);
};

bool c_explicit_object::is_writeable(void) const
{
    mangled_ppc("?is_writeable@c_explicit_object@@QBA_NXZ");

    return is_global_object_variable();
};

bool c_explicit_object::is_networked(s_custom_game_engine_definition const * definition) const
{
    mangled_ppc("?is_networked@c_explicit_object@@QBA_NPBUs_custom_game_engine_definition@@@Z");

    bool networked = false;
    if (is_global_object_variable())
    {
        networked = definition->global_variable_metadata.get_variable_network_state(_variable_type_object, static_cast<unsigned char>(get_global_object_variable_index())) != _megalo_variable_network_state_none;
    }

    return networked;
};

void c_explicit_object::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_explicit_object@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("explicit-object-type", m_explicit_object_type);
};

void c_explicit_object::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_explicit_object@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("explicit-object-type", &m_explicit_object_type);
};

