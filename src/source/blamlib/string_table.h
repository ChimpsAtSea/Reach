#pragma once
#ifndef __STRING_TABLE_H__
#define __STRING_TABLE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_string_table_scratch_buffer
{
public:
    c_string_table_scratch_buffer();
    ~c_string_table_scratch_buffer();

    void * get_buffer();
    unsigned long get_buffer_size();
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STRING_TABLE_H__

