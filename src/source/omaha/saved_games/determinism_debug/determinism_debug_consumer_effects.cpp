#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\determinism_debug\\determinism_debug_consumer_effects.cpp"
/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumer_effects.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\effects\effects.h"
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

// public: virtual bool c_game_state_consumer_effects::iterate_next(struct s_game_state_consumer_iterator *);
// public: virtual unsigned long c_game_state_consumer_effects::get_deterministic_item_checksum(unsigned long, long, void const *);
// public: effect_datum::effect_datum(void);
// public: virtual void c_game_state_consumer_effects::get_deterministic_item_data(long, void const *, void *, long, long *);
// public: virtual bool c_game_state_consumer_events::iterate_next(struct s_game_state_consumer_iterator *);
// public: virtual bool c_game_state_consumer_effect_locations::iterate_next(struct s_game_state_consumer_iterator *);
// public: c_flags<enum e_effect_flags, unsigned long, 25, struct s_default_enum_string_resolver>::c_flags<enum e_effect_flags, unsigned long, 25, struct s_default_enum_string_resolver>(void);
// public: bool c_flags_no_init<enum e_effect_flags, unsigned long, 25, struct s_default_enum_string_resolver>::is_clear(void) const;
// private: static unsigned long c_flags_no_init<enum e_effect_flags, unsigned long, 25, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long c_flags_no_init<enum e_effect_flags, unsigned long, 25, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_effect_flags);

bool c_game_state_consumer_effects::iterate_next(s_game_state_consumer_iterator * iterator)
{
    mangled_ppc("?iterate_next@c_game_state_consumer_effects@@UAA_NPAUs_game_state_consumer_iterator@@@Z");

    return c_game_state_consumer_datum_array<effect_datum>::iterate_next_in_range(iterator, 0, k_maximum_effects_per_map);
};

unsigned long c_game_state_consumer_effects::get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address)
{
    mangled_ppc("?get_deterministic_item_checksum@c_game_state_consumer_effects@@UAAKKJPBX@Z");

    effect_datum effect;
    long size_out;

    get_deterministic_item_data(index, game_state_base_address, &effect, sizeof(effect), &size_out);
    assert_tag_debug_untracked_jul_11_2011(36, size_out == sizeof(effect));

    return fast_checksum(crc, &effect);
};

void c_game_state_consumer_effects::get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out)
{
    mangled_ppc("?get_deterministic_item_data@c_game_state_consumer_effects@@UAAXJPBXPAXJPAJ@Z");

    PROFILER_SCOPE_BEGIN(50, effects_get_item_data, profile_instance);

    c_game_state_consumer_datum_array<effect_datum>::get_deterministic_item_data(index, game_state_base_address, data_out, max_size, size_out);

    effect_datum * effect = static_cast<effect_datum *>(data_out);
    effect->looping_sound_indices.set_all(NONE);
    effect->first_person_player_user_mask = NONE;
    effect->first_person_weapon_user_index = NONE;
    effect->lightprobe_index = NONE;
    effect->random_seed = 0;
    effect->unknown98 = 0;
};

bool c_game_state_consumer_events::iterate_next(s_game_state_consumer_iterator * iterator)
{
    mangled_ppc("?iterate_next@c_game_state_consumer_events@@UAA_NPAUs_game_state_consumer_iterator@@@Z");

    return c_game_state_consumer_datum_array<event_datum>::iterate_next_in_range(iterator, 0, k_maximum_events_per_map);
};

bool c_game_state_consumer_effect_locations::iterate_next(s_game_state_consumer_iterator * iterator)
{
    mangled_ppc("?iterate_next@c_game_state_consumer_effect_locations@@UAA_NPAUs_game_state_consumer_iterator@@@Z");

    return c_game_state_consumer_datum_array<effect_location_datum>::iterate_next_in_range(iterator, 0, k_maximum_effect_locations_per_map);
};

