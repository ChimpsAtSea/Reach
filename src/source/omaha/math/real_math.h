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

const float k_degrees_to_radians = 0.017453292f;
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
// k_cosine60 / k_sine60 are NOT defined here either: in the target they are dynamically initialized statics
// (??__Ek_cosine60 / ??__Ek_sine60) owned only by the TUs that use them; define them in the using .cpp as
//     static real k_cosine60 = k_sine30;
//     static real k_sine60 = k_cosine30;
// (camera_obstruction.cpp)
// k_full_circle / k_half_circle / k_quarter_circle / k_eighth_circle are NOT defined here: in the target only the TUs that use them own a
// ??__Ek_half_circle / ??__Ek_quarter_circle dynamic initializer (this cl emits the initializer even for an
// unreferenced header static), so define them in the using .cpp as
//     static real k_half_circle = k_pi;
//     static real k_quarter_circle = k_half_pi;
//     static real k_full_circle = k_2pi;
//     static real k_eighth_circle = k_quarter_pi;
// (verified in character_physics_utilities.cpp)
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
#define _realcmp(a, b, epsilon) (fabs((a) - (b)) < (epsilon))

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

union real_bounds
{
	real n[2];
	struct
	{
		real lower;
		real upper;
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

real real_sgn(real x);
real real_pin(real value, real min_value, real max_value);
real arcsine(real x);
void real_math_test();
real real_max(real a, real b); // $TODO inline in the target (f i, rasterizer_text.obj); body not reversed yet
real real_min(real a, real b); // $TODO inline in the target (f i, rasterizer_text.obj); branchless fsel on a-b vs 0.0 (+/-1 table __real@3f800000bf800000), body not reversed yet
vector4d * set_real_vector4d(vector4d * v, real i, real j, real k, real l); // $TODO inline in the target (f i, rasterizer_main.obj)
void real_vector3d_build_axes_from_vectors(vector3d const * forward_vector, vector3d const * up_vector, vector3d * out_forward, vector3d * out_left, vector3d * out_up);
real cosine(real x); // $TODO inline in the target (f i, rasterizer_text.obj); body not reversed yet
real sine(real x); // $TODO body not reversed yet
real arctangent(real y, real x); // $TODO inline in the target (f i, render_lens_flares.obj); body not reversed yet
vector3d * fast_normalize3d(vector3d * v); // $TODO inline in the target (f i, real_math.obj); body not reversed yet
bool point_in_sphere(real_point3d const * point, real_point3d const * center, real radius); // $TODO inline in the target (f i, old_render_debug.obj); body not reversed yet
plane3d * plane3d_from_point_and_normal(plane3d * plane, real_point3d const * point, vector3d const * normal); // $TODO inline in the target (f i, render_player_view.obj); body not reversed yet
real point_to_line_distance3d(real_point3d const * point, real_point3d const * line_point, vector3d const * line_vector); // $TODO inline in the target (f i, render_debug_structure.obj); body not reversed yet
real point_to_line_distance_squared3d(real_point3d const * point, real_point3d const * line_point, vector3d const * line_vector, real * out_t);
bool fast_vector_intersects_sphere(real_point3d const * point, vector3d const * vector, real_point3d const * center, real radius);
bool point_in_cone3d(real_point3d const * point, real_point3d const * cone_point, vector3d const * cone_axis, real cone_length, real cosine_angle);
real plane2d_distance_to_point(plane2d const * plane, real_point2d const * point);
void real_vector3d_build_axes_from_forward(vector3d const * forward, vector3d * left, vector3d * up);
vector3d * rotate_vector_about_axis(vector3d * vector, vector3d const * axis, real sine_angle, real cosine_angle);

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

extern inline float interpolate_linear(float a, float b, float t); // $TODO inline in the target (f i, old_render_debug.obj); body not reversed yet
extern inline float ease_in_ease_out(float t); // $TODO inline in the target (f i, game_sound.obj); body not reversed yet
extern inline float ease_in_ease_out_heavy(float t); // $TODO inline in the target (f i, vehicle_type_wolverine.obj); body not reversed yet

extern void orientations_interpolate(real_orientation const * a, real_orientation const * b, float t, real_orientation * result);
extern void approximate_orientations_interpolate(real_orientation const * a, real_orientation const * b, float t, real_orientation * result);

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

extern inline bool valid_real(float const & value); // "?valid_real@@YA_NABM@Z" (f i, body not reversed)

extern inline bool valid_realcmp(float x, float y);
//inline bool valid_realcmp(float x, float y)
//{
//    mangled_ppc("?valid_realcmp@@YA_NMM@Z");
//};

bool valid_real_quaternion(real32_quaternion const * q); // real_math.cpp

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

extern inline float power(float base, float exponent); // f i, weapons.obj
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

extern inline bool valid_real_vector3d_axes2(vector3d const * forward, vector3d const * up); // $TODO inline in the target (f i, render_view.obj); body not reversed yet

// needs foundation\baselib\datatypes\static_string.h (c_string_builder) and cseries_asserts.h at the use site
// (verified in character_physics_utilities.cpp)
#define assert_valid_real_vector3d_axes2(LINE, forward, up) if(!valid_real_vector3d_axes2(forward, up) && !assert_handle(c_string_builder("%s, %s: assert_valid_real_vector3d_axes2(%f, %f, %f / %f, %f, %f)", #forward, #up, (forward)->i, (forward)->j, (forward)->k, (up)->i, (up)->j, (up)->k), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
// same requirements as assert_valid_real_vector3d_axes2 (verified in character_physics_mode_flying.cpp)
#define assert_valid_real_normal3d(LINE, n) if(!valid_real_normal3d(n) && !assert_handle(c_string_builder("%s: assert_valid_real_normal3d(%f, %f, %f)", #n, (n)->i, (n)->j, (n)->k), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }

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

extern real_point3d * point_from_line3d(real_point3d const * p, vector3d const * v, real t, real_point3d * result);
extern vector3d * subtract_vectors3d(vector3d const * a, vector3d const * b, vector3d * result);
extern inline vector3d * vector_from_points3d(real_point3d const * a, real_point3d const * b, vector3d * result); // $TODO inline in the target (f i, render_view.obj); body not reversed yet
extern inline vector3d * cross_product3d(vector3d const * a, vector3d const * b, vector3d * result); // $TODO inline in the target (f i, render_lights.obj); body not reversed yet
extern real normalize3d_with_default(vector3d * v, vector3d const * default_vector);
extern void quaternion_from_unit_vectors(real32_quaternion * q, vector3d const * u, vector3d const * v);
extern vector3d * generate_up_vector3d(vector3d const * forward, vector3d * up);
extern void points_interpolate(real_point3d const * previous_point, real_point3d const * next_point, real fraction, real_point3d * result);
extern vector3d * scale_vector3d(vector3d const * a, real c, vector3d * result);
extern inline vector3d * add_vectors3d(vector3d const * a, vector3d const * b, vector3d * result); // $TODO inline in the target (f i); body not reversed yet
extern inline real arccosine(real x); // $TODO inline in the target (f i); body not reversed yet
extern inline real real_map_linear_intervals(real source_min, real source_max, real target_min, real target_max, real value); // $TODO inline in the target (f i); body not reversed yet
extern inline real distance_squared3d(real_point3d const * a, real_point3d const * b); // $TODO inline in the target (f i, render_view.obj); body not reversed yet
extern inline real_rectangle3d * real_rectangle3d_enclose_point(real_rectangle3d * bounds, real_point3d const * point); // $TODO inline in the target (f i, old_render_debug.obj); body not reversed yet
//union vector3d * scale_vector3d(union vector3d const *, float, union vector3d *)
//{
//    mangled_ppc("?scale_vector3d@@YAPATvector3d@@PBT1@MPAT1@@Z");
//};

extern inline float normalize3d(vector3d * v);
//float normalize3d(union vector3d *)
//{
//    mangled_ppc("?normalize3d@@YAMPATvector3d@@@Z");
//};

extern float magnitude3d(union vector3d const *);
extern inline vector3d * negate_vector3d(vector3d const * v, vector3d * result); // $TODO inline in the target (f i, render_lights.obj); body not reversed yet
extern inline vector3d * set_real_vector3d(vector3d * v, real i, real j, real k); // $TODO inline in the target (f i, render_lights.obj); body not reversed yet
extern inline vector3d * multiply_vectors3d(vector3d const * a, vector3d const * b, vector3d * result); // $TODO inline in the target (f i, vehicle_type_human_plane.obj); body not reversed yet
extern bool accelerate_to_position(real * position, real * velocity, real desired_position, real dt, real maximum_acceleration, real maximum_velocity, real minimum_position, real maximum_position, bool circular_position); // real_math.obj
extern void update_spring_system(real * position, real * velocity, real desired_position, real spring_constant, real damping_constant, real dt); // real_math.obj
extern void angular_accelerate_to_position(vector3d * position, vector3d const * desired_position, real dt, vector3d * angular_velocity, real maximum_angular_velocity, real maximum_angular_acceleration, bool unknown); // real_math.obj
extern vector3d * vector3d_from_euler_angles2d(vector3d * v, euler_angles2d const * angles);
extern euler_angles2d * euler_angles2d_from_vector3d(euler_angles2d * angles, vector3d const * v);
extern vector3d * vector3d_from_angle(vector3d * v, real angle);
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
