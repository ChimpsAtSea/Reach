#pragma once
#ifndef __TAG_GROUPS_H__
#define __TAG_GROUPS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_tag_allocator
{
public:
    virtual long string_id_new(char const *) = 0;
    virtual char const * string_id_get_string_const(long) = 0;
    virtual void string_id_release(long) = 0;
    virtual char const * add_tracked_string(char const *) = 0;
    virtual void remove_tracked_string(char const *) = 0;
    virtual void * allocate(long, long, char const *, unsigned long) = 0;
    virtual void deallocate(void *, long, unsigned long) = 0;
    virtual void * allocate_temporary(long, long, char const *) = 0;
    virtual void deallocate_temporary(void *, long) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUPS_H__

