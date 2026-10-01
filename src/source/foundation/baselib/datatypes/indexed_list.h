#ifndef __INDEXED_LIST_H__
#define __INDEXED_LIST_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

unsigned short const k_il_index_null = 0xFFFF;

#define INDEXED_LIST_H_FILE "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\indexed_list.h"

/* ---------- definitions */

struct s_il_node
{
    unsigned short next;
    unsigned short prev;
};
static_assert(sizeof(s_il_node) == 0x4, "s_il_node");

template<typename t_type, long k_size>
class c_indexed_list
{
public:
    class iterator
    {
    public:
        iterator(c_indexed_list * list, unsigned short prev, unsigned short current, unsigned short next) :
            m_list(list),
            m_prev(prev),
            m_current(current),
            m_next(next)
        {
        };

        t_type & operator*()
        {
            return m_list->get_data(m_current);
        };

        iterator & operator++()
        {
            m_prev = m_current;
            m_current = m_next;
            m_next = m_list->get_next(m_current);
            return *this;
        };

        iterator & operator--()
        {
            m_next = m_current;
            m_current = m_prev;
            m_prev = m_list->get_prev(m_current);
            return *this;
        };

        bool operator==(iterator const & other) const
        {
            return other.m_current == m_current && other.m_list == m_list;
        };

        bool operator!=(iterator const & other) const
        {
            return !(*this == other);
        };

        c_indexed_list * m_list;
        unsigned short m_prev;
        unsigned short m_current;
        unsigned short m_next;
    };

    class const_iterator
    {
    public:
        const_iterator(iterator const & other) :
            m_list(other.m_list),
            m_prev(other.m_prev),
            m_current(other.m_current),
            m_next(other.m_next)
        {
        };

        t_type const & operator*() const
        {
            return m_list->get_data(m_current);
        };

        const_iterator & operator++()
        {
            m_prev = m_current;
            m_current = m_next;
            m_next = m_list->get_next(m_current);
            return *this;
        };

        bool operator==(const_iterator const & other) const
        {
            return other.m_current == m_current && other.m_list == m_list;
        };

        bool operator!=(const_iterator const & other) const
        {
            return !(*this == other);
        };

        c_indexed_list const * m_list;
        unsigned short m_prev;
        unsigned short m_current;
        unsigned short m_next;
    };

    void initialize()
    {
        clear();
    };

    void dispose()
    {
        assert_decomp(m_num_nodes == 0, INDEXED_LIST_H_FILE, 383);
    };

    void clear()
    {
        m_max_count = k_size;
        m_num_nodes = 0;
        m_num_free = 0;
        m_free_head = k_il_index_null;
        m_head = k_il_index_null;
        m_tail = k_il_index_null;

        long index = k_size;
        while (index != 0)
        {
            index--;
            s_il_node * node = &m_nodes[index];
            node->next = k_il_index_null;
            node->prev = k_il_index_null;
            push(node);
        }
    };

    long count() const
    {
        return m_num_nodes;
    };

    long max_count() const
    {
        return m_max_count;
    };

    bool empty() const
    {
        return m_num_nodes == 0;
    };

    bool full() const
    {
        return m_num_nodes == m_max_count;
    };

    iterator begin()
    {
        unsigned short index = get_head();
        unsigned short prev = get_prev(index);
        unsigned short next = get_next(index);
        return iterator(this, prev, index, next);
    };

    iterator end()
    {
        unsigned short prev = get_tail();
        unsigned short index = k_il_index_null;
        unsigned short next = k_il_index_null;
        return iterator(this, prev, index, next);
    };

    bool push_front(t_type const & value)
    {
        bool result = false;

        if (m_num_nodes == 0)
        {
            m_head = pop();
            m_tail = m_head;
            assert_decomp(m_head != k_il_index_null, INDEXED_LIST_H_FILE, 427);
            result = true;
        }
        else
        {
            unsigned short head = m_head;
            unsigned short index = pop();
            if (index != k_il_index_null)
            {
                m_head = index;
                result = true;
                m_nodes[m_head].next = head;
                m_nodes[head].prev = m_head;
            }
        }

        if (result)
        {
            m_data[m_head] = value;
            m_num_nodes++;
        }

        return result;
    };

    bool push_back(t_type const & value)
    {
        bool result = false;

        if (m_num_nodes == 0)
        {
            m_head = pop();
            m_tail = m_head;
            assert_decomp(m_head != k_il_index_null, INDEXED_LIST_H_FILE, 471);
            result = true;
        }
        else
        {
            unsigned short prev = m_tail;
            unsigned short index = pop();
            if (index != k_il_index_null)
            {
                m_tail = index;
                result = true;
                m_nodes[m_tail].prev = prev;
                m_nodes[prev].next = m_tail;
            }
        }

        if (result)
        {
            m_data[m_tail] = value;
            m_num_nodes++;
        }

        return result;
    };

    t_type pop_head()
    {
        assert_decomp(m_num_nodes > 0, INDEXED_LIST_H_FILE, 504);
        m_num_nodes--;

        unsigned short index = m_head;
        s_il_node * free_node = &m_nodes[index];
        m_head = free_node->next;
        push(free_node);

        if (m_head != k_il_index_null)
        {
            m_nodes[m_head].prev = k_il_index_null;
        }

        return m_data[index];
    };

    void remove(iterator & it)
    {
        if (it.m_current != k_il_index_null)
        {
            unsigned short index = it.m_current;
            it.m_current = it.m_next;
            it.m_next = get_next(it.m_current);
            remove_indexed(index);
        }
    };

private:
    unsigned short get_next(unsigned short index) const
    {
        return index != k_il_index_null ? m_nodes[index].next : k_il_index_null;
    };

    unsigned short get_prev(unsigned short index) const
    {
        return index != k_il_index_null ? m_nodes[index].prev : k_il_index_null;
    };

    unsigned short get_head() const
    {
        return m_head;
    };

    unsigned short get_tail() const
    {
        return m_tail;
    };

    t_type & get_data(unsigned short index)
    {
        return m_data[index];
    };

    t_type const & get_data(unsigned short index) const
    {
        return m_data[index];
    };

    unsigned short pop()
    {
        unsigned short index = m_free_head;
        if (index != k_il_index_null)
        {
            s_il_node * node = &m_nodes[m_free_head];
            if (node)
            {
                m_free_head = node->next;
            }
            else
            {
                m_free_head = k_il_index_null;
            }

            if (m_num_free > 1 && m_free_head == k_il_index_null)
            {
                assert_decomp(0, INDEXED_LIST_H_FILE, 57);
            }

            if (node)
            {
                node->next = k_il_index_null;
                node->prev = k_il_index_null;
            }

            if (index != k_il_index_null)
            {
                m_num_free--;
            }
        }

        return index;
    };

    void push(s_il_node * node)
    {
        node->next = m_free_head;
        m_free_head = static_cast<unsigned short>(node - m_nodes);
        m_num_free++;
    };

    void remove_indexed(unsigned short index)
    {
        if (index != k_il_index_null)
        {
            assert_decomp(m_num_nodes > 0, INDEXED_LIST_H_FILE, 531);
            m_num_nodes--;

            s_il_node * node = &m_nodes[index];
            if (index == m_head)
            {
                m_head = node->next;
            }
            if (index == m_tail)
            {
                m_tail = node->prev;
            }
            if (node->prev != k_il_index_null)
            {
                m_nodes[node->prev].next = node->next;
            }
            if (node->next != k_il_index_null)
            {
                m_nodes[node->next].prev = node->prev;
            }
            push(node);
        }
    };

    s_il_node m_nodes[k_size];
    t_type m_data[k_size];
    long m_num_nodes;
    long m_num_free;
    long m_max_count;
    unsigned short m_head;
    unsigned short m_tail;
    unsigned short m_free_head;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __INDEXED_LIST_H__

