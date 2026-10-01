#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\particle_model_definitions.cpp"
/* ---------- headers */

#include "omaha\effects\particle_model_definitions.h"
#include "omaha\geometry\geometry_definitions.h"
#include "omaha\rasterizer\rasterizer_shaders.h"
#include "omaha\render\render_mesh.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include <math.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

e_vertex_buffer_usage const c_particle_model_definition::x_vertex_buffer_usage = _vertex_buffer_usage_standard;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static enum e_vertex_buffer_usage const c_particle_model_definition::x_vertex_buffer_usage; // "?x_vertex_buffer_usage@c_particle_model_definition@@2W4e_vertex_buffer_usage@@B"
// struct s_tag_block_definition particle_model_block; // "?particle_model_block@@3Us_tag_block_definition@@A"
// struct s_tag_group particle_model_group; // "?particle_model_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_particle_model_vtable; // "?legacy_particle_model_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_particle_model_stream_definition; // "?legacy_particle_model_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_particle_model_xsync_declaration; // "?legacy_particle_model_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_particle_model_vtable_shim; // "?legacy_particle_model_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: bool c_particle_model_definition::get_has_mesh(void) const;
// public: float c_particle_model_definition::get_bounding_radius(void) const;
// public: void c_particle_model_definition::set_vertex_stream(void) const;

bool c_particle_model_definition::get_has_mesh(void) const
{
    mangled_ppc("?get_has_mesh@c_particle_model_definition@@QBA_NXZ");

    s_mesh const * mesh = static_cast<s_mesh const *>(tag_block_get_element_with_size(&m_render_geometry.meshes, 0, sizeof(s_mesh)));
    if (mesh)
    {
        unsigned short vertex_buffer_index = mesh->vertex_buffer_indices[x_vertex_buffer_usage];
        if (vertex_buffer_index != 0xFFFF)
        {
            return true;
        }
    }

    event_wrapped(_event_error, "effects:particles:Particle model tag contains no imported mesh!");
    return false;
};

float c_particle_model_definition::get_bounding_radius(void) const
{
    mangled_ppc("?get_bounding_radius@c_particle_model_definition@@QBAMXZ");

    s_compression_info const * compression_info = static_cast<s_compression_info const *>(tag_block_get_element_with_size(&m_render_geometry.compression_infos, 0, sizeof(s_compression_info)));
    float bounding_radius = 0.0f;
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.x0));
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.x1));
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.y0));
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.y1));
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.z0));
    bounding_radius = MAX(bounding_radius, fabsf(compression_info->position_bounds.z1));

    return bounding_radius;
};

void c_particle_model_definition::set_vertex_stream(void) const
{
    mangled_ppc("?set_vertex_stream@c_particle_model_definition@@QBAXXZ");

    s_mesh const * mesh = static_cast<s_mesh const *>(tag_block_get_element_with_size(&m_render_geometry.meshes, 0, sizeof(s_mesh)));
    assert_tag_debug_untracked_jul_11_2011(110, mesh);

    c_rasterizer_vertex_buffer const * vertex_buffer = mesh_get_vertex_buffer(&m_render_geometry, mesh, x_vertex_buffer_usage);
    assert_tag_debug_untracked_jul_11_2011(112, vertex_buffer);

    c_rasterizer_shaders::set_vertex_stream(vertex_buffer);

    s_compression_info const * compression_info = static_cast<s_compression_info const *>(tag_block_get_element_with_size(&m_render_geometry.compression_infos, 0, sizeof(s_compression_info)));
    render_mesh_submit_compression(compression_info);
};

