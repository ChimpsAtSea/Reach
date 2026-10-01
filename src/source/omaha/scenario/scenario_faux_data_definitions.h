#pragma once
#ifndef __SCENARIO_FAUX_DATA_DEFINITIONS_H__
#define __SCENARIO_FAUX_DATA_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    SCENARIO_FAUX_DATA_TAG = 'sFdT',
};

/* ---------- definitions */

struct s_faux_data_lightmap_group_data
{
    char name[32]; // 0x0
    unsigned char pad[2]; // 0x20
    short bsp_reference_index; // 0x22
    s_tag_block clusters; // 0x24
    s_tag_block instances; // 0x30
    s_tag_block objects; // 0x3C
    s_tag_block airprobes; // 0x48
    s_tag_block scenery_probes; // 0x54
    s_tag_block device_probes; // 0x60
    long instance_probe_manifest_index; // 0x6C
    long instance_single_probe_count; // 0x70
};
static_assert(sizeof(s_faux_data_lightmap_group_data) == 0x74, "s_faux_data_lightmap_group_data");

struct s_scenario_faux_data
{
    long version_number; // 0x0
    long farm_job_id; // 0x4
    s_tag_block lightmap_groups; // 0x8
    s_tag_block global_bsp_data; // 0x14
    s_tag_block airprobes; // 0x20
    s_tag_block scenery_probes; // 0x2C
    s_tag_block device_machine_probes; // 0x38
};
static_assert(sizeof(s_scenario_faux_data) == 0x44, "s_scenario_faux_data");

/* ---------- prototypes */

s_faux_data_lightmap_group_data * faux_data_find_lightgroup_for_bsp(long faux_data_index, long bsp_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_FAUX_DATA_DEFINITIONS_H__

