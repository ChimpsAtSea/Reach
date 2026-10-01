#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\models\\damage_info_definitions.cpp"
/* ---------- headers */

#include "omaha\models\damage_info_definitions.h"
#include "omaha\models\model_definitions.h"
#include "omaha\animations\animation_graph.h"
#include "omaha\math\function_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long *damage_part_string_id_list; // "?damage_part_string_id_list@@3PAJA"
// char const **g_global_damage_aftermath_special_damage_type_enum_strings; // "?g_global_damage_aftermath_special_damage_type_enum_strings@@3PAPBDA"
// char const **model_state_enum_definition_strings; // "?model_state_enum_definition_strings@@3PAPBDA"
// struct s_string_list_definition model_state_enum_definition; // "?model_state_enum_definition@@3Us_string_list_definition@@A"
// struct s_string_list_definition object_damage_aftermath_special_damage_type_enum; // "?object_damage_aftermath_special_damage_type_enum@@3Us_string_list_definition@@A"
// struct s_tag_block_definition global_damage_section_block; // "?global_damage_section_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition global_damage_section_block_struct_definition; // "?global_damage_section_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition global_damage_nodes_block_struct_definition; // "?global_damage_nodes_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_damage_nodes_block; // "?global_damage_nodes_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition damage_constraint_info_block; // "?damage_constraint_info_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition damage_constraint_info_block_struct_definition; // "?damage_constraint_info_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_damage_info_block; // "?global_damage_info_block@@3Us_tag_block_definition@@A"
// struct s_tag_field *instantaneous_response_damage_effect_fields_v1; // "?instantaneous_response_damage_effect_fields_v1@@3PAUs_tag_field@@A"
// struct s_tag_field *instantaneous_response_damage_effect_fields_v2; // "?instantaneous_response_damage_effect_fields_v2@@3PAUs_tag_field@@A"
// struct s_tag_field *instantaneous_response_damage_effect_marker_fields_v1; // "?instantaneous_response_damage_effect_marker_fields_v1@@3PAUs_tag_field@@A"
// struct s_tag_field *instantaneous_response_damage_effect_marker_fields_v2; // "?instantaneous_response_damage_effect_marker_fields_v2@@3PAUs_tag_field@@A"
// struct s_tag_struct_definition damage_transfer_block_struct_definition; // "?damage_transfer_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition damage_transfer_block; // "?damage_transfer_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition new_global_damage_section_block_struct_definition; // "?new_global_damage_section_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition new_global_damage_section_block; // "?new_global_damage_section_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition model_damage_info_struct; // "?model_damage_info_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition global_damage_info_block_struct_definition; // "?global_damage_info_block_struct_definition@@3Us_tag_struct_definition@@A"

// char * instantaneous_damage_repsonse_format_block_proc(long, __int64, struct s_tag_block *, long, char *, long);
// char * damage_section_recharge_fraction_format_proc(long, __int64, struct s_tag_block *, long, char *, long);
// bool damage_section_recharge_speed_multiplier_on_new_proc(void *);
// char * damage_response_region_transition_format_proc(long, __int64, struct s_tag_block *, long, char *, long);
// public: static long `void build_damage_root_node_map(struct s_model_definition const *, short *const)'::`10'::build_map_helper::fixup_damage_parts_for_chain(short, short *const, struct s_model_definition const *);
// bool damage_info_build_nodes(struct s_model_definition const *, struct s_tag_block *);
// short damage_part_name_match(char const *);
// void build_damage_root_node_map(struct s_model_definition const *, short *const);
// short get_damage_part_for_node_usage_flag(enum e_animation_node_usage);
// bool damage_info_conversion_func(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *);

char * instantaneous_damage_repsonse_format_block_proc(long tag_index, __int64 block_offset, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?instantaneous_damage_repsonse_format_block_proc@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_instantaneous_damage_response * response = &static_cast<s_instantaneous_damage_response *>(block->address)[element_index];
    csnzprintf(buffer, buffer_size, "%.3f : %s -> %s", response->damage_threshold, string_id_get_string_const(response->transition_region_swap.region_name), model_state_enum_definition_strings[response->transition_region_swap.new_state]);

    return buffer;
};

char * damage_section_recharge_fraction_format_proc(long tag_index, __int64 block_offset, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?damage_section_recharge_fraction_format_proc@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    float * recharge_fraction = &static_cast<float *>(block->address)[element_index];
    csnzprintf(buffer, buffer_size, "%.3f", *recharge_fraction);

    return buffer;
};

bool damage_section_recharge_speed_multiplier_on_new_proc(void * element)
{
    mangled_ppc("?damage_section_recharge_speed_multiplier_on_new_proc@@YA_NPAX@Z");

    s_damage_section_recharge_speed_multiplier_curve * curve = static_cast<s_damage_section_recharge_speed_multiplier_curve *>(element);
    {
        c_function_definition_editor editor(&curve->mapping);
        editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
        editor.set_function_type(c_function_definition::_function_type_linear);
        editor.calc_default_values();
        editor.set_control_point_y(0, 0, 0.5f);
        editor.set_control_point_y(0, 1, 0.5f);
        editor.set_clamp_range_min(0.0f);
        editor.set_clamp_range_max(2.0f);
    }

    return true;
};

char * damage_response_region_transition_format_proc(long tag_index, __int64 block_offset, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?damage_response_region_transition_format_proc@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_region_transition * transition = &static_cast<s_region_transition *>(block->address)[element_index];
    csnzprintf(buffer, buffer_size, "%s -> %s", string_id_get_string_const(transition->region_name), model_state_enum_definition_strings[transition->new_state]);

    return buffer;
};

bool damage_info_build_nodes(s_model_definition const * model, s_tag_block * nodes_block)
{
    mangled_ppc("?damage_info_build_nodes@@YA_NPBUs_model_definition@@PAUs_tag_block@@@Z");

    bool result = true;
    short node_damage_parts[MAXIMUM_NODES_PER_MODEL];
    build_damage_root_node_map(model, node_damage_parts);
    if (tag_block_resize(nodes_block, model->runtime_nodes.count))
    {
        for (short node_index = 0; node_index < nodes_block->count; node_index++)
        {
            s_damage_node * damage_node = static_cast<s_damage_node *>(tag_block_get_element_with_size(nodes_block, node_index, sizeof(s_damage_node)));
            short model_node_index = node_index;
            short damage_part = NONE;
            damage_part = node_damage_parts[node_index];
            if (damage_part == NONE)
            {
                do
                {
                    s_model_node const * model_node = static_cast<s_model_node const *>(tag_block_get_element_with_size(&model->runtime_nodes, model_node_index, sizeof(s_model_node)));
                    damage_part = damage_part_name_match(string_id_get_string_const(model_node->name));
                    if (damage_part != NONE)
                    {
                        break;
                    }
                    model_node_index = model_node->parent_node_index;
                }
                while (model_node_index != NONE);
            }
            damage_node->damage_part = damage_part;
        }
    }
    else
    {
        event_wrapped(_event_error, "damage_resistance_build_nodes: can't resize nodes block");
        result = false;
    }

    return result;
};

short damage_part_name_match(char const * name)
{
    mangled_ppc("?damage_part_name_match@@YAFPBD@Z");

    static char const * damage_part_names[k_damage_part_count][k_maximum_damage_part_names] =
    {
        { "spine", "pelvis" },
        { "spine1" },
        { "head", "neck" },
        { "l_clavicle", "l_upperarm" },
        { "l_forearm", "l_hand" },
        { "l_thigh" },
        { "l_thigh", "l_horselink", "l_calf", "l_foot" },
        { "r_clavicle", "r_upperarm" },
        { "r_forearm", "r_hand" },
        { "r_thigh" },
        { "r_thigh", "r_horselink", "r_calf", "r_foot", "tail" },
    };

    for (short damage_part = k_damage_part_count - 1; damage_part >= 0; damage_part--)
    {
        for (short name_index = 0; name_index < k_maximum_damage_part_names; name_index++)
        {
            if (damage_part_names[damage_part][name_index] != NULL && strstr(name, damage_part_names[damage_part][name_index]) != NULL)
            {
                return damage_part;
            }
        }
    }

    return NONE;
};

void build_damage_root_node_map(s_model_definition const * model, short * const node_damage_parts)
{
    mangled_ppc("?build_damage_root_node_map@@YAXPBUs_model_definition@@QAF@Z");

    memset(node_damage_parts, NONE, sizeof(short) * MAXIMUM_NODES_PER_MODEL);
    if (model->animation_graph.index != NONE)
    {
        c_model_animation_graph const * animation_graph = c_model_animation_graph::get(model->animation_graph.index);
        for (short usage_index = _animation_node_usage_damage_root_gut; usage_index <= _animation_node_usage_damage_root_right_foot; usage_index++)
        {
            e_animation_node_usage node_usage = static_cast<e_animation_node_usage>(usage_index);
            short damage_part = get_damage_part_for_node_usage_flag(node_usage);
            long node_index = animation_graph->find_node_by_usage(node_usage);
            if (node_index != NONE)
            {
                node_damage_parts[node_index] = damage_part;
            }
        }

        struct build_map_helper
        {
            static long fixup_damage_parts_for_chain(short node_index, short * const node_damage_parts, s_model_definition const * model)
            {
                mangled_ppc("?fixup_damage_parts_for_chain@build_map_helper@?9??build_damage_root_node_map@@YAXPBUs_model_definition@@QAF@Z@SAJF10@Z");

                short damage_part = NONE;
                if (node_index != NONE)
                {
                    damage_part = node_damage_parts[node_index];
                    if (damage_part == NONE)
                    {
                        s_model_node const * node = static_cast<s_model_node const *>(tag_block_get_element_with_size(&model->runtime_nodes, node_index, sizeof(s_model_node)));
                        damage_part = static_cast<short>(fixup_damage_parts_for_chain(node->parent_node_index, node_damage_parts, model));
                        node_damage_parts[node_index] = damage_part;
                    }
                }

                return damage_part;
            };
        };

        for (short node_index = static_cast<short>(model->runtime_nodes.count - 1); node_index >= 0; node_index--)
        {
            if (node_damage_parts[node_index] == NONE)
            {
                build_map_helper::fixup_damage_parts_for_chain(node_index, node_damage_parts, model);
            }
        }
    }
};

// $TODO nonmatching (only the jump table data differs: target table holds absolute addresses)
short get_damage_part_for_node_usage_flag(e_animation_node_usage usage)
{
    mangled_ppc("?get_damage_part_for_node_usage_flag@@YAFW4e_animation_node_usage@@@Z");

    short damage_part = NONE;
    switch (usage)
    {
    case _animation_node_usage_damage_root_gut:
        damage_part = _damage_part_gut;
        break;
    case _animation_node_usage_damage_root_chest:
        damage_part = _damage_part_chest;
        break;
    case _animation_node_usage_damage_root_head:
        damage_part = _damage_part_head;
        break;
    case _animation_node_usage_damage_root_left_shoulder:
        damage_part = _damage_part_left_shoulder;
        break;
    case _animation_node_usage_damage_root_left_arm:
        damage_part = _damage_part_left_arm;
        break;
    case _animation_node_usage_damage_root_left_leg:
        damage_part = _damage_part_left_leg;
        break;
    case _animation_node_usage_damage_root_left_foot:
        damage_part = _damage_part_left_foot;
        break;
    case _animation_node_usage_damage_root_right_shoulder:
        damage_part = _damage_part_right_shoulder;
        break;
    case _animation_node_usage_damage_root_right_arm:
        damage_part = _damage_part_right_arm;
        break;
    case _animation_node_usage_damage_root_right_leg:
        damage_part = _damage_part_right_leg;
        break;
    case _animation_node_usage_damage_root_right_foot:
        damage_part = _damage_part_right_foot;
        break;
    default:
        dassert_tag_debug_untracked_jul_11_2011(1256, false, "unreachable");
        break;
    }

    return damage_part;
};

bool damage_info_conversion_func(unsigned long conversion_flags, s_tag_field const * old_fields, long old_version, long old_size, void * old_data, s_tag_field const * new_fields, long new_version, long new_size, void * new_data)
{
    mangled_ppc("?damage_info_conversion_func@@YA_NKPBUs_tag_field@@JJPAX0JJ1@Z");

    s_model_damage_info_v1 * old_damage_info = static_cast<s_model_damage_info_v1 *>(old_data);
    s_model_damage_info * new_damage_info = static_cast<s_model_damage_info *>(new_data);
    new_damage_info->flags = old_damage_info->flags;
    new_damage_info->global_indirect_material_name = old_damage_info->global_indirect_material_name;
    new_damage_info->body.maximum_vitality = old_damage_info->maximum_vitality;
    new_damage_info->shield.maximum_shield_vitality = old_damage_info->maximum_shield_vitality;
    new_damage_info->shield.global_shield_material_name = old_damage_info->global_shield_material_name;
    new_damage_info->shield.minimum_stun_damage = old_damage_info->minimum_stun_damage;
    new_damage_info->shield.stun_time = old_damage_info->stun_time;
    new_damage_info->shield.recharge_time = old_damage_info->recharge_time;
    new_damage_info->shield.shield_damaged_threshold = old_damage_info->shield_damaged_threshold;
    new_damage_info->shield.shield_damaged_effect = old_damage_info->shield_damaged_effect;
    new_damage_info->shield.shield_depleted_effect = old_damage_info->shield_depleted_effect;
    new_damage_info->shield.shield_recharging_effect = old_damage_info->shield_recharging_effect;
    new_damage_info->runtime_shield_material_type = old_damage_info->runtime_shield_material_type;
    new_damage_info->runtime_indirect_material_type = old_damage_info->runtime_indirect_material_type;
    new_damage_info->runtime_shield_recharge_velocity = old_damage_info->runtime_shield_recharge_velocity;
    reassign_tag_block_and_memory(&new_damage_info->damage_sections, &old_damage_info->damage_sections);
    reassign_tag_block_and_memory(&new_damage_info->nodes, &old_damage_info->nodes);

    return true;
};
