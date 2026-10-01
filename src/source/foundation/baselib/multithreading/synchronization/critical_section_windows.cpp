#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\critical_section_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "baselib\system_time_xenon.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_critical_section const k_critical_section_invalid = { k_synchronization_object_id_invalid };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_critical_section const k_critical_section_invalid; // "?k_critical_section_invalid@@3Us_critical_section@@B"

// struct s_critical_section critical_section_declare(long, struct s_critical_section_definition const *);
// void critical_section_create(class c_critical_section_instance *, unsigned long, long, struct s_critical_section_definition const *);
// public: void c_synchronization_object::set_non_stack_ordering(bool);
// void critical_section_destroy(class c_critical_section_instance *);
// void critical_section_enter_internal(struct s_critical_section, enum e_critical_section_recursive);
// public: long c_synchronization_object::get_locking_thread(void) const;
// public: void c_synchronization_object::increment_lock_count(long);
// bool critical_section_try_and_enter_internal(struct s_critical_section);
// void critical_section_leave_internal(struct s_critical_section, enum e_critical_section_recursive);
// public: void c_synchronization_object::decrement_lock_count(void);
// bool critical_section_inside(struct s_critical_section);
// void critical_section_force_release_if_owned_by_thread(class c_critical_section_instance *, long);
// public: c_critical_section_scope::c_critical_section_scope(struct s_critical_section);
// public: c_critical_section_scope::c_critical_section_scope(struct s_critical_section, long, bool *);
// public: c_critical_section_scope::~c_critical_section_scope(void);
// public: void s_flags<enum e_synchronization_object_flags, unsigned long, 1>::set(enum e_synchronization_object_flags, bool);
// public: static bool s_flags<enum e_synchronization_object_flags, unsigned long, 1>::valid_bit(enum e_synchronization_object_flags);
// public: bool s_flags<enum e_synchronization_object_flags, unsigned long, 1>::valid(void) const;
// private: static unsigned long s_flags<enum e_synchronization_object_flags, unsigned long, 1>::flag_size_type(enum e_synchronization_object_flags);
// private: static unsigned long s_flags<enum e_synchronization_object_flags, unsigned long, 1>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_synchronization_object_flags, unsigned long, 1>::make_N_bit_mask_size_type(enum e_synchronization_object_flags);

s_critical_section critical_section_declare(long synchronization_group_index, s_critical_section_definition const * definition)
{
    mangled_ppc("?critical_section_declare@@YA?AUs_critical_section@@JPBUs_critical_section_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(29, definition);
    assert_tag_debug_untracked_jul_11_2011(30, definition->name);
    assert_tag_debug_untracked_jul_11_2011(31, definition->spin_count>=0);

    s_critical_section critical_section;
    critical_section.object_id = synchronization_declare_critical_section(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(34, critical_section.object_id != NONE, "too many critical sections, increase k_maximum_critical_sections");

    return critical_section;
};

void critical_section_create(c_critical_section_instance * section, unsigned long object_id, long lock_node_index, s_critical_section_definition const * definition)
{
    mangled_ppc("?critical_section_create@@YAXPAVc_critical_section_instance@@KJPBUs_critical_section_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(45, section);
    assert_tag_debug_untracked_jul_11_2011(46, object_id!=k_synchronization_object_id_invalid);
    assert_tag_debug_untracked_jul_11_2011(47, !(SYNCHRONIZATION_OBJECT_GROUP(object_id)==k_synchronization_group_base && lock_node_index==NONE));
    assert_tag_debug_untracked_jul_11_2011(48, definition);
    assert_tag_debug_untracked_jul_11_2011(49, definition->name);
    assert_tag_debug_untracked_jul_11_2011(50, definition->spin_count>=0);

    InitializeCriticalSectionAndSpinCount(reinterpret_cast<CRITICAL_SECTION *>(section->m_critical_section), definition->spin_count);
    section->initialize(object_id);
    section->set_lock_node_index(lock_node_index);
    section->set_non_stack_ordering(definition->non_stack_ordering);
};

void critical_section_destroy(c_critical_section_instance * section)
{
    mangled_ppc("?critical_section_destroy@@YAXPAVc_critical_section_instance@@@Z");

    assert_tag_debug_untracked_jul_11_2011(61, section);
};

void critical_section_enter_internal(s_critical_section critical_section, e_critical_section_recursive recursive)
{
    mangled_ppc("?critical_section_enter_internal@@YAXUs_critical_section@@W4e_critical_section_recursive@@@Z");

    c_critical_section_instance * section = synchronization_get_critical_section(critical_section.object_id);
    assert_tag_debug_untracked_jul_11_2011(71, VALID_INDEX(recursive, k_critical_section_recursive_count));

    if (recursive != _critical_section_recursive)
    {
        section->acquire_prerequisites();
    }

    {
        c_synchronization_block_timer block_timer(critical_section.object_id, section->get_locking_thread());

        {
            long thread_index = synchronization_get_current_thread_index();
            g_synchronization_lock_tracker->verify_push(section);
            EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(section->m_critical_section));
            section->increment_lock_count(thread_index);
            g_synchronization_lock_tracker->push(section);
        }
    }
};

bool critical_section_try_and_enter_internal(s_critical_section critical_section)
{
    mangled_ppc("?critical_section_try_and_enter_internal@@YA_NUs_critical_section@@@Z");

    c_critical_section_instance * section = synchronization_get_critical_section(critical_section.object_id);
    bool entered = true;

    {
        c_synchronization_block_timer block_timer(critical_section.object_id, section->get_locking_thread());

        {
            long thread_index = synchronization_get_current_thread_index();
            g_synchronization_lock_tracker->verify_push(section);
            entered = TryEnterCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(section->m_critical_section)) != FALSE;

            if (entered)
            {
                section->increment_lock_count(thread_index);
                g_synchronization_lock_tracker->push(section);
            }
        }
    }

    return entered;
};

void critical_section_leave_internal(s_critical_section critical_section, e_critical_section_recursive recursive)
{
    mangled_ppc("?critical_section_leave_internal@@YAXUs_critical_section@@W4e_critical_section_recursive@@@Z");

    c_critical_section_instance * section = synchronization_get_critical_section(critical_section.object_id);
    assert_tag_debug_untracked_jul_11_2011(128, VALID_INDEX(recursive, k_critical_section_recursive_count));

    g_synchronization_lock_tracker->pop(section);
    section->decrement_lock_count();
    LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(section->m_critical_section));

    if (recursive != _critical_section_recursive)
    {
        section->release_prerequisites();
    }
};

bool critical_section_inside(s_critical_section critical_section)
{
    mangled_ppc("?critical_section_inside@@YA_NUs_critical_section@@@Z");

    c_critical_section_instance * section = synchronization_get_critical_section(critical_section.object_id);
    long thread_index = synchronization_get_current_thread_index();
    bool inside = static_cast<bool>(section->get_locking_thread() == thread_index);

    return inside;
};

void critical_section_force_release_if_owned_by_thread(c_critical_section_instance * section, long thread_index)
{
    mangled_ppc("?critical_section_force_release_if_owned_by_thread@@YAXPAVc_critical_section_instance@@J@Z");

    if (section->get_locking_thread() == thread_index)
    {
        s_critical_section critical_section;
        critical_section.object_id = section->get_object_id();

        do
        {
            critical_section_leave_internal(critical_section, _critical_section_recursive);
        } while (section->get_locking_thread() == thread_index);
    }
};

c_critical_section_scope::c_critical_section_scope(s_critical_section critical_section)
{
    mangled_ppc("??0c_critical_section_scope@@QAA@Us_critical_section@@@Z");

    m_critical_section = critical_section;
    m_lock_entered = false;

    if (m_critical_section.object_id != k_synchronization_object_id_invalid)
    {
        critical_section_enter_internal(m_critical_section, _critical_section_non_recursive);
        m_lock_entered = true;
    }
};

c_critical_section_scope::c_critical_section_scope(s_critical_section critical_section, long try_acquire_milliseconds, bool * out_lock_acquired)
{
    mangled_ppc("??0c_critical_section_scope@@QAA@Us_critical_section@@JPA_N@Z");

    m_critical_section = critical_section;
    m_lock_entered = false;

    unsigned long attempt_end_time = system_milliseconds() + try_acquire_milliseconds;
    assert_tag_debug_untracked_jul_11_2011(198, out_lock_acquired);

    *out_lock_acquired = false;

    do
    {
        m_lock_entered = critical_section_try_and_enter_internal(m_critical_section);

        if (m_lock_entered)
        {
            *out_lock_acquired = true;
            break;
        }
        else
        {
            thread_switch();
        }
    } while (system_milliseconds() < attempt_end_time);
};

c_critical_section_scope::~c_critical_section_scope(void)
{
    mangled_ppc("??1c_critical_section_scope@@QAA@XZ");

    if (m_lock_entered)
    {
        critical_section_leave_internal(m_critical_section, _critical_section_non_recursive);
    }
};
