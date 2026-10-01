#pragma once
#ifndef __PARTICLE_MODEL_DEFINITIONS_H__
#define __PARTICLE_MODEL_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\geometry\geometry_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_particle_model_definition
{
public:
    enum
    {
        k_tag_type = 'pmdf',
    };

    struct s_gpu_data
    {
        s_tag_block m_variants; // 0x0
    };

    static e_vertex_buffer_usage const x_vertex_buffer_usage;

    bool get_has_mesh(void) const;
    float get_bounding_radius(void) const;
    void set_vertex_stream(void) const;

private:
    s_render_geometry m_render_geometry; // 0x0
    s_gpu_data m_gpu_data; // 0x9C
};
static_assert(sizeof(c_particle_model_definition) == 0xA8, "c_particle_model_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __PARTICLE_MODEL_DEFINITIONS_H__

