#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\determinism_debug\\determinism_debug_consumer_players.cpp"
/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumer_players.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\players.h"
#include "omaha\memory\crc.h"
#include "omaha\profiler\profiler.h"

// the target code for this file is optimized (register allocation, tail calls) but not inlined
#pragma optimize("gt", on)

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual unsigned long c_game_state_consumer_players::get_deterministic_item_checksum(unsigned long, long, void const *);
// public: virtual void c_game_state_consumer_players::get_deterministic_item_data(long, void const *, void *, long, long *);

unsigned long c_game_state_consumer_players::get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address)
{
    mangled_ppc("?get_deterministic_item_checksum@c_game_state_consumer_players@@UAAKKJPBX@Z");

    player_datum player;
    long size_out;

    get_deterministic_item_data(index, game_state_base_address, &player, sizeof(player), &size_out);
    assert_tag_debug_untracked_jul_11_2011(27, size_out == sizeof(player));

    return fast_checksum(crc, &player);
};

void c_game_state_consumer_players::get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out)
{
    mangled_ppc("?get_deterministic_item_data@c_game_state_consumer_players@@UAAXJPBXPAXJPAJ@Z");

    PROFILER_SCOPE_BEGIN(41, players_get_det_item_data, profile_instance);

    c_game_state_consumer_datum_array<player_datum>::get_deterministic_item_data(index, game_state_base_address, data_out, max_size, size_out);

    player_datum * player = static_cast<player_datum *>(data_out);
    player->player_display_count = 0;
    player->player_display_index = NONE;
    player->loadout_palette_type = _loadout_palette_type_none;
    player->__unknown4D0 = NONE;

    if (game_is_distributed() && game_is_predicted())
    {
        player->__unknown4C8 = NONE;
    }
};

