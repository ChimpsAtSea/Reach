#pragma once
#ifndef __HS_SCENARIO_DEFINITIONS_H__
#define __HS_SCENARIO_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum
{
    HS_SOURCE_FILE_TAG = 'hsc*',
};

enum
{
    k_maximum_hs_unit_seat_mappings = 65536,
};

/* ---------- definitions */

// hs_scripts_block (haloreach_tagtest_x360.json)
struct hs_script
{
    long name; // 0x0 string_id
    short script_type; // 0x4
    short return_type; // 0x6
    long root_expression_index; // 0x8
    s_tag_block parameters; // 0xC
};
static_assert(sizeof(hs_script) == 0x18, "hs_script");

// size 0x44 per haloreach_tagtest_x360.json (hs_source_files_block); field order from H3
struct hs_source_file
{
    char name[32]; // 0x0
    s_tag_data source; // 0x20
    s_tag_block external_references; // 0x34
    unsigned long flags; // 0x40
};
static_assert(sizeof(hs_source_file) == 0x44, "hs_source_file");

// size 0xC (element size in hs_match_unit_seat_internal)
struct s_hs_unit_seat_mapping
{
    long unit_definition_index; // 0x0
    c_big_flags_typed_no_init<long, 64> unit_seats; // 0x4
};
static_assert(sizeof(s_hs_unit_seat_mapping) == 0xC, "s_hs_unit_seat_mapping");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HS_SCENARIO_DEFINITIONS_H__

