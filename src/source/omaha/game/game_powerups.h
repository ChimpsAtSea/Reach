#pragma once
#ifndef __GAME_POWERUPS_H__
#define __GAME_POWERUPS_H__

/* ---------- headers */

#include "omaha\items\equipment_definitions.h"

/* ---------- constants */

/* ---------- definitions */

class c_player_traits;

/* ---------- prototypes */

extern float game_get_powerup_duration_seconds(e_multiplayer_powerup_flavor powerup_flavor);
extern void game_get_powerup_traits(e_multiplayer_powerup_flavor powerup_flavor, c_player_traits * powerup_traits);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_POWERUPS_H__

