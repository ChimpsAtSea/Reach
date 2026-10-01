/* ---------- headers */

/* ---------- constants */

#define LOCKFREE_EVENT_FIFO_INL_FILE "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\threadlib/multithreading/datatypes/lockfree_event_fifo.inl"

/* ---------- public code */

template<typename t_type, long k_maximum_count>
t_event_fifo<t_type, k_maximum_count>::t_event_fifo(void) :
    m_initialized(false)
{
}

template<typename t_type, long k_maximum_count>
t_event_fifo<t_type, k_maximum_count>::~t_event_fifo(void)
{
}

template<typename t_type, long k_maximum_count>
void t_event_fifo<t_type, k_maximum_count>::initialize(void)
{
    assert_decomp(!m_initialized, LOCKFREE_EVENT_FIFO_INL_FILE, 22);

    synchronized_list_initialize(&m_readable_lists[0]);
    synchronized_list_initialize(&m_readable_lists[1]);
    synchronized_list_initialize(&m_writable_list);

    for (long event_index = 0; event_index < m_events.get_count(); event_index++)
    {
        synchronized_list_entry_clear(&m_events[event_index].list_entry);
    }

    {
        long entry_count = 0;
        s_static_array<s_synchronized_list_entry *, k_maximum_count> entries;

        for (long event_index = 0; event_index < m_events.get_count(); event_index++)
        {
            entries[entry_count++] = &m_events[event_index].list_entry;
        }

        synchronized_list_push_multiple(&m_writable_list, entry_count, entries.get_elements());
    }

    m_initialized = true;
}

template<typename t_type, long k_maximum_count>
void t_event_fifo<t_type, k_maximum_count>::dispose(void)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_FIFO_INL_FILE, 55);

    reset();
    m_initialized = false;
}

template<typename t_type, long k_maximum_count>
void t_event_fifo<t_type, k_maximum_count>::reset(void)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_FIFO_INL_FILE, 68);

    for (long list_index = 0; list_index < k_readable_list_count; list_index++)
    {
        s_synchronized_list_entry * entry = synchronized_list_flush(&m_readable_lists[list_index]);
        s_synchronized_list_entry * next;

        while (entry != NULL)
        {
            next = synchronized_list_entry_set(entry, NULL);
            synchronized_list_push(&m_writable_list, entry);
            entry = next;
        }
    }
}

template<typename t_type, long k_maximum_count>
long t_event_fifo<t_type, k_maximum_count>::peek_pending_count(void) const
{
    long pending_count = 0;

    assert_decomp(m_initialized, LOCKFREE_EVENT_FIFO_INL_FILE, 94);

    for (long list_index = 0; list_index < k_readable_list_count; list_index++)
    {
        pending_count += synchronized_list_get_count(const_cast<s_synchronized_list_header *>(&m_readable_lists[list_index]));
    }

    return pending_count;
}

template<typename t_type, long k_maximum_count>
t_type * t_event_fifo<t_type, k_maximum_count>::get_next_readable_event(void)
{
    t_type * result = NULL;
    s_synchronized_list_entry * entry_chain = synchronized_list_flush(&m_readable_lists[0]);

    if (entry_chain == NULL)
    {
        entry_chain = synchronized_list_flush(&m_readable_lists[1]);
    }

    if (entry_chain != NULL)
    {
        s_synchronized_list_entry * current = entry_chain;
        s_synchronized_list_entry * previous = NULL;
        s_synchronized_list_entry * next = NULL;

        while (current != NULL)
        {
            next = synchronized_list_entry_set(current, previous);
            previous = current;
            current = next;
        }

        result = reinterpret_cast<t_type *>(previous);
        current = synchronized_list_entry_set(previous, NULL);

        assert_decomp(valid_event(result), LOCKFREE_EVENT_FIFO_INL_FILE, 137);
        assert_decomp(synchronized_list_entry_next(&result->list_entry)==NULL, LOCKFREE_EVENT_FIFO_INL_FILE, 138);

        while (current != NULL)
        {
            next = synchronized_list_entry_next(current);
            synchronized_list_push(&m_readable_lists[0], current);
            current = next;
        }
    }

    return result;
}

template<typename t_type, long k_maximum_count>
t_type * t_event_fifo<t_type, k_maximum_count>::get_next_writable_event(void)
{
    s_synchronized_list_entry * entry = synchronized_list_pop(&m_writable_list);
    t_type * event = reinterpret_cast<t_type *>(entry);

    assert_decomp(event==NULL || valid_event(event), LOCKFREE_EVENT_FIFO_INL_FILE, 161);

    return event;
}

template<typename t_type, long k_maximum_count>
void t_event_fifo<t_type, k_maximum_count>::queue_readable_event(t_type * event)
{
    assert_decomp(valid_event(event), LOCKFREE_EVENT_FIFO_INL_FILE, 172);

    synchronized_list_push(&m_readable_lists[1], &event->list_entry);
}

template<typename t_type, long k_maximum_count>
void t_event_fifo<t_type, k_maximum_count>::queue_writable_event(t_type * event)
{
    assert_decomp(valid_event(event), LOCKFREE_EVENT_FIFO_INL_FILE, 181);

    synchronized_list_push(&m_writable_list, &event->list_entry);
}

template<typename t_type, long k_maximum_count>
bool t_event_fifo<t_type, k_maximum_count>::valid_event(t_type const * event) const
{
    bool valid = true;

    valid = valid && m_initialized;
    valid = valid && event != NULL;
    valid = valid && event >= &m_events[0];
    valid = valid && event <= &m_events[m_events.get_count() - 1];
    valid = valid && pointer_is_aligned(event, 4);

    return valid;
}

#undef LOCKFREE_EVENT_FIFO_INL_FILE
