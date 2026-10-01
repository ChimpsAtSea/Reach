#ifndef __ARRAY_H__
#define __ARRAY_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout not reversed yet (wraps dynamic_array: element size @0x0, count @0x4); methods are inline (f i) in the target
template<typename t_type>
struct array_template
{
    void append(t_type const * source, long count);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ARRAY_H__

