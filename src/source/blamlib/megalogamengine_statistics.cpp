/* ---------- headers */

#include "blamlib\megalogamengine_statistics.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries.h"
#include "omaha\interface\user_interface_utilities.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_megalo_game_statistic::encode(class c_bitstream *) const;
// public: void c_megalo_game_statistic::decode(class c_bitstream *);
// public: bool c_megalo_game_statistic::is_valid(void) const;
// public: bool c_megalo_game_statistic::format_value_for_display(long, class c_static_wchar_string<1024> *) const;
// public: enum e_megalo_game_statistic_format c_enum_no_init<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>::operator enum e_megalo_game_statistic_format(void) const;
// public: bool c_enum_no_init<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>::in_range(void) const;
// public: bool c_enum_no_init<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>::in_range(void) const;
// public: bool c_enum_no_init<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_bitstream::write_enum<class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>);
// public: void c_bitstream::write_enum<class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>);
// public: void c_bitstream::write_enum<class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver> *);
// public: void c_bitstream::read_enum<class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver> *);
// public: void c_bitstream::read_enum<class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver> *);
// public: void c_enum_no_init<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>::set_raw_value(unsigned char);
// public: void c_enum_no_init<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>::set_raw_value(char);
// public: void c_enum_no_init<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>::set_raw_value(char);
// long required_encoding_bits_for_enum<class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver> >(class c_enum<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>);
// long required_encoding_bits_for_enum<class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver> >(class c_enum<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>);
// long required_encoding_bits_for_enum<class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver> >(class c_enum<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>);
// public: static enum e_megalo_game_statistic_format c_enum_no_init<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static unsigned char c_enum_no_init<enum e_megalo_game_statistic_format, unsigned char, 0, 4, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);
// public: static enum e_megalo_game_statistic_sort c_enum_no_init<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum e_megalo_game_statistic_sort, char, -1, 3, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);
// public: static enum e_megalo_game_statistic_grouping c_enum_no_init<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static char c_enum_no_init<enum e_megalo_game_statistic_grouping, char, 0, 2, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

void c_megalo_game_statistic::encode(c_bitstream * packet) const
{
    mangled_ppc("?encode@c_megalo_game_statistic@@QBAXPAVc_bitstream@@@Z");

    packet->write_integer("name-string-index", m_name_string_index, k_megalo_string_table_index_bits);
    packet->write_enum("format", m_format);
    packet->write_enum("sort-order", m_sort_order);
    packet->write_enum("grouping", m_grouping);
};

void c_megalo_game_statistic::decode(c_bitstream * packet)
{
    mangled_ppc("?decode@c_megalo_game_statistic@@QAAXPAVc_bitstream@@@Z");

    m_name_string_index = static_cast<unsigned char>(packet->read_integer("name-string-index", k_megalo_string_table_index_bits));
    packet->read_enum("format", &m_format);
    packet->read_enum("sort-order", &m_sort_order);
    packet->read_enum("grouping", &m_grouping);
};

bool c_megalo_game_statistic::is_valid() const
{
    mangled_ppc("?is_valid@c_megalo_game_statistic@@QBA_NXZ");

    bool valid = m_name_string_index == NONE || VALID_INDEX(m_name_string_index, k_megalo_string_table_maximum_strings);
    valid = valid && m_format.in_range();
    valid = valid && m_sort_order.in_range();
    valid = valid && m_grouping.in_range();

    return valid;
};

bool c_megalo_game_statistic::format_value_for_display(long value, c_static_wchar_string<1024> * display_string) const
{
    mangled_ppc("?format_value_for_display@c_megalo_game_statistic@@QBA_NJPAV?$c_static_wchar_string@$0EAA@@@@Z");

    bool result = true;

    switch (m_format)
    {
    case _megalo_game_statistic_format_number:
    {
        display_string->print(L"%i", value);
    }
    break;
    case _megalo_game_statistic_format_number_with_sign:
    {
        display_string->print(L"%+i", value);
    }
    break;
    case _megalo_game_statistic_format_percentage:
    {
        display_string->print(L"%i%%", value);
    }
    break;
    case _megalo_game_statistic_format_time:
    {
        result = user_interface_get_timespan_string(value, _user_interface_timespan_format_hours_minutes_seconds, false, display_string);
    }
    break;
    default:
    {
        event_wrapped(_event_error, "megalo: megalo_game_statistic: unknown format in format_value_for_display");
        display_string->clear();
        result = false;
    }
    break;
    }

    return result;
};

