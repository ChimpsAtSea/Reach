#pragma once
#ifndef __INITIALIZATION_CONTAINER_INL__
#define __INITIALIZATION_CONTAINER_INL__

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "baselib\thread_execution_windows.h"

/* ---------- constants */

#define __INITIALIZATION_CONTAINER_INL_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/multithreading/datatypes/initialization_container.inl"

/* ---------- public code */

template<typename t_type>
t_initialization_container<t_type>::t_initialization_container(void)
{
}

template<typename t_type>
t_initialization_container<t_type>::~t_initialization_container(void)
{
}

template<typename t_type>
t_type const * t_initialization_container<t_type>::get(void (* const initialize_function)(t_type *))
{
    if (!m_initialized.peek())
    {
        if (m_lock.set_if_equal(1, 0) == 0)
        {
            s_thread_id current_thread_id = thread_get_current_id();
            m_initializing_thread_id = current_thread_id;
            initialize_function(&m_value);
            assert_decomp(m_initializing_thread_id.id==current_thread_id.id, __INITIALIZATION_CONTAINER_INL_FILE__, 31);
            m_initialized.set(1);
            m_lock.set(0);
        }
        else
        {
            s_thread_id current_thread_id = thread_get_current_id();
            dassert_decomp(m_initializing_thread_id.id != current_thread_id.id, "t_initialization_container attempted to reentrantly initialize", __INITIALIZATION_CONTAINER_INL_FILE__, 43);
            do
            {
                thread_switch();
            }
            while (!m_initialized.peek());
        }
    }

    return &m_value;
}

#endif // __INITIALIZATION_CONTAINER_INL__
