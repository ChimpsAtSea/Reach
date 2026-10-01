#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\geometry\\triangle_strip_utilities.cpp"
/* ---------- headers */

#include "omaha\geometry\triangle_strip_utilities.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void count_strip_triangles(unsigned short const *, long, long *, long *);
// long find_next_valid_strip_triangle(unsigned short const *, long, long);
// long find_triangle(unsigned short, unsigned short, unsigned short, unsigned short const *, long, bool, long *);
// long find_triangle_long(long, long, long, long const *, long, bool, long *);

void count_strip_triangles(unsigned short const * strip_indices, long strip_index_count, long * valid_triangles, long * degenerate_triangles)
{
    mangled_ppc("?count_strip_triangles@@YAXPBGJPAJ1@Z");

    assert_tag_debug_untracked_jul_11_2011(18, valid_triangles && degenerate_triangles);

    *valid_triangles = 0;
    *degenerate_triangles = 0;

    if (strip_index_count < 3)
    {
        return;
    }
    else
    {
        long vertex_A = strip_indices[0];
        long vertex_B = strip_indices[1];
        long index = 2;

        while (index < strip_index_count)
        {
            long vertex_C = strip_indices[index];

            if (vertex_A == vertex_B || vertex_A == vertex_C || vertex_B == vertex_C)
            {
                (*degenerate_triangles)++;
            }
            else
            {
                (*valid_triangles)++;
            }

            vertex_A = vertex_B;
            vertex_B = vertex_C;
            index++;
        }
    }
};

long find_next_valid_strip_triangle(unsigned short const * strip_indices, long strip_index_count, long previous_triangle_start_index)
{
    mangled_ppc("?find_next_valid_strip_triangle@@YAJPBGJJ@Z");

    long result = NONE;

    long index = previous_triangle_start_index + 3;

    while (index < strip_index_count)
    {
        long vertex_A = strip_indices[index - 2];
        long vertex_B = strip_indices[index - 1];
        long vertex_C = strip_indices[index];

        if ((index & 1) == 1)
        {
            long temp = vertex_A;
            vertex_A = vertex_B;
            vertex_B = temp;
        }

        if (vertex_A == vertex_B || vertex_A == vertex_C || vertex_B == vertex_C)
        {
        }
        else
        {
            result = index - 2;
            goto done;
        }

        index++;
    }

done:
    return result;
};

long find_triangle(unsigned short vertex_A, unsigned short vertex_B, unsigned short vertex_C, unsigned short const * indices, long index_count, bool strips, long * rotation)
{
    mangled_ppc("?find_triangle@@YAJGGGPBGJ_NPAJ@Z");

    long triangle_index;
    long index = 2;

    triangle_index = NONE;

    while (index < index_count)
    {
        long vertex_0 = indices[index - 2];
        long vertex_1 = indices[index - 1];
        long vertex_2 = indices[index];

        triangle_index = index - 2;

        if (strips)
        {
            if ((index & 1) == 1)
            {
                long temp = vertex_0;
                vertex_0 = vertex_1;
                vertex_1 = temp;
            }

            index++;
        }
        else
        {
            index += 3;
        }

        if (vertex_0 == vertex_A && vertex_1 == vertex_B && vertex_2 == vertex_C)
        {
            *rotation = 0;
            goto done;
        }
        else if (vertex_0 == vertex_B && vertex_1 == vertex_C && vertex_2 == vertex_A)
        {
            *rotation = 1;
            goto done;
        }
        else if (vertex_0 == vertex_C && vertex_1 == vertex_A && vertex_2 == vertex_B)
        {
            *rotation = 2;
            goto done;
        }
    }

    triangle_index = NONE;

done:
    return triangle_index;
};

long find_triangle_long(long vertex_A, long vertex_B, long vertex_C, long const * indices, long index_count, bool strips, long * rotation)
{
    mangled_ppc("?find_triangle_long@@YAJJJJPBJJ_NPAJ@Z");

    long triangle_index;
    long index = 2;

    triangle_index = NONE;

    while (index < index_count)
    {
        long vertex_0 = indices[index - 2];
        long vertex_1 = indices[index - 1];
        long vertex_2 = indices[index];

        triangle_index = index - 2;

        if (strips)
        {
            if ((index & 1) == 1)
            {
                long temp = vertex_0;
                vertex_0 = vertex_1;
                vertex_1 = temp;
            }

            index++;
        }
        else
        {
            index += 3;
        }

        if (vertex_0 == vertex_A && vertex_1 == vertex_B && vertex_2 == vertex_C)
        {
            *rotation = 0;
            goto done;
        }
        else if (vertex_0 == vertex_B && vertex_1 == vertex_C && vertex_2 == vertex_A)
        {
            *rotation = 1;
            goto done;
        }
        else if (vertex_0 == vertex_C && vertex_1 == vertex_A && vertex_2 == vertex_B)
        {
            *rotation = 2;
            goto done;
        }
    }

    triangle_index = NONE;

done:
    return triangle_index;
};
