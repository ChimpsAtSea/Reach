#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\xbox_minidump.cpp"
/* ---------- headers */

#include "omaha\cseries\xbox_minidump.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\tag_files\files.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const k_crash_minidump_file_path = "minidump.sdmp";
char const * const k_debug_memory_minidump_memory_stream = "minidump_memory_stream.stream";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const k_crash_minidump_file_path; // "?k_crash_minidump_file_path@@3PBDB"
// char const *const k_debug_memory_minidump_memory_stream; // "?k_debug_memory_minidump_memory_stream@@3PBDB"

// long upload_minidump_start(long, struct s_file_reference *);

long upload_minidump_start(long maximum_file_count, s_file_reference * out_file_list)
{
    mangled_ppc("?upload_minidump_start@@YAJJPAUs_file_reference@@@Z");

    c_crash_report_output_path crash_output_path;
    long file_count = 2;

    assert_tag_debug_untracked_jul_11_2011(35, maximum_file_count>=1);

    file_reference_create_from_path(&out_file_list[0], crash_output_path.get_path(k_crash_minidump_file_path), false);
    file_reference_create_from_path(&out_file_list[1], crash_output_path.get_path(k_debug_memory_minidump_memory_stream), false);

    return file_count;
};

