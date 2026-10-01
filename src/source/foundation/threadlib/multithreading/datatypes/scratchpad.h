#ifndef __SCRATCHPAD_H__
#define __SCRATCHPAD_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "baselib\synchronized_value_windows.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type, long k_size>
class c_scratchpad
{
public:
    c_scratchpad(void)
    {
    }

    ~c_scratchpad(void)
    {
    }

    t_type * get_scratchpad(void)
    {
        long id_to_use = m_next_id.increment() - 1;
        assert_decomp(id_to_use < k_size, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib/multithreading/datatypes/scratchpad.h", 27);

        return &m_scratchpads[id_to_use];
    }

private:
    t_type m_scratchpads[k_size];
    c_synchronized_int32 m_next_id;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCRATCHPAD_H__

