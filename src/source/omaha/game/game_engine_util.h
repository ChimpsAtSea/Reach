#pragma once
#ifndef __GAME_ENGINE_UTIL_H__
#define __GAME_ENGINE_UTIL_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern long game_engine_get_object_definition_index_from_global_object_type_index(long global_object_type_index);
extern long game_engine_get_multiplayer_weapon_selection_absolute_index(long weapon_selection_name);
extern long game_engine_get_multiplayer_equipment_selection_absolute_index(long equipment_selection_name);
extern long game_engine_get_multiplayer_weapon_selection_name(long weapon_selection_absolute_index);
extern long game_engine_get_multiplayer_equipment_selection_name(long equipment_selection_absolute_index);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_UTIL_H__

