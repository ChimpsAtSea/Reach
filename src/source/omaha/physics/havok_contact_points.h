#pragma once
#ifndef __HAVOK_CONTACT_POINTS_H__
#define __HAVOK_CONTACT_POINTS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

union vector3d;

// $TODO layout not reversed; only used through pointers so far
class c_havok_contact_point
{
public:
    vector3d const * get_normal(void) const;
};

class c_havok_contact_point_iterator
{
public:
    c_havok_contact_point_iterator(long object_index, bool include_deleted_points);
    bool valid(void);
    c_havok_contact_point * get_contact_point(void);
    void next(void);

private:
    // layout from the constructor (0x8322DC18); names past m_object_index are guesses
    bool m_include_deleted_points; // 0x0
    bool m_current_point_deleted; // 0x1
    bool m_unknown2; // 0x2
    long m_object_index; // 0x4
    long m_previous_contact_point_index; // 0x8
    long m_contact_point_index; // 0xC
};
static_assert(sizeof(c_havok_contact_point_iterator) == 0x10, "c_havok_contact_point_iterator");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_CONTACT_POINTS_H__

