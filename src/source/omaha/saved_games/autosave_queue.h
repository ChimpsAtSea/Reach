#pragma once
#ifndef __AUTOSAVE_QUEUE_H__
#define __AUTOSAVE_QUEUE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\saved_games\content\content_item_metadata.h"
#include "omaha\tag_files\files.h"

/* ---------- constants */

/* ---------- definitions */

// 4-byte packed via s_content_item_metadata (0x3CC stride in autosave_queue_sort_items_*)
struct s_autosave_queue_item
{
    s_file_reference file; // 0x0
    s_file_last_modification_date modification_date; // 0x110
    unsigned long size_in_bytes; // 0x118 name unverified (file_get_size in c_autosave_queue_enumerate_async::read_metadata)
    s_content_item_metadata metadata; // 0x11C
};
static_assert(sizeof(s_autosave_queue_item) == 0x3CC, "s_autosave_queue_item");

/* ---------- prototypes */

extern char const * autosave_queue_get_directory_path(void);

/* ---------- globals */

/* ---------- public code */

#endif // __AUTOSAVE_QUEUE_H__

