#pragma once
#ifndef __MEGALOGAMENGINE_OBJECT_TYPE_REFERENCE_H__
#define __MEGALOGAMENGINE_OBJECT_TYPE_REFERENCE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

class c_object_type_reference
{
public:
    long get_object_definition_index(void) const;
    void initialize(void);
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

private:
    long m_object_type_index;
};
static_assert(sizeof(c_object_type_reference) == 0x4, "c_object_type_reference");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_OBJECT_TYPE_REFERENCE_H__

