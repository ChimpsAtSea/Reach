#pragma once
#ifndef __PLAYER_MODEL_CUSTOMIZATION_H__
#define __PLAYER_MODEL_CUSTOMIZATION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_player_customization_type
{
    _player_customization_type_model = 0,
    _player_customization_type_non_model,
    _player_customization_type_visor,

    k_player_customization_type_count
};

enum e_player_model_customization_area
{
    _player_model_customization_area_first = 0,

    k_player_model_customization_area_count = 8
};

enum e_player_non_model_customization
{
    _player_non_model_customization_first = 0,

    k_player_non_model_customization_count = 4
};

long const k_maximum_number_of_model_customization_selections_per_area = 128;

/* ---------- definitions */

struct s_player_model_customization_globals_definition;

struct s_player_customization_description
{
    s_player_customization_description(e_player_model_customization_area area)
    {
        mangled_ppc("??0s_player_customization_description@@QAA@W4e_player_model_customization_area@@@Z");

        type = _player_customization_type_model;
        model_area = area;
    };

    e_player_customization_type type; // 0x0
    union
    {
        e_player_model_customization_area model_area; // 0x4
        e_player_non_model_customization non_model_customization; // 0x4
    };
};
static_assert(sizeof(s_player_customization_description) == 0x8, "s_player_customization_description");

/* ---------- prototypes */

inline e_player_model_customization_area & operator++(e_player_model_customization_area & area)
{
    mangled_ppc("??E@YAAAW4e_player_model_customization_area@@AAW40@@Z");

    area = static_cast<e_player_model_customization_area>(area + 1);

    return area;
}

inline e_player_non_model_customization & operator++(e_player_non_model_customization & customization)
{
    mangled_ppc("??E@YAAAW4e_player_non_model_customization@@AAW40@@Z");

    customization = static_cast<e_player_non_model_customization>(customization + 1);

    return customization;
}

e_player_model_customization_area operator++(e_player_model_customization_area & area, int); // $TODO inline in the target (network_game_definitions.obj)
e_player_non_model_customization operator++(e_player_non_model_customization & customization, int); // $TODO inline in the target (network_game_definitions.obj)

s_player_model_customization_globals_definition const * customization_globals_try_and_get(void);
long player_model_customization_get_player_customization_selection_index(s_player_customization_description const * description, long selection);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_MODEL_CUSTOMIZATION_H__

