#pragma once
#ifndef __BEAM_DEFINITIONS_H__
#define __BEAM_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO layout: only the methods referenced so far are declared
class c_beam_definition
{
public:
    unsigned long get_used_states() const;
};

// $TODO layout: only the methods referenced so far are declared
class c_beam_system_definition
{
public:
    long get_beam_count() const;
    c_beam_definition const * get_beam_definition(long beam_index) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __BEAM_DEFINITIONS_H__

