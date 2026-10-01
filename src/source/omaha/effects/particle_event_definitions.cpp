#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\particle_event_definitions.cpp"
/* ---------- headers */

#include "omaha\effects\particle_event_definitions.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_particle_collision_event::initialize(union real_point3d const *, union vector3d const *, union vector3d const *, class c_global_material_type);

void c_particle_collision_event::initialize(real_point3d const * position, vector3d const * direction, vector3d const * normal, c_global_material_type material_type)
{
    mangled_ppc("?initialize@c_particle_collision_event@@QAAXPBTreal_point3d@@PBTvector3d@@1Vc_global_material_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(208, position != NULL);
    assert_tag_debug_untracked_jul_11_2011(209, direction != NULL);
    assert_tag_debug_untracked_jul_11_2011(210, normal != NULL);

    vector3d forward = *direction;
    normalize3d_with_default(&forward, global_down3d);

    m_material_type = material_type;
    m_collision_point = *position;
    m_collision_forward = forward;
    m_collision_normal = *normal;
};

