#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\multithreading\\test\\lockfree_event_queue_tests.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\test\lockfree_event_queue_tests.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\multithreading\datatypes\lockfree_event_queue.h"

/* ---------- constants */

/* ---------- definitions */

struct s_test_event :
    s_synchronized_list_entry
{
    long payload;
    long pad[2];
};
static_assert(sizeof(s_test_event) == 0x10, "s_test_event");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_test_event, 32>::k_element_count; // "?k_element_count@?$s_static_array@Us_test_event@@$0CA@@@2JB"
// public: static long const s_static_array<struct s_synchronized_list_entry *, 32>::k_element_count; // "?k_element_count@?$s_static_array@PAUs_synchronized_list_entry@@$0CA@@@2JB"

// void lockfree_event_queue_run_unit_test(void);
// public: t_event_queue<struct s_test_event, 32>::t_event_queue<struct s_test_event, 32>(void);
// public: t_event_queue<struct s_test_event, 32>::~t_event_queue<struct s_test_event, 32>(void);
// public: void t_event_queue<struct s_test_event, 32>::initialize(void);
// public: void t_event_queue<struct s_test_event, 32>::set_name(char const *);
// public: void t_event_queue<struct s_test_event, 32>::dispose(void);
// public: void t_event_queue<struct s_test_event, 32>::reset(void);
// public: long t_event_queue<struct s_test_event, 32>::peek_pending_count(void) const;
// public: struct s_test_event * t_event_queue<struct s_test_event, 32>::allocate_event(void);
// public: void t_event_queue<struct s_test_event, 32>::queue_event(struct s_test_event *);
// public: struct s_test_event * t_event_queue<struct s_test_event, 32>::acquire_top_event(void);
// public: struct s_test_event * t_event_queue<struct s_test_event, 32>::acquire_event_chain(enum e_event_queue_chain_order);
// public: struct s_test_event * t_event_queue<struct s_test_event, 32>::release_chain_top_event(struct s_test_event *);
// public: struct s_test_event * t_event_queue<struct s_test_event, 32>::requeue_chain_top_event(struct s_test_event *);
// public: void t_event_queue<struct s_test_event, 32>::initialize_limited(long);
// public: bool t_event_queue<struct s_test_event, 32>::valid_event(void const *) const;
// public: void t_event_queue<struct s_test_event, 32>::assert_valid_chain(struct s_synchronized_list_entry *) const;
// public: static long s_static_array<struct s_test_event, 32>::get_count(void);
// public: struct s_synchronized_list_entry ** s_static_array<struct s_synchronized_list_entry *, 32>::get_elements(void);
// public: struct s_test_event & s_static_array<struct s_test_event, 32>::operator[]<long>(long);
// public: struct s_synchronized_list_entry *& s_static_array<struct s_synchronized_list_entry *, 32>::operator[]<long>(long);
// public: struct s_test_event const & s_static_array<struct s_test_event, 32>::operator[]<int>(int) const;
// public: struct s_test_event const & s_static_array<struct s_test_event, 32>::operator[]<long>(long) const;
// public: static bool s_static_array<struct s_test_event, 32>::valid<long>(long);
// public: static bool s_static_array<struct s_synchronized_list_entry *, 32>::valid<long>(long);
// public: static bool s_static_array<struct s_test_event, 32>::valid<int>(int);

void lockfree_event_queue_run_unit_test(void)
{
    mangled_ppc("?lockfree_event_queue_run_unit_test@@YAXXZ");

    t_event_queue<s_test_event, 32> event_queue;

    event_queue.initialize();
    event_queue.set_name("test-event-queue");

    {
        s_test_event * event = event_queue.allocate_event();
        assert_tag_debug_untracked_jul_11_2011(39, event);

        event->payload = 5;
        event_queue.queue_event(event);
        assert_tag_debug_untracked_jul_11_2011(42, event_queue.peek_pending_count()==1);
    }

    {
        s_test_event * event = event_queue.acquire_top_event();
        assert_tag_debug_untracked_jul_11_2011(48, event);
        assert_tag_debug_untracked_jul_11_2011(49, event->payload==5);
        assert_tag_debug_untracked_jul_11_2011(50, event_queue.peek_pending_count()==0);

        event = event_queue.release_chain_top_event(event);
        assert_tag_debug_untracked_jul_11_2011(52, event==NULL);

        event = event_queue.acquire_top_event();
        assert_tag_debug_untracked_jul_11_2011(55, event==NULL);
    }

    {
        s_test_event * event1 = event_queue.allocate_event();
        s_test_event * event2 = event_queue.allocate_event();
        assert_tag_debug_untracked_jul_11_2011(65, event1);
        assert_tag_debug_untracked_jul_11_2011(66, event2);

        event1->payload = 9;
        event2->payload = 10;
        event_queue.queue_event(event1);
        event_queue.queue_event(event2);
        assert_tag_debug_untracked_jul_11_2011(71, event_queue.peek_pending_count()==2);
    }

    {
        s_test_event * event_chain = event_queue.acquire_event_chain(_event_queue_chain_order_fifo);
        assert_tag_debug_untracked_jul_11_2011(77, event_chain);
        assert_tag_debug_untracked_jul_11_2011(78, event_chain->payload==9);

        event_chain = event_queue.requeue_chain_top_event(event_chain);
        assert_tag_debug_untracked_jul_11_2011(81, event_chain);
        assert_tag_debug_untracked_jul_11_2011(82, event_chain->payload==10);

        event_chain = event_queue.requeue_chain_top_event(event_chain);
        assert_tag_debug_untracked_jul_11_2011(85, event_chain==NULL);
        assert_tag_debug_untracked_jul_11_2011(86, event_queue.peek_pending_count()==2);
    }

    {
        s_test_event * event_chain = event_queue.acquire_event_chain(_event_queue_chain_order_lifo);
        assert_tag_debug_untracked_jul_11_2011(92, event_chain);
        assert_tag_debug_untracked_jul_11_2011(93, event_chain->payload==10);

        event_chain = event_queue.release_chain_top_event(event_chain);
        assert_tag_debug_untracked_jul_11_2011(96, event_chain);
        assert_tag_debug_untracked_jul_11_2011(97, event_chain->payload==9);

        event_chain = event_queue.release_chain_top_event(event_chain);
        assert_tag_debug_untracked_jul_11_2011(100, event_chain==NULL);
        assert_tag_debug_untracked_jul_11_2011(101, event_queue.acquire_top_event()==NULL);
        assert_tag_debug_untracked_jul_11_2011(102, event_queue.peek_pending_count()==0);
    }

    {
        s_test_event * event = event_queue.allocate_event();
        assert_tag_debug_untracked_jul_11_2011(110, event);

        event->payload = 12;
        event_queue.queue_event(event);
        assert_tag_debug_untracked_jul_11_2011(113, event_queue.peek_pending_count()==1);

        event_queue.reset();
        assert_tag_debug_untracked_jul_11_2011(116, event_queue.acquire_top_event()==NULL);
        assert_tag_debug_untracked_jul_11_2011(117, event_queue.peek_pending_count()==0);
    }

    event_queue.dispose();
};
