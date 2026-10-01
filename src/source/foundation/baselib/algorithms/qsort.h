#pragma once
#ifndef __QSORT_H__
#define __QSORT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

typedef bool (*qsort_compare_function)(void const * element_a, void const * element_b, void const * context);

/* ---------- prototypes */

void qsort_elements(void * elements, long element_count, unsigned int element_size, qsort_compare_function const compare, void const * context);

/* ---------- globals */

/* ---------- public code */

#endif // __QSORT_H__

