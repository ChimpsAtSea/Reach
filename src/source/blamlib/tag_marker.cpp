#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\blamlib\\tag_marker.cpp"
/* ---------- headers */

#include "blamlib\tag_marker.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long volatile `public: void __cdecl c_big_flags_typed_no_init<long, 20000>::clear(void)'::`35'::x_event_category_index; // "?x_event_category_index@?CD@??clear@?$c_big_flags_typed_no_init@J$0EOCA@@@QAAXXZ@4JC"

// public: c_tag_marker::c_tag_marker(void);
// public: bool c_tag_marker::mark_tag(long);
// public: bool c_tag_marker::try_to_mark_tag(long);
// public: bool c_tag_marker::tag_is_marked(long) const;
// public: bool c_tag_marker::unmark_tag(long);
// public: void c_tag_marker::reset(void);
// public: void c_tag_marker::merge(class c_tag_marker const &);
// public: void c_tag_marker::exclude(class c_tag_marker const &);
// public: class c_big_flags<20000> const * c_tag_marker::get_marked_tags_flags(void) const;
// public: c_big_flags<20000>::c_big_flags<20000>(void);
// public: void c_big_flags_typed_no_init<long, 20000>::clear(void);
// public: void c_big_flags_typed_no_init<long, 20000>::set(long, bool);
// public: class c_big_flags_typed_no_init<long, 20000> & c_big_flags_typed_no_init<long, 20000>::operator|=(class c_big_flags_typed_no_init<long, 20000> const &);
// public: void c_big_flags_typed_no_init<long, 20000>::and_not_range(class c_big_flags_typed_no_init<long, 20000> const *, long, long);
// public: c_big_flags_typed<long, 20000>::c_big_flags_typed<long, 20000>(void);
// public: bool c_big_flags_typed_no_init<long, 20000>::is_clear(void) const;
// protected: static unsigned long c_big_flags_typed_no_init<long, 20000>::get_mask_of_first_slice_of_chunk_inclusive(long);

c_tag_marker::c_tag_marker(void)
{
    mangled_ppc("??0c_tag_marker@@QAA@XZ");
};

bool c_tag_marker::mark_tag(long tag_index)
{
    mangled_ppc("?mark_tag@c_tag_marker@@QAA_NJ@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(tag_index);
    bool was_marked = m_marked_tags.test(absolute_index);
    m_marked_tags.set(absolute_index, true);

    return !was_marked;
};

bool c_tag_marker::try_to_mark_tag(long tag_index)
{
    mangled_ppc("?try_to_mark_tag@c_tag_marker@@QAA_NJ@Z");

    return tag_index != NONE && mark_tag(tag_index);
};

bool c_tag_marker::tag_is_marked(long tag_index) const
{
    mangled_ppc("?tag_is_marked@c_tag_marker@@QBA_NJ@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(tag_index);
    bool was_marked = m_marked_tags.test(absolute_index);

    return was_marked;
};

bool c_tag_marker::unmark_tag(long tag_index)
{
    mangled_ppc("?unmark_tag@c_tag_marker@@QAA_NJ@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(tag_index);
    bool was_marked = m_marked_tags.test(absolute_index);
    m_marked_tags.set(absolute_index, false);

    return was_marked;
};

void c_tag_marker::reset(void)
{
    mangled_ppc("?reset@c_tag_marker@@QAAXXZ");

    m_marked_tags.clear();
};

void c_tag_marker::merge(c_tag_marker const & other)
{
    mangled_ppc("?merge@c_tag_marker@@QAAXABV1@@Z");

    m_marked_tags |= other.m_marked_tags;
};

void c_tag_marker::exclude(c_tag_marker const & other)
{
    mangled_ppc("?exclude@c_tag_marker@@QAAXABV1@@Z");

    m_marked_tags.and_not_range(&other.m_marked_tags, 0, 20000 - 1);
};

c_big_flags<20000> const * c_tag_marker::get_marked_tags_flags(void) const
{
    mangled_ppc("?get_marked_tags_flags@c_tag_marker@@QBAPBV?$c_big_flags@$0EOCA@@@XZ");

    return &m_marked_tags;
};

//public: void c_big_flags_typed_no_init<long, 20000>::set(long, bool)
//{
//    mangled_ppc("?set@?$c_big_flags_typed_no_init@J$0EOCA@@@QAAXJ_N@Z");
//};
