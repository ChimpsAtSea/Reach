#pragma once
#ifndef __MATRIX_MATH_H__
#define __MATRIX_MATH_H__

/* ---------- headers */

#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void matrix4x3_rotation_from_vectors(real_matrix4x3 * matrix, vector3d const * forward, vector3d const * up);
void matrix4x3_rotation_from_angles(real_matrix4x3 * matrix, real yaw, real pitch, real roll);
void matrix4x3_rotation_to_quaternion(real_matrix4x3 const * matrix, real32_quaternion * quaternion);
vector3d * matrix3x3_transform_vector(matrix3x3 const * matrix, vector3d const * vector, vector3d * result);
void matrix4x3_inverse(real_matrix4x3 const * matrix, real_matrix4x3 * result);
void matrix4x3_multiply(real_matrix4x3 const * __restrict a, real_matrix4x3 const * __restrict b, real_matrix4x3 * __restrict result);
real_point3d * matrix4x3_transform_point(real_matrix4x3 const * matrix, real_point3d const * point, real_point3d * result);
vector3d * matrix4x3_transform_normal(real_matrix4x3 const * matrix, vector3d const * normal, vector3d * result);
vector3d * matrix4x3_transform_vector(real_matrix4x3 const * matrix, vector3d const * vector, vector3d * result);
vector3d * matrix4x3_inverse_transform_vector(real_matrix4x3 const * matrix, vector3d const * vector, vector3d * result);
void matrix4x3_rotation_from_axis_and_angle(real_matrix4x3 * matrix, vector3d const * axis, real sine_angle, real cosine_angle);
matrix3x3 * matrix3x3_multiply(matrix3x3 const * a, matrix3x3 const * b, matrix3x3 * result);
matrix3x3 * matrix3x3_rotation_from_quaternion(matrix3x3 * __restrict matrix, real32_quaternion const * __restrict quaternion);

/* ---------- globals */

/* ---------- public code */

#endif // __MATRIX_MATH_H__

