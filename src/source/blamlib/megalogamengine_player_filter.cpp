/* ---------- headers */

#include "blamlib\megalogamengine_player_filter.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_default.h"
#include "omaha\game\megalogamengine\megalogamengine_internal.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_player_filter::initialize(enum e_player_filter_type);
// public: bool c_player_filter::operator==(class c_player_filter const &) const;
// public: bool c_player_filter::operator!=(class c_player_filter const &) const;
// public: class c_string_builder c_player_filter::describe(void) const;
// public: void c_player_filter::encode(class c_bitstream *) const;
// public: void c_player_filter::decode(class c_bitstream *);
// public: void c_player_filter_modifier::encode(class c_bitstream *) const;
// public: void c_player_filter_modifier::decode(class c_bitstream *);
// public: bool c_player_filter::player_matches_filter(long, enum e_multiplayer_team_designator) const;
// public: bool c_player_filter::team_matches_filter(enum e_multiplayer_team_designator, enum e_multiplayer_team_designator) const;
// public: void c_player_filter_modifier::apply_to(class c_player_filter *) const;
// public: c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>(enum e_player_filter_type);
// public: enum e_player_filter_type c_enum_no_init<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::operator enum e_player_filter_type(void) const;
// public: void c_bitstream::write_enum<class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver> *);
// public: bool c_enum_no_init<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::set_raw_value(unsigned char);
// long required_encoding_bits_for_enum<class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver> >(class c_enum<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>);
// public: static enum e_player_filter_type c_enum_no_init<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static unsigned char c_enum_no_init<enum e_player_filter_type, unsigned char, 0, 6, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

void c_player_filter::initialize(e_player_filter_type filter_type)
{
    mangled_ppc("?initialize@c_player_filter@@QAAXW4e_player_filter_type@@@Z");

    m_filter_type = filter_type;

    switch (m_filter_type)
    {
    case _player_filter_type_no_one:
    case _player_filter_type_allies:
    case _player_filter_type_enemies:
    case _player_filter_type_player_mask:
    case _player_filter_type_default:
        m_player_mask.clear();
        break;
    case _player_filter_type_everyone:
        m_player_mask.set_all();
        break;
    }
};

bool c_player_filter::operator==(c_player_filter const & other) const
{
    mangled_ppc("??8c_player_filter@@QBA_NABV0@@Z");

    return m_filter_type == other.m_filter_type && m_player_mask == other.m_player_mask;
};

bool c_player_filter::operator!=(c_player_filter const & other) const
{
    mangled_ppc("??9c_player_filter@@QBA_NABV0@@Z");

    return !(*this == other);
};

c_string_builder c_player_filter::describe(void) const
{
    mangled_ppc("?describe@c_player_filter@@QBA?AVc_string_builder@@XZ");

    switch (m_filter_type)
    {
    case _player_filter_type_no_one:
        return c_string_builder("no_one");
    case _player_filter_type_everyone:
        return c_string_builder("everyone");
    case _player_filter_type_allies:
        return c_string_builder("allies");
    case _player_filter_type_enemies:
        return c_string_builder("enemies");
    case _player_filter_type_player_mask:
        return c_string_builder(m_player_mask.to_string().get_string());
    case _player_filter_type_default:
        return c_string_builder("default");
    }

    return c_string_builder("INVALID");
};

void c_player_filter::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_player_filter@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("type", m_filter_type);
    if (m_filter_type == _player_filter_type_player_mask)
    {
        bitstream->write_flags("player-mask", m_player_mask);
    }
};

void c_player_filter::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_player_filter@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("type", &m_filter_type);
    if (m_filter_type == _player_filter_type_player_mask)
    {
        bitstream->read_flags("player-mask", &m_player_mask);
    }
};

void c_player_filter_modifier::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_player_filter_modifier@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("type", m_filter_type);
    if (m_filter_type == _player_filter_type_player_mask)
    {
        m_player.encode(bitstream);
        m_value.encode(bitstream);
    }
};

void c_player_filter_modifier::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_player_filter_modifier@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("type", &m_filter_type);
    if (m_filter_type == _player_filter_type_player_mask)
    {
        m_player.decode(bitstream);
        m_value.decode(bitstream);
    }
};

bool c_player_filter::player_matches_filter(long player_index, e_multiplayer_team_designator team_designator) const
{
    mangled_ppc("?player_matches_filter@c_player_filter@@QBA_NJW4e_multiplayer_team_designator@@@Z");

    bool matches = false;

    switch (m_filter_type)
    {
    case _player_filter_type_no_one:
    case _player_filter_type_default:
        matches = false;
        break;
    case _player_filter_type_everyone:
        matches = true;
        break;
    case _player_filter_type_allies:
        matches = get_disposition_between_team_designators(current_game_engine()->get_player_team_designator(player_index), team_designator) == _disposition_friendly;
        break;
    case _player_filter_type_enemies:
        matches = get_disposition_between_team_designators(current_game_engine()->get_player_team_designator(player_index), team_designator) == _disposition_enemy;
        break;
    case _player_filter_type_player_mask:
        if (player_index != NONE)
        {
            matches = m_player_mask.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(player_index));
        }
        break;
    }

    return matches;
};

bool c_player_filter::team_matches_filter(e_multiplayer_team_designator team_designator, e_multiplayer_team_designator other_team_designator) const
{
    mangled_ppc("?team_matches_filter@c_player_filter@@QBA_NW4e_multiplayer_team_designator@@0@Z");

    bool matches = false;

    switch (m_filter_type)
    {
    case _player_filter_type_no_one:
    case _player_filter_type_default:
        matches = false;
        break;
    case _player_filter_type_everyone:
        matches = true;
        break;
    case _player_filter_type_allies:
        matches = get_disposition_between_team_designators(team_designator, other_team_designator) == _disposition_friendly;
        break;
    case _player_filter_type_enemies:
        matches = get_disposition_between_team_designators(team_designator, other_team_designator) == _disposition_enemy;
        break;
    case _player_filter_type_player_mask:
        matches = false;
        break;
    }

    return matches;
};

void c_player_filter_modifier::apply_to(c_player_filter * filter) const
{
    mangled_ppc("?apply_to@c_player_filter_modifier@@QBAXPAVc_player_filter@@@Z");

    switch (filter->m_filter_type)
    {
    case _player_filter_type_no_one:
    case _player_filter_type_allies:
    case _player_filter_type_enemies:
    case _player_filter_type_default:
        filter->m_player_mask.clear();
        break;
    case _player_filter_type_everyone:
        filter->m_player_mask.set_all();
        break;
    case _player_filter_type_player_mask:
        break;
    }

    switch (m_filter_type)
    {
    case _player_filter_type_no_one:
    case _player_filter_type_allies:
    case _player_filter_type_enemies:
    case _player_filter_type_default:
        filter->m_player_mask.clear();
        break;
    case _player_filter_type_everyone:
        filter->m_player_mask.set_all();
        break;
    case _player_filter_type_player_mask:
    {
        long player_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(m_player.get_player_index());
        filter->m_player_mask.set(player_absolute_index, m_value.evaluate() != 0);
        break;
    }
    }

    filter->m_filter_type = m_filter_type;
};
