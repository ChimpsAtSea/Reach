#pragma once
#ifndef __TRIANGLE_STRIP_UTILITIES_H__
#define __TRIANGLE_STRIP_UTILITIES_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void count_strip_triangles(unsigned short const * strip_indices, long strip_index_count, long * valid_triangles, long * degenerate_triangles);
long find_next_valid_strip_triangle(unsigned short const * strip_indices, long strip_index_count, long previous_triangle_start_index);
long find_triangle(unsigned short vertex_A, unsigned short vertex_B, unsigned short vertex_C, unsigned short const * indices, long index_count, bool strips, long * rotation);
long find_triangle_long(long vertex_A, long vertex_B, long vertex_C, long const * indices, long index_count, bool strips, long * rotation);

/* ---------- globals */

/* ---------- public code */

#endif // __TRIANGLE_STRIP_UTILITIES_H__

