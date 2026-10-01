#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_event_definitions.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_event_definitions.h"
#include "omaha\tag_files\string_ids.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

// file-static in the target (0x85313AAC, not in the map)
static char const * game_engine_event_audience_enum_definition_strings[k_number_of_game_engine_event_audiences] =
{
    "cause player",
    "cause team",
    "effect player",
    "effect team",
    "all",
};

c_tag_struct_vtable<c_game_engine_event_block_vtable> game_engine_event_block_struct_struct_vtable;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition game_engine_event_block; // "?game_engine_event_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition game_engine_event_block_struct; // "?game_engine_event_block_struct@@3Us_tag_struct_definition@@A"
// class c_tag_struct_vtable<class c_game_engine_event_block_vtable> game_engine_event_block_struct_struct_vtable; // "?game_engine_event_block_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_game_engine_event_block_vtable@@@@A"

// char * game_engine_event_definition_format(long, __int64, struct s_tag_block *, long, char *, long);
// public: c_tag_struct_vtable<class c_game_engine_event_block_vtable>::c_tag_struct_vtable<class c_game_engine_event_block_vtable>(void);
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_byte_swap_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_engine_event_block_vtable>::byte_swap_block_proc(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_postprocess_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_format_proc(void) const;
// public: virtual char * c_tag_struct_vtable<class c_game_engine_event_block_vtable>::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_on_delete_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_engine_event_block_vtable>::on_delete_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_on_new_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::on_new_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_on_copy_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_write_to_cache_file_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_engine_event_block_vtable>::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_block_does_not_exist_in_cache_file_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::block_does_not_exist_in_cache_file_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_tag_struct_vtable<class c_game_engine_event_block_vtable>::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::has_fixup_old_struct_from_disk_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_engine_event_block_vtable>::fixup_old_struct_from_disk_thunk(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: static void s_tag_vtable_has_byte_swap_proc<class c_game_engine_event_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_postprocess_proc<class c_game_engine_event_block_vtable>::call(long, void *, bool);
// public: static char * s_tag_vtable_has_format_proc<class c_game_engine_event_block_vtable>::call(long, __int64, struct s_tag_block *, long, char *, long);
// public: static char * c_game_engine_event_block_vtable::format_proc(long, __int64, struct s_tag_block *, long, char *, long);
// public: static void s_tag_vtable_has_on_delete_proc<class c_game_engine_event_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_new_proc<class c_game_engine_event_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_copy_proc<class c_game_engine_event_block_vtable>::call(void const *, void *);
// public: static void s_tag_vtable_has_write_to_cache_file_proc<class c_game_engine_event_block_vtable>::call(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);
// public: static bool s_tag_vtable_has_block_does_not_exist_in_cache_file<class c_game_engine_event_block_vtable>::call(void);
// public: static struct s_tag_struct_definition * s_tag_vtable_has_get_fixup_source_definition_proc<class c_game_engine_event_block_vtable>::call(void);
// public: static struct s_tag_struct_definition * c_game_engine_event_block_vtable::get_fixup_source_definition_proc(void);
// public: static bool s_tag_vtable_has_fixup_old_struct_proc<class c_game_engine_event_block_vtable>::call(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool c_game_engine_event_block_vtable::fixup_old_struct_proc(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool s_tag_vtable_has_fixup_old_struct_from_disk_proc<class c_game_engine_event_block_vtable>::call(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: void c_flags_no_init<enum e_game_engine_event_input, unsigned char, 5, struct s_default_enum_string_resolver>::set(enum e_game_engine_event_input, bool);
// public: struct s_game_engine_event_response_definition_v1* c_basic_buffer<void>::c_basic_buffer_checked_caster::operatorcast<struct s_game_engine_event_response_definition_v1>(void);
// public: struct s_game_engine_event_response_definition * c_basic_buffer<void>::c_basic_buffer_checked_caster::operatorcast<struct s_game_engine_event_response_definition>(void);
// public: struct s_game_engine_event_response_definition_v1* c_basic_buffer<void>::get_as_type<struct s_game_engine_event_response_definition_v1>(void);
// public: struct s_game_engine_event_response_definition * c_basic_buffer<void>::get_as_type<struct s_game_engine_event_response_definition>(void);
// public: struct s_game_engine_event_response_definition_v1* c_basic_buffer<void>::get_as_type_from_offset<struct s_game_engine_event_response_definition_v1>(unsigned long);
// public: struct s_game_engine_event_response_definition * c_basic_buffer<void>::get_as_type_from_offset<struct s_game_engine_event_response_definition>(unsigned long);

char * game_engine_event_definition_format(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?game_engine_event_definition_format@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_game_engine_event_response_definition * response = &static_cast<s_game_engine_event_response_definition *>(block->address)[element_index];
    csnzprintf(buffer, buffer_size, "%s : %s", string_id_get_string_const(response->name), game_engine_event_audience_enum_definition_strings[response->audience]);

    return buffer;
};
