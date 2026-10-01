#pragma once
#ifndef __ASYNC_SPASM_H__
#define __ASYNC_SPASM_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

class c_async_completion_flag;

void async_yield_until_done_internal(c_async_completion_flag * completion_flag, bool with_spinner, bool with_rendering);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_SPASM_H__

