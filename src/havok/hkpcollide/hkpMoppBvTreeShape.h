#pragma once
#ifndef __HKPMOPPBVTREESHAPE_H__
#define __HKPMOPPBVTREESHAPE_H__

/* ---------- headers */

#include "havok\hkpcollide\hkpShape.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout not reversed; size 0x40 verified (c_mopp_bv_tree_shape::m_scale lives at 0x40)
class hkpMoppBvTreeShape :
    public hkpShape
{
public:
    unsigned char unknown10[0x40 - 0x10]; // 0x10
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HKPMOPPBVTREESHAPE_H__

