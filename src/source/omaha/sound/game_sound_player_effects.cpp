/* ---------- headers */

#include "omaha\sound\game_sound_player_effects.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\platform_sound_effect_definitions.h"
#include "omaha\sound\sound_effect_manager.h"
#include "omaha\sound\sound_manager.h"
#include "omaha\sound\sound_manager_platform_playback.h"
#include <string.h>

/* ---------- constants */

// Reach has a single (scripted) global effect slot
enum
{
    k_number_of_game_sound_effects = 1,
};

enum e_game_sound_effect_state
{
    _game_sound_effect_state_none = 0,
    _game_sound_effect_state_playing,
    _game_sound_effect_state_stopping,
};

/* ---------- definitions */

// Reach layout (0x18); names after H3 s_game_sound_effect_datum where the meaning carried over
struct s_game_sound_effect_datum
{
    long state; // 0x0 e_game_sound_effect_state
    long effect_label; // 0x4
    float scale; // 0x8
    long sound_effect_index; // 0xC
    float time_elapsed; // 0x10
    float duration; // 0x14
};
static_assert(sizeof(s_game_sound_effect_datum) == 0x18, "s_game_sound_effect_datum");

struct s_game_sound_player_effects_globals
{
    s_game_sound_effect_datum sound_effects[k_number_of_game_sound_effects]; // 0x0
};
static_assert(sizeof(s_game_sound_player_effects_globals) == 0x18, "s_game_sound_player_effects_globals");

/* ---------- prototypes */

/* ---------- globals */

static real k_half_circle = k_pi;
static float oo_speed_of_sound = 1.0f / k_speed_of_sound * 1000.0f;

__declspec(thread) s_game_sound_player_effects_globals * g_game_sound_player_effects_globals;
t_restricted_allocation_manager<2, 0, 0, __tls_set_g_player_effects_globals_allocator> g_player_effects_globals_allocator;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class t_restricted_allocation_manager<2, 0, 0, void (__cdecl __tls_set_g_player_effects_globals_allocator::*)(void *)> g_player_effects_globals_allocator; // "?g_player_effects_globals_allocator@@3V?$t_restricted_allocation_manager@$01$0A@$0A@$1?__tls_set_g_player_effects_globals_allocator@@YAXPAX@Z@@A"
// struct s_game_sound_player_effects_globals *g_game_sound_player_effects_globals; // "?g_game_sound_player_effects_globals@@3PAUs_game_sound_player_effects_globals@@A"

// void __tls_set_g_player_effects_globals_allocator(void *);
// void game_sound_player_effects_initialize(void);
// void game_sound_player_effects_dispose(void);
// void game_sound_player_effects_initialize_for_new_map(void);
// void game_sound_player_effects_dispose_from_old_map(void);
// void game_sound_player_effects_handle_tag_reload(void);
// void game_sound_player_effects_restore(void);
// void game_sound_player_effects_update(float);
// void game_sound_player_effects_start_global_effect(long, float, float);
// void game_sound_player_effects_stop_global_effect(long);
// public: void * t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::reserve_memory(char const *, char const *, unsigned int, long);
// public: bool t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::valid(void) const;
// public: t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>(void);
// public: virtual void * t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::allocate(unsigned int, char const *, long, char const *, char const *, char const *);
// public: virtual void t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::deallocate(void *, char const *, long);
// public: void t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::free_memory(void);
// public: t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>::~t_restricted_allocation_manager<2, 0, 0, void (__tls_set_g_player_effects_globals_allocator::*)(void *)>(void);
// void g_player_effects_globals_allocator::`dynamic atexit destructor'(void);

void __tls_set_g_player_effects_globals_allocator(void * new_address)
{
    mangled_ppc("?__tls_set_g_player_effects_globals_allocator@@YAXPAX@Z");

    g_game_sound_player_effects_globals = static_cast<s_game_sound_player_effects_globals *>(new_address);
};

void game_sound_player_effects_initialize(void)
{
    mangled_ppc("?game_sound_player_effects_initialize@@YAXXZ");

    g_game_sound_player_effects_globals = static_cast<s_game_sound_player_effects_globals *>(g_player_effects_globals_allocator.reserve_memory("game sound player effects globals", NULL, sizeof(s_game_sound_player_effects_globals), 0));
};

void game_sound_player_effects_dispose(void)
{
    mangled_ppc("?game_sound_player_effects_dispose@@YAXXZ");
};

void game_sound_player_effects_initialize_for_new_map(void)
{
    mangled_ppc("?game_sound_player_effects_initialize_for_new_map@@YAXXZ");

    memset(g_game_sound_player_effects_globals, 0, sizeof(s_game_sound_player_effects_globals));
};

void game_sound_player_effects_dispose_from_old_map(void)
{
    mangled_ppc("?game_sound_player_effects_dispose_from_old_map@@YAXXZ");
};

void game_sound_player_effects_handle_tag_reload(void)
{
    mangled_ppc("?game_sound_player_effects_handle_tag_reload@@YAXXZ");

    game_sound_player_effects_restore();
};

void game_sound_player_effects_restore(void)
{
    mangled_ppc("?game_sound_player_effects_restore@@YAXXZ");

    game_sound_player_effects_update(0.0f);
};

void game_sound_player_effects_update(float dt)
{
    mangled_ppc("?game_sound_player_effects_update@@YAXM@Z");

    s_platform_sound_effect_properties global_effect_properties;
    for (long sound_effect_index = 0; sound_effect_index < k_number_of_game_sound_effects; sound_effect_index++)
    {
        s_game_sound_effect_datum * effect_datum = &g_game_sound_player_effects_globals->sound_effects[sound_effect_index];
        if (effect_datum->state != _game_sound_effect_state_none)
        {
            effect_datum->time_elapsed += dt;
            if (effect_datum->state == _game_sound_effect_state_playing && effect_datum->duration > 0.0f && effect_datum->time_elapsed > effect_datum->duration)
            {
                if (effect_datum->sound_effect_index != NONE)
                {
                    sound_effect_manager_stop_manual(effect_datum->sound_effect_index);
                    effect_datum->sound_effect_index = NONE;
                }
                effect_datum->state = _game_sound_effect_state_stopping;
            }

            s_platform_sound_effect_input_parameters input_parameters;
            input_parameters.inputs[0] = effect_datum->scale;
            input_parameters.inputs[1] = effect_datum->time_elapsed;
            input_parameters.inputs[2] = effect_datum->state == _game_sound_effect_state_stopping ? effect_datum->time_elapsed - effect_datum->duration : 0.0f;
            long playback_designator = game_sound_find_platform_playback_by_label(effect_datum->effect_label);
            sound_build_sound_effect_properties(NONE, playback_designator, &input_parameters, &global_effect_properties);
            if (global_effect_properties.effect_type == 0)
            {
                if (effect_datum->sound_effect_index != NONE)
                {
                    sound_effect_manager_stop_manual(effect_datum->sound_effect_index);
                    effect_datum->sound_effect_index = NONE;
                }
                effect_datum->state = _game_sound_effect_state_none;
            }
        }
    }
    sound_manager_set_global_effects(&global_effect_properties);
};

void game_sound_player_effects_start_global_effect(long effect_label, float scale, float duration)
{
    mangled_ppc("?game_sound_player_effects_start_global_effect@@YAXJMM@Z");

    long playback_designator = game_sound_find_platform_playback_by_label(effect_label);
    s_game_sound_effect_datum * effect_datum = g_game_sound_player_effects_globals->sound_effects;
    if (playback_designator != NONE)
    {
        if (effect_datum->state == _game_sound_effect_state_none || effect_datum->effect_label == effect_label)
        {
            if (effect_datum->state != _game_sound_effect_state_playing)
            {
                effect_datum->sound_effect_index = sound_effect_manager_create_manual(playback_designator, scale, FLAG(3));
            }
            else if (effect_datum->sound_effect_index != NONE)
            {
                sound_effect_manager_set_scale_manual(effect_datum->sound_effect_index, scale);
            }
            effect_datum->time_elapsed = 0.0f;
            effect_datum->duration = duration;
            effect_datum->effect_label = effect_label;
            effect_datum->scale = scale;
            effect_datum->state = _game_sound_effect_state_playing;
        }
    }
};

void game_sound_player_effects_stop_global_effect(long effect_label)
{
    mangled_ppc("?game_sound_player_effects_stop_global_effect@@YAXJ@Z");

    s_game_sound_effect_datum * effect_datum = g_game_sound_player_effects_globals->sound_effects;
    if (effect_datum->effect_label == effect_label)
    {
        effect_datum->duration = effect_datum->time_elapsed;
    }
};
