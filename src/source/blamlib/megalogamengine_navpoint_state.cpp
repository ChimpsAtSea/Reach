/* ---------- headers */

#include "blamlib\megalogamengine_navpoint_state.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * navpoint_icon_names[k_chud_navpoint_icon_type_count + 1] =
{
    "none",
    "speaker",
    "dead_teammate",
    "unused",
    "target",
    "destination",
    "bomb",
    "flag",
    "skull",
    "king",
    "vip",
    "lock",
    "num",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "ordnance",
    "interface",
    "recon",
    "ammunition",
    "recover",
    "defend",
    "neutralize",
    "coop spawning",
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **navpoint_icon_names; // "?navpoint_icon_names@@3PAPBDA"

// public: void s_megalogamengine_navpoint_state::initialize(void);
// public: bool s_megalogamengine_navpoint_state::operator==(struct s_megalogamengine_navpoint_state const &) const;
// public: bool s_megalogamengine_navpoint_state::operator!=(struct s_megalogamengine_navpoint_state const &) const;
// public: void s_megalogamengine_navpoint_state::encode(class c_bitstream *) const;
// public: void s_megalogamengine_navpoint_state::decode(class c_bitstream *);
// public: c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>::c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>(enum e_chud_navpoint_icon_type);
// public: c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>(enum e_navpoint_priority);
// public: bool c_enum_no_init<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::operator==(enum e_navpoint_priority) const;
// public: void c_bitstream::write_enum<class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>);
// public: void c_bitstream::write_enum<class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>);
// public: void c_bitstream::write_index<101, unsigned char>(char const *, unsigned char);
// public: void c_bitstream::read_enum<class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver> *);
// public: void c_bitstream::read_enum<class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver> *);
// public: long c_bitstream::read_index<101>(char const *);
// public: bool c_enum_no_init<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>::set_raw_value(char);
// public: bool c_enum_no_init<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::set_raw_value(unsigned char);
// long required_encoding_bits_for_enum<class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver> >(class c_enum<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>);
// long required_encoding_bits_for_enum<class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(class c_enum<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>);
// long required_encoding_bits_for_index<101>(void);
// public: static enum e_chud_navpoint_icon_type c_enum_no_init<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum e_chud_navpoint_icon_type, char, -1, 28, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);
// public: static enum e_navpoint_priority c_enum_no_init<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static unsigned char c_enum_no_init<enum e_navpoint_priority, unsigned char, 0, 4, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

void s_megalogamengine_navpoint_state::initialize(void)
{
    mangled_ppc("?initialize@s_megalogamengine_navpoint_state@@QAAXXZ");

    text.initialize();
    filter.initialize(_player_filter_type_no_one);
    icon = _chud_navpoint_icon_type_none;
    priority = _navpoint_priority_normal;
    timer_index = NONE;
    min_distance = NONE;
    max_distance = NONE;
};

bool s_megalogamengine_navpoint_state::operator==(s_megalogamengine_navpoint_state const & other) const
{
    mangled_ppc("??8s_megalogamengine_navpoint_state@@QBA_NABU0@@Z");

    return text == other.text &&
        filter == other.filter &&
        icon == other.icon &&
        priority == other.priority &&
        timer_index == other.timer_index &&
        min_distance == other.min_distance &&
        max_distance == other.max_distance;
};

bool s_megalogamengine_navpoint_state::operator!=(s_megalogamengine_navpoint_state const & other) const
{
    mangled_ppc("??9s_megalogamengine_navpoint_state@@QBA_NABU0@@Z");

    return !(*this == other);
};

void s_megalogamengine_navpoint_state::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@s_megalogamengine_navpoint_state@@QBAXPAVc_bitstream@@@Z");

    text.encode(bitstream);
    filter.encode(bitstream);
    bitstream->write_enum("icon", icon);
    bitstream->write_enum("priority", priority);
    bitstream->write_index<k_navpoint_timer_index_count>("timer-index", timer_index);
    bitstream->write_index<k_navpoint_distance_count>("min-distance", min_distance);
    bitstream->write_index<k_navpoint_distance_count>("max-distance", max_distance);
};

void s_megalogamengine_navpoint_state::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@s_megalogamengine_navpoint_state@@QAAXPAVc_bitstream@@@Z");

    text.decode(bitstream);
    filter.decode(bitstream);
    bitstream->read_enum("icon", &icon);
    bitstream->read_enum("priority", &priority);
    timer_index = static_cast<char>(bitstream->read_index<k_navpoint_timer_index_count>("timer-index"));
    min_distance = static_cast<unsigned char>(bitstream->read_index<k_navpoint_distance_count>("min-distance"));
    max_distance = static_cast<unsigned char>(bitstream->read_index<k_navpoint_distance_count>("max-distance"));
};
