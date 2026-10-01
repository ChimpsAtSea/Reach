#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\determinism_debug\\determinism_debug_consumer_lights.cpp"
/* ---------- headers */

#include "omaha\saved_games\determinism_debug\determinism_debug_consumer_lights.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\crc.h"
#include "omaha\objects\lights.h"
#include "omaha\profiler\profiler.h"

#include <string.h>

// the target code for this file is optimized (register allocation, tail calls) but not inlined
#pragma optimize("gt", on)

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual unsigned long c_game_state_consumer_lights::get_deterministic_item_checksum(unsigned long, long, void const *);
// public: light_datum::light_datum(void);
// public: virtual void c_game_state_consumer_lights::get_deterministic_item_data(long, void const *, void *, long, long *);
// public: c_enum<enum e_change_color_reference, char, 0, 5, struct s_default_enum_string_resolver>::c_enum<enum e_change_color_reference, char, 0, 5, struct s_default_enum_string_resolver>(void);

unsigned long c_game_state_consumer_lights::get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address)
{
    mangled_ppc("?get_deterministic_item_checksum@c_game_state_consumer_lights@@UAAKKJPBX@Z");

    light_datum light;
    long size_out;

    get_deterministic_item_data(index, game_state_base_address, &light, sizeof(light), &size_out);
    assert_tag_debug_untracked_jul_11_2011(27, size_out == sizeof(light));

    return fast_checksum(crc, &light);
};

void c_game_state_consumer_lights::get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out)
{
    mangled_ppc("?get_deterministic_item_data@c_game_state_consumer_lights@@UAAXJPBXPAXJPAJ@Z");

    PROFILER_SCOPE_BEGIN(41, lights_get_det_item_data, profile_instance);

    c_game_state_consumer_datum_array<light_datum>::get_deterministic_item_data(index, game_state_base_address, data_out, max_size, size_out);

    light_datum * light = static_cast<light_datum *>(data_out);
    memset(&light->state, 0, sizeof(light->state));
};

