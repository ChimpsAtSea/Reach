#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\game_state_procs.cpp"
/* ---------- headers */

#include "omaha\saved_games\game_state_procs.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "baselib\synchronized_value_windows.h"
#include "omaha\ai\ai.h"
#include "omaha\ai\ai_debug.h"
#include "omaha\bink\bink_playback.h"
#include "omaha\cache\restricted_memory_regions.h"
#include "omaha\camera\director.h"
#include "omaha\camera\observer.h"
#include "omaha\cutscene\cinematics.h"
#include "omaha\cutscene\recorded_animations.h"
#include "omaha\data_mining\data_mine_usability.h"
#include "omaha\effects\decal_manager.h"
#include "omaha\effects\effects.h"
#include "omaha\game\campaign_metagame.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine_multiplayer_sounds.h"
#include "omaha\game\incidents\incident.h"
#include "omaha\game\player_training.h"
#include "omaha\game\players.h"
#include "omaha\hs\hs_runtime.h"
#include "omaha\interface\chud\chud.h"
#include "omaha\interface\user_interface.h"
#include "omaha\main\main.h"
#include "omaha\main\main_time.h"
#include "omaha\objects\object_placement.h"
#include "omaha\objects\objects.h"
#include "omaha\physics\breakable_surfaces.h"
#include "omaha\physics\havok.h"
#include "omaha\profiler\profiler.h"
#include "omaha\rasterizer\rasterizer_main.h"
#include "omaha\render\render_objects_static_lighting.h"
#include "omaha\render\render_water.h"
#include "omaha\saved_games\determinism_debug\determinism_debug_manager.h"
#include "omaha\saved_games\game_state.h"
#include "omaha\simulation\simulation.h"
#include "omaha\sound\game_sound.h"
#include "omaha\sound\looping_sound_manager.h"
#include "omaha\sound\sound_manager.h"
#include "omaha\structures\structure_seams.h"
#include "omaha\structures\structures.h"
#include "omaha\tag_files\tag_resource_runtime.h"
#include "omaha\visibility\visibility_portal_activation.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_state_proc_globals
{
    c_synchronized_int32 state; // 0x0
    unsigned long thread_unlock_token; // 0x4
};
static_assert(sizeof(s_game_state_proc_globals) == 0x8, "s_game_state_proc_globals");

/* ---------- prototypes */

/* ---------- globals */

static game_state_proc before_save_procs[] =
{
    game_state_store_tag_file_checksum,
    havok_save_to_game_state,
    observer_initialize_before_saved_game,
    player_training_handle_saved_game,
    game_state_handle_saved_game,
    game_sound_cleanup,
    breakable_surfaces_save_to_game_state,
    structure_seams_save_to_game_state,
    looping_sound_save_to_game_state,
    campaign_metagame_save_to_game_state,
};

static game_state_proc after_save_procs[] =
{
    havok_after_save_to_game_state,
    determinism_debug_manager_initialize_for_saved_game,
    looping_sound_after_save_to_game_state,
};

static game_state_proc before_load_procs[] =
{
    havok_prepare_for_game_state_load,
    game_state_reset_mapping,
    game_sound_cleanup,
    game_sound_clear,
    bink_playback_prepare_for_game_state_load,
    simulation_prepare_to_load_saved_game,
};

static game_state_proc after_load_procs[] =
{
    structure_seams_load_from_game_state,
    breakable_surfaces_load_from_game_state,
    structures_context_cache_load_from_game_state,
    main_time_restore,
    game_state_restore_internal,
    game_options_validate_for_saved_game,
    director_fix_vtables_for_saved_game,
    havok_load_from_game_state,
    object_placement_restore,
    objects_initialize_for_saved_game,
    cinematic_load_from_game_state,
    sound_stop_all,
    game_sound_cleanup,
    game_sound_restore,
    observer_initialize_for_saved_game,
    players_initialize_for_saved_game,
    simulation_initialize_for_saved_game,
    render_objects_reset_render_state,
    recorded_animations_clear_debug_storage,
    ai_debug_initialize_for_new_map,
    game_state_set_revert_time,
    director_initialize_for_saved_game,
    ai_initialize_for_saved_game,
    c_decal_system::initialize_after_load_saved_game,
    observer_initialize_after_load_saved_game,
    game_state_after_load_proc_machine_door_portals,
    game_state_after_load_objects_setup_structure_bsp_fake_lightprobes,
    data_mine_usability_restore_from_gamestate,
    hs_restore_from_saved_game,
    determinism_debug_manager_initialize_for_saved_game,
    water_interaction_clear_all,
    campaign_metagame_initialize_for_saved_game,
    main_clear_global_pending_zone_activation,
    user_interface_main_menu_music_initialize_for_saved_game,
    chud_initialize_for_saved_game,
    incident_initialize_for_saved_game,
    multiplayer_sound_initialize_for_saved_game,
    effects_handle_game_state_after_load,
};

static s_game_state_proc_globals g_game_state_proc_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void game_state_proc_globals_initialize(void);
// void game_state_proc_globals_dispose(void);
// enum e_game_state_proc_state game_state_proc_globals_get_state(void);
// void game_state_call_before_save_procs(long);
// void game_state_call_after_save_procs(long);
// void game_state_call_before_load_procs(long);
// void game_state_call_after_load_procs(long);
// public: s_game_state_proc_globals::s_game_state_proc_globals(void);
// public: s_game_state_proc_globals::~s_game_state_proc_globals(void);
// void g_game_state_proc_globals::`dynamic atexit destructor'(void);

void game_state_proc_globals_initialize(void)
{
    mangled_ppc("?game_state_proc_globals_initialize@@YAXXZ");

    g_game_state_proc_globals.state.set(_game_state_proc_state_none);
};

void game_state_proc_globals_dispose(void)
{
    mangled_ppc("?game_state_proc_globals_dispose@@YAXXZ");
};

e_game_state_proc_state game_state_proc_globals_get_state(void)
{
    mangled_ppc("?game_state_proc_globals_get_state@@YA?AW4e_game_state_proc_state@@XZ");

    return static_cast<e_game_state_proc_state>(g_game_state_proc_globals.state.peek());
};

void game_state_call_before_save_procs(long game_state_proc_flags)
{
    mangled_ppc("?game_state_call_before_save_procs@@YAXJ@Z");

    profiler_pause_reporting();
    g_game_state_proc_globals.thread_unlock_token = halt_render_thread_and_lock_resources(262);
    c_rasterizer::block_on_last_fence();
    long old_state = g_game_state_proc_globals.state.set(_game_state_proc_state_saving);
    assert_tag_debug_untracked_jul_11_2011(265, old_state == _game_state_proc_state_none);

    sound_render_deferred_wait(false);
    restricted_region_lock_primary(k_global_audio_region);
    restricted_region_lock_primary(2);

    {
        c_tag_resources_game_lock __local_tag_resource_scope_lock;
        for (short index = 0; index < NUMBEROF(before_save_procs); index++)
        {
            before_save_procs[index](game_state_proc_flags);
        }
    }

    game_state_lock(true);
    if (!TEST_BIT(game_state_proc_flags, _defer_writing_signature_bit))
    {
        bool use_insecure_signature = TEST_BIT(game_state_proc_flags, _use_insecure_signature_bit);
        game_state_security_write_signature(use_insecure_signature, NULL);
    }
};

void game_state_call_after_save_procs(long game_state_proc_flags)
{
    mangled_ppc("?game_state_call_after_save_procs@@YAXJ@Z");

    if (game_state_verify_on_write && !TEST_BIT(game_state_proc_flags, _defer_writing_signature_bit))
    {
        bool signature_valid;
        if (TEST_BIT(game_state_proc_flags, _use_insecure_signature_bit))
        {
            signature_valid = game_state_security_verify_signature_insecure(NULL);
        }
        else
        {
            signature_valid = game_state_security_verify_signature_secure(NULL);
        }
        dassert_tag_debug_untracked_jul_11_2011(319, signature_valid, "game_state: signature is invalid after saving, the game state we just output will not load successfully");
    }

    game_state_lock(false);

    {
        c_tag_resources_game_lock __local_tag_resource_scope_lock;
        for (short index = 0; index < NUMBEROF(after_save_procs); index++)
        {
            after_save_procs[index](game_state_proc_flags);
        }
    }

    restricted_region_unlock_primary(2);
    restricted_region_unlock_primary(k_global_audio_region);

    long old_state = g_game_state_proc_globals.state.set(_game_state_proc_state_none);
    assert_tag_debug_untracked_jul_11_2011(343, old_state == _game_state_proc_state_saving);

    unlock_resources_and_resume_render_thread(g_game_state_proc_globals.thread_unlock_token);
};

void game_state_call_before_load_procs(long game_state_proc_flags)
{
    mangled_ppc("?game_state_call_before_load_procs@@YAXJ@Z");

    PROFILER_SCOPE_BEGIN(353, game_state_call_before_load_procs, profile_instance);
    short index;
    long old_state;

    g_game_state_proc_globals.thread_unlock_token = halt_render_thread_and_lock_resources(358);
    c_rasterizer::block_on_last_fence();
    old_state = g_game_state_proc_globals.state.set(_game_state_proc_state_loading);
    assert_tag_debug_untracked_jul_11_2011(361, old_state == _game_state_proc_state_none);

    sound_render_deferred_wait(false);
    restricted_region_lock_primary(k_global_audio_region);
    restricted_region_lock_primary(2);

    {
        c_tag_resources_game_lock __local_tag_resource_scope_lock;
        for (index = 0; index < NUMBEROF(before_load_procs); index++)
        {
            before_load_procs[index](game_state_proc_flags);
        }
    }

    game_state_lock(true);
    game_state_security_invalidate_signature();
};

void game_state_call_after_load_procs(long game_state_proc_flags)
{
    mangled_ppc("?game_state_call_after_load_procs@@YAXJ@Z");

    short index;
    long old_state;

    {
        PROFILER_SCOPE_BEGIN(393, game_state_call_after_load_procs, profile_instance);

        game_state_lock(false);

        {
            c_tag_resources_game_lock __local_tag_resource_scope_lock;
            for (index = 0; index < NUMBEROF(after_load_procs); index++)
            {
                after_load_procs[index](game_state_proc_flags);
            }
        }

        restricted_region_unlock_primary(2);
        restricted_region_unlock_primary(k_global_audio_region);

        old_state = g_game_state_proc_globals.state.set(_game_state_proc_state_none);
        assert_tag_debug_untracked_jul_11_2011(414, old_state == _game_state_proc_state_loading);

        unlock_resources_and_resume_render_thread(g_game_state_proc_globals.thread_unlock_token);
    }
};

// s_game_state_proc_globals ctor/dtor and the g_game_state_proc_globals atexit destructor are compiler-generated (matched)

