/* ---------- headers */

#include "omaha\physics\havok_vehicle_physics_definitions.h"
#include "omaha\cseries\cseries.h"
#include "omaha\models\model_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\vehicle_definitions.h"
#include "omaha\animations\animation_graph.h"
#include "omaha\animations\animation_definitions.h"
#include "omaha\models\render_models.h"
#include "omaha\physics\physics_model_definitions.h"
#include "omaha\game\materials.h"
#include "omaha\math\real_math.h"
#include "core\corelib\cseries\cseries_events.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition havok_vehicle_physics_struct; // "?havok_vehicle_physics_struct@@3Us_tag_struct_definition@@A"

// void havok_vehicle_physics_postprocess(long);
// void havok_vehicle_shape_phantom_postprocess(long);
// void model_postprocess_vehicle_anti_gravity_points(struct s_havok_vehicle_physics_definition *, long);
// bool havok_vehicle_physics_has_suspension(struct s_havok_vehicle_physics_definition const *);
// void havok_vehicle_physics_definition_fixup(struct s_havok_vehicle_physics_definition *);
// void havok_vehicle_physics_definition_teardown(struct s_havok_vehicle_physics_definition *);

void havok_vehicle_physics_postprocess(long vehicle_definition_index)
{
    mangled_ppc("?havok_vehicle_physics_postprocess@@YAXJ@Z");

    vehicle_definition * definition = static_cast<vehicle_definition *>(tag_get(VEHICLE_DEFINITION_TAG, vehicle_definition_index));
    s_havok_vehicle_physics_definition * physics = &definition->vehicle.havok_vehicle_physics;
    physics->iteration_count = MAX(physics->iteration_count, 1);

    if (definition->unit.object.model.index != NONE)
    {
        s_model_definition const * model_definition = static_cast<s_model_definition const *>(tag_get(MODEL_DEFINITION_TAG, definition->unit.object.model.index));
        if (model_definition->physics_model.index != NONE &&
            model_definition->render_model.index != NONE &&
            static_cast<s_physics_model_definition const *>(tag_get(k_physics_model_definition_tag, model_definition->physics_model.index))->rigid_bodies.count > 0)
        {
            bool success = true;

            physics->ground_plane_minimum_k0 = cosine(k_degrees_to_radians * physics->ground_plane_minimum_k0);
            physics->ground_plane_minimum_k1 = cosine(k_degrees_to_radians * physics->ground_plane_minimum_k1);
            physics->ground_plane_minimum_k1 = CEILING(physics->ground_plane_minimum_k1, physics->ground_plane_minimum_k0);

            if (physics->maximum_update_period_ticks == 0)
            {
                physics->maximum_update_period_ticks = 2;
            }

            if (physics->maximum_remote_update_period_ticks == 0)
            {
                physics->maximum_remote_update_period_ticks = 4;
            }

            if (physics->ground_plane_minimum_k1 > physics->ground_plane_minimum_k0 - 0.001f)
            {
                physics->ground_plane_minimum_k1 = physics->ground_plane_minimum_k0 - 0.001f;
            }

            if (physics->gravity_scale <= 0.0f)
            {
                physics->gravity_scale = 1.0f;
            }
            else if (physics->gravity_scale <= 0.001f)
            {
                physics->gravity_scale = 0.0f;
            }

            if (physics->maximum_normal_force_friction_contribution <= 0.0f)
            {
                physics->maximum_normal_force_friction_contribution = 3.0f;
            }

            for (long anti_gravity_point_index = 0; anti_gravity_point_index < physics->anti_gravity_points.count; anti_gravity_point_index++)
            {
                s_anti_gravity_point_definition * anti_gravity_point = static_cast<s_anti_gravity_point_definition *>(tag_block_get_element_with_size(&physics->anti_gravity_points, anti_gravity_point_index, sizeof(s_anti_gravity_point_definition)));
                long marker_index = render_model_find_marker_group_by_name(model_definition->render_model.index, anti_gravity_point->marker_name);
                if (marker_index == NONE)
                {
                    event_wrapped(_event_error, "objects:vehicle_physics: marker %s not found for vehicle (%s.vehicle) anti gravity point", string_id_get_string_const(anti_gravity_point->marker_name), tag_get_name(vehicle_definition_index));
                }

                anti_gravity_point->collision_global_material_type = global_material_name_resolve(anti_gravity_point->collision_global_material_name, _material_usage_type_default);
                if (!anti_gravity_point->collision_global_material_type.valid())
                {
                    anti_gravity_point->collision_global_material_type = k_global_material_type_default;
                    event_wrapped(_event_warning, "objects: vehicle '%s' has no valid collision global material name set for anti gravity point index %d.  Using default material", tag_get_name(vehicle_definition_index), anti_gravity_point_index);
                }
            }

            for (long friction_point_index = 0; friction_point_index < physics->friction_points.count; friction_point_index++)
            {
                s_friction_point_definition * friction_point_definition = static_cast<s_friction_point_definition *>(tag_block_get_element_with_size(&physics->friction_points, friction_point_index, sizeof(s_friction_point_definition)));
                long marker_index = render_model_find_marker_group_by_name(model_definition->render_model.index, friction_point_definition->marker_name);
                if (marker_index == NONE)
                {
                    event_wrapped(_event_error, "objects:vehicle_physics: marker %s not found for vehicle (%s.vehicle) friction point", string_id_get_string_const(friction_point_definition->marker_name), tag_get_name(vehicle_definition_index));
                }

                friction_point_definition->collision_global_material_type = global_material_name_resolve(friction_point_definition->collision_global_material_name, _material_usage_type_default);
                if (!friction_point_definition->collision_global_material_type.valid())
                {
                    friction_point_definition->collision_global_material_type = k_global_material_type_default;
                    event_wrapped(_event_warning, "objects: vehicle '%s' has no valid collision global material name set for friction point index %d.  Using default material", tag_get_name(vehicle_definition_index), friction_point_index);
                }

                friction_point_definition->destroyed_runtime_region_index = NONE;
                for (long model_region_index = 0; model_region_index < model_definition->runtime_regions.count; model_region_index++)
                {
                    s_model_region const * model_region = static_cast<s_model_region const *>(tag_block_get_element_with_size(&model_definition->runtime_regions, model_region_index, sizeof(s_model_region)));
                    if (model_region->name == friction_point_definition->destroyed_region_name)
                    {
                        friction_point_definition->destroyed_runtime_region_index = model_region_index;
                        break;
                    }
                }
            }

            model_postprocess_vehicle_anti_gravity_points(physics, definition->unit.object.model.index);

            if (success)
            {
                havok_vehicle_shape_phantom_postprocess(vehicle_definition_index);
            }
        }
    }
};

void havok_vehicle_shape_phantom_postprocess(long vehicle_definition_index)
{
    mangled_ppc("?havok_vehicle_shape_phantom_postprocess@@YAXJ@Z");

    vehicle_definition * definition = static_cast<vehicle_definition *>(tag_get(VEHICLE_DEFINITION_TAG, vehicle_definition_index));
    s_havok_vehicle_physics_definition * physics = &definition->vehicle.havok_vehicle_physics;
    physics->suspension_count = 0;

    if (definition->unit.object.model.index != NONE)
    {
        s_model_definition const * model_definition = static_cast<s_model_definition const *>(tag_get(MODEL_DEFINITION_TAG, definition->unit.object.model.index));
        if (model_definition->render_model.index != NONE)
        {
            s_model_definition const * animated_model_definition = static_cast<s_model_definition const *>(tag_get(MODEL_DEFINITION_TAG, definition->unit.object.model.index));
            if (animated_model_definition->animation_graph.index != NONE && animated_model_definition->runtime_nodes.count > 0)
            {
                c_model_animation_graph const * animation_graph = c_model_animation_graph::get(animated_model_definition->animation_graph.index);
                suspension_animation_iterator iterator;
                while (animation_graph->find_next_vehicle_suspension(&iterator))
                {
                    physics->suspension_count++;
                    SET_BIT(physics->flags, _havok_vehicle_physics_definition_has_suspension_bit, true);
                }
            }
        }
    }

    havok_vehicle_physics_definition_fixup(physics);
};

void model_postprocess_vehicle_anti_gravity_points(s_havok_vehicle_physics_definition * physics, long model_definition_index)
{
    mangled_ppc("?model_postprocess_vehicle_anti_gravity_points@@YAXPAUs_havok_vehicle_physics_definition@@J@Z");

    s_model_definition const * model_definition = static_cast<s_model_definition const *>(tag_get(MODEL_DEFINITION_TAG, model_definition_index));
    for (long anti_gravity_point_index = 0; anti_gravity_point_index < physics->anti_gravity_points.count; anti_gravity_point_index++)
    {
        s_anti_gravity_point_definition * anti_gravity_point = static_cast<s_anti_gravity_point_definition *>(tag_block_get_element_with_size(&physics->anti_gravity_points, anti_gravity_point_index, sizeof(s_anti_gravity_point_definition)));
        anti_gravity_point->runtime_damage_source_region_index = NONE;
        if (anti_gravity_point->damage_source_region_name != _string_id_invalid && anti_gravity_point->damage_source_region_name != _string_id_empty_string)
        {
            short region_index = NONE;
            for (long model_region_index = 0; model_region_index < model_definition->runtime_regions.count; model_region_index++)
            {
                s_model_region const * model_region = static_cast<s_model_region const *>(tag_block_get_element_with_size(&model_definition->runtime_regions, model_region_index, sizeof(s_model_region)));
                if (model_region->name == anti_gravity_point->damage_source_region_name)
                {
                    region_index = static_cast<short>(model_region_index);
                    break;
                }
            }

            if (region_index != NONE)
            {
                anti_gravity_point->runtime_damage_source_region_index = region_index;
            }
        }
    }
};

bool havok_vehicle_physics_has_suspension(s_havok_vehicle_physics_definition const * physics)
{
    mangled_ppc("?havok_vehicle_physics_has_suspension@@YA_NPBUs_havok_vehicle_physics_definition@@@Z");

    return TEST_BIT(physics->flags, _havok_vehicle_physics_definition_has_suspension_bit);
};

void havok_vehicle_physics_definition_fixup(s_havok_vehicle_physics_definition * physics)
{
    mangled_ppc("?havok_vehicle_physics_definition_fixup@@YAXPAUs_havok_vehicle_physics_definition@@@Z");
};

void havok_vehicle_physics_definition_teardown(s_havok_vehicle_physics_definition * physics)
{
    mangled_ppc("?havok_vehicle_physics_definition_teardown@@YAXPAUs_havok_vehicle_physics_definition@@@Z");
};

