/* ---------- headers */

#include "blamlib\async_io_file_overlapped_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void initialize_simple_overlapped(unsigned long, unsigned long, struct _OVERLAPPED *, struct s_simple_read_file_ex_overlapped_result *);
// public: void s_simple_read_file_ex_overlapped_result::reset(void);
// void simple_read_file_ex_completion_routine(unsigned long, unsigned long, struct _OVERLAPPED *);

void initialize_simple_overlapped(unsigned long offset, unsigned long size, _OVERLAPPED * out_overlapped, s_simple_read_file_ex_overlapped_result * out_overlapped_result)
{
    mangled_ppc("?initialize_simple_overlapped@@YAXKKPAU_OVERLAPPED@@PAUs_simple_read_file_ex_overlapped_result@@@Z");

    out_overlapped->Offset = offset;
    out_overlapped->OffsetHigh = 0;
    out_overlapped->hEvent = out_overlapped_result;
    out_overlapped_result->bytes_requested = size;
    out_overlapped_result->reset();
};

void simple_read_file_ex_completion_routine(unsigned long error_code, unsigned long bytes_transferred, _OVERLAPPED * overlapped)
{
    mangled_ppc("?simple_read_file_ex_completion_routine@@YAXKKPAU_OVERLAPPED@@@Z");

    s_simple_read_file_ex_overlapped_result * result = static_cast<s_simple_read_file_ex_overlapped_result *>(overlapped->hEvent);
    if (result)
    {
        result->error_code = error_code;
        result->bytes_transferred = bytes_transferred;
        result->done.set(1);
    }
};

