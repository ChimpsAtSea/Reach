#pragma once
#ifndef __XENON_GEOMETRY_CACHE_H__
#define __XENON_GEOMETRY_CACHE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\optional_cache_constants.h"

/* ---------- constants */

enum e_geometry_block_type
{
    _geometry_block_type_all = 0,
    _geometry_block_type_bsp_geometry,
    _geometry_block_type_screenshot,
};

/* ---------- definitions */

struct geometry_block_info;

struct geometry_cache_debug_options_definition
{
    bool display_cache_graph; // 0x0
    bool display_cache_list; // 0x1
    bool status; // 0x2
    bool block_warning; // 0x3
    bool never_block; // 0x4
    bool debug_display; // 0x5
};
static_assert(sizeof(geometry_cache_debug_options_definition) == 0x6, "geometry_cache_debug_options_definition");

/* ---------- prototypes */

void geometry_cache_new(void);
void geometry_cache_delete(void);
void geometry_cache_memory_initialize(e_map_memory_configuration memory_configuration);
void geometry_cache_memory_dispose(void);
void geometry_cache_open(void);
void geometry_cache_close(void);
bool geometry_cache_in_use(void);
void geometry_cache_block_for_one_frame(e_geometry_block_type block_type);
void geometry_cache_update_for_render(void);
void geometry_cache_idle(void);
void geometry_cache_clear_structure_block_pending_count(void);
long geometry_cache_get_structure_block_pending_count(void);
bool _geometry_cache_block_query(geometry_block_info * block_info, long flags);
void geometry_cache_block_new(geometry_block_info * block_info);
void geometry_cache_block_delete(geometry_block_info * block_info);
void geometry_cache_set_blocking(bool blocking);
void geometry_cache_flush(void);
void geometry_cache_flush_tag(long owner_tag_index);
void geometry_cache_get_base_address_and_size(void ** base_address, long * size);
void geometry_cache_debug_render(void);
bool geometry_cache_predict(geometry_block_info * block_info);
bool geometry_cache_is_blocking(void);
long geometry_cache_get_locked_size(void);

/* ---------- globals */

extern geometry_cache_debug_options_definition geometry_cache_debug_options;
extern bool debug_geometry_cache;

/* ---------- public code */

#endif // __XENON_GEOMETRY_CACHE_H__

