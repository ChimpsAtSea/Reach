#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\physics_variables.cpp"
/* ---------- headers */

#include "omaha\physics\physics_variables.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern float fabs(float x);
float physics_variable_position_get_seek_direction(float position, physics_variable_position const * definition, bool cyclical_position, float desired_position);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void physics_variable_position_update(float *, struct physics_variable_position const *, bool, float, float);
// bool physics_variable_position_update_seek(float *, struct physics_variable_position const *, bool, float, float, float);
// void physics_variable_speed_update(float *, struct physics_variable_speed const *, float, float);
// bool physics_variable_speed_update_seek(float *, struct physics_variable_speed const *, float, float, float);
// void physics_variable_update(float *, float *, struct physics_variable const *, bool, float, float);
// bool physics_variable_update_seek(float *, float *, struct physics_variable const *, bool, float, float, float);
// float physics_variable_position_get_seek_direction(float, struct physics_variable_position const *, bool, float);

void physics_variable_position_update(float * position, physics_variable_position const * definition, bool cyclical_position, float speed, float dt)
{
    mangled_ppc("?physics_variable_position_update@@YAXPAMPBUphysics_variable_position@@_NMM@Z");

    *position = *position + speed * dt;

    if (*position < definition->minimum_position)
    {
        if (cyclical_position)
        {
            *position += definition->maximum_position - definition->minimum_position;
        }
        else
        {
            *position = definition->minimum_position;
        }
    }
    else if (*position > definition->maximum_position)
    {
        if (cyclical_position)
        {
            *position -= definition->maximum_position - definition->minimum_position;
        }
        else
        {
            *position = definition->maximum_position;
        }
    }
};

bool physics_variable_position_update_seek(float * position, physics_variable_position const * definition, bool cyclical_position, float desired_position, float speed, float dt)
{
    mangled_ppc("?physics_variable_position_update_seek@@YA_NPAMPBUphysics_variable_position@@_NMMM@Z");

    bool success = true;
    float direction = physics_variable_position_get_seek_direction(*position, definition, cyclical_position, desired_position);

    if (direction != 0.0f)
    {
        physics_variable_position_update(position, definition, cyclical_position, direction * speed, dt);

        if (direction != physics_variable_position_get_seek_direction(*position, definition, cyclical_position, desired_position))
        {
            *position = desired_position;
        }
        else
        {
            success = false;
        }
    }

    return success;
};

void physics_variable_speed_update(float * speed, physics_variable_speed const * definition, float magnitude, float dt)
{
    mangled_ppc("?physics_variable_speed_update@@YAXPAMPBUphysics_variable_speed@@MM@Z");

    if (magnitude != 0.0f)
    {
        float absolute_magnitude = fabs(magnitude);
        float acceleration = absolute_magnitude * definition->acceleration * dt;
        float deceleration = absolute_magnitude * definition->deceleration * dt;

        if (magnitude > 0.0f)
        {
            if (*speed <= -deceleration)
            {
                *speed = *speed + deceleration;
            }
            else if (*speed >= 0.0f)
            {
                *speed = *speed + acceleration;
            }
            else
            {
                *speed = (1.0f + *speed / deceleration) * acceleration;
            }

            *speed = *speed > definition->maximum_forward_speed ? definition->maximum_forward_speed : *speed;
        }
        else
        {
            if (*speed >= deceleration)
            {
                *speed = *speed - deceleration;
            }
            else if (*speed <= 0.0f)
            {
                *speed = *speed - acceleration;
            }
            else
            {
                *speed = (*speed / deceleration - 1.0f) * acceleration;
            }

            *speed = MAX(*speed, -definition->maximum_reverse_speed);
        }
    }
};

bool physics_variable_speed_update_seek(float * speed, physics_variable_speed const * definition, float desired_speed, float magnitude, float dt)
{
    mangled_ppc("?physics_variable_speed_update_seek@@YA_NPAMPBUphysics_variable_speed@@MMM@Z");

    bool success = true;

    if (*speed > desired_speed)
    {
        physics_variable_speed_update(speed, definition, -magnitude, dt);

        if (*speed <= desired_speed)
        {
            *speed = desired_speed;
        }
        else
        {
            success = false;
        }
    }
    else if (*speed < desired_speed)
    {
        physics_variable_speed_update(speed, definition, magnitude, dt);

        if (*speed >= desired_speed)
        {
            *speed = desired_speed;
        }
        else
        {
            success = false;
        }
    }

    return success;
};

void physics_variable_update(float * position, float * speed, physics_variable const * definition, bool cyclical_position, float magnitude, float dt)
{
    mangled_ppc("?physics_variable_update@@YAXPAM0PBUphysics_variable@@_NMM@Z");

    physics_variable_position const * position_definition = reinterpret_cast<physics_variable_position const *>(definition);
    physics_variable_speed const * speed_definition = reinterpret_cast<physics_variable_speed const *>(&definition->maximum_speed);

    physics_variable_speed_update(speed, speed_definition, magnitude, dt);
    physics_variable_position_update(position, position_definition, cyclical_position, *speed, dt);
};

bool physics_variable_update_seek(float * position, float * speed, physics_variable const * definition, bool cyclical_position, float desired_position, float magnitude, float dt)
{
    mangled_ppc("?physics_variable_update_seek@@YA_NPAM0PBUphysics_variable@@_NMMM@Z");

    bool success = true;
    physics_variable_position const * position_definition = reinterpret_cast<physics_variable_position const *>(definition);
    physics_variable_speed const * speed_definition = reinterpret_cast<physics_variable_speed const *>(&definition->maximum_speed);
    float direction = physics_variable_position_get_seek_direction(*position, position_definition, cyclical_position, desired_position);

    if (direction != 0.0f)
    {
        physics_variable_speed_update(speed, speed_definition, direction * magnitude, dt);
        physics_variable_position_update(position, position_definition, cyclical_position, *speed, dt);

        if (direction != physics_variable_position_get_seek_direction(*position, position_definition, cyclical_position, desired_position))
        {
            *position = desired_position;
            *speed = 0.0f;
        }
        else
        {
            success = false;
        }
    }

    return success;
};

float physics_variable_position_get_seek_direction(float position, physics_variable_position const * definition, bool cyclical_position, float desired_position)
{
    mangled_ppc("?physics_variable_position_get_seek_direction@@YAMMPBUphysics_variable_position@@_NM@Z");

    float delta = desired_position - position;

    if (delta != 0.0f)
    {
        if (cyclical_position && fabs(delta) > 0.5f * (definition->maximum_position - definition->minimum_position))
        {
            delta = -delta;
        }

        delta = delta > 0.0f ? 1.0f : -1.0f;
    }

    return delta;
};
