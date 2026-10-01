#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\curve_codec\\catmull_spline.cpp"
/* ---------- headers */

#include "omaha\animations\curve_codec\catmull_spline.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <math.h>
#include <new>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: float s_catmull_spline::calculate_fitting_error(long, float const *, float *, float *) const;
// public: float s_catmull_spline::interpolate_by_index(long, long) const;
// private: float s_catmull_spline::index_2_time(long, long) const;
// private: void s_catmull_spline::pregenerate_sample_coefficients(long, struct s_catmull_coefficients *) const;
// private: float s_catmull_spline::calculate_fitting_error_fast(long, float const *, struct s_catmull_coefficients const *, float *, float *) const;
// public: float s_catmull_spline::fit_with_optimization(long, float const *, float);

real s_catmull_spline::calculate_fitting_error(long sample_count, real const * samples, real * out_average_error, real * out_max_error) const
{
    mangled_ppc("?calculate_fitting_error@s_catmull_spline@@QBAMJPBMPAM1@Z");

    real average_error = 0.0f;
    real max_error = 0.0f;

    if (sample_count <= 2)
    {
        goto finish;
    }

    for (long sample_index = 0; sample_index < sample_count; sample_index++)
    {
        real interpolated_value = interpolate_by_index(sample_index, sample_count);
        real error = fabs(interpolated_value - samples[sample_index]);
        average_error += error / sample_count;
        if (error > max_error)
        {
            max_error = error;
        }
    }

finish:

    if (out_average_error)
    {
        *out_average_error = average_error;
    }
    if (out_max_error)
    {
        *out_max_error = max_error;
    }

    return spline_fitting_preceptual_error(max_error, average_error);
};

void s_catmull_spline::pregenerate_sample_coefficients(long sample_count, s_catmull_coefficients * sample_coeffs) const
{
    mangled_ppc("?pregenerate_sample_coefficients@s_catmull_spline@@ABAXJPAUs_catmull_coefficients@@@Z");

    assert_tag_debug_untracked_jul_11_2011(38, sample_coeffs);
    assert_tag_debug_untracked_jul_11_2011(39, sample_count >= 2);

    for (long sample_index = 0; sample_index < sample_count; sample_index++)
    {
        real time = index_2_time(sample_index, sample_count);
        calculate_coefficients_by_time(time, &sample_coeffs[sample_index]);
    }
};

real s_catmull_spline::calculate_fitting_error_fast(long sample_count, real const * samples, s_catmull_coefficients const * sample_coeffs, real * out_average_error, real * out_max_error) const
{
    mangled_ppc("?calculate_fitting_error_fast@s_catmull_spline@@ABAMJPBMPBUs_catmull_coefficients@@PAM2@Z");

    real average_error = 0.0f;
    real max_error = 0.0f;

    assert_tag_debug_untracked_jul_11_2011(56, sample_coeffs);

    if (sample_count <= 2)
    {
        goto finish;
    }

    for (long sample_index = 0; sample_index < sample_count; sample_index++)
    {
        real interpolated_value = interpolate_by_coefficients(&sample_coeffs[sample_index]);
        real error = fabs(interpolated_value - samples[sample_index]);
        average_error += error / sample_count;
        if (error > max_error)
        {
            max_error = error;
        }
    }

finish:

    if (out_average_error)
    {
        *out_average_error = average_error;
    }
    if (out_max_error)
    {
        *out_max_error = max_error;
    }

    return spline_fitting_preceptual_error(max_error, average_error);
};

real s_catmull_spline::fit_with_optimization(long sample_count, real const * samples, real error_threshold)
{
    mangled_ppc("?fit_with_optimization@s_catmull_spline@@QAAMJPBMM@Z");

    assert_tag_debug_untracked_jul_11_2011(85, sample_count > 0);

    s_catmull_coefficients * sample_coeffs = NULL;

    p0 = samples[0];
    p1 = samples[sample_count - 1];
    real delta = samples[sample_count - 1] - samples[0];
    m0 = delta;
    m1 = delta;

    real best_error = calculate_fitting_error(sample_count, samples, NULL, NULL);

    if (sample_count <= 2)
    {
        goto cleanup;
    }

    sample_coeffs = new s_catmull_coefficients[sample_count];
    if (!sample_coeffs)
    {
        goto cleanup;
    }

    pregenerate_sample_coefficients(sample_count, sample_coeffs);

    s_catmull_spline spline = *this;
    for (long m0_index = -k_spline_lean_step_count; m0_index <= k_spline_lean_step_count; m0_index++)
    {
        for (long m1_index = -k_spline_lean_step_count; m1_index <= k_spline_lean_step_count; m1_index++)
        {
            spline.set_lean_indices(static_cast<char>(m0_index), static_cast<char>(m1_index));
            real error = spline.calculate_fitting_error_fast(sample_count, samples, sample_coeffs, NULL, NULL);
            if (error < best_error)
            {
                m0 = spline.m0;
                m1 = spline.m1;
                best_error = error;
                if (best_error < error_threshold)
                {
                    goto cleanup;
                }
            }
        }
    }

cleanup:
    if (sample_coeffs)
    {
        delete[] sample_coeffs;
    }

    return best_error;
};
