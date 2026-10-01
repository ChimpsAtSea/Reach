#pragma once
#ifndef __THREAD_SAFE_LINKED_LIST_H__
#define __THREAD_SAFE_LINKED_LIST_H__

/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_type>
class t_thread_safe_list
{
public:
    struct s_list_element
    {
        t_type data;
        s_list_element * next;
    };

    t_thread_safe_list(void);
    ~t_thread_safe_list(void);

    void initialize(s_critical_section critical_section);
    void dispose(void);

    void add_element_to_front(s_list_element * element);
    template<typename t_comparer>
    void add_element_ordered(s_list_element * element, t_comparer & comparer);
    template<typename t_comparer>
    void add_element_ordered_assumes_locked(s_list_element * element, t_comparer & comparer);

    bool is_empty(void);
    long size(void);
    s_list_element * get_and_remove_head_element(void);
    bool remove_element_assumes_locked(s_list_element * element);

    template<typename t_visitor>
    void visit_list(t_visitor * visitor);

    void lock(void);
    void unlock(void);

private:
    s_list_element * m_head;
    s_critical_section m_critical_section;
};

template<typename t_type>
class c_list_comparer_ordered
{
public:
    bool operator()(t_type const & a, t_type const & b)
    {
        return a < b;
    }
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#include "foundation\threadlib\multithreading\datatypes\thread_safe_linked_list.inl"

#endif // __THREAD_SAFE_LINKED_LIST_H__
