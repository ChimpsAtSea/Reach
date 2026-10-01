#pragma once
#ifndef __HKPMOPPUTILITY_H__
#define __HKPMOPPUTILITY_H__

/* ---------- headers */

#include "havok\hkbase\hkArray.h"

/* ---------- constants */

/* ---------- definitions */

class hkpMoppCode;
class hkpShapeContainer;
class hkpMoppCompilerInput;
struct hkpMoppCodeReindexedTerminal;

class hkpMoppUtility
{
public:
    static hkpMoppCode * buildCode(hkpShapeContainer const * shapeContainer, hkpMoppCompilerInput const & moppInput, hkArray<hkpMoppCodeReindexedTerminal, hkContainerHeapAllocator> * reindexInfo);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPMOPPUTILITY_H__

