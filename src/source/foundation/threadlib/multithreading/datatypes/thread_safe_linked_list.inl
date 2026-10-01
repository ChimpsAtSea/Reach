#pragma once
#ifndef __THREAD_SAFE_LINKED_LIST_INL__
#define __THREAD_SAFE_LINKED_LIST_INL__

/* ---------- headers */

/* ---------- constants */

#define __THREAD_SAFE_LINKED_LIST_INL_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib/multithreading/datatypes/thread_safe_linked_list.inl"

/* ---------- public code */

template<typename t_type>
t_thread_safe_list<t_type>::t_thread_safe_list(void) :
    m_head(NULL),
    m_critical_section(k_critical_section_invalid)
{
}

template<typename t_type>
t_thread_safe_list<t_type>::~t_thread_safe_list(void)
{
}

template<typename t_type>
void t_thread_safe_list<t_type>::initialize(s_critical_section critical_section)
{
    assert_decomp(m_critical_section.object_id==k_critical_section_invalid.object_id, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 31);

    m_critical_section = critical_section;
}

template<typename t_type>
void t_thread_safe_list<t_type>::dispose(void)
{
    m_critical_section = k_critical_section_invalid;
}

template<typename t_type>
template<typename t_visitor>
void t_thread_safe_list<t_type>::visit_list(t_visitor * visitor)
{
    assert_decomp(visitor, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 72);

    lock();
    visitor->visit(m_head);
    unlock();
}

template<typename t_type>
void t_thread_safe_list<t_type>::add_element_to_front(s_list_element * element)
{
    lock();
    element->next = m_head;
    m_head = element;
    unlock();
}

template<typename t_type>
template<typename t_comparer>
void t_thread_safe_list<t_type>::add_element_ordered(s_list_element * element, t_comparer & comparer)
{
    lock();
    add_element_ordered_assumes_locked(element, comparer);
    unlock();
}

template<typename t_type>
template<typename t_comparer>
void t_thread_safe_list<t_type>::add_element_ordered_assumes_locked(s_list_element * element, t_comparer & comparer)
{
    assert_decomp(element!=NULL, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 163);
    assert_decomp(element!=m_head, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 164);
    assert_decomp(critical_section_inside(m_critical_section), __THREAD_SAFE_LINKED_LIST_INL_FILE__, 165);

    if (m_head == NULL)
    {
        m_head = element;
        element->next = NULL;
    }
    else if (comparer(element->data, m_head->data))
    {
        element->next = m_head;
        m_head = element;
    }
    else
    {
        s_list_element * current = m_head;
        while (true)
        {
            if (current->next == NULL)
            {
                current->next = element;
                element->next = NULL;
                break;
            }
            else if (comparer(element->data, current->next->data))
            {
                element->next = current->next;
                current->next = element;
                break;
            }

            assert_decomp(current->next != NULL, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 206);
            current = current->next;
        }
    }

    assert_decomp(element->next != element, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 212);
}

template<typename t_type>
bool t_thread_safe_list<t_type>::is_empty(void)
{
    bool result = false;

    lock();
    result = m_head == NULL;
    unlock();

    return result;
}

template<typename t_type>
long t_thread_safe_list<t_type>::size(void)
{
    long count = 0;
    s_list_element * current = NULL;

    lock();
    current = m_head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    unlock();

    return count;
}

template<typename t_type>
typename t_thread_safe_list<t_type>::s_list_element * t_thread_safe_list<t_type>::get_and_remove_head_element(void)
{
    s_list_element * element = NULL;

    lock();
    element = m_head;
    if (element != NULL)
    {
        remove_element_assumes_locked(element);
    }
    unlock();

    return element;
}

template<typename t_type>
bool t_thread_safe_list<t_type>::remove_element_assumes_locked(s_list_element * element)
{
    bool removed = false;

    assert_decomp(element!=NULL, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 221);
    assert_decomp(critical_section_inside(m_critical_section), __THREAD_SAFE_LINKED_LIST_INL_FILE__, 222);

    if (m_head == element)
    {
        m_head = m_head->next;
        removed = true;
    }
    else
    {
        s_list_element * current = m_head;
        while (current != NULL && !removed)
        {
            if (current->next == element)
            {
                current->next = element->next;
                removed = true;
            }
            current = current->next;
        }
    }

    assert_decomp(m_head!=element, __THREAD_SAFE_LINKED_LIST_INL_FILE__, 248);

    return removed;
}

template<typename t_type>
void t_thread_safe_list<t_type>::lock(void)
{
    critical_section_enter_internal(m_critical_section, _critical_section_non_recursive);
}

template<typename t_type>
void t_thread_safe_list<t_type>::unlock(void)
{
    critical_section_leave_internal(m_critical_section, _critical_section_non_recursive);
}

#undef __THREAD_SAFE_LINKED_LIST_INL_FILE__

#endif // __THREAD_SAFE_LINKED_LIST_INL__
