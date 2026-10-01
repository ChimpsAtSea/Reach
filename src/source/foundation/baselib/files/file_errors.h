#pragma once
#ifndef __FILE_ERRORS_H__
#define __FILE_ERRORS_H__

/* ---------- headers */

/* ---------- constants */

enum e_file_error_mode
{
    _file_error_mode_report = 0,
    _file_error_mode_silent,

    k_file_error_mode_count
};

/* ---------- definitions */

class c_file_path;
struct s_file_accessor;

/* ---------- prototypes */

void file_error(char const * location, e_file_error_mode error_mode, s_file_accessor const * file);
void file_utility_error(char const * location, e_file_error_mode error_mode, c_file_path const * path, c_file_path const * other_path);
extern void file_errors_suppress_push(void);
extern void file_errors_suppress_pop(void);

/* ---------- globals */

/* ---------- public code */

#endif // __FILE_ERRORS_H__

