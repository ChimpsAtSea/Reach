#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\xenon_texture_cache.cpp"
/* ---------- headers */

#include "omaha\cache\xenon_texture_cache.h"
#include "omaha\bitmaps\bitmaps.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool debug_texture_cache;
texture_cache_debug_options_definition texture_cache_debug_options;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool debug_texture_cache; // "?debug_texture_cache@@3_NA"
// struct texture_cache_debug_options_definition texture_cache_debug_options; // "?texture_cache_debug_options@@3Utexture_cache_debug_options_definition@@A"

// void * _texture_cache_bitmap_get_hardware_format(struct bitmap_data const *, long, float);
// void texture_cache_debug_render(void);
// void texture_cache_open_pregame(void);
// void texture_cache_close_pregame(void);
// void texture_cache_open(void);
// void texture_cache_close(void);
// void texture_cache_block_for_one_frame(enum e_texture_cache_block_type);
// void texture_cache_update_for_render(void);
// void texture_cache_idle(void);
// void texture_cache_enable_game_texture(bool);
// void texture_cache_flush(void);
// bool texture_cache_is_open(void);
// void texture_cache_test_malloc(void);
// void * texture_cache_malloc(long, enum e_texture_cache_allocation, char const *, long, void *, void (*)(void *, void *), void (*)(void *, void *));
// void texture_cache_free(void *, char const *, long);
// bool texture_cache_bitmap_new(long, struct bitmap_data *);
// void texture_cache_bitmap_delete(struct bitmap_data *);
// void texture_cache_bitmap_reset(long, struct bitmap_data *);
// void texture_cache_bitmap_downsample(long, struct bitmap_data *);
// bool texture_cache_bitmap_permanently_lock(struct bitmap_data *);
// void texture_cache_report_to_file(void);
// bool texture_cache_is_blocking(void);
// bool texture_cache_predict(struct bitmap_data *);
// long texture_cache_get_locked_size(void);

void * _texture_cache_bitmap_get_hardware_format(bitmap_data const * bitmap, long flags, float lod_bias)
{
    mangled_ppc("?_texture_cache_bitmap_get_hardware_format@@YAPAXPBUbitmap_data@@JM@Z");

    assert_tag_debug_untracked_jul_11_2011(27, bitmap);

    return NULL;
};

void texture_cache_debug_render(void)
{
    mangled_ppc("?texture_cache_debug_render@@YAXXZ");
};

void texture_cache_open_pregame(void)
{
    mangled_ppc("?texture_cache_open_pregame@@YAXXZ");
};

void texture_cache_close_pregame(void)
{
    mangled_ppc("?texture_cache_close_pregame@@YAXXZ");
};

void texture_cache_open(void)
{
    mangled_ppc("?texture_cache_open@@YAXXZ");
};

void texture_cache_close(void)
{
    mangled_ppc("?texture_cache_close@@YAXXZ");
};

void texture_cache_block_for_one_frame(e_texture_cache_block_type block_type)
{
    mangled_ppc("?texture_cache_block_for_one_frame@@YAXW4e_texture_cache_block_type@@@Z");
};

void texture_cache_update_for_render(void)
{
    mangled_ppc("?texture_cache_update_for_render@@YAXXZ");
};

void texture_cache_idle(void)
{
    mangled_ppc("?texture_cache_idle@@YAXXZ");
};

void texture_cache_enable_game_texture(bool enable)
{
    mangled_ppc("?texture_cache_enable_game_texture@@YAX_N@Z");
};

void texture_cache_flush(void)
{
    mangled_ppc("?texture_cache_flush@@YAXXZ");
};

bool texture_cache_is_open(void)
{
    mangled_ppc("?texture_cache_is_open@@YA_NXZ");

    return true;
};

void texture_cache_test_malloc(void)
{
    mangled_ppc("?texture_cache_test_malloc@@YAXXZ");
};

void * texture_cache_malloc(long size, e_texture_cache_allocation allocation_speed, char const * file, long line, void * user_data, void (*idle_proc)(void *, void *), void (*termination_proc)(void *, void *))
{
    mangled_ppc("?texture_cache_malloc@@YAPAXJW4e_texture_cache_allocation@@PBDJPAXP6AX22@Z3@Z");

    void * result = NULL;

    return result;
};

void texture_cache_free(void * pointer, char const * file, long line)
{
    mangled_ppc("?texture_cache_free@@YAXPAXPBDJ@Z");

    debug_free(pointer, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 128);
};

bool texture_cache_bitmap_new(long tag_index, bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_bitmap_new@@YA_NJPAUbitmap_data@@@Z");

    assert_tag_debug_untracked_jul_11_2011(138, bitmap->base_address);

    bitmap_rebuild(bitmap);

    return true;
};

void texture_cache_bitmap_delete(bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_bitmap_delete@@YAXPAUbitmap_data@@@Z");
};

void texture_cache_bitmap_reset(long tag_index, bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_bitmap_reset@@YAXJPAUbitmap_data@@@Z");
};

void texture_cache_bitmap_downsample(long tag_index, bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_bitmap_downsample@@YAXJPAUbitmap_data@@@Z");
};

bool texture_cache_bitmap_permanently_lock(bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_bitmap_permanently_lock@@YA_NPAUbitmap_data@@@Z");

    bool result = true;

    return result;
};

void texture_cache_report_to_file(void)
{
    mangled_ppc("?texture_cache_report_to_file@@YAXXZ");
};

bool texture_cache_is_blocking(void)
{
    mangled_ppc("?texture_cache_is_blocking@@YA_NXZ");

    return false;
};

bool texture_cache_predict(bitmap_data * bitmap)
{
    mangled_ppc("?texture_cache_predict@@YA_NPAUbitmap_data@@@Z");

    return true;
};

long texture_cache_get_locked_size(void)
{
    mangled_ppc("?texture_cache_get_locked_size@@YAJXZ");

    return 0;
};

