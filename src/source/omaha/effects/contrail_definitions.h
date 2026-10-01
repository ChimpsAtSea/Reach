#pragma once
#ifndef __CONTRAIL_DEFINITIONS_H__
#define __CONTRAIL_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO layout: only the methods referenced so far are declared
class c_contrail_definition
{
public:
    unsigned long get_used_states() const;
};

// $TODO layout: only the methods referenced so far are declared
class c_contrail_system_definition
{
public:
    long get_contrail_count() const;
    c_contrail_definition const * get_contrail_definition(long contrail_index) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CONTRAIL_DEFINITIONS_H__

