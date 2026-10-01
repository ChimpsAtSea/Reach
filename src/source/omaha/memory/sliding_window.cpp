#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\sliding_window.cpp"
/* ---------- headers */

#include "omaha\memory\sliding_window.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: bool c_sliding_window::initialized(void) const;
// public: long c_sliding_window::current_size(void) const;
// public: bool c_sliding_window::full(void) const;
// public: bool c_sliding_window::empty(void) const;
// public: long c_sliding_window::newest_sequence_number(void) const;
// public: long c_sliding_window::oldest_sequence_number(void) const;
// public: long c_sliding_window::trailing_edge(void) const;
// public: long c_sliding_window::get_storage_index(long) const;
// public: void c_sliding_window::reset(bool, long);
// public: void c_sliding_window::close(long);
// public: void c_sliding_window::open(long);

bool c_sliding_window::initialized() const
{
    mangled_ppc("?initialized@c_sliding_window@@QBA_NXZ");

    return m_initialized;
};

long c_sliding_window::current_size() const
{
    mangled_ppc("?current_size@c_sliding_window@@QBAJXZ");

    long size = m_leading_sequence_number - m_trailing_sequence_number;
    assert_tag_debug_untracked_jul_11_2011(26, m_initialized);
    assert_tag_debug_untracked_jul_11_2011(27, size>=0 && size<=m_size);
    return size;
};

bool c_sliding_window::full() const
{
    mangled_ppc("?full@c_sliding_window@@QBA_NXZ");

    return current_size() >= m_size;
};

bool c_sliding_window::empty() const
{
    mangled_ppc("?empty@c_sliding_window@@QBA_NXZ");

    return current_size() == 0;
};

long c_sliding_window::newest_sequence_number() const
{
    mangled_ppc("?newest_sequence_number@c_sliding_window@@QBAJXZ");

    assert_tag_debug_untracked_jul_11_2011(50, m_initialized);
    return m_leading_sequence_number;
};

long c_sliding_window::oldest_sequence_number() const
{
    mangled_ppc("?oldest_sequence_number@c_sliding_window@@QBAJXZ");

    assert_tag_debug_untracked_jul_11_2011(58, m_initialized);
    assert_tag_debug_untracked_jul_11_2011(59, !empty());
    return m_trailing_sequence_number + 1;
};

long c_sliding_window::trailing_edge() const
{
    mangled_ppc("?trailing_edge@c_sliding_window@@QBAJXZ");

    assert_tag_debug_untracked_jul_11_2011(67, m_initialized);
    return m_trailing_sequence_number;
};

long c_sliding_window::get_storage_index(long sequence_number) const
{
    mangled_ppc("?get_storage_index@c_sliding_window@@QBAJJ@Z");

    long storage_index = NONE;
    assert_tag_debug_untracked_jul_11_2011(77, m_initialized);

    if (sequence_number > m_trailing_sequence_number && sequence_number <= m_leading_sequence_number)
    {
        long index_in_window = sequence_number - (m_trailing_sequence_number + 1);
        assert_tag_debug_untracked_jul_11_2011(85, index_in_window>=0 && index_in_window<current_size());

        assert_tag_debug_untracked_jul_11_2011(88, m_window.size()==m_size);
        assert_tag_debug_untracked_jul_11_2011(89, m_window.count()==current_size());

        storage_index = (m_window.first_element() + index_in_window) % m_size;
        assert_tag_debug_untracked_jul_11_2011(92, storage_index>=0 && storage_index<m_size);
    }

    return storage_index;
};

void c_sliding_window::reset(bool initialize, long initial_sequence_number)
{
    mangled_ppc("?reset@c_sliding_window@@QAAX_NJ@Z");

    m_leading_sequence_number = initial_sequence_number;
    m_trailing_sequence_number = initial_sequence_number;
    m_window.clear();
    m_initialized = initialize;
};

void c_sliding_window::close(long new_trailing_edge)
{
    mangled_ppc("?close@c_sliding_window@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(120, m_initialized);

    assert_tag_debug_untracked_jul_11_2011(123, new_trailing_edge >= m_trailing_sequence_number);
    assert_tag_debug_untracked_jul_11_2011(124, new_trailing_edge <= m_leading_sequence_number);

    long amount_to_close = new_trailing_edge - m_trailing_sequence_number;
    assert_tag_debug_untracked_jul_11_2011(128, amount_to_close>=0 && amount_to_close<m_size);

    if (amount_to_close > 0)
    {
        m_window.remove_elements(amount_to_close);
        m_trailing_sequence_number = new_trailing_edge;
    }

    assert_tag_debug_untracked_jul_11_2011(136, m_window.count()==current_size());
};

void c_sliding_window::open(long new_leading_edge)
{
    mangled_ppc("?open@c_sliding_window@@QAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(145, m_initialized);

    assert_tag_debug_untracked_jul_11_2011(148, new_leading_edge >= m_leading_sequence_number);

    assert_tag_debug_untracked_jul_11_2011(151, new_leading_edge >= m_trailing_sequence_number);
    assert_tag_debug_untracked_jul_11_2011(152, new_leading_edge <= m_trailing_sequence_number + m_size);

    if (new_leading_edge > m_leading_sequence_number)
    {
        m_window.add_elements(new_leading_edge - m_leading_sequence_number);
        m_leading_sequence_number = new_leading_edge;
    }

    assert_tag_debug_untracked_jul_11_2011(160, m_window.count()==current_size());
};

