#pragma once
#ifndef __HKPSIMULATIONISLAND_H__
#define __HKPSIMULATIONISLAND_H__

/* ---------- headers */

#include "havok\hkbase\hkArray.h"

/* ---------- constants */

/* ---------- definitions */

class hkpEntity;

class hkpSimulationIsland
{
public:
    hkArray<hkpEntity *, hkContainerHeapAllocator> const & getEntities() const; // $TODO inline in the target (f i); body not reversed yet
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPSIMULATIONISLAND_H__

