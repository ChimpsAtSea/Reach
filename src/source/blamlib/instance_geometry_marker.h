#pragma once
#ifndef __INSTANCE_GEOMETRY_MARKER_H__
#define __INSTANCE_GEOMETRY_MARKER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\multithreading\datatypes\scratchpad.h"

/* ---------- constants */

/* ---------- definitions */

class c_structure_globals
{
public:
    // $TODO s_static_array<c_big_flags_typed_no_init<long, 8192>, 16>
    unsigned long m_geometry_marked_flags[16][8192 / 32];
    bool instanced_geometry_marker_initialized;
};
static_assert(sizeof(c_structure_globals) == 0x4004, "c_structure_globals");

/* ---------- prototypes */

extern c_structure_globals * get_structure_globals(void);

/* ---------- globals */

extern c_scratchpad<c_structure_globals, 6> structure_globals_pad;
extern __declspec(thread) c_structure_globals * structure_globals_tlsptr;

/* ---------- public code */

#endif // __INSTANCE_GEOMETRY_MARKER_H__

