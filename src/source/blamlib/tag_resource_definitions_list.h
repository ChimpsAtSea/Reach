#pragma once
#ifndef __TAG_RESOURCE_DEFINITIONS_LIST_H__
#define __TAG_RESOURCE_DEFINITIONS_LIST_H__

/* ---------- headers */

#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

enum
{
    k_tag_resource_definition_count = 9,
};

/* ---------- definitions */

struct s_tag_resource_definition;

/* ---------- prototypes */

c_wrapped_array<s_tag_resource_definition const *> tag_resources_get_definitions_global_list(void);

/* ---------- globals */

extern s_tag_resource_definition const * g_resource_definition_list[k_tag_resource_definition_count];

/* ---------- public code */

#endif // __TAG_RESOURCE_DEFINITIONS_LIST_H__

