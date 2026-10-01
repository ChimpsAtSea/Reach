/* ---------- headers */

#include "omaha\game\incidents\incident_response_definition.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static s_tag_struct_legacy_vtable game_incident_daily_challenge_to_increment_block_struct_definition_legacy_vtable;
static s_tag_struct_manual_fixup_definition game_incident_daily_challenge_to_increment_block_struct_definition_manual_fixup;
static s_tag_struct_manual_fixup_definition game_incident_response_block_v1_struct_definition_manual_fixup;
static s_tag_struct_legacy_vtable game_incident_response_block_v1_struct_definition_legacy_vtable =
{
    NULL,
    postprocess_game_incident_response_block,
    NULL,
    NULL,
    NULL,
    format_game_incident_response_block,
    NULL
};
static c_legacy_tag_struct_vtable_shim game_incident_daily_challenge_to_increment_block_struct_definition_vtable_shim(&game_incident_daily_challenge_to_increment_block_struct_definition_legacy_vtable, &game_incident_daily_challenge_to_increment_block_struct_definition_manual_fixup);
static c_legacy_tag_struct_vtable_shim game_incident_response_block_v1_struct_definition_vtable_shim(&game_incident_response_block_v1_struct_definition_legacy_vtable, &game_incident_response_block_v1_struct_definition_manual_fixup);
c_tag_struct_vtable<c_game_incident_response_block_vtable> game_incident_response_block_struct_struct_vtable;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition game_incident_response_block; // "?game_incident_response_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition game_incident_response_block_struct; // "?game_incident_response_block_struct@@3Us_tag_struct_definition@@A"
// class c_tag_struct_vtable<class c_game_incident_response_block_vtable> game_incident_response_block_struct_struct_vtable; // "?game_incident_response_block_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_game_incident_response_block_vtable@@@@A"

// char * format_game_incident_response_block(long, __int64, struct s_tag_block *, long, char *, long);
// bool postprocess_game_incident_response_block(long, void *, bool);
// public: c_tag_struct_vtable<class c_game_incident_response_block_vtable>::c_tag_struct_vtable<class c_game_incident_response_block_vtable>(void);
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_byte_swap_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_incident_response_block_vtable>::byte_swap_block_proc(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_postprocess_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_format_proc(void) const;
// public: virtual char * c_tag_struct_vtable<class c_game_incident_response_block_vtable>::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_on_delete_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_incident_response_block_vtable>::on_delete_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_on_new_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::on_new_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_on_copy_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_write_to_cache_file_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_incident_response_block_vtable>::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_block_does_not_exist_in_cache_file_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::block_does_not_exist_in_cache_file_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_tag_struct_vtable<class c_game_incident_response_block_vtable>::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::has_fixup_old_struct_from_disk_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_incident_response_block_vtable>::fixup_old_struct_from_disk_thunk(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: static void s_tag_vtable_has_byte_swap_proc<class c_game_incident_response_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_postprocess_proc<class c_game_incident_response_block_vtable>::call(long, void *, bool);
// public: static bool c_game_incident_response_block_vtable::postprocess_proc(long, void *, bool);
// public: static char * s_tag_vtable_has_format_proc<class c_game_incident_response_block_vtable>::call(long, __int64, struct s_tag_block *, long, char *, long);
// public: static char * c_game_incident_response_block_vtable::format_proc(long, __int64, struct s_tag_block *, long, char *, long);
// public: static void s_tag_vtable_has_on_delete_proc<class c_game_incident_response_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_new_proc<class c_game_incident_response_block_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_copy_proc<class c_game_incident_response_block_vtable>::call(void const *, void *);
// public: static void s_tag_vtable_has_write_to_cache_file_proc<class c_game_incident_response_block_vtable>::call(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);
// public: static bool s_tag_vtable_has_block_does_not_exist_in_cache_file<class c_game_incident_response_block_vtable>::call(void);
// public: static struct s_tag_struct_definition * s_tag_vtable_has_get_fixup_source_definition_proc<class c_game_incident_response_block_vtable>::call(void);
// public: static struct s_tag_struct_definition * c_game_incident_response_block_vtable::get_fixup_source_definition_proc(void);
// public: static bool s_tag_vtable_has_fixup_old_struct_proc<class c_game_incident_response_block_vtable>::call(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool c_game_incident_response_block_vtable::fixup_old_struct_proc(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool s_tag_vtable_has_fixup_old_struct_from_disk_proc<class c_game_incident_response_block_vtable>::call(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: struct s_game_incident_response_v1* c_basic_buffer<void>::c_basic_buffer_checked_caster::operatorcast<struct s_game_incident_response_v1>(void);
// public: struct s_game_incident_response * c_basic_buffer<void>::c_basic_buffer_checked_caster::operatorcast<struct s_game_incident_response>(void);
// public: struct s_game_incident_response_v1* c_basic_buffer<void>::get_as_type<struct s_game_incident_response_v1>(void);
// public: struct s_game_incident_response * c_basic_buffer<void>::get_as_type<struct s_game_incident_response>(void);
// public: struct s_game_incident_response_v1* c_basic_buffer<void>::get_as_type_from_offset<struct s_game_incident_response_v1>(unsigned long);
// public: struct s_game_incident_response * c_basic_buffer<void>::get_as_type_from_offset<struct s_game_incident_response>(unsigned long);

char * format_game_incident_response_block(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_game_incident_response_block@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    s_game_incident_response * response = static_cast<s_game_incident_response *>(tag_block_get_element_with_size(block, element_index, sizeof(s_game_incident_response)));
    if (response->heat_award != 0)
    {
        csnzprintf(buffer, buffer_size, " %d heat", response->heat_award);
    }
    if (response->game_engine_event != 0)
    {
        csnzappendf(buffer, buffer_size, " %s", string_id_get_string_const(response->game_engine_event));
    }
    if (response->medal != 0)
    {
        csnzappendf(buffer, buffer_size, " %s", string_id_get_string_const(response->medal));
    }
    if (response->commendation != 0)
    {
        csnzappendf(buffer, buffer_size, " %s", string_id_get_string_const(response->commendation));
    }
    if (response->achievement != 0)
    {
        csnzappendf(buffer, buffer_size, " %s", string_id_get_string_const(response->achievement));
    }
    if (response->avatar_award != 0)
    {
        csnzappendf(buffer, buffer_size, " %s", string_id_get_string_const(response->avatar_award));
    }
    if (response->challenges.count != 0)
    {
        csnzappendf(buffer, buffer_size, " challenges");
    }
    return buffer;
};

bool postprocess_game_incident_response_block(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_game_incident_response_block@@YA_NJPAX_N@Z");

    s_game_incident_response * response = static_cast<s_game_incident_response *>(data);
    response->internal_hs_script_index = NONE;
    return true;
};
