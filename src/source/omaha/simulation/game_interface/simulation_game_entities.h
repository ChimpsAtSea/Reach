#pragma once
#ifndef __SIMULATION_GAME_ENTITIES_H__
#define __SIMULATION_GAME_ENTITIES_H__

/* ---------- headers */

/* ---------- constants */

enum e_simulation_entity_type
{
	_simulation_entity_type_sandbox_engine = 0,
	_simulation_entity_type_custom_engine,
	_simulation_entity_type_game_engine_player,
	_simulation_entity_type_game_engine_megalo_team,

	_simulation_entity_type_game_statborg,
	_simulation_entity_type_breakable_surface_group,
	_simulation_entity_type_map_variant,
	_simulation_entity_type_debug_globals,

	_simulation_entity_type_biped, // previously `_simulation_entity_type_unit`
	_simulation_entity_type_item,
	_simulation_entity_type_generic,
	_simulation_entity_type_generic_garbage,
	_simulation_entity_type_vehicle,
	_simulation_entity_type_projectile,
	_simulation_entity_type_weapon,
	_simulation_entity_type_device,

	k_simulation_entity_type_count,
	/* $todo confirm k_simulation_entity_type_none = -1, */

	k_simulation_entity_type_first_game_engine = _simulation_entity_type_sandbox_engine,
	k_simulation_entity_type_last_game_engine = _simulation_entity_type_game_engine_megalo_team,

    /* $todo confirm k_simulation_entity_type_bits = 5, */
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SIMULATION_GAME_ENTITIES_H__
