#pragma once
#ifndef __STRUCTURE_MANIFEST_DEFINITIONS_H__
#define __STRUCTURE_MANIFEST_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\system\system_identity_xenon.h"
#include "omaha\scenario\scenario_content_status.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_maximum_structure_manifest_items_count = 64,
};

/* ---------- definitions */

struct s_structure_manifest_build_identifier_definition
{
    s_system_global_unique_identifier manifest_id; // 0x0
    long build_index; // 0x10
    long structure_importer_version; // 0x14
};
static_assert(sizeof(s_structure_manifest_build_identifier_definition) == 0x18, "s_structure_manifest_build_identifier_definition");

struct s_structure_manifest_bsp_definition
{
    s_structure_manifest_build_identifier_definition build_identifier; // 0x0
    s_structure_manifest_build_identifier_definition parent_build_identifier; // 0x18
    char bsp_name[256]; // 0x30
};
static_assert(sizeof(s_structure_manifest_bsp_definition) == 0x130, "s_structure_manifest_bsp_definition");

struct s_structure_manifest_definition
{
    s_structure_manifest_build_identifier_definition build_identifier; // 0x0
    s_structure_manifest_build_identifier_definition parent_build_identifier; // 0x18
    s_tag_block bsp_manifest; // 0x30 s_structure_manifest_bsp_definition
};
static_assert(sizeof(s_structure_manifest_definition) == 0x3C, "s_structure_manifest_definition");

/* ---------- prototypes */

s_structure_manifest_bsp_definition const * structure_manifest_find_bsp_manifest(s_structure_manifest_definition const * manifest, char const * bsp_name);
void structure_manifest_build_identifier_initialize(s_structure_manifest_build_identifier_definition * build_identifier);
bool structure_manifest_build_identifiers_match(s_structure_manifest_build_identifier_definition const * build_identifier0, s_structure_manifest_build_identifier_definition const * build_identifier1);
char const * structure_manifest_build_content_source_structure_seam_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size);
char const * structure_manifest_build_content_source_bsp_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size);
char const * structure_manifest_build_content_source_structure_design_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size);
char const * structure_manifest_build_content_source_lighting_info_tag_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __STRUCTURE_MANIFEST_DEFINITIONS_H__

