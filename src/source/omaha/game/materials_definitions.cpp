#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\materials_definitions.cpp"
/* ---------- headers */

#include "omaha\game\materials_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\effects\effect_definitions.h"
#include "omaha\objects\object_types.h"
#include "omaha\scenario\scenario_object_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition object_type_drag_properties_block; // "?object_type_drag_properties_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition object_type_drag_properties_block_struct_definition; // "?object_type_drag_properties_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition materials_sweeteners_struct; // "?materials_sweeteners_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition underwater_proxies_block_struct_definition; // "?underwater_proxies_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition underwater_proxies_block; // "?underwater_proxies_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition wet_proxies_struct; // "?wet_proxies_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition materials_block_struct_definition; // "?materials_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition materials_block; // "?materials_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition runtime_materials_block_struct_definition; // "?runtime_materials_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition runtime_materials_block; // "?runtime_materials_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition material_physics_properties_struct; // "?material_physics_properties_struct@@3Us_tag_struct_definition@@A"

// char * global_material_object_drag_properties_format(long, __int64, struct s_tag_block *, long, char *, long);
// bool material_physics_properties_postprocess(long, void *, bool);
// char * global_material_format(long, __int64, struct s_tag_block *, long, char *, long);
// bool postprocess_material_block(long, void *, bool);

char * global_material_object_drag_properties_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?global_material_object_drag_properties_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(34, element_index<NUMBER_OF_OBJECT_TYPES);
    csnzprintf(buffer, buffer_size, "%s", object_type_enum_definition.strings[element_index]);

    return buffer;
};

bool material_physics_properties_postprocess(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?material_physics_properties_postprocess@@YA_NJPAX_N@Z");

    s_material_physics_properties * physics_properties = static_cast<s_material_physics_properties *>(data);
    while (physics_properties->drag_overrides.count < NUMBER_OF_OBJECT_TYPES)
    {
        tag_block_add_element(&physics_properties->drag_overrides);
    }

    return true;
};

char * global_material_format(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?global_material_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_global_material_definition * material = static_cast<s_global_material_definition *>(tag_block_get_element_with_size(block, element_index, sizeof(s_global_material_definition)));
    csnzprintf(buffer, buffer_size, "%s%s", material->flags.test(_global_material_used_directly_bit) ? "$" : (material->flags.test(_global_material_used_by_children_bit) ? "*" : "-"), string_id_get_string_const(material->name));

    return buffer;
};

bool postprocess_material_block(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_material_block@@YA_NJPAX_N@Z");

    s_global_material_definition * material = static_cast<s_global_material_definition *>(data);
    if (!for_editor)
    {
        long looping_effect_indices[] =
        {
            material->sweeteners.effect_sweetener_grinding.index,
            material->sweeteners.effect_sweetener_rolling.index
        };

        for (unsigned long effect_index = 0; effect_index < NUMBEROF(looping_effect_indices); effect_index++)
        {
            if (looping_effect_indices[effect_index] != NONE)
            {
                effect_definition * effect = static_cast<effect_definition *>(tag_get(EFFECT_DEFINITION_TAG, looping_effect_indices[effect_index]));
                if (effect->loop_start_event == NONE)
                {
                    event_wrapped(_event_warning, "effects: looping effect '%s' in tag '%s' material '%s' doesn't have its loop start event set", tag_get_name(looping_effect_indices[effect_index]), tag_get_name(tag_index), string_id_get_string_const(material->name));
                }
            }
        }
    }

    return true;
};

