#pragma once
#ifndef __AIM_ASSIST_ENCODING_H__
#define __AIM_ASSIST_ENCODING_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_aim_assist_encoding_precision
{
    _aim_assist_encoding_precision_low = 0,
    _aim_assist_encoding_precision_high,

    k_aim_assist_encoding_precision_count
};

/* ---------- prototypes */

class c_bitstream;
union vector3d;

void aim_assist_encode_lead_vector(c_bitstream * packet, vector3d const * lead_vector, e_aim_assist_encoding_precision precision);
void aim_assist_decode_lead_vector(c_bitstream * packet, vector3d * lead_vector, e_aim_assist_encoding_precision precision);
bool aim_assist_compare_lead_vectors(vector3d const * lead_vector1, vector3d const * lead_vector2, e_aim_assist_encoding_precision precision);
bool aim_assist_can_encode_lead_vector(vector3d * lead_vector);
long lead_vector_magnitude_bits(e_aim_assist_encoding_precision precision);
long lead_vector_orientation_bits(e_aim_assist_encoding_precision precision);

/* ---------- globals */

/* ---------- public code */

#endif // __AIM_ASSIST_ENCODING_H__

