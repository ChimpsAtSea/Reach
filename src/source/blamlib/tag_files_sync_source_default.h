#pragma once
#ifndef __TAG_FILES_SYNC_SOURCE_DEFAULT_H__
#define __TAG_FILES_SYNC_SOURCE_DEFAULT_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups_sync.h"

/* ---------- constants */

/* ---------- definitions */

class c_default_tag_file_sync_source :
    public c_tag_file_sync_source
{
public:
    virtual void idle(void);
    virtual bool any_changes(void);
    virtual void begin(void);
    virtual c_tag_file_difference_iterator * get_difference_iterator(void);
    virtual void dispose_difference_iterator(c_tag_file_difference_iterator * iterator);
    virtual void end(void);
    virtual char const * get_name(void);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FILES_SYNC_SOURCE_DEFAULT_H__

