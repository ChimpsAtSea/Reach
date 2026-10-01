#pragma once
#ifndef __INITIALIZATION_CONTAINER_H__
#define __INITIALIZATION_CONTAINER_H__

/* ---------- headers */

#include "baselib\synchronized_value_windows.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type>
class t_initialization_container
{
public:
    t_initialization_container(void);
    ~t_initialization_container(void);

    t_type const * get(void (* const initialize_function)(t_type *));

private:
    c_synchronized_int32 m_lock;
    c_synchronized_int32 m_initialized;
    s_thread_id m_initializing_thread_id;
    t_type m_value;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#include "foundation\baselib\multithreading\datatypes\initialization_container.inl"

#endif // __INITIALIZATION_CONTAINER_H__
