#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\async_io_profile.cpp"
/* ---------- headers */

#include "omaha\cseries\async_io_profile.h"
#include "baselib\synchronized_value_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

struct s_async_io_internal_statistics
{
    c_interlocked_int32 seek_count; // 0x0
    c_interlocked_int32 read_count; // 0x4
    c_interlocked_int32 read_bytes; // 0x8
    c_interlocked_int32 write_count; // 0xC
    c_interlocked_int32 write_bytes; // 0x10
};

/* ---------- prototypes */

/* ---------- globals */

static s_async_io_internal_statistics g_async_io_statistics;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void async_io_record_seek(void);
// void async_io_record_read(long);
// void async_io_record_write(long);
// void async_io_get_statistics(struct s_async_io_statistics *);
// void async_io_profile_initialize(void);
// void async_io_profile_dispose(void);
// void async_io_record_read_history(void const *, long, void const *, long);
// public: s_async_io_internal_statistics::s_async_io_internal_statistics(void);
// public: s_async_io_internal_statistics::~s_async_io_internal_statistics(void);
// void g_async_io_statistics::`dynamic atexit destructor'(void);

void async_io_record_seek(void)
{
    mangled_ppc("?async_io_record_seek@@YAXXZ");

    g_async_io_statistics.seek_count.increment();
};

void async_io_record_read(long size)
{
    mangled_ppc("?async_io_record_read@@YAXJ@Z");

    g_async_io_statistics.read_count.increment();
    g_async_io_statistics.read_bytes.add(size);
};

void async_io_record_write(long size)
{
    mangled_ppc("?async_io_record_write@@YAXJ@Z");

    g_async_io_statistics.write_count.increment();
    g_async_io_statistics.write_bytes.add(size);
};

void async_io_get_statistics(s_async_io_statistics * async_io_statistics)
{
    mangled_ppc("?async_io_get_statistics@@YAXPAUs_async_io_statistics@@@Z");

    assert_tag_debug_untracked_jul_11_2011(87, async_io_statistics);

    async_io_statistics->seek_count = g_async_io_statistics.seek_count.peek();
    async_io_statistics->read_count = g_async_io_statistics.read_count.peek();
    async_io_statistics->read_bytes = g_async_io_statistics.read_bytes.peek();
    async_io_statistics->write_count = g_async_io_statistics.write_count.peek();
    async_io_statistics->write_bytes = g_async_io_statistics.write_bytes.peek();
};

void async_io_profile_initialize(void)
{
    mangled_ppc("?async_io_profile_initialize@@YAXXZ");
};

void async_io_profile_dispose(void)
{
    mangled_ppc("?async_io_profile_dispose@@YAXXZ");
};

void async_io_record_read_history(void const * a1, long a2, void const * a3, long a4)
{
    mangled_ppc("?async_io_record_read_history@@YAXPBXJ0J@Z");
};

// compiler-generated: s_async_io_internal_statistics::s_async_io_internal_statistics(void) ("??0s_async_io_internal_statistics@@QAA@XZ")
// compiler-generated: s_async_io_internal_statistics::~s_async_io_internal_statistics(void) ("??1s_async_io_internal_statistics@@QAA@XZ")
// compiler-generated: g_async_io_statistics::`dynamic atexit destructor'(void) ("??__Fg_async_io_statistics@@YAXXZ")
