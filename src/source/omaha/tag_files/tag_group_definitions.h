#pragma once
#ifndef __TAG_GROUP_DEFINITIONS_H__
#define __TAG_GROUP_DEFINITIONS_H__

/* ---------- headers */

#include "omaha/memory/static_arrays.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum e_tag_memory_allocation_type
{
    _tag_memory_unknown = 0,
    _tag_memory_node
};

enum e_tag_memory_usage_bit
{
    _tag_memory_unknown0_bit,
    _tag_memory_unknown1_bit,
    _tag_memory_writeable_bit,
    _tag_memory_unknown3_bit,
    _tag_memory_unknown4_bit,
    _tag_memory_unknown5_bit,
    k_num_tag_memory_usage_bits
};

enum e_runtime_platform_type;
enum e_tag_reload_stage;

// 62 types (s_static_array<s_tag_persist_index<3>, 62> in tag_group_layout_writer); values verified in tag_field_editor_defaults (2,3,39,40,50,57,59,60), names from the Reach tag field type list
enum e_tag_field
{
    _field_string = 0,
    _field_long_string,
    _field_string_id,
    _field_old_string_id,
    _field_char_integer,
    _field_short_integer,
    _field_long_integer,
    _field_int64_integer,
    _field_angle,
    _field_tag,
    _field_char_enum,
    _field_enum,
    _field_long_enum,
    _field_long_flags,
    _field_word_flags,
    _field_byte_flags,
    _field_point_2d,
    _field_rectangle_2d,
    _field_rgb_color,
    _field_argb_color,
    _field_real,
    _field_real_fraction,
    _field_real_point_2d,
    _field_real_point_3d,
    _field_real_vector_2d,
    _field_real_vector_3d,
    _field_real_quaternion,
    _field_real_euler_angles_2d,
    _field_real_euler_angles_3d,
    _field_real_plane_2d,
    _field_real_plane_3d,
    _field_real_rgb_color,
    _field_real_argb_color,
    _field_real_hsv_color,
    _field_real_ahsv_color,
    _field_short_bounds,
    _field_angle_bounds,
    _field_real_bounds,
    _field_real_fraction_bounds,
    _field_tag_reference,
    _field_block,
    _field_long_block_flags,
    _field_word_block_flags,
    _field_byte_block_flags,
    _field_char_block_index,
    _field_custom_char_block_index,
    _field_short_block_index,
    _field_custom_short_block_index,
    _field_long_block_index,
    _field_custom_long_block_index,
    _field_data,
    _field_vertex_buffer,
    _field_pad,
    _field_useless_pad,
    _field_skip,
    _field_explanation,
    _field_custom,
    _field_struct,
    _field_array,
    _field_pageable_resource,
    _field_api_interop,
    _field_terminator,
    k_number_of_tag_field_types
};

/* ---------- definitions */

struct byte_swap_definition;
class c_tag_struct_vtable_interface;

// $TODO layout: get_struct_size reads +0x24, get_byte_swap_definition returns this+0x6C
struct s_tag_struct_definition
{
    long get_struct_size(void) const;
    byte_swap_definition * get_byte_swap_definition(void) const;
    long get_alignment_bits(void) const;
    unsigned long get_runtime_flags(void) const;
    char const * get_name(void) const;
    s_tag_struct_definition const * get_descendent_definition(void) const;
    s_tag_struct_definition const * get_ancestor_definition(void) const;
    c_tag_struct_vtable_interface const * get_struct_vtable(void) const;
};

// layout from c_tag_block_from_struct::c_tag_block_from_struct ("fake_block_init", "fake_block_init", 1, "1", struct_definition) and tag_block_get_max_element_size (+0x10)
struct s_tag_block_definition
{
    char const * name; // 0x0
    char const * display_name; // 0x4
    long maximum_element_count; // 0x8
    char const * maximum_element_count_string; // 0xC
    s_tag_struct_definition const * struct_definition; // 0x10

    char const * get_block_name(void) const;
};
static_assert(sizeof(s_tag_block_definition) == 0x14, "s_tag_block_definition");

struct s_tag_block;
struct s_cache_file_builder_stream_context;
struct s_tag_group_stream_list;
struct s_tag_resource_estimated_size;

// tag_field_scan indexes fields with a 0x10 stride; type @0x0 and definition @0x8 verified in c_tag_struct_editor, name/id from H3 (unverified)
struct s_tag_field
{
    e_tag_field type; // 0x0
    char const * name; // 0x4
    void const * definition; // 0x8
    unsigned long id; // 0xC
};
static_assert(sizeof(s_tag_field) == 0x10, "s_tag_field");

// maps a field type to the type of s_tag_field::definition (return type of get_field_definition<k_field_type>)
template<e_tag_field k_field_type>
struct s_tag_field_definition_type;

struct s_tag_reference_definition;

template<>
struct s_tag_field_definition_type<_field_tag_reference>
{
    typedef s_tag_reference_definition type;
};

// count @0x4 and struct_definition @0xC verified in tag_field_get_inline_aggregate_count / tag_field_get_aggregate_definition; name/count_string and total size unverified
struct s_tag_array_definition
{
    char const * name; // 0x0
    long count; // 0x4
    char const * count_string; // 0x8
    s_tag_struct_definition const * struct_definition; // 0xC
};

struct s_tag_resource_definition;
struct s_tag_interop_definition;

template<>
struct s_tag_field_definition_type<_field_block>
{
    typedef s_tag_block_definition type;
};

template<>
struct s_tag_field_definition_type<_field_struct>
{
    typedef s_tag_struct_definition type;
};

template<>
struct s_tag_field_definition_type<_field_array>
{
    typedef s_tag_array_definition type;
};

template<>
struct s_tag_field_definition_type<_field_pageable_resource>
{
    typedef s_tag_resource_definition type;
};

template<>
struct s_tag_field_definition_type<_field_api_interop>
{
    typedef s_tag_interop_definition type;
};

// ??$get_field_definition@$0CH@@@YAPAUs_tag_reference_definition@@PBUs_tag_field@@@Z (f i, scenario_zone_resources.obj, body not reversed yet)
// also instantiated for _field_block/_field_pageable_resource/_field_api_interop (tag_groups.obj), _field_struct/_field_array (tag_group_editing.obj)
template<e_tag_field k_field_type>
typename s_tag_field_definition_type<k_field_type>::type * get_field_definition(s_tag_field const * field);

class c_cache_file_scratch_allocator;
class c_cache_file_resource_library;
class c_cache_file_tracer;
class c_cache_file_global_tag_registry;
class c_tag_group_reporter;
class c_tag_resource_predictor;
class c_tag_resource_prediction_collector;
class c_tag_allocator;

template<typename t_type> class c_basic_buffer;

// $TODO layout (struct definition pointer @0x8 per get_persistent_identifier)
struct s_tag_resource_definition
{
    char const * name; // 0x0 (?sound_resource_definition@@3Us_tag_resource_definition@@A data)
    unsigned long unknown4; // 0x4
    s_tag_struct_definition const * struct_definition; // 0x8 (read by get_struct_from_resource_definition)

    s_tag_persistent_identifier const & get_persistent_identifier(void) const;
};

class c_tag_memory_attributes
{
private:
    e_tag_memory_allocation_type m_allocation_type;
    c_flags_no_init<e_tag_memory_usage_bit, unsigned long, k_num_tag_memory_usage_bits, s_default_enum_string_resolver> m_usage;
public:
    e_tag_memory_allocation_type get_memory_type(void) const;
    unsigned long get_usage_flags(void)const;
    void set_attributes(e_tag_memory_allocation_type allocation_type, unsigned long usage_flags);
    bool operator==(c_tag_memory_attributes const &) const;
    bool operator!=(c_tag_memory_attributes const &) const;
};

enum e_tag_data_definition_flags
{
    _tag_data_definition_is_temporary_bit = 13,
};

// layout from ?hs_old_syntax_data_definition@@3Us_tag_data_definition@@A (0x28 apart from hs_string_data_definition)
struct s_tag_data_definition
{
    char const * name; // 0x0
    unsigned long flags; // 0x4
    long alignment_bits; // 0x8
    long maximum_size; // 0xC
    char const * maximum_size_string; // 0x10
    void * unknown14; // 0x14
    void (*byte_swap_proc)(void * struct_data, void * data, long data_size, bool writing); // 0x18 (called false/true around writes)
    unsigned long unknown1C[3]; // 0x1C

    unsigned long get_allocation_flags(void) const;
};
static_assert(sizeof(s_tag_data_definition) == 0x28, "s_tag_data_definition");

// $TODO: fields after strings not reversed (object_type_enum_definition data: name, count 14, strings, 0, 0)
struct s_string_list_definition
{
    char const * name; // 0x0
    long count; // 0x4
    char const ** strings; // 0x8
};

template<typename t_type>
struct s_tag_vtable_default_entry
{
    static t_type call(void);
};

struct s_tag_struct_legacy_vtable
{
    void (*byte_swap_proc)(void *);
    bool (*postprocess_proc)(long, void *, bool);
    bool (*new_proc)(void *);
    void (*delete_proc)(void *);
    bool (*copy_proc)(void const *, void *);
    char* (*format_proc)(long, __int64, s_tag_block *, long, char *, long);
    void (*write_to_cache_file_block)(long, s_tag_block *, s_cache_file_builder_stream_context const *, void **, void **);
};

struct s_tag_struct_manual_fixup_definition
{
    s_tag_struct_definition * from_struct_definition;
    bool (*fixup_proc)(c_basic_buffer<void> &, s_tag_struct_definition const *, c_basic_buffer<void> &, s_tag_struct_definition const *, c_tag_allocator *, bool);
};

class c_tag_struct_vtable_interface
{
public:
    virtual bool has_byte_swap_proc(void)const;
    virtual void byte_swap_block_proc(void *)const;
    virtual bool has_postprocess_proc(void)const;
    virtual bool postprocess_thunk(long,void *,bool)const;
    virtual bool has_format_proc(void)const;
    virtual char * format_thunk(long,__int64,s_tag_block *,long,char *,long)const ;
    virtual bool has_on_delete_proc(void)const;
    virtual void on_delete_thunk(void *)const;
    virtual bool has_on_new_proc(void)const;
    virtual bool on_new_thunk(void *)const;
    virtual bool has_on_copy_proc(void)const;
    virtual bool on_copy_thunk(void const *,void *)const;
    virtual bool has_write_to_cache_file_proc(void)const;
    virtual void write_to_cache_file_thunk(long,s_tag_block *,s_cache_file_builder_stream_context const *,void * *,void * *)const;
    virtual bool has_block_does_not_exist_in_cache_file_proc(void)const;
    virtual bool block_does_not_exist_in_cache_file_thunk(void)const ;
    virtual bool has_fixup_old_struct_definition(void)const;
    virtual s_tag_struct_definition * get_fixup_source_definition_thunk(void)const;
    virtual bool has_fixup_old_struct_proc(void)const;
    virtual bool fixup_old_struct_thunk(c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const;
    virtual bool has_fixup_old_struct_from_disk_proc(void)const;
    virtual bool fixup_old_struct_from_disk_thunk(s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const;
};

class c_legacy_tag_struct_vtable_shim :
    public c_tag_struct_vtable_interface
{
public:
    // ??0c_legacy_tag_struct_vtable_shim@@QAA@PBUs_tag_struct_legacy_vtable@@PBUs_tag_struct_manual_fixup_definition@@@Z (body not reversed yet)
    c_legacy_tag_struct_vtable_shim(s_tag_struct_legacy_vtable const * struct_vtable, s_tag_struct_manual_fixup_definition const * manual_fixup);

    virtual bool has_byte_swap_proc(void)const;
    virtual void byte_swap_block_proc(void *)const;
    virtual bool has_postprocess_proc(void)const;
    virtual bool postprocess_thunk(long,void *,bool)const;
    virtual bool has_format_proc(void)const;
    virtual char * format_thunk(long,__int64,s_tag_block *,long,char *,long)const ;
    virtual bool has_on_delete_proc(void)const;
    virtual void on_delete_thunk(void *)const;
    virtual bool has_on_new_proc(void)const;
    virtual bool on_new_thunk(void *)const;
    virtual bool has_on_copy_proc(void)const;
    virtual bool on_copy_thunk(void const *,void *)const;
    virtual bool has_write_to_cache_file_proc(void)const;
    virtual void write_to_cache_file_thunk(long,s_tag_block *,s_cache_file_builder_stream_context const *,void * *,void * *)const;
    virtual bool has_block_does_not_exist_in_cache_file_proc(void)const;
    virtual bool block_does_not_exist_in_cache_file_thunk(void)const ;
    virtual bool has_fixup_old_struct_definition(void)const;
    virtual s_tag_struct_definition * get_fixup_source_definition_thunk(void)const;
    virtual bool has_fixup_old_struct_proc(void)const;
    virtual bool fixup_old_struct_thunk(c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const;
    virtual bool has_fixup_old_struct_from_disk_proc(void)const;
    virtual bool fixup_old_struct_from_disk_thunk(s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const;

    s_tag_struct_legacy_vtable const * m_struct_vtable;
    s_tag_struct_manual_fixup_definition const * m_manual_fixup;
};

// default procs for templated tag struct vtables; a t_vtable class derives from this and hides the procs it implements
class c_tag_struct_vtable_defaults
{
public:
    static void byte_swap_proc(void * data)
    {
        s_tag_vtable_default_entry<void>::call();
    }

    static bool postprocess_proc(long tag_index, void * data, bool for_editor)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }

    static char * format_proc(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
    {
        return s_tag_vtable_default_entry<char *>::call();
    }

    static void on_delete_proc(void * data)
    {
        s_tag_vtable_default_entry<void>::call();
    }

    static bool on_new_proc(void * data)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }

    static bool on_copy_proc(void const * source, void * destination)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }

    static void write_to_cache_file_proc(long tag_index, s_tag_block * block, s_cache_file_builder_stream_context const * context, void ** source, void ** destination)
    {
        s_tag_vtable_default_entry<void>::call();
    }

    static bool block_does_not_exist_in_cache_file(void)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }

    static s_tag_struct_definition * get_fixup_source_definition_proc(void)
    {
        return s_tag_vtable_default_entry<s_tag_struct_definition *>::call();
    }

    static bool fixup_old_struct_proc(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }

    static bool fixup_old_struct_from_disk_proc(s_tag_struct_definition const * disk_definition, c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        return s_tag_vtable_default_entry<bool>::call();
    }
};

// tag vtable with no custom procs (c_tag_struct_vtable<c_null_tag_vtable> globals)
class c_null_tag_vtable :
    public c_tag_struct_vtable_defaults
{
};

// compile-time check whether a t_vtable proc is the c_tag_struct_vtable_defaults one
template<typename t_proc, t_proc k_proc, t_proc k_default_proc>
struct s_tag_vtable_proc_overridden
{
    enum { value = true };
};

template<typename t_proc, t_proc k_proc>
struct s_tag_vtable_proc_overridden<t_proc, k_proc, k_proc>
{
    enum { value = false };
};

template<typename t_vtable>
struct s_tag_vtable_has_byte_swap_proc
{
    enum { value = s_tag_vtable_proc_overridden<void (*)(void *), &t_vtable::byte_swap_proc, &c_tag_struct_vtable_defaults::byte_swap_proc>::value };

    static void call(void * data)
    {
        t_vtable::byte_swap_proc(data);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_postprocess_proc
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(long, void *, bool), &t_vtable::postprocess_proc, &c_tag_struct_vtable_defaults::postprocess_proc>::value };

    static bool call(long tag_index, void * data, bool for_editor)
    {
        return t_vtable::postprocess_proc(tag_index, data, for_editor);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_format_proc
{
    enum { value = s_tag_vtable_proc_overridden<char * (*)(long, __int64, s_tag_block *, long, char *, long), &t_vtable::format_proc, &c_tag_struct_vtable_defaults::format_proc>::value };

    static char * call(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
    {
        return t_vtable::format_proc(tag_index, field_id, block, element_index, buffer, buffer_size);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_on_delete_proc
{
    enum { value = s_tag_vtable_proc_overridden<void (*)(void *), &t_vtable::on_delete_proc, &c_tag_struct_vtable_defaults::on_delete_proc>::value };

    static void call(void * data)
    {
        t_vtable::on_delete_proc(data);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_on_new_proc
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(void *), &t_vtable::on_new_proc, &c_tag_struct_vtable_defaults::on_new_proc>::value };

    static bool call(void * data)
    {
        return t_vtable::on_new_proc(data);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_on_copy_proc
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(void const *, void *), &t_vtable::on_copy_proc, &c_tag_struct_vtable_defaults::on_copy_proc>::value };

    static bool call(void const * source, void * destination)
    {
        return t_vtable::on_copy_proc(source, destination);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_write_to_cache_file_proc
{
    enum { value = s_tag_vtable_proc_overridden<void (*)(long, s_tag_block *, s_cache_file_builder_stream_context const *, void **, void **), &t_vtable::write_to_cache_file_proc, &c_tag_struct_vtable_defaults::write_to_cache_file_proc>::value };

    static void call(long tag_index, s_tag_block * block, s_cache_file_builder_stream_context const * context, void ** source, void ** destination)
    {
        t_vtable::write_to_cache_file_proc(tag_index, block, context, source, destination);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_block_does_not_exist_in_cache_file
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(void), &t_vtable::block_does_not_exist_in_cache_file, &c_tag_struct_vtable_defaults::block_does_not_exist_in_cache_file>::value };

    static bool call(void)
    {
        return t_vtable::block_does_not_exist_in_cache_file();
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_get_fixup_source_definition_proc
{
    enum { value = s_tag_vtable_proc_overridden<s_tag_struct_definition * (*)(void), &t_vtable::get_fixup_source_definition_proc, &c_tag_struct_vtable_defaults::get_fixup_source_definition_proc>::value };

    static s_tag_struct_definition * call(void)
    {
        return t_vtable::get_fixup_source_definition_proc();
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_fixup_old_struct_proc
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(c_basic_buffer<void> &, s_tag_struct_definition const *, c_basic_buffer<void> &, s_tag_struct_definition const *, c_tag_allocator *, bool), &t_vtable::fixup_old_struct_proc, &c_tag_struct_vtable_defaults::fixup_old_struct_proc>::value };

    static bool call(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        return t_vtable::fixup_old_struct_proc(old_buffer, old_definition, new_buffer, new_definition, allocator, byte_swap);
    }
};

template<typename t_vtable>
struct s_tag_vtable_has_fixup_old_struct_from_disk_proc
{
    enum { value = s_tag_vtable_proc_overridden<bool (*)(s_tag_struct_definition const *, c_basic_buffer<void> &, s_tag_struct_definition const *, c_basic_buffer<void> &, s_tag_struct_definition const *, c_tag_allocator *, bool), &t_vtable::fixup_old_struct_from_disk_proc, &c_tag_struct_vtable_defaults::fixup_old_struct_from_disk_proc>::value };

    static bool call(s_tag_struct_definition const * disk_definition, c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        return t_vtable::fixup_old_struct_from_disk_proc(disk_definition, old_buffer, old_definition, new_buffer, new_definition, allocator, byte_swap);
    }
};

// templated tag struct vtable; t_vtable derives from c_tag_struct_vtable_defaults
template<typename t_vtable>
class c_tag_struct_vtable :
    public c_tag_struct_vtable_interface
{
public:
    virtual bool has_byte_swap_proc(void) const
    {
        return s_tag_vtable_has_byte_swap_proc<t_vtable>::value;
    }

    virtual void byte_swap_block_proc(void * data) const
    {
        s_tag_vtable_has_byte_swap_proc<t_vtable>::call(data);
    }

    virtual bool has_postprocess_proc(void) const
    {
        return s_tag_vtable_has_postprocess_proc<t_vtable>::value;
    }

    virtual bool postprocess_thunk(long tag_index, void * data, bool for_editor) const
    {
        return s_tag_vtable_has_postprocess_proc<t_vtable>::call(tag_index, data, for_editor);
    }

    virtual bool has_format_proc(void) const
    {
        return s_tag_vtable_has_format_proc<t_vtable>::value;
    }

    virtual char * format_thunk(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size) const
    {
        return s_tag_vtable_has_format_proc<t_vtable>::call(tag_index, field_id, block, element_index, buffer, buffer_size);
    }

    virtual bool has_on_delete_proc(void) const
    {
        return s_tag_vtable_has_on_delete_proc<t_vtable>::value;
    }

    virtual void on_delete_thunk(void * data) const
    {
        s_tag_vtable_has_on_delete_proc<t_vtable>::call(data);
    }

    virtual bool has_on_new_proc(void) const
    {
        return s_tag_vtable_has_on_new_proc<t_vtable>::value;
    }

    virtual bool on_new_thunk(void * data) const
    {
        return s_tag_vtable_has_on_new_proc<t_vtable>::call(data);
    }

    virtual bool has_on_copy_proc(void) const
    {
        return s_tag_vtable_has_on_copy_proc<t_vtable>::value;
    }

    virtual bool on_copy_thunk(void const * source, void * destination) const
    {
        return s_tag_vtable_has_on_copy_proc<t_vtable>::call(source, destination);
    }

    virtual bool has_write_to_cache_file_proc(void) const
    {
        return s_tag_vtable_has_write_to_cache_file_proc<t_vtable>::value;
    }

    virtual void write_to_cache_file_thunk(long tag_index, s_tag_block * block, s_cache_file_builder_stream_context const * context, void ** source, void ** destination) const
    {
        s_tag_vtable_has_write_to_cache_file_proc<t_vtable>::call(tag_index, block, context, source, destination);
    }

    virtual bool has_block_does_not_exist_in_cache_file_proc(void) const
    {
        return s_tag_vtable_has_block_does_not_exist_in_cache_file<t_vtable>::value;
    }

    virtual bool block_does_not_exist_in_cache_file_thunk(void) const
    {
        return s_tag_vtable_has_block_does_not_exist_in_cache_file<t_vtable>::call();
    }

    virtual bool has_fixup_old_struct_definition(void) const
    {
        return s_tag_vtable_has_get_fixup_source_definition_proc<t_vtable>::value;
    }

    virtual s_tag_struct_definition * get_fixup_source_definition_thunk(void) const
    {
        return s_tag_vtable_has_get_fixup_source_definition_proc<t_vtable>::call();
    }

    virtual bool has_fixup_old_struct_proc(void) const
    {
        return s_tag_vtable_has_fixup_old_struct_proc<t_vtable>::value;
    }

    virtual bool fixup_old_struct_thunk(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap) const
    {
        return s_tag_vtable_has_fixup_old_struct_proc<t_vtable>::call(old_buffer, old_definition, new_buffer, new_definition, allocator, byte_swap);
    }

    virtual bool has_fixup_old_struct_from_disk_proc(void) const
    {
        return s_tag_vtable_has_fixup_old_struct_from_disk_proc<t_vtable>::value;
    }

    virtual bool fixup_old_struct_from_disk_thunk(s_tag_struct_definition const * disk_definition, c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap) const
    {
        return s_tag_vtable_has_fixup_old_struct_from_disk_proc<t_vtable>::call(disk_definition, old_buffer, old_definition, new_buffer, new_definition, allocator, byte_swap);
    }
};

class c_tag_group_vtable_interface
{
public:
    virtual bool has_custom_postprocess_proc(void)const;
    virtual bool postprocess_tag_thunk(long,bool)const;
    virtual bool has_custom_missing_tag_proc(void)const;
    virtual void handle_missing_tag_thunk(unsigned long,char const *,unsigned long,unsigned long,char const *,long *)const;
    virtual bool has_on_save_tag_proc(void)const;
    virtual void on_save_tag_thunk(long)const;
    virtual bool has_write_to_cache_file_proc(void)const;
    virtual void write_tag_to_cache_file_thunk(long,unsigned long,c_cache_file_scratch_allocator *,c_cache_file_resource_library *,c_cache_file_tracer *,void * *,void * *)const;
    virtual bool has_valid_alternate_streams(void)const;
    virtual s_tag_group_stream_list * get_alterante_streams_thunk(void)const;
    virtual bool has_should_load_tag_stream_proc(void)const;
    virtual bool should_load_tag_stream_thunk(unsigned long,bool)const;
    virtual bool has_custom_xsync_runtime_platforms(void)const;
    virtual unsigned long get_xsync_runtime_platforms_thunk(void)const;
    virtual bool has_get_current_xsync_version_proc(void)const;
    virtual unsigned long get_current_xsync_version_thunk(void)const;
    virtual bool has_get_xsync_version_flags_proc(void)const;
    virtual unsigned long get_xsync_version_flags_thunk(unsigned long)const;
    virtual bool has_postprocess_on_sync_proc(void)const;
    virtual bool postprocess_on_sync_thunk(long,e_runtime_platform_type,c_cache_file_global_tag_registry *,bool)const;
    virtual bool has_generate_tag_report_proc(void)const;
    virtual void generate_tag_report_thunk(long,c_tag_group_reporter *)const;
    virtual bool has_build_tag_resource_prediction_proc(void)const;
    virtual void build_predicted_tag_resources_thunk(long,c_tag_resource_predictor *)const;
    virtual bool has_collect_tag_resource_prediction_proc(void)const;
    virtual void collect_predicted_tag_resources_thunk(long,c_tag_resource_prediction_collector *)const;
    virtual bool has_can_group_ever_load_in_game_proc(void)const;
    virtual bool can_group_ever_load_in_game_thunk(void)const;
    virtual bool has_optimize_for_cache_file_proc(void)const;
    virtual void optimize_for_cache_file_thunk(long,e_runtime_platform_type,c_cache_file_global_tag_registry *,bool)const;
    virtual bool has_on_edit_field_proc(void)const;
    virtual unsigned long on_edit_field_thunk(long,__int64,s_tag_field const *)const;
    virtual bool has_estimate_final_resource_size_proc(void)const;
    virtual bool estimate_final_resource_size_thunk(long,s_tag_resource_estimated_size *)const;
    virtual bool has_valid_for_reload_stage_proc(void)const;
    virtual bool valid_for_reload_stage_thunk(e_tag_reload_stage)const;
};

struct s_tag_group_legacy_vtable
{
    bool (*postprocess_tag)(long, bool);
    void (*missing_proc)(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
    void (*on_save_tag)(long);
    void (*write_tag_to_cache_file)(long,unsigned long,c_cache_file_scratch_allocator *,c_cache_file_resource_library *,c_cache_file_tracer *,void * *,void * *);
};

struct s_tag_group_stream_definition
{
    s_tag_group_stream_list * stream_list;
    bool (*should_load_tag_stream)(unsigned long, bool);
};

struct s_tag_group_sync_definition
{
    unsigned long unknown0;
    unsigned long xsync_runtime_platforms;
    bool (*postprocess_on_sync)(int, e_runtime_platform_type, c_cache_file_global_tag_registry *, bool);
};

class c_legacy_tag_group_vtable_shim :
    public c_tag_group_vtable_interface
{
public:
    c_legacy_tag_group_vtable_shim(
        s_tag_group_legacy_vtable const * legacy_vtable,
        s_tag_group_stream_definition const * legacy_stream,
        s_tag_group_sync_definition const * legacy_xsync_declaration);

    virtual bool has_custom_postprocess_proc(void)const ;
    virtual bool postprocess_tag_thunk(long,bool)const ;
    virtual bool has_custom_missing_tag_proc(void)const ;
    virtual void handle_missing_tag_thunk(unsigned long,char const *,unsigned long,unsigned long,char const *,long *)const ;
    virtual bool has_on_save_tag_proc(void)const ;
    virtual void on_save_tag_thunk(long)const ;
    virtual bool has_write_to_cache_file_proc(void)const ;
    virtual void write_tag_to_cache_file_thunk(long,unsigned long,c_cache_file_scratch_allocator *,c_cache_file_resource_library *,c_cache_file_tracer *,void * *,void * *)const ;
    virtual bool has_valid_alternate_streams(void)const ;
    virtual s_tag_group_stream_list * get_alterante_streams_thunk(void)const ;
    virtual bool has_should_load_tag_stream_proc(void)const ;
    virtual bool should_load_tag_stream_thunk(unsigned long,bool)const ;
    virtual bool has_custom_xsync_runtime_platforms(void)const ;
    virtual unsigned long get_xsync_runtime_platforms_thunk(void)const ;
    virtual bool has_postprocess_on_sync_proc(void)const ;
    virtual bool postprocess_on_sync_thunk(long,e_runtime_platform_type,c_cache_file_global_tag_registry *,bool)const ;

private:
    s_tag_group_legacy_vtable const *m_legacy_vtable;
    s_tag_group_stream_definition const *m_legacy_stream;
    s_tag_group_sync_definition const * m_legacy_xsync_declaration;
};

/* ---------- prototypes */

extern bool tag_persistent_identifiers_equal(s_tag_persistent_identifier const & lhs, s_tag_persistent_identifier const & rhs);

/* ---------- globals */

/* ---------- public code */

bool c_tag_struct_vtable_interface::has_byte_swap_proc(void)const
{
    return false;
}

void c_tag_struct_vtable_interface::byte_swap_block_proc(void *)const
{
    s_tag_vtable_default_entry<void>::call();
}

bool c_tag_struct_vtable_interface::has_postprocess_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::postprocess_thunk(long,void *,bool)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_struct_vtable_interface::has_format_proc(void)const
{
    return false;
}

char * c_tag_struct_vtable_interface::format_thunk(long,__int64,s_tag_block *,long,char *,long)const 
{
    return s_tag_vtable_default_entry<char *>::call();
}

bool c_tag_struct_vtable_interface::has_on_delete_proc(void)const
{
    return false;
}

void c_tag_struct_vtable_interface::on_delete_thunk(void *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_struct_vtable_interface::has_on_new_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::on_new_thunk(void *)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_struct_vtable_interface::has_on_copy_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::on_copy_thunk(void const *,void *)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_struct_vtable_interface::has_write_to_cache_file_proc(void)const
{
    return false;
}

void c_tag_struct_vtable_interface::write_to_cache_file_thunk(long,s_tag_block *,s_cache_file_builder_stream_context const *,void * *,void * *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_struct_vtable_interface::has_block_does_not_exist_in_cache_file_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::block_does_not_exist_in_cache_file_thunk(void)const 
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_struct_vtable_interface::has_fixup_old_struct_definition(void)const
{
    return false;
}

s_tag_struct_definition * c_tag_struct_vtable_interface::get_fixup_source_definition_thunk(void)const
{
    return s_tag_vtable_default_entry<s_tag_struct_definition *>::call();
}

bool c_tag_struct_vtable_interface::has_fixup_old_struct_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::fixup_old_struct_thunk(c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_struct_vtable_interface::has_fixup_old_struct_from_disk_proc(void)const
{
    return false;
}

bool c_tag_struct_vtable_interface::fixup_old_struct_from_disk_thunk(s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_basic_buffer<void> &,s_tag_struct_definition const *,c_tag_allocator *,bool)const
{
    return s_tag_vtable_default_entry<bool>::call();
};

bool c_tag_group_vtable_interface::has_custom_postprocess_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::postprocess_tag_thunk(long,bool)const
{
    NOT_IMPLEMENTED;
}

bool c_tag_group_vtable_interface::has_custom_missing_tag_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::handle_missing_tag_thunk(unsigned long,char const *,unsigned long,unsigned long,char const *,long *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_on_save_tag_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::on_save_tag_thunk(long)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_write_to_cache_file_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::write_tag_to_cache_file_thunk(long,unsigned long,c_cache_file_scratch_allocator *,c_cache_file_resource_library *,c_cache_file_tracer *,void * *,void * *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_valid_alternate_streams(void)const
{
    return false;
}

s_tag_group_stream_list * c_tag_group_vtable_interface::get_alterante_streams_thunk(void)const
{
    return s_tag_vtable_default_entry<s_tag_group_stream_list *>::call();
}

bool c_tag_group_vtable_interface::has_should_load_tag_stream_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::should_load_tag_stream_thunk(unsigned long,bool)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_group_vtable_interface::has_custom_xsync_runtime_platforms(void)const
{
    return false;
}

unsigned long c_tag_group_vtable_interface::get_xsync_runtime_platforms_thunk(void)const
{
    return s_tag_vtable_default_entry<unsigned long>::call();
}

bool c_tag_group_vtable_interface::has_get_current_xsync_version_proc(void)const
{
    return false;
}

unsigned long c_tag_group_vtable_interface::get_current_xsync_version_thunk(void)const
{
    return s_tag_vtable_default_entry<unsigned long>::call();
}

bool c_tag_group_vtable_interface::has_get_xsync_version_flags_proc(void)const
{
    return false;
}

unsigned long c_tag_group_vtable_interface::get_xsync_version_flags_thunk(unsigned long)const
{
    return s_tag_vtable_default_entry<unsigned long>::call();
}

bool c_tag_group_vtable_interface::has_postprocess_on_sync_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::postprocess_on_sync_thunk(long,e_runtime_platform_type,c_cache_file_global_tag_registry *,bool)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_group_vtable_interface::has_generate_tag_report_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::generate_tag_report_thunk(long,c_tag_group_reporter *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_build_tag_resource_prediction_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::build_predicted_tag_resources_thunk(long,c_tag_resource_predictor *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_collect_tag_resource_prediction_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::collect_predicted_tag_resources_thunk(long,c_tag_resource_prediction_collector *)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_can_group_ever_load_in_game_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::can_group_ever_load_in_game_thunk(void)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_group_vtable_interface::has_optimize_for_cache_file_proc(void)const
{
    return false;
}

void c_tag_group_vtable_interface::optimize_for_cache_file_thunk(long,e_runtime_platform_type,c_cache_file_global_tag_registry *,bool)const
{
    return s_tag_vtable_default_entry<void>::call();
}

bool c_tag_group_vtable_interface::has_on_edit_field_proc(void)const
{
    return false;
}

unsigned long c_tag_group_vtable_interface::on_edit_field_thunk(long,__int64,s_tag_field const *)const
{
    return s_tag_vtable_default_entry<unsigned long>::call();
}

bool c_tag_group_vtable_interface::has_estimate_final_resource_size_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::estimate_final_resource_size_thunk(long,s_tag_resource_estimated_size *)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

bool c_tag_group_vtable_interface::has_valid_for_reload_stage_proc(void)const
{
    return false;
}

bool c_tag_group_vtable_interface::valid_for_reload_stage_thunk(e_tag_reload_stage)const
{
    return s_tag_vtable_default_entry<bool>::call();
}

#endif // __TAG_GROUP_DEFINITIONS_H__
