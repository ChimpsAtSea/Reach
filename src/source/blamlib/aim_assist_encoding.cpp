#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\aim_assist_encoding.cpp"
/* ---------- headers */

#include "blamlib\aim_assist_encoding.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

static float const k_aim_assist_lead_vector_magnitude_minimum = 0.01f;
static float const k_aim_assist_lead_vector_magnitude_maximum = 10.0f;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void aim_assist_encode_lead_vector(class c_bitstream *, union vector3d const *, enum e_aim_assist_encoding_precision);
// void aim_assist_decode_lead_vector(class c_bitstream *, union vector3d *, enum e_aim_assist_encoding_precision);
// bool aim_assist_compare_lead_vectors(union vector3d const *, union vector3d const *, enum e_aim_assist_encoding_precision);
// bool aim_assist_can_encode_lead_vector(union vector3d *);
// long lead_vector_magnitude_bits(enum e_aim_assist_encoding_precision);
// long lead_vector_orientation_bits(enum e_aim_assist_encoding_precision);

void aim_assist_encode_lead_vector(c_bitstream * packet, vector3d const * lead_vector, e_aim_assist_encoding_precision precision)
{
    mangled_ppc("?aim_assist_encode_lead_vector@@YAXPAVc_bitstream@@PBTvector3d@@W4e_aim_assist_encoding_precision@@@Z");

    packet->write_vector("lead_vector", lead_vector, k_aim_assist_lead_vector_magnitude_minimum, k_aim_assist_lead_vector_magnitude_maximum, lead_vector_magnitude_bits(precision), lead_vector_orientation_bits(precision));
};

void aim_assist_decode_lead_vector(c_bitstream * packet, vector3d * lead_vector, e_aim_assist_encoding_precision precision)
{
    mangled_ppc("?aim_assist_decode_lead_vector@@YAXPAVc_bitstream@@PATvector3d@@W4e_aim_assist_encoding_precision@@@Z");

    packet->read_vector("lead_vector", lead_vector, k_aim_assist_lead_vector_magnitude_minimum, k_aim_assist_lead_vector_magnitude_maximum, lead_vector_magnitude_bits(precision), lead_vector_orientation_bits(precision));
};

bool aim_assist_compare_lead_vectors(vector3d const * lead_vector1, vector3d const * lead_vector2, e_aim_assist_encoding_precision precision)
{
    mangled_ppc("?aim_assist_compare_lead_vectors@@YA_NPBTvector3d@@0W4e_aim_assist_encoding_precision@@@Z");

    bool const vectors_equal = c_bitstream::compare_vectors(lead_vector1, lead_vector2, k_aim_assist_lead_vector_magnitude_minimum, k_aim_assist_lead_vector_magnitude_maximum, lead_vector_magnitude_bits(precision), lead_vector_orientation_bits(precision));

    return vectors_equal;
};

bool aim_assist_can_encode_lead_vector(vector3d * lead_vector)
{
    mangled_ppc("?aim_assist_can_encode_lead_vector@@YA_NPATvector3d@@@Z");

    bool can_encode = true;
    if (magnitude_squared3d(lead_vector) > k_aim_assist_lead_vector_magnitude_maximum * k_aim_assist_lead_vector_magnitude_maximum)
    {
        can_encode = false;
    }

    return can_encode;
};

long lead_vector_magnitude_bits(e_aim_assist_encoding_precision precision)
{
    mangled_ppc("?lead_vector_magnitude_bits@@YAJW4e_aim_assist_encoding_precision@@@Z");

    return precision == _aim_assist_encoding_precision_high ? 14 : 7;
};

long lead_vector_orientation_bits(e_aim_assist_encoding_precision precision)
{
    mangled_ppc("?lead_vector_orientation_bits@@YAJW4e_aim_assist_encoding_precision@@@Z");

    return precision == _aim_assist_encoding_precision_high ? 20 : 15;
};

