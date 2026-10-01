#pragma once
#ifndef __HKPSHAPE_H__
#define __HKPSHAPE_H__

/* ---------- headers */

#include "havok\hkbase\hkReferencedObject.h"

/* ---------- constants */

/* ---------- definitions */

class hkpShape :
    public hkReferencedObject
{
public:
    static void * operator new(unsigned int size, void * pointer); // $TODO inline in the target (f i, sync_action.obj); body not reversed yet

    unsigned long m_userData; // 0x8
    long m_type; // 0xC hkpShapeType
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPSHAPE_H__

