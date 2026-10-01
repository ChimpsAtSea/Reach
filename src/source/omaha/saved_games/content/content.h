#pragma once
#ifndef __CONTENT_H__
#define __CONTENT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

struct _XCONTENT_DATA;

// wraps an XCONTENT_DATA (sizeof 0x134); get/get_const are f i (online_file_transfer*.obj)
struct s_content_item_platform_handle
{
    c_opaque_data<_XCONTENT_DATA, 0x134, 4> content_data; // 0x0
};
static_assert(sizeof(s_content_item_platform_handle) == 0x134, "s_content_item_platform_handle");

/* ---------- prototypes */

void content_build_filename(s_content_item_platform_handle const * platform_handle, s_static_string<256> const * const extension, s_static_string<256> * out_filename);

/* ---------- globals */

/* ---------- public code */

#endif // __CONTENT_H__

