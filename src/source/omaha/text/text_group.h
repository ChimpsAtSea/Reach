#pragma once
#ifndef __TEXT_GROUP_H__
#define __TEXT_GROUP_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool string_list_get_normal_string(long tag_index, long string_index, c_static_wchar_string<256> * string, bool * string_is_localized);

/* ---------- globals */

/* ---------- public code */

#endif // __TEXT_GROUP_H__

