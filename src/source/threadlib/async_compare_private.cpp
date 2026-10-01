/* ---------- headers */

#include "threadlib\async_compare_private.h"

#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\threadlib\async\async_setup.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_async_task_element_comparer::c_async_task_element_comparer(long);
// public: c_async_task_element_comparer::~c_async_task_element_comparer(void);
// public: bool c_async_task_element_comparer::operator()(struct s_async_task_element const &, struct s_async_task_element const &);

c_async_task_element_comparer::c_async_task_element_comparer(long thread_index) :
    m_thread_index(thread_index)
{
    mangled_ppc("??0c_async_task_element_comparer@@QAA@J@Z");

    csmemset(m_storage, 0, sizeof(m_storage));
};

c_async_task_element_comparer::~c_async_task_element_comparer(void)
{
    mangled_ppc("??1c_async_task_element_comparer@@QAA@XZ");

    s_async_task_compare_interface * compare_interface = async_setup_get_compare_interface_for_thread(m_thread_index);
    if (compare_interface != NULL && compare_interface->unknown8 != NULL)
    {
        compare_interface->unknown8(this);
    }
};

bool c_async_task_element_comparer::operator()(s_async_task_element const & a, s_async_task_element const & b)
{
    mangled_ppc("??Rc_async_task_element_comparer@@QAA_NABUs_async_task_element@@0@Z");

    bool result = true;
    s_async_task_compare_interface * compare_interface = async_setup_get_compare_interface_for_thread(m_thread_index);
    if (compare_interface != NULL && compare_interface->compare != NULL)
    {
        s_async_task_compare_element element0;
        s_async_task_compare_element element1;
        element0.priority = a.priority;
        element0.callback = a.callback;
        element0.task_data = a.task_data;
        element1.priority = b.priority;
        element1.callback = b.callback;
        element1.task_data = b.task_data;
        result = compare_interface->compare(this, &element0, &element1);
    }

    return result;
};

