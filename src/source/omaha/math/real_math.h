#pragma once
#ifndef __REAL_MATH_H__
#define __REAL_MATH_H__

/* ---------- headers */

/* ---------- constants */

#ifndef __FLT_EPSILON__
#define __FLT_EPSILON__ 1.192092896e-07f // 0x34000000
#endif
#ifndef __FLT_MAX__
#define __FLT_MAX__ 3.402823466e+38f // 0x7F7FFFFF
#endif
#ifndef __FLT_MIN__
#define __FLT_MIN__ 1.175494351e-38f // 0x00800000
#endif

const float k_degrees_to_radians = 0.0174533f;
const float k_radians_to_degrees = 57.2957802f;
const float k_real_precision = __FLT_EPSILON__;
const float k_pi = 3.1415927f;
const float k_2pi = 6.2831855f;
const float k_3pi = 9.424778f;
const float k_half_pi = 1.5707964f;
const float k_quarter_pi = 0.7853982f;
const float k_one_over_root2 = 0.7071068f;
const float k_cosine30 = 0.8660254f;
const float k_sine30 = 0.5f;
const float k_cosine45 = 0.7071068f;
const float k_sine45 = 0.7071068f;
const float k_cosine60 = 0.5f;
const float k_sine60 = 0.8660254f;
const float k_full_circle = 6.2831855f;
const float k_half_circle = 3.1415927f;
const float k_quarter_circle = 1.5707964f;
const float k_eighth_circle = 0.7853982f;
const float k_real_epsilon = 0.0001f;
const float k_valid_real_epsilon = 0.001f;
const float k_double_epsilon = 0.000001f;
const float k_root_5 = 2.236068f;
const float k_golden_ratio = 1.618034f;
const float k_one_over_golden_ratio = 0.618034f;
const float k_real_min = -__FLT_MAX__;
const float k_real_max = __FLT_MAX__;
const float REAL_MIN = -__FLT_MAX__;
const float REAL_MAX = __FLT_MAX__;

#define realcmp(a, b) (fabs((a) - (b)) < k_real_epsilon)

/* ---------- definitions */

typedef float real;

union euler_angles2d
{
	real n[2];
	struct {
		real yaw;
		real pitch;
	};
};

union euler_angles3d
{
	real n[3];
	struct {
		real yaw;
		real pitch;
		real roll;
	};
};

union real_point2d
{
	real n[2];
	struct {
		real x;
		real y;
	};
	struct {
		real u;
		real v;
	};
};

union real_point3d
{
	real n[3];
	struct {
		real x;
		real y;
		real z;
	};
	struct {
		real u;
		real v;
		real w;
	};
};

union vector2d
{
	real n[2];
	struct {
		real i;
		real j;
	};
};

union vector3d
{
	real n[3];
	struct {
		real i;
		real j;
		real k;
	};
};

union vector4d
{
	real n[4];
	struct {
		real i;
		real j;
		real k;
		real l;
	};
};

struct real32_quaternion
{
	vector3d v;
	real w;
};

struct real_orientation
{
	real32_quaternion rotation;
	real_point3d translation;
	real scale;
};

struct matrix3x3
{
	union {
		real n[3][3];
		vector3d basis[3];
		struct {
			vector3d forward;
			vector3d left;
			vector3d up;
		};
	};
};

struct real_matrix4x3
{
	real scale;
	union {
		real n[4][3];
		matrix3x3 matrix3x3;
		struct {
			vector3d basis[3];
			real_point3d origin;
		};
		struct {
			vector3d forward;
			vector3d left;
			vector3d up;
			real_point3d position;
		};
	};
};

struct plane2d
{
	vector2d n;
	real d;
};

struct plane3d
{
	vector3d n;
	real d;
};

union real_rectangle2d
{
	real n[4];
	real m[2][2];
	struct
	{
		real x0;
		real x1;
		real y0;
		real y1;
	};
};

union real_rectangle3d
{
	real n[6];
	real m[3][2];
	struct
	{
		real x0;
		real x1;
		real y0;
		real y1;
		real z0;
		real z1;
	};
};

typedef euler_angles2d real_euler_angles2d; // $todo compat
typedef euler_angles3d real_euler_angles3d; // $todo compat
typedef vector2d real_vector2d; // $todo compat
typedef vector3d real_vector3d; // $todo compat
typedef vector4d real_vector4d; // $todo compat
typedef real32_quaternion real_quaternion; // $todo compat
typedef matrix3x3 real_matrix3x3; // $todo compat
typedef plane2d real_plane2d;
typedef plane3d real_plane3d;

/* ---------- prototypes */

/* ---------- globals */

extern short const global_projection3d_mappings[2][3];
extern short const global_projection3d_inverse_mappings[2][3];
extern bool g_enable_new_ik_method;
extern real_point2d const * global_origin2d;
extern real_point2d const * global_x_axis2d;
extern real_point2d const * global_y_axis2d;
extern real_point2d const * global_negative_x_axis2d;
extern real_point2d const * global_negative_y_axis2d;
extern vector2d const * global_zero_vector2d;
extern vector2d const * global_forward2d;
extern vector2d const * global_left2d;
extern vector2d const * global_backward2d;
extern vector2d const * global_right2d;
extern real_point3d const * global_origin3d;
extern real_point3d const * global_x_axis3d;
extern real_point3d const * global_y_axis3d;
extern real_point3d const * global_z_axis3d;
extern real_point3d const * global_negative_x_axis3d;
extern real_point3d const * global_negative_y_axis3d;
extern real_point3d const * global_negative_z_axis3d;
extern vector3d const * global_zero_vector3d;
extern vector3d const * global_forward3d;
extern vector3d const * global_left3d;
extern vector3d const * global_up3d;
extern vector3d const * global_backward3d;
extern vector3d const * global_right3d;
extern vector3d const * global_down3d;
extern vector4d const * global_zero_vector4d;
extern euler_angles2d const * global_zero_angles2d;
extern euler_angles3d const * global_zero_angles3d;
extern real32_quaternion const * global_identity_quaternion;
extern matrix3x3 const * global_identity3x3;
extern real_matrix4x3 const * global_identity4x3;
extern real_matrix4x3 const * global_negative_identity4x3;
extern real_orientation const * global_identity_orientation;
extern real_rectangle2d const * global_null_rectangle2d;
extern real_rectangle3d const * global_null_rectangle3d;
extern real_rectangle2d const * global_zero_rectangle2d;
extern real_rectangle3d const * global_zero_rectangle3d;
extern float max_vmx_error;

/* ---------- public code */

#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define __min(a,b) (((a) < (b)) ? (a) : (b))

extern inline vector2d * vector_from_points2d(real_point2d const * a, real_point2d const * b, vector2d * result);
//inline vector2d * vector_from_points2d(real_point2d const * a, real_point2d const * b, vector2d * result)
//{
//    mangled_ppc("?vector_from_points2d@@YAPATvector2d@@PBTreal_point2d@@0PAT1@@Z");
//};

extern inline vector2d * add_vectors2d(vector2d const * v1, vector2d const * v2, vector2d * result);
//inline vector2d * add_vectors2d(vector2d const * v1, vector2d const * v2, vector2d * result)
//{
//    mangled_ppc("?add_vectors2d@@YAPATvector2d@@PBT1@0PAT1@@Z");
//};

extern inline vector2d * scale_vector2d(vector2d const * v, float c, vector2d * result);
//inline vector2d * scale_vector2d(vector2d const * v, float c, vector2d * result)
//{
//    mangled_ppc("?scale_vector2d@@YAPATvector2d@@PBT1@MPAT1@@Z");
//};

extern inline float magnitude2d(vector2d const * v);
//inline float magnitude2d(vector2d const * v)
//{
//    mangled_ppc("?magnitude2d@@YAMPBTvector2d@@@Z");
//};

extern inline float normalize2d(vector2d * v);
//inline float normalize2d(vector2d * v)
//{
//    mangled_ppc("?normalize2d@@YAMPATvector2d@@@Z");
//};

extern inline float distance2d(real_point2d const * a, real_point2d const * b);
//inline float distance2d(real_point2d const * a, real_point2d const * b)
//{
//    mangled_ppc("?distance2d@@YAMPBTreal_point2d@@0@Z");
//};

extern inline float distance_squared2d(real_point2d const * a, real_point2d const * b);
//inline float distance_squared2d(real_point2d const * a, real_point2d const * b)
//{
//    mangled_ppc("?distance_squared2d@@YAMPBTreal_point2d@@0@Z");
//};

extern inline float magnitude_squared2d(vector2d const * v);
//inline float magnitude_squared2d(vector2d const * v)
//{
//    mangled_ppc("?magnitude_squared2d@@YAMPBTvector2d@@@Z");
//};

extern inline float dot_product2d(vector2d const * a, vector2d const * b);
//inline float dot_product2d(vector2d const * a, vector2d const * b)
//{
//    mangled_ppc("?dot_product2d@@YAMPBTvector2d@@0@Z");
//};

extern inline real_point2d * set_real_point2d(real_point2d * p, float x, float y);
//inline real_point2d * set_real_point2d(real_point2d * p, float x, float y)
//{
//    mangled_ppc("?set_real_point2d@@YAPATreal_point2d@@PAT1@MM@Z");
//};

extern inline real_point2d * point_from_line2d(real_point2d const * p, vector2d const * v, float t, real_point2d * result);
//inline real_point2d * point_from_line2d(real_point2d const * p, vector2d const * v, float t, real_point2d * result)
//{
//    mangled_ppc("?point_from_line2d@@YAPATreal_point2d@@PBT1@PBTvector2d@@MPAT1@@Z");
//};

extern inline real_point2d * midpoint2d(real_point2d const * p0, real_point2d const * p1, real_point2d * result);
//inline real_point2d * midpoint2d(real_point2d const * p0, real_point2d const * p1, real_point2d * result)
//{
//    mangled_ppc("?midpoint2d@@YAPATreal_point2d@@PBT1@0PAT1@@Z");
//};

extern inline real_point3d * project_point2d(real_point2d const * p2d, plane3d const * plane, short projection, bool sign, real_point3d * p3d);
//inline real_point3d * project_point2d(real_point2d const * p2d, plane3d const * plane, short projection, bool sign, real_point3d * p3d)
//{
//    mangled_ppc("?project_point2d@@YAPATreal_point3d@@PBTreal_point2d@@PBUplane3d@@F_NPAT1@@Z");
//};

extern inline real_point3d * midpoint3d(real_point3d const * p0, real_point3d const * p1, real_point3d * result);
//inline real_point3d * midpoint3d(real_point3d const * p0, real_point3d const * p1, real_point3d * result)
//{
//    mangled_ppc("?midpoint3d@@YAPATreal_point3d@@PBT1@0PAT1@@Z");
//};

extern inline float plane3d_distance_to_point(plane3d const * plane, real_point3d const * point);
//inline float plane3d_distance_to_point(plane3d const * plane, real_point3d const * point)
//{
//    mangled_ppc("?plane3d_distance_to_point@@YAMPBUplane3d@@PBTreal_point3d@@@Z");
//};

extern inline real_point3d * rectangle3d_center(real_rectangle3d const * bounds, real_point3d * center);
//inline real_point3d * rectangle3d_center(real_rectangle3d const * bounds, real_point3d * center)
//{
//    mangled_ppc("?rectangle3d_center@@YAPATreal_point3d@@PBTreal_rectangle3d@@PAT1@@Z");
//};

extern inline float square_root(float x);
//inline  float square_root(float x)
//{
//    mangled_ppc("?square_root@@YAMM@Z");
//};

extern inline float dot_product3d(vector3d const * a, vector3d const * b);
//inline float dot_product3d(vector3d const * a, vector3d const * b)
//{
//    mangled_ppc("?dot_product3d@@YAMPBTvector3d@@0@Z");
//};

extern inline bool valid_realcmp(float x, float y);
//inline bool valid_realcmp(float x, float y)
//{
//    mangled_ppc("?valid_realcmp@@YA_NMM@Z");
//};

extern inline bool valid_real_point3d(real_point3d const * p);
//inline bool valid_real_point3d(real_point3d const * p)
//{
//    mangled_ppc("?valid_real_point3d@@YA_NPBTreal_point3d@@@Z");
//};

extern inline  bool valid_real_normal3d(vector3d const * n);
//inline  bool valid_real_normal3d(vector3d const * n)
//{
//    mangled_ppc("?valid_real_normal3d@@YA_NPBTvector3d@@@Z");
//};

extern inline float magnitude_squared3d(vector3d const * v);
//inline float magnitude_squared3d(vector3d const * v)
//{
//    mangled_ppc("?magnitude_squared3d@@YAMPBTvector3d@@@Z");
//};

extern inline bool valid_real_matrix4x3(real_matrix4x3 const * m);
//inline bool valid_real_matrix4x3(real_matrix4x3const * m)
//{
//    mangled_ppc("?valid_real_matrix4x3@@YA_NPBUreal_matrix4x3@@@Z");
//};

extern inline bool valid_real_vector3d_axes3(vector3d const * f, vector3d const * l, vector3d const * u);
//inline bool valid_real_vector3d_axes3(vector3d const * f, vector3d const * l, vector3d const * u)
//{
//    mangled_ppc("?valid_real_vector3d_axes3@@YA_NPBTvector3d@@00@Z");
//};

extern float cross_product2d(vector2d const * a, vector2d const * b);
//float cross_product2d(vector2d const * a, vector2d const * b)
//{
//    mangled_ppc("?cross_product2d@@YAMPBTvector2d@@0@Z");
//
//	return a->i * b->j - a->j * b->i;
//};

extern float magnitude_squared4d(union vector4d const * v);
extern float magnitude4d(union vector4d const * v);

extern double abs(double d);
/*double abs(double d)
{
    mangled_ppc("?abs@@YANN@Z");

	return fabs(d);
};*/

//float tangent(float)
//{
//    mangled_ppc("?tangent@@YAMM@Z");
//};

//union vector3d * set_real_vector3d(union vector3d *, float, float, float)
//{
//    mangled_ppc("?set_real_vector3d@@YAPATvector3d@@PAT1@MMM@Z");
//};

//union real_point3d * point_from_line3d(union real_point3d const *, union vector3d const *, float, union real_point3d *)
//{
//    mangled_ppc("?point_from_line3d@@YAPATreal_point3d@@PBT1@PBTvector3d@@MPAT1@@Z");
//};

//union vector3d * scale_vector3d(union vector3d const *, float, union vector3d *)
//{
//    mangled_ppc("?scale_vector3d@@YAPATvector3d@@PBT1@MPAT1@@Z");
//};

//float normalize3d(union vector3d *)
//{
//    mangled_ppc("?normalize3d@@YAMPATvector3d@@@Z");
//};

extern float magnitude3d(union vector3d const *);
//float magnitude3d(union vector3d const *)
//{
//    mangled_ppc("?magnitude3d@@YAMPBTvector3d@@@Z");
//};

//float distance3d(union real_point3d const *, union real_point3d const *)
//{
//    mangled_ppc("?distance3d@@YAMPBTreal_point3d@@0@Z");
//};

//union vector3d * cross_product3d(union vector3d const *, union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?cross_product3d@@YAPATvector3d@@PBT1@0PAT1@@Z");
//};

//union vector3d * negate_vector3d(union vector3d const *, union vector3d *)
//{
//    mangled_ppc("?negate_vector3d@@YAPATvector3d@@PBT1@PAT1@@Z");
//};

#endif // __REAL_MATH_H__
