/* ---------- headers */

/* ---------- constants */

#define LOCKFREE_EVENT_QUEUE_INL_FILE "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib/multithreading/datatypes/lockfree_event_queue.inl"

/* ---------- public code */

template<typename t_type, long k_maximum_count>
t_event_queue<t_type, k_maximum_count>::t_event_queue(void) :
    m_initialized(false),
    m_limit_count(0),
    m_name(NULL)
{
}

template<typename t_type, long k_maximum_count>
t_event_queue<t_type, k_maximum_count>::~t_event_queue(void)
{
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::initialize_limited(long limit_count)
{
    assert_decomp(!m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 39);
    assert_decomp(VALID_COUNT(limit_count, k_maximum_count), LOCKFREE_EVENT_QUEUE_INL_FILE, 40);

    synchronized_list_initialize(&m_pending_list);
    synchronized_list_initialize(&m_free_list);

    for (long event_index = 0; event_index < m_events.get_count(); event_index++)
    {
        synchronized_list_entry_clear(&m_events[event_index]);
    }

    m_initialized = true;
    m_limit_count = limit_count;

    if (m_limit_count != 0)
    {
        long entry_count = 0;
        s_static_array<s_synchronized_list_entry *, k_maximum_count> entries;

        for (long event_index = m_limit_count - 1; event_index >= 0; event_index--)
        {
            entries[entry_count++] = &m_events[event_index];
        }

        synchronized_list_push_multiple(&m_free_list, entry_count, entries.get_elements());
    }
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::initialize(void)
{
    initialize_limited(k_maximum_count);
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::set_name(char const * name)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 74);

    m_name = name;
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::dispose(void)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 84);

    reset();
    m_initialized = false;
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::reset(void)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 94);

    t_type * event_chain = acquire_event_chain(_event_queue_chain_order_lifo);
    while (event_chain != NULL)
    {
        event_chain = release_chain_top_event(event_chain);
    }
}

template<typename t_type, long k_maximum_count>
long t_event_queue<t_type, k_maximum_count>::peek_pending_count(void) const
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 112);

    return synchronized_list_get_count(const_cast<s_synchronized_list_header *>(&m_pending_list));
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::assert_valid_chain(s_synchronized_list_entry * chain) const
{
    for (s_synchronized_list_entry * entry = chain; entry != NULL; entry = synchronized_list_entry_next(entry))
    {
        t_type * test_event = static_cast<t_type *>(entry);
        assert_decomp(valid_event(test_event), LOCKFREE_EVENT_QUEUE_INL_FILE, 160);
    }
}

template<typename t_type, long k_maximum_count>
t_type * t_event_queue<t_type, k_maximum_count>::allocate_event(void)
{
    s_synchronized_list_entry * new_entry = NULL;
    long attempt_count = 0;

    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 175);

    while (new_entry == NULL)
    {
        new_entry = synchronized_list_pop(&m_free_list);
        attempt_count++;
        dassert_decomp(attempt_count < 1000000, "deadlock in t_event_queue::allocate_event?", LOCKFREE_EVENT_QUEUE_INL_FILE, 184);
    }

    t_type * new_event = static_cast<t_type *>(new_entry);
    assert_decomp(valid_event(new_event), LOCKFREE_EVENT_QUEUE_INL_FILE, 189);

    return new_event;
}

template<typename t_type, long k_maximum_count>
void t_event_queue<t_type, k_maximum_count>::queue_event(t_type * event)
{
    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 210);
    assert_decomp(valid_event(event), LOCKFREE_EVENT_QUEUE_INL_FILE, 211);

    synchronized_list_push(&m_pending_list, event);
}

template<typename t_type, long k_maximum_count>
t_type * t_event_queue<t_type, k_maximum_count>::acquire_top_event(void)
{
    s_synchronized_list_entry * entry = synchronized_list_pop(&m_pending_list);
    t_type * event = static_cast<t_type *>(entry);

    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 224);

    if (event != NULL)
    {
        assert_decomp(valid_event(event), LOCKFREE_EVENT_QUEUE_INL_FILE, 230);

        synchronized_list_entry_set(entry, NULL);
        assert_valid_chain(entry);
    }

    return event;
}

template<typename t_type, long k_maximum_count>
t_type * t_event_queue<t_type, k_maximum_count>::acquire_event_chain(e_event_queue_chain_order desired_order)
{
    s_synchronized_list_entry * entry_chain = synchronized_list_flush(&m_pending_list);
    t_type * event_chain = static_cast<t_type *>(entry_chain);

    assert_decomp(m_initialized, LOCKFREE_EVENT_QUEUE_INL_FILE, 248);
    assert_decomp(VALID_INDEX(desired_order, k_event_queue_chain_order_count), LOCKFREE_EVENT_QUEUE_INL_FILE, 249);

    if (event_chain != NULL)
    {
        assert_decomp(valid_event(event_chain), LOCKFREE_EVENT_QUEUE_INL_FILE, 253);
        assert_valid_chain(entry_chain);

        if (desired_order == _event_queue_chain_order_fifo)
        {
            s_synchronized_list_entry * current = entry_chain;
            s_synchronized_list_entry * previous = NULL;
            s_synchronized_list_entry * next = NULL;

            while (current != NULL)
            {
                next = synchronized_list_entry_next(current);
                synchronized_list_entry_set(current, previous);
                previous = current;
                current = next;
            }

            entry_chain = previous;
            event_chain = static_cast<t_type *>(entry_chain);

            assert_decomp(valid_event(event_chain), LOCKFREE_EVENT_QUEUE_INL_FILE, 275);
            assert_valid_chain(entry_chain);
        }
    }

    return event_chain;
}

template<typename t_type, long k_maximum_count>
t_type * t_event_queue<t_type, k_maximum_count>::release_chain_top_event(t_type * chain)
{
    s_synchronized_list_entry * entry = chain;
    s_synchronized_list_entry * next_entry = synchronized_list_entry_next(entry);
    t_type * next_event = static_cast<t_type *>(next_entry);

    assert_decomp(valid_event(chain), LOCKFREE_EVENT_QUEUE_INL_FILE, 292);
    assert_decomp(next_event==NULL || valid_event(next_event), LOCKFREE_EVENT_QUEUE_INL_FILE, 293);

    synchronized_list_push(&m_free_list, entry);

    return next_event;
}

template<typename t_type, long k_maximum_count>
t_type * t_event_queue<t_type, k_maximum_count>::requeue_chain_top_event(t_type * chain)
{
    s_synchronized_list_entry * entry = chain;
    s_synchronized_list_entry * next_entry = synchronized_list_entry_next(entry);
    t_type * next_event = static_cast<t_type *>(next_entry);

    assert_decomp(valid_event(chain), LOCKFREE_EVENT_QUEUE_INL_FILE, 308);
    assert_decomp(next_event==NULL || valid_event(next_event), LOCKFREE_EVENT_QUEUE_INL_FILE, 309);

    synchronized_list_push(&m_pending_list, entry);

    return next_event;
}

template<typename t_type, long k_maximum_count>
bool t_event_queue<t_type, k_maximum_count>::valid_event(void const * event) const
{
    bool valid = true;

    valid = valid && m_initialized;
    valid = valid && event != NULL;
    valid = valid && event >= &m_events[0];
    valid = valid && event <= &m_events[m_events.get_count() - 1];
    valid = valid && pointer_is_aligned(event, 4);

    return valid;
}

#undef LOCKFREE_EVENT_QUEUE_INL_FILE
