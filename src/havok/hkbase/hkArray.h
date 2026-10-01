#pragma once
#ifndef __HKARRAY_H__
#define __HKARRAY_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct hkContainerHeapAllocator;
struct hkContainerTempAllocator;

template <typename t_type>
class hkArrayBase
{
public:
    int getSize() const; // $TODO inline in the target (f i); body not reversed yet
    t_type const & operator[](int index) const; // $TODO inline in the target (f i); body not reversed yet

protected:
    t_type * m_data; // 0x0
    int m_size; // 0x4
    int m_capacityAndFlags; // 0x8
};

template <typename t_type, typename t_allocator>
class hkArray :
    public hkArrayBase<t_type>
{
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKARRAY_H__

