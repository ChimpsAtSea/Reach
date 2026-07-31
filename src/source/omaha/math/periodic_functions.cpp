#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\math\\periodic_functions.cpp"
/* ---------- headers */

#include "omaha\math\periodic_functions.h"

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <stdio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern real fabs(real x);
extern real fmod(real x, real y);
extern real real_sgn(real x);

/* ---------- globals */

/* ---------- public code */

void periodic_functions_initialize(void)
{
	mangled_ppc("?periodic_functions_initialize@@YAXXZ");
};

void periodic_functions_dispose(void)
{
	mangled_ppc("?periodic_functions_dispose@@YAXXZ");
};

real periodic_function_evaluate(short function_type, real time)
{
	mangled_ppc("?periodic_function_evaluate@@YAMFM@Z");

	real value;
	real next_value;
	real one_over_255;
	unsigned char const* table;
	real time_scale;
	real fractional_time;
	long integer_time;
	real result;

	if (function_type == _periodic_function_one)
	{
		result = 1.0f;
	}
	else
	{
		assert_tag_debug_untracked_jul_11_2011(216, function_type>=0 && function_type<k_periodic_functions_count);

		time_scale = 36.5714302f;
		time *= time_scale;

		fractional_time = time - (double)(__int64)time;
		assert_tag_debug_untracked_jul_11_2011(228, realcmp(fractional_time, fmod(time, 1.f)));

		integer_time = (long)((time - fractional_time) + real_sgn(time - fractional_time) * 0.5f) & (NUMBEROF(periodic_function_tables[function_type]) - 1);

		one_over_255 = 1.0f / 255.0f;
		table = periodic_function_tables[function_type];

		assert_tag_debug_untracked_jul_11_2011(237, VALID_INDEX(integer_time, NUMBEROF(periodic_function_tables[function_type])));

		value = table[integer_time] * one_over_255;
		next_value = table[(integer_time + 1) & (NUMBEROF(periodic_function_tables[function_type]) - 1)] * one_over_255;

		if (FLAG(function_type) & (FLAG(_periodic_function_slide) | FLAG(_periodic_function_slide_variable_period)))
		{
			if (value > 0.75f && next_value < 0.25f)
				next_value += 1.0f;

			result = value * (1.0f - fractional_time) + next_value * fractional_time;

			if (result > 1.0f)
				result -= 1.0f;
		}
		else
		{
			result = value * (1.0f - fractional_time) + next_value * fractional_time;
		}
	}

	return result;
};

real transition_function_evaluate(short function_type, real time)
{
	mangled_ppc("?transition_function_evaluate@@YAMFM@Z");

	real value;
	real next_value;
	real one_over_255;
	unsigned char const* table;
	real scaled_time;
	short integer_time;
	real fractional_time;
	real result;

	if (time < 0.0f)
		time = 0.0f;
	else if (time > 1.0f)
		time = 1.0f;

	if (function_type == _transition_function_linear)
	{
		result = time;
	}
	else
	{
		assert_tag_debug_untracked_jul_11_2011(275, function_type>=0 && function_type<k_transition_functions_count);

		one_over_255 = 1.0f / 255.0f;
		table = transition_function_tables[function_type];

		scaled_time = 1023.0f * time;
		fractional_time = scaled_time - (double)(__int64)scaled_time;
		integer_time = (short)(long)((scaled_time - 0.1f) + real_sgn(scaled_time - 0.1f) * 0.5f);

		if (integer_time == NUMBEROF(transition_function_tables[function_type]) - 1)
		{
			result = table[integer_time] * one_over_255;
		}
		else
		{
			value = table[integer_time] * one_over_255;
			next_value = table[integer_time + 1] * one_over_255;

			result = value * (1.0f - fractional_time) + next_value * fractional_time;
		}

		result = MIN(MAX(result, 0.0f), 1.0f);
	}

	return result;
};

/* ---------- private code */

void byte_table_writer(FILE* file, void const* data, long count, long stride)
{
	mangled_ppc("?byte_table_writer@@YAXPAU_iobuf@@PBXJJ@Z");

	long values_per_line;
	unsigned char const* values;
	long index;
	long value_index;

	values = (unsigned char const*)data;
	values_per_line = 4;

	fprintf(file, "{\n");

	for (index = 0; index < count; index++)
	{
		fprintf(file, "\t{\n\t\t");

		for (value_index = 0; value_index < stride; value_index++)
		{
			fprintf(file, "%d", *values);
			values++;

			if (value_index + 1 < stride)
				fprintf(file, ",");

			if (values_per_line - 1 == value_index % values_per_line)
				fprintf(file, "\n\t\t");
		}

		fprintf(file, "\n\t}");

		if (index + 1 < count)
			fprintf(file, ",");

		fprintf(file, "\n");
	}

	fprintf(file, "};\n");
};

/* ---------- reverse engineering */

// char const **global_periodic_functions_enum_strings; // "?global_periodic_functions_enum_strings@@3PAPBDA"
// struct s_string_list_definition global_periodic_functions_enum; // "?global_periodic_functions_enum@@3Us_string_list_definition@@A"
// char const **global_transition_functions_enum_strings; // "?global_transition_functions_enum_strings@@3PAPBDA"
// struct s_string_list_definition global_transition_functions_enum; // "?global_transition_functions_enum@@3Us_string_list_definition@@A"
// char const **global_reverse_transition_functions_enum_strings; // "?global_reverse_transition_functions_enum_strings@@3PAPBDA"
// struct s_string_list_definition global_reverse_transition_functions_enum; // "?global_reverse_transition_functions_enum@@3Us_string_list_definition@@A"
// unsigned char (*periodic_function_tables)[1024]; // "?periodic_function_tables@@3PAY0EAA@EA"
// unsigned char (*transition_function_tables)[1024]; // "?transition_function_tables@@3PAY0EAA@EA"

// void byte_table_writer(struct _iobuf *, void const *, long, long);
// void periodic_functions_initialize(void);
// void periodic_functions_dispose(void);
// float periodic_function_evaluate(short, float);
// float transition_function_evaluate(short, float);
