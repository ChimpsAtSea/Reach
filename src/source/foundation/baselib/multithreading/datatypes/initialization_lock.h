#pragma once
#ifndef __INITIALIZATION_LOCK_H__
#define __INITIALIZATION_LOCK_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- prototypes */

extern void initialization_lock_startup_begin(void);
extern void initialization_lock_thread_begin(void);
extern void initialization_lock_assert_thread_read_valid(void);
extern void initialization_lock_assert_thread_write_valid(void);

/* ---------- definitions */

// wraps startup-initialized globals; accessors assert the calling thread may read/write them
template<typename t_type>
class t_initialization_lock
{
public:
    t_type const * get_const() const
    {
        initialization_lock_assert_thread_read_valid();
        return &m_value;
    };

    t_type * get_writable()
    {
        initialization_lock_assert_thread_write_valid();
        return &m_value;
    };

    t_type * get_writable_UNSAFE()
    {
        return &m_value;
    };

private:
    t_type m_value;
};

/* ---------- globals */

/* ---------- public code */

#endif // __INITIALIZATION_LOCK_H__

