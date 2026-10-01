#pragma once
#ifndef __DATA_MINING_H__
#define __DATA_MINING_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

class c_datamine_game_info;

// layout ported from H3 (pointers shrunk to 32-bit); only sizeof verified (stack frame of datamine_event_handler)
class c_datamine
{
public:
    c_datamine(long priority, char const * event_name, long category_count, ...);
    ~c_datamine();

    void additional_category(char const * category);
    void add_long(char const * name, long value);
    void add_int64(char const * name, __int64 value);
    void add_string(char const * name, char const * value);
    void add_args(char const * format, char * arglist);

private:
    long m_priority;
    long m_category_count;
    long m_parameter_count;
    c_datamine_game_info * m_external_game_info;
    char * m_event_buffer;
    long m_event_buffer_count;
    c_static_string<512> m_event_name;
    c_static_string<512> m_parameter_signature;
    c_static_string<32> m_categories[16];
};
static_assert(sizeof(c_datamine) == 0x618, "c_datamine");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DATA_MINING_H__

