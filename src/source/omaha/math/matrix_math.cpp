#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\math\\matrix_math.cpp"
/* ---------- headers */

#include "omaha\math\matrix_math.h"
#include "omaha\math\real_math.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

float magnitude_squared4d(union vector4d const * v)
{
    mangled_ppc("?magnitude_squared4d@@YAMPBTvector4d@@@Z");

	return v->i * v->i + v->j * v->j + v->k * v->k + v->l * v->l;
};

float magnitude4d(union vector4d const * v)
{
    mangled_ppc("?magnitude4d@@YAMPBTvector4d@@@Z");

	return square_root(magnitude_squared4d(v));
};

/* ---------- private code */

/* ---------- reverse engineering */

// void matrix4x3_identity(struct real_matrix4x3*);
// void matrix4x3_transpose(struct real_matrix4x3*);
// void matrix4x3_inverse(struct real_matrix4x3const *, struct real_matrix4x3*);
// void matrix4x3_scale(struct real_matrix4x3*, float);
// void matrix4x3_translation(struct real_matrix4x3*, union real_point3d const *);
// void matrix4x3_rotation_from_axis_and_angle(struct real_matrix4x3*, union vector3d const *, float, float);
// void matrix4x3_rotation_from_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *);
// void matrix4x3_rotation_from_nonaxial_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *);
// void matrix4x3_rotation_from_nonaxial_vectors_using_up(struct real_matrix4x3*, union vector3d const *, union vector3d const *);
// void matrix4x3_rotation_from_nonaxial_forward_and_left(struct real_matrix4x3*, union vector3d const *, union vector3d const *);
// void matrix4x3_rotation_between_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *);
// void matrix4x3_rotation_from_angles(struct real_matrix4x3*, float, float, float);
// void matrix4x3_rotation_to_angles(struct real_matrix4x3const *, union euler_angles3d *);
// struct matrix3x3* matrix3x3_rotation_from_quaternion(unsigned int *, struct matrix3x3&, unsigned int *, struct real32_quaternion &volatile);
// void matrix4x3_rotation_from_quaternion(struct real_matrix4x3*, struct real32_quaternion const *);
// struct real32_quaternion * matrix3x3_rotation_to_quaternion(unsigned int *, struct matrix3x3&volatile, unsigned int *, struct real32_quaternion &);
// bool matrix3x3_normalize(struct matrix3x3*);
// void matrix4x3_rotation_to_quaternion(struct real_matrix4x3const *, struct real32_quaternion *);
// void matrix4x3_from_point_and_vectors(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *);
// void matrix4x3_from_point_and_nonaxial_vectors(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *);
// void matrix4x3_from_point_and_nonaxial_vectors_using_up(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *);
// void matrix4x3_from_point_and_nonaxial_forward_and_left(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *);
// void matrix4x3_from_point_and_quaternion(struct real_matrix4x3*, union real_point3d const *, struct real32_quaternion const *);
// void matrix4x3_from_orientation(unsigned int *, struct real_matrix4x3&, unsigned int *, struct real_orientation &volatile);
// void matrix4x3_to_orientation(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &);
// void matrix4x3_apply_orientation(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &volatile, unsigned int *, struct real_matrix4x3&);
// void matrix4x3_apply_orientation_vmx(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &volatile, unsigned int *, struct real_matrix4x3&);
// __lvx;
// void matrix4x3_from_plane(struct real_matrix4x3*, struct plane3d const *);
// void matrix4x3_to_point_and_vectors(struct real_matrix4x3const *, union real_point3d *, union vector3d *, union vector3d *);
// union vector3d * vector_from_matrices4x3(struct real_matrix4x3const *, struct real_matrix4x3const *, union vector3d *);
// union real_point3d * matrix4x3_transform_point(struct real_matrix4x3const *, union real_point3d const *, union real_point3d *);
// union vector3d * matrix4x3_transform_vector(struct real_matrix4x3const *, union vector3d const *, union vector3d *);
// union vector3d * matrix4x3_transform_normal(struct real_matrix4x3const *, union vector3d const *, union vector3d *);
// struct plane3d * matrix4x3_transform_plane(struct real_matrix4x3const *, struct plane3d const *, struct plane3d *);
// union real_point3d * matrix4x3_inverse_transform_point(struct real_matrix4x3const *, union real_point3d const *, union real_point3d *);
// union vector3d * matrix4x3_inverse_transform_vector(struct real_matrix4x3const *, union vector3d const *, union vector3d *);
// union vector3d * matrix4x3_inverse_transform_normal(struct real_matrix4x3const *, union vector3d const *, union vector3d *);
// struct plane3d * matrix4x3_inverse_transform_plane(struct real_matrix4x3const *, struct plane3d const *, struct plane3d *);
// void matrix4x3_transform_points(struct real_matrix4x3const *, long, union real_point3d const *const, union real_point3d *const);
// void matrix4x3_inverse_transform_points(struct real_matrix4x3const *, long, union real_point3d const *const, union real_point3d *const);
// void matrix4x3_multiply(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, unsigned int *, struct real_matrix4x3&);
// void matrix4x3_multiply_vmx(struct real_matrix4x3const *, struct real_matrix4x3const *, struct real_matrix4x3*);
// float matrix3x3_determinant(struct matrix3x3const *);
// struct matrix3x3* matrix3x3_transpose(struct matrix3x3const *, struct matrix3x3*);
// struct matrix3x3* matrix3x3_inverse(struct matrix3x3const *, float, struct matrix3x3*);
// struct matrix3x3* matrix3x3_from_forward_and_up(struct matrix3x3*, union vector3d const *, union vector3d const *);
// struct matrix3x3* matrix3x3_from_axis_and_angle(struct matrix3x3*, union vector3d const *, float, float);
// void matrix3x3_from_angles_cpp(struct matrix3x3*, float, float, float);
// void matrix3x3_from_angles(struct matrix3x3*, float, float, float);
// void matrix3x3_from_angles_vmx(struct matrix3x3*, float, float, float);
// struct matrix3x3* matrix3x3_multiply(struct matrix3x3const *, struct matrix3x3const *, struct matrix3x3*);
// union vector3d * matrix3x3_transform_vector(struct matrix3x3const *, union vector3d const *, union vector3d *);
// union vector3d * matrix3x3_inverse_transform_vector(struct matrix3x3const *, union vector3d const *, union vector3d *);
// bool linear_equation_solve_3x3(double const (*const)[3], double const *const, double *const);
// bool linear_equation_solve_4x4(double const (*const)[4], double const *const, double *const);
// void prefetch<struct real_matrix4x3>(struct real_matrix4x3const *);
// void XMVectorSinCos(struct __vector4*, struct __vector4*, struct __vector4);
// float magnitude4d(union vector4d const *);
// float magnitude_squared4d(union vector4d const *);

//void matrix4x3_identity(struct real_matrix4x3*)
//{
//    mangled_ppc("?matrix4x3_identity@@YAXPAUreal_matrix4x3@@@Z");
//};

//void matrix4x3_transpose(struct real_matrix4x3*)
//{
//    mangled_ppc("?matrix4x3_transpose@@YAXPAUreal_matrix4x3@@@Z");
//};

//void matrix4x3_inverse(struct real_matrix4x3const *, struct real_matrix4x3*)
//{
//    mangled_ppc("?matrix4x3_inverse@@YAXPBUreal_matrix4x3@@PAU1@@Z");
//};

//void matrix4x3_scale(struct real_matrix4x3*, float)
//{
//    mangled_ppc("?matrix4x3_scale@@YAXPAUreal_matrix4x3@@M@Z");
//};

//void matrix4x3_translation(struct real_matrix4x3*, union real_point3d const *)
//{
//    mangled_ppc("?matrix4x3_translation@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@@Z");
//};

//void matrix4x3_rotation_from_axis_and_angle(struct real_matrix4x3*, union vector3d const *, float, float)
//{
//    mangled_ppc("?matrix4x3_rotation_from_axis_and_angle@@YAXPAUreal_matrix4x3@@PBTvector3d@@MM@Z");
//};

//void matrix4x3_rotation_from_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_rotation_from_vectors@@YAXPAUreal_matrix4x3@@PBTvector3d@@1@Z");
//};

//void matrix4x3_rotation_from_nonaxial_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_rotation_from_nonaxial_vectors@@YAXPAUreal_matrix4x3@@PBTvector3d@@1@Z");
//};

//void matrix4x3_rotation_from_nonaxial_vectors_using_up(struct real_matrix4x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_rotation_from_nonaxial_vectors_using_up@@YAXPAUreal_matrix4x3@@PBTvector3d@@1@Z");
//};

//void matrix4x3_rotation_from_nonaxial_forward_and_left(struct real_matrix4x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_rotation_from_nonaxial_forward_and_left@@YAXPAUreal_matrix4x3@@PBTvector3d@@1@Z");
//};

//void matrix4x3_rotation_between_vectors(struct real_matrix4x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_rotation_between_vectors@@YAXPAUreal_matrix4x3@@PBTvector3d@@1@Z");
//};

//void matrix4x3_rotation_from_angles(struct real_matrix4x3*, float, float, float)
//{
//    mangled_ppc("?matrix4x3_rotation_from_angles@@YAXPAUreal_matrix4x3@@MMM@Z");
//};

//void matrix4x3_rotation_to_angles(struct real_matrix4x3const *, union euler_angles3d *)
//{
//    mangled_ppc("?matrix4x3_rotation_to_angles@@YAXPBUreal_matrix4x3@@PATeuler_angles3d@@@Z");
//};

//struct matrix3x3* matrix3x3_rotation_from_quaternion(unsigned int *, struct matrix3x3&, unsigned int *, struct real32_quaternion &volatile)
//{
//    mangled_ppc("?matrix3x3_rotation_from_quaternion@@YAPAUmatrix3x3@@PIAU1@PIBUreal32_quaternion@@@Z");
//};

//void matrix4x3_rotation_from_quaternion(struct real_matrix4x3*, struct real32_quaternion const *)
//{
//    mangled_ppc("?matrix4x3_rotation_from_quaternion@@YAXPAUreal_matrix4x3@@PBUreal32_quaternion@@@Z");
//};

//struct real32_quaternion * matrix3x3_rotation_to_quaternion(unsigned int *, struct matrix3x3&volatile, unsigned int *, struct real32_quaternion &)
//{
//    mangled_ppc("?matrix3x3_rotation_to_quaternion@@YAPAUreal32_quaternion@@PIBUmatrix3x3@@PIAU1@@Z");
//};

//bool matrix3x3_normalize(struct matrix3x3*)
//{
//    mangled_ppc("?matrix3x3_normalize@@YA_NPAUmatrix3x3@@@Z");
//};

//void matrix4x3_rotation_to_quaternion(struct real_matrix4x3const *, struct real32_quaternion *)
//{
//    mangled_ppc("?matrix4x3_rotation_to_quaternion@@YAXPBUreal_matrix4x3@@PAUreal32_quaternion@@@Z");
//};

//void matrix4x3_from_point_and_vectors(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_from_point_and_vectors@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@PBTvector3d@@2@Z");
//};

//void matrix4x3_from_point_and_nonaxial_vectors(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_from_point_and_nonaxial_vectors@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@PBTvector3d@@2@Z");
//};

//void matrix4x3_from_point_and_nonaxial_vectors_using_up(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_from_point_and_nonaxial_vectors_using_up@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@PBTvector3d@@2@Z");
//};

//void matrix4x3_from_point_and_nonaxial_forward_and_left(struct real_matrix4x3*, union real_point3d const *, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix4x3_from_point_and_nonaxial_forward_and_left@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@PBTvector3d@@2@Z");
//};

//void matrix4x3_from_point_and_quaternion(struct real_matrix4x3*, union real_point3d const *, struct real32_quaternion const *)
//{
//    mangled_ppc("?matrix4x3_from_point_and_quaternion@@YAXPAUreal_matrix4x3@@PBTreal_point3d@@PBUreal32_quaternion@@@Z");
//};

//void matrix4x3_from_orientation(unsigned int *, struct real_matrix4x3&, unsigned int *, struct real_orientation &volatile)
//{
//    mangled_ppc("?matrix4x3_from_orientation@@YAXPIAUreal_matrix4x3@@PIBUreal_orientation@@@Z");
//};

//void matrix4x3_to_orientation(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &)
//{
//    mangled_ppc("?matrix4x3_to_orientation@@YAXPIBUreal_matrix4x3@@PIAUreal_orientation@@@Z");
//};

//void matrix4x3_apply_orientation(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &volatile, unsigned int *, struct real_matrix4x3&)
//{
//    mangled_ppc("?matrix4x3_apply_orientation@@YAXPIBUreal_matrix4x3@@PIBUreal_orientation@@PIAU1@@Z");
//};

//void matrix4x3_apply_orientation_vmx(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, struct real_orientation &volatile, unsigned int *, struct real_matrix4x3&)
//{
//    mangled_ppc("?matrix4x3_apply_orientation_vmx@@YAXPIBUreal_matrix4x3@@PIBUreal_orientation@@PIAU1@@Z");
//};

//__lvx
//{
//    mangled_ppc("__lvx");
//};

//void matrix4x3_from_plane(struct real_matrix4x3*, struct plane3d const *)
//{
//    mangled_ppc("?matrix4x3_from_plane@@YAXPAUreal_matrix4x3@@PBUplane3d@@@Z");
//};

//void matrix4x3_to_point_and_vectors(struct real_matrix4x3const *, union real_point3d *, union vector3d *, union vector3d *)
//{
//    mangled_ppc("?matrix4x3_to_point_and_vectors@@YAXPBUreal_matrix4x3@@PATreal_point3d@@PATvector3d@@2@Z");
//};

//union vector3d * vector_from_matrices4x3(struct real_matrix4x3const *, struct real_matrix4x3const *, union vector3d *)
//{
//    mangled_ppc("?vector_from_matrices4x3@@YAPATvector3d@@PBUreal_matrix4x3@@0PAT1@@Z");
//};

//union real_point3d * matrix4x3_transform_point(struct real_matrix4x3const *, union real_point3d const *, union real_point3d *)
//{
//    mangled_ppc("?matrix4x3_transform_point@@YAPATreal_point3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//union vector3d * matrix4x3_transform_vector(struct real_matrix4x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix4x3_transform_vector@@YAPATvector3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//union vector3d * matrix4x3_transform_normal(struct real_matrix4x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix4x3_transform_normal@@YAPATvector3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//struct plane3d * matrix4x3_transform_plane(struct real_matrix4x3const *, struct plane3d const *, struct plane3d *)
//{
//    mangled_ppc("?matrix4x3_transform_plane@@YAPAUplane3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
//};

//union real_point3d * matrix4x3_inverse_transform_point(struct real_matrix4x3const *, union real_point3d const *, union real_point3d *)
//{
//    mangled_ppc("?matrix4x3_inverse_transform_point@@YAPATreal_point3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//union vector3d * matrix4x3_inverse_transform_vector(struct real_matrix4x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix4x3_inverse_transform_vector@@YAPATvector3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//union vector3d * matrix4x3_inverse_transform_normal(struct real_matrix4x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix4x3_inverse_transform_normal@@YAPATvector3d@@PBUreal_matrix4x3@@PBT1@PAT1@@Z");
//};

//struct plane3d * matrix4x3_inverse_transform_plane(struct real_matrix4x3const *, struct plane3d const *, struct plane3d *)
//{
//    mangled_ppc("?matrix4x3_inverse_transform_plane@@YAPAUplane3d@@PBUreal_matrix4x3@@PBU1@PAU1@@Z");
//};

//void matrix4x3_transform_points(struct real_matrix4x3const *, long, union real_point3d const *const, union real_point3d *const)
//{
//    mangled_ppc("?matrix4x3_transform_points@@YAXPBUreal_matrix4x3@@JQBTreal_point3d@@QAT2@@Z");
//};

//void matrix4x3_inverse_transform_points(struct real_matrix4x3const *, long, union real_point3d const *const, union real_point3d *const)
//{
//    mangled_ppc("?matrix4x3_inverse_transform_points@@YAXPBUreal_matrix4x3@@JQBTreal_point3d@@QAT2@@Z");
//};

//void matrix4x3_multiply(unsigned int *, struct real_matrix4x3&volatile, unsigned int *, unsigned int *, struct real_matrix4x3&)
//{
//    mangled_ppc("?matrix4x3_multiply@@YAXPIBUreal_matrix4x3@@0PIAU1@@Z");
//};

//void matrix4x3_multiply_vmx(struct real_matrix4x3const *, struct real_matrix4x3const *, struct real_matrix4x3*)
//{
//    mangled_ppc("?matrix4x3_multiply_vmx@@YAXPBUreal_matrix4x3@@0PAU1@@Z");
//};

//float matrix3x3_determinant(struct matrix3x3const *)
//{
//    mangled_ppc("?matrix3x3_determinant@@YAMPBUmatrix3x3@@@Z");
//};

//struct matrix3x3* matrix3x3_transpose(struct matrix3x3const *, struct matrix3x3*)
//{
//    mangled_ppc("?matrix3x3_transpose@@YAPAUmatrix3x3@@PBU1@PAU1@@Z");
//};

//struct matrix3x3* matrix3x3_inverse(struct matrix3x3const *, float, struct matrix3x3*)
//{
//    mangled_ppc("?matrix3x3_inverse@@YAPAUmatrix3x3@@PBU1@MPAU1@@Z");
//};

//struct matrix3x3* matrix3x3_from_forward_and_up(struct matrix3x3*, union vector3d const *, union vector3d const *)
//{
//    mangled_ppc("?matrix3x3_from_forward_and_up@@YAPAUmatrix3x3@@PAU1@PBTvector3d@@1@Z");
//};

//struct matrix3x3* matrix3x3_from_axis_and_angle(struct matrix3x3*, union vector3d const *, float, float)
//{
//    mangled_ppc("?matrix3x3_from_axis_and_angle@@YAPAUmatrix3x3@@PAU1@PBTvector3d@@MM@Z");
//};

//void matrix3x3_from_angles_cpp(struct matrix3x3*, float, float, float)
//{
//    mangled_ppc("?matrix3x3_from_angles_cpp@@YAXPAUmatrix3x3@@MMM@Z");
//};

//void matrix3x3_from_angles(struct matrix3x3*, float, float, float)
//{
//    mangled_ppc("?matrix3x3_from_angles@@YAXPAUmatrix3x3@@MMM@Z");
//};

//void matrix3x3_from_angles_vmx(struct matrix3x3*, float, float, float)
//{
//    mangled_ppc("?matrix3x3_from_angles_vmx@@YAXPAUmatrix3x3@@MMM@Z");
//};

//struct matrix3x3* matrix3x3_multiply(struct matrix3x3const *, struct matrix3x3const *, struct matrix3x3*)
//{
//    mangled_ppc("?matrix3x3_multiply@@YAPAUmatrix3x3@@PBU1@0PAU1@@Z");
//};

//union vector3d * matrix3x3_transform_vector(struct matrix3x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix3x3_transform_vector@@YAPATvector3d@@PBUmatrix3x3@@PBT1@PAT1@@Z");
//};

//union vector3d * matrix3x3_inverse_transform_vector(struct matrix3x3const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?matrix3x3_inverse_transform_vector@@YAPATvector3d@@PBUmatrix3x3@@PBT1@PAT1@@Z");
//};

bool linear_equation_solve_3x3(double const (* const a)[3], double const* const b, double* const x)
{
	mangled_ppc("?linear_equation_solve_3x3@@YA_NQAY02$$CBNQBNQAN@Z");

	long row_index;
	long x_pivot;
	long y_pivot;
	long reduce_indices[2];
	double x_pivot_row[4];
	double y_pivot_row[3];
	double final_row[2];
	double reduced_rows[2][3];

	if (abs(a[1][0]) > abs(a[2][0]))
	{
		if (abs(a[0][0]) > abs(a[1][0]))
		{
			x_pivot = 0;
			reduce_indices[0] = 1;
			reduce_indices[1] = 2;
		}
		else
		{
			x_pivot = 1;
			reduce_indices[0] = 0;
			reduce_indices[1] = 2;
		}
	}
	else
	{
		if (abs(a[0][0]) > abs(a[2][0]))
		{
			x_pivot = 0;
			reduce_indices[0] = 1;
			reduce_indices[1] = 2;
		}
		else
		{
			x_pivot = 2;
			reduce_indices[0] = 0;
			reduce_indices[1] = 1;
		}
	}
	if (abs(a[x_pivot][0]) < k_real_epsilon)
	{
		return false;
	}
	x_pivot_row[0] = a[x_pivot][0];
	x_pivot_row[1] = a[x_pivot][1] / x_pivot_row[0];
	x_pivot_row[2] = a[x_pivot][2] / x_pivot_row[0];
	x_pivot_row[3] = b[x_pivot] / x_pivot_row[0];
	for (row_index = 0; row_index < 2; row_index++)
	{
		long row = reduce_indices[row_index];
		double multiplier = -a[row][0];
		reduced_rows[row_index][0] = a[row][1] + multiplier * x_pivot_row[1];
		reduced_rows[row_index][1] = a[row][2] + multiplier * x_pivot_row[2];
		reduced_rows[row_index][2] = b[row] + multiplier * x_pivot_row[3];
	}
	y_pivot = abs(reduced_rows[1][0]) > abs(reduced_rows[0][0]);
	if (abs(reduced_rows[y_pivot][0]) < k_real_epsilon)
	{
		return false;
	}
	y_pivot_row[0] = reduced_rows[y_pivot][0];
	y_pivot_row[1] = reduced_rows[y_pivot][1] / y_pivot_row[0];
	y_pivot_row[2] = reduced_rows[y_pivot][2] / y_pivot_row[0];
	{
		double multiplier = -reduced_rows[y_pivot == 0][0];
		final_row[0] = reduced_rows[y_pivot == 0][1] + multiplier * y_pivot_row[1];
		final_row[1] = reduced_rows[y_pivot == 0][2] + multiplier * y_pivot_row[2];
	}
	if (abs(final_row[0]) < k_real_epsilon)
	{
		return false;
	}
	x[2] = final_row[1] / final_row[0];
	x[1] = y_pivot_row[2] - y_pivot_row[1] * x[2];
	x[0] = x_pivot_row[3] - x_pivot_row[2] * x[2] - x_pivot_row[1] * x[1];
	{
		double x_prime[3];
		real_vector3d solution_error;
		x_prime[0] = a[0][0] * x[0] + a[0][1] * x[1] + a[0][2] * x[2];
		x_prime[1] = a[1][0] * x[0] + a[1][1] * x[1] + a[1][2] * x[2];
		x_prime[2] = a[2][0] * x[0] + a[2][1] * x[1] + a[2][2] * x[2];
		solution_error.n[0] = static_cast<float>(x_prime[0] - b[0]);
		solution_error.n[1] = static_cast<float>(x_prime[1] - b[1]);
		solution_error.n[2] = static_cast<float>(x_prime[2] - b[2]);
#ifdef _DEBUG
		assert_tag_debug_untracked_jul_11_2011(2183, magnitude3d(&solution_error) < k_real_epsilon);
#endif
	}
	return true;
}

bool linear_equation_solve_4x4(double const (* const a)[4], double const* const b, double* const x)
{
    mangled_ppc("?linear_equation_solve_4x4@@YA_NQAY03$$CBNQBNQAN@Z");

	long row_index;
	long x_pivot;
	long y_pivot;
	long z_pivot;
	double x_pivot_row[5];
	double y_pivot_row[4];
	double z_pivot_row[3];
	double final_row[2];
	long y_reduced_indices[3];
	long z_reduced_indices[2];
	double y_reduced_rows[3][4];
	double z_reduced_rows[2][3];

	{
		double pivot_magnitude = 0.0;
	    x_pivot = NONE;
		for (row_index = 0; row_index < 4; row_index++)
		{
			double magnitude = abs(a[row_index][0]);
			if (magnitude > pivot_magnitude)
			{
				pivot_magnitude = magnitude;
				x_pivot = row_index;
			}
		}
		if (pivot_magnitude < k_real_epsilon)
		{
			return false;
		}
	}
	for (row_index = 0; row_index < 3; row_index++)
	{
		y_reduced_indices[row_index] = (x_pivot + row_index + 1) % 4;
	}
	x_pivot_row[0] = a[x_pivot][0];
	x_pivot_row[1] = a[x_pivot][1] / x_pivot_row[0];
	x_pivot_row[2] = a[x_pivot][2] / x_pivot_row[0];
	x_pivot_row[3] = a[x_pivot][3] / x_pivot_row[0];
	x_pivot_row[4] = b[x_pivot] / x_pivot_row[0];
	for (row_index = 0; row_index < 3; row_index++)
	{
		long row = y_reduced_indices[row_index];
		double multiplier = -a[row][0];
		y_reduced_rows[row_index][0] = a[row][1] + multiplier * x_pivot_row[1];
		y_reduced_rows[row_index][1] = a[row][2] + multiplier * x_pivot_row[2];
		y_reduced_rows[row_index][2] = a[row][3] + multiplier * x_pivot_row[3];
		y_reduced_rows[row_index][3] = b[row] + multiplier * x_pivot_row[4];
	}
	{
		double pivot_magnitude = 0.0;
	    y_pivot = NONE;
		for (row_index = 0; row_index < 3; row_index++)
		{
			double magnitude = abs(y_reduced_rows[row_index][0]);
			if (magnitude > pivot_magnitude)
			{
				pivot_magnitude = magnitude;
				y_pivot = row_index;
			}
		}
		if (pivot_magnitude < k_real_epsilon)
		{
			return false;
		}
	}
	for (row_index = 0; row_index < 2; row_index++)
	{
		z_reduced_indices[row_index] = (y_pivot + row_index + 1) % 3;
	}
	y_pivot_row[0] = y_reduced_rows[y_pivot][0];
	y_pivot_row[1] = y_reduced_rows[y_pivot][1] / y_pivot_row[0];
	y_pivot_row[2] = y_reduced_rows[y_pivot][2] / y_pivot_row[0];
	y_pivot_row[3] = y_reduced_rows[y_pivot][3] / y_pivot_row[0];
	for (row_index = 0; row_index < 2; row_index++)
	{
		long row = z_reduced_indices[row_index];
		double multiplier = -y_reduced_rows[row][0];
		z_reduced_rows[row_index][0] = y_reduced_rows[row][1] + multiplier * y_pivot_row[1];
		z_reduced_rows[row_index][1] = y_reduced_rows[row][2] + multiplier * y_pivot_row[2];
		z_reduced_rows[row_index][2] = y_reduced_rows[row][3] + multiplier * y_pivot_row[3];
	}
	z_pivot = abs(z_reduced_rows[1][0]) > abs(z_reduced_rows[0][0]);
	if (abs(z_reduced_rows[z_pivot][0]) < k_real_epsilon)
	{
		return false;
	}
	z_pivot_row[0] = z_reduced_rows[z_pivot][0];
	z_pivot_row[1] = z_reduced_rows[z_pivot][1] / z_pivot_row[0];
	z_pivot_row[2] = z_reduced_rows[z_pivot][2] / z_pivot_row[0];
	{
		double multiplier = -z_reduced_rows[z_pivot == 0][0];
		final_row[0] = z_reduced_rows[z_pivot == 0][1] + multiplier * z_pivot_row[1];
		final_row[1] = z_reduced_rows[z_pivot == 0][2] + multiplier * z_pivot_row[2];
	}
	if (abs(final_row[0]) < k_real_epsilon)
	{
		return false;
	}
	x[3] = final_row[1] / final_row[0];
	x[2] = z_pivot_row[2] - z_pivot_row[1] * x[3];
	x[1] = y_pivot_row[3] - y_pivot_row[2] * x[3] - y_pivot_row[1] * x[2];
	x[0] = x_pivot_row[4] - x_pivot_row[3] * x[3] - x_pivot_row[2] * x[2] - x_pivot_row[1] * x[1];
	{
		double x_prime[4];
		real_vector4d solution_error;
		x_prime[0] = a[0][0] * x[0] + a[0][1] * x[1] + a[0][2] * x[2] + a[0][3] * x[3];
		x_prime[1] = a[1][0] * x[0] + a[1][1] * x[1] + a[1][2] * x[2] + a[1][3] * x[3];
		x_prime[2] = a[2][0] * x[0] + a[2][1] * x[1] + a[2][2] * x[2] + a[2][3] * x[3];
		x_prime[3] = a[3][0] * x[0] + a[3][1] * x[1] + a[3][2] * x[2] + a[3][3] * x[3];
		solution_error.i = static_cast<float>(x_prime[0] - b[0]);
		solution_error.j = static_cast<float>(x_prime[1] - b[1]);
		solution_error.k = static_cast<float>(x_prime[2] - b[2]);
		solution_error.l = static_cast<float>(x_prime[3] - b[3]);
		assert_tag_debug_untracked_jul_11_2011(2360, magnitude4d(&solution_error) < k_real_epsilon);
	}
	return true;
};

//void prefetch<struct real_matrix4x3>(struct real_matrix4x3const *)
//{
//    mangled_ppc("??$prefetch@Ureal_matrix4x3@@@@YAXPBUreal_matrix4x3@@@Z");
//};

//void XMVectorSinCos(struct __vector4*, struct __vector4*, struct __vector4)
//{
//    mangled_ppc("?XMVectorSinCos@@YAXPAU__vector4@@0U1@@Z");
//};
