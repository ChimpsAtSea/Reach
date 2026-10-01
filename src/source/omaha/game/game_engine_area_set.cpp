#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_area_set.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_area_set.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries.h"
#include "omaha\objects\objects.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_area::c_area(void);
// public: void c_area::get_center(union real_point3d *) const;
// public: float c_area::get_radius(void) const;
// public: float c_area::get_height(void) const;
// public: void c_area::calculate_boundary_geometry(void);
// public: bool c_area::player_inside(long) const;
// public: bool c_area::player_inside_radius(long, float) const;
// public: bool c_area::point_inside(union real_point3d const *) const;
// public: void c_area::render(void) const;
// public: void c_area::submit(void) const;
// bool area_set_compare_by_order_index(void const *, void const *, void const *);

c_area::c_area()
{
    mangled_ppc("??0c_area@@QAA@XZ");

    m_object_index = NONE;
    m_area_color = *global_real_argb_grey;
};

void c_area::get_center(real_point3d * area_center) const
{
    mangled_ppc("?get_center@c_area@@QBAXPATreal_point3d@@@Z");

    assert_tag_debug_untracked_jul_11_2011(30, area_center!=NULL);

    *area_center = m_boundary_data.boundary_transform.position;
};

float c_area::get_radius() const
{
    mangled_ppc("?get_radius@c_area@@QBAMXZ");

    return m_boundary_data.bounding_sphere_radius;
};

// $TODO nonmatching: target copies positive_height through a 4-byte aggregate temp (lwz/stw 0x54, lfs) before storing to height
float c_area::get_height() const
{
    mangled_ppc("?get_height@c_area@@QBAMXZ");

    float height = 0.0f;
    if (m_boundary_data.shape == _shape_cylinder || m_boundary_data.shape == _shape_box)
    {
        height = m_boundary_data.positive_height;
    }

    return height;
};

void c_area::calculate_boundary_geometry()
{
    mangled_ppc("?calculate_boundary_geometry@c_area@@QAAXXZ");

    if (m_object_index != NONE)
    {
        multiplayer_object_calculate_boundary_geometry(m_object_index, &m_boundary_data, false);
    }
};

bool c_area::player_inside(long player_index) const
{
    mangled_ppc("?player_inside@c_area@@QBA_NJ@Z");

    return player_in_multiplayer_object_boundary(player_index, &m_boundary_data);
};

bool c_area::player_inside_radius(long player_index, float radius) const
{
    mangled_ppc("?player_inside_radius@c_area@@QBA_NJM@Z");

    s_multiplayer_object_boundary_geometry_data boundary_data = m_boundary_data;
    boundary_data.width_or_radius = radius;
    boundary_data.bounding_sphere_radius = radius;
    if (boundary_data.shape == _shape_cylinder)
    {
        boundary_data.bounding_sphere_radius += MAX(boundary_data.positive_height, -boundary_data.negative_height);
    }

    return player_in_multiplayer_object_boundary(player_index, &boundary_data);
};

bool c_area::point_inside(real_point3d const * point) const
{
    mangled_ppc("?point_inside@c_area@@QBA_NPBTreal_point3d@@@Z");

    return point_in_multiplayer_object_boundary(point, &m_boundary_data);
};

void c_area::render() const
{
    mangled_ppc("?render@c_area@@QBAXXZ");
};

void c_area::submit() const
{
    mangled_ppc("?submit@c_area@@QBAXXZ");

    multiplayer_object_submit_boundary(&m_boundary_data, &m_area_color, m_object_index, NONE);
};

bool area_set_compare_by_order_index(void const * a, void const * b, void const * context)
{
    mangled_ppc("?area_set_compare_by_order_index@@YA_NPBX00@Z");

    long object_index_a = *static_cast<long const *>(a);
    long object_index_b = *static_cast<long const *>(b);
    object_datum const * object_a = static_cast<object_datum const *>(object_get_and_verify_type(object_index_a, NONE));
    object_datum const * object_b = static_cast<object_datum const *>(object_get_and_verify_type(object_index_b, NONE));
    s_multiplayer_object_properties const * properties_a = static_cast<s_multiplayer_object_properties const *>(object_header_block_get(object_index_a, &object_a->object.multiplayer));
    s_multiplayer_object_properties const * properties_b = static_cast<s_multiplayer_object_properties const *>(object_header_block_get(object_index_b, &object_b->object.multiplayer));

    long result = properties_a->spawn_order - properties_b->spawn_order;
    if (result == 0)
    {
        result = object_a->object.scenario_datum_index - object_b->object.scenario_datum_index;
    }
    if (result == 0)
    {
        result = object_a->object.map_variant_index - object_b->object.map_variant_index;
    }

    if (object_index_a != object_index_b && result == 0)
    {
        event_wrapped(_event_error, "c_area_set: objects %x and %x are indistinguishable", object_index_a, object_index_b);
    }

    return result > 0;
};

