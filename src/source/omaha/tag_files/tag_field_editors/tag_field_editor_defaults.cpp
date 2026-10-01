#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_field_editors\\tag_field_editor_defaults.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_field_editors\tag_field_editor_defaults.h"
#include "blamlib\tag_api_interop_editor.h"
#include "blamlib\tag_resource_editor.h"
#include "blamlib\tag_string_id_editor.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\tag_files\tag_api_interop.h"
#include "omaha\tag_files\tag_field_editors\tag_block_editor.h"
#include "omaha\tag_files\tag_field_editors\tag_data_editor.h"
#include "omaha\tag_files\tag_field_editors\tag_reference_editor.h"
#include "omaha\tag_files\tag_field_editors\tag_struct_editor.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_tag_field_editor * get_default_tag_field_editor(enum e_tag_field, void const *);
// void initialize_tag_field_scanner_for_tag_field_editors(struct tag_field_scan_state *);
// bool tag_field_has_storage_chunk(enum e_tag_field);
// public: virtual class c_tag_field_editor * c_tag_field_editor_manager_default::tag_field_editor_get(enum e_tag_field, void const *);
// public: virtual class c_tag_field_editor * c_tag_field_editor_manager_default::tag_struct_editor_get(struct s_tag_struct_definition const *);
// public: virtual void c_tag_field_editor_manager_default::set_tag_field_scanner_fields(struct tag_field_scan_state *);
// public: virtual struct s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_block_definition(struct s_tag_block_definition const *);
// public: virtual struct s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_resource_definition(struct s_tag_resource_definition const *);
// public: virtual struct s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_interop_definition(struct s_tag_interop_definition const *);

c_tag_field_editor * get_default_tag_field_editor(e_tag_field field_type, void const * definition)
{
    mangled_ppc("?get_default_tag_field_editor@@YAPAVc_tag_field_editor@@W4e_tag_field@@PBX@Z");

    c_tag_field_editor * editor = NULL;
    switch (field_type)
    {
    case _field_struct:
        editor = get_default_tag_struct_editor();
        break;
    case _field_block:
        editor = get_default_tag_block_editor();
        break;
    case _field_data:
        editor = get_default_tag_data_editor();
        break;
    case _field_tag_reference:
        editor = get_default_tag_reference_editor();
        break;
    case _field_string_id:
    case _field_old_string_id:
        editor = get_default_tag_string_id_editor();
        break;
    case _field_pageable_resource:
        editor = get_default_tag_resource_editor();
        break;
    case _field_api_interop:
        editor = get_default_tag_interop_editor();
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(62, false, "unreachable");
        break;
    }

    return editor;
};

void initialize_tag_field_scanner_for_tag_field_editors(tag_field_scan_state * scan_state)
{
    mangled_ppc("?initialize_tag_field_scanner_for_tag_field_editors@@YAXPAUtag_field_scan_state@@@Z");

    tag_field_scan_state_add_field_type(scan_state, _field_struct);
    tag_field_scan_state_add_field_type(scan_state, _field_block);
    tag_field_scan_state_add_field_type(scan_state, _field_pageable_resource);
    tag_field_scan_state_add_field_type(scan_state, _field_data);
    tag_field_scan_state_add_field_type(scan_state, _field_tag_reference);
    tag_field_scan_state_add_field_type(scan_state, _field_string_id);
    tag_field_scan_state_add_field_type(scan_state, _field_old_string_id);
    tag_field_scan_state_add_field_type(scan_state, _field_api_interop);
    scan_state->flags = 13;
};

bool tag_field_has_storage_chunk(e_tag_field field_type)
{
    mangled_ppc("?tag_field_has_storage_chunk@@YA_NW4e_tag_field@@@Z");

    return field_type == _field_struct || field_type == _field_block || field_type == _field_pageable_resource || field_type == _field_data || field_type == _field_tag_reference || field_type == _field_string_id || field_type == _field_old_string_id || field_type == _field_api_interop;
};

c_tag_field_editor * c_tag_field_editor_manager_default::tag_field_editor_get(e_tag_field field_type, void const * definition)
{
    mangled_ppc("?tag_field_editor_get@c_tag_field_editor_manager_default@@UAAPAVc_tag_field_editor@@W4e_tag_field@@PBX@Z");

    return get_default_tag_field_editor(field_type, definition);
};

c_tag_field_editor * c_tag_field_editor_manager_default::tag_struct_editor_get(s_tag_struct_definition const * struct_definition)
{
    mangled_ppc("?tag_struct_editor_get@c_tag_field_editor_manager_default@@UAAPAVc_tag_field_editor@@PBUs_tag_struct_definition@@@Z");

    return tag_field_editor_get(_field_struct, struct_definition);
};

void c_tag_field_editor_manager_default::set_tag_field_scanner_fields(tag_field_scan_state * scan_state)
{
    mangled_ppc("?set_tag_field_scanner_fields@c_tag_field_editor_manager_default@@UAAXPAUtag_field_scan_state@@@Z");

    initialize_tag_field_scanner_for_tag_field_editors(scan_state);
};

s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_block_definition(s_tag_block_definition const * block_definition)
{
    mangled_ppc("?get_struct_from_block_definition@c_tag_field_editor_manager_default@@UAAPBUs_tag_struct_definition@@PBUs_tag_block_definition@@@Z");

    return block_definition->struct_definition;
};

s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_resource_definition(s_tag_resource_definition const * resource_definition)
{
    mangled_ppc("?get_struct_from_resource_definition@c_tag_field_editor_manager_default@@UAAPBUs_tag_struct_definition@@PBUs_tag_resource_definition@@@Z");

    return resource_definition->struct_definition;
};

s_tag_struct_definition const * c_tag_field_editor_manager_default::get_struct_from_interop_definition(s_tag_interop_definition const * interop_definition)
{
    mangled_ppc("?get_struct_from_interop_definition@c_tag_field_editor_manager_default@@UAAPBUs_tag_struct_definition@@PBUs_tag_interop_definition@@@Z");

    return interop_definition->get_descriptor_definition();
};

