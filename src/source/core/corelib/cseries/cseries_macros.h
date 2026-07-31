#pragma once
#ifndef __CSERIES_MACROS_H__
#define __CSERIES_MACROS_H__

/* ---------- headers */

/* ---------- constants */

#define NUMBEROF(_array) (sizeof(_array) / sizeof(_array[0]))
#define IN_RANGE_INCLUSIVE(value, begin, end) ((value) >= (begin) && (value) <= (end))
#define VALID_INDEX(index, count) ((index) >= 0 && (index) < (count))
#define FLAG(bit) (1 << (bit))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_MACROS_H__
