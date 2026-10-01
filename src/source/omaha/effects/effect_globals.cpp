#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\effect_globals.cpp"
/* ---------- headers */

#include "omaha\effects\effect_globals.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\algorithms\qsort.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static unsigned long const k_effect_holdback_budgets[k_effect_holdback_type_max] =
{
    460, 900, 690, 128, 512, 160, 160, 160, 160, 160, 160, 160, 160, 256,
    256, 2048, 8192, 160, 160, 160, 160, 576, 576, 832, 2048, 448, 256, 576
};

char const * g_effect_priority_names[k_effect_priority_max] =
{
    "normal",
    "high",
    "essential"
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **g_effect_priority_names; // "?g_effect_priority_names@@3PAPBDA"
// char const **global_effect_priority_enum_strings; // "?global_effect_priority_enum_strings@@3PAPBDA"
// struct s_string_list_definition global_effect_priority_enum; // "?global_effect_priority_enum@@3Us_string_list_definition@@A"
// struct s_string_list_definition effect_holdback_type_enum; // "?effect_holdback_type_enum@@3Us_string_list_definition@@A"
// char const **effect_holdback_type_enum_strings; // "?effect_holdback_type_enum_strings@@3PAPBDA"
// struct s_tag_block_definition effect_globals_block; // "?effect_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_effect_globals_vtable; // "?legacy_effect_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group effect_globals_group; // "?effect_globals_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_effect_globals_reference; // "?global_effect_globals_reference@@3Us_tag_reference_definition@@A"
// struct s_effect_globals_definition const *const effect_globals; // "?effect_globals@@3PBUs_effect_globals_definition@@B"
// struct s_tag_group_stream_definition legacy_effect_globals_stream_definition; // "?legacy_effect_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_effect_globals_xsync_declaration; // "?legacy_effect_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_effect_globals_vtable_shim; // "?legacy_effect_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// char const * effect_globals_get_priority_name(unsigned char);
// public: static bool s_effect_component_holdbacks::holdback_compare_proc(void const *, void const *, void const *);
// public: static bool s_effect_component_holdbacks::postprocess_block_proc(long, void *, bool);
// public: struct s_effect_component_holdbacks::s_holdback * s_effect_component_holdbacks::get_holdback_modifiable(long);
// public: struct s_effect_component_holdbacks::s_holdback const * s_effect_component_holdbacks::get_holdback(long) const;
// public: static bool s_effect_globals_definition::component_holdback_compare_proc(void const *, void const *, void const *);
// public: static bool s_effect_globals_definition::postprocess_proc(class c_tag_index, bool);
// public: struct s_effect_component_holdbacks * s_effect_globals_definition::get_component_holdback_modifiable(long);
// public: struct s_effect_component_holdbacks const * s_effect_globals_definition::get_component_holdback(long) const;

char const * effect_globals_get_priority_name(unsigned char priority)
{
    mangled_ppc("?effect_globals_get_priority_name@@YAPBDE@Z");

    assert_tag_debug_untracked_jul_11_2011(20, VALID_INDEX(priority, k_effect_priority_max));
    return g_effect_priority_names[priority];
};

// $TODO nonmatching: the two locals land in swapped stack slots (-0x10/-0xc)
bool s_effect_component_holdbacks::holdback_compare_proc(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?holdback_compare_proc@s_effect_component_holdbacks@@SA_NPBX00@Z");

    s_holdback const * holdback_a = static_cast<s_holdback const *>(element_a);
    s_holdback const * holdback_b = static_cast<s_holdback const *>(element_b);
    return holdback_a->m_priority > holdback_b->m_priority;
};

bool s_effect_component_holdbacks::postprocess_block_proc(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_block_proc@s_effect_component_holdbacks@@SA_NJPAX_N@Z");

    bool postprocess_success = true;
    s_effect_component_holdbacks * holdbacks = static_cast<s_effect_component_holdbacks *>(element);

    qsort_elements(holdbacks->m_holdbacks.address, holdbacks->m_holdbacks.count, sizeof(s_holdback), holdback_compare_proc, NULL);
    for (long priority = 0; priority < k_effect_priority_max; priority++)
    {
        if (priority < holdbacks->m_holdbacks.count)
        {
            s_holdback const * existing_holdback = holdbacks->get_holdback(priority);
            if (existing_holdback->m_priority == priority)
            {
                continue;
            }
        }

        tag_block_insert_element(&holdbacks->m_holdbacks, priority);
        s_holdback * new_holdback = holdbacks->get_holdback_modifiable(priority);
        new_holdback->m_priority = static_cast<e_effect_priority>(priority);
    }
    tag_block_resize(&holdbacks->m_holdbacks, k_effect_priority_max);

    if (!for_editor)
    {
        unsigned long used_budget = 0;
        for (long priority_index = k_effect_priority_max - 1; priority_index >= 0; priority_index--)
        {
            s_holdback * holdback = holdbacks->get_holdback_modifiable(priority_index);
            holdback->m_budget = holdbacks->m_absolute_budget - CEILING(holdbacks->m_absolute_budget, used_budget);
            unsigned long holdback_count = static_cast<unsigned long>(MAX(static_cast<float>(holdback->m_absolute), holdback->m_relative * static_cast<float>(holdbacks->m_absolute_budget) / 100.0f));
            used_budget += holdback_count;
        }
    }

    return postprocess_success;
};



// $TODO nonmatching: the two locals land in swapped stack slots (-0x10/-0xc)
bool s_effect_globals_definition::component_holdback_compare_proc(void const * element_a, void const * element_b, void const * context)
{
    mangled_ppc("?component_holdback_compare_proc@s_effect_globals_definition@@SA_NPBX00@Z");

    s_effect_component_holdbacks const * holdbacks_a = static_cast<s_effect_component_holdbacks const *>(element_a);
    s_effect_component_holdbacks const * holdbacks_b = static_cast<s_effect_component_holdbacks const *>(element_b);
    return holdbacks_a->m_holdback_type > holdbacks_b->m_holdback_type;
};

bool s_effect_globals_definition::postprocess_proc(c_tag_index tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_effect_globals_definition@@SA_NVc_tag_index@@_N@Z");

    bool success = true;
    s_effect_globals_definition * definition = static_cast<s_effect_globals_definition *>(tag_get(k_tag_type, tag_index));

    qsort_elements(definition->m_component_holdbacks.address, definition->m_component_holdbacks.count, sizeof(s_effect_component_holdbacks), component_holdback_compare_proc, NULL);
    for (long holdback_type = 0; holdback_type < k_effect_holdback_type_max; holdback_type++)
    {
        if (holdback_type < definition->m_component_holdbacks.count)
        {
            s_effect_component_holdbacks const * existing_holdbacks = definition->get_component_holdback(holdback_type);
            if (existing_holdbacks->m_holdback_type == holdback_type)
            {
                continue;
            }
        }

        tag_block_insert_element(&definition->m_component_holdbacks, holdback_type);
        s_effect_component_holdbacks * holdbacks = definition->get_component_holdback_modifiable(holdback_type);
        holdbacks->m_holdback_type = static_cast<e_effect_holdback_type>(holdback_type);
        s_effect_component_holdbacks::postprocess_block_proc(NONE, holdbacks, for_editor);
    }
    tag_block_resize(&definition->m_component_holdbacks, k_effect_holdback_type_max);

    for (long holdback_index = 0; holdback_index < k_effect_holdback_type_max; holdback_index++)
    {
        s_effect_component_holdbacks * component_holdbacks = definition->get_component_holdback_modifiable(holdback_index);
        component_holdbacks->m_absolute_budget = k_effect_holdback_budgets[holdback_index];
        s_effect_component_holdbacks::postprocess_block_proc(tag_index, component_holdbacks, for_editor);
    }

    return success;
};



