#pragma once
#ifndef __CSERIES_XENON_H__
#define __CSERIES_XENON_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void * allocate_contiguous_memory_untracked(unsigned long size, void const * address, long alignment_bits, unsigned long protect);
void free_contiguous_memory_untracked(void * address);
void * allocate_contiguous_memory_tracked_verbose(unsigned long size, void const * address, long alignment_bits, unsigned long protect, unsigned long flags, char const * file, long line, char const * type, char const * subtype, char const * name);
void free_contiguous_memory_tracked_verbose(void * address, char const * file, long line);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_XENON_H__

