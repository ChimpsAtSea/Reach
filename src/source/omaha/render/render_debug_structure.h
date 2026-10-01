#pragma once
#ifndef __RENDER_DEBUG_STRUCTURE_H__
#define __RENDER_DEBUG_STRUCTURE_H__

/* ---------- headers */

#include <math.h>

/* ---------- constants */

// H3 old_render_debug.cpp; in Reach these are dynamically initialized (log10(float)) in ~200 TUs
// (??__Ek_log_complex_geometry_edge_length_cutoff@@YAXXZ etc.), so they live in some widely included header.
// $TODO: the real owning header is unknown (every Reach TU that includes structure_bsp_definitions.h has them,
// except tag_resource_definitions_list.obj); kept here so only TUs that include this header pick them up
static float const k_log_complex_geometry_edge_length_cutoff = log10(0.2f);
static float const k_log_complex_geometry_edge_length_max = log10(0.2f);
static float const k_log_complex_geometry_edge_length_min = log10(0.05f);

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RENDER_DEBUG_STRUCTURE_H__

