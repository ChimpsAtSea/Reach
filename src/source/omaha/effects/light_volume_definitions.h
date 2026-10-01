#pragma once
#ifndef __LIGHT_VOLUME_DEFINITIONS_H__
#define __LIGHT_VOLUME_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO layout: only the methods referenced so far are declared
class c_light_volume_definition
{
public:
    unsigned long get_used_states() const;
};

// $TODO layout: only the methods referenced so far are declared
class c_light_volume_system_definition
{
public:
    long get_light_volume_count() const;
    c_light_volume_definition const * get_light_volume_definition(long light_volume_index) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LIGHT_VOLUME_DEFINITIONS_H__

