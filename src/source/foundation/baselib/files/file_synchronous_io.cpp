#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_synchronous_io.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_synchronous_io.h"
#include "baselib\file_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"

#include <stdarg.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned int file_get_position(struct s_file_accessor *);
// bool file_read_from_position(struct s_file_accessor *, unsigned int, unsigned int, enum e_file_error_mode, void *);
// bool file_write_to_position(struct s_file_accessor *, unsigned int, unsigned int, enum e_file_error_mode, void const *);
// void file_print(struct s_file_accessor *, char const *);
// void file_printf(struct s_file_accessor *, char const *, ...);
// void file_vprintf(struct s_file_accessor *, char const *, char *);

unsigned int file_get_position(s_file_accessor * file)
{
    mangled_ppc("?file_get_position@@YAIPAUs_file_accessor@@@Z");

    assert_tag_debug_untracked_jul_11_2011(19, file_valid(file));

    return file->position;
};

bool file_read_from_position(s_file_accessor * file, unsigned int position, unsigned int size, e_file_error_mode error_mode, void * buffer)
{
    mangled_ppc("?file_read_from_position@@YA_NPAUs_file_accessor@@IIW4e_file_error_mode@@PAX@Z");

    return file_set_position(file, position, error_mode) && file_read(file, size, error_mode, buffer);
};

bool file_write_to_position(s_file_accessor * file, unsigned int position, unsigned int size, e_file_error_mode error_mode, void const * buffer)
{
    mangled_ppc("?file_write_to_position@@YA_NPAUs_file_accessor@@IIW4e_file_error_mode@@PBX@Z");

    return file_set_position(file, position, error_mode) && file_write(file, size, error_mode, buffer);
};

void file_print(s_file_accessor * file, char const * string)
{
    mangled_ppc("?file_print@@YAXPAUs_file_accessor@@PBD@Z");

    unsigned int length = strlen_debug(string);
    if (length > 0)
    {
        file_write(file, length, _file_error_mode_report, string);
    }
};

void file_printf(s_file_accessor * file, char const * format, ...)
{
    mangled_ppc("?file_printf@@YAXPAUs_file_accessor@@PBDZZ");

    assert_tag_debug_untracked_jul_11_2011(65, format);

    va_list arglist;
    va_start(arglist, format);
    file_vprintf(file, format, arglist);
    va_end(arglist);
};

void file_vprintf(s_file_accessor * file, char const * format, va_list arglist)
{
    mangled_ppc("?file_vprintf@@YAXPAUs_file_accessor@@PBDPAD@Z");

    s_static_string<1024> string;
    string.print_va(format, arglist);
    file_print(file, string.get_string());
};
