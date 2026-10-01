#ifndef __TAG_RESOURCE_INTERNALS_H__
#define __TAG_RESOURCE_INTERNALS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries_wrapped.h"

/* ---------- constants */

enum e_tag_resource_fixup_type
{
    _tag_resource_fixup_value = 0,
    _tag_resource_fixup_control_offset,
    _tag_resource_fixup_cache_offset,
    _tag_resource_fixup_optional_offset,

    k_number_of_tag_resource_fixup_types
};

/* ---------- definitions */

template<typename t_type> class c_basic_buffer;

// $TODO bodies not yet recovered (all "f i" in the target, owned by tag_resource_internals.obj)
class c_tag_resource_fixup :
    private c_long_designator<3, 0>
{
public:
    unsigned long get_fixup_value(void) const;
    void set_fixup_value(unsigned long new_fixup_value);
    e_tag_resource_fixup_type get_type(void) const;
    void set_type(e_tag_resource_fixup_type new_type);
    void clear(void);
};
static_assert(sizeof(c_tag_resource_fixup) == 0x4, "c_tag_resource_fixup");

struct s_tag_resource_fixup_location
{
    unsigned long address_offset;
    c_tag_resource_fixup fixup;
};
static_assert(sizeof(s_tag_resource_fixup_location) == 0x8, "s_tag_resource_fixup_location");

struct s_tag_resource_interop_location
{
    c_tag_resource_fixup interop_fixup;
    long interop_type_index;
};
static_assert(sizeof(s_tag_resource_interop_location) == 0x8, "s_tag_resource_interop_location");

/* ---------- prototypes */

extern void * get_address_from_fixup(c_tag_resource_fixup fixup, c_basic_buffer<void> control_data, c_basic_buffer<void> * pageable_data, c_basic_buffer<void> * optional_data);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_RESOURCE_INTERNALS_H__

