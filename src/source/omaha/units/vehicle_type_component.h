#pragma once
#ifndef __VEHICLE_TYPE_COMPONENT_H__
#define __VEHICLE_TYPE_COMPONENT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct real_matrix4x3;

// $TODO members not reversed (H3: m_vehicle_type_buffer, m_initialization_type)
class c_vehicle_type_component
{
public:
    void get_trick_desired_transform(long vehicle_index, real_matrix4x3 * transform) const;
    long get_trick_ticks_left(long vehicle_index) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __VEHICLE_TYPE_COMPONENT_H__

