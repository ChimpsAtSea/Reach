#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\lock_tracker.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<unsigned long, 128>::k_element_count; // "?k_element_count@?$s_static_array@K$0IA@@@2JB"

// public: void c_lock_tracker::initialize(class c_lock_hierarchy const *);
// public: void c_lock_tracker::dispose(void);
// public: void c_lock_tracker::set_enforcement_enabled(bool);
// public: void c_lock_tracker::check_empty(void) const;
// public: bool c_synchronization_object::get_non_stack_ordering(void) const;
// public: void c_lock_tracker::verify_push(class c_synchronization_object const *);
// public: long c_synchronization_object::get_lock_node_index(void) const;
// public: void c_lock_tracker::push(class c_synchronization_object const *);
// public: void c_lock_tracker::pop(class c_synchronization_object const *);
// public: bool c_static_stack<struct s_lock_tracker_entry, 32>::valid(long) const;
// public: long c_static_stack<struct s_lock_tracker_entry, 32>::top(void) const;
// public: long c_static_stack<struct s_lock_tracker_entry, 32>::count(void) const;
// public: void c_static_stack<struct s_lock_tracker_entry, 32>::clear(void);
// public: void c_static_stack<struct s_lock_tracker_entry, 32>::push_back(struct s_lock_tracker_entry const &);
// public: void c_static_stack<struct s_lock_tracker_entry, 32>::pop(void);
// public: struct s_lock_tracker_entry & c_static_stack<struct s_lock_tracker_entry, 32>::operator[](long);
// public: struct s_lock_tracker_entry const * c_static_stack<struct s_lock_tracker_entry, 32>::get(long) const;
// public: struct s_lock_tracker_entry * c_static_stack<struct s_lock_tracker_entry, 32>::get(long);
// public: void s_static_bitarray<128>::clear(void);
// public: bool s_static_bitarray<128>::test(long) const;
// public: void s_static_bitarray<128>::set(long, bool);
// public: long * s_static_array<long, 128>::get_elements(void);
// public: static long s_static_array<long, 128>::get_count(void);
// public: unsigned long * s_static_array<unsigned long, 128>::get_elements(void);
// public: bool c_static_stack<struct s_lock_tracker_entry, 32>::valid(void) const;
// public: bool c_static_stack<struct s_lock_tracker_entry, 32>::empty(void) const;
// public: long c_static_stack<struct s_lock_tracker_entry, 32>::push(void);
// public: bool c_static_stack<struct s_lock_tracker_entry, 32>::full(void) const;
// public: bool s_flags<enum e_synchronization_object_flags, unsigned long, 1>::test(enum e_synchronization_object_flags) const;

void c_lock_tracker::initialize(c_lock_hierarchy const * hierarchy)
{
    mangled_ppc("?initialize@c_lock_tracker@@QAAXPBVc_lock_hierarchy@@@Z");

    assert_tag_debug_untracked_jul_11_2011(47, hierarchy);

    m_hierarchy = hierarchy;
    m_lock_stack.clear();
    m_enforcement_enabled = true;
};

void c_lock_tracker::dispose(void)
{
    mangled_ppc("?dispose@c_lock_tracker@@QAAXXZ");

    m_lock_stack.clear();
};

void c_lock_tracker::set_enforcement_enabled(bool enabled)
{
    mangled_ppc("?set_enforcement_enabled@c_lock_tracker@@QAAX_N@Z");

    m_enforcement_enabled = enabled;
};

void c_lock_tracker::check_empty(void) const
{
    mangled_ppc("?check_empty@c_lock_tracker@@QBAXXZ");

    if (m_enforcement_enabled)
    {
        long held_count = 0;
        s_static_string<1024> held_string;
        held_string.clear();
        for (long entry_index = 0; entry_index < m_lock_stack.count(); entry_index++)
        {
            s_lock_tracker_entry const * entry = m_lock_stack.get(entry_index);
            if (entry->object->get_non_stack_ordering())
            {
                // non-stack-ordered objects may legitimately remain held
            }
            else
            {
                held_string.append_print("%s'%s'@#%d", held_count == 0 ? "" : ", ", entry->name, entry_index);
                held_count++;
            }
        }

        if (held_count > 0)
        {
            event(_event_error, "synchronization:lock_tracker: empty-check but we are not empty: '%s'", held_string.get_string());
        }
    }
};

bool c_synchronization_object::get_non_stack_ordering(void) const
{
    mangled_ppc("?get_non_stack_ordering@c_synchronization_object@@QBA_NXZ");

    return m_flags.test(_synchronization_object_non_stack_ordering_bit);
};

void c_lock_tracker::verify_push(c_synchronization_object const * object)
{
    mangled_ppc("?verify_push@c_lock_tracker@@QAAXPBVc_synchronization_object@@@Z");

    if (m_enforcement_enabled)
    {
        long lock_node_index = object->get_lock_node_index();
        if (object->get_non_stack_ordering())
        {
            // non-stack-ordered objects are not checked against the hierarchy
        }
        else if (lock_node_index == NONE)
        {
            assert_tag_debug_untracked_jul_11_2011(120, object->get_synchronization_group_index()!=k_synchronization_group_base);
        }
        else
        {
            bool found_unordered = false;
            long closest_parent_index = NONE;
            long indirect_parent_index = NONE;
            s_static_bitarray<k_maximum_lock_nodes> lock_flags;
            lock_flags.clear();
            s_static_string<1024> unordered_string;
            unordered_string.clear();

            for (long entry_index = 0; entry_index < m_lock_stack.count(); entry_index++)
            {
                s_lock_tracker_entry * entry = m_lock_stack.get(entry_index);
                lock_flags.set(DATUM_INDEX_TO_ABSOLUTE_INDEX(entry->lock_node_index), true);

                e_lock_relationship blocking_relationship;
                if (entry->object->get_non_stack_ordering())
                {
                    blocking_relationship = k_lock_relationship_count;
                }
                else if (entry->lock_node_index == NONE)
                {
                    blocking_relationship = k_lock_relationship_count;
                }
                else
                {
                    long chain_length;
                    s_static_array<long, k_maximum_lock_nodes> chain_node_indices;
                    s_static_array<unsigned long, k_maximum_lock_nodes> chain_object_ids;
                    blocking_relationship = m_hierarchy->query_blocking_relationship(entry->lock_node_index, lock_node_index, chain_node_indices.get_count(), chain_node_indices.get_elements(), chain_object_ids.get_elements(), &chain_length);
                }

                switch (blocking_relationship)
                {
                case _lock_relationship_parent:
                    closest_parent_index = entry_index;
                    break;
                case _lock_relationship_ancestor:
                    indirect_parent_index = entry_index;
                    break;
                case _lock_relationship_same:
                case k_lock_relationship_count:
                    break;
                case _lock_relationship_child:
                case _lock_relationship_descendant:
                    if (m_hierarchy->query_reverse_dependency(entry->lock_node_index, lock_node_index))
                    {
                        assert_tag_debug_untracked_jul_11_2011(205, lock_flags.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(lock_node_index)));
                    }
                    else if (lock_flags.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(lock_node_index)))
                    {
                        // we already hold this lock
                    }
                    else
                    {
                        s_static_string<1024> violation_string;
                        violation_string.print("tried to take parent '%s' while holding child '%s'@#%d/#%d, chain is:", object->get_name(), entry->name, entry_index, m_lock_stack.count());
                        for (long chain_index = 0; chain_index < m_lock_stack.count(); chain_index++)
                        {
                            violation_string.append_print(" '%s'@#%d", m_lock_stack[chain_index].name, chain_index);
                        }

                        event(_event_error, "synchronization:lock_tracker: %s", violation_string.get_string());
                        vassert_tag_debug_untracked_jul_11_2011(228, false, "lock hierarchy violation: %s", violation_string.get_string());
                    }
                    break;
                case _lock_relationship_common_descendant:
                case _lock_relationship_common_ancestor:
                case _lock_relationship_unrelated:
                    if (!found_unordered)
                    {
                        unordered_string.print("unordered push '%s' onto %d:", object->get_name(), m_lock_stack.count());
                        found_unordered = true;
                    }

                    unordered_string.append_print(" (%s:'%s'@#%d)", blocking_relationship == _lock_relationship_common_descendant ? "unordered-parent" : blocking_relationship == _lock_relationship_common_ancestor ? "unordered-children" : "unconnected", entry->name, entry_index);
                    break;
                default:
                    dassert_tag_debug_untracked_jul_11_2011(250, false, "unreachable");
                    break;
                }
            }

            if (found_unordered)
            {
                event(_event_error, "synchronization:lock_tracker: %s", unordered_string.get_string());
                vassert_tag_debug_untracked_jul_11_2011(259, false, "lock hierarchy insufficient information: %s", unordered_string.get_string());
            }

            if (indirect_parent_index > closest_parent_index)
            {
                s_lock_tracker_entry * indirect_parent_entry = m_lock_stack.get(indirect_parent_index);
                s_static_string<1024> undeclared_string;
                undeclared_string.print("tried to take lock '%s' which is only declared as an indirect child of '%s'@#%d/#%d, chain is:", object->get_name(), indirect_parent_entry->name, indirect_parent_index, m_lock_stack.count());
                for (long chain_index = 0; chain_index < m_lock_stack.count(); chain_index++)
                {
                    undeclared_string.append_print(" '%s'@#%d", m_lock_stack[chain_index].name, chain_index);
                }

                event(_event_error, "synchronization:lock_tracker: %s", undeclared_string.get_string());
                vassert_tag_debug_untracked_jul_11_2011(280, false, "lock hierarchy undeclared call: %s", undeclared_string.get_string());
            }
        }
    }
};

long c_synchronization_object::get_lock_node_index(void) const
{
    mangled_ppc("?get_lock_node_index@c_synchronization_object@@QBAJXZ");

    return m_lock_node_index;
};

void c_lock_tracker::push(c_synchronization_object const * object)
{
    mangled_ppc("?push@c_lock_tracker@@QAAXPBVc_synchronization_object@@@Z");

    s_lock_tracker_entry entry;
    csmemset(&entry, 0, sizeof(entry));
    entry.object_id = object->get_object_id();
    entry.lock_node_index = object->get_lock_node_index();
    entry.object = object;
    entry.name = object->get_name();
    m_lock_stack.push_back(entry);
};

void c_lock_tracker::pop(c_synchronization_object const * object)
{
    mangled_ppc("?pop@c_lock_tracker@@QAAXPBVc_synchronization_object@@@Z");

    long entry_index;
    unsigned long object_id = object->get_object_id();
    for (entry_index = m_lock_stack.top(); entry_index >= 0; entry_index--)
    {
        if (m_lock_stack[entry_index].object_id == object_id)
        {
            break;
        }
    }

    if (m_lock_stack.valid(entry_index))
    {
        if (entry_index != m_lock_stack.top())
        {
            if (m_enforcement_enabled)
            {
                if (object->get_non_stack_ordering())
                {
                    // non-stack-ordered objects may be released out of order
                }
                else
                {
                    vassert_tag_debug_untracked_jul_11_2011(335, false, "tried to pop synchronization object '%s' that was not top-of-stack (you are not unwinding in the reverse order that you acquired!)", object->get_name());

                    s_static_string<1024> inbetween_string;
                    inbetween_string.print("non-stack pop '%s'@#%d != top #%d, inbetween:", m_lock_stack[entry_index].name, entry_index, m_lock_stack.top());
                    for (long inbetween_index = entry_index + 1; inbetween_index <= m_lock_stack.top(); inbetween_index++)
                    {
                        inbetween_string.append_print(" '%s'@#%d", m_lock_stack[inbetween_index].name, inbetween_index);
                    }

                    event(_event_error, "synchronization:lock_tracker: %s", inbetween_string.get_string());
                }
            }

            {
                s_lock_tracker_entry entry = m_lock_stack[entry_index];
                m_lock_stack[entry_index] = m_lock_stack[m_lock_stack.top()];
                m_lock_stack[m_lock_stack.top()] = entry;
            }
        }

        assert_tag_debug_untracked_jul_11_2011(362, m_lock_stack[m_lock_stack.top()].object_id==object_id);
        m_lock_stack.pop();
    }
    else if (m_enforcement_enabled)
    {
        vassert_tag_debug_untracked_jul_11_2011(369, false, "tried to pop synchronization object '%s' that was not in the stack (unmatched critical_section_leave/mutex_release?)", object->get_name());
    }
};

//public: void s_static_bitarray<128>::set(long, bool)
//{
//    mangled_ppc("?set@?$s_static_bitarray@$0IA@@@QAAXJ_N@Z");
//};

