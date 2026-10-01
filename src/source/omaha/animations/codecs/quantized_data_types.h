#ifndef __QUANTIZED_DATA_TYPES_H__
#define __QUANTIZED_DATA_TYPES_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_quantized_quaternion_8byte
{
public:
    short i;
    short j;
    short k;
    short w;
};
static_assert(sizeof(c_quantized_quaternion_8byte) == 0x8, "c_quantized_quaternion_8byte");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __QUANTIZED_DATA_TYPES_H__

