#pragma once
#ifndef __DAMAGED_MEDIA_H__
#define __DAMAGED_MEDIA_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

bool damaged_media_get_global_memory(unsigned long * out_size, void const ** out_address);

extern void damaged_media_halt_and_display_error(char const * format, ...);

/* ---------- globals */

/* ---------- public code */

#endif // __DAMAGED_MEDIA_H__

