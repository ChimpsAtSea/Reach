#pragma once
#ifndef __ANIMATION_GRAPH_H__
#define __ANIMATION_GRAPH_H__

/* ---------- headers */

/* ---------- constants */

// order from animation_usage_enumeration
enum e_animation_node_usage
{
    _animation_node_usage_physics_control = 0,
    _animation_node_usage_camera_control,
    _animation_node_usage_origin_marker,
    _animation_node_usage_left_clavicle,
    _animation_node_usage_left_upperarm,
    _animation_node_usage_pose_blend_pitch,
    _animation_node_usage_pose_blend_yaw,
    _animation_node_usage_pedestal,
    _animation_node_usage_pelvis,
    _animation_node_usage_left_foot,
    _animation_node_usage_right_foot,
    _animation_node_usage_damage_root_gut,
    _animation_node_usage_damage_root_chest,
    _animation_node_usage_damage_root_head,
    _animation_node_usage_damage_root_left_shoulder,
    _animation_node_usage_damage_root_left_arm,
    _animation_node_usage_damage_root_left_leg,
    _animation_node_usage_damage_root_left_foot,
    _animation_node_usage_damage_root_right_shoulder,
    _animation_node_usage_damage_root_right_arm,
    _animation_node_usage_damage_root_right_leg,
    _animation_node_usage_damage_root_right_foot,

    k_animation_node_usage_count
};

/* ---------- definitions */

class c_model_animation_graph
{
public:
    static c_model_animation_graph const * get(long tag_index);
    long find_node_by_usage(e_animation_node_usage usage) const;
    bool find_next_vehicle_suspension(class suspension_animation_iterator * iterator) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ANIMATION_GRAPH_H__
