#pragma once
#ifndef __USER_INTERFACE_NETWORKING_H__
#define __USER_INTERFACE_NETWORKING_H__

/* ---------- headers */

/* ---------- constants */

// range per c_enum_no_init<e_gui_game_mode, char, -1, 7>; per game_engine_variant_initialize_built_in_metadata
// campaign 1, megalo 3, sandbox 4, survival 6 (names unverified)
enum e_gui_game_mode
{
    _gui_game_mode_none = -1,

    // names unverified (H3 style); values per content_item_metadata_set_from_game_options
    _gui_game_mode_campaign = 1,
    _gui_game_mode_theater = 2,
    _gui_game_mode_multiplayer = 3,
    _gui_game_mode_mapeditor = 4,
    _gui_game_mode_survival = 6,

    k_gui_game_mode_count = 7
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __USER_INTERFACE_NETWORKING_H__

