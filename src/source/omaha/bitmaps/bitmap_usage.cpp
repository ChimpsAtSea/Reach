#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\bitmaps\\bitmap_usage.cpp"
/* ---------- headers */

#include "omaha\bitmaps\bitmap_usage.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static class c_bitmap_usage const *const const c_bitmap_usage::k_globals; // "?k_globals@c_bitmap_usage@@2QBV1@B"
// char const **bitmap_usage_global_enum_strings; // "?bitmap_usage_global_enum_strings@@3PAPBDA"
// struct s_string_list_definition bitmap_usage_global_enum; // "?bitmap_usage_global_enum@@3Us_string_list_definition@@A"
// public: static char const **c_bitmap_usage::k_global_suffixes; // "?k_global_suffixes@c_bitmap_usage@@2PAPBDA"
// char const **bitmap_usage_format_def_strings; // "?bitmap_usage_format_def_strings@@3PAPBDA"
// struct s_string_list_definition bitmap_usage_format_def; // "?bitmap_usage_format_def@@3Us_string_list_definition@@A"
// struct s_tag_struct_definition bitmap_usage_block_struct_definition; // "?bitmap_usage_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition bitmap_usage_block; // "?bitmap_usage_block@@3Us_tag_block_definition@@A"
// struct s_tag_group bitmap_usage_group; // "?bitmap_usage_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_bitmap_usage_vtable; // "?legacy_bitmap_usage_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_bitmap_usage_stream_definition; // "?legacy_bitmap_usage_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_bitmap_usage_xsync_declaration; // "?legacy_bitmap_usage_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_bitmap_usage_vtable_shim; // "?legacy_bitmap_usage_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static long c_bitmap_usage::get_pc_bitmap_format(enum c_bitmap_usage::e_format);
// public: static long c_bitmap_usage::get_xenon_bitmap_format(enum c_bitmap_usage::e_format);
// bool operator!=<enum c_bitmap_usage::e_format>(enum c_bitmap_usage::e_format const &, enum e_none_sentinel const &);
// bool operator==<enum c_bitmap_usage::e_format>(enum c_bitmap_usage::e_format const &, enum e_none_sentinel const &);

long c_bitmap_usage::get_pc_bitmap_format(e_format format)
{
    mangled_ppc("?get_pc_bitmap_format@c_bitmap_usage@@SAJW4e_format@1@@Z");

    static long const k_pc_bitmap_formats[k_format_count] =
    {
        16, 16, 11, 22, 22, 1, 1, 1,
        NONE, NONE, NONE, NONE, NONE, NONE, 14, 15,
        16, 11, 3, 37, 29, 30, 25, 24,
        2, 2, 2, 3, 9, NONE, 1, NONE,
        NONE, 32, 33, 34, 27, NONE, NONE, NONE,
        27, 1, 1, 11, 11, 11, NONE, 0,
        0, 0, NONE, NONE, NONE, NONE, 22, 22,
        22, 31, 28
    };

    long result = NONE;
    if (format != NONE)
    {
        assert_tag_debug_untracked_jul_11_2011(96, format>=0 && format<k_format_count);
        result = k_pc_bitmap_formats[format];
    }

    return result;
};

long c_bitmap_usage::get_xenon_bitmap_format(e_format format)
{
    mangled_ppc("?get_xenon_bitmap_format@c_bitmap_usage@@SAJW4e_format@1@@Z");

    static long const k_xenon_bitmap_formats[k_format_count] =
    {
        16, 16, 11, 39, 22, 43, 1, 43,
        NONE, NONE, NONE, NONE, NONE, NONE, 14, 15,
        16, 11, 3, 37, 29, 30, 25, 24,
        2, 35, 36, 44, 9, NONE, 1, NONE,
        NONE, 32, 33, 34, 27, NONE, NONE, NONE,
        26, 41, 43, 45, 46, 47, NONE, 40,
        42, 0, NONE, NONE, NONE, NONE, 38, 39,
        22, 31, 28
    };

    long result = NONE;
    if (format != NONE)
    {
        assert_tag_debug_untracked_jul_11_2011(187, format>=0 && format<k_format_count);
        result = k_xenon_bitmap_formats[format];
    }

    return result;
};

