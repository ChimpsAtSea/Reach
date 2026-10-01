#pragma once
#ifndef __PROGRESS_H__
#define __PROGRESS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

typedef void (*progress_new_proc)(char const * description, void * user_data);
typedef void (*progress_update_proc)(char const * description, char const * optional_description, long progress, void * user_data);
typedef void (*progress_done_proc)(char const * description, void * user_data);

struct progress_callbacks
{
    progress_new_proc new_proc; // 0x0
    progress_update_proc update_proc; // 0x4
    progress_done_proc done_proc; // 0x8
    void * user_data; // 0xC
};
static_assert(sizeof(progress_callbacks) == 0x10, "progress_callbacks");

/* ---------- prototypes */

void progress_set_default_callbacks(progress_callbacks const * callbacks);
void progress_set_custom_callbacks(progress_callbacks const * callbacks);
void progress_disable_callbacks(bool disabled);
void progress_new(char const * description);
long progress_update(long current_amount, long total_amount);
long progress_update_with_description(long current_amount, long total_amount, char const * optional_description);
void progress_done(void);

/* ---------- globals */

/* ---------- public code */

#endif // __PROGRESS_H__

