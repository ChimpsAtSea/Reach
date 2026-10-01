#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_zone_resource_attachment.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_zone_resource_attachment.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_api_interop.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\tag_helpers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual bool c_scenario_structure_bsp_resource_registrar::register_tag_variant(char const *, enum e_scenario_bsp_resource_attachment_type, long, long);
// public: virtual void c_scenario_structure_bsp_resource_registrar::visit_entire_tag_block(char const *, enum e_scenario_bsp_resource_attachment_type, struct s_tag_block const *);
// public: virtual void c_scenario_structure_bsp_resource_registrar::visit_tag_block_element(char const *, enum e_scenario_bsp_resource_attachment_type, struct s_tag_block const *, long);

bool c_scenario_structure_bsp_resource_registrar::register_tag_variant(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, long tag_index, long variant_name)
{
    mangled_ppc("?register_tag_variant@c_scenario_structure_bsp_resource_registrar@@UAA_NPBDW4e_scenario_bsp_resource_attachment_type@@JJ@Z");

    return false;
};

void c_scenario_structure_bsp_resource_registrar::visit_entire_tag_block(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, s_tag_block const * block)
{
    mangled_ppc("?visit_entire_tag_block@c_scenario_structure_bsp_resource_registrar@@UAAXPBDW4e_scenario_bsp_resource_attachment_type@@PBUs_tag_block@@@Z");

    for (long element_index = 0; element_index < block->count; element_index++)
    {
        visit_tag_block_element(name, attachment_type, block, element_index);
    }
};

void c_scenario_structure_bsp_resource_registrar::visit_tag_block_element(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, s_tag_block const * block, long element_index)
{
    mangled_ppc("?visit_tag_block_element@c_scenario_structure_bsp_resource_registrar@@UAAXPBDW4e_scenario_bsp_resource_attachment_type@@PBUs_tag_block@@J@Z");

    c_tag_field_scanner scanner(block, element_index);
    scanner.add_scan_type(_field_tag_reference);
    scanner.add_scan_type(_field_block);
    scanner.add_scan_type(_field_api_interop);
    while (scanner.next())
    {
        switch (scanner.type())
        {
        case _field_block:
        {
            visit_entire_tag_block(name, attachment_type, static_cast<s_tag_block const *>(scanner.address()));
        }
        break;
        case _field_api_interop:
        {
            s_tag_interop const * interop = static_cast<s_tag_interop const *>(scanner.address());
            c_tag_block_from_struct interop_block(tag_interop_descriptor_get(interop), interop->definition->struct_definition);
            visit_entire_tag_block(name, attachment_type, &interop_block);
        }
        break;
        case _field_tag_reference:
        {
            s_tag_reference const * reference = static_cast<s_tag_reference const *>(scanner.address());
            if (reference->index != NONE)
            {
                visit_tag(name, attachment_type, reference->index);
            }
        }
        break;
        default:
        {
            dassert_tag_debug_untracked_jul_11_2011(76, false, "unreachable");
        }
        break;
        }
    }
};

