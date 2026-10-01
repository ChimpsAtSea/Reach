#ifndef __MATERIALS_ACCESS_DEFINITIONS_H__
#define __MATERIALS_ACCESS_DEFINITIONS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\materials.h"

/* ---------- constants */

#define __MATERIALS_ACCESS_DEFINITIONS_H_FILE__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\materials_access_definitions.h"

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

// ??0c_global_material_type@@QAA@XZ (f i, size 0x18)
inline c_global_material_type::c_global_material_type() :
    m_index(NONE)
{
}

// ??0c_global_material_type@@QAA@W4e_base_types@0@@Z (f i); /Od codegen not verified
inline c_global_material_type::c_global_material_type(e_base_types base_type)
{
    switch (base_type)
    {
    case _base_type_invalid:
        m_index = NONE;
        break;
    case _base_type_default:
        m_index = 0;
        break;
    default:
        dassert_decomp(false, "unreachable", __MATERIALS_ACCESS_DEFINITIONS_H_FILE__, 72);
        break;
    }
}

// ?valid@c_global_material_type@@QBA_NXZ (f i); /Od codegen not verified
inline bool c_global_material_type::valid() const
{
    assert_decomp(m_index == NONE || m_index >= 0, __MATERIALS_ACCESS_DEFINITIONS_H_FILE__, 96);

    return m_index != NONE;
}

// ??8c_global_material_type@@QBA_NABV0@@Z (f i); /Od codegen not verified
inline bool c_global_material_type::operator==(c_global_material_type const & global_material_type) const
{
    return m_index == global_material_type.m_index;
}

// ??9c_global_material_type@@QBA_NABV0@@Z (f i); /Od codegen not verified
inline bool c_global_material_type::operator!=(c_global_material_type const & global_material_type) const
{
    return m_index != global_material_type.m_index;
}

// ?get_raw_material_index@c_global_material_type@@QBAFXZ (f i); /Od codegen not verified
inline short c_global_material_type::get_raw_material_index() const
{
    return m_index;
}

#endif // __MATERIALS_ACCESS_DEFINITIONS_H__
