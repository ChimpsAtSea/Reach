/* ---------- headers */

#include "blamlib\spring_acceleration.h"
#include "omaha\cseries\cseries.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\math\function_definitions.h"
#include "omaha\game\game_time.h"
#include "omaha\physics\spring_acceleration_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern real fabs(real x);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void spring_acceleration_state_update(struct s_spring_acceleration_state *, long, union vector3d const *, bool);

void spring_acceleration_state_update(s_spring_acceleration_state * state, long spring_acceleration_index, vector3d const * world_velocity, bool reset)
{
    mangled_ppc("?spring_acceleration_state_update@@YAXPAUs_spring_acceleration_state@@JPBTvector3d@@_N@Z");

    s_spring_acceleration_struct_definition * definition = static_cast<s_spring_acceleration_struct_definition *>(tag_get(SPRING_ACCELERATION_TAG, spring_acceleration_index));
    if (reset)
    {
        state->previous_world_velocity = *world_velocity;
    }

    vector3d world_acceleration;
    subtract_vectors3d(world_velocity, &state->previous_world_velocity, &world_acceleration);
    scale_vector3d(&world_acceleration, static_cast<real>(game_tick_rate()), &world_acceleration);
    state->previous_world_velocity = *world_velocity;

    for (long axis = 0; axis < 3; axis++)
    {
        if (definition->axis_linear_acceleration_indices[axis] != NONE)
        {
            s_spring_linear_acceleration_block * linear_acceleration = static_cast<s_spring_linear_acceleration_block *>(tag_block_get_element_with_size(&definition->linear_accelerations, definition->axis_linear_acceleration_indices[axis], sizeof(s_spring_linear_acceleration_block)));
            if (!realcmp(linear_acceleration->velocity_domain, 0.0f))
            {
                real range = fabs(linear_acceleration->acceleration_range);
                real ratio = fabs(state->position.n[axis] * linear_acceleration->inverse_acceleration_range);
                ratio = CEILING(ratio, 1.0f);

                real spring_acceleration = -(state->position.n[axis] != 0.0f ? (state->position.n[axis] < 0.0f ? -1 : 1) : 0) * linear_acceleration->spring_acceleration.function.get_const()->evaluate_scalar(ratio, 0.0f);
                world_acceleration.n[axis] *= -linear_acceleration->world_acceleration_scale;
                world_acceleration.n[axis] += spring_acceleration;
                state->velocity.n[axis] += world_acceleration.n[axis] * game_tick_length();

                real velocity_input = state->velocity.n[axis] / linear_acceleration->velocity_domain;
                velocity_input = PIN(fabs(velocity_input), 0.0f, 1.0f);

                real damping = linear_acceleration->spring_damping.function.get_const()->evaluate_scalar(velocity_input, 0.0f);
                state->velocity.n[axis] *= PIN(1.0f - damping, 0.0f, 1.0f);
                state->velocity.n[axis] = PIN(state->velocity.n[axis], -linear_acceleration->velocity_domain, linear_acceleration->velocity_domain);
                state->position.n[axis] += state->velocity.n[axis] * game_tick_length();
                state->position.n[axis] = PIN(state->position.n[axis], -range, range);
                state->acceleration.n[axis] = state->position.n[axis] * linear_acceleration->inverse_acceleration_range;
            }
        }
    }
};

