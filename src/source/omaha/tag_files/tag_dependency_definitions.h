#pragma once
#ifndef __TAG_DEPENDENCY_DEFINITIONS_H__
#define __TAG_DEPENDENCY_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_reference_definition;

// element of tag_dependency_block_definition (size from add_single_tag_dependency)
struct s_tag_dependency_definition
{
    s_tag_reference dependency; // 0x0
    unsigned long flags; // 0x10 (copied from s_tag_reference_definition::flags)
};
static_assert(sizeof(s_tag_dependency_definition) == 0x14, "s_tag_dependency_definition");

// element of tag_dependency_list_block (the 'want' alternate stream root)
struct s_tag_dependency_list_definition
{
    s_tag_block dependencies; // 0x0
};
static_assert(sizeof(s_tag_dependency_list_definition) == 0xC, "s_tag_dependency_list_definition");

/* ---------- prototypes */

extern bool build_tag_dependency_list_from_tag(s_tag_block const * block, s_tag_block * out_dependency_list_block);
extern bool add_tag_dependencies_from_block(s_tag_block const * block, s_tag_dependency_list_definition * out_dependency_list);
extern bool add_single_tag_dependency(s_tag_reference const * reference, s_tag_reference_definition const * reference_definition, s_tag_dependency_list_definition * out_dependency_list);
extern s_tag_block * tag_try_and_get_tag_dependency_list(long tag_index);
extern s_tag_block * tag_get_or_create_tag_dependency_list(long tag_index);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_DEPENDENCY_DEFINITIONS_H__
