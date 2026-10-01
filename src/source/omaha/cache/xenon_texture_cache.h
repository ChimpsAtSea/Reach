#pragma once
#ifndef __XENON_TEXTURE_CACHE_H__
#define __XENON_TEXTURE_CACHE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum e_texture_cache_block_type
{
    _texture_cache_block_type_all = 0,
    _texture_cache_block_type_lightmaps,
    _texture_cache_block_type_screenshot,
};

enum e_texture_cache_allocation
{
    _texture_cache_allocation_fast = 0,
    _texture_cache_allocation_more_reliable,
    _texture_cache_allocation_most_reliable,
    k_texture_cache_allocation_count,
};

/* ---------- definitions */

struct bitmap_data;

struct texture_cache_debug_options_definition
{
    bool display_mipmap_bias; // 0x0
    bool display_cache_graph; // 0x1
    bool display_cache_list; // 0x2
    bool force_low_detail; // 0x3
    bool force_medium_detail; // 0x4
    bool force_high_detail; // 0x5
    bool status; // 0x6
    bool usage; // 0x7
    bool block_warning; // 0x8
    bool lod_bias; // 0x9
    bool dynamic_low_detail_texture; // 0xA
    long display_cache_list_page; // 0xC
};
static_assert(sizeof(texture_cache_debug_options_definition) == 0x10, "texture_cache_debug_options_definition");

/* ---------- prototypes */

void * _texture_cache_bitmap_get_hardware_format(bitmap_data const * bitmap, long flags, float lod_bias);
void texture_cache_debug_render(void);
void texture_cache_open_pregame(void);
void texture_cache_close_pregame(void);
void texture_cache_open(void);
void texture_cache_close(void);
void texture_cache_block_for_one_frame(e_texture_cache_block_type block_type);
void texture_cache_update_for_render(void);
void texture_cache_idle(void);
void texture_cache_enable_game_texture(bool enable);
void texture_cache_flush(void);
bool texture_cache_is_open(void);
void texture_cache_test_malloc(void);
void * texture_cache_malloc(long size, e_texture_cache_allocation allocation_speed, char const * file, long line, void * user_data, void (*idle_proc)(void *, void *), void (*termination_proc)(void *, void *));
void texture_cache_free(void * pointer, char const * file, long line);
bool texture_cache_bitmap_new(long tag_index, bitmap_data * bitmap);
void texture_cache_bitmap_delete(bitmap_data * bitmap);
void texture_cache_bitmap_reset(long tag_index, bitmap_data * bitmap);
void texture_cache_bitmap_downsample(long tag_index, bitmap_data * bitmap);
bool texture_cache_bitmap_permanently_lock(bitmap_data * bitmap);
void texture_cache_report_to_file(void);
bool texture_cache_is_blocking(void);
bool texture_cache_predict(bitmap_data * bitmap);
long texture_cache_get_locked_size(void);

/* ---------- globals */

extern bool debug_texture_cache;
extern texture_cache_debug_options_definition texture_cache_debug_options;

/* ---------- public code */

#endif // __XENON_TEXTURE_CACHE_H__

