#pragma once
#ifndef __MEGALOGAMENGINE_CUSTOM_VARIABLE_REFERENCE_H__
#define __MEGALOGAMENGINE_CUSTOM_VARIABLE_REFERENCE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

// $TODO: layout not yet reversed; only the methods used so far are declared
class c_custom_variable_reference
{
public:
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
    long evaluate(void) const;

protected:
    // $TODO 0x0: short immediate value (read with lha) overlapping explicit reference (0x0) and variable index (0x1);
    // the type must stay 1-byte aligned (s_variant_variable keeps its type byte at 0x3)
    unsigned char m_value[2]; // 0x0
    unsigned char m_type; // 0x2 $TODO c_enum_no_init<e_custom_variable_type, unsigned char, 0, 44>
};
static_assert(sizeof(c_custom_variable_reference) == 0x3, "c_custom_variable_reference");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_CUSTOM_VARIABLE_REFERENCE_H__

