#ifndef __VISIBILITY_COLLECTION_H__
#define __VISIBILITY_COLLECTION_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_visibility_region;

// $TODO: data layout not reversed (get_region reads a pointer at +0x14 and asserts "m_input!=NULL", visibility_collection.h line 95)
class c_visibility_collection
{
public:
    // f i (instance owned by old_render_debug.obj); declared only until the layout is known
    s_visibility_region const * get_region() const;
    bool get_bsp_portal_visible(long structure_bsp_index, long portal_index) const;
};

/* ---------- prototypes */

extern c_visibility_collection * get_global_camera_collection();

/* ---------- globals */

/* ---------- public code */

#endif // __VISIBILITY_COLLECTION_H__

