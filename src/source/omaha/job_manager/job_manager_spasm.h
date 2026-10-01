#pragma once
#ifndef __JOB_MANAGER_SPASM_H__
#define __JOB_MANAGER_SPASM_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern unsigned long job_main_thread(void * thread_parameter);
extern void job_manager_omaha_initialize(void);
extern void job_manager_omaha_dispose(void);
extern void job_manager_block_callback(void);
extern bool job_manager_has_any_job_thread_crashed(void);

/* ---------- globals */

extern bool volatile g_signal_active_job_threads;

/* ---------- public code */

#endif // __JOB_MANAGER_SPASM_H__

