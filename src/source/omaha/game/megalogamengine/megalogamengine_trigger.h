#pragma once
#ifndef __MEGALOGAMENGINE_TRIGGER_H__
#define __MEGALOGAMENGINE_TRIGGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_trigger
{
public:
    c_trigger(void);

protected:
    // $TODO field names unverified (layout from c_trigger::c_trigger)
    short m_condition_start_index; // 0x0
    short m_condition_count; // 0x2
    unsigned char m_execution_mode; // 0x4 $TODO c_enum<e_trigger_execution_mode, unsigned char, 0, 6>
    unsigned char m_trigger_type; // 0x5 $TODO c_enum<e_trigger_type, unsigned char, 0, 8>
    char m_object_filter_index; // 0x6
    short m_action_start_index; // 0x8
    short m_action_count; // 0xA
};
static_assert(sizeof(c_trigger) == 0xC, "c_trigger");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_TRIGGER_H__

