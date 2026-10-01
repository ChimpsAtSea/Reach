#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\bitmaps\\bitmap_tag_definition.cpp"
/* ---------- headers */

#include "omaha\bitmaps\bitmap_tag_definition.h"
#include "omaha\bitmaps\bitmaps.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include <string.h>

/* ---------- constants */

// element sizes of the v1 and v2 bitmap data blocks
long const k_old_bitmap_data_size = 0x30;
long const k_new_bitmap_data_size = 0x2C;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **bitmap_types_strings; // "?bitmap_types_strings@@3PAPBDA"
// struct s_string_list_definition bitmap_types; // "?bitmap_types@@3Us_string_list_definition@@A"
// char const **bitmap_curve_enum_strings; // "?bitmap_curve_enum_strings@@3PAPBDA"
// struct s_string_list_definition bitmap_curve_enum; // "?bitmap_curve_enum@@3Us_string_list_definition@@A"
// struct s_tag_field *bitmap_tags_v1; // "?bitmap_tags_v1@@3PAUs_tag_field@@A"
// struct s_tag_field *bitmap_tags_v2; // "?bitmap_tags_v2@@3PAUs_tag_field@@A"
// struct s_tag_block_definition bitmap_data_block_def; // "?bitmap_data_block_def@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition bitmap_data_block_def_struct_definition; // "?bitmap_data_block_def_struct_definition@@3Us_tag_struct_definition@@A"

// bool load_old_bitmap(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *);
// bool postprocess_bitmap(long, void *, bool);
// void delete_bitmap(void *);

bool load_old_bitmap(unsigned long old_version, s_tag_field const * old_fields, long old_count, long old_size, void * old_data, s_tag_field const * new_fields, long new_count, long new_size, void * new_data)
{
    mangled_ppc("?load_old_bitmap@@YA_NKPBUs_tag_field@@JJPAX0JJ1@Z");

    if (old_version != 0)
    {
        assert_tag_debug_untracked_jul_11_2011(329, 0);
        return false;
    }

    long min_count = old_count > new_count ? new_count : old_count;
    char * old_bitmaps = static_cast<char *>(old_data);
    char * new_bitmaps = static_cast<char *>(new_data);
    memset(new_bitmaps, 0, new_count * k_new_bitmap_data_size);
    for (long bitmap_index = 0; bitmap_index < min_count; bitmap_index++)
    {
        char * old_bitmap = old_bitmaps + bitmap_index * k_old_bitmap_data_size;
        char * new_bitmap = new_bitmaps + bitmap_index * k_new_bitmap_data_size;
        memcpy(new_bitmap, old_bitmap, k_old_bitmap_data_size);
        memset(old_bitmap, 0, k_old_bitmap_data_size);
    }

    return true;
};

bool postprocess_bitmap(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_bitmap@@YA_NJPAX_N@Z");

    bool result = true;
    if (!for_editor)
    {
        bitmap_data * bitmap = static_cast<bitmap_data *>(data);
        result = bitmap_verify(bitmap, false);
    }

    return result;
};

void delete_bitmap(void * data)
{
    mangled_ppc("?delete_bitmap@@YAXPAX@Z");

    bitmap_data * bitmap = static_cast<bitmap_data *>(data);
    bitmap_delete(bitmap);
};

