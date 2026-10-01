#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_voice_manager_xenon.cpp"
/* ---------- headers */

#include "omaha\sound\sound_voice_manager_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static real k_half_circle = k_pi;
static float oo_speed_of_sound = 1.0f / k_speed_of_sound * 1000.0f;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool sound_voice_manager_initialize(struct s_sound_preferences const *);
// void sound_voice_manager_initialize_for_new_structure_bsp(void);
// void sound_voice_manager_dispose_from_old_map(void);
// void sound_voice_manager_dispose(void);
// long sound_voice_manager_find_or_create_voice(struct sound_datum const *, short);
// short sound_voice_manager_get_hardware_voice(long);
// short sound_voice_manager_get_player_spatial_voice(long);
// bool sound_voice_manager_update_voice(long, struct sound_datum const *, bool *);
// void sound_voice_manager_release_voice(long);
// long sound_voice_manager_get_actual_count(void);

bool sound_voice_manager_initialize(s_sound_preferences const *preferences)
{
    mangled_ppc("?sound_voice_manager_initialize@@YA_NPBUs_sound_preferences@@@Z");

    bool success = true;
    return success;
};

void sound_voice_manager_initialize_for_new_structure_bsp(void)
{
    mangled_ppc("?sound_voice_manager_initialize_for_new_structure_bsp@@YAXXZ");
};

void sound_voice_manager_dispose_from_old_map(void)
{
    mangled_ppc("?sound_voice_manager_dispose_from_old_map@@YAXXZ");
};

void sound_voice_manager_dispose(void)
{
    mangled_ppc("?sound_voice_manager_dispose@@YAXXZ");
};

long sound_voice_manager_find_or_create_voice(sound_datum const *sound, short hardware_voice_index)
{
    mangled_ppc("?sound_voice_manager_find_or_create_voice@@YAJPBUsound_datum@@F@Z");

    bool voice_allocated = sound_manager_allocate_hardware_voice_explicit(hardware_voice_index);
    assert_tag_debug_untracked_jul_11_2011(42, voice_allocated);

    return hardware_voice_index;
};

short sound_voice_manager_get_hardware_voice(long voice_index)
{
    mangled_ppc("?sound_voice_manager_get_hardware_voice@@YAFJ@Z");

    return static_cast<short>(voice_index);
};

short sound_voice_manager_get_player_spatial_voice(long voice_index)
{
    mangled_ppc("?sound_voice_manager_get_player_spatial_voice@@YAFJ@Z");

    return static_cast<short>(voice_index + 196);
};

bool sound_voice_manager_update_voice(long voice_index, sound_datum const *sound, bool *out_first_time)
{
    mangled_ppc("?sound_voice_manager_update_voice@@YA_NJPBUsound_datum@@PA_N@Z");

    assert_tag_debug_untracked_jul_11_2011(65, out_first_time);

    bool result = true;
    *out_first_time = true;
    return result;
};

void sound_voice_manager_release_voice(long voice_index)
{
    mangled_ppc("?sound_voice_manager_release_voice@@YAXJ@Z");

    if (voice_index != NONE)
    {
        sound_manager_free_hardware_voice(static_cast<short>(voice_index));
    }
};

long sound_voice_manager_get_actual_count(void)
{
    mangled_ppc("?sound_voice_manager_get_actual_count@@YAJXZ");

    return NONE;
};

