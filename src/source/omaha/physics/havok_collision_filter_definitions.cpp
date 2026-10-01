#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\havok_collision_filter_definitions.cpp"
/* ---------- headers */

#include "omaha\physics\havok_collision_filter_definitions.h"
#include "omaha\physics\havok_collision_filter.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * collision_filter_enum_strings[k_havok_group_count] =
{
    "everything",
    "environment",
    "environment only",
    "small crate",
    "crate",
    "huge crate",
    "item",
    "projectile",
    "machine",
    "early mover machine",
    "creature",
    "biped",
    "dead biped",
    "super collidable ragdoll",
    "ragdoll",
    "vehicle",
    "vehicle friction points",
    "forge dynamic scenary",
    "small expensive plant",
    "expensive plant",
    "proxy",
    "huge vehicle",
    "behemoth",
    "character posture",
    "item blocker",
    "user00",
    "user01",
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **collision_filter_enum_strings; // "?collision_filter_enum_strings@@3PAPBDA"
// struct s_string_list_definition collision_filter_enum; // "?collision_filter_enum@@3Us_string_list_definition@@A"
// struct s_tag_block_definition havok_collision_filter_block; // "?havok_collision_filter_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_havok_collision_filter_vtable; // "?legacy_havok_collision_filter_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group havok_collision_filter_group; // "?havok_collision_filter_group@@3Us_tag_group@@A"
// struct s_tag_group_stream_definition legacy_havok_collision_filter_stream_definition; // "?legacy_havok_collision_filter_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_havok_collision_filter_xsync_declaration; // "?legacy_havok_collision_filter_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_havok_collision_filter_vtable_shim; // "?legacy_havok_collision_filter_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool havok_collision_filter_postprocess(long, bool);
// char * havok_collision_filter_group_format(long, __int64, struct s_tag_block *, long, char *, long);
// void havok_collision_filter_fixup(long);

bool havok_collision_filter_postprocess(long tag_index, bool for_editor)
{
    mangled_ppc("?havok_collision_filter_postprocess@@YA_NJ_N@Z");

    s_havok_collision_filter_definition * definition = static_cast<s_havok_collision_filter_definition *>(tag_get(k_havok_collision_filter_definition_tag, tag_index));
    tag_block_resize(&definition->groups, k_havok_group_count);
    if (definition->groups.count > 0)
    {
        s_havok_collision_filter_group * everything_group = static_cast<s_havok_collision_filter_group *>(tag_block_get_element_with_size(&definition->groups, 0, sizeof(s_havok_collision_filter_group)));
        everything_group->flags = static_cast<unsigned long>(MASK_64(definition->groups.count));
    }

    for (long group_index = 0; group_index < definition->groups.count; group_index++)
    {
        s_havok_collision_filter_group * group = static_cast<s_havok_collision_filter_group *>(tag_block_get_element_with_size(&definition->groups, group_index, sizeof(s_havok_collision_filter_group)));
        for (long other_group_index = 0; other_group_index < definition->groups.count; other_group_index++)
        {
            s_havok_collision_filter_group * other_group = static_cast<s_havok_collision_filter_group *>(tag_block_get_element_with_size(&definition->groups, other_group_index, sizeof(s_havok_collision_filter_group)));
            if (TEST_BIT(group->flags, other_group_index))
            {
                SET_BIT(other_group->flags, group_index, true);
            }
        }
    }

    if (!for_editor)
    {
        havok_collision_filter_build(definition);
    }

    return true;
};

char * havok_collision_filter_group_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?havok_collision_filter_group_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(197, VALID_INDEX(element_index, k_havok_group_count));
    csnzprintf(buffer, buffer_size, "%s", collision_filter_enum_strings[element_index]);

    return buffer;
};

void havok_collision_filter_fixup(long havok_collision_filter_definition_index)
{
    mangled_ppc("?havok_collision_filter_fixup@@YAXJ@Z");

    havok_collision_filter_fixup(static_cast<s_havok_collision_filter_definition *>(tag_get(k_havok_collision_filter_definition_tag, havok_collision_filter_definition_index)));
};
