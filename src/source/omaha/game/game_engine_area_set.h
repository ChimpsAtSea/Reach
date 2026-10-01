#ifndef __GAME_ENGINE_AREA_SET_H__
#define __GAME_ENGINE_AREA_SET_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\color_math.h"
#include "omaha\objects\multiplayer_game_objects.h"

/* ---------- constants */

/* ---------- definitions */

class c_area
{
public:
    c_area();
    void get_center(real_point3d * area_center) const;
    float get_radius() const;
    float get_height() const;
    void calculate_boundary_geometry();
    bool player_inside(long player_index) const;
    bool player_inside_radius(long player_index, float radius) const;
    bool point_inside(real_point3d const * point) const;
    void render() const;
    void submit() const;

protected:
    s_multiplayer_object_boundary_geometry_data m_boundary_data; // 0x0
    argb_color m_area_color; // 0x50
    long m_object_index; // 0x60
};
static_assert(sizeof(c_area) == 0x64, "c_area");

/* ---------- prototypes */

extern bool area_set_compare_by_order_index(void const * a, void const * b, void const * context);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_AREA_SET_H__

