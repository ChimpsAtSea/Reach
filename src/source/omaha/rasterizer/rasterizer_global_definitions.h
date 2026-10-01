#ifndef __RASTERIZER_GLOBAL_DEFINITIONS_H__
#define __RASTERIZER_GLOBAL_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\bitmaps\bitmap_group.h"
#include "omaha\cseries\cseries.h"
#include "omaha\rasterizer\rasterizer_textures.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    RASTERIZER_GLOBALS_GROUP_TAG = 'rasg',
};

/* ---------- definitions */

// layout not reversed yet; only used through pointers
class c_rasterizer_globals
{
public:
    s_tag_reference const * get_default_texture_ref(long default_texture) const;

    // f i (instance owned by screen_postprocess_xenon.obj); body per IDA, codegen unverified
    c_rasterizer_texture_ref const get_default_texture_rasterizer_texture_ref(long default_texture) const
    {
        mangled_ppc("?get_default_texture_rasterizer_texture_ref@c_rasterizer_globals@@QBA?BVc_rasterizer_texture_ref@@J@Z");

        s_tag_reference const * default_texture_ref = get_default_texture_ref(default_texture);
        dassert_decomp(default_texture_ref->index != NONE, "undefined default bitmap in rasterizer_globals", "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\rasterizer\\rasterizer_global_definitions.h", 411);

        c_rasterizer_texture_ref texture_ref;
        bool has_hardware_texture = bitmap_group_get_bitmap_hardware_format(default_texture_ref->index, 0, &texture_ref);
        dassert_decomp(has_hardware_texture, "default bitmap does not have a hardware texture!", "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\rasterizer\\rasterizer_global_definitions.h", 417);

        return texture_ref;
    };
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __RASTERIZER_GLOBAL_DEFINITIONS_H__

