#ifndef __CONTROLLERS_H__
#define __CONTROLLERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_controller_index
{
    k_no_controller = -1,
    _controller0 = 0,
    _controller1,
    _controller2,
    _controller3,

    k_number_of_controllers,

    k_any_controller = 255
};

#define VALID_CONTROLLER(controller_index) ((controller_index) >= _controller0 && (controller_index) < k_number_of_controllers)

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

inline e_controller_index first_controller()
{
    return _controller0;
}

inline e_controller_index next_controller(e_controller_index controller_index)
{
    e_controller_index next_controller_index = k_no_controller;

    assert_decomp(controller_index==k_no_controller || (controller_index>=0 && controller_index<k_number_of_controllers), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\input\\controllers.h", 54);

    if (VALID_INDEX(controller_index, k_number_of_controllers - 1))
    {
        next_controller_index = static_cast<e_controller_index>(controller_index + 1);
    }
    return next_controller_index;
}

#endif // __CONTROLLERS_H__

