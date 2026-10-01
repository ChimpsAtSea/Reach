#pragma once
#ifndef __VISIBILITY_COLLECTION_RENDER_H__
#define __VISIBILITY_COLLECTION_RENDER_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct structure_bsp;
struct s_visibility_region;

class c_visibility_collection_render
{
public:
    static void render_structure_cluster_portal(structure_bsp const * structure_bsp, short portal_index, float alpha);
    static void render_region_cluster_portals(long region_cluster_index, float alpha, bool only_visible_portals);
    static void render_visible_portals();
    static void render_debug_visibility_region(s_visibility_region const * region);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __VISIBILITY_COLLECTION_RENDER_H__

