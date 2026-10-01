#pragma once
#ifndef __MATERIALS_H__
#define __MATERIALS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// $TODO: enumerator names unknown; only value 0 is used so far (havok_vehicle_physics_postprocess)
enum e_material_usage_type
{
    _material_usage_type_default = 0,

    // global_material_name_resolve_query_only passes -1: resolve without marking the material as used
    _material_usage_type_none = -1,
};

/* ---------- definitions */

struct s_game_globals;
struct s_global_material_definition;
union real_point3d;

class c_global_material_type
{
public:
    enum e_base_types
    {
        _base_type_invalid = 0,
        _base_type_default,
    };

    // inline in the target (f i in materials.obj)
    c_global_material_type(s_game_globals const * game_globals, short index)
    {
        mangled_ppc("??0c_global_material_type@@QAA@PBUs_game_globals@@F@Z");

        set_raw_material_index(game_globals, index);
    }

    c_global_material_type(); // inline, materials_access_definitions.h
    c_global_material_type(e_base_types base_type); // inline, materials_access_definitions.h

    c_global_material_type & operator=(c_global_material_type const & global_material_type)
    {
        mangled_ppc("??4c_global_material_type@@QAAAAV0@ABV0@@Z");

        m_index = global_material_type.m_index;
        return *this;
    }

    bool valid() const; // inline, materials_access_definitions.h
    bool operator==(c_global_material_type const & global_material_type) const; // inline, materials_access_definitions.h
    bool operator!=(c_global_material_type const & global_material_type) const; // inline, materials_access_definitions.h
    short get_raw_material_index() const; // inline, materials_access_definitions.h

    s_global_material_definition * get_material(s_game_globals const * game_globals) const;
    void set_raw_material_index(s_game_globals const * game_globals, short index);

private:
    short m_index; // 0x0
};
static_assert(sizeof(c_global_material_type) == 0x2, "c_global_material_type");

/* ---------- prototypes */

s_game_globals * material_resolution_get_game_globals();
c_global_material_type global_material_name_resolve_query_only(long name);
c_global_material_type global_material_name_resolve(long name, e_material_usage_type usage);
short global_material_resolve_material_name_internal_with_usage(s_game_globals const * game_globals, long name, e_material_usage_type usage);
short global_material_resolve_material_name_internal(s_game_globals const * game_globals, long name);
c_global_material_type global_material_name_resolve_internal(s_game_globals const * game_globals, long name, e_material_usage_type usage);
s_global_material_definition * global_name_get_material(long name, e_material_usage_type usage);
s_global_material_definition * global_get_material_internal(s_game_globals const * game_globals, c_global_material_type type);
s_global_material_definition * global_get_material(c_global_material_type type);
c_global_material_type global_material_resolve_underwater_material_proxy(c_global_material_type material_type, real_point3d const * position);
c_global_material_type global_material_resolve_underwater_material_proxy(c_global_material_type material_type, c_global_material_type underwater_material_type);
c_global_material_type object_get_default_material(long object_index);
bool global_material_is_family(c_global_material_type material_type, c_global_material_type family_material_type);

/* ---------- globals */

extern c_global_material_type const k_global_material_type_invalid;
extern c_global_material_type const k_global_material_type_default;

/* ---------- public code */

#include "omaha\game\materials_access_definitions.h"

#endif // __MATERIALS_H__

