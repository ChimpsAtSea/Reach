/* ---------- headers */

#include "omaha\game\player_rewards\player_medals.h"
#include "omaha\game\game_globals.h"
#include "omaha\scenario\scenario.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_tag_struct_vtable<c_game_medal_block_struct_vtable> game_medal_block_struct_struct_vtable;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition game_medal_globals_block; // "?game_medal_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_group game_medal_globals_group; // "?game_medal_globals_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_game_medal_globals_vtable; // "?legacy_game_medal_globals_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_game_medal_globals_stream_definition; // "?legacy_game_medal_globals_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_game_medal_globals_xsync_declaration; // "?legacy_game_medal_globals_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_tag_struct_vtable<class c_game_medal_block_struct_vtable> game_medal_block_struct_struct_vtable; // "?game_medal_block_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_game_medal_block_struct_vtable@@@@A"
// class c_legacy_tag_group_vtable_shim legacy_game_medal_globals_vtable_shim; // "?legacy_game_medal_globals_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long game_medal_definition_get_count(void);
// struct s_game_medal_definition const * game_medal_definition_get(long);
// long game_medal_definition_find(long);
// public: c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::c_tag_struct_vtable<class c_game_medal_block_struct_vtable>(void);
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_byte_swap_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::byte_swap_block_proc(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_postprocess_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_format_proc(void) const;
// public: virtual char * c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_on_delete_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::on_delete_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_on_new_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::on_new_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_on_copy_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_write_to_cache_file_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_block_does_not_exist_in_cache_file_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::block_does_not_exist_in_cache_file_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::has_fixup_old_struct_from_disk_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_game_medal_block_struct_vtable>::fixup_old_struct_from_disk_thunk(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: static void s_tag_vtable_has_byte_swap_proc<class c_game_medal_block_struct_vtable>::call(void *);
// public: static bool s_tag_vtable_has_postprocess_proc<class c_game_medal_block_struct_vtable>::call(long, void *, bool);
// public: static bool c_game_medal_block_struct_vtable::postprocess_proc(long, void *, bool);
// public: static char * s_tag_vtable_has_format_proc<class c_game_medal_block_struct_vtable>::call(long, __int64, struct s_tag_block *, long, char *, long);
// public: static void s_tag_vtable_has_on_delete_proc<class c_game_medal_block_struct_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_new_proc<class c_game_medal_block_struct_vtable>::call(void *);
// public: static bool c_game_medal_block_struct_vtable::on_new_proc(void *);
// public: static bool s_tag_vtable_has_on_copy_proc<class c_game_medal_block_struct_vtable>::call(void const *, void *);
// public: static void s_tag_vtable_has_write_to_cache_file_proc<class c_game_medal_block_struct_vtable>::call(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);
// public: static bool s_tag_vtable_has_block_does_not_exist_in_cache_file<class c_game_medal_block_struct_vtable>::call(void);
// public: static struct s_tag_struct_definition * s_tag_vtable_has_get_fixup_source_definition_proc<class c_game_medal_block_struct_vtable>::call(void);
// public: static bool s_tag_vtable_has_fixup_old_struct_proc<class c_game_medal_block_struct_vtable>::call(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool s_tag_vtable_has_fixup_old_struct_from_disk_proc<class c_game_medal_block_struct_vtable>::call(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);

long game_medal_definition_get_count()
{
    mangled_ppc("?game_medal_definition_get_count@@YAJXZ");

    long count = 0;
    s_game_medal_globals const * medal_globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()))->game_medal_globals.index != NONE ? static_cast<s_game_medal_globals const *>(tag_get(GAME_MEDAL_GLOBALS_TAG, static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()))->game_medal_globals.index)) : NULL;
    if (medal_globals)
    {
        count = medal_globals->medals.count;
    }

    return count;
};

s_game_medal_definition const * game_medal_definition_get(long medal_index)
{
    mangled_ppc("?game_medal_definition_get@@YAPBUs_game_medal_definition@@J@Z");

    s_game_medal_definition const * medal = NULL;
    s_game_medal_globals const * medal_globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()))->game_medal_globals.index != NONE ? static_cast<s_game_medal_globals const *>(tag_get(GAME_MEDAL_GLOBALS_TAG, static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()))->game_medal_globals.index)) : NULL;
    if (medal_globals && medal_index >= 0 && medal_index < medal_globals->medals.count)
    {
        medal = static_cast<s_game_medal_definition const *>(tag_block_get_element_with_size(&medal_globals->medals, medal_index, sizeof(s_game_medal_definition)));
    }

    return medal;
};

long game_medal_definition_find(long name)
{
    mangled_ppc("?game_medal_definition_find@@YAJJ@Z");

    long medal_index = NONE;
    for (long index = 0; index < game_medal_definition_get_count(); index++)
    {
        s_game_medal_definition const * medal = game_medal_definition_get(index);
        if (medal->name == name)
        {
            medal_index = index;
        }
    }

    return medal_index;
};
