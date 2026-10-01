#pragma once
#ifndef __HKPSHAPECOLLECTION_H__
#define __HKPSHAPECOLLECTION_H__

/* ---------- headers */

#include "havok\hkpcollide\hkpShape.h"
#include "havok\hkpcollide\hkpShapeContainer.h"

/* ---------- constants */

/* ---------- definitions */

// hkpShape at 0x0, hkpShapeContainer at 0x10 (verified by the base adjustment in collision_bsp_physics_build)
class hkpShapeCollection :
    public hkpShape,
    public hkpShapeContainer
{
public:
    bool m_disableWelding; // 0x14
    unsigned char m_collectionType; // 0x15
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPSHAPECOLLECTION_H__

