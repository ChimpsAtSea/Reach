#pragma once
#ifndef __ASYNC_IO_PROFILE_H__
#define __ASYNC_IO_PROFILE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_async_io_statistics
{
    long seek_count; // 0x0
    long read_count; // 0x4
    long read_bytes; // 0x8
    long write_count; // 0xC
    long write_bytes; // 0x10
};

/* ---------- prototypes */

void async_io_record_seek(void);
void async_io_record_read(long size);
void async_io_record_write(long size);
void async_io_get_statistics(s_async_io_statistics * async_io_statistics);
void async_io_profile_initialize(void);
void async_io_profile_dispose(void);
void async_io_record_read_history(void const * a1, long a2, void const * a3, long a4);

/* ---------- globals */

/* ---------- public code */

#endif // __ASYNC_IO_PROFILE_H__

