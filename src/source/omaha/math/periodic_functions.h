#pragma once
#ifndef __PERIODIC_FUNCTIONS_H__
#define __PERIODIC_FUNCTIONS_H__

/* ---------- headers */

#include "omaha\math\real_math.h"

/* ---------- constants */

enum e_periodic_function
{
	_periodic_function_one = 0,
	_periodic_function_zero,
	_periodic_function_cosine,
	_periodic_function_cosine_variable_period,
	_periodic_function_diagonal_wave,
	_periodic_function_diagonal_wave_variable_period,
	_periodic_function_slide,
	_periodic_function_slide_variable_period,
	_periodic_function_noise,
	_periodic_function_jitter,
	_periodic_function_wander,
	_periodic_function_spark,

	k_periodic_functions_count
};

enum e_transition_function
{
	_transition_function_linear = 0,
	_transition_function_early,
	_transition_function_very_early,
	_transition_function_late,
	_transition_function_very_late,
	_transition_function_cosine,
	_transition_function_one,
	_transition_function_zero,

	k_transition_functions_count
};

/* ---------- definitions */

/* ---------- prototypes */

extern void periodic_functions_initialize(void);
extern void periodic_functions_dispose(void);
extern real periodic_function_evaluate(short function_type, real time);
extern real transition_function_evaluate(short function_type, real time);

/* ---------- globals */

extern unsigned char periodic_function_tables[k_periodic_functions_count][1024];
extern unsigned char transition_function_tables[k_transition_functions_count][1024];

/* ---------- public code */

#endif // __PERIODIC_FUNCTIONS_H__
