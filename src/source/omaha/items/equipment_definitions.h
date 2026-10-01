#pragma once
#ifndef __EQUIPMENT_DEFINITIONS_H__
#define __EQUIPMENT_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    EQUIPMENT_DEFINITION_TAG = 'eqip',
};

enum e_multiplayer_powerup_flavor
{
    _powerup_flavor_first = 0,
    _powerup_flavor_red = _powerup_flavor_first,
    _powerup_flavor_blue,
    _powerup_flavor_yellow,

    k_multiplayer_powerup_flavor_count,

    _powerup_flavor_none = -1,
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EQUIPMENT_DEFINITIONS_H__

