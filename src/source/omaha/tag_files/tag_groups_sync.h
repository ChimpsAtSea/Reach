#pragma once
#ifndef __TAG_GROUPS_SYNC_H__
#define __TAG_GROUPS_SYNC_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_tag_file_difference_iterator;

class c_tag_file_sync_source
{
public:
    virtual void idle(void) = 0;
    virtual bool any_changes(void) = 0;
    virtual void begin(void) = 0;
    virtual c_tag_file_difference_iterator * get_difference_iterator(void) = 0;
    virtual void dispose_difference_iterator(c_tag_file_difference_iterator * iterator) = 0;
    virtual void end(void) = 0;
    virtual char const * get_name(void) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUPS_SYNC_H__

