#pragma once
#ifndef __SCENARIO_H__
#define __SCENARIO_H__

/* ---------- headers */

/* ---------- constants */

// Reach: c_enum_no_init<e_scenario_type, short, 0, 5>; values checked against cache_file_get_maximum_size
enum e_scenario_type
{
    _scenario_type_invalid = -1,
    _scenario_type_solo = 0,
    _scenario_type_multiplayer,
    _scenario_type_main_menu,
    _scenario_type_multiplayer_shared,
    _scenario_type_single_player_shared,

    k_scenario_type_count
};

/* ---------- definitions */

struct scenario;
struct s_game_globals;
struct structure_bsp;
struct s_cluster_reference;
union real_point3d;

struct s_scenario_game_state
{
    unsigned long flags; // 0x0 c_flags_no_init<e_scenario_game_state_bit, unsigned long, 1>
    long zone_set_index; // 0x4
    unsigned long designer_zone_mask; // 0x8
    unsigned long active_bsp_mask; // 0xC
    unsigned long touched_bsp_mask; // 0x10
    unsigned long cinematic_zone_mask; // 0x14
    unsigned long touched_cinematic_zone_mask; // 0x18
};

/* ---------- prototypes */

// void scenario_initialize(void);
// void scenario_dispose(void);
// void scenario_initialize_for_new_map(void);
// void scenario_dispose_from_old_map(void);
// void scenario_initialize_for_new_structure_bsp(unsigned long);
// void scenario_initialize_for_new_structure_bsp_internal(long, struct s_structure_seams const *, unsigned long);
// void scenario_dispose_from_old_structure_bsp(unsigned long);
// void scenario_frame_update(float);
// char const * scenario_get_name(void);
// char const * scenario_get_path(void);
// void scenario_force_pruning_for_cubemaps(void);
// bool scenario_save_tag_groups_state(class c_persist_stream *);
// bool scenario_restore_tag_groups_state(class c_persist_stream *);
// bool scenario_load(enum e_game_mode, enum e_campaign_id, enum e_map_id, struct s_scenario_tags_load_parameters const *);
// void scenario_invalidate_internal(void);
// void scenario_invalidate_zone_set_internal(void);
// bool scenario_tag_package_load(char const *);
// bool scenario_load(enum e_game_mode, enum e_campaign_id, enum e_map_id, char const *, enum e_language);
// class c_empty_wrapped_array make_empty_wrapped_array(void);
// void scenario_unload(void);
// enum e_scenario_content_source global_scenario_content_source_get(struct scenario const *);
// enum e_scenario_content_source global_scenario_master_content_source_get(struct scenario const *);
// struct s_structure_seams const * global_structure_seams_get(void);
// struct s_structure_seams const * global_structure_seams_get(struct scenario const *, enum e_scenario_content_source);
// long global_scenario_get_game_globals_tag_index(void);
// void scenario_set_name_on_reload(char const *);
// void scenario_unload_level_only(void);
// bool scenario_is_quick_loading(void);
// enum e_scenario_type scenario_get_type(char const *, unsigned short *);
// enum e_scenario_type global_scenario_get_type(unsigned short *);
// enum e_scenario_type global_scenario_try_and_get_type(unsigned short *);
// void global_scenario_handle_tag_reloads(void);
// long scenario_tag_load(unsigned long, char const *);
// void scenario_reconnect_active_zone_set(void);
// public: c_tag_resources_game_lock::c_tag_resources_game_lock(void);
// public: c_tag_resources_game_lock::~c_tag_resources_game_lock(void);
// void scenario_commit_new_zone_set_internal(long, bool);
// void scenario_zones_render_debug(void);
// void scenario_display_zone_size_estimates(bool);
// void scenario_dump_zone_size_estimates(void);
// char const * scenario_tag_get_structure_bsp_name(long, long);
// char const * scenario_get_structure_bsp_name(long);
// char const * scenario_get_structure_bsp_string_from_mask(unsigned long, char *, unsigned int);
// char const * scenario_get_designer_zone_string_from_mask(unsigned long, char *, unsigned int);
// char const * scenario_get_cinematic_zone_string_from_mask(unsigned long, char *, unsigned int);
// char const * scenario_zone_set_get_name(long);
// long global_structure_bsp_first_active_index_get(void);
extern long global_structure_bsp_first_active_index_get();
// long global_structure_bsp_next_active_index_get(long);
extern long global_structure_bsp_next_active_index_get(long structure_bsp_index);
// long global_structure_design_first_active_index_get(void);
// unsigned long global_structure_design_active_mask_get(void);
// long global_structure_design_next_active_index_get(long);
// bool global_structure_design_is_active(long);
// unsigned long global_structure_bsp_active_mask_get(void);
extern unsigned long global_structure_bsp_active_mask_get();
// bool global_structure_bsp_is_active(long);
// bool global_cinematic_zone_is_active(long);
// unsigned long scenario_get_touched_bsp_mask_internal(void);
extern unsigned long global_designer_zone_active_mask_get();
// unsigned long global_cinematic_zone_active_mask_get(void);
// unsigned long scenario_get_touched_cinematics_mask_internal(void);
// class c_collision_bsp_reference global_collision_bsp_get(long);
// enum e_registered_threads get_current_thread_cache_context(void);
// struct structure_instanced_geometry_definition const * global_instance_geometry_definition_get(long, long);
// struct s_tag_block * global_instance_definitions_block_get(long);
// enum e_scenario_content_source global_structure_bsp_tag_source_get(struct scenario const *, long);
// bool global_structure_tag_manifest_matches(struct scenario const *, char const *, enum e_scenario_content_source);
// struct s_tag_reference const * global_structure_bsp_tag_reference_get_explicit_source(struct scenario const *, long, enum e_scenario_content_source);
// struct s_tag_reference const * global_structure_bsp_tag_reference_get(struct scenario const *, long);
extern struct s_tag_reference const * global_structure_bsp_tag_reference_get(scenario const * scenario, long structure_bsp_index);
// struct s_tag_reference * global_structure_bsp_tag_reference_get_writable(struct scenario *, long);
// long global_structure_bsp_tag_index_get(struct scenario const *, long);
extern long global_structure_bsp_tag_index_get(scenario const * scenario, long structure_bsp_index);
// struct structure_bsp const * global_structure_bsp_get(long);
extern structure_bsp const * global_structure_bsp_get(long structure_bsp_index);
// struct structure_bsp const * global_structure_bsp_get(struct scenario const *, long);
// struct structure_bsp const * global_structure_bsp_try_and_get(long);
// struct structure_bsp const * global_structure_bsp_try_and_get(struct scenario const *, long);
// enum e_scenario_content_source global_structure_design_tag_source_get(struct scenario const *, long);
// struct s_tag_reference const * global_structure_design_tag_reference_get(struct scenario const *, long);
// struct s_tag_reference * global_structure_design_tag_reference_get_writable(struct scenario *, long);
// long global_structure_design_tag_index_get(struct scenario const *, long);
// struct s_structure_design const * global_structure_design_get(struct scenario const *, long);
// struct s_tag_reference const * global_structure_lighting_info_tag_reference_get(struct scenario const *, long);
// struct s_structure_lighting_info const * global_structure_lighting_info_get(long);
extern long global_scenario_index_get();
// long global_scenario_game_globals_index_get(void);
extern long global_scenario_game_globals_index_get();
// struct scenario * global_scenario_get_internal(bool);
// bool game_tag_defense_enabled(void);
// struct scenario * global_scenario_get(void);
extern scenario * global_scenario_get();
// struct scenario * global_scenario_try_and_get(void);
extern scenario * global_scenario_try_and_get();
// struct s_game_globals * scenario_get_game_globals(void);
extern struct s_game_globals * scenario_get_game_globals();
extern s_game_globals * scenario_try_and_get_game_globals();
// long global_structure_bsp_tag_index_get(long);
// bool scenario_location_valid(struct s_location);
// bool scenario_cluster_reference_valid(struct s_cluster_reference);
// void scenario_location_from_leaf(struct s_location *, long, long);
// void scenario_location_from_point(struct s_location *, union real_point3d const *);
// void scenario_location_from_line(struct s_location *, struct s_location const *, union real_point3d const *, union real_point3d const *);
// bool scenario_location_deafening(struct s_location const *);
// bool scenario_illumination_at_point(union real_point3d const *, union vector3d *, union vector3d *, union rgb_color *, union rgb_color *);
// bool scenario_ensure_point_within_world(union real_point3d *);
// long scenario_leaf_index_from_point(long, union real_point3d const *);
// long scenario_leaf_index_from_point(union real_point3d const *, long *);
// struct s_cluster_reference scenario_cluster_reference_from_leaf_index(long, long);
// struct s_cluster_reference scenario_cluster_reference_from_point(long, union real_point3d const *);
// struct s_cluster_reference scenario_cluster_reference_from_point(union real_point3d const *);
extern s_cluster_reference scenario_cluster_reference_from_point(real_point3d const * point);
// short scenario_structure_index_from_point(union real_point3d const *);
// bool scenario_test_pvs(struct s_cluster_reference, struct s_cluster_reference);
// bool scenario_location_potentially_visible_local(struct s_location const *);
// bool scenario_location_potentially_visible(struct s_location const *);
// short scenario_object_name_index_from_string(struct scenario const *, long);
// bool scenario_position_underwater(union real_point3d const *, class c_global_material_type *, union rgb_color *, float *);
// public: s_water_physics_test_sphere_result::s_water_physics_test_sphere_result(void);
// float scenario_position_water_depth(union real_point3d const *);
// long scenario_zone_set_index_get(void);
extern long scenario_zone_set_index_get();
// long scenario_zone_set_index_from_string(char const *);
// char const * scenario_zone_set_string_get(void);
// char const * scenario_zone_set_string_get(long);
// long scenario_zone_set_name_get(void);
// long scenario_zone_set_index_get_if_fully_activated(void);
// unsigned long scenario_get_startup_designer_zone_mask(void);
// bool scenario_preload_initial_zone_set(char const *);
// void scenario_recover_from_tag_package_load(void);
// bool scenario_activate_initial_designer_zones(long);
// bool scenario_zone_set_is_fully_active(long);
// void scenario_reset_zone_resources_from_main(void);
// bool scenario_activate_initial_zone_set(long);
// bool scenario_connect_zone_set_resources(long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, bool);
// void scenario_zone_set_debug_status(char const *, long);
// bool scenario_prepare_to_switch_zone_set(long);
// void scenario_do_resource_fixup_for_havok(void);
// bool scenario_modify_zone_activation_internal(long, unsigned long, unsigned long, unsigned long, struct s_scenario_zone_change const *, unsigned long, bool);
// bool scenario_disconnect_game_from_old_bsps(unsigned long, unsigned long);
// void scenario_unload_old_bsps(unsigned long, unsigned long, bool);
// bool scenario_postprocess_new_bsps_after_zone_switch(unsigned long);
// bool scenario_add_preplaced_decals_to_new_bsps_after_zone_switch(unsigned long);
// bool scenario_load_new_bsps(unsigned long, unsigned long, unsigned long *);
// void scenario_connect_game_resources_to_new_bsps(unsigned long, unsigned long);
// bool scenario_connect_game_to_new_bsps(unsigned long, unsigned long);
// void scenario_disconnect_from_old_zone_set(unsigned long, unsigned long);
// bool scenario_prepare_zone_set_for_cache_builder(long);
// bool scenario_switch_zone_set_internal(long, bool);
// void scenario_activate_all_designer_zones(void);
// void scenario_deactivate_all_zones_for_cache_builder(void);
extern bool scenario_switch_zone_set(long);
// void scenario_switch_to_null_zone_set(void);
// void scenario_detach_game_from_old_non_bsp_zones(unsigned long, unsigned long, struct s_scenario_zone_change const *, bool);
// public: unsigned long s_scenario_zone_change::get_deactivating_designer_zone_mask(void) const;
// public: unsigned long s_scenario_zone_change::get_deactivating_cinematic_zone_mask(void) const;
// public: unsigned long s_scenario_zone_change::pre_switch_designer_zone_mask(void) const;
// public: unsigned long s_scenario_zone_change::pre_switch_cinematic_zone_mask(void) const;
// public: bool s_scenario_zone_change::any_zone_changes(void) const;
// public: bool s_scenario_zone_change::any_designer_zone_changes(void) const;
// public: bool s_scenario_zone_change::any_cinematic_zone_changes(void) const;
// bool scenario_attach_game_to_new_non_bsp_zones(struct s_scenario_zone_change const *);
// public: unsigned long s_scenario_zone_change::get_activating_designer_zone_mask(void) const;
// public: unsigned long s_scenario_zone_change::get_activating_cinematic_zone_mask(void) const;
// bool scenario_modify_active_zones(struct s_scenario_zone_activation const *);
// bool scenario_switch_to_designer_zone_mask(unsigned long);
// bool scenario_activate_structure_bsp(long);
// void scenario_get_global_zone_state(struct s_scenario_zone_state *);
// unsigned long debug_touched_bsp_active_mask_get(void);
// long scenario_get_zone_set_index_by_name(struct scenario const *, char const *, bool);
// char const * scenario_get_structure_bsp_path(struct scenario const *, short);
// long scenario_get_structure_bsp_reference_index_by_name(struct scenario const *, char const *, bool);
// void scenario_player_get_position_and_facing(struct scenario_player_starting_location const *, union real_point3d *, float *);
// void scenario_debug_lruv_cache_to_file(void *, class c_formatted_output *);
// char const * global_scenario_zone_set_get_name(void);
// void scenario_rebuild_active_zone_set(void);
// public: c_wait_for_render_thread::c_wait_for_render_thread(char const *, long);
// public: c_wait_for_render_thread::~c_wait_for_render_thread(void);
// void scenario_reload_active_zone_set(void);
// void scenario_set_and_activate_runtime_cinematic_tag(long);
// void scenario_handle_invalid_structure_materials(void);
// void scenario_recalculate_all_bsp_geometry_flags(void);
// long scenario_load_and_connect_game_globals(void);
// void scenario_make_flags_and_prune(long);
// bool scenario_tags_load(enum e_game_mode, struct s_scenario_tags_load_parameters const *);
// struct s_ai_globals_data * ai_globals_try_and_get_data(struct s_ai_globals_definition const *);
// public: c_tag_group_allocation_section_timer::c_tag_group_allocation_section_timer(void);
// public: void c_tag_group_allocation_section_timer::report(char const *);
// public: void c_tag_group_allocation_section_timer::reset(void);
// public: void c_section_thread_timer::mark(char const *);
// public: c_section_thread_timer::c_section_thread_timer(void);
// public: c_scenario_tag_prediction_manager::c_scenario_tag_prediction_manager(void);
// public: virtual bool c_scenario_tag_prediction_manager::predict_tag(unsigned long, char const *);
// public: c_tag_files_prediction_manager::c_tag_files_prediction_manager(void);
// void scenario_tags_load_finished(void);
// bool scenario_tag_package_tags_load(char const *);
// void scenario_load_tag_children(long);
// void scenario_tags_unload(void);
// void scenario_structure_bsp_unload(long, short, struct s_tag_reference *);
// public: virtual void `void scenario_structure_bsp_unload(long, short, struct s_tag_reference *)'::`2'::c_structure_bsp_unload_visitor::visit(enum e_scenario_bsp_tag, struct s_tag_reference *);
// public: `void scenario_structure_bsp_unload(long, short, struct s_tag_reference *)'::`2'::c_structure_bsp_unload_visitor::c_structure_bsp_unload_visitor(void);
// public: c_scenario_bsp_tags_visitor::c_scenario_bsp_tags_visitor(void);
// bool scenario_structure_bsp_load(long, short, struct s_tag_reference *);
// public: virtual void `bool scenario_structure_bsp_load(long, short, struct s_tag_reference *)'::`3'::c_structure_bsp_load_visitor::visit(enum e_scenario_bsp_tag, struct s_tag_reference *);
// bool scenario_resolve_tag_reference(struct s_tag_reference *);
// public: `bool scenario_structure_bsp_load(long, short, struct s_tag_reference *)'::`3'::c_structure_bsp_load_visitor::c_structure_bsp_load_visitor(void);
// bool scenario_language_pack_load(void);
// void scenario_language_pack_unload(void);
// bool scenario_structure_bsp_load_runtime(long, short, struct s_tag_reference *);
// bool scenario_tags_match(enum e_campaign_id, enum e_map_id, char const *);
// void scenario_initialize_scenario_soft_ceilings_for_activating_structure_bsps(long, unsigned long);
// void scenario_zone_set_fixup_and_build_pvs(long);
// bool scenario_active_zone_is_tag_available(long);
// long scenario_budget_resource_get_model_animation_graph_reference(long);
// long scenario_budget_resource_get_looping_sound_reference(long);
// long scenario_budget_resource_get_sound_reference(long);
// bool scenario_use_designer_zones(void);
extern bool scenario_use_designer_zones();
// bool scenario_do_not_attach_unused_designer_zone_resources(void);
// bool scenario_couple_structure_objects_to_structure(void);
// void scenario_initialize_game_state(struct s_scenario_game_state *);
// bool scenario_prepare_for_game_state_revert(struct s_scenario_game_state const *);
// bool scenario_game_states_match(struct s_scenario_game_state const *, struct s_scenario_game_state const *);
// bool scenario_game_state_matches_global_state(struct s_scenario_game_state const *);
// void scenario_game_state_grab_global_state(struct s_scenario_game_state *);
// bool scenario_position_inside_safe_zone(union real_point3d const *, bool);
// void scenario_prepare_for_map_reset(char const *);
// class c_static_string<256> scenario_game_state_describe(struct s_scenario_game_state const *);
// void scenario_handle_tag_resource_lock(long);
extern void scenario_handle_tag_resource_lock(long thread_index);
// void scenario_handle_tag_resource_unlock(long);
extern void scenario_handle_tag_resource_unlock(long thread_index);
// void scenario_alias_tag_resource_shortcuts_to_thread(long);
// void scenario_clear_tag_resource_shortcuts_in_thread(long);
// bool scenario_is_in_space(void);
// struct s_tag_block * scenario_get_palette_block(struct scenario *, enum e_scenario_palette);
// struct s_tag_reference * scenario_get_tag_reference_from_palette_entry(struct scenario *, enum e_scenario_palette, long);
// enum e_scenario_palette scenario_get_palette_from_tag(unsigned long);
// unsigned long scenario_get_tag_from_palette(enum e_scenario_palette);
// struct s_tag_block * scenario_get_requisition_palette(long);
// bool scenario_player_can_use_requisition_zone(long, long, struct s_scenario_requisition_trigger_volume const *);
// bool scenario_player_is_in_requisition_zone(long, long);
// class c_flags<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> scenario_player_get_requisition_zone_flags(long, long);
// void scenario_get_location_name_by_player(long, class c_static_wchar_string<32> *, union real_point3d *);
// void scenario_get_location_name_by_unit(long, class c_static_wchar_string<32> *, union real_point3d *);
// void scenario_print_zone_sets(void);
// void scenario_print_current_zone_set(void);
// void scenario_debug_update(void);
// void scenario_print_map_info(bool);
// void print_message_to_source(bool, long *, char const *, ...);
// void scenario_print_map_info(void);
// public: virtual void c_tag_groups_scenario_memory_usage::report_usage(void);
// public: virtual void c_tag_groups_scenario_memory_usage::report_brief(long, char *);
// public: virtual long c_tag_groups_scenario_memory_usage::upload_report(long, class c_file_path *);
// public: enum e_scenario_type c_enum_no_init<enum e_scenario_type, short, 0, 5, struct s_default_enum_string_resolver>::operator enum e_scenario_type(void) const;
// public: c_flags<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::c_flags<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>(class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>);
// public: c_stop_watch_template<class c_default_stop_watch_traits>::c_stop_watch_template<class c_default_stop_watch_traits>(void);
// public: c_stop_watch_template<class c_thread_stop_watch_traits>::c_stop_watch_template<class c_thread_stop_watch_traits>(void);
// public: struct c_status_line * s_static_array<struct c_status_line, 16>::get_elements(void);
// public: static long s_static_array<struct c_status_line, 16>::get_count(void);
// public: c_flags<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::c_flags<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>(class c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>);
// public: c_wrapped_array<char>::c_wrapped_array<char>(char *, long);
// public: char * c_wrapped_array_no_init<char>::begin(void);
// public: long c_wrapped_array_no_init<char>::count(void) const;
// public: void c_wrapped_array_no_init<char>::set_elements(char *, long);
// public: bool c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::test(enum e_scenario_requisition_trigger_volume_flag) const;
// public: class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::operator|(class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> const &) const;
// public: class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> & c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::operator|=(class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> const &);
// public: static class c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver> c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::make_flag(enum e_scenario_requisition_trigger_volume_flag);
// public: unsigned short c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::get_unsafe(void) const;
// public: void c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::set_unsafe(unsigned short);
// public: c_flags<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::c_flags<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>(void);
// public: unsigned long const * c_big_flags_typed_no_init<long, 20000>::get_bits_direct(void) const;
// public: void c_big_flags_typed_no_init<long, 20000>::set_bits_direct_destructive(long, unsigned long const *);
// public: void c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::test(enum e_scenario_game_state_bit) const;
// public: void c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::set(enum e_scenario_game_state_bit, bool);
// public: bool c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::operator==(class c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver> const &) const;
// class c_wrapped_array<char const *> make_wrapped_array<char const *, 1>(char const * (&)[1]);
// public: class c_wrapped_array<char const *> c_empty_wrapped_array::operatorcast<char const *>(void);
// public: void s_static_string<1024>::print_va(char const *, char *);
// public: class c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver> c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::operator|(class c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver> const &) const;
// public: static class c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver> c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::make_flag(enum e_scenario_prune_flags);
// public: unsigned long c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::get_unsafe(void) const;
// public: void c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::set_unsafe(unsigned long);
// public: c_flags<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::c_flags<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>(void);
// public: wchar_t const * c_static_wchar_string<32>::print(wchar_t const *, ...);
// public: struct c_status_line & s_static_array<struct c_status_line, 16>::operator[]<long>(long);
// public: unsigned long & s_static_array<unsigned long, 256>::operator[]<long>(long);
// public: c_wrapped_array<char const *>::c_wrapped_array<char const *>(void);
// public: void c_wrapped_array_no_init<char const *>::set_elements(char const **, long);
// public: void c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::is_clear(void) const;
// public: static bool c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::valid_bit(enum e_scenario_requisition_trigger_volume_flag);
// public: bool c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::valid(void) const;
// private: static unsigned short c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::flag_size_type(enum e_scenario_requisition_trigger_volume_flag);
// public: bool c_big_flags_typed_no_init<long, 20000>::valid(void) const;
// public: static bool c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::valid_bit(enum e_scenario_game_state_bit);
// private: static unsigned long c_flags_no_init<enum e_scenario_game_state_bit, unsigned long, 1, struct s_default_enum_string_resolver>::flag_size_type(enum e_scenario_game_state_bit);
// public: c_wrapped_array<char const *>::ctor<1>(char const * (&)[1]);
// public: void c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::is_clear(void) const;
// public: static bool c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::valid_bit(enum e_scenario_prune_flags);
// public: bool c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::valid(void) const;
// private: static unsigned long c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::flag_size_type(enum e_scenario_prune_flags);
// public: static bool s_static_array<struct c_status_line, 16>::valid<long>(long);
// public: static bool s_static_array<unsigned long, 256>::valid<long>(long);
// private: static unsigned short c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// protected: static unsigned long c_big_flags_typed_no_init<long, 20000>::get_mask_of_second_slice_of_chunk_inclusive(long);
// private: static unsigned long c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned short c_flags_no_init<enum e_scenario_requisition_trigger_volume_flag, unsigned short, 5, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_scenario_requisition_trigger_volume_flag);
// protected: static long c_big_flags_typed_no_init<long, 20000>::flag_chunk_index_to_bit_index(long);
// protected: static long c_big_flags_typed_no_init<long, 20000>::bit_index_to_flag_chunk_index(long);
// protected: static unsigned long c_big_flags_typed_no_init<long, 20000>::get_valid_mask_of_last_chunk(void);
// private: static unsigned long c_flags_no_init<enum e_scenario_prune_flags, unsigned long, 8, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_scenario_prune_flags);
// protected: static unsigned long c_big_flags_typed_no_init<long, 20000>::get_mask_of_first_slice_of_chunk_exclusive(long);
// public: c_scenario_zone_tags_registry::c_scenario_zone_tags_registry(void);
// public: virtual void c_tag_groups_observer::on_tag_postprocess_success(long);
// public: virtual void c_tag_groups_observer::on_tag_resolved(long, long);
// public: virtual void c_tag_groups_observer::on_tag_delete_end(long);
// public: virtual void c_tag_groups_observer::on_tag_reload_begin(long);
// public: virtual void c_tag_groups_observer::on_tag_reload_succeeded(long);
// public: virtual void c_tag_groups_observer::on_tag_reload_failed(long);
// public: virtual void c_tag_groups_observer::on_tag_get(long);
// public: c_tag_groups_observer::c_tag_groups_observer(void);
// public: virtual void c_tag_groups_observer::on_tag_new(long);
// public: virtual void c_tag_groups_observer::on_tag_delete_begin(long);
// public: s_static_array<class c_tag_marker, 16>::s_static_array<class c_tag_marker, 16>(void);
// public: s_static_array<class c_tag_marker, 32>::s_static_array<class c_tag_marker, 32>(void);
// public: s_static_array<class c_scenario_bsp_zone_lightmap_resources_registry, 16>::s_static_array<class c_scenario_bsp_zone_lightmap_resources_registry, 16>(void);
// public: s_static_array<struct c_scenario_zone_tags_registry::s_zone_status_line, 16>::s_static_array<struct c_scenario_zone_tags_registry::s_zone_status_line, 16>(void);
// public: s_static_array<struct c_scenario_zone_tags_registry::s_zone_status_line, 32>::s_static_array<struct c_scenario_zone_tags_registry::s_zone_status_line, 32>(void);
// public: c_scenario_zone_tags_registry::s_zone_status_line::s_zone_status_line(void);
// public: c_scenario_tags_estimated_size_registry::c_scenario_tags_estimated_size_registry(void);
// public: c_scenario_bsp_zone_lightmap_resources_registry::c_scenario_bsp_zone_lightmap_resources_registry(void);
// public: c_static_sized_dynamic_array<long, 3>::c_static_sized_dynamic_array<long, 3>(void);
// public: c_static_string<40>::c_static_string<40>(void);
// public: void s_static_string<40>::clear(void);
// public: c_tag_groups_scenario_memory_usage::c_tag_groups_scenario_memory_usage(void);
// public: c_debug_memory_reporter::c_debug_memory_reporter(void);
// public: s_static_array<struct c_status_line, 16>::s_static_array<struct c_status_line, 16>(void);
// public: s_collision_bsp_cache::s_collision_bsp_cache(void);
// public: s_collision_resource_address_table::s_collision_resource_address_table(void);

/* ---------- globals */

/* ---------- public code */

inline void game_tag_defense_push(bool enable)
{
    mangled_ppc("?game_tag_defense_push@@YAX_N@Z");
};

inline void game_tag_defense_pop(void)
{
    mangled_ppc("?game_tag_defense_pop@@YAXXZ");
};

class c_game_tag_defense_push_scope
{
public:
    c_game_tag_defense_push_scope(bool enable)
    {
        mangled_ppc("??0c_game_tag_defense_push_scope@@QAA@_N@Z");

        game_tag_defense_push(enable);
    };

    ~c_game_tag_defense_push_scope(void)
    {
        mangled_ppc("??1c_game_tag_defense_push_scope@@QAA@XZ");

        game_tag_defense_pop();
    };
};

#endif // __SCENARIO_H__
