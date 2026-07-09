/* ---------- headers */

#include "omaha\simulation\simulation_entity_database.h"
#include "omaha\simulation\game_interface\simulation_game_entities.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_simulation_entity_database::initialize(class c_simulation_world *, class c_replication_entity_manager *, class c_simulation_type_collection *);
// public: void c_simulation_entity_database::reset(void);
// public: void c_simulation_entity_database::destroy(void);
// public: void c_simulation_entity_database::process_pending_updates(void);
// public: bool c_replication_entity_manager::is_entity_local(long) const;
// private: struct s_replication_entity_data * c_replication_entity_manager::get_entity(long) const;
// public: bool c_replication_entity_manager::is_entity_being_deleted(long) const;
// public: class c_simulation_entity_definition * c_simulation_type_collection::get_entity_definition(enum e_simulation_entity_type) const;
// public: char const * c_simulation_entity_database::get_entity_type_name(enum e_simulation_entity_type) const;
// public: struct s_simulation_entity const * c_simulation_entity_database::entity_get(long) const;
// public: bool c_replication_entity_manager::is_entity_allocated(long) const;
// private: struct s_replication_entity_data * c_replication_entity_manager::try_and_get_entity(long) const;
// public: struct s_simulation_entity * c_simulation_entity_database::entity_get(long);
// public: struct s_simulation_entity const * c_simulation_entity_database::entity_try_and_get(long) const;
// public: struct s_simulation_entity * c_simulation_entity_database::entity_try_and_get(long);
// public: bool c_simulation_entity_database::entity_is_required_to_join(long) const;
// public: bool c_simulation_entity_database::entity_is_local(long) const;
// public: long c_simulation_entity_database::entity_create(enum e_simulation_entity_type);
// public: void c_simulation_entity_database::entity_capture_creation_data(long);
// bool simulation_entity_type_is_object(enum e_simulation_entity_type);
// public: void c_simulation_entity_database::entity_delete(long);
// public: void c_simulation_entity_database::entity_update(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, bool);
// public: void c_simulation_entity_database::rotate_entity_index(long *) const;
// public: void c_simulation_entity_database::event_reference_add(long, class c_replication_outgoing_event const *);
// public: class c_simulation_event_definition * c_simulation_type_collection::get_event_definition(enum e_simulation_event_type) const;
// public: long c_replication_outgoing_event::get_type(void) const;
// public: void c_simulation_entity_database::event_reference_remove(long, class c_replication_outgoing_event const *);
// public: bool c_simulation_entity_database::calculate_creation_requirements(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, float *);
// public: void c_simulation_entity_database::write_creation_description_to_string(long, void const *, long, char *);
// public: bool c_simulation_entity_database::write_creation_to_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, class c_bitstream *, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *);
// public: long c_bitstream::get_space_left_in_bits(void) const;
// public: s_entity_update_encode_data::s_entity_update_encode_data(void);
// public: void s_entity_update_encode_data::set_entity_index(long);
// void simulation_profiler_recorder_record_start(class c_bitstream *, enum e_simulation_profiler_bandwidth_use_context, enum e_simulation_profiler_attribute_type_value);
// void simulation_profiler_recorder_record_set_attribute(enum e_simulation_profiler_attribute, unsigned char);
// void simulation_profiler_recorder_record_cancel(void);
// void simulation_profiler_recorder_record_stop(class c_bitstream *);
// public: enum e_network_read_result c_simulation_entity_database::read_creation_from_packet(long, long *, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *, long, long *, struct s_replication_allocation_block *, class c_bitstream *);
// public: bool c_bitstream::read_only_for_consistency(void) const;
// public: s_entity_update_decode_data::s_entity_update_decode_data(void);
// void simulation_profiler_recorder_record_cancel_if_necessary(void);
// void simulation_profiler_recorder_set_current_object_index(long);
// public: void c_simulation_entity_database::process_creation(long, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, long, struct s_replication_allocation_block *);
// public: bool c_simulation_entity_database::calculate_update_requirements(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, unsigned long, void const *, float *);
// public: s_entity_evaluate_update_inputs::s_entity_evaluate_update_inputs(void);
// public: s_entity_evaluate_update_outputs::s_entity_evaluate_update_outputs(void);
// public: void c_simulation_entity_database::write_update_description_to_string(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, unsigned long, void const *, long, char *);
// public: bool c_simulation_entity_database::write_update_to_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, class c_bitstream *, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *);
// long simulation_object_glue_get_object_index(long);
// public: enum e_network_read_result c_simulation_entity_database::read_update_from_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *, struct s_received_packet_info const *, long, long *, struct s_replication_allocation_block *, class c_bitstream *);
// public: void c_simulation_entity_database::process_update(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, long, struct s_replication_allocation_block *);
// public: bool c_simulation_entity_database::calculate_deletion_requirements(long, void const *, float *);
// public: void c_simulation_entity_database::notify_mark_entity_for_deletion(long, bool);
// public: void c_simulation_entity_database::notify_delete_entity(long);
// public: bool c_simulation_entity_database::notify_promote_to_authority(long);
// public: void c_simulation_entity_database::notify_creation_sent(long);
// public: void c_simulation_entity_database::rotate_entity_seed(long);
// public: class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_simulation_entity_database::generate_current_entity_update_mask(long);
// public: class c_static_string<256> c_simulation_entity_database::describe_entity(long) const;
// private: void c_simulation_entity_database::entity_create_internal(long, enum e_simulation_entity_type, long, void *, long, void *);
// private: void c_simulation_entity_database::entity_delete_gameworld(long, bool);
// private: void c_simulation_entity_database::entity_delete_internal(long);
// private: void c_simulation_entity_database::entity_validate_creation_data(long) const;
// private: void c_simulation_entity_database::entity_validate_state_data(long) const;
// private: bool c_simulation_entity_database::entity_allocate_creation_data(enum e_simulation_entity_type, long *, void **) const;
// private: bool c_simulation_entity_database::entity_allocate_state_data(enum e_simulation_entity_type, long *, void **) const;
// public: static void c_simulation_entity_database::debug_render(void);
// public: c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>);
// public: bool c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::test(enum e_replication_entity_flags) const;
// public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::is_clear(void) const;
// public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::set_range(long, long, bool);
// public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::any_flagged_outside_range(long, long) const;
// public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator==(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const;
// public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator!=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const;
// public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator~(void) const;
// public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator&(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const;
// public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> & c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator|=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &);
// public: unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::get_unsafe(void) const;
// public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::set_unsafe(unsigned __int64);
// public: c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>(void);
// public: void c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::test(enum e_simulation_entity_flag) const;
// public: void c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::set(enum e_simulation_entity_flag, bool);
// public: struct s_replication_entity_data const & s_static_array<struct s_replication_entity_data, 1024>::operator[]<long>(long) const;
// bool operator==<enum e_simulation_entity_type>(enum e_simulation_entity_type const &, enum e_none_sentinel const &);
// public: static bool c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::valid_bit(enum e_replication_entity_flags);
// private: static unsigned char c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::flag_size_type(enum e_replication_entity_flags);
// public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> & c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator&=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &);
// public: static class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_mask_from_range(long, long);
// public: static bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::valid_bit(long);
// public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::valid(void) const;
// private: static unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// public: static bool c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::valid_bit(enum e_simulation_entity_flag);
// private: static unsigned char c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::flag_size_type(enum e_simulation_entity_flag);
// public: static bool s_static_array<struct s_replication_entity_data, 1024>::valid<long>(long);
// private: static unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(long);

//public: void c_simulation_entity_database::initialize(class c_simulation_world *, class c_replication_entity_manager *, class c_simulation_type_collection *)
//{
//    mangled_ppc("?initialize@c_simulation_entity_database@@QAAXPAVc_simulation_world@@PAVc_replication_entity_manager@@PAVc_simulation_type_collection@@@Z");
//};

//public: void c_simulation_entity_database::reset(void)
//{
//    mangled_ppc("?reset@c_simulation_entity_database@@QAAXXZ");
//};

//public: void c_simulation_entity_database::destroy(void)
//{
//    mangled_ppc("?destroy@c_simulation_entity_database@@QAAXXZ");
//};

//public: void c_simulation_entity_database::process_pending_updates(void)
//{
//    mangled_ppc("?process_pending_updates@c_simulation_entity_database@@QAAXXZ");
//};

//public: bool c_replication_entity_manager::is_entity_local(long) const
//{
//    mangled_ppc("?is_entity_local@c_replication_entity_manager@@QBA_NJ@Z");
//};

//private: struct s_replication_entity_data * c_replication_entity_manager::get_entity(long) const
//{
//    mangled_ppc("?get_entity@c_replication_entity_manager@@ABAPAUs_replication_entity_data@@J@Z");
//};

//public: bool c_replication_entity_manager::is_entity_being_deleted(long) const
//{
//    mangled_ppc("?is_entity_being_deleted@c_replication_entity_manager@@QBA_NJ@Z");
//};

//public: class c_simulation_entity_definition * c_simulation_type_collection::get_entity_definition(enum e_simulation_entity_type) const
//{
//    mangled_ppc("?get_entity_definition@c_simulation_type_collection@@QBAPAVc_simulation_entity_definition@@W4e_simulation_entity_type@@@Z");
//};

//public: char const * c_simulation_entity_database::get_entity_type_name(enum e_simulation_entity_type) const
//{
//    mangled_ppc("?get_entity_type_name@c_simulation_entity_database@@QBAPBDW4e_simulation_entity_type@@@Z");
//};

//public: struct s_simulation_entity const * c_simulation_entity_database::entity_get(long) const
//{
//    mangled_ppc("?entity_get@c_simulation_entity_database@@QBAPBUs_simulation_entity@@J@Z");
//};

//public: bool c_replication_entity_manager::is_entity_allocated(long) const
//{
//    mangled_ppc("?is_entity_allocated@c_replication_entity_manager@@QBA_NJ@Z");
//};

//private: struct s_replication_entity_data * c_replication_entity_manager::try_and_get_entity(long) const
//{
//    mangled_ppc("?try_and_get_entity@c_replication_entity_manager@@ABAPAUs_replication_entity_data@@J@Z");
//};

//public: struct s_simulation_entity * c_simulation_entity_database::entity_get(long)
//{
//    mangled_ppc("?entity_get@c_simulation_entity_database@@QAAPAUs_simulation_entity@@J@Z");
//};

//public: struct s_simulation_entity const * c_simulation_entity_database::entity_try_and_get(long) const
//{
//    mangled_ppc("?entity_try_and_get@c_simulation_entity_database@@QBAPBUs_simulation_entity@@J@Z");
//};

//public: struct s_simulation_entity * c_simulation_entity_database::entity_try_and_get(long)
//{
//    mangled_ppc("?entity_try_and_get@c_simulation_entity_database@@QAAPAUs_simulation_entity@@J@Z");
//};

//public: bool c_simulation_entity_database::entity_is_required_to_join(long) const
//{
//    mangled_ppc("?entity_is_required_to_join@c_simulation_entity_database@@QBA_NJ@Z");
//};

//public: bool c_simulation_entity_database::entity_is_local(long) const
//{
//    mangled_ppc("?entity_is_local@c_simulation_entity_database@@QBA_NJ@Z");
//};

//public: long c_simulation_entity_database::entity_create(enum e_simulation_entity_type)
//{
//    mangled_ppc("?entity_create@c_simulation_entity_database@@QAAJW4e_simulation_entity_type@@@Z");
//};

//public: void c_simulation_entity_database::entity_capture_creation_data(long)
//{
//    mangled_ppc("?entity_capture_creation_data@c_simulation_entity_database@@QAAXJ@Z");
//};

bool simulation_entity_type_is_object(enum e_simulation_entity_type entity_type)
{
    mangled_ppc("?simulation_entity_type_is_object@@YA_NW4e_simulation_entity_type@@@Z");
    
    bool entity_is_object = false;
    switch (entity_type)
    {
        case _simulation_entity_type_biped:
        case _simulation_entity_type_item:
        case _simulation_entity_type_generic:
        case _simulation_entity_type_generic_garbage:
        case _simulation_entity_type_vehicle:
        case _simulation_entity_type_projectile:
        case _simulation_entity_type_weapon:
        case _simulation_entity_type_device:
            entity_is_object = true;
            break;
    }
    return entity_is_object;
};

//public: void c_simulation_entity_database::entity_delete(long)
//{
//    mangled_ppc("?entity_delete@c_simulation_entity_database@@QAAXJ@Z");
//};

//public: void c_simulation_entity_database::entity_update(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, bool)
//{
//    mangled_ppc("?entity_update@c_simulation_entity_database@@QAAXJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@_N@Z");
//};

//public: void c_simulation_entity_database::rotate_entity_index(long *) const
//{
//    mangled_ppc("?rotate_entity_index@c_simulation_entity_database@@QBAXPAJ@Z");
//};

//public: void c_simulation_entity_database::event_reference_add(long, class c_replication_outgoing_event const *)
//{
//    mangled_ppc("?event_reference_add@c_simulation_entity_database@@QAAXJPBVc_replication_outgoing_event@@@Z");
//};

//public: class c_simulation_event_definition * c_simulation_type_collection::get_event_definition(enum e_simulation_event_type) const
//{
//    mangled_ppc("?get_event_definition@c_simulation_type_collection@@QBAPAVc_simulation_event_definition@@W4e_simulation_event_type@@@Z");
//};

//public: long c_replication_outgoing_event::get_type(void) const
//{
//    mangled_ppc("?get_type@c_replication_outgoing_event@@QBAJXZ");
//};

//public: void c_simulation_entity_database::event_reference_remove(long, class c_replication_outgoing_event const *)
//{
//    mangled_ppc("?event_reference_remove@c_simulation_entity_database@@QAAXJPBVc_replication_outgoing_event@@@Z");
//};

//public: bool c_simulation_entity_database::calculate_creation_requirements(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, float *)
//{
//    mangled_ppc("?calculate_creation_requirements@c_simulation_entity_database@@QAA_NJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@PBXPAM@Z");
//};

//public: void c_simulation_entity_database::write_creation_description_to_string(long, void const *, long, char *)
//{
//    mangled_ppc("?write_creation_description_to_string@c_simulation_entity_database@@QAAXJPBXJPAD@Z");
//};

//public: bool c_simulation_entity_database::write_creation_to_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, class c_bitstream *, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *)
//{
//    mangled_ppc("?write_creation_to_packet@c_simulation_entity_database@@QAA_NJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@PBXPAVc_bitstream@@JPAV2@@Z");
//};

//public: long c_bitstream::get_space_left_in_bits(void) const
//{
//    mangled_ppc("?get_space_left_in_bits@c_bitstream@@QBAJXZ");
//};

//public: s_entity_update_encode_data::s_entity_update_encode_data(void)
//{
//    mangled_ppc("??0s_entity_update_encode_data@@QAA@XZ");
//};

//public: void s_entity_update_encode_data::set_entity_index(long)
//{
//    mangled_ppc("?set_entity_index@s_entity_update_encode_data@@QAAXJ@Z");
//};

//void simulation_profiler_recorder_record_start(class c_bitstream *, enum e_simulation_profiler_bandwidth_use_context, enum e_simulation_profiler_attribute_type_value)
//{
//    mangled_ppc("?simulation_profiler_recorder_record_start@@YAXPAVc_bitstream@@W4e_simulation_profiler_bandwidth_use_context@@W4e_simulation_profiler_attribute_type_value@@@Z");
//};

//void simulation_profiler_recorder_record_set_attribute(enum e_simulation_profiler_attribute, unsigned char)
//{
//    mangled_ppc("?simulation_profiler_recorder_record_set_attribute@@YAXW4e_simulation_profiler_attribute@@E@Z");
//};

//void simulation_profiler_recorder_record_cancel(void)
//{
//    mangled_ppc("?simulation_profiler_recorder_record_cancel@@YAXXZ");
//};

//void simulation_profiler_recorder_record_stop(class c_bitstream *)
//{
//    mangled_ppc("?simulation_profiler_recorder_record_stop@@YAXPAVc_bitstream@@@Z");
//};

//public: enum e_network_read_result c_simulation_entity_database::read_creation_from_packet(long, long *, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *, long, long *, struct s_replication_allocation_block *, class c_bitstream *)
//{
//    mangled_ppc("?read_creation_from_packet@c_simulation_entity_database@@QAA?AW4e_network_read_result@@JPAJPAV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@J0PAUs_replication_allocation_block@@PAVc_bitstream@@@Z");
//};

//public: bool c_bitstream::read_only_for_consistency(void) const
//{
//    mangled_ppc("?read_only_for_consistency@c_bitstream@@QBA_NXZ");
//};

//public: s_entity_update_decode_data::s_entity_update_decode_data(void)
//{
//    mangled_ppc("??0s_entity_update_decode_data@@QAA@XZ");
//};

//void simulation_profiler_recorder_record_cancel_if_necessary(void)
//{
//    mangled_ppc("?simulation_profiler_recorder_record_cancel_if_necessary@@YAXXZ");
//};

//void simulation_profiler_recorder_set_current_object_index(long)
//{
//    mangled_ppc("?simulation_profiler_recorder_set_current_object_index@@YAXJ@Z");
//};

//public: void c_simulation_entity_database::process_creation(long, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, long, struct s_replication_allocation_block *)
//{
//    mangled_ppc("?process_creation@c_simulation_entity_database@@QAAXJJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@JPAUs_replication_allocation_block@@@Z");
//};

//public: bool c_simulation_entity_database::calculate_update_requirements(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, unsigned long, void const *, float *)
//{
//    mangled_ppc("?calculate_update_requirements@c_simulation_entity_database@@QAA_NJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@KPBXPAM@Z");
//};

//public: s_entity_evaluate_update_inputs::s_entity_evaluate_update_inputs(void)
//{
//    mangled_ppc("??0s_entity_evaluate_update_inputs@@QAA@XZ");
//};

//public: s_entity_evaluate_update_outputs::s_entity_evaluate_update_outputs(void)
//{
//    mangled_ppc("??0s_entity_evaluate_update_outputs@@QAA@XZ");
//};

//public: void c_simulation_entity_database::write_update_description_to_string(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, unsigned long, void const *, long, char *)
//{
//    mangled_ppc("?write_update_description_to_string@c_simulation_entity_database@@QAAXJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@KPBXJPAD@Z");
//};

//public: bool c_simulation_entity_database::write_update_to_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, void const *, class c_bitstream *, long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *)
//{
//    mangled_ppc("?write_update_to_packet@c_simulation_entity_database@@QAA_NJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@PBXPAVc_bitstream@@JPAV2@@Z");
//};

//long simulation_object_glue_get_object_index(long)
//{
//    mangled_ppc("?simulation_object_glue_get_object_index@@YAJJ@Z");
//};

//public: enum e_network_read_result c_simulation_entity_database::read_update_from_packet(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> *, struct s_received_packet_info const *, long, long *, struct s_replication_allocation_block *, class c_bitstream *)
//{
//    mangled_ppc("?read_update_from_packet@c_simulation_entity_database@@QAA?AW4e_network_read_result@@JPAV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@PBUs_received_packet_info@@JPAJPAUs_replication_allocation_block@@PAVc_bitstream@@@Z");
//};

//public: void c_simulation_entity_database::process_update(long, class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>, long, struct s_replication_allocation_block *)
//{
//    mangled_ppc("?process_update@c_simulation_entity_database@@QAAXJV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@JPAUs_replication_allocation_block@@@Z");
//};

//public: bool c_simulation_entity_database::calculate_deletion_requirements(long, void const *, float *)
//{
//    mangled_ppc("?calculate_deletion_requirements@c_simulation_entity_database@@QAA_NJPBXPAM@Z");
//};

//public: void c_simulation_entity_database::notify_mark_entity_for_deletion(long, bool)
//{
//    mangled_ppc("?notify_mark_entity_for_deletion@c_simulation_entity_database@@QAAXJ_N@Z");
//};

//public: void c_simulation_entity_database::notify_delete_entity(long)
//{
//    mangled_ppc("?notify_delete_entity@c_simulation_entity_database@@QAAXJ@Z");
//};

//public: bool c_simulation_entity_database::notify_promote_to_authority(long)
//{
//    mangled_ppc("?notify_promote_to_authority@c_simulation_entity_database@@QAA_NJ@Z");
//};

//public: void c_simulation_entity_database::notify_creation_sent(long)
//{
//    mangled_ppc("?notify_creation_sent@c_simulation_entity_database@@QAAXJ@Z");
//};

//public: void c_simulation_entity_database::rotate_entity_seed(long)
//{
//    mangled_ppc("?rotate_entity_seed@c_simulation_entity_database@@QAAXJ@Z");
//};

//public: class c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_simulation_entity_database::generate_current_entity_update_mask(long)
//{
//    mangled_ppc("?generate_current_entity_update_mask@c_simulation_entity_database@@QAA?AV?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@J@Z");
//};

//public: class c_static_string<256> c_simulation_entity_database::describe_entity(long) const
//{
//    mangled_ppc("?describe_entity@c_simulation_entity_database@@QBA?AV?$c_static_string@$0BAA@@@J@Z");
//};

//private: void c_simulation_entity_database::entity_create_internal(long, enum e_simulation_entity_type, long, void *, long, void *)
//{
//    mangled_ppc("?entity_create_internal@c_simulation_entity_database@@AAAXJW4e_simulation_entity_type@@JPAXJ1@Z");
//};

//private: void c_simulation_entity_database::entity_delete_gameworld(long, bool)
//{
//    mangled_ppc("?entity_delete_gameworld@c_simulation_entity_database@@AAAXJ_N@Z");
//};

//private: void c_simulation_entity_database::entity_delete_internal(long)
//{
//    mangled_ppc("?entity_delete_internal@c_simulation_entity_database@@AAAXJ@Z");
//};

//private: void c_simulation_entity_database::entity_validate_creation_data(long) const
//{
//    mangled_ppc("?entity_validate_creation_data@c_simulation_entity_database@@ABAXJ@Z");
//};

//private: void c_simulation_entity_database::entity_validate_state_data(long) const
//{
//    mangled_ppc("?entity_validate_state_data@c_simulation_entity_database@@ABAXJ@Z");
//};

//private: bool c_simulation_entity_database::entity_allocate_creation_data(enum e_simulation_entity_type, long *, void **) const
//{
//    mangled_ppc("?entity_allocate_creation_data@c_simulation_entity_database@@ABA_NW4e_simulation_entity_type@@PAJPAPAX@Z");
//};

//private: bool c_simulation_entity_database::entity_allocate_state_data(enum e_simulation_entity_type, long *, void **) const
//{
//    mangled_ppc("?entity_allocate_state_data@c_simulation_entity_database@@ABA_NW4e_simulation_entity_type@@PAJPAPAX@Z");
//};

//public: static void c_simulation_entity_database::debug_render(void)
//{
//    mangled_ppc("?debug_render@c_simulation_entity_database@@SAXXZ");
//};

//public: c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>)
//{
//    mangled_ppc("??0?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@QAA@V?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@@Z");
//};

//public: bool c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::test(enum e_replication_entity_flags) const
//{
//    mangled_ppc("?test@?$c_flags_no_init@W4e_replication_entity_flags@@E$04Us_default_enum_string_resolver@@@@QBA_NW4e_replication_entity_flags@@@Z");
//};

//public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::clear(void)
//{
//    mangled_ppc("?clear@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QAAXXZ");
//};

//public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::is_clear(void) const
//{
//    mangled_ppc("?is_clear@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_NXZ");
//};

//public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::set_range(long, long, bool)
//{
//    mangled_ppc("?set_range@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QAAXJJ_N@Z");
//};

//public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::any_flagged_outside_range(long, long) const
//{
//    mangled_ppc("?any_flagged_outside_range@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_NJJ@Z");
//};

//public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator==(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const
//{
//    mangled_ppc("??8?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_NABV0@@Z");
//};

//public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator!=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const
//{
//    mangled_ppc("??9?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_NABV0@@Z");
//};

//public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator~(void) const
//{
//    mangled_ppc("??S?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA?AV0@XZ");
//};

//public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator&(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &) const
//{
//    mangled_ppc("??I?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA?AV0@ABV0@@Z");
//};

//public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> & c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator|=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &)
//{
//    mangled_ppc("??_5?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QAAAAV0@ABV0@@Z");
//};

//public: unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::get_unsafe(void) const
//{
//    mangled_ppc("?get_unsafe@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_KXZ");
//};

//public: void c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::set_unsafe(unsigned __int64)
//{
//    mangled_ppc("?set_unsafe@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QAAX_K@Z");
//};

//public: c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::c_flags<long, unsigned __int64, 64, struct s_default_enum_string_resolver>(void)
//{
//    mangled_ppc("??0?$c_flags@J_K$0EA@Us_default_enum_string_resolver@@@@QAA@XZ");
//};

//public: void c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::clear(void)
//{
//    mangled_ppc("?clear@?$c_flags_no_init@W4e_simulation_entity_flag@@E$01Us_default_enum_string_resolver@@@@QAAXXZ");
//};

//public: bool c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::test(enum e_simulation_entity_flag) const
//{
//    mangled_ppc("?test@?$c_flags_no_init@W4e_simulation_entity_flag@@E$01Us_default_enum_string_resolver@@@@QBA_NW4e_simulation_entity_flag@@@Z");
//};

//public: void c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::set(enum e_simulation_entity_flag, bool)
//{
//    mangled_ppc("?set@?$c_flags_no_init@W4e_simulation_entity_flag@@E$01Us_default_enum_string_resolver@@@@QAAXW4e_simulation_entity_flag@@_N@Z");
//};

//public: struct s_replication_entity_data const & s_static_array<struct s_replication_entity_data, 1024>::operator[]<long>(long) const
//{
//    mangled_ppc("??$?AJ@?$s_static_array@Us_replication_entity_data@@$0EAA@@@QBAABUs_replication_entity_data@@J@Z");
//};

//bool operator==<enum e_simulation_entity_type>(enum e_simulation_entity_type const &, enum e_none_sentinel const &)
//{
//    mangled_ppc("??$?8W4e_simulation_entity_type@@@@YA_NABW4e_simulation_entity_type@@ABW4e_none_sentinel@@@Z");
//};

//public: static bool c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::valid_bit(enum e_replication_entity_flags)
//{
//    mangled_ppc("?valid_bit@?$c_flags_no_init@W4e_replication_entity_flags@@E$04Us_default_enum_string_resolver@@@@SA_NW4e_replication_entity_flags@@@Z");
//};

//private: static unsigned char c_flags_no_init<enum e_replication_entity_flags, unsigned char, 5, struct s_default_enum_string_resolver>::flag_size_type(enum e_replication_entity_flags)
//{
//    mangled_ppc("?flag_size_type@?$c_flags_no_init@W4e_replication_entity_flags@@E$04Us_default_enum_string_resolver@@@@CAEW4e_replication_entity_flags@@@Z");
//};

//public: class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> & c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::operator&=(class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> const &)
//{
//    mangled_ppc("??_4?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QAAAAV0@ABV0@@Z");
//};

//public: static class c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver> c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_mask_from_range(long, long)
//{
//    mangled_ppc("?make_mask_from_range@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@SA?AV1@JJ@Z");
//};

//public: static bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::valid_bit(long)
//{
//    mangled_ppc("?valid_bit@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@SA_NJ@Z");
//};

//public: bool c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::valid(void) const
//{
//    mangled_ppc("?valid@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@QBA_NXZ");
//};

//private: static unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void)
//{
//    mangled_ppc("?make_mask_with_all_valid_bits_on_size_type@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@CA_KXZ");
//};

//public: static bool c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::valid_bit(enum e_simulation_entity_flag)
//{
//    mangled_ppc("?valid_bit@?$c_flags_no_init@W4e_simulation_entity_flag@@E$01Us_default_enum_string_resolver@@@@SA_NW4e_simulation_entity_flag@@@Z");
//};

//private: static unsigned char c_flags_no_init<enum e_simulation_entity_flag, unsigned char, 2, struct s_default_enum_string_resolver>::flag_size_type(enum e_simulation_entity_flag)
//{
//    mangled_ppc("?flag_size_type@?$c_flags_no_init@W4e_simulation_entity_flag@@E$01Us_default_enum_string_resolver@@@@CAEW4e_simulation_entity_flag@@@Z");
//};

//public: static bool s_static_array<struct s_replication_entity_data, 1024>::valid<long>(long)
//{
//    mangled_ppc("??$valid@J@?$s_static_array@Us_replication_entity_data@@$0EAA@@@SA_NJ@Z");
//};

//private: static unsigned __int64 c_flags_no_init<long, unsigned __int64, 64, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(long)
//{
//    mangled_ppc("?make_N_bit_mask_size_type@?$c_flags_no_init@J_K$0EA@Us_default_enum_string_resolver@@@@CA_KJ@Z");
//};
