#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_definitions.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

// Partial layouts for the recovered accessors only. The storage lengths cover
// the fields read here; they do not establish the complete definition sizes.
// Offsets are from the July 7 tag_play bodies; see docs/recovery/tag_definition_accessors.md.
struct s_tag_struct_definition
{
	long get_struct_size(void) const;
	long get_cache_file_struct_size(void) const;
	long get_alignment_bits(void) const;
	unsigned long get_runtime_flags(void) const;
	__int64 get_exploded_struct_size(void) const;
	c_tag_struct_vtable_interface const *get_struct_vtable(void) const;
	char const *get_name(void) const;
	unsigned char storage[136];
};

struct s_tag_block_definition
{
	char const *get_block_name(void) const;
	unsigned char storage[8];
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */


//bool tag_persistent_identifiers_equal(struct s_tag_persistent_identifier const &, struct s_tag_persistent_identifier const &)
//{
//    mangled_ppc("?tag_persistent_identifiers_equal@@YA_NABUs_tag_persistent_identifier@@0@Z");
//};

//bool resolve_block_reference_to_null(long, struct s_tag_field const *, void const *, void const *, __int64, struct s_tag_block_resolve_custom_result *)
//{
//    mangled_ppc("?resolve_block_reference_to_null@@YA_NJPBUs_tag_field@@PBX1_JPAUs_tag_block_resolve_custom_result@@@Z");
//};

//bool block_definition_can_match_nothing(struct s_tag_field const *, struct s_tag_block_definition const *)
//{
//    mangled_ppc("?block_definition_can_match_nothing@@YA_NPBUs_tag_field@@PBUs_tag_block_definition@@@Z");
//};

//struct s_tag_struct_definition declare_legacy_field_set(struct s_tag_field const *, char const *, long, long, long, bool (*)(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *))
//{
//    mangled_ppc("?declare_legacy_field_set@@YA?AUs_tag_struct_definition@@PBUs_tag_field@@PBDJJJP6A_NK0JJPAX0JJ2@Z@Z");
//};

//struct s_tag_struct_definition * get_mutable_legacy_ancestor_field_set(struct s_tag_struct_definition *)
//{
//    mangled_ppc("?get_mutable_legacy_ancestor_field_set@@YAPAUs_tag_struct_definition@@PAU1@@Z");
//};

//struct s_tag_struct_definition const * get_legacy_field_set(struct s_tag_struct_definition const *, long)
//{
//    mangled_ppc("?get_legacy_field_set@@YAPBUs_tag_struct_definition@@PBU1@J@Z");
//};

//void tag_persistent_identifier_create(struct s_tag_persistent_identifier *)
//{
//    mangled_ppc("?tag_persistent_identifier_create@@YAXPAUs_tag_persistent_identifier@@@Z");
//};

//public: struct s_tag_field const * s_tag_struct_definition::get_fields(void) const
//{
//    mangled_ppc("?get_fields@s_tag_struct_definition@@QBAPBUs_tag_field@@XZ");
//};

//public: void s_tag_struct_definition::set_fields(struct s_tag_field const *)
//{
//    mangled_ppc("?set_fields@s_tag_struct_definition@@QAAXPBUs_tag_field@@@Z");
//};

//public: bool s_tag_struct_definition::owns_field(struct s_tag_field const *) const
//{
//    mangled_ppc("?owns_field@s_tag_struct_definition@@QBA_NPBUs_tag_field@@@Z");
//};

long s_tag_struct_definition::get_struct_size(void) const
{
	return *reinterpret_cast<long const *>(storage + 28);
}

long s_tag_struct_definition::get_cache_file_struct_size(void) const
{
	return *reinterpret_cast<long const *>(storage + 132);
}

long s_tag_struct_definition::get_alignment_bits(void) const
{
	return *reinterpret_cast<long const *>(storage + 36);
}

//public: char const * s_tag_struct_definition::get_size_string(void) const
//{
//    mangled_ppc("?get_size_string@s_tag_struct_definition@@QBAPBDXZ");
//};

unsigned long s_tag_struct_definition::get_runtime_flags(void) const
{
	return *reinterpret_cast<unsigned long const *>(storage + 124);
}

//public: bool s_tag_struct_definition::is_built_from_disk(void) const
//{
//    mangled_ppc("?is_built_from_disk@s_tag_struct_definition@@QBA_NXZ");
//};

//public: struct byte_swap_definition * s_tag_struct_definition::get_byte_swap_definition(void) const
//{
//    mangled_ppc("?get_byte_swap_definition@s_tag_struct_definition@@QBAPAUbyte_swap_definition@@XZ");
//};

__int64 s_tag_struct_definition::get_exploded_struct_size(void) const
{
	return *reinterpret_cast<__int64 const *>(storage + 80);
}

c_tag_struct_vtable_interface const *s_tag_struct_definition::get_struct_vtable(void) const
{
	return *reinterpret_cast<c_tag_struct_vtable_interface const *const *>(storage + 72);
}

//public: void const * s_tag_struct_definition::get_type_key(void) const
//{
//    mangled_ppc("?get_type_key@s_tag_struct_definition@@QBAPBXXZ");
//};

//public: struct s_tag_persistent_identifier const & s_tag_struct_definition::get_persistent_identifier(void) const
//{
//    mangled_ppc("?get_persistent_identifier@s_tag_struct_definition@@QBAABUs_tag_persistent_identifier@@XZ");
//};

//public: struct s_tag_struct_definition const * s_tag_struct_definition::get_ancestor_definition(void) const
//{
//    mangled_ppc("?get_ancestor_definition@s_tag_struct_definition@@QBAPBU1@XZ");
//};

//public: struct s_tag_struct_definition * s_tag_struct_definition::get_ancestor_definition_mutable(void)
//{
//    mangled_ppc("?get_ancestor_definition_mutable@s_tag_struct_definition@@QAAPAU1@XZ");
//};

//public: struct s_tag_struct_definition * s_tag_struct_definition::get_mutable_ancestor_definition(void)
//{
//    mangled_ppc("?get_mutable_ancestor_definition@s_tag_struct_definition@@QAAPAU1@XZ");
//};

//public: struct s_tag_struct_definition const * s_tag_struct_definition::get_descendent_definition(void) const
//{
//    mangled_ppc("?get_descendent_definition@s_tag_struct_definition@@QBAPBU1@XZ");
//};

//public: char const * s_tag_struct_definition::get_pretty_name(void) const
//{
//    mangled_ppc("?get_pretty_name@s_tag_struct_definition@@QBAPBDXZ");
//};

char const *s_tag_struct_definition::get_name(void) const
{
	return *reinterpret_cast<char const *const *>(storage + 4);
}

//public: void s_tag_struct_definition::set_descendent_definition(struct s_tag_struct_definition *)
//{
//    mangled_ppc("?set_descendent_definition@s_tag_struct_definition@@QAAXPAU1@@Z");
//};

//public: enum e_tag_memory_allocation_type s_tag_struct_definition::get_preferred_memory_type(void)
//{
//    mangled_ppc("?get_preferred_memory_type@s_tag_struct_definition@@QAA?AW4e_tag_memory_allocation_type@@XZ");
//};

//public: class c_tag_memory_attributes const & s_tag_struct_definition::get_memory_attributes(void) const
//{
//    mangled_ppc("?get_memory_attributes@s_tag_struct_definition@@QBAABVc_tag_memory_attributes@@XZ");
//};

//public: void s_tag_struct_definition::validate_vtable(void)
//{
//    mangled_ppc("?validate_vtable@s_tag_struct_definition@@QAAXXZ");
//};

//public: long s_tag_block_definition::get_element_size(void) const
//{
//    mangled_ppc("?get_element_size@s_tag_block_definition@@QBAJXZ");
//};

//public: char const * s_tag_block_definition::get_size_string(void) const
//{
//    mangled_ppc("?get_size_string@s_tag_block_definition@@QBAPBDXZ");
//};

//public: struct s_tag_field const * s_tag_block_definition::get_fields(void) const
//{
//    mangled_ppc("?get_fields@s_tag_block_definition@@QBAPBUs_tag_field@@XZ");
//};

//public: long s_tag_block_definition::get_cache_file_element_size(void) const
//{
//    mangled_ppc("?get_cache_file_element_size@s_tag_block_definition@@QBAJXZ");
//};

//public: unsigned long s_tag_block_definition::get_runtime_flags(void) const
//{
//    mangled_ppc("?get_runtime_flags@s_tag_block_definition@@QBAKXZ");
//};

//public: bool s_tag_block_definition::does_not_exist_in_cache_build(void) const
//{
//    mangled_ppc("?does_not_exist_in_cache_build@s_tag_block_definition@@QBA_NXZ");
//};

//public: long s_tag_block_definition::get_alignment_bits(void) const
//{
//    mangled_ppc("?get_alignment_bits@s_tag_block_definition@@QBAJXZ");
//};

//public: struct byte_swap_definition * s_tag_block_definition::get_byte_swap_definition(void) const
//{
//    mangled_ppc("?get_byte_swap_definition@s_tag_block_definition@@QBAPAUbyte_swap_definition@@XZ");
//};

//public: __int64 s_tag_block_definition::get_exploded_maximum_block_size(void) const
//{
//    mangled_ppc("?get_exploded_maximum_block_size@s_tag_block_definition@@QBA_JXZ");
//};

//public: class c_tag_struct_vtable_interface const * s_tag_block_definition::get_struct_vtable(void) const
//{
//    mangled_ppc("?get_struct_vtable@s_tag_block_definition@@QBAPBVc_tag_struct_vtable_interface@@XZ");
//};

//public: void const * s_tag_block_definition::get_type_key(void) const
//{
//    mangled_ppc("?get_type_key@s_tag_block_definition@@QBAPBXXZ");
//};

//public: struct s_tag_persistent_identifier const & s_tag_block_definition::get_persistent_identifier(void) const
//{
//    mangled_ppc("?get_persistent_identifier@s_tag_block_definition@@QBAABUs_tag_persistent_identifier@@XZ");
//};

//public: char const * s_tag_block_definition::get_pretty_name(void) const
//{
//    mangled_ppc("?get_pretty_name@s_tag_block_definition@@QBAPBDXZ");
//};

//public: char const * s_tag_block_definition::get_elements_name(void) const
//{
//    mangled_ppc("?get_elements_name@s_tag_block_definition@@QBAPBDXZ");
//};

char const *s_tag_block_definition::get_block_name(void) const
{
	return *reinterpret_cast<char const *const *>(storage + 4);
}

//public: unsigned long s_tag_block_definition::get_allocation_flags(void) const
//{
//    mangled_ppc("?get_allocation_flags@s_tag_block_definition@@QBAKXZ");
//};

//public: enum e_tag_memory_allocation_type s_tag_block_definition::get_preferred_memory_type(void)
//{
//    mangled_ppc("?get_preferred_memory_type@s_tag_block_definition@@QAA?AW4e_tag_memory_allocation_type@@XZ");
//};

//public: class c_tag_memory_attributes const & s_tag_block_definition::get_memory_attributes(void) const
//{
//    mangled_ppc("?get_memory_attributes@s_tag_block_definition@@QBAABVc_tag_memory_attributes@@XZ");
//};

//public: struct s_tag_field const * s_tag_array_definition::get_fields(void) const
//{
//    mangled_ppc("?get_fields@s_tag_array_definition@@QBAPBUs_tag_field@@XZ");
//};

//public: long s_tag_array_definition::get_element_size(void) const
//{
//    mangled_ppc("?get_element_size@s_tag_array_definition@@QBAJXZ");
//};

//public: long s_tag_array_definition::get_cache_file_element_size(void) const
//{
//    mangled_ppc("?get_cache_file_element_size@s_tag_array_definition@@QBAJXZ");
//};

//public: unsigned long s_tag_array_definition::get_runtime_flags(void) const
//{
//    mangled_ppc("?get_runtime_flags@s_tag_array_definition@@QBAKXZ");
//};

//public: class c_tag_struct_vtable_interface const * s_tag_array_definition::get_struct_vtable(void) const
//{
//    mangled_ppc("?get_struct_vtable@s_tag_array_definition@@QBAPBVc_tag_struct_vtable_interface@@XZ");
//};

//public: void const * s_tag_array_definition::get_type_key(void) const
//{
//    mangled_ppc("?get_type_key@s_tag_array_definition@@QBAPBXXZ");
//};

//public: struct s_tag_persistent_identifier const & s_tag_array_definition::get_persistent_identifier(void) const
//{
//    mangled_ppc("?get_persistent_identifier@s_tag_array_definition@@QBAABUs_tag_persistent_identifier@@XZ");
//};

//public: char const * s_tag_array_definition::get_pretty_name(void) const
//{
//    mangled_ppc("?get_pretty_name@s_tag_array_definition@@QBAPBDXZ");
//};

//public: char const * s_tag_array_definition::get_elements_name(void) const
//{
//    mangled_ppc("?get_elements_name@s_tag_array_definition@@QBAPBDXZ");
//};

//public: char const * s_tag_array_definition::get_array_name(void) const
//{
//    mangled_ppc("?get_array_name@s_tag_array_definition@@QBAPBDXZ");
//};

//public: enum e_tag_memory_allocation_type s_tag_array_definition::get_preferred_memory_type(void)
//{
//    mangled_ppc("?get_preferred_memory_type@s_tag_array_definition@@QAA?AW4e_tag_memory_allocation_type@@XZ");
//};

//public: class c_tag_memory_attributes const & s_tag_array_definition::get_memory_attributes(void) const
//{
//    mangled_ppc("?get_memory_attributes@s_tag_array_definition@@QBAABVc_tag_memory_attributes@@XZ");
//};

//public: struct s_tag_field const * s_tag_resource_definition::get_fields(void) const
//{
//    mangled_ppc("?get_fields@s_tag_resource_definition@@QBAPBUs_tag_field@@XZ");
//};

//public: long s_tag_resource_definition::get_alignment_bits(void) const
//{
//    mangled_ppc("?get_alignment_bits@s_tag_resource_definition@@QBAJXZ");
//};

//public: long s_tag_resource_definition::get_resource_size(void) const
//{
//    mangled_ppc("?get_resource_size@s_tag_resource_definition@@QBAJXZ");
//};

//public: long s_tag_resource_definition::get_cache_file_resource_size(void) const
//{
//    mangled_ppc("?get_cache_file_resource_size@s_tag_resource_definition@@QBAJXZ");
//};

//public: unsigned long s_tag_resource_definition::get_runtime_flags(void) const
//{
//    mangled_ppc("?get_runtime_flags@s_tag_resource_definition@@QBAKXZ");
//};

//public: class c_tag_struct_vtable_interface const * s_tag_resource_definition::get_struct_vtable(void) const
//{
//    mangled_ppc("?get_struct_vtable@s_tag_resource_definition@@QBAPBVc_tag_struct_vtable_interface@@XZ");
//};

//public: void const * s_tag_resource_definition::get_type_key(void) const
//{
//    mangled_ppc("?get_type_key@s_tag_resource_definition@@QBAPBXXZ");
//};

//public: long s_tag_resource_definition::get_pageable_alignment_bits(void) const
//{
//    mangled_ppc("?get_pageable_alignment_bits@s_tag_resource_definition@@QBAJXZ");
//};

//public: long s_tag_resource_definition::get_optional_alignment_bits(void) const
//{
//    mangled_ppc("?get_optional_alignment_bits@s_tag_resource_definition@@QBAJXZ");
//};

//public: struct s_tag_persistent_identifier const & s_tag_resource_definition::get_persistent_identifier(void) const
//{
//    mangled_ppc("?get_persistent_identifier@s_tag_resource_definition@@QBAABUs_tag_persistent_identifier@@XZ");
//};

//public: char const * s_tag_resource_definition::get_pretty_name(void) const
//{
//    mangled_ppc("?get_pretty_name@s_tag_resource_definition@@QBAPBDXZ");
//};

//public: char const * s_tag_resource_definition::get_resource_name(void) const
//{
//    mangled_ppc("?get_resource_name@s_tag_resource_definition@@QBAPBDXZ");
//};

//public: char const * s_tag_resource_definition::get_elements_name(void) const
//{
//    mangled_ppc("?get_elements_name@s_tag_resource_definition@@QBAPBDXZ");
//};

//public: bool s_tag_resource_definition::required(void) const
//{
//    mangled_ppc("?required@s_tag_resource_definition@@QBA_NXZ");
//};

//public: bool s_tag_resource_definition::not_required_immediately(void) const
//{
//    mangled_ppc("?not_required_immediately@s_tag_resource_definition@@QBA_NXZ");
//};

//public: bool s_tag_resource_definition::optional(void) const
//{
//    mangled_ppc("?optional@s_tag_resource_definition@@QBA_NXZ");
//};

//public: bool s_tag_resource_definition::streamed(void) const
//{
//    mangled_ppc("?streamed@s_tag_resource_definition@@QBA_NXZ");
//};

//public: void s_tag_resource_definition::validate_vtable(void)
//{
//    mangled_ppc("?validate_vtable@s_tag_resource_definition@@QAAXXZ");
//};

//public: unsigned long s_tag_struct_definition::get_legacy_struct_tag(void) const
//{
//    mangled_ppc("?get_legacy_struct_tag@s_tag_struct_definition@@QBAKXZ");
//};

//public: long s_tag_struct_definition::get_legacy_version(void) const
//{
//    mangled_ppc("?get_legacy_version@s_tag_struct_definition@@QBAJXZ");
//};

//public: long s_tag_block_definition::get_legacy_version(void) const
//{
//    mangled_ppc("?get_legacy_version@s_tag_block_definition@@QBAJXZ");
//};

//public: long s_tag_array_definition::get_legacy_version(void) const
//{
//    mangled_ppc("?get_legacy_version@s_tag_array_definition@@QBAJXZ");
//};

//public: unsigned long s_tag_data_definition::get_allocation_flags(void) const
//{
//    mangled_ppc("?get_allocation_flags@s_tag_data_definition@@QBAKXZ");
//};
//
//public: class c_tag_memory_attributes s_tag_data_definition::get_memory_attributes(void) const
//{
//    mangled_ppc("?get_memory_attributes@s_tag_data_definition@@QBA?AVc_tag_memory_attributes@@XZ");
//};

bool c_legacy_tag_struct_vtable_shim::has_byte_swap_proc(void) const
{
    mangled_ppc("?has_byte_swap_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(705, m_struct_vtable);

    return m_struct_vtable->byte_swap_proc != NULL;
};

void c_legacy_tag_struct_vtable_shim::byte_swap_block_proc(void * arg1) const
{
    mangled_ppc("?byte_swap_block_proc@c_legacy_tag_struct_vtable_shim@@UBAXPAX@Z");
    
    assert_tag_debug_untracked_jul_11_2011(712, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(713, m_struct_vtable->byte_swap_proc);
    
    m_struct_vtable->byte_swap_proc(arg1);
};

bool c_legacy_tag_struct_vtable_shim::has_postprocess_proc(void) const
{
    mangled_ppc("?has_postprocess_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(720, m_struct_vtable);

    return m_struct_vtable->postprocess_proc != NULL;
};

bool c_legacy_tag_struct_vtable_shim::postprocess_thunk(long arg1, void * arg2, bool arg3) const
{
    mangled_ppc("?postprocess_thunk@c_legacy_tag_struct_vtable_shim@@UBA_NJPAX_N@Z");
    
    assert_tag_debug_untracked_jul_11_2011(729, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(730, m_struct_vtable->postprocess_proc!=NULL);
    
    return m_struct_vtable->postprocess_proc(arg1, arg2, arg3);
};

bool c_legacy_tag_struct_vtable_shim::has_format_proc(void) const
{
    mangled_ppc("?has_format_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(737, m_struct_vtable);

    return m_struct_vtable->format_proc != NULL;
};

char * c_legacy_tag_struct_vtable_shim::format_thunk(long arg1, __int64 arg2, s_tag_block * arg3, long arg4, char * arg5, long arg6) const
{
    mangled_ppc("?format_thunk@c_legacy_tag_struct_vtable_shim@@UBAPADJ_JPAUs_tag_block@@JPADJ@Z");
    
    assert_tag_debug_untracked_jul_11_2011(749, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(750, m_struct_vtable->format_proc!=NULL);
    
    return m_struct_vtable->format_proc(arg1, arg2, arg3, arg4, arg5, arg6);
};

bool c_legacy_tag_struct_vtable_shim::has_on_delete_proc(void) const
{
    mangled_ppc("?has_on_delete_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(757, m_struct_vtable);

    return m_struct_vtable->delete_proc != NULL;
};

void c_legacy_tag_struct_vtable_shim::on_delete_thunk(void * arg1) const
{
    mangled_ppc("?on_delete_thunk@c_legacy_tag_struct_vtable_shim@@UBAXPAX@Z");
    
    assert_tag_debug_untracked_jul_11_2011(764, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(765, m_struct_vtable->delete_proc!=NULL);
    
    return m_struct_vtable->delete_proc(arg1);
};

bool c_legacy_tag_struct_vtable_shim::has_on_new_proc(void) const
{
    mangled_ppc("?has_on_new_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(772, m_struct_vtable);

    return m_struct_vtable->new_proc != NULL;
};

bool c_legacy_tag_struct_vtable_shim::on_new_thunk(void * arg1) const
{
    mangled_ppc("?on_new_thunk@c_legacy_tag_struct_vtable_shim@@UBA_NPAX@Z");
    
    assert_tag_debug_untracked_jul_11_2011(779, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(780, m_struct_vtable->new_proc);
    
    return m_struct_vtable->new_proc(arg1);
};

bool c_legacy_tag_struct_vtable_shim::has_on_copy_proc(void) const
{
    mangled_ppc("?has_on_copy_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(787, m_struct_vtable);

    return m_struct_vtable->copy_proc != NULL;
};

bool c_legacy_tag_struct_vtable_shim::on_copy_thunk(void const * arg1, void * arg2) const
{
    mangled_ppc("?on_copy_thunk@c_legacy_tag_struct_vtable_shim@@UBA_NPBXPAX@Z");
    
    assert_tag_debug_untracked_jul_11_2011(795, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(796, m_struct_vtable->copy_proc!=NULL);
    
    return m_struct_vtable->copy_proc(arg1, arg2);
};

bool c_legacy_tag_struct_vtable_shim::has_write_to_cache_file_proc(void) const
{
    mangled_ppc("?has_write_to_cache_file_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(803, m_struct_vtable);

    return m_struct_vtable->write_to_cache_file_block != NULL;
};

void c_legacy_tag_struct_vtable_shim::write_to_cache_file_thunk(long arg1, s_tag_block * arg2, s_cache_file_builder_stream_context const * arg3, void ** arg4, void ** arg5) const
{
    mangled_ppc("?write_to_cache_file_thunk@c_legacy_tag_struct_vtable_shim@@UBAXJPAUs_tag_block@@PBUs_cache_file_builder_stream_context@@PAPAX2@Z");
    
    assert_tag_debug_untracked_jul_11_2011(814, m_struct_vtable);
    assert_tag_debug_untracked_jul_11_2011(815, m_struct_vtable->write_to_cache_file_block);

    return m_struct_vtable->write_to_cache_file_block(arg1, arg2, arg3, arg4, arg5);
};

bool c_legacy_tag_struct_vtable_shim::has_fixup_old_struct_definition(void) const
{
    mangled_ppc("?has_fixup_old_struct_definition@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(822, m_manual_fixup);

    return m_manual_fixup->from_struct_definition != NULL;
};

s_tag_struct_definition * c_legacy_tag_struct_vtable_shim::get_fixup_source_definition_thunk(void) const
{
    mangled_ppc("?get_fixup_source_definition_thunk@c_legacy_tag_struct_vtable_shim@@UBAPAUs_tag_struct_definition@@XZ");
    
    assert_tag_debug_untracked_jul_11_2011(829, m_manual_fixup);
    assert_tag_debug_untracked_jul_11_2011(830, m_manual_fixup->from_struct_definition);

    return m_manual_fixup->from_struct_definition;
};

bool c_legacy_tag_struct_vtable_shim::has_fixup_old_struct_proc(void) const
{
    mangled_ppc("?has_fixup_old_struct_proc@c_legacy_tag_struct_vtable_shim@@UBA_NXZ");
    
    assert_tag_debug_untracked_jul_11_2011(837, m_manual_fixup);

    return m_manual_fixup->fixup_proc != NULL;
}

bool c_legacy_tag_struct_vtable_shim::fixup_old_struct_thunk(c_basic_buffer<void> & arg1, s_tag_struct_definition const * arg2, c_basic_buffer<void> & arg3, s_tag_struct_definition const * arg4, c_tag_allocator * arg5, bool arg6) const
{
    mangled_ppc("?fixup_old_struct_thunk@c_legacy_tag_struct_vtable_shim@@UBA_NAAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@01PAVc_tag_allocator@@_N@Z");
    
    assert_tag_debug_untracked_jul_11_2011(849, m_manual_fixup);
    assert_tag_debug_untracked_jul_11_2011(850, m_manual_fixup->fixup_proc);

    return m_manual_fixup->fixup_proc(arg1, arg2, arg3, arg4, arg5, arg6);
};

bool c_legacy_tag_group_vtable_shim::has_custom_postprocess_proc(void) const
{
    mangled_ppc("?has_custom_postprocess_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(858, m_legacy_vtable);

    return m_legacy_vtable->postprocess_tag != NULL;
};

bool c_legacy_tag_group_vtable_shim::postprocess_tag_thunk(long arg1, bool arg2) const
{
    mangled_ppc("?postprocess_tag_thunk@c_legacy_tag_group_vtable_shim@@UBA_NJ_N@Z");

    assert_tag_debug_untracked_jul_11_2011(864, m_legacy_vtable);
    assert_tag_debug_untracked_jul_11_2011(865, m_legacy_vtable->postprocess_tag!=NULL);

    return m_legacy_vtable->postprocess_tag(arg1, arg2);
};

bool c_legacy_tag_group_vtable_shim::has_custom_missing_tag_proc(void) const
{
    mangled_ppc("?has_custom_missing_tag_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(871, m_legacy_vtable);

    return m_legacy_vtable->missing_proc != NULL;
};

void c_legacy_tag_group_vtable_shim::handle_missing_tag_thunk(unsigned long arg1, char const * arg2, unsigned long arg3, unsigned long arg4, char const * arg5, long * arg6) const
{
    mangled_ppc("?handle_missing_tag_thunk@c_legacy_tag_group_vtable_shim@@UBAXKPBDKK0PAJ@Z");

    assert_tag_debug_untracked_jul_11_2011(877, m_legacy_vtable);
    assert_tag_debug_untracked_jul_11_2011(878, m_legacy_vtable->missing_proc);

    return m_legacy_vtable->missing_proc(arg1, arg2, arg3, arg4, arg5, arg6);
};

bool c_legacy_tag_group_vtable_shim::has_on_save_tag_proc(void) const
{
    mangled_ppc("?has_on_save_tag_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(885, m_legacy_vtable);

    return m_legacy_vtable->on_save_tag != NULL;
};

void c_legacy_tag_group_vtable_shim::on_save_tag_thunk(long arg1) const
{
    mangled_ppc("?on_save_tag_thunk@c_legacy_tag_group_vtable_shim@@UBAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(891, m_legacy_vtable);
    assert_tag_debug_untracked_jul_11_2011(892, m_legacy_vtable->on_save_tag!=NULL);

    return m_legacy_vtable->on_save_tag(arg1);
};

bool c_legacy_tag_group_vtable_shim::has_write_to_cache_file_proc(void) const
{
    mangled_ppc("?has_write_to_cache_file_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(898, m_legacy_vtable);

    return m_legacy_vtable->write_tag_to_cache_file != NULL;
};

void c_legacy_tag_group_vtable_shim::write_tag_to_cache_file_thunk(long arg1, unsigned long arg2, c_cache_file_scratch_allocator * arg3, c_cache_file_resource_library * arg4, c_cache_file_tracer * arg5, void ** arg6, void ** arg7) const
{
    mangled_ppc("?write_tag_to_cache_file_thunk@c_legacy_tag_group_vtable_shim@@UBAXJKPAVc_cache_file_scratch_allocator@@PAVc_cache_file_resource_library@@PAVc_cache_file_tracer@@PAPAX3@Z");

    assert_tag_debug_untracked_jul_11_2011(904, m_legacy_vtable);
    assert_tag_debug_untracked_jul_11_2011(905, m_legacy_vtable->write_tag_to_cache_file!=NULL);

    return m_legacy_vtable->write_tag_to_cache_file(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
};

bool c_legacy_tag_group_vtable_shim::has_valid_alternate_streams(void) const
{
    mangled_ppc("?has_valid_alternate_streams@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(912, m_legacy_stream);

    return m_legacy_stream->stream_list != NULL;
};

s_tag_group_stream_list * c_legacy_tag_group_vtable_shim::get_alterante_streams_thunk(void) const
{
    mangled_ppc("?get_alterante_streams_thunk@c_legacy_tag_group_vtable_shim@@UBAPAUs_tag_group_stream_list@@XZ");

    assert_tag_debug_untracked_jul_11_2011(918, m_legacy_stream);
    assert_tag_debug_untracked_jul_11_2011(919, m_legacy_stream->stream_list);

    return m_legacy_stream->stream_list;
};

bool c_legacy_tag_group_vtable_shim::has_should_load_tag_stream_proc(void) const
{
    mangled_ppc("?has_should_load_tag_stream_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(925, m_legacy_stream);

    return m_legacy_stream->should_load_tag_stream != NULL;
};

bool c_legacy_tag_group_vtable_shim::should_load_tag_stream_thunk(unsigned long arg1, bool arg2) const
{
    mangled_ppc("?should_load_tag_stream_thunk@c_legacy_tag_group_vtable_shim@@UBA_NK_N@Z");

    assert_tag_debug_untracked_jul_11_2011(931, m_legacy_stream);

    return m_legacy_stream->should_load_tag_stream(arg1, arg2);
};

bool c_legacy_tag_group_vtable_shim::has_custom_xsync_runtime_platforms(void) const
{
    mangled_ppc("?has_custom_xsync_runtime_platforms@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(938, m_legacy_xsync_declaration);

    return m_legacy_xsync_declaration->xsync_runtime_platforms != 0;
};

unsigned long c_legacy_tag_group_vtable_shim::get_xsync_runtime_platforms_thunk(void) const
{
    mangled_ppc("?get_xsync_runtime_platforms_thunk@c_legacy_tag_group_vtable_shim@@UBAKXZ");

    assert_tag_debug_untracked_jul_11_2011(944, m_legacy_xsync_declaration);

    return m_legacy_xsync_declaration->xsync_runtime_platforms;
};

bool c_legacy_tag_group_vtable_shim::has_postprocess_on_sync_proc(void) const
{
    mangled_ppc("?has_postprocess_on_sync_proc@c_legacy_tag_group_vtable_shim@@UBA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(950, m_legacy_xsync_declaration);

    return m_legacy_xsync_declaration->postprocess_on_sync != NULL;
};

bool c_legacy_tag_group_vtable_shim::postprocess_on_sync_thunk(long arg1, e_runtime_platform_type arg2, c_cache_file_global_tag_registry * arg3, bool arg4) const
{
    mangled_ppc("?postprocess_on_sync_thunk@c_legacy_tag_group_vtable_shim@@UBA_NJW4e_runtime_platform_type@@PAVc_cache_file_global_tag_registry@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(956, m_legacy_xsync_declaration);
    assert_tag_debug_untracked_jul_11_2011(957, m_legacy_xsync_declaration->postprocess_on_sync);

    return m_legacy_xsync_declaration->postprocess_on_sync(arg1, arg2, arg3, arg4);
};

//public: unsigned long s_tag_group::get_xsync_version(void) const
//{
//    mangled_ppc("?get_xsync_version@s_tag_group@@QBAKXZ");
//};

//public: long s_tag_group::get_non_temporary_group_index(void) const
//{
//    mangled_ppc("?get_non_temporary_group_index@s_tag_group@@QBAJXZ");
//};

//public: void s_tag_group::set_non_temporary_group_index(long)
//{
//    mangled_ppc("?set_non_temporary_group_index@s_tag_group@@QAAXJ@Z");
//};

//public: bool s_tag_group::valid_for_reload_stage(enum e_tag_reload_stage) const
//{
//    mangled_ppc("?valid_for_reload_stage@s_tag_group@@QBA_NW4e_tag_reload_stage@@@Z");
//};

//public: void s_tag_group::validate_vtable(void)
//{
//    mangled_ppc("?validate_vtable@s_tag_group@@QAAXXZ");
//};

e_tag_memory_allocation_type c_tag_memory_attributes::get_memory_type(void) const
{
    mangled_ppc("?get_memory_type@c_tag_memory_attributes@@QBA?AW4e_tag_memory_allocation_type@@XZ");

    return m_allocation_type;
};

unsigned long c_tag_memory_attributes::get_usage_flags(void) const
{
    mangled_ppc("?get_usage_flags@c_tag_memory_attributes@@QBAKXZ");

    return m_usage.get_unsafe();
};

void c_tag_memory_attributes::set_attributes(e_tag_memory_allocation_type allocation_type, unsigned long usage_flags)
{
    mangled_ppc("?set_attributes@c_tag_memory_attributes@@QAAXW4e_tag_memory_allocation_type@@K@Z");

    m_allocation_type = allocation_type;
    m_usage.set_unsafe(usage_flags);
};

bool c_tag_memory_attributes::operator==(class c_tag_memory_attributes const & rhs) const
{
    mangled_ppc("??8c_tag_memory_attributes@@QBA_NABV0@@Z");

    return m_allocation_type == rhs.m_allocation_type && m_usage == rhs.m_usage;
};

bool c_tag_memory_attributes::operator!=(class c_tag_memory_attributes const & rhs) const
{
    mangled_ppc("??9c_tag_memory_attributes@@QBA_NABV0@@Z");

    return !operator==(rhs);
};

c_tag_memory_attributes make_tag_memory_attributes(e_tag_memory_allocation_type allocation_type, unsigned long usage_flags)
{
    mangled_ppc("?make_tag_memory_attributes@@YA?AVc_tag_memory_attributes@@W4e_tag_memory_allocation_type@@K@Z");

    c_tag_memory_attributes memory_attributes;
    memory_attributes.set_attributes(allocation_type, usage_flags);
    return memory_attributes;
};

//unsigned long const * array_begin<unsigned long const, 4>(unsigned long const (&)[4])
//{
//    mangled_ppc("??$array_begin@$$CBK$03@@YAPBKAAY03$$CBK@Z");
//};

//unsigned long const * array_end<unsigned long const, 4>(unsigned long const (&)[4])
//{
//    mangled_ppc("??$array_end@$$CBK$03@@YAPBKAAY03$$CBK@Z");
//};

//bool std::equal<unsigned long const *, unsigned long const *>(unsigned long const *, unsigned long const *, unsigned long const *)
//{
//    mangled_ppc("??$equal@PBKPBK@std@@YA_NPBK00@Z");
//};

//unsigned long const * std::_Checked_base<unsigned long const *>(unsigned long const *&)
//{
//    mangled_ppc("??$_Checked_base@PBK@std@@YAPBKAAPBK@Z");
//};

//struct std::random_access_iterator_tag std::_Iter_random<unsigned long const *, unsigned long const *>(unsigned long const *const &, unsigned long const *const &)
//{
//    mangled_ppc("??$_Iter_random@PBKPBK@std@@YA?AUrandom_access_iterator_tag@0@ABQBK0@Z");
//};

//bool std::_Equal<unsigned long const *, unsigned long const *>(unsigned long const *, unsigned long const *, unsigned long const *, struct std::random_access_iterator_tag, struct std::_Range_checked_iterator_tag)
//{
//    mangled_ppc("??$_Equal@PBKPBK@std@@YA_NPBK00Urandom_access_iterator_tag@0@U_Range_checked_iterator_tag@0@@Z");
//};

//unsigned long const * std::_Checked_base<unsigned long const *>(unsigned long const *&, struct std::_Unchanged_checked_iterator_base_type_tag)
//{
//    mangled_ppc("??$_Checked_base@PBK@std@@YAPBKAAPBKU_Unchanged_checked_iterator_base_type_tag@0@@Z");
//};

//bool std::_Equal<unsigned long const *, unsigned long const *, struct std::forward_iterator_tag>(unsigned long const *, unsigned long const *, unsigned long const *, struct std::forward_iterator_tag, struct std::_Range_checked_iterator_tag)
//{
//    mangled_ppc("??$_Equal@PBKPBKUforward_iterator_tag@std@@@std@@YA_NPBK00Uforward_iterator_tag@0@U_Range_checked_iterator_tag@0@@Z");
//};

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition g_null_block_struct_definition; // "?g_null_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition g_null_block; // "?g_null_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition g_non_traversed_reference_definition; // "?g_non_traversed_reference_definition@@3Us_tag_reference_definition@@A"
// struct s_block_index_custom_search_definition g_null_custom_search_block_reference; // "?g_null_custom_search_block_reference@@3Us_block_index_custom_search_definition@@A"
// char const **g_tag_reference_definition_flags_strings; // "?g_tag_reference_definition_flags_strings@@3PAPBDA"
// struct s_string_list_definition g_tag_reference_definition_flags; // "?g_tag_reference_definition_flags@@3Us_string_list_definition@@A"
// class c_legacy_tag_struct_vtable_shim g_empty_tag_struct_legacy_vtable_shim; // "?g_empty_tag_struct_legacy_vtable_shim@@3Vc_legacy_tag_struct_vtable_shim@@A"
// class c_tag_memory_attributes const k_read_only_tag_memory_attributes; // "?k_read_only_tag_memory_attributes@@3Vc_tag_memory_attributes@@B"
// class c_tag_memory_attributes const k_read_write_tag_memory_attributes; // "?k_read_write_tag_memory_attributes@@3Vc_tag_memory_attributes@@B"
// class c_tag_memory_attributes const k_physical_read_only_tag_memory_attributes; // "?k_physical_read_only_tag_memory_attributes@@3Vc_tag_memory_attributes@@B"
// class c_tag_memory_attributes const k_physical_read_write_tag_memory_attributes; // "?k_physical_read_write_tag_memory_attributes@@3Vc_tag_memory_attributes@@B"
// class c_tag_memory_attributes const k_physical_write_combined_tag_memory_attributes; // "?k_physical_write_combined_tag_memory_attributes@@3Vc_tag_memory_attributes@@B"

// bool tag_persistent_identifiers_equal(struct s_tag_persistent_identifier const &, struct s_tag_persistent_identifier const &);
// bool resolve_block_reference_to_null(long, struct s_tag_field const *, void const *, void const *, __int64, struct s_tag_block_resolve_custom_result *);
// bool block_definition_can_match_nothing(struct s_tag_field const *, struct s_tag_block_definition const *);
// struct s_tag_struct_definition declare_legacy_field_set(struct s_tag_field const *, char const *, long, long, long, bool (*)(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *));
// struct s_tag_struct_definition * get_mutable_legacy_ancestor_field_set(struct s_tag_struct_definition *);
// struct s_tag_struct_definition const * get_legacy_field_set(struct s_tag_struct_definition const *, long);
// void tag_persistent_identifier_create(struct s_tag_persistent_identifier *);
// public: struct s_tag_field const * s_tag_struct_definition::get_fields(void) const;
// public: void s_tag_struct_definition::set_fields(struct s_tag_field const *);
// public: bool s_tag_struct_definition::owns_field(struct s_tag_field const *) const;
// public: long s_tag_struct_definition::get_struct_size(void) const;
// public: long s_tag_struct_definition::get_cache_file_struct_size(void) const;
// public: long s_tag_struct_definition::get_alignment_bits(void) const;
// public: char const * s_tag_struct_definition::get_size_string(void) const;
// public: unsigned long s_tag_struct_definition::get_runtime_flags(void) const;
// public: bool s_tag_struct_definition::is_built_from_disk(void) const;
// public: struct byte_swap_definition * s_tag_struct_definition::get_byte_swap_definition(void) const;
// public: __int64 s_tag_struct_definition::get_exploded_struct_size(void) const;
// public: class c_tag_struct_vtable_interface const * s_tag_struct_definition::get_struct_vtable(void) const;
// public: void const * s_tag_struct_definition::get_type_key(void) const;
// public: struct s_tag_persistent_identifier const & s_tag_struct_definition::get_persistent_identifier(void) const;
// public: struct s_tag_struct_definition const * s_tag_struct_definition::get_ancestor_definition(void) const;
// public: struct s_tag_struct_definition * s_tag_struct_definition::get_ancestor_definition_mutable(void);
// public: struct s_tag_struct_definition * s_tag_struct_definition::get_mutable_ancestor_definition(void);
// public: struct s_tag_struct_definition const * s_tag_struct_definition::get_descendent_definition(void) const;
// public: char const * s_tag_struct_definition::get_pretty_name(void) const;
// public: char const * s_tag_struct_definition::get_name(void) const;
// public: void s_tag_struct_definition::set_descendent_definition(struct s_tag_struct_definition *);
// public: enum e_tag_memory_allocation_type s_tag_struct_definition::get_preferred_memory_type(void);
// public: class c_tag_memory_attributes const & s_tag_struct_definition::get_memory_attributes(void) const;
// public: void s_tag_struct_definition::validate_vtable(void);
// public: long s_tag_block_definition::get_element_size(void) const;
// public: char const * s_tag_block_definition::get_size_string(void) const;
// public: struct s_tag_field const * s_tag_block_definition::get_fields(void) const;
// public: long s_tag_block_definition::get_cache_file_element_size(void) const;
// public: unsigned long s_tag_block_definition::get_runtime_flags(void) const;
// public: bool s_tag_block_definition::does_not_exist_in_cache_build(void) const;
// public: long s_tag_block_definition::get_alignment_bits(void) const;
// public: struct byte_swap_definition * s_tag_block_definition::get_byte_swap_definition(void) const;
// public: __int64 s_tag_block_definition::get_exploded_maximum_block_size(void) const;
// public: class c_tag_struct_vtable_interface const * s_tag_block_definition::get_struct_vtable(void) const;
// public: void const * s_tag_block_definition::get_type_key(void) const;
// public: struct s_tag_persistent_identifier const & s_tag_block_definition::get_persistent_identifier(void) const;
// public: char const * s_tag_block_definition::get_pretty_name(void) const;
// public: char const * s_tag_block_definition::get_elements_name(void) const;
// public: char const * s_tag_block_definition::get_block_name(void) const;
// public: unsigned long s_tag_block_definition::get_allocation_flags(void) const;
// public: enum e_tag_memory_allocation_type s_tag_block_definition::get_preferred_memory_type(void);
// public: class c_tag_memory_attributes const & s_tag_block_definition::get_memory_attributes(void) const;
// public: struct s_tag_field const * s_tag_array_definition::get_fields(void) const;
// public: long s_tag_array_definition::get_element_size(void) const;
// public: long s_tag_array_definition::get_cache_file_element_size(void) const;
// public: unsigned long s_tag_array_definition::get_runtime_flags(void) const;
// public: class c_tag_struct_vtable_interface const * s_tag_array_definition::get_struct_vtable(void) const;
// public: void const * s_tag_array_definition::get_type_key(void) const;
// public: struct s_tag_persistent_identifier const & s_tag_array_definition::get_persistent_identifier(void) const;
// public: char const * s_tag_array_definition::get_pretty_name(void) const;
// public: char const * s_tag_array_definition::get_elements_name(void) const;
// public: char const * s_tag_array_definition::get_array_name(void) const;
// public: enum e_tag_memory_allocation_type s_tag_array_definition::get_preferred_memory_type(void);
// public: class c_tag_memory_attributes const & s_tag_array_definition::get_memory_attributes(void) const;
// public: struct s_tag_field const * s_tag_resource_definition::get_fields(void) const;
// public: long s_tag_resource_definition::get_alignment_bits(void) const;
// public: long s_tag_resource_definition::get_resource_size(void) const;
// public: long s_tag_resource_definition::get_cache_file_resource_size(void) const;
// public: unsigned long s_tag_resource_definition::get_runtime_flags(void) const;
// public: class c_tag_struct_vtable_interface const * s_tag_resource_definition::get_struct_vtable(void) const;
// public: void const * s_tag_resource_definition::get_type_key(void) const;
// public: long s_tag_resource_definition::get_pageable_alignment_bits(void) const;
// public: long s_tag_resource_definition::get_optional_alignment_bits(void) const;
// public: struct s_tag_persistent_identifier const & s_tag_resource_definition::get_persistent_identifier(void) const;
// public: char const * s_tag_resource_definition::get_pretty_name(void) const;
// public: char const * s_tag_resource_definition::get_resource_name(void) const;
// public: char const * s_tag_resource_definition::get_elements_name(void) const;
// public: bool s_tag_resource_definition::required(void) const;
// public: bool s_tag_resource_definition::not_required_immediately(void) const;
// public: bool s_tag_resource_definition::optional(void) const;
// public: bool s_tag_resource_definition::streamed(void) const;
// public: void s_tag_resource_definition::validate_vtable(void);
// public: unsigned long s_tag_struct_definition::get_legacy_struct_tag(void) const;
// public: long s_tag_struct_definition::get_legacy_version(void) const;
// public: long s_tag_block_definition::get_legacy_version(void) const;
// public: long s_tag_array_definition::get_legacy_version(void) const;
// public: unsigned long s_tag_data_definition::get_allocation_flags(void) const;
// public: class c_tag_memory_attributes s_tag_data_definition::get_memory_attributes(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_byte_swap_proc(void) const;
// public: virtual void c_legacy_tag_struct_vtable_shim::byte_swap_block_proc(void *) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_postprocess_proc(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_format_proc(void) const;
// public: virtual char * c_legacy_tag_struct_vtable_shim::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_on_delete_proc(void) const;
// public: virtual void c_legacy_tag_struct_vtable_shim::on_delete_thunk(void *) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_on_new_proc(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::on_new_thunk(void *) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_on_copy_proc(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_write_to_cache_file_proc(void) const;
// public: virtual void c_legacy_tag_struct_vtable_shim::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_legacy_tag_struct_vtable_shim::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_legacy_tag_struct_vtable_shim::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_custom_postprocess_proc(void) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::postprocess_tag_thunk(long, bool) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_custom_missing_tag_proc(void) const;
// public: virtual void c_legacy_tag_group_vtable_shim::handle_missing_tag_thunk(unsigned long, char const *, unsigned long, unsigned long, char const *, long *) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_on_save_tag_proc(void) const;
// public: virtual void c_legacy_tag_group_vtable_shim::on_save_tag_thunk(long) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_write_to_cache_file_proc(void) const;
// public: virtual void c_legacy_tag_group_vtable_shim::write_tag_to_cache_file_thunk(long, unsigned long, class c_cache_file_scratch_allocator *, class c_cache_file_resource_library *, class c_cache_file_tracer *, void **, void **) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_valid_alternate_streams(void) const;
// public: virtual struct s_tag_group_stream_list * c_legacy_tag_group_vtable_shim::get_alterante_streams_thunk(void) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_should_load_tag_stream_proc(void) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::should_load_tag_stream_thunk(unsigned long, bool) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_custom_xsync_runtime_platforms(void) const;
// public: virtual unsigned long c_legacy_tag_group_vtable_shim::get_xsync_runtime_platforms_thunk(void) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::has_postprocess_on_sync_proc(void) const;
// public: virtual bool c_legacy_tag_group_vtable_shim::postprocess_on_sync_thunk(long, enum e_runtime_platform_type, class c_cache_file_global_tag_registry *, bool) const;
// public: unsigned long s_tag_group::get_xsync_version(void) const;
// public: long s_tag_group::get_non_temporary_group_index(void) const;
// public: void s_tag_group::set_non_temporary_group_index(long);
// public: bool s_tag_group::valid_for_reload_stage(enum e_tag_reload_stage) const;
// public: void s_tag_group::validate_vtable(void);
// public: enum e_tag_memory_allocation_type c_tag_memory_attributes::get_memory_type(void) const;
// public: unsigned long c_tag_memory_attributes::get_usage_flags(void) const;
// public: void c_tag_memory_attributes::set_attributes(enum e_tag_memory_allocation_type, unsigned long);
// public: bool c_tag_memory_attributes::operator==(class c_tag_memory_attributes const &) const;
// public: bool c_tag_memory_attributes::operator!=(class c_tag_memory_attributes const &) const;
// class c_tag_memory_attributes make_tag_memory_attributes(enum e_tag_memory_allocation_type, unsigned long);
// public: bool c_flags_no_init<enum e_tag_memory_usage_bit, unsigned long, 6, struct s_default_enum_string_resolver>::operator==(class c_flags_no_init<enum e_tag_memory_usage_bit, unsigned long, 6, struct s_default_enum_string_resolver> const &) const;
// unsigned long const * array_begin<unsigned long const, 4>(unsigned long const (&)[4]);
// unsigned long const * array_end<unsigned long const, 4>(unsigned long const (&)[4]);
// bool std::equal<unsigned long const *, unsigned long const *>(unsigned long const *, unsigned long const *, unsigned long const *);
// unsigned long const * std::_Checked_base<unsigned long const *>(unsigned long const *&);
// struct std::random_access_iterator_tag std::_Iter_random<unsigned long const *, unsigned long const *>(unsigned long const *const &, unsigned long const *const &);
// bool std::_Equal<unsigned long const *, unsigned long const *>(unsigned long const *, unsigned long const *, unsigned long const *, struct std::random_access_iterator_tag, struct std::_Range_checked_iterator_tag);
// unsigned long const * std::_Checked_base<unsigned long const *>(unsigned long const *&, struct std::_Unchanged_checked_iterator_base_type_tag);
// bool std::_Equal<unsigned long const *, unsigned long const *, struct std::forward_iterator_tag>(unsigned long const *, unsigned long const *, unsigned long const *, struct std::forward_iterator_tag, struct std::_Range_checked_iterator_tag);
