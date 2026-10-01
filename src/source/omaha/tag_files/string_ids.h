#pragma once
#ifndef __STRING_IDS_H__
#define __STRING_IDS_H__

/* ---------- headers */

/* ---------- constants */

const long _string_id_invalid = -1;
const long _string_id_empty_string = 0;

/* ---------- definitions */

class c_old_string_id
{
public:
    char const * get_string() const;
    void set_string(char const * string);
    bool is_string(char const * string) const;

    long m_value; // 0x0
};

/* ---------- prototypes */

long string_id_new(char const * string);
long string_id_retrieve(char const * string);
char const * string_id_get_string_const(long string_id);
char const * string_id_get(long string_id);

/* ---------- globals */

/* ---------- public code */

#endif // __STRING_IDS_H__

