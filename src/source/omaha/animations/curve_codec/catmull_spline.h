#ifndef __CATMULL_SPLINE_H__
#define __CATMULL_SPLINE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"

/* ---------- constants */

enum
{
    k_spline_lean_step_count = 7
};

/* ---------- definitions */

struct s_catmull_coefficients
{
    real h00;
    real h01;
    real h10;
    real h11;
};
static_assert(sizeof(s_catmull_coefficients) == 0x10, "s_catmull_coefficients");

struct s_catmull_spline
{
public:
    void get_lean_indices(char * m0_index, char * m1_index) const;
    void set_lean_indices(char m0_index, char m1_index);
    void set_lean_indices(real m0, real m1);
    real interpolate_by_time(real time) const;
    real calculate_fitting_error(long sample_count, real const * samples, real * out_average_error, real * out_max_error) const;
    real fit_with_optimization(long sample_count, real const * samples, real error_threshold);

    inline real interpolate_by_index(long index, long sample_count) const
    {
        mangled_ppc("?interpolate_by_index@s_catmull_spline@@QBAMJJ@Z");

        real time = index_2_time(index, sample_count);
        return interpolate_by_time(time);
    };

private:
    void calculate_coefficients_by_time(real time, s_catmull_coefficients * coefficients) const;
    real interpolate_by_coefficients(s_catmull_coefficients const * coefficients) const;
    void pregenerate_sample_coefficients(long sample_count, s_catmull_coefficients * sample_coeffs) const;
    real calculate_fitting_error_fast(long sample_count, real const * samples, s_catmull_coefficients const * sample_coeffs, real * out_average_error, real * out_max_error) const;

    inline real index_2_time(long index, long sample_count) const
    {
        mangled_ppc("?index_2_time@s_catmull_spline@@ABAMJJ@Z");

        assert_decomp(index>= 0 && sample_count>=2, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\animations\\curve_codec\\catmull_spline.h", 262);
        assert_decomp(index < sample_count, "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\animations\\curve_codec\\catmull_spline.h", 263);

        real time = static_cast<real>(index) / static_cast<real>(sample_count - 1);
        return time;
    };

public:
    real p0;
    real p1;
    real m0;
    real m1;
};
static_assert(sizeof(s_catmull_spline) == 0x10, "s_catmull_spline");

/* ---------- prototypes */

extern real spline_fitting_preceptual_error(real max_error, real average_error);

/* ---------- globals */

/* ---------- public code */

#endif // __CATMULL_SPLINE_H__
