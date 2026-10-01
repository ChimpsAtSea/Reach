#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\synchronization_object.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

#include "core\corelib\cseries\cseries_asserts.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "foundation\baselib\multithreading\synchronization\mutex_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: long c_synchronization_object::get_synchronization_group_index(void) const;
// public: char const * c_synchronization_object::get_name(void) const;
// public: void c_synchronization_object::acquire_prerequisites(void) const;
// public: void c_synchronization_object::release_prerequisites(void) const;
// public: unsigned long * s_static_array<unsigned long, 8>::get_elements(void);

long c_synchronization_object::get_synchronization_group_index(void) const
{
    mangled_ppc("?get_synchronization_group_index@c_synchronization_object@@QBAJXZ");

    return SYNCHRONIZATION_OBJECT_GROUP(m_object_id);
};

char const * c_synchronization_object::get_name(void) const
{
    mangled_ppc("?get_name@c_synchronization_object@@QBAPBDXZ");

    return synchronization_object_get_name(m_object_id);
};

void c_synchronization_object::acquire_prerequisites(void) const
{
    mangled_ppc("?acquire_prerequisites@c_synchronization_object@@QBAXXZ");

    if (m_lock_node_index != NONE)
    {
        c_lock_hierarchy const * lock_hierarchy = synchronization_get_lock_hierarchy_const();
        s_static_array<unsigned long, 8> prerequisites;
        long prerequisites_count = lock_hierarchy->query_prerequisites(m_lock_node_index, prerequisites.get_count(), NULL, prerequisites.get_elements());
        for (long prerequisite_index = 0; prerequisite_index < prerequisites_count; prerequisite_index++)
        {
            unsigned long object_id = prerequisites[prerequisite_index];
            long object_type = SYNCHRONIZATION_OBJECT_TYPE(object_id);
            switch (object_type)
            {
            case _synchronization_object_critical_section:
            {
                s_critical_section critical_section = { object_id };
                critical_section_enter_internal(critical_section, _critical_section_recursive);
            }
            break;
            case _synchronization_object_mutex:
            {
                s_mutex mutex = { object_id };
                mutex_take_internal(mutex, _mutex_recursive);
            }
            break;
            default:
            {
                dassert_tag_debug_untracked_jul_11_2011(70, false, "unreachable");
            }
            break;
            }
        }
    }
};

void c_synchronization_object::release_prerequisites(void) const
{
    mangled_ppc("?release_prerequisites@c_synchronization_object@@QBAXXZ");

    if (m_lock_node_index != NONE)
    {
        c_lock_hierarchy const * lock_hierarchy = synchronization_get_lock_hierarchy_const();
        s_static_array<unsigned long, 8> prerequisites;
        long prerequisites_count = lock_hierarchy->query_prerequisites(m_lock_node_index, prerequisites.get_count(), NULL, prerequisites.get_elements());
        for (long prerequisite_index = prerequisites_count - 1; prerequisite_index >= 0; prerequisite_index--)
        {
            unsigned long object_id = prerequisites[prerequisite_index];
            long object_type = SYNCHRONIZATION_OBJECT_TYPE(object_id);
            switch (object_type)
            {
            case _synchronization_object_critical_section:
            {
                s_critical_section critical_section = { object_id };
                critical_section_leave_internal(critical_section, _critical_section_recursive);
            }
            break;
            case _synchronization_object_mutex:
            {
                s_mutex mutex = { object_id };
                mutex_release_internal(mutex, _mutex_recursive);
            }
            break;
            default:
            {
                dassert_tag_debug_untracked_jul_11_2011(111, false, "unreachable");
            }
            break;
            }
        }
    }
};
