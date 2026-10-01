#pragma once
#ifndef __PHYSICS_VARIABLES_H__
#define __PHYSICS_VARIABLES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct physics_variable_position
{
    float maximum_position; // 0x0
    float minimum_position; // 0x4
};
static_assert(sizeof(physics_variable_position) == 0x8, "physics_variable_position");

struct physics_variable_speed
{
    float maximum_forward_speed; // 0x0
    float maximum_reverse_speed; // 0x4
    float acceleration; // 0x8
    float deceleration; // 0xC
};
static_assert(sizeof(physics_variable_speed) == 0x10, "physics_variable_speed");

struct physics_variable
{
    float maximum_position; // 0x0
    float minimum_position; // 0x4
    float maximum_speed; // 0x8
    float minimum_speed; // 0xC
    float acceleration; // 0x10
    float deceleration; // 0x14
};
static_assert(sizeof(physics_variable) == 0x18, "physics_variable");

/* ---------- prototypes */

extern void physics_variable_position_update(float * position, physics_variable_position const * definition, bool cyclical_position, float speed, float dt);
extern bool physics_variable_position_update_seek(float * position, physics_variable_position const * definition, bool cyclical_position, float desired_position, float speed, float dt);
extern void physics_variable_speed_update(float * speed, physics_variable_speed const * definition, float magnitude, float dt);
extern bool physics_variable_speed_update_seek(float * speed, physics_variable_speed const * definition, float desired_speed, float magnitude, float dt);
extern void physics_variable_update(float * position, float * speed, physics_variable const * definition, bool cyclical_position, float magnitude, float dt);
extern bool physics_variable_update_seek(float * position, float * speed, physics_variable const * definition, bool cyclical_position, float desired_position, float magnitude, float dt);

/* ---------- globals */

/* ---------- public code */

#endif // __PHYSICS_VARIABLES_H__

