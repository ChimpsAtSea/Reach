#pragma once
#ifndef __RASTERIZER_TEXTURES_H__
#define __RASTERIZER_TEXTURES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_rasterizer_texture_ref
{
public:
    // f i (instances owned by rasterizer_main.obj / rasterizer_surfaces.obj / rasterizer_render_targets.obj); bodies per IDA
    c_rasterizer_texture_ref()
    {
        mangled_ppc("??0c_rasterizer_texture_ref@@QAA@XZ");

        m_datum_ref = -1;
    };

    c_rasterizer_texture_ref(c_rasterizer_texture_ref const & other)
    {
        mangled_ppc("??0c_rasterizer_texture_ref@@QAA@ABV0@@Z");

        m_datum_ref = other.m_datum_ref;
    };

    c_rasterizer_texture_ref & operator=(c_rasterizer_texture_ref other)
    {
        mangled_ppc("??4c_rasterizer_texture_ref@@QAAAAV0@V0@@Z");

        m_datum_ref = other.m_datum_ref;
        return *this;
    };

private:
    long m_datum_ref; // 0x0
};
static_assert(sizeof(c_rasterizer_texture_ref) == 0x4, "c_rasterizer_texture_ref");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_TEXTURES_H__

