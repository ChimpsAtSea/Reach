#pragma once
#ifndef __SIMULATION_GAME_EVENTS_H__
#define __SIMULATION_GAME_EVENTS_H__

/* ---------- headers */

enum e_simulation_event_type
{
	_simulation_event_type_damage_aftermath = 0,
	_simulation_event_type_damage_section_response,
	_simulation_event_type_breakable_surface_break,
	_simulation_event_type_breakable_surface_damage_aoe,
	_simulation_event_type_projectile_attached,
	_simulation_event_type_projectile_detonate,
	_simulation_event_type_projectile_impact_effect,
	_simulation_event_type_projectile_object_impact_effect,
	_simulation_event_type_biped_board_vehicle,
	_simulation_event_type_biped_pickup,
	_simulation_event_type_weapon_effect,
	_simulation_event_type_weapon_empty_click,
	_simulation_event_type_biped_melee_clang,
	_simulation_event_type_player_account_balance_notification,
	_simulation_event_type_incident,
	_simulation_event_type_player_money_grant,
	_simulation_event_type_unit_zoom,
	_simulation_event_type_megalo_chud_message,
	_simulation_event_type_authority_ignored_predicted_position,
	_simulation_event_type_biped_exit_vehicle,
	_simulation_event_type_device_touch,
	_simulation_event_type_biped_debug_teleport,
	_simulation_event_type_biped_assassinate,
	_simulation_event_type_biped_equipment_activation,
	_simulation_event_type_request_weapon_fire,
	_simulation_event_type_action_weapon_fire,
	_simulation_event_type_weapon_reload,
	_simulation_event_type_biped_throw_initiate,
	_simulation_event_type_biped_melee_initiate,
	_simulation_event_type_vehicle_trick,
	_simulation_event_type_biped_dodge,
	_simulation_event_type_weapon_pickup,
	_simulation_event_type_weapon_put_away,
	_simulation_event_type_weapon_drop,
	_simulation_event_type_weapon_tether_request,
	_simulation_event_type_vehicle_flip,
	_simulation_event_type_biped_throw_release,
	_simulation_event_type_biped_melee_damage,
	_simulation_event_type_biped_enter_vehicle,
	_simulation_event_type_game_engine_request_boot_player,
	_simulation_event_type_request_projectile_attach,
	_simulation_event_type_biped_pickup_item_request,
	_simulation_event_type_projectile_supercombine_request,
	_simulation_event_type_object_refresh,
	_simulation_event_type_player_editor_request,
	_simulation_event_type_player_purchase_request,
	_simulation_event_type_player_loadout_request,
	_simulation_event_type_biped_laser_designation,
	_simulation_event_type_player_set_respawn_target_transform,
	_simulation_event_type_player_set_orbiting_camera_target,
	_simulation_event_type_player_call_for_help_request,
	_simulation_event_type_player_force_base_respawn,

	k_simulation_event_type_count,
};

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SIMULATION_GAME_EVENTS_H__
