#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_context.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_context.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_event_thread_context::push(char const *, char const *, bool);
// public: void c_event_thread_context::pop(void);
// public: bool c_event_thread_context::describe(enum e_event_context_query_destination_type, class s_static_string<256> *) const;
// public: static long s_static_array<struct c_event_thread_context::s_stack_entry, 32>::get_count(void);
// public: struct c_event_thread_context::s_stack_entry & s_static_array<struct c_event_thread_context::s_stack_entry, 32>::operator[]<long>(long);
// public: struct c_event_thread_context::s_stack_entry const & s_static_array<struct c_event_thread_context::s_stack_entry, 32>::operator[]<long>(long) const;
// public: static bool s_static_array<struct c_event_thread_context::s_stack_entry, 32>::valid<long>(long);

void c_event_thread_context::push(char const * type, char const * description, bool display_to_console)
{
    mangled_ppc("?push@c_event_thread_context@@QAAXPBD0_N@Z");

    assert_tag_debug_untracked_jul_11_2011(21, type);
    assert_tag_debug_untracked_jul_11_2011(22, description);

    if (m_stack_depth >= 0 && m_stack_depth < m_stack.get_count())
    {
        s_stack_entry & entry = m_stack[m_stack_depth];
        entry.type = type;
        entry.description = description;
        entry.display_to_console = display_to_console;
    }
    else
    {
        dassert_tag_debug_untracked_jul_11_2011(38, false, "exceeded the maximum event context count!");
    }

    m_stack_depth++;
};

void c_event_thread_context::pop(void)
{
    mangled_ppc("?pop@c_event_thread_context@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(47, m_stack_depth>0);

    m_stack_depth--;
};

bool c_event_thread_context::describe(e_event_context_query_destination_type destination_type, s_static_string<256> * out_description) const
{
    mangled_ppc("?describe@c_event_thread_context@@QBA_NW4e_event_context_query_destination_type@@PAV?$s_static_string@$0BAA@@@@Z");

    // local names affect /Od stack slot assignment (count must sit below has_context)
    long count = int_pin(m_stack_depth, 0, m_stack.get_count());
    bool has_context = false;

    assert_tag_debug_untracked_jul_11_2011(58, out_description);
    out_description->clear();

    switch (destination_type)
    {
    case _event_context_query_destination_console:
    {
        for (long stack_index = 0; stack_index < count; stack_index++)
        {
            s_stack_entry const & entry = m_stack[stack_index];
            if (entry.display_to_console)
            {
                out_description->append(entry.description);
                if (stack_index < count - 1)
                {
                    out_description->append(":");
                }
                has_context = true;
            }
        }
    }
    break;
    case _event_context_query_destination_log:
    case _event_context_query_destination_remote_log:
    case _event_context_query_destination_unknown3:
    {
        for (long stack_index = count - 1; stack_index >= 0; stack_index--)
        {
            s_stack_entry const & entry = m_stack[stack_index];
            out_description->append_print("%s(%s)%s%s", stack_index == count - 1 ? "[" : "", entry.type, entry.description, stack_index > 0 ? ":" : "]");
            has_context = true;
        }
    }
    break;
    default:
    {
        dassert_tag_debug_untracked_jul_11_2011(94, false, "unreachable");
    }
    break;
    }

    return has_context;
};

//public: static long s_static_array<struct c_event_thread_context::s_stack_entry, 32>::get_count(void)
//{
//    mangled_ppc("?get_count@?$s_static_array@Us_stack_entry@c_event_thread_context@@$0CA@@@SAJXZ");
//};

//public: struct c_event_thread_context::s_stack_entry & s_static_array<struct c_event_thread_context::s_stack_entry, 32>::operator[]<long>(long)
//{
//    mangled_ppc("??$?AJ@?$s_static_array@Us_stack_entry@c_event_thread_context@@$0CA@@@QAAAAUs_stack_entry@c_event_thread_context@@J@Z");
//};

//public: struct c_event_thread_context::s_stack_entry const & s_static_array<struct c_event_thread_context::s_stack_entry, 32>::operator[]<long>(long) const
//{
//    mangled_ppc("??$?AJ@?$s_static_array@Us_stack_entry@c_event_thread_context@@$0CA@@@QBAABUs_stack_entry@c_event_thread_context@@J@Z");
//};

//public: static bool s_static_array<struct c_event_thread_context::s_stack_entry, 32>::valid<long>(long)
//{
//    mangled_ppc("??$valid@J@?$s_static_array@Us_stack_entry@c_event_thread_context@@$0CA@@@SA_NJ@Z");
//};

