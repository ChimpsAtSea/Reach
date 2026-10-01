#pragma once
#ifndef __LIGHTNING_DEFINITION_H__
#define __LIGHTNING_DEFINITION_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_bolt_definition
{
    static bool new_block_proc(void * element);
    static bool postprocess_block_proc(long element_index, void * element, bool for_editor);
};

struct s_lightning_system_definition
{
    static bool postprocess_proc(c_tag_index tag_index, bool for_editor);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHTNING_DEFINITION_H__

