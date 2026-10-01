#pragma once
#ifndef __GAME_ENGINE_DEFAULT_H__
#define __GAME_ENGINE_DEFAULT_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_constants.h"
#include "omaha\game\game_engine.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

enum e_multiplayer_team;
enum e_team_scoring_method;
enum e_output_user_index;
enum e_object_type;
enum e_scenario_requisition_trigger_volume_flag;
enum e_game_engine_status;
enum e_simulation_entity_type;
enum e_game_engine_restoration_type;
enum e_simulation_event_type;
enum e_network_game_simulation_protocol;

struct game_engine_interface_state;
struct s_objective_status;
struct c_chud_navpoint;
class c_player_traits;
class c_ai_traits;
struct s_netgame_goal_influencer;
struct s_scenario_object;
struct s_scenario_multiplayer_object_properties;
struct s_object_placement_data;
struct s_damage_reporting_info;
class c_game_team;
struct scenario_requisition_palette_entry;
class c_bitstream;
struct s_game_engine_state_data;
struct s_incident_metadata;
struct s_multiplayer_runtime_globals_definition;
struct s_file_reference;
struct s_mp_objective_fireteam_member;

typedef c_flags<long, unsigned __int64, 64> c_game_engine_update_mask; // $TODO real name

// vtable order per ??_7c_game_engine@@6B@ (game_engine_sandbox.obj); msvc emits overloads in reverse declaration order
class c_game_engine
{
public:
    virtual e_game_engine_type get_type(void) const;
    virtual long get_score_to_win_round(void) const;
    virtual void recompute_team_score(e_multiplayer_team team_index, long player_adjustment, e_team_scoring_method scoring_method) const;
    virtual void get_score_string(long score, c_static_wchar_string<256> * string) const;
    virtual void get_hud_interface_state(long player_index, game_engine_interface_state * interface_state) const;
    virtual bool get_objective_interface_state(long player_index, s_objective_status * objective_status) const;
    virtual bool minimap_available(long player_index) const;
    virtual bool team_mapping_is_valid(void) const;
    virtual bool initialize_for_new_map(void) const;
    virtual void dispose_from_old_map(void) const;
    virtual void initialize_for_new_round(void) const;
    virtual void stats_reset_for_round_switch(void) const;
    virtual bool validate_team_designator_for_new_map(e_multiplayer_team_designator team_designator) const;
    virtual void build_valid_team_mapping(
        c_flags<e_multiplayer_team_designator, unsigned short, k_multiplayer_team_designator_count> * valid_team_designators,
        c_flags<e_multiplayer_team, unsigned short, static_cast<e_multiplayer_team>(8)> * valid_teams,
        c_flags<e_multiplayer_team_designator, unsigned short, k_multiplayer_team_designator_count> * active_team_designators,
        s_static_array<c_enum<e_multiplayer_team_designator, char, _multiplayer_team_designator_none, k_multiplayer_team_designator_count, s_multiplayer_team_designator_string_resolver>, 8> * team_designator_mapping) const;
    virtual void player_added(long player_index) const;
    virtual void player_activated(long player_index) const;
    virtual void player_left(long player_index) const;
    virtual void player_rejoined(long player_index) const;
    virtual void player_changed_indices(long player_old_index, long player_new_index) const;
    virtual void player_changed_teams(long player_index) const;
    virtual void player_about_to_spawn(long player_index) const;
    virtual void player_just_spawned(long player_index) const;
    virtual void game_ending(void) const;
    virtual void game_starting(void) const;
    virtual void render(long player_index) const;
    virtual void render_debug(long player_index) const;
    virtual void submit_navpoints(e_output_user_index user_index, long named_player_index) const;
    virtual bool build_player_navpoint(e_output_user_index user_index, long target_player_index, long named_player_index, bool name_only, c_chud_navpoint * navpoint) const;
    virtual bool should_draw_navpoint(e_output_user_index user_index, long target_player_index) const;
    virtual void update(void) const;
    virtual void player_update(long player_index) const;
    virtual void apply_baseline_traits_for_player(long player_index, c_player_traits * traits) const;
    virtual void apply_game_engine_traits_for_player(long player_index, c_player_traits * traits) const;
    virtual void apply_ai_traits(c_ai_traits * traits) const;
    virtual void assemble_spawn_influencers_for_player(long player_index, s_netgame_goal_influencer * influencers, long * in_out_count) const;
    virtual bool coop_spawning_enabled(long player_index) const;
    virtual long compare_players(long player_index_a, long player_index_b) const;
    virtual long compare_teams(e_multiplayer_team team_a, e_multiplayer_team team_b) const;
    virtual char const * get_key_set_from_scoring_type(long scoring_type) const;
    virtual bool allow_weapon_pickup(long player_index, long weapon_index) const;
    virtual bool should_auto_pickup_weapon(long player_index, long weapon_index) const;
    virtual bool does_weapon_have_pickup_priority(long weapon_index) const;
    virtual bool requires_scenario_object(long scenario_datum_index, e_object_type object_type, long object_definition_index, s_scenario_object const * scenario_object, s_scenario_multiplayer_object_properties const * multiplayer_properties) const;
    virtual bool requires_unplaced_object(s_object_placement_data const * placement_data) const;
    virtual long object_get_emblem_player(long object_index) const;
    virtual float compute_object_function(long object_index, long function) const;
    virtual void handle_new_multiplayer_object(long object_index) const;
    virtual void handle_deleted_object(long object_index) const;
    virtual void multiplayer_object_before_team_change(long object_index, e_multiplayer_team_designator team_designator) const;
    virtual void multiplayer_object_after_team_change(long object_index, e_multiplayer_team_designator team_designator) const;
    virtual e_multiplayer_team_designator get_player_team_designator(long player_index) const;
    virtual bool player_is_enemy(long player_index, long other_player_index) const;
    virtual bool team_is_enemy(e_multiplayer_team our_team, e_multiplayer_team other_team) const;
    virtual void score_header_string(c_static_wchar_string<256> * text) const;
    virtual bool is_medal_allowed(long medal) const;
    virtual void player_damaged_player(long killing_player_index, long killing_object_index, long dead_player_index, bool friendly_fire) const;
    virtual void player_assisted_with_kill(long assisting_player_index, long dead_player_index) const;
    virtual long player_killed_player_get_kill_message(long killing_player_index, long dead_player_index, bool friendly_fire) const;
    virtual void handle_incident_begin(void) const;
    virtual void handle_incident(long incident_type, long player_index, long object_index, s_damage_reporting_info const & damage_reporting_info) const;
    virtual void handle_incident_end(void) const;
    virtual void object_killed(long object_index, long killing_player_index, long killing_object_index, c_game_team const & killing_team, s_damage_reporting_info const & damage_reporting_info) const;
    virtual bool object_can_be_damaged(long object_index) const;
    virtual void adjust_object_gravity(long object_index, float * in_out_gravity) const;
    virtual bool player_purchase_menu_available(long player_index) const;
    virtual c_flags<e_scenario_requisition_trigger_volume_flag, unsigned short, static_cast<e_scenario_requisition_trigger_volume_flag>(5)> get_player_purchase_flags(long player_index) const;
    virtual long get_current_object_price(scenario_requisition_palette_entry const * palette_entry, long player_index) const;
    virtual bool handle_player_laser_designation(long player_index) const;
    virtual void prepare_for_new_state(long new_state) const;
    virtual bool should_end_round(long * winner_index) const;
    virtual bool should_update_round_timer(void) const;
    virtual e_game_engine_status get_player_state_index(long player_index, bool * state_is_overridable) const;
    virtual void close_any_custom_ui(e_output_user_index user_index) const;
    virtual e_simulation_entity_type get_simulation_entity_type(void) const;

    // f i (game_engine_sandbox.obj)
    virtual void detach_from_simulation(void) const
    {
    };

    virtual void promote_to_simulation_authority(c_bitstream * packet, e_game_engine_restoration_type restoration_type) const;
    virtual void build_snapshot_state(c_bitstream * packet) const;
    virtual void recover_state_before_promotion(void) const;
    virtual void notify_authority_that_client_reset_game_engine_state(void) const;
    virtual void build_global_baseline(s_game_engine_state_data * state_data) const;
    virtual void build_global_update(c_game_engine_update_mask update_mask, c_game_engine_update_mask * actual_update_mask, s_game_engine_state_data * state_data) const;
    virtual bool apply_global_update(c_game_engine_update_mask update_mask, s_game_engine_state_data const * state_data) const;
    virtual void build_simulation_baseline(long state_data_size, void * state_data) const;
    virtual void build_simulation_update(c_game_engine_update_mask * update_mask, long state_data_size, void * state_data) const;
    virtual bool apply_simulation_update(c_game_engine_update_mask update_mask, long state_data_size, void const * state_data) const;
    virtual void build_player_baseline(long state_data_size, void * state_data) const;
    virtual void build_player_update(short player_absolute_index, c_game_engine_update_mask * update_mask, long state_data_size, void * state_data) const;
    virtual bool apply_player_update(short player_absolute_index, c_game_engine_update_mask update_mask, long state_data_size, void const * state_data) const;
    virtual long parse_multiplayer_string_token(long player_index, wchar_t const * token, long token_length, s_incident_metadata const * incident, wchar_t * destination, long available_characters_to_write) const;

    // f i (game_engine_sandbox.obj)
    virtual bool handle_incoming_simulation_event(e_simulation_event_type type, void const * data) const
    {
        return false;
    };

    virtual bool enable_lead_change_messages(void) const;
    virtual bool enable_tied_leader_messages(void) const;
    virtual long get_message_chud_reference(void) const;

    // f i (game_engine_sandbox.obj)
    virtual long get_message_chud_reference(s_multiplayer_runtime_globals_definition * runtime_data) const
    {
        return NONE;
    };

    virtual void dump_settings(s_file_reference * file) const;
    virtual void player_hump(long player_index) const;
    virtual e_network_game_simulation_protocol get_simulation_protocol(void) const;
    virtual bool requires_valid_multiplayer_globals_in_scenario(void) const;
    virtual bool desires_round_based_fading(void) const;
    virtual bool competitive_game_in_progress(void) const;
    virtual bool desires_garbage_collection(void) const;
    virtual bool desires_influence_based_spawning(void) const;
    virtual bool desires_teleporters(void) const;

protected:
    virtual void emit_game_start_event(long player_index) const;
    virtual void fire_team_get_interface_state(long player_index, game_engine_interface_state * interface_state) const;
    virtual void build_interface_fireteam_member_status(long player_index, long fireteam_member_player_index, s_mp_objective_fireteam_member * fireteam_member_status) const;
};
static_assert(sizeof(c_game_engine) == 0x4, "c_game_engine");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_ENGINE_DEFAULT_H__

