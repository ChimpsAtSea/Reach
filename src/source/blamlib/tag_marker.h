#pragma once
#ifndef __TAG_MARKER_H__
#define __TAG_MARKER_H__

/* ---------- headers */

#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

// layout from IDA (m_marked_tags : c_static_flags<20000>, 0x9C4 bytes)
class c_tag_marker
{
public:
    c_tag_marker(void);

    bool mark_tag(long tag_index);
    bool try_to_mark_tag(long tag_index);
    bool tag_is_marked(long tag_index) const;
    bool unmark_tag(long tag_index);
    void reset(void);
    void merge(c_tag_marker const & other);
    void exclude(c_tag_marker const & other);
    c_big_flags<20000> const * get_marked_tags_flags(void) const;

private:
    c_big_flags<20000> m_marked_tags; // 0x0
};
static_assert(sizeof(c_tag_marker) == 0x9C4, "c_tag_marker");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_MARKER_H__

