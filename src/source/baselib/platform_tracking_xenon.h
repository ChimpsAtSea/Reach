#pragma once
#ifndef __PLATFORM_TRACKING_XENON_H__
#define __PLATFORM_TRACKING_XENON_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void debug_platform_memory_consumer(char const * consumer, char const * file, long line);
extern void debug_platform_memory_tracking_thread_enable(bool enable);
extern void * XMemAlloc_tracked(unsigned long size, unsigned long attributes);
extern void XMemFree_tracked(void * address, unsigned long attributes);
extern unsigned long XMemSize_tracked(void * address, unsigned long attributes);
extern bool xenon_allocator_tracking_enabled(void);
extern char const * xenon_allocator_type(unsigned long allocator_id, unsigned long object_type);

/* ---------- globals */

/* ---------- public code */

#endif // __PLATFORM_TRACKING_XENON_H__

