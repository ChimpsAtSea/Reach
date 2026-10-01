#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\structures\\structure_lighting_definitions.cpp"
/* ---------- headers */

#include "omaha\structures\structure_lighting_definitions.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool lightmap_light_preview_mode;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition scenario_structure_lighting_info_block; // "?scenario_structure_lighting_info_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_scenario_structure_lighting_info_vtable; // "?legacy_scenario_structure_lighting_info_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group scenario_structure_lighting_info_group; // "?scenario_structure_lighting_info_group@@3Us_tag_group@@A"
// bool lightmap_light_preview_mode; // "?lightmap_light_preview_mode@@3_NA"
// struct s_tag_group_stream_definition legacy_scenario_structure_lighting_info_stream_definition; // "?legacy_scenario_structure_lighting_info_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_scenario_structure_lighting_info_xsync_declaration; // "?legacy_scenario_structure_lighting_info_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_scenario_structure_lighting_info_vtable_shim; // "?legacy_scenario_structure_lighting_info_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool s_structure_lighting_generic_light_definition::postprocess_proc(long, void *, bool);
// public: static bool s_structure_lighting_generic_light_instance::postprocess_proc(long, void *, bool);
// public: static bool s_structure_material_lighting_info::postprocess_proc(long, void *, bool);
// public: static bool s_structure_lighting_info::structure_lighting_info_postprocess(long, bool);

bool s_structure_lighting_generic_light_definition::postprocess_proc(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_structure_lighting_generic_light_definition@@SA_NJPAX_N@Z");

    s_structure_lighting_generic_light_definition * light_definition = static_cast<s_structure_lighting_generic_light_definition *>(data);

    if (!TEST_BIT(light_definition->flags, _structure_lighting_generic_light_version_1_bit))
    {
        SET_BIT(light_definition->flags, _structure_lighting_generic_light_version_1_bit, true);

        if (!TEST_BIT(light_definition->flags, _structure_lighting_generic_light_use_far_attenuation_bit))
        {
            SET_BIT(light_definition->flags, _structure_lighting_generic_light_use_far_attenuation_bit, true);

            if (TEST_BIT(light_definition->flags, _structure_lighting_generic_light_use_near_attenuation_bit))
            {
                light_definition->far_attenuation_bounds.lower = MAX(light_definition->near_attenuation_bounds.upper, 900.0f);
            }
            else
            {
                light_definition->far_attenuation_bounds.lower = 900.0f;
            }
            light_definition->far_attenuation_bounds.upper = 4000.0f;
        }

        light_definition->intensity *= 125.78616f;

        real intensity_scale;
        switch (light_definition->type)
        {
        case _structure_lighting_generic_light_type_directional:
            intensity_scale = 0.005f;
            break;
        case _structure_lighting_generic_light_type_spot:
            intensity_scale = 0.025f;
            break;
        default:
            intensity_scale = 0.003f;
            break;
        }
        light_definition->intensity *= intensity_scale;

        SET_BIT(light_definition->flags, _structure_lighting_generic_light_inverse_squared_falloff_bit, true);
    }

    if (light_definition->hotspot_falloff_speed == 0.0f)
    {
        light_definition->hotspot_falloff_speed = 5.0f;
    }

    if (!for_editor)
    {
        real distance_scale = 0.01f;
        light_definition->near_attenuation_bounds.lower *= distance_scale;
        light_definition->near_attenuation_bounds.upper *= distance_scale;
        light_definition->far_attenuation_bounds.lower *= distance_scale;
        light_definition->far_attenuation_bounds.upper *= distance_scale;

        switch (light_definition->type)
        {
        case _structure_lighting_generic_light_type_spot:
            light_definition->hotspot_size *= 0.017453292f;
            light_definition->hotspot_cutoff_size *= 0.017453292f;
            break;
        case _structure_lighting_generic_light_type_directional:
            light_definition->hotspot_size *= distance_scale;
            light_definition->hotspot_cutoff_size *= distance_scale;
            break;
        }
    }

    return true;
};

bool s_structure_lighting_generic_light_instance::postprocess_proc(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_structure_lighting_generic_light_instance@@SA_NJPAX_N@Z");

    s_structure_lighting_generic_light_instance * light_instance = static_cast<s_structure_lighting_generic_light_instance *>(data);

    if (!TEST_BIT(light_instance->flags, _light_instance_version_1_instances_bit))
    {
        SET_BIT(light_instance->flags, _light_instance_version_1_instances_bit, true);
        light_instance->bounce_light_control = 1.0f;
    }

    if (!for_editor)
    {
        if (lightmap_light_preview_mode && (light_instance->bungie_light_type == _structure_lighting_bungie_light_type_default_lightmap_light || light_instance->bungie_light_type == _structure_lighting_bungie_light_type_uber_light))
        {
            light_instance->bungie_light_type = _structure_lighting_bungie_light_type_screen_space_light;
        }

        if (light_instance->fade_out_distance == 0.0f && light_instance->fade_start_distance == 0.0f)
        {
            light_instance->fade_out_distance = 255.0f;
            light_instance->fade_start_distance = 200.0f;
        }

        SET_BIT(light_instance->flags, _light_instance_rain_volume_bit, light_instance->light_volume_distance > 0.0f && light_instance->light_volume_intensity_scalar > 0.0f);
    }

    return true;
};

bool s_structure_material_lighting_info::postprocess_proc(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_proc@s_structure_material_lighting_info@@SA_NJPAX_N@Z");

    s_structure_material_lighting_info * material_lighting_info = static_cast<s_structure_material_lighting_info *>(data);

    if (material_lighting_info->attenuation_falloff <= 0.0f && material_lighting_info->attenuation_cutoff <= 0.0f)
    {
        material_lighting_info->attenuation_falloff = 200.0f;
        material_lighting_info->attenuation_cutoff = 800.0f;
    }

    if (!for_editor)
    {
        real distance_scale = 0.01f;
        material_lighting_info->attenuation_falloff *= distance_scale;
        material_lighting_info->attenuation_cutoff *= distance_scale;
    }

    return true;
};

//public: static bool s_structure_lighting_info::structure_lighting_info_postprocess(long, bool)
//{
//    mangled_ppc("?structure_lighting_info_postprocess@s_structure_lighting_info@@SA_NJ_N@Z");
//};

