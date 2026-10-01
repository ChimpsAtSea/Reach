#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\materials.cpp"
/* ---------- headers */

#include "omaha\game\materials.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_globals.h"
#include "omaha\game\materials_definitions.h"
#include "omaha\models\damage_info.h"
#include "omaha\objects\object_definitions.h"
#include "omaha\objects\object_types.h"
#include "omaha\objects\objects.h"
#include "omaha\physics\water_physics.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\biped_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_global_material_type const k_global_material_type_invalid(c_global_material_type::_base_type_invalid);
c_global_material_type const k_global_material_type_default(c_global_material_type::_base_type_default);

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_global_material_type const k_global_material_type_invalid; // "?k_global_material_type_invalid@@3Vc_global_material_type@@B"
// class c_global_material_type const k_global_material_type_default; // "?k_global_material_type_default@@3Vc_global_material_type@@B"

// struct s_game_globals * material_resolution_get_game_globals(void);
// public: struct s_global_material_definition * c_global_material_type::get_material(struct s_game_globals const *) const;
// public: void c_global_material_type::set_raw_material_index(struct s_game_globals const *, short);
// class c_global_material_type global_material_name_resolve_query_only(long);
// class c_global_material_type global_material_name_resolve(long, enum e_material_usage_type);
// public: c_global_material_type::c_global_material_type(struct s_game_globals const *, short);
// short global_material_resolve_material_name_internal_with_usage(struct s_game_globals const *, long, enum e_material_usage_type);
// short global_material_resolve_material_name_internal(struct s_game_globals const *, long);
// class c_global_material_type global_material_name_resolve_internal(struct s_game_globals const *, long, enum e_material_usage_type);
// struct s_global_material_definition * global_name_get_material(long, enum e_material_usage_type);
// struct s_global_material_definition * global_get_material_internal(struct s_game_globals const *, class c_global_material_type);
// struct s_global_material_definition * global_get_material(class c_global_material_type);
// class c_global_material_type global_material_resolve_underwater_material_proxy(class c_global_material_type, union real_point3d const *);
// class c_global_material_type global_material_resolve_underwater_material_proxy(class c_global_material_type, class c_global_material_type);
// class c_global_material_type object_get_default_material(long);
// bool global_material_is_family(class c_global_material_type, class c_global_material_type);
// public: void c_flags_no_init<enum e_global_material_bit, unsigned short, 5, struct s_default_enum_string_resolver>::set(enum e_global_material_bit, bool);

s_game_globals * material_resolution_get_game_globals()
{
    mangled_ppc("?material_resolution_get_game_globals@@YAPAUs_game_globals@@XZ");

    long game_globals_index = global_scenario_game_globals_index_get();
    return static_cast<s_game_globals *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, game_globals_index));
};

s_global_material_definition * c_global_material_type::get_material(s_game_globals const * game_globals) const
{
    mangled_ppc("?get_material@c_global_material_type@@QBAPAUs_global_material_definition@@PBUs_game_globals@@@Z");

    s_global_material_definition * result = NULL;
    if (valid())
    {
        dassert_tag_debug_untracked_jul_11_2011(55, game_globals->runtime_materials.count > 0, "you need to get the globals tag (globals/globals.globals)");

        if (VALID_INDEX(m_index, game_globals->runtime_materials.count))
        {
            result = static_cast<s_global_material_definition *>(tag_block_get_element_with_size(&game_globals->runtime_materials, m_index, sizeof(s_global_material_definition)));
        }
    }

    return result;
};

void c_global_material_type::set_raw_material_index(s_game_globals const * game_globals, short index)
{
    mangled_ppc("?set_raw_material_index@c_global_material_type@@QAAXPBUs_game_globals@@F@Z");

    assert_tag_debug_untracked_jul_11_2011(74, game_globals);

    if (index != NONE)
    {
        dassert_tag_debug_untracked_jul_11_2011(78, game_globals->runtime_materials.count > 0, "you need to get the globals tag (globals/globals.globals)");

        if (VALID_INDEX(index, game_globals->runtime_materials.count))
        {
            m_index = index;
        }
    }
    else
    {
        m_index = NONE;
    }
};

c_global_material_type global_material_name_resolve_query_only(long name)
{
    mangled_ppc("?global_material_name_resolve_query_only@@YA?AVc_global_material_type@@J@Z");

    return global_material_name_resolve(name, _material_usage_type_none);
};

c_global_material_type global_material_name_resolve(long name, e_material_usage_type usage)
{
    mangled_ppc("?global_material_name_resolve@@YA?AVc_global_material_type@@JW4e_material_usage_type@@@Z");

    return c_global_material_type(material_resolution_get_game_globals(), global_material_resolve_material_name_internal_with_usage(material_resolution_get_game_globals(), name, usage));
};

short global_material_resolve_material_name_internal_with_usage(s_game_globals const * game_globals, long name, e_material_usage_type usage)
{
    mangled_ppc("?global_material_resolve_material_name_internal_with_usage@@YAFPBUs_game_globals@@JW4e_material_usage_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(133, game_globals != NULL);

    short index = global_material_resolve_material_name_internal(game_globals, name);
    if (index != NONE && usage != _material_usage_type_none)
    {
        s_global_material_definition * material = static_cast<s_global_material_definition *>(tag_block_get_element_with_size(&game_globals->runtime_materials, index, sizeof(s_global_material_definition)));
        material->flags.set(_global_material_used_directly_bit, true);
    }

    return index;
};

short global_material_resolve_material_name_internal(s_game_globals const * game_globals, long name)
{
    mangled_ppc("?global_material_resolve_material_name_internal@@YAFPBUs_game_globals@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(97, game_globals != NULL);

    short index = NONE;
    for (long global_material_index = 0; global_material_index < game_globals->runtime_materials.count; global_material_index++)
    {
        s_global_material_definition * material = static_cast<s_global_material_definition *>(tag_block_get_element_with_size(&game_globals->runtime_materials, global_material_index, sizeof(s_global_material_definition)));
        if (name == material->name)
        {
            index = static_cast<short>(global_material_index);
            break;
        }
    }

    return index;
};

c_global_material_type global_material_name_resolve_internal(s_game_globals const * game_globals, long name, e_material_usage_type usage)
{
    mangled_ppc("?global_material_name_resolve_internal@@YA?AVc_global_material_type@@PBUs_game_globals@@JW4e_material_usage_type@@@Z");

    return c_global_material_type(game_globals, global_material_resolve_material_name_internal_with_usage(game_globals, name, usage));
};

s_global_material_definition * global_name_get_material(long name, e_material_usage_type usage)
{
    mangled_ppc("?global_name_get_material@@YAPAUs_global_material_definition@@JW4e_material_usage_type@@@Z");

    c_global_material_type type = global_material_name_resolve(name, usage);
    s_global_material_definition * result = global_get_material(type);

    return result;
};

s_global_material_definition * global_get_material_internal(s_game_globals const * game_globals, c_global_material_type type)
{
    mangled_ppc("?global_get_material_internal@@YAPAUs_global_material_definition@@PBUs_game_globals@@Vc_global_material_type@@@Z");

    return type.get_material(game_globals);
};

s_global_material_definition * global_get_material(c_global_material_type type)
{
    mangled_ppc("?global_get_material@@YAPAUs_global_material_definition@@Vc_global_material_type@@@Z");

    return type.get_material(material_resolution_get_game_globals());
};

c_global_material_type global_material_resolve_underwater_material_proxy(c_global_material_type material_type, real_point3d const * position)
{
    mangled_ppc("?global_material_resolve_underwater_material_proxy@@YA?AVc_global_material_type@@V1@PBTreal_point3d@@@Z");

    c_global_material_type underwater_material_proxy_type = material_type;
    c_global_material_type underwater_material_type;
    if (water_physics_test_point(position, &underwater_material_type))
    {
        underwater_material_proxy_type = global_material_resolve_underwater_material_proxy(material_type, underwater_material_type);
    }

    return underwater_material_proxy_type;
};

c_global_material_type global_material_resolve_underwater_material_proxy(c_global_material_type material_type, c_global_material_type underwater_material_type)
{
    mangled_ppc("?global_material_resolve_underwater_material_proxy@@YA?AVc_global_material_type@@V1@0@Z");

    s_global_material_definition const * material = global_get_material(material_type);
    c_global_material_type proxy_type = material_type;
    if (material != NULL)
    {
        for (long proxy_index = 0; proxy_index < material->underwater_proxies.count; proxy_index++)
        {
            s_global_material_underwater_proxy * proxy = static_cast<s_global_material_underwater_proxy *>(tag_block_get_element_with_size(&material->underwater_proxies, proxy_index, sizeof(s_global_material_underwater_proxy)));
            if (global_material_is_family(underwater_material_type, proxy->underwater_material_type))
            {
                proxy_type = proxy->proxy_material_type;
                break;
            }
        }
    }

    return proxy_type;
};

c_global_material_type object_get_default_material(long object_index)
{
    mangled_ppc("?object_get_default_material@@YA?AVc_global_material_type@@J@Z");

    c_global_material_type result = k_global_material_type_invalid;
    object_datum * object = static_cast<object_datum *>(object_get(object_index));
    _object_definition * object_definition = static_cast<_object_definition *>(tag_get(OBJECT_TAG, object->definition_index));
    if (object_try_and_get_and_verify_type(object_index, _object_mask_biped) != NULL)
    {
        struct biped_definition * biped_definition = static_cast<struct biped_definition *>(tag_get(BIPED_DEFINITION_TAG, object->definition_index));
        if (object->object.damage_flags.test(_object_dead_bit))
        {
            result = biped_definition->biped.physics.dead_collision_global_material_type;
        }
        else
        {
            result = biped_definition->biped.physics.collision_global_material_type;
        }
    }

    if (result == k_global_material_type_invalid)
    {
        result = model_damage_info_get_indirect_material_type(object_definition->model.index);
    }

    return result;
};

bool global_material_is_family(c_global_material_type material_type, c_global_material_type family_material_type)
{
    mangled_ppc("?global_material_is_family@@YA_NVc_global_material_type@@0@Z");

    bool is_family = false;
    while (true)
    {
        s_global_material_definition const * material = global_get_material(material_type);
        if (material_type == family_material_type)
        {
            is_family = true;
            break;
        }

        if (material == NULL)
        {
            break;
        }
        else
        {
            material_type = material->runtime_material_index;
        }
    }

    return is_family;
};
