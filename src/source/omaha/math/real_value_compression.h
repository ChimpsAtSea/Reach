#pragma once
#ifndef __REAL_VALUE_COMPRESSION_H__
#define __REAL_VALUE_COMPRESSION_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

union vector3d;

unsigned long compress_real_vector3d_normalized_to_DHenN3(vector3d const * v);
void uncompress_DHenN3_to_real_vector3d_normalized(unsigned long compressed, vector3d * v);

/* ---------- globals */

/* ---------- public code */

#endif // __REAL_VALUE_COMPRESSION_H__

