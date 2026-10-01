/* ---------- headers */

#include "baselib\file_interface.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\files\file_synchronous_io.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void file_invalidate(struct s_file_accessor *);
// bool file_valid(struct s_file_accessor const *);

void file_invalidate(s_file_accessor * file)
{
    mangled_ppc("?file_invalidate@@YAXPAUs_file_accessor@@@Z");

    csmemset(file, 0, sizeof(s_file_accessor));
    file->location = k_file_location_invalid;
    file->handle = INVALID_HANDLE_VALUE;
};

bool file_valid(s_file_accessor const * file)
{
    mangled_ppc("?file_valid@@YA_NPBUs_file_accessor@@@Z");

    bool valid = file != NULL;
    valid = valid && file->handle != NULL && file->handle != INVALID_HANDLE_VALUE;
    return valid;
};

