#pragma once
#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

long binary_search_4byte(long key_val, long const * base, long count, long (* const compare)(long, long, void const *), void const * compare_data);
long binary_search_elements(void const * key_val, void const * base, long count, unsigned int element_size, long (* const compare)(void const *, void const *, void const *), void const * compare_data);

/* ---------- globals */

/* ---------- public code */

#endif // __BINARY_SEARCH_H__

