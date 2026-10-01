#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\determinism_debug\\determinism_debug_consumer_sound.cpp"
/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumer_sound.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\crc.h"
#include "omaha\sound\game_sound.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual unsigned long c_game_state_consumer_game_sound_scripted_impulses::get_deterministic_item_checksum(unsigned long, long, void const *);
// public: virtual void c_game_state_consumer_game_sound_scripted_impulses::get_deterministic_item_data(long, void const *, void *, long, long *);

unsigned long c_game_state_consumer_game_sound_scripted_impulses::get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address)
{
    mangled_ppc("?get_deterministic_item_checksum@c_game_state_consumer_game_sound_scripted_impulses@@UAAKKJPBX@Z");

    s_game_sound_impulse_datum const * item = static_cast<s_game_sound_impulse_datum const *>(game_state_base_address);
    assert_tag_debug_untracked_jul_11_2011(23, game_state_base_address);

    item += index;

    {
        s_game_sound_impulse_datum datum_to_checksum = *item;
        datum_to_checksum.sound_impulse_index = NONE;
        datum_to_checksum.attached_to_object_index = NONE;
        datum_to_checksum.fake_cinematic_lipsync = false;
        datum_to_checksum.pad = 0;

        crc = fast_checksum(crc, &datum_to_checksum);
    }

    return crc;
};

void c_game_state_consumer_game_sound_scripted_impulses::get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out)
{
    mangled_ppc("?get_deterministic_item_data@c_game_state_consumer_game_sound_scripted_impulses@@UAAXJPBXPAXJPAJ@Z");

    c_game_state_consumer_generic<s_game_sound_impulse_datum, 32>::get_deterministic_item_data(index, game_state_base_address, data_out, max_size, size_out);

    s_game_sound_impulse_datum * data_to_clear = static_cast<s_game_sound_impulse_datum *>(data_out);
    data_to_clear->sound_impulse_index = NONE;
    data_to_clear->attached_to_object_index = NONE;
    data_to_clear->fake_cinematic_lipsync = false;
    data_to_clear->pad = 0;
};

