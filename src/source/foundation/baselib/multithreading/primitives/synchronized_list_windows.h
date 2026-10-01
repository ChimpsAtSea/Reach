#pragma once
#ifndef __SYNCHRONIZED_LIST_WINDOWS_H__
#define __SYNCHRONIZED_LIST_WINDOWS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// Xbox 360 SLIST_ENTRY
struct s_synchronized_list_entry
{
    s_synchronized_list_entry * next;
};
static_assert(sizeof(s_synchronized_list_entry) == 0x4, "s_synchronized_list_entry");

// Xbox 360 SLIST_HEADER
struct s_synchronized_list_header
{
    unsigned __int64 alignment;
};
static_assert(sizeof(s_synchronized_list_header) == 0x8, "s_synchronized_list_header");

/* ---------- prototypes */

void synchronized_list_initialize(s_synchronized_list_header * header);
void synchronized_list_entry_clear(s_synchronized_list_entry * entry);
s_synchronized_list_entry * synchronized_list_entry_next(s_synchronized_list_entry * entry);
s_synchronized_list_entry * synchronized_list_entry_set(s_synchronized_list_entry * entry, s_synchronized_list_entry * next);
void synchronized_list_push(s_synchronized_list_header * header, s_synchronized_list_entry * entry);
void synchronized_list_push_multiple(s_synchronized_list_header * header, long entry_count, s_synchronized_list_entry ** entries);
s_synchronized_list_entry * synchronized_list_pop(s_synchronized_list_header * header);
s_synchronized_list_entry * synchronized_list_flush(s_synchronized_list_header * header);
long synchronized_list_get_count(s_synchronized_list_header * header);

/* ---------- globals */

/* ---------- public code */

#endif // __SYNCHRONIZED_LIST_WINDOWS_H__

