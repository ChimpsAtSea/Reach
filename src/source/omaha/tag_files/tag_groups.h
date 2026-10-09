#pragma once
#ifndef __TAG_GROUPS_H__
#define __TAG_GROUPS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block_definition;

struct s_tag_block
{
    long count;
    void * address;
    s_tag_block_definition * definition;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUPS_H__

