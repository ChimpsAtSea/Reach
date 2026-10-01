#ifndef __GAME_VARIANT_H__
#define __GAME_VARIANT_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_traits_structures.h"
#include "omaha\interface\user_interface_multiplayer_game_settings_group.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO: members not yet reversed
class c_game_engine_custom_variant :
    public c_game_engine_base_variant
{
public:
    // f i (content_item_metadata_internal.obj)
    long get_category_index(void) const
    {
        return m_category_index;
    };

private:
    unsigned char m_unknown_custom_variant_data[0xF714 - sizeof(c_game_engine_base_variant)]; // $TODO
    long m_category_index; // 0xF714
};

class c_game_variant
{
public:
    c_game_variant(void);
    void copy_from_and_validate(c_game_variant const * other);
    void set_game_engine_index(e_game_engine_type game_engine_index);
    c_game_engine_custom_variant * get_custom_variant_writeable(void);
    c_game_engine_custom_variant const * get_custom_variant(void) const;
    e_game_engine_type get_game_engine_index(void) const;

    // f i (network_game_definitions.obj)
    c_game_engine_base_variant const * get_active_variant(void) const
    {
        return reinterpret_cast<c_game_engine_base_variant const *>(m_variant_storage);
    };

    static e_text_value_pair_parameter_type get_expected_game_engine_setting_parameter_type(e_game_variant_parameter parameter);

private:
    e_game_engine_type m_game_engine_index;
    unsigned char m_variant_storage[0xF800]; // $TODO union of the per-engine variants
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_VARIANT_H__

