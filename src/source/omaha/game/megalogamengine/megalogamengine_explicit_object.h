#ifndef __MEGALOGAMENGINE_EXPLICIT_OBJECT_H__
#define __MEGALOGAMENGINE_EXPLICIT_OBJECT_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;
struct s_custom_game_engine_definition;

class c_explicit_object
{
public:
    // $TODO enumerator names unverified (values from c_explicit_object::get_object_index)
    enum e_explicit_object_type
    {
        _explicit_object_type_none = 0,
        _explicit_object_type_global_object_0,
        _explicit_object_type_global_object_1,
        _explicit_object_type_global_object_2,
        _explicit_object_type_global_object_3,
        _explicit_object_type_global_object_4,
        _explicit_object_type_global_object_5,
        _explicit_object_type_global_object_6,
        _explicit_object_type_global_object_7,
        _explicit_object_type_global_object_8,
        _explicit_object_type_global_object_9,
        _explicit_object_type_global_object_10,
        _explicit_object_type_global_object_11,
        _explicit_object_type_global_object_12,
        _explicit_object_type_global_object_13,
        _explicit_object_type_global_object_14,
        _explicit_object_type_global_object_15,
        _explicit_object_type_current_object,
        _explicit_object_type_target_object,
        _explicit_object_type_killed_object,
        _explicit_object_type_killer_object,

        k_explicit_object_type_count
    };

    long get_object_index(void) const;
    void set_value(long object_index) const;
    void initialize_from_global_variable(long variable_index);
    bool is_writeable(void) const;
    bool is_networked(s_custom_game_engine_definition const * definition) const;
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);

private:
    bool is_global_object_variable(void) const
    {
        return m_explicit_object_type >= _explicit_object_type_global_object_0 && m_explicit_object_type <= _explicit_object_type_global_object_15;
    };

    long get_global_object_variable_index(void) const
    {
        assert_decomp(is_global_object_variable(), "c:\\sd\\reach\\publishing\\main\\shared\\engine\\source\\omaha\\game\\megalogamengine\\megalogamengine_explicit_object.h", 45);

        return m_explicit_object_type - _explicit_object_type_global_object_0;
    };

    c_enum_no_init<e_explicit_object_type, char, _explicit_object_type_none, k_explicit_object_type_count> m_explicit_object_type; // 0x0
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_EXPLICIT_OBJECT_H__

