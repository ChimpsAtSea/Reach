#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_log_cache.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_log_cache.h"
#include "baselib\system_time_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\errors\events\event_log_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_event_log_cache::initialize(class c_event_log_manager *);
// public: void c_event_log_cache::dispose(void);
// public: bool c_event_log_cache::is_empty(void) const;
// public: bool c_event_log_cache::is_space_available(long) const;
// public: bool c_event_log_cache::add_to_cache(long, enum e_event_log_index const *, char const *, bool *);
// public: void c_event_log_cache::flush(void);
// enum e_event_log_index & operator++(enum e_event_log_index &);
// public: unsigned long c_event_log_cache::get_last_flush_time(void) const;
// public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::empty(void) const;
// public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::full(void) const;
// public: long c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::count(void) const;
// public: void c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::clear(void);
// public: long c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::push(void);
// public: struct c_event_log_cache::s_cache_entry * c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::get(long);
// public: static long s_static_array<char, 32768>::get_count(void);
// public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::valid(void) const;
// public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::valid(long) const;
// public: void s_flags<enum e_event_log_index, unsigned long, 32>::clear(void);
// public: bool s_flags<enum e_event_log_index, unsigned long, 32>::test(enum e_event_log_index) const;
// public: void s_flags<enum e_event_log_index, unsigned long, 32>::set(enum e_event_log_index, bool);
// public: class s_flags<enum e_event_log_index, unsigned long, 32> & s_flags<enum e_event_log_index, unsigned long, 32>::operator|=(class s_flags<enum e_event_log_index, unsigned long, 32> const &);
// public: char & s_static_array<char, 32768>::operator[]<long>(long);
// public: static bool s_flags<enum e_event_log_index, unsigned long, 32>::valid_bit(enum e_event_log_index);
// public: bool s_flags<enum e_event_log_index, unsigned long, 32>::valid(void) const;
// private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::flag_size_type(enum e_event_log_index);
// public: static bool s_static_array<char, 32768>::valid<long>(long);
// private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::make_N_bit_mask_size_type(enum e_event_log_index);

void c_event_log_cache::initialize(c_event_log_manager * manager)
{
    mangled_ppc("?initialize@c_event_log_cache@@QAAXPAVc_event_log_manager@@@Z");

    assert_tag_debug_untracked_jul_11_2011(21, manager!=NULL);

    m_manager = manager;
    m_enabled = false;
    m_last_flush_time = system_milliseconds();
    m_cached_log_mask.clear();
    m_cache_entries.clear();
    m_string_buffer_size = 0;
};

void c_event_log_cache::dispose(void)
{
    mangled_ppc("?dispose@c_event_log_cache@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(35, is_empty());
};

bool c_event_log_cache::is_empty(void) const
{
    mangled_ppc("?is_empty@c_event_log_cache@@QBA_NXZ");

    return m_cache_entries.empty();
};

bool c_event_log_cache::is_space_available(long string_size_required) const
{
    mangled_ppc("?is_space_available@c_event_log_cache@@QBA_NJ@Z");

    bool result = !m_cache_entries.full();
    result = result && m_string_buffer_size + string_size_required <= m_string_buffer.get_count();

    return result;
};

bool c_event_log_cache::add_to_cache(long event_log_count, e_event_log_index const * event_log_indices, char const * string, bool * out_request_flush)
{
    mangled_ppc("?add_to_cache@c_event_log_cache@@QAA_NJPBW4e_event_log_index@@PBDPA_N@Z");

    long string_size_required = csstrnlen(string, 0x800) + 1;
    bool result = false;

    assert_tag_debug_untracked_jul_11_2011(63, event_log_count>0);
    assert_tag_debug_untracked_jul_11_2011(64, event_log_indices);
    assert_tag_debug_untracked_jul_11_2011(65, string);
    assert_tag_debug_untracked_jul_11_2011(66, out_request_flush);

    if (get_enabled() && is_space_available(string_size_required))
    {
        char * cached_string;
        s_flags<e_event_log_index, unsigned long, 32> event_log_mask;
        event_log_mask.clear();

        for (long event_log_index_index = 0; event_log_index_index < event_log_count; event_log_index_index++)
        {
            e_event_log_index event_log_index = event_log_indices[event_log_index_index];
            assert_tag_debug_untracked_jul_11_2011(79, m_manager->log_is_valid(event_log_index));

            if (m_manager->log_is_valid(event_log_index))
            {
                event_log_mask.set(event_log_index, true);
            }
        }

        assert_tag_debug_untracked_jul_11_2011(88, m_string_buffer_size>=0 && m_string_buffer_size+string_size_required<=m_string_buffer.get_count());

        cached_string = &m_string_buffer[m_string_buffer_size];
        csstrnzcpy(cached_string, string, string_size_required);
        m_string_buffer_size += string_size_required;

        {
            s_cache_entry * entry = m_cache_entries.get(m_cache_entries.push());
            entry->event_log_indices = event_log_mask;
            entry->string = cached_string;
        }
        m_cached_log_mask |= event_log_mask;
        result = true;

        if (m_cache_entries.full() || m_string_buffer_size >= k_string_buffer_flush_threshold)
        {
            *out_request_flush = true;
        }
    }

    return result;
};

void c_event_log_cache::flush(void)
{
    mangled_ppc("?flush@c_event_log_cache@@QAAXXZ");

    for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < k_maximum_event_logs; ++event_log_index)
    {
        if (m_cached_log_mask.test(event_log_index))
        {
            m_manager->begin_writing(event_log_index);
        }
    }

    {
        long entry_count = m_cache_entries.count();
        for (long entry_index = 0; entry_index < entry_count; entry_index++)
        {
            s_cache_entry * entry = m_cache_entries.get(entry_index);
            for (e_event_log_index event_log_index = static_cast<e_event_log_index>(0); event_log_index < k_maximum_event_logs; ++event_log_index)
            {
                if (entry->event_log_indices.test(event_log_index))
                {
                    assert_tag_debug_untracked_jul_11_2011(141, m_cached_log_mask.test(event_log_index));
                    m_manager->write_to_log(event_log_index, c_event_log_manager::_write_buffer_mode_buffered, entry->string);
                }
            }
        }
    }

    m_manager->flush_all_open_logs();
    m_cache_entries.clear();
    m_string_buffer_size = 0;
    m_cached_log_mask.clear();
    m_last_flush_time = system_milliseconds();
};

//enum e_event_log_index & operator++(enum e_event_log_index &)
//{
//    mangled_ppc("??E@YAAAW4e_event_log_index@@AAW40@@Z");
//};

unsigned long c_event_log_cache::get_last_flush_time(void) const
{
    mangled_ppc("?get_last_flush_time@c_event_log_cache@@QBAKXZ");

    return m_last_flush_time;
};

//public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::empty(void) const
//{
//    mangled_ppc("?empty@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QBA_NXZ");
//};

//public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::full(void) const
//{
//    mangled_ppc("?full@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QBA_NXZ");
//};

//public: long c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::count(void) const
//{
//    mangled_ppc("?count@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QBAJXZ");
//};

//public: void c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::clear(void)
//{
//    mangled_ppc("?clear@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QAAXXZ");
//};

//public: long c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::push(void)
//{
//    mangled_ppc("?push@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QAAJXZ");
//};

//public: struct c_event_log_cache::s_cache_entry * c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::get(long)
//{
//    mangled_ppc("?get@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QAAPAUs_cache_entry@c_event_log_cache@@J@Z");
//};

//public: static long s_static_array<char, 32768>::get_count(void)
//{
//    mangled_ppc("?get_count@?$s_static_array@D$0IAAA@@@SAJXZ");
//};

//public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::valid(void) const
//{
//    mangled_ppc("?valid@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QBA_NXZ");
//};

//public: bool c_static_stack<struct c_event_log_cache::s_cache_entry, 1024>::valid(long) const
//{
//    mangled_ppc("?valid@?$c_static_stack@Us_cache_entry@c_event_log_cache@@$0EAA@@@QBA_NJ@Z");
//};

//public: void s_flags<enum e_event_log_index, unsigned long, 32>::clear(void)
//{
//    mangled_ppc("?clear@?$s_flags@W4e_event_log_index@@K$0CA@@@QAAXXZ");
//};

//public: bool s_flags<enum e_event_log_index, unsigned long, 32>::test(enum e_event_log_index) const
//{
//    mangled_ppc("?test@?$s_flags@W4e_event_log_index@@K$0CA@@@QBA_NW4e_event_log_index@@@Z");
//};

//public: void s_flags<enum e_event_log_index, unsigned long, 32>::set(enum e_event_log_index, bool)
//{
//    mangled_ppc("?set@?$s_flags@W4e_event_log_index@@K$0CA@@@QAAXW4e_event_log_index@@_N@Z");
//};

//public: class s_flags<enum e_event_log_index, unsigned long, 32> & s_flags<enum e_event_log_index, unsigned long, 32>::operator|=(class s_flags<enum e_event_log_index, unsigned long, 32> const &)
//{
//    mangled_ppc("??_5?$s_flags@W4e_event_log_index@@K$0CA@@@QAAAAV0@ABV0@@Z");
//};

//public: char & s_static_array<char, 32768>::operator[]<long>(long)
//{
//    mangled_ppc("??$?AJ@?$s_static_array@D$0IAAA@@@QAAAADJ@Z");
//};

//public: static bool s_flags<enum e_event_log_index, unsigned long, 32>::valid_bit(enum e_event_log_index)
//{
//    mangled_ppc("?valid_bit@?$s_flags@W4e_event_log_index@@K$0CA@@@SA_NW4e_event_log_index@@@Z");
//};

//public: bool s_flags<enum e_event_log_index, unsigned long, 32>::valid(void) const
//{
//    mangled_ppc("?valid@?$s_flags@W4e_event_log_index@@K$0CA@@@QBA_NXZ");
//};

//private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::flag_size_type(enum e_event_log_index)
//{
//    mangled_ppc("?flag_size_type@?$s_flags@W4e_event_log_index@@K$0CA@@@CAKW4e_event_log_index@@@Z");
//};

//public: static bool s_static_array<char, 32768>::valid<long>(long)
//{
//    mangled_ppc("??$valid@J@?$s_static_array@D$0IAAA@@@SA_NJ@Z");
//};

//private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::make_mask_with_all_valid_bits_on_size_type(void)
//{
//    mangled_ppc("?make_mask_with_all_valid_bits_on_size_type@?$s_flags@W4e_event_log_index@@K$0CA@@@CAKXZ");
//};

//private: static unsigned long s_flags<enum e_event_log_index, unsigned long, 32>::make_N_bit_mask_size_type(enum e_event_log_index)
//{
//    mangled_ppc("?make_N_bit_mask_size_type@?$s_flags@W4e_event_log_index@@K$0CA@@@CAKW4e_event_log_index@@@Z");
//};

