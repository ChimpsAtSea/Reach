#ifndef __TAG_API_INTEROP_H__
#define __TAG_API_INTEROP_H__
#pragma once

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

struct s_tag_struct_definition;

// $TODO layout (only struct_definition verified, via get_descriptor_definition)
struct s_tag_interop_definition
{
    char const * get_interop_name(void) const;
    s_tag_struct_definition const * get_descriptor_definition(void) const;
    s_tag_struct_definition * get_descriptor_definition(void);

    unsigned char unknown0[0x10]; // 0x0
    s_tag_struct_definition const * struct_definition; // 0x10
};

/* ---------- prototypes */

bool tag_interop_descriptor_exists(s_tag_interop const * interop);
void tag_interop_initialize(s_tag_interop * interop, s_tag_interop_definition const * definition);
void tag_interop_destroy(s_tag_interop * interop);
void * tag_interop_descriptor_get_with_definition(s_tag_interop const * interop, s_tag_struct_definition const * struct_definition);
void * tag_interop_descriptor_get(s_tag_interop const * interop);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_API_INTEROP_H__

