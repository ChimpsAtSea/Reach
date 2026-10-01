#pragma once
#ifndef __MEGALOGAMENGINE_PLAYER_REFERENCE_H__
#define __MEGALOGAMENGINE_PLAYER_REFERENCE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

// $TODO: layout not yet reversed; only the methods used so far are declared
class c_player_reference
{
public:
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
    long get_player_index(void) const;

protected:
    unsigned char m_explicit_player; // 0x0 $TODO c_explicit_player (encode is called on the reference itself)
    unsigned char m_variable_index; // 0x1
    unsigned char m_type; // 0x2 $TODO c_enum_no_init<e_player_reference_type, unsigned char, 0, 4>
};
static_assert(sizeof(c_player_reference) == 0x3, "c_player_reference");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_PLAYER_REFERENCE_H__

