#ifndef __CACHE_FILE_BUILDER_H__
#define __CACHE_FILE_BUILDER_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_cache_file_global_tag_registry
{
public:
    // $TODO names of the interface methods are unknown; slot 0 returns the global tag index for a group tag
    virtual long get_global_tag_index(unsigned long group_tag) = 0;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CACHE_FILE_BUILDER_H__

