/* ---------- headers */

#include "omaha\structures\structure_physics_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\cseries\cseries.h"
#include "omaha\physics\havok_mopp_code_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real const k_soft_surface_maximum_sink_depths[k_soft_surface_sink_class_count] = { 0.0f, 0.2f, 0.09f, 0.2f, 0.04f, 0.0f };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **soft_ceiling_type_enum_strings; // "?soft_ceiling_type_enum_strings@@3PAPBDA"
// struct s_string_list_definition soft_ceiling_type_enum; // "?soft_ceiling_type_enum@@3Us_string_list_definition@@A"
// struct s_tag_struct_definition soft_surfaces_definition_block_struct_definition; // "?soft_surfaces_definition_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition soft_surfaces_definition_block; // "?soft_surfaces_definition_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_structure_physics_struct; // "?global_structure_physics_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition global_structure_physics_design_struct; // "?global_structure_physics_design_struct@@3Us_tag_struct_definition@@A"

// void structure_physics_fixup(struct s_structure_physics *);
// void structure_physics_design_fixup(struct s_structure_design_physics *);
// bool structure_water_instance_postprocess(long, void *, bool);
// bool load_old_structure_physics_v1(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *);
// bool soft_surfaces_definition_postprocess(long, void *, bool);
// bool structure_physics_postprocess(long, void *, bool);
// bool scenario_soft_ceilings_plane_from_triangle(struct plane3d *, union real_point3d const *, union real_point3d const *, union real_point3d const *);
// bool scenario_soft_ceiling_triangle_postprocess(struct s_structure_soft_ceiling_triangle *);
// bool structure_physics_design_postprocess(long, void *, bool);
// public: void s_structure_design_physics::clear(void);

void structure_physics_fixup(s_structure_physics * structure_physics)
{
    mangled_ppc("?structure_physics_fixup@@YAXPAUs_structure_physics@@@Z");

    havok_mopp_code_definitions_fixup(&structure_physics->mopp_code);
    havok_mopp_code_definitions_fixup(&structure_physics->breakable_surface_mopp_code);
};

void structure_physics_design_fixup(s_structure_design_physics * structure_physics_design)
{
    mangled_ppc("?structure_physics_design_fixup@@YAXPAUs_structure_design_physics@@@Z");

    havok_mopp_code_definitions_fixup(&structure_physics_design->soft_ceiling_mopp_code);
    havok_mopp_code_definitions_fixup(&structure_physics_design->water_mopp_code);
};

bool structure_water_instance_postprocess(long block_index, void * element, bool for_editor)
{
    mangled_ppc("?structure_water_instance_postprocess@@YA_NJPAX_N@Z");

    s_structure_physics_water_instance * water_instance = static_cast<s_structure_physics_water_instance *>(element);
    water_instance->bounds = *global_null_rectangle3d;
    for (long debug_triangle_index = 0; debug_triangle_index < water_instance->debug_triangles.count; debug_triangle_index++)
    {
        s_structure_physics_water_instance_debug_triangle * debug_triangle = static_cast<s_structure_physics_water_instance_debug_triangle *>(tag_block_get_element_with_size(&water_instance->debug_triangles, debug_triangle_index, sizeof(s_structure_physics_water_instance_debug_triangle)));
        for (long vertex_index = 0; vertex_index < 3; vertex_index++)
        {
            real_rectangle3d_enclose_point(&water_instance->bounds, &debug_triangle->vertices[vertex_index]);
        }
    }

    return true;
};

bool load_old_structure_physics_v1(unsigned long old_version, s_tag_field const * old_fields, long old_size, long old_count, void * old_data, s_tag_field const * new_fields, long new_size, long new_count, void * new_data)
{
    mangled_ppc("?load_old_structure_physics_v1@@YA_NKPBUs_tag_field@@JJPAX0JJ1@Z");

    s_structure_physics const * old_structure_physics = static_cast<s_structure_physics const *>(old_data);
    s_structure_physics * new_structure_physics = static_cast<s_structure_physics *>(new_data);
    memcpy(new_structure_physics, old_structure_physics, sizeof(s_structure_physics));
    tag_block_resize(&new_structure_physics->breakable_surface_mopp_code, 0);
    tag_block_resize(&new_structure_physics->mopp_code, 0);

    return true;
};

// $TODO nonmatching: only diff is that the target object has no relocation for the k_soft_surface_maximum_sink_depths table address (lis/subi), instruction bytes match
bool soft_surfaces_definition_postprocess(long block_index, void * element, bool for_editor)
{
    mangled_ppc("?soft_surfaces_definition_postprocess@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_soft_surfaces_definition * soft_surfaces_definition = static_cast<s_soft_surfaces_definition *>(element);
        for (long sink_class = 0; sink_class < k_soft_surface_sink_class_count; sink_class++)
        {
            soft_surfaces_definition->sink_depths[sink_class] = PIN(soft_surfaces_definition->sink_depths[sink_class], 0.0f, k_soft_surface_maximum_sink_depths[sink_class]);
        }
    }

    return true;
};

bool structure_physics_postprocess(long block_index, void * element, bool for_editor)
{
    mangled_ppc("?structure_physics_postprocess@@YA_NJPAX_N@Z");

    s_structure_physics * structure_physics = static_cast<s_structure_physics *>(element);
    havok_mopp_code_definitions_fixup(&structure_physics->mopp_code);
    havok_mopp_code_definitions_fixup(&structure_physics->breakable_surface_mopp_code);

    return true;
};

bool scenario_soft_ceilings_plane_from_triangle(plane3d * plane, real_point3d const * point0, real_point3d const * point1, real_point3d const * point2)
{
    mangled_ppc("?scenario_soft_ceilings_plane_from_triangle@@YA_NPAUplane3d@@PBTreal_point3d@@11@Z");

    vector3d edge0;
    vector3d edge1;
    bool result = false;
    vector_from_points3d(point0, point1, &edge0);
    vector_from_points3d(point0, point2, &edge1);
    cross_product3d(&edge0, &edge1, &plane->n);
    if (normalize3d(&plane->n) != 0.0f)
    {
        plane->d = dot_product3d(&plane->n, reinterpret_cast<vector3d const *>(point0));
        result = true;
    }

    return result;
};

bool scenario_soft_ceiling_triangle_postprocess(s_structure_soft_ceiling_triangle * triangle)
{
    mangled_ppc("?scenario_soft_ceiling_triangle_postprocess@@YA_NPAUs_structure_soft_ceiling_triangle@@@Z");

    real_point3d midpoint;
    real_point3d const * a = &triangle->vertices[0];
    real_point3d const * b = &triangle->vertices[1];
    real_point3d const * c = &triangle->vertices[2];
    real bounding_sphere_radius_squared = 0.0f;
    bool result = false;
    real distance;

    add_vectors3d(global_zero_vector3d, reinterpret_cast<vector3d const *>(a), reinterpret_cast<vector3d *>(&midpoint));
    add_vectors3d(reinterpret_cast<vector3d const *>(&midpoint), reinterpret_cast<vector3d const *>(b), reinterpret_cast<vector3d *>(&midpoint));
    add_vectors3d(reinterpret_cast<vector3d const *>(&midpoint), reinterpret_cast<vector3d const *>(c), reinterpret_cast<vector3d *>(&midpoint));
    scale_vector3d(reinterpret_cast<vector3d const *>(&midpoint), 1.0f / 3.0f, reinterpret_cast<vector3d *>(&midpoint));

    distance = distance_squared3d(&midpoint, a);
    bounding_sphere_radius_squared = MAX(bounding_sphere_radius_squared, distance);
    distance = distance_squared3d(&midpoint, b);
    bounding_sphere_radius_squared = MAX(bounding_sphere_radius_squared, distance);
    distance = distance_squared3d(&midpoint, c);
    bounding_sphere_radius_squared = MAX(bounding_sphere_radius_squared, distance);

    triangle->bounding_sphere_radius = square_root(bounding_sphere_radius_squared);
    triangle->bounding_sphere_center = midpoint;

    if (scenario_soft_ceilings_plane_from_triangle(&triangle->plane, a, b, c))
    {
        result = true;
    }
    else
    {
        triangle->plane.n = *global_zero_vector3d;
        triangle->plane.d = 0.0f;
        result = false;
    }

    return result;
};

bool structure_physics_design_postprocess(long block_index, void * element, bool for_editor)
{
    mangled_ppc("?structure_physics_design_postprocess@@YA_NJPAX_N@Z");

    s_structure_design_physics * structure_physics_design = static_cast<s_structure_design_physics *>(element);
    havok_mopp_code_definitions_fixup(&structure_physics_design->soft_ceiling_mopp_code);
    havok_mopp_code_definitions_fixup(&structure_physics_design->water_mopp_code);
    if (structure_physics_design->import_version < k_structure_design_importer_version)
    {
        for (long soft_ceiling_index = 0; soft_ceiling_index < structure_physics_design->soft_ceiling_block.count; soft_ceiling_index++)
        {
            s_structure_soft_ceiling * soft_ceiling = static_cast<s_structure_soft_ceiling *>(tag_block_get_element_with_size(&structure_physics_design->soft_ceiling_block, soft_ceiling_index, sizeof(s_structure_soft_ceiling)));
            for (long triangle_index = 0; triangle_index < soft_ceiling->triangles.count; triangle_index++)
            {
                s_structure_soft_ceiling_triangle * triangle = static_cast<s_structure_soft_ceiling_triangle *>(tag_block_get_element_with_size(&soft_ceiling->triangles, triangle_index, sizeof(s_structure_soft_ceiling_triangle)));
                scenario_soft_ceiling_triangle_postprocess(triangle);
            }
        }
    }

    return true;
};

void s_structure_design_physics::clear()
{
    mangled_ppc("?clear@s_structure_design_physics@@QAAXXZ");

    import_version = NONE;
    tag_block_resize(&soft_ceiling_mopp_code, 0);
    tag_block_resize(&soft_ceiling_block, 0);
    tag_block_resize(&water_mopp_code, 0);
    tag_block_resize(&water_groups_block, 0);
    tag_block_resize(&water_instances_block, 0);
};

