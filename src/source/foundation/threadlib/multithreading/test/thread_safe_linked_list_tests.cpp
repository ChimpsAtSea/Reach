#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\multithreading\\test\\thread_safe_linked_list_tests.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\test\thread_safe_linked_list_tests.h"
#include "foundation\threadlib\multithreading\datatypes\thread_safe_linked_list.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "foundation\baselib\multithreading\threads\thread_wrappers.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

template<typename t_list>
struct s_thread_work_parameters
{
    t_list * source_list;
    t_list * destination_list;
};

template<typename t_type>
class c_validator
{
public:
    void visit(typename t_thread_safe_list<t_type>::s_list_element * head);

    t_type const * m_expected_data;
    long m_expected_count;
};

template<typename t_list>
class c_test_scoped_setup
{
public:
    c_test_scoped_setup(long synchronization_group_index, t_list * list);
    ~c_test_scoped_setup(void);

private:
    t_list * m_list;
};

/* ---------- prototypes */

void test_head_removal(void);
void test_default_ordering(void);
void test_custom_ordering(void);
void test_basic_thread_safety(void);
unsigned long thread_safe_list_test_worker_function(void * thread_parameters);
void test_manual_locking(void);
unsigned long thread_safe_list_pop_test_worker_function(void * thread_parameters);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 3>::k_element_count; // "?k_element_count@?$s_static_array@U?$s_thread_work_parameters@V?$t_thread_safe_list@J@@@@$02@@2JB"
// public: static long const s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 2>::k_element_count; // "?k_element_count@?$s_static_array@U?$s_thread_work_parameters@V?$t_thread_safe_list@J@@@@$01@@2JB"

// void thread_safe_linked_list_run_unit_test(void);
// void test_head_removal(void);
// void test_default_ordering(void);
// void test_custom_ordering(void);
// void test_basic_thread_safety(void);
// unsigned long thread_safe_list_test_worker_function(void *);
// public: c_thread_crew::~c_thread_crew(void);
// public: s_static_array<class c_thread_wrapper, 16>::~s_static_array<class c_thread_wrapper, 16>(void);
// public: virtual c_thread_wrapper::~c_thread_wrapper(void);
// void test_manual_locking(void);
// unsigned long thread_safe_list_pop_test_worker_function(void *);
// public: struct s_thread_work_parameters<class t_thread_safe_list<long> > * s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 3>::get_elements(void);
// public: static unsigned int s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 3>::get_element_size(void);
// public: struct s_thread_work_parameters<class t_thread_safe_list<long> > * s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 2>::get_elements(void);
// public: static unsigned int s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 2>::get_element_size(void);
// public: t_thread_safe_list<long>::t_thread_safe_list<long>(void);
// public: t_thread_safe_list<long>::~t_thread_safe_list<long>(void);
// public: void t_thread_safe_list<long>::add_element_to_front(struct t_thread_safe_list<long>::s_list_element *);
// public: bool t_thread_safe_list<long>::is_empty(void);
// public: struct t_thread_safe_list<long>::s_list_element * t_thread_safe_list<long>::get_and_remove_head_element(void);
// public: void t_thread_safe_list<long>::lock(void);
// public: void t_thread_safe_list<long>::unlock(void);
// public: bool t_thread_safe_list<long>::remove_element_assumes_locked(struct t_thread_safe_list<long>::s_list_element *);
// public: void t_thread_safe_list<long>::add_element_ordered<class c_list_comparer_ordered<long> >(struct t_thread_safe_list<long>::s_list_element *, class c_list_comparer_ordered<long> &);
// public: c_test_scoped_setup<class t_thread_safe_list<long> >::c_test_scoped_setup<class t_thread_safe_list<long> >(long, class t_thread_safe_list<long> *);
// public: c_test_scoped_setup<class t_thread_safe_list<long> >::~c_test_scoped_setup<class t_thread_safe_list<long> >(void);
// public: void t_thread_safe_list<long>::visit_list<class c_validator<long> >(class c_validator<long> *);
// public: struct s_thread_work_parameters<class t_thread_safe_list<long> > & s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 3>::operator[]<long>(long);
// public: struct s_thread_work_parameters<class t_thread_safe_list<long> > & s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 2>::operator[]<long>(long);
// public: void t_thread_safe_list<long>::add_element_ordered_assumes_locked<class c_list_comparer_ordered<long> >(struct t_thread_safe_list<long>::s_list_element *, class c_list_comparer_ordered<long> &);
// public: bool c_list_comparer_ordered<long>::operator()(long const &, long const &);
// public: void t_thread_safe_list<long>::initialize(struct s_critical_section);
// public: void t_thread_safe_list<long>::dispose(void);
// public: void c_validator<long>::visit(struct t_thread_safe_list<long>::s_list_element *);
// public: static bool s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 3>::valid<long>(long);
// public: static bool s_static_array<struct s_thread_work_parameters<class t_thread_safe_list<long> >, 2>::valid<long>(long);

void thread_safe_linked_list_run_unit_test(void)
{
    mangled_ppc("?thread_safe_linked_list_run_unit_test@@YAXXZ");

    test_head_removal();
    test_default_ordering();
    test_custom_ordering();
    test_basic_thread_safety();
    test_manual_locking();
};

void test_head_removal(void)
{
    mangled_ppc("?test_head_removal@@YAXXZ");

    long synchronization_group_index = synchronization_declare_object_group();
    long data[] = { 1, 2, 3, 4 };
    t_thread_safe_list<long>::s_list_element elements[NUMBEROF(data)];
    t_thread_safe_list<long> safe_list;
    {
        c_test_scoped_setup<t_thread_safe_list<long> > setup(synchronization_group_index, &safe_list);
        synchronization_create_object_group(synchronization_group_index);

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            elements[element_index].data = data[element_index];
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            safe_list.add_element_to_front(&elements[element_index]);
        }

        assert_tag_debug_untracked_jul_11_2011(197, !safe_list.is_empty());
        assert_tag_debug_untracked_jul_11_2011(198, safe_list.get_and_remove_head_element()->data==4);

        assert_tag_debug_untracked_jul_11_2011(200, !safe_list.is_empty());
        assert_tag_debug_untracked_jul_11_2011(201, safe_list.get_and_remove_head_element()->data==3);

        assert_tag_debug_untracked_jul_11_2011(203, !safe_list.is_empty());
        assert_tag_debug_untracked_jul_11_2011(204, safe_list.get_and_remove_head_element()->data==2);

        assert_tag_debug_untracked_jul_11_2011(206, !safe_list.is_empty());
        assert_tag_debug_untracked_jul_11_2011(207, safe_list.get_and_remove_head_element()->data==1);

        assert_tag_debug_untracked_jul_11_2011(210, safe_list.is_empty());
    }
    synchronization_destroy_object_group(synchronization_group_index);
};

void test_default_ordering(void)
{
    mangled_ppc("?test_default_ordering@@YAXXZ");

    long synchronization_group_index = synchronization_declare_object_group();
    long data[] = { 1, 2, 3, 4 };
    long expected_data[] = { 4, 3, 2, 1 };
    t_thread_safe_list<long>::s_list_element elements[NUMBEROF(data)];
    t_thread_safe_list<long> safe_list;
    {
        c_test_scoped_setup<t_thread_safe_list<long> > setup(synchronization_group_index, &safe_list);
        synchronization_create_object_group(synchronization_group_index);

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            elements[element_index].data = data[element_index];
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            safe_list.add_element_to_front(&elements[element_index]);
        }

        c_validator<long> validator = { expected_data, NUMBEROF(expected_data) };
        safe_list.visit_list(&validator);
    }
    synchronization_destroy_object_group(synchronization_group_index);
};

void test_custom_ordering(void)
{
    mangled_ppc("?test_custom_ordering@@YAXXZ");

    long synchronization_group_index = synchronization_declare_object_group();
    long data[] = { 3, 1, 4, 2, 5 };
    long expected_data[] = { 1, 2, 3, 4, 5 };
    t_thread_safe_list<long>::s_list_element elements[NUMBEROF(data)];
    t_thread_safe_list<long> safe_list;
    {
        c_test_scoped_setup<t_thread_safe_list<long> > setup(synchronization_group_index, &safe_list);
        synchronization_create_object_group(synchronization_group_index);

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            elements[element_index].data = data[element_index];
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            c_list_comparer_ordered<long> comparer;
            safe_list.add_element_ordered(&elements[element_index], comparer);
        }

        c_validator<long> validator = { expected_data, NUMBEROF(expected_data) };
        safe_list.visit_list(&validator);
    }
    synchronization_destroy_object_group(synchronization_group_index);
};

void test_basic_thread_safety(void)
{
    mangled_ppc("?test_basic_thread_safety@@YAXXZ");

    long synchronization_group_index = synchronization_declare_object_group();
    long data[] = { 21, 1, 18, 2, 4, 15, 5, 7, 12, 8, 10, 9, 11, 13, 14, 6, 16, 17, 3, 19, 20 };
    long expected_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };
    t_thread_safe_list<long>::s_list_element elements[NUMBEROF(data)];
    t_thread_safe_list<long> source_list;
    t_thread_safe_list<long> sorted_list;
    {
        c_test_scoped_setup<t_thread_safe_list<long> > source_list_scoped_setup(synchronization_group_index, &source_list);
        c_test_scoped_setup<t_thread_safe_list<long> > sorted_list_setup(synchronization_group_index, &sorted_list);
        synchronization_create_object_group(synchronization_group_index);

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            elements[element_index].data = data[element_index];
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            source_list.add_element_to_front(&elements[element_index]);
        }

        long const crew_size = 3;
        c_thread_crew crew;
        s_static_array<s_thread_work_parameters<t_thread_safe_list<long> >, crew_size> thread_parameters;
        for (long thread_index = 0; thread_index < crew_size; thread_index++)
        {
            thread_parameters[thread_index].source_list = &source_list;
            thread_parameters[thread_index].destination_list = &sorted_list;
        }

        crew.setup_array("test thread safe list", crew_size, thread_safe_list_test_worker_function, thread_parameters.get_elements(), thread_parameters.get_element_size());
        crew.start();
        crew.wait();

        c_validator<long> validator = { expected_data, NUMBEROF(expected_data) };
        assert_tag_debug_untracked_jul_11_2011(345, source_list.is_empty());
        sorted_list.visit_list(&validator);
    }
    synchronization_destroy_object_group(synchronization_group_index);
};

unsigned long thread_safe_list_test_worker_function(void * thread_parameters)
{
    mangled_ppc("?thread_safe_list_test_worker_function@@YAKPAX@Z");

    s_thread_work_parameters<t_thread_safe_list<long> > * parameters = static_cast<s_thread_work_parameters<t_thread_safe_list<long> > *>(thread_parameters);
    t_thread_safe_list<long>::s_list_element * list_element = parameters->source_list->get_and_remove_head_element();
    while (list_element != NULL)
    {
        c_list_comparer_ordered<long> comparer;
        parameters->destination_list->add_element_ordered(list_element, comparer);
        list_element = parameters->source_list->get_and_remove_head_element();
    }

    return 0;
};

void test_manual_locking(void)
{
    mangled_ppc("?test_manual_locking@@YAXXZ");

    long synchronization_group_index = synchronization_declare_object_group();
    long data[] = { 21, 1, 18, 2, 4, 15, 5, 7, 12, 8, 10, 9, 11, 13, 14, 6, 16, 17, 3, 19, 20 };
    t_thread_safe_list<long>::s_list_element elements[NUMBEROF(data)];
    t_thread_safe_list<long> source_list;
    {
        c_test_scoped_setup<t_thread_safe_list<long> > source_list_scoped_setup(synchronization_group_index, &source_list);
        synchronization_create_object_group(synchronization_group_index);

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            elements[element_index].data = data[element_index];
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            c_list_comparer_ordered<long> comparer;
            source_list.add_element_ordered(&elements[element_index], comparer);
        }

        long const crew_size = 2;
        c_thread_crew crew;
        s_static_array<s_thread_work_parameters<t_thread_safe_list<long> >, crew_size> thread_parameters;
        for (long thread_index = 0; thread_index < crew_size; thread_index++)
        {
            thread_parameters[thread_index].source_list = &source_list;
            thread_parameters[thread_index].destination_list = NULL;
        }

        crew.setup_array("test thread safe list", crew_size, thread_safe_list_pop_test_worker_function, thread_parameters.get_elements(), thread_parameters.get_element_size());

        source_list.lock();
        crew.start();

        bool element_removed = false;
        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            element_removed = source_list.remove_element_assumes_locked(&elements[element_index]);
            assert_tag_debug_untracked_jul_11_2011(406, element_removed);
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            c_list_comparer_ordered<long> comparer;
            source_list.add_element_ordered_assumes_locked(&elements[element_index], comparer);
        }

        for (unsigned long element_index = 0; element_index < NUMBEROF(data); element_index++)
        {
            element_removed = source_list.remove_element_assumes_locked(&elements[element_index]);
            assert_tag_debug_untracked_jul_11_2011(421, element_removed);
        }

        source_list.unlock();
        crew.wait();

        assert_tag_debug_untracked_jul_11_2011(431, source_list.is_empty());
    }
    synchronization_destroy_object_group(synchronization_group_index);
};

unsigned long thread_safe_list_pop_test_worker_function(void * thread_parameters)
{
    mangled_ppc("?thread_safe_list_pop_test_worker_function@@YAKPAX@Z");

    long const pop_count = 50;
    s_thread_work_parameters<t_thread_safe_list<long> > * parameters = static_cast<s_thread_work_parameters<t_thread_safe_list<long> > *>(thread_parameters);
    for (long pop_index = 0; pop_index < pop_count; pop_index++)
    {
        parameters->source_list->get_and_remove_head_element();
    }

    return 0;
};

template<typename t_list>
c_test_scoped_setup<t_list>::c_test_scoped_setup(long synchronization_group_index, t_list * list) :
    m_list(list)
{
    mangled_ppc("??0?$c_test_scoped_setup@V?$t_thread_safe_list@J@@@@QAA@JPAV?$t_thread_safe_list@J@@@Z");

    s_critical_section_definition definition = { "CS: threadlib unit tests", 0, false, false };
    s_critical_section critical_section = critical_section_declare(synchronization_group_index, &definition);
    m_list->initialize(critical_section);
};

template<typename t_list>
c_test_scoped_setup<t_list>::~c_test_scoped_setup(void)
{
    mangled_ppc("??1?$c_test_scoped_setup@V?$t_thread_safe_list@J@@@@QAA@XZ");

    m_list->dispose();
};

template<typename t_type>
void c_validator<t_type>::visit(typename t_thread_safe_list<t_type>::s_list_element * head)
{
    mangled_ppc("?visit@?$c_validator@J@@QAAXPAUs_list_element@?$t_thread_safe_list@J@@@Z");

    long list_count = 0;
    typename t_thread_safe_list<t_type>::s_list_element * current;
    current = head;
    while (current != NULL)
    {
        list_count++;
        current = current->next;
    }
    assert_tag_debug_untracked_jul_11_2011(117, list_count==m_expected_count);

    long list_index = 0;
    current = head;
    while (current != NULL)
    {
        assert_tag_debug_untracked_jul_11_2011(124, m_expected_data[list_index]==current->data);
        list_index++;
        current = current->next;
    }
};
