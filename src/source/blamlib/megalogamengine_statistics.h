#pragma once
#ifndef __MEGALOGAMENGINE_STATISTICS_H__
#define __MEGALOGAMENGINE_STATISTICS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\static_arrays.h"

class c_bitstream;

/* ---------- constants */

// megalo string table capacity (c_string_table<112, 0x4C00>)
long const k_megalo_string_table_maximum_strings = 112;
long const k_megalo_string_table_index_bits = 7;

enum e_megalo_game_statistic_format
{
    _megalo_game_statistic_format_number = 0,
    _megalo_game_statistic_format_number_with_sign,
    _megalo_game_statistic_format_percentage,
    _megalo_game_statistic_format_time,

    k_megalo_game_statistic_format_count
};

enum e_megalo_game_statistic_sort
{
    _megalo_game_statistic_sort_none = -1,
    _megalo_game_statistic_sort_descending,
    _megalo_game_statistic_sort_ascending,
    _megalo_game_statistic_sort_unknown2,

    k_megalo_game_statistic_sort_count
};

enum e_megalo_game_statistic_grouping
{
    _megalo_game_statistic_grouping_enabled = 0,
    _megalo_game_statistic_grouping_disabled,

    k_megalo_game_statistic_grouping_count
};

/* ---------- definitions */

class c_megalo_game_statistic
{
public:
    void encode(c_bitstream * packet) const;
    void decode(c_bitstream * packet);
    bool is_valid() const;
    bool format_value_for_display(long value, c_static_wchar_string<1024> * display_string) const;

protected:
    unsigned char m_name_string_index; // 0x0
    c_enum<e_megalo_game_statistic_format, unsigned char, _megalo_game_statistic_format_number, k_megalo_game_statistic_format_count> m_format; // 0x1
    c_enum<e_megalo_game_statistic_sort, char, _megalo_game_statistic_sort_none, k_megalo_game_statistic_sort_count> m_sort_order; // 0x2
    c_enum<e_megalo_game_statistic_grouping, char, _megalo_game_statistic_grouping_enabled, k_megalo_game_statistic_grouping_count> m_grouping; // 0x3
};
static_assert(sizeof(c_megalo_game_statistic) == 0x4, "c_megalo_game_statistic");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_STATISTICS_H__

