#pragma once
#ifndef __STRUCTURE_SEAM_DEFINITIONS_H__
#define __STRUCTURE_SEAM_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\system\system_identity_xenon.h"
#include "omaha\structures\structure_manifest_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    STRUCTURE_SEAMS_TAG = 'stse',
};

/* ---------- definitions */

struct s_structure_seam_identifier
{
    s_system_global_unique_identifier identifier; // 0x0
};
static_assert(sizeof(s_structure_seam_identifier) == 0x10, "s_structure_seam_identifier");

struct s_structure_seams
{
    s_structure_manifest_definition structure_manifest; // 0x0
    long version; // 0x3C
    s_tag_block errors; // 0x40
    s_tag_block seams; // 0x4C
    s_tag_block seam_triangle_mopp_codes; // 0x58
};
static_assert(sizeof(s_structure_seams) == 0x64, "s_structure_seams");

/* ---------- prototypes */

bool structure_seams_postprocess(long structure_seams_index, bool for_editor);
bool structure_seam_identifiers_are_equal(s_structure_seam_identifier const * structure_seam_identifier0, s_structure_seam_identifier const * structure_seam_identifier1);

/* ---------- globals */

/* ---------- public code */

#endif // __STRUCTURE_SEAM_DEFINITIONS_H__

