#pragma once
#ifndef __GROUNDED_FRICTION_H__
#define __GROUNDED_FRICTION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

union vector3d;
struct s_grounded_friction_definition;

struct s_grounded_friction_update_input
{
    s_grounded_friction_definition * definition; // 0x0
};

class c_grounded_friction_component
{
public:
    void initialize(long object_index);
    void update(s_grounded_friction_update_input * input);
    void notify_of_acceleration(vector3d const * acceleration, s_grounded_friction_definition * definition);

private:
    bool find_flattest_contact_surface(float * slope);

    long m_object_index; // 0x0
    unsigned short m_grounded_ticks; // 0x4
};
static_assert(sizeof(c_grounded_friction_component) == 0x8, "c_grounded_friction_component");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GROUNDED_FRICTION_H__

