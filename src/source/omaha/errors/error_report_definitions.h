#pragma once
#ifndef __ERROR_REPORT_DEFINITIONS_H__
#define __ERROR_REPORT_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct error_report_category
{
    char name[256]; // 0x0
    short report_type; // 0x100
    unsigned short flags; // 0x102
    short runtime_generation_flags; // 0x104
    unsigned char pad[2]; // 0x106
    long runtime_something; // 0x108
    s_tag_block reports; // 0x10C
};
static_assert(sizeof(error_report_category) == 0x118, "error_report_category");

/* ---------- prototypes */

bool postprocess_error_report(long element_index, void * element, bool for_editor);

/* ---------- globals */

extern bool prune_error_geometry;

/* ---------- public code */

#endif // __ERROR_REPORT_DEFINITIONS_H__

