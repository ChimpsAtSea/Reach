/* ---------- headers */

#include "omaha\errors\error_report_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool prune_error_geometry;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition global_error_report_categories_block; // "?global_error_report_categories_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_error_report_categories_block_struct_definition; // "?global_error_report_categories_block_struct_definition@@3Us_tag_struct_definition@@A"
// bool prune_error_geometry; // "?prune_error_geometry@@3_NA"

// bool postprocess_error_report(long, void *, bool);

bool postprocess_error_report(long element_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_error_report@@YA_NJPAX_N@Z");

    error_report_category * category = static_cast<error_report_category *>(element);

    if (!for_editor && prune_error_geometry)
    {
        tag_block_delete_all_elements(&category->reports);
    }

    return true;
};

