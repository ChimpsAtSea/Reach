#pragma once
#ifndef __TAG_GROUP_DEFINITIONS_H__
#define __TAG_GROUP_DEFINITIONS_H__

/* ---------- headers */

#include "omaha/memory/static_arrays.h"
#include "omaha/tag_files/tag_groups.h"

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

/* ---------- definitions */

struct s_tag_struct_definition;
struct s_cache_file_builder_stream_context;
struct s_tag_group_stream_list;
struct s_tag_field;
struct s_tag_resource_estimated_size;

class c_cache_file_scratch_allocator;
class c_cache_file_resource_library;
class c_cache_file_tracer;
class c_cache_file_global_tag_registry;
class c_tag_group_reporter;
class c_tag_resource_predictor;
class c_tag_resource_prediction_collector;
class c_tag_allocator;

template<typename t_type> class c_basic_buffer;

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

struct s_tag_data_definition
{

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
