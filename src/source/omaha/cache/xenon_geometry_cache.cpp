#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\xenon_geometry_cache.cpp"
/* ---------- headers */

#include "omaha\cache\xenon_geometry_cache.h"
#include "omaha\geometry\geometry_definitions_new.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

geometry_cache_debug_options_definition geometry_cache_debug_options;
bool debug_geometry_cache;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct geometry_cache_debug_options_definition geometry_cache_debug_options; // "?geometry_cache_debug_options@@3Ugeometry_cache_debug_options_definition@@A"
// bool debug_geometry_cache; // "?debug_geometry_cache@@3_NA"

// void geometry_cache_new(void);
// void geometry_cache_delete(void);
// void geometry_cache_memory_initialize(enum e_map_memory_configuration);
// void geometry_cache_memory_dispose(void);
// void geometry_cache_open(void);
// void geometry_cache_close(void);
// bool geometry_cache_in_use(void);
// void geometry_cache_block_for_one_frame(enum e_geometry_block_type);
// void geometry_cache_update_for_render(void);
// void geometry_cache_idle(void);
// void geometry_cache_clear_structure_block_pending_count(void);
// long geometry_cache_get_structure_block_pending_count(void);
// bool _geometry_cache_block_query(struct geometry_block_info *, long);
// void geometry_cache_block_new(struct geometry_block_info *);
// void geometry_cache_block_delete(struct geometry_block_info *);
// void geometry_cache_set_blocking(bool);
// void geometry_cache_flush(void);
// void geometry_cache_flush_tag(long);
// void geometry_cache_get_base_address_and_size(void **, long *);
// void geometry_cache_debug_render(void);
// bool geometry_cache_predict(struct geometry_block_info *);
// bool geometry_cache_is_blocking(void);
// long geometry_cache_get_locked_size(void);

void geometry_cache_new(void)
{
    mangled_ppc("?geometry_cache_new\\YAXXZ");
};

void geometry_cache_delete(void)
{
    mangled_ppc("?geometry_cache_delete\\YAXXZ");
};

void geometry_cache_memory_initialize(e_map_memory_configuration memory_configuration)
{
    mangled_ppc("?geometry_cache_memory_initialize\\YAXW4e_map_memory_configuration\\\Z");
};

void geometry_cache_memory_dispose(void)
{
    mangled_ppc("?geometry_cache_memory_dispose\\YAXXZ");
};

void geometry_cache_open(void)
{
    mangled_ppc("?geometry_cache_open\\YAXXZ");
};

void geometry_cache_close(void)
{
    mangled_ppc("?geometry_cache_close\\YAXXZ");
};

bool geometry_cache_in_use(void)
{
    mangled_ppc("?geometry_cache_in_use\\YA_NXZ");

    return false;
};

void geometry_cache_block_for_one_frame(e_geometry_block_type block_type)
{
    mangled_ppc("?geometry_cache_block_for_one_frame\\YAXW4e_geometry_block_type\\\Z");
};

void geometry_cache_update_for_render(void)
{
    mangled_ppc("?geometry_cache_update_for_render\\YAXXZ");
};

void geometry_cache_idle(void)
{
    mangled_ppc("?geometry_cache_idle\\YAXXZ");
};

void geometry_cache_clear_structure_block_pending_count(void)
{
    mangled_ppc("?geometry_cache_clear_structure_block_pending_count\\YAXXZ");
};

long geometry_cache_get_structure_block_pending_count(void)
{
    mangled_ppc("?geometry_cache_get_structure_block_pending_count\\YAJXZ");

    return 0;
};

bool _geometry_cache_block_query(geometry_block_info * block_info, long flags)
{
    mangled_ppc("?_geometry_cache_block_query\\YA_NPAUgeometry_block_info\\J\Z");

    return false;
};

void geometry_cache_block_new(geometry_block_info * block_info)
{
    mangled_ppc("?geometry_cache_block_new\\YAXPAUgeometry_block_info\\\Z");

    assert_tag_debug_untracked_jul_11_2011(110, block_info);

    block_info->runtime_cache_block_index = NONE;
};

void geometry_cache_block_delete(geometry_block_info * block_info)
{
    mangled_ppc("?geometry_cache_block_delete\\YAXPAUgeometry_block_info\\\Z");

    assert_tag_debug_untracked_jul_11_2011(121, block_info);

    block_info->runtime_cache_block_index = NONE;
};

void geometry_cache_set_blocking(bool blocking)
{
    mangled_ppc("?geometry_cache_set_blocking\\YAX_N\Z");
};

void geometry_cache_flush(void)
{
    mangled_ppc("?geometry_cache_flush\\YAXXZ");
};

void geometry_cache_flush_tag(long owner_tag_index)
{
    mangled_ppc("?geometry_cache_flush_tag\\YAXJ\Z");
};

void geometry_cache_get_base_address_and_size(void ** base_address, long * size)
{
    mangled_ppc("?geometry_cache_get_base_address_and_size\\YAXPAPAXPAJ\Z");
};

void geometry_cache_debug_render(void)
{
    mangled_ppc("?geometry_cache_debug_render\\YAXXZ");
};

bool geometry_cache_predict(geometry_block_info * block_info)
{
    mangled_ppc("?geometry_cache_predict\\YA_NPAUgeometry_block_info\\\Z");

    return true;
};

bool geometry_cache_is_blocking(void)
{
    mangled_ppc("?geometry_cache_is_blocking\\YA_NXZ");

    return false;
};

long geometry_cache_get_locked_size(void)
{
    mangled_ppc("?geometry_cache_get_locked_size\\YAJXZ");

    return 0;
};
