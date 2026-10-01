#pragma once
#ifndef __HKPWORLD_H__
#define __HKPWORLD_H__

/* ---------- headers */

#include "havok\hkbase\hkArray.h"

/* ---------- constants */

/* ---------- definitions */

class hkpSimulationIsland;

class hkpWorld
{
public:
    hkArray<hkpSimulationIsland *, hkContainerHeapAllocator> const & getActiveSimulationIslands() const; // $TODO inline in the target (f i); body not reversed yet
    hkArray<hkpSimulationIsland *, hkContainerHeapAllocator> const & getInactiveSimulationIslands() const; // $TODO inline in the target (f i); body not reversed yet
    hkpSimulationIsland const * getFixedIsland() const; // $TODO inline in the target (f i); body not reversed yet
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPWORLD_H__

