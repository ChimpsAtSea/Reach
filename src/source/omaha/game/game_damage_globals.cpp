/* ---------- headers */

#include "omaha\game\game_damage_globals.h"
#include "foundation\baselib\algorithms\qsort.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition damage_globals_block_struct_definition; // "?damage_globals_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition damage_globals_block; // "?damage_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition shield_boost_block; // "?shield_boost_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition shield_boost_block_struct_definition; // "?shield_boost_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition game_globals_damage_block_struct_definition; // "?game_globals_damage_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition game_globals_damage_block; // "?game_globals_damage_block@@3Us_tag_block_definition@@A"

// bool game_globals_damage_group_postprocess(long, void *, bool);
// bool damage_armor_modifier_compare_proc(void const *, void const *, void const *);
// bool game_globals_damage_globals_postprocess(long, void *, bool);
// bool damage_group_compare_proc(void const *, void const *, void const *);

bool game_globals_damage_group_postprocess(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?game_globals_damage_group_postprocess@@YA_NJPAX_N@Z");

    bool result = true;
    if (!for_editor)
    {
        s_damage_group_definition * damage_group = static_cast<s_damage_group_definition *>(element);
        qsort_elements(damage_group->armor_modifiers.address, damage_group->armor_modifiers.count, sizeof(s_armor_modifier_definition), damage_armor_modifier_compare_proc, NULL);
    }

    return result;
};

bool damage_armor_modifier_compare_proc(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?damage_armor_modifier_compare_proc@@YA_NPBX00@Z");

    return static_cast<s_armor_modifier_definition const *>(element_a)->name > static_cast<s_armor_modifier_definition const *>(element_b)->name;
};

bool game_globals_damage_globals_postprocess(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?game_globals_damage_globals_postprocess@@YA_NJPAX_N@Z");

    bool result = true;
    if (!for_editor)
    {
        s_damage_globals_definition * damage_globals = static_cast<s_damage_globals_definition *>(element);
        qsort_elements(damage_globals->damage_groups.address, damage_globals->damage_groups.count, sizeof(s_damage_group_definition), damage_group_compare_proc, NULL);
    }

    return result;
};

bool damage_group_compare_proc(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?damage_group_compare_proc@@YA_NPBX00@Z");

    return static_cast<s_damage_group_definition const *>(element_a)->name > static_cast<s_damage_group_definition const *>(element_b)->name;
};

