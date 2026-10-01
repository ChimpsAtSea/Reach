#ifndef __RANDOM_MATH_H__
#define __RANDOM_MATH_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

unsigned short _random(unsigned long * seed, char const * purpose, char const * source_file, unsigned long source_line); // $TODO inline in the target ("f i")
unsigned long * get_local_random_seed_address(void);
unsigned long * get_random_seed_address(void);
short _random_range(unsigned long * seed, char const * purpose, char const * source_file, unsigned long source_line, short lower_bound, short upper_bound);
bool _random_boolean(unsigned long * seed, char const * purpose, char const * source_file, unsigned long source_line);
float _real_random(unsigned long * seed, char const * purpose, char const * source_file, unsigned long source_line); // $TODO inline in the target ("f i")
float _real_random_range(unsigned long * seed, char const * purpose, char const * source_file, unsigned long source_line, float lower_bound, float upper_bound);

/* ---------- globals */

/* ---------- public code */

#endif // __RANDOM_MATH_H__

