#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_buffer.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_buffer.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_event_buffer::reset(void);
// public: void c_event_buffer::add_event(char const *);
// public: void c_event_buffer::verify(void) const;
// public: long c_event_buffer::get_event_history(struct s_event_buffer_entry const **) const;
// private: void c_event_buffer::get_empty_space(long, long, long *, long *) const;
// private: void c_event_buffer::make_entries(long);
// private: void c_event_buffer::make_space(long);
// private: void c_event_buffer::delete_entries(long);
// public: struct s_event_buffer_entry const * s_static_array<struct s_event_buffer_entry, 128>::get_elements(void) const;
// public: struct s_event_buffer_entry * s_static_array<struct s_event_buffer_entry, 128>::get_elements(void);
// public: static long s_static_array<struct s_event_buffer_entry, 128>::get_count(void);
// public: static unsigned int s_static_array<struct s_event_buffer_entry, 128>::get_element_size(void);
// public: unsigned int s_static_array<struct s_event_buffer_entry, 128>::get_total_element_size(void) const;
// public: char const * s_static_array<char, 65536>::get_elements(void) const;
// public: static long s_static_array<char, 65536>::get_count(void);
// public: struct s_event_buffer_entry & s_static_array<struct s_event_buffer_entry, 128>::operator[]<long>(long);
// public: char & s_static_array<char, 65536>::operator[]<long>(long);
// public: struct s_event_buffer_entry const & s_static_array<struct s_event_buffer_entry, 128>::operator[]<long>(long) const;
// public: char const & s_static_array<char, 65536>::operator[]<long>(long) const;
// public: static bool s_static_array<struct s_event_buffer_entry, 128>::valid<long>(long);
// public: static bool s_static_array<char, 65536>::valid<long>(long);

void c_event_buffer::reset(void)
{
    mangled_ppc("?reset@c_event_buffer@@QAAXXZ");

    m_entry_count = 0;
    verify();
};

void c_event_buffer::add_event(char const * event_string)
{
    mangled_ppc("?add_event@c_event_buffer@@QAAXPBD@Z");

    long text_length = csstrnlen(event_string, k_event_buffer_size);
    long size_required = text_length + 1;
    {
        long write_offset;
        long end_offset;
        get_empty_space(size_required, 0, &write_offset, &end_offset);
        if (write_offset + size_required > end_offset)
        {
            make_space(size_required);
        }
    }

    if (m_entry_count + 1 > m_entries.get_count())
    {
        make_entries(1);
    }

    {
        s_event_buffer_entry * entry = &m_entries[m_entry_count];
        long write_offset;
        long end_offset;
        get_empty_space(size_required, 0, &write_offset, &end_offset);
        assert_tag_debug_untracked_jul_11_2011(66, end_offset>=write_offset+text_length+1);

        csstrnzcpy(&m_data[write_offset], event_string, end_offset - write_offset);
        m_data[write_offset + text_length] = '\0';
        entry->string = &m_data[write_offset];
        entry->text_size = size_required;
        m_entry_count++;
    }

    verify();
};

void c_event_buffer::verify(void) const
{
    mangled_ppc("?verify@c_event_buffer@@QBAXXZ");

    assert_tag_debug_untracked_jul_11_2011(87, VALID_COUNT(m_entry_count, m_entries.get_count()));

    for (long entry_index = 0; entry_index < m_entry_count; entry_index++)
    {
        s_event_buffer_entry const * entry = &m_entries[entry_index];
        long offset = pointer_distance(m_data.get_elements(), entry->string);

        assert_tag_debug_untracked_jul_11_2011(93, entry->text_size>0);
        assert_tag_debug_untracked_jul_11_2011(94, VALID_INDEX(offset, m_data.get_count()));
        assert_tag_debug_untracked_jul_11_2011(95, VALID_COUNT(offset+entry->text_size, m_data.get_count()));
        assert_tag_debug_untracked_jul_11_2011(96, m_data[offset+entry->text_size-1]=='\0');

        for (long test_index = 0; test_index < entry_index; test_index++)
        {
            s_event_buffer_entry const * test_entry = &m_entries[test_index];
            long test_offset = pointer_distance(m_data.get_elements(), test_entry->string);

            assert_tag_debug_untracked_jul_11_2011(103, test_offset+test_entry->text_size<=offset || test_offset>=offset+entry->text_size);
        }
    }
};

long c_event_buffer::get_event_history(s_event_buffer_entry const ** out_events) const
{
    mangled_ppc("?get_event_history@c_event_buffer@@QBAJPAPBUs_event_buffer_entry@@@Z");

    assert_tag_debug_untracked_jul_11_2011(113, out_events);

    *out_events = m_entries.get_elements();
    return m_entry_count;
};

void c_event_buffer::get_empty_space(long size_required, long deleted_entries, long * out_write_offset, long * out_end_offset) const
{
    mangled_ppc("?get_empty_space@c_event_buffer@@ABAXJJPAJ0@Z");

    long write_offset = 0;
    long end_offset = m_data.get_count();

    assert_tag_debug_untracked_jul_11_2011(134, size_required>0 && size_required<=m_data.get_count());
    assert_tag_debug_untracked_jul_11_2011(135, VALID_COUNT(deleted_entries, m_entry_count));

    if (m_entry_count > deleted_entries)
    {
        s_event_buffer_entry const * first_entry = &m_entries[deleted_entries];
        s_event_buffer_entry const * last_entry = &m_entries[m_entry_count - 1];
        long last_end_offset = pointer_distance32(m_data.get_elements(), last_entry->string) + last_entry->text_size;
        long first_offset = pointer_distance32(m_data.get_elements(), first_entry->string);

        if (first_offset >= last_end_offset)
        {
            write_offset = last_end_offset;
            end_offset = first_offset;
        }
        else
        {
            write_offset = last_end_offset;
            end_offset = m_data.get_count();
            if (write_offset + size_required > end_offset && first_offset >= size_required)
            {
                write_offset = 0;
                end_offset = first_offset;
            }
        }
    }

    assert_tag_debug_untracked_jul_11_2011(165, end_offset>=write_offset);

    *out_write_offset = write_offset;
    *out_end_offset = end_offset;

    for (long test_index = deleted_entries; test_index < m_entry_count; test_index++)
    {
        s_event_buffer_entry const * test_entry = &m_entries[test_index];
        long test_offset = pointer_distance(m_data.get_elements(), test_entry->string);

        assert_tag_debug_untracked_jul_11_2011(176, test_offset+test_entry->text_size<=write_offset || test_offset>=end_offset);
    }
};

void c_event_buffer::make_entries(long entry_count)
{
    mangled_ppc("?make_entries@c_event_buffer@@AAAXJ@Z");

    long entries_to_delete = m_entry_count + entry_count - m_entries.get_count();
    if (entries_to_delete > 0)
    {
        delete_entries(entries_to_delete);
    }
};

void c_event_buffer::make_space(long size_required)
{
    mangled_ppc("?make_space@c_event_buffer@@AAAXJ@Z");

    long write_offset = NONE;
    long end_offset = NONE;
    long entries_to_delete = 0;

    assert_tag_debug_untracked_jul_11_2011(202, size_required<=m_data.get_count());

    for (entries_to_delete = 0; entries_to_delete <= m_entry_count; entries_to_delete++)
    {
        get_empty_space(size_required, entries_to_delete, &write_offset, &end_offset);
        if (end_offset >= write_offset + size_required)
        {
            break;
        }
    }

    assert_tag_debug_untracked_jul_11_2011(220, entries_to_delete<=m_entry_count);

    if (entries_to_delete > 0)
    {
        delete_entries(entries_to_delete);
    }

    get_empty_space(size_required, 0, &write_offset, &end_offset);
    assert_tag_debug_untracked_jul_11_2011(230, end_offset>=write_offset+size_required);
};

void c_event_buffer::delete_entries(long delete_entry_count)
{
    mangled_ppc("?delete_entries@c_event_buffer@@AAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(252, delete_entry_count>0 && delete_entry_count<=m_entry_count);

    if (delete_entry_count < m_entry_count)
    {
        memmove_guarded(m_entries.get_elements(), &m_entries[delete_entry_count], (m_entry_count - delete_entry_count) * m_entries.get_element_size(), m_entries.get_elements(), m_entries.get_total_element_size());
    }

    m_entry_count -= delete_entry_count;
    verify();
};
