#pragma once
#ifndef __FILE_INTERFACE_H__
#define __FILE_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_file_accessor;

/* ---------- prototypes */

void file_invalidate(s_file_accessor * file);
bool file_valid(s_file_accessor const * file);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_INTERFACE_H__

