#pragma once
#ifndef __SHARED_REGION_H__
#define __SHARED_REGION_H__

/* ---------- headers */

#include "omaha\cache\restricted_memory_section.h"

/* ---------- constants */

long const k_shared_region_mirror_count = 2;

/* ---------- definitions */

/* ---------- prototypes */

void shared_region_initialize(void);
void shared_region_dispose(void);
void audio_region_initialize(void);
void audio_region_dispose(void);

/* ---------- globals */

extern void * g_restricted_global_shared_memory;
extern void * g_restricted_global_audio_memory;
extern c_restricted_section g_restricted_global_shared_memory_section;
extern c_restricted_section g_restricted_global_audio_memory_section;
extern c_restricted_section g_restricted_global_shared_memory_mirror_sections[k_shared_region_mirror_count];

/* ---------- public code */

#endif // __SHARED_REGION_H__

