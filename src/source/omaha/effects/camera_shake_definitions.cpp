/* ---------- headers */

#include "omaha\effects\camera_shake_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern real fabs(real x);

/* ---------- globals */

c_tag_struct_vtable<c_camera_shake_struct_vtable> camera_shake_struct_struct_vtable;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition global_camera_impulse_block_struct_definition; // "?global_camera_impulse_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_camera_impulse_block; // "?global_camera_impulse_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition camera_shake_block; // "?camera_shake_block@@3Us_tag_block_definition@@A"
// struct s_tag_group camera_shake_group; // "?camera_shake_group@@3Us_tag_group@@A"
// struct s_tag_reference_definition global_camera_shake_reference; // "?global_camera_shake_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group_legacy_vtable legacy_camera_shake_vtable; // "?legacy_camera_shake_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_camera_shake_stream_definition; // "?legacy_camera_shake_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_camera_shake_xsync_declaration; // "?legacy_camera_shake_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_tag_struct_vtable<class c_camera_shake_struct_vtable> camera_shake_struct_struct_vtable; // "?camera_shake_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_camera_shake_struct_vtable@@@@A"
// class c_legacy_tag_group_vtable_shim legacy_camera_shake_vtable_shim; // "?legacy_camera_shake_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool camera_impulse_globals_on_new_proc(void *);
// public: c_tag_struct_vtable<class c_camera_shake_struct_vtable>::c_tag_struct_vtable<class c_camera_shake_struct_vtable>(void);
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_byte_swap_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_camera_shake_struct_vtable>::byte_swap_block_proc(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_postprocess_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::postprocess_thunk(long, void *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_format_proc(void) const;
// public: virtual char * c_tag_struct_vtable<class c_camera_shake_struct_vtable>::format_thunk(long, __int64, struct s_tag_block *, long, char *, long) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_on_delete_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_camera_shake_struct_vtable>::on_delete_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_on_new_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::on_new_thunk(void *) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_on_copy_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::on_copy_thunk(void const *, void *) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_write_to_cache_file_proc(void) const;
// public: virtual void c_tag_struct_vtable<class c_camera_shake_struct_vtable>::write_to_cache_file_thunk(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_block_does_not_exist_in_cache_file_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::block_does_not_exist_in_cache_file_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_fixup_old_struct_definition(void) const;
// public: virtual struct s_tag_struct_definition * c_tag_struct_vtable<class c_camera_shake_struct_vtable>::get_fixup_source_definition_thunk(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_fixup_old_struct_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::fixup_old_struct_thunk(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::has_fixup_old_struct_from_disk_proc(void) const;
// public: virtual bool c_tag_struct_vtable<class c_camera_shake_struct_vtable>::fixup_old_struct_from_disk_thunk(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool) const;
// public: static void s_tag_vtable_has_byte_swap_proc<class c_camera_shake_struct_vtable>::call(void *);
// public: static bool s_tag_vtable_has_postprocess_proc<class c_camera_shake_struct_vtable>::call(long, void *, bool);
// public: static bool c_camera_shake_struct_vtable::postprocess_proc(long, void *, bool);
// public: static char * s_tag_vtable_has_format_proc<class c_camera_shake_struct_vtable>::call(long, __int64, struct s_tag_block *, long, char *, long);
// public: static void s_tag_vtable_has_on_delete_proc<class c_camera_shake_struct_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_new_proc<class c_camera_shake_struct_vtable>::call(void *);
// public: static bool s_tag_vtable_has_on_copy_proc<class c_camera_shake_struct_vtable>::call(void const *, void *);
// public: static void s_tag_vtable_has_write_to_cache_file_proc<class c_camera_shake_struct_vtable>::call(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);
// public: static bool s_tag_vtable_has_block_does_not_exist_in_cache_file<class c_camera_shake_struct_vtable>::call(void);
// public: static struct s_tag_struct_definition * s_tag_vtable_has_get_fixup_source_definition_proc<class c_camera_shake_struct_vtable>::call(void);
// public: static bool s_tag_vtable_has_fixup_old_struct_proc<class c_camera_shake_struct_vtable>::call(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: static bool s_tag_vtable_has_fixup_old_struct_from_disk_proc<class c_camera_shake_struct_vtable>::call(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);

bool camera_impulse_globals_on_new_proc(void * data)
{
    mangled_ppc("?camera_impulse_globals_on_new_proc@@YA_NPAX@Z");

    s_camera_impulse_globals * camera_impulse_globals = static_cast<s_camera_impulse_globals *>(data);
    c_function_definition_editor editor(&camera_impulse_globals->mapping);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    editor.set_function_type(c_function_definition::_function_type_constant);
    editor.calc_default_values();
    editor.set_clamp_range_min(1.0f);
    editor.set_clamp_range_max(1.0f);

    return true;
};

bool c_camera_shake_struct_vtable::postprocess_proc(long tag_index, void * data, bool for_editor)
{
    mangled_ppc("?postprocess_proc@c_camera_shake_struct_vtable@@SA_NJPAX_N@Z");

    if (!for_editor)
    {
        s_camera_shake * camera_shake = static_cast<s_camera_shake *>(data);
        if (realcmp(camera_shake->wobble_function_period, 0.0f))
        {
            camera_shake->wobble_function_period = 1.0f;
        }
    }

    return true;
};

