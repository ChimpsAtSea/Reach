#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\threadlib\multithreading\test\lockfree_event_fifo_tests.cpp"
/* ---------- headers */

#include "foundation\threadlib\multithreading\test\lockfree_event_fifo_tests.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\multithreading\datatypes\lockfree_event_fifo.h"

/* ---------- constants */

/* ---------- definitions */

struct s_test_event
{
    s_synchronized_list_entry list_entry;
    long payload;
    long pad[2];
};
static_assert(sizeof(s_test_event) == 0x10, "s_test_event");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void lockfree_event_fifo_run_unit_test(void);
// public: t_event_fifo<struct s_test_event, 32>::t_event_fifo<struct s_test_event, 32>(void);
// public: t_event_fifo<struct s_test_event, 32>::~t_event_fifo<struct s_test_event, 32>(void);
// public: void t_event_fifo<struct s_test_event, 32>::initialize(void);
// public: void t_event_fifo<struct s_test_event, 32>::dispose(void);
// public: void t_event_fifo<struct s_test_event, 32>::reset(void);
// public: long t_event_fifo<struct s_test_event, 32>::peek_pending_count(void) const;
// public: struct s_test_event * t_event_fifo<struct s_test_event, 32>::get_next_readable_event(void);
// public: struct s_test_event * t_event_fifo<struct s_test_event, 32>::get_next_writable_event(void);
// public: void t_event_fifo<struct s_test_event, 32>::queue_readable_event(struct s_test_event *);
// public: void t_event_fifo<struct s_test_event, 32>::queue_writable_event(struct s_test_event *);
// public: bool t_event_fifo<struct s_test_event, 32>::valid_event(struct s_test_event const *) const;

void lockfree_event_fifo_run_unit_test(void)
{
    mangled_ppc("?lockfree_event_fifo_run_unit_test@@YAXXZ");

    t_event_fifo<s_test_event, 32> fifo;

    fifo.initialize();

    assert_tag_debug_untracked_jul_11_2011(35, fifo.get_next_readable_event()==NULL);

    {
        s_test_event * event = fifo.get_next_writable_event();
        assert_tag_debug_untracked_jul_11_2011(40, event);

        event->payload = 5;
        fifo.queue_readable_event(event);
        assert_tag_debug_untracked_jul_11_2011(43, fifo.peek_pending_count()==1);
    }

    {
        s_test_event * event = fifo.get_next_readable_event();
        assert_tag_debug_untracked_jul_11_2011(49, event);
        assert_tag_debug_untracked_jul_11_2011(50, event->payload==5);
        assert_tag_debug_untracked_jul_11_2011(51, fifo.peek_pending_count()==0);

        fifo.queue_writable_event(event);
        event = fifo.get_next_readable_event();
        assert_tag_debug_untracked_jul_11_2011(55, event==NULL);
    }

    {
        s_test_event * event1 = fifo.get_next_writable_event();
        s_test_event * event2 = fifo.get_next_writable_event();
        s_test_event * event3 = fifo.get_next_writable_event();
        assert_tag_debug_untracked_jul_11_2011(66, event1);
        assert_tag_debug_untracked_jul_11_2011(67, event2);
        assert_tag_debug_untracked_jul_11_2011(68, event3);

        event1->payload = 9;
        event2->payload = 10;
        event3->payload = 11;
        fifo.queue_readable_event(event1);
        fifo.queue_readable_event(event2);
        fifo.queue_readable_event(event3);
        assert_tag_debug_untracked_jul_11_2011(75, fifo.peek_pending_count()==3);
    }

    {
        s_test_event * event = fifo.get_next_readable_event();
        assert_tag_debug_untracked_jul_11_2011(81, event);
        assert_tag_debug_untracked_jul_11_2011(82, event->payload==9);
        fifo.queue_writable_event(event);

        event = fifo.get_next_readable_event();
        assert_tag_debug_untracked_jul_11_2011(86, event);
        assert_tag_debug_untracked_jul_11_2011(87, event->payload==10);
        fifo.queue_writable_event(event);

        event = fifo.get_next_readable_event();
        assert_tag_debug_untracked_jul_11_2011(91, event);
        assert_tag_debug_untracked_jul_11_2011(92, event->payload==11);
        fifo.queue_writable_event(event);

        assert_tag_debug_untracked_jul_11_2011(95, fifo.peek_pending_count()==0);
    }

    {
        s_test_event * event1 = fifo.get_next_writable_event();
        s_test_event * event2 = fifo.get_next_writable_event();
        assert_tag_debug_untracked_jul_11_2011(105, event1);
        assert_tag_debug_untracked_jul_11_2011(106, event2);

        event1->payload = 19;
        event2->payload = 20;
        fifo.queue_readable_event(event2);
        fifo.queue_readable_event(event1);
        assert_tag_debug_untracked_jul_11_2011(113, fifo.peek_pending_count()==2);
    }

    {
        s_test_event * read_event1 = fifo.get_next_readable_event();
        s_test_event * read_event2 = fifo.get_next_readable_event();

        assert_tag_debug_untracked_jul_11_2011(121, read_event2);
        assert_tag_debug_untracked_jul_11_2011(122, read_event2->payload==19);
        fifo.queue_writable_event(read_event2);

        assert_tag_debug_untracked_jul_11_2011(125, read_event1);
        assert_tag_debug_untracked_jul_11_2011(126, read_event1->payload==20);
        fifo.queue_writable_event(read_event1);

        assert_tag_debug_untracked_jul_11_2011(129, fifo.peek_pending_count()==0);
    }

    {
        s_test_event * event = fifo.get_next_writable_event();
        assert_tag_debug_untracked_jul_11_2011(137, event);

        event->payload = 12;
        fifo.queue_readable_event(event);
        assert_tag_debug_untracked_jul_11_2011(140, fifo.peek_pending_count()==1);

        fifo.reset();
        assert_tag_debug_untracked_jul_11_2011(143, fifo.get_next_readable_event()==NULL);
        assert_tag_debug_untracked_jul_11_2011(144, fifo.peek_pending_count()==0);
    }

    fifo.dispose();
};

