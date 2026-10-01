#pragma once
#ifndef __MEGALOGAMENGINE_TEXT_H__
#define __MEGALOGAMENGINE_TEXT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

enum e_replaceable_token_type
{
    _replaceable_token_type_player = 0,
    _replaceable_token_type_team,
    _replaceable_token_type_object,
    _replaceable_token_type_custom_variable,
    _replaceable_token_type_custom_timer,

    k_replaceable_token_type_count,

    _replaceable_token_type_none = -1
};

/* ---------- definitions */

class c_bitstream;

class c_replaceable_token
{
public:
    void initialize(void);
    bool operator==(c_replaceable_token const & other) const;
    bool operator!=(c_replaceable_token const & other) const;
    e_replaceable_token_type get_type(void) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

private:
    // $TODO: storage for the player/team/object/custom variable/custom timer reference selected by m_type
    unsigned char m_reference_storage[3];
    c_enum_no_init<e_replaceable_token_type, char, _replaceable_token_type_none, k_replaceable_token_type_count> m_type;
};
static_assert(sizeof(c_replaceable_token) == 0x4, "c_replaceable_token");

class c_dynamic_string
{
public:
    void initialize(void);
    bool operator==(c_dynamic_string const & other) const;
    bool operator!=(c_dynamic_string const & other) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

private:
    s_static_array<c_replaceable_token, 2> m_tokens;
    short m_string_index;
};
static_assert(sizeof(c_dynamic_string) == 0xA, "c_dynamic_string");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_TEXT_H__

