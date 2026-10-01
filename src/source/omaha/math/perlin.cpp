#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\math\\perlin.cpp"
/* ---------- headers */

#include "omaha\math\perlin.h"
#include "omaha\math\real_math.h"
#include "omaha\math\random_math.h"
#include "omaha\math\real_value_compression.h"
#include "omaha\game\game_time.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void perlin_state_reset(struct s_perlin_state *);
// void perlin_state_update(struct s_perlin_state *, long, float, float, float, bool, union real_point3d *);
// void perlin_state_compress(struct s_perlin_state const *, float, struct s_compressed_perlin_state *);
// void perlin_state_decompress(struct s_compressed_perlin_state const *, float, struct s_perlin_state *);

void perlin_state_reset(s_perlin_state * perlin)
{
    mangled_ppc("?perlin_state_reset@@YAXPAUs_perlin_state@@@Z");

    perlin->random_offset_ticks = 0;
    perlin->random_offset_total_ticks = NONE;
    perlin->previous_random_offset = *global_origin3d;
    perlin->random_offset = *global_origin3d;
};

void perlin_state_update(s_perlin_state * perlin, long ticks, real offset_scale, real offset_period_min, real offset_period_max, bool ground_based, real_point3d * offset_ref)
{
    mangled_ppc("?perlin_state_update@@YAXPAUs_perlin_state@@JMMM_NPATreal_point3d@@@Z");

    real t;
    real deltax;
    real deltay;
    real deltaz;

    assert_tag_debug_untracked_jul_11_2011(41, offset_ref);

    perlin->random_offset_ticks += ticks;
    if (perlin->random_offset_ticks > perlin->random_offset_total_ticks)
    {
        perlin->previous_random_offset = perlin->random_offset;
        perlin->random_offset.x = _real_random_range(get_random_seed_address(), "perlin-random-offset-x", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 50, -offset_scale, offset_scale);
        perlin->random_offset.y = _real_random_range(get_random_seed_address(), "perlin-random-offset-y", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 51, -offset_scale, offset_scale);
        if (ground_based)
        {
            perlin->random_offset.z = 0.0f;
        }
        else
        {
            perlin->random_offset.z = _real_random_range(get_random_seed_address(), "perlin-random-offset-z", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 59, -offset_scale, offset_scale);
        }

        real offset_period = _real_random_range(get_random_seed_address(), "perlin-random-offset-period", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 62, offset_period_min, offset_period_max);
        perlin->random_offset_total_ticks = static_cast<short>(int_max<long>(1, game_seconds_to_ticks_round(offset_period)));
        perlin->random_offset_ticks = 0;
    }

    if (perlin->random_offset_total_ticks > 0)
    {
        t = 0.5f + 0.5f * cosine(k_pi * (perlin->random_offset_ticks / static_cast<real>(perlin->random_offset_total_ticks)));
    }
    else
    {
        t = 0.0f;
    }

    deltax = perlin->random_offset.x - perlin->previous_random_offset.x;
    deltay = perlin->random_offset.y - perlin->previous_random_offset.y;
    offset_ref->x = perlin->previous_random_offset.x + deltax * (1.0f - t);
    offset_ref->y = perlin->previous_random_offset.y + deltay * (1.0f - t);
    if (ground_based)
    {
        offset_ref->z = 0.0f;
    }
    else
    {
        deltaz = perlin->random_offset.z - perlin->previous_random_offset.z;
        offset_ref->z = perlin->previous_random_offset.z + deltaz * (1.0f - t);
    }
};

void perlin_state_compress(s_perlin_state const * perlin, real scale, s_compressed_perlin_state * out_compressed_perlin)
{
    mangled_ppc("?perlin_state_compress@@YAXPBUs_perlin_state@@MPAUs_compressed_perlin_state@@@Z");

    assert_tag_debug_untracked_jul_11_2011(97, perlin);
    assert_tag_debug_untracked_jul_11_2011(98, out_compressed_perlin);

    real inverse_scale = scale > 0.0f ? 1.0f / scale : 0.0f;
    vector3d previous_vector;
    vector3d random_offset_vector;

    out_compressed_perlin->random_offset_total_ticks = static_cast<unsigned char>(int_min(int_max(perlin->random_offset_total_ticks, 0), 255));
    out_compressed_perlin->random_offset_ticks = static_cast<unsigned char>(int_min(int_max(perlin->random_offset_ticks, 0), 255));
    scale_vector3d(reinterpret_cast<vector3d const *>(&perlin->random_offset), inverse_scale, &random_offset_vector);
    scale_vector3d(reinterpret_cast<vector3d const *>(&perlin->previous_random_offset), inverse_scale, &previous_vector);
    out_compressed_perlin->random_offset = compress_real_vector3d_normalized_to_DHenN3(&random_offset_vector);
    out_compressed_perlin->previous_random_offset = compress_real_vector3d_normalized_to_DHenN3(&previous_vector);
};

void perlin_state_decompress(s_compressed_perlin_state const * compressed_perlin, real scale, s_perlin_state * out_perlin)
{
    mangled_ppc("?perlin_state_decompress@@YAXPBUs_compressed_perlin_state@@MPAUs_perlin_state@@@Z");

    assert_tag_debug_untracked_jul_11_2011(121, compressed_perlin);
    assert_tag_debug_untracked_jul_11_2011(122, out_perlin);

    vector3d previous_vector;
    vector3d random_offset_vector;

    out_perlin->random_offset_total_ticks = compressed_perlin->random_offset_total_ticks;
    out_perlin->random_offset_ticks = compressed_perlin->random_offset_ticks;
    uncompress_DHenN3_to_real_vector3d_normalized(compressed_perlin->random_offset, &random_offset_vector);
    uncompress_DHenN3_to_real_vector3d_normalized(compressed_perlin->previous_random_offset, &previous_vector);
    scale_vector3d(&random_offset_vector, scale, reinterpret_cast<vector3d *>(&out_perlin->random_offset));
    scale_vector3d(&previous_vector, scale, reinterpret_cast<vector3d *>(&out_perlin->previous_random_offset));
};
