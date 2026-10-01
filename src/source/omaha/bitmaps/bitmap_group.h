#pragma once
#ifndef __BITMAP_GROUP_H__
#define __BITMAP_GROUP_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\bitmaps\bitmaps.h"

/* ---------- constants */

/* ---------- definitions */

enum
{
    BITMAP_GROUP_TAG = 'bitm'
};

struct bitmap_group_sequence
{
    char name[32]; // 0x0
    short first_bitmap_index; // 0x20
    short bitmap_count; // 0x22
    long unused[4]; // 0x24
    s_tag_block sprites; // 0x34
};
static_assert(sizeof(bitmap_group_sequence) == 0x40, "bitmap_group_sequence");

struct bitmap_group
{
    long usage; // 0x0
    unsigned short flags; // 0x4
    short sprite_spacing; // 0x6
    float bump_map_height; // 0x8
    float fade_factor; // 0xC
    float blur; // 0x10
    float mipmap_blur; // 0x14
    char curve_mode; // 0x18
    char max_mipmap_level; // 0x19
    short max_resolution; // 0x1A
    unsigned char pad0[2]; // 0x1C
    short force_bitmap_format; // 0x1E
    float tight_bounds_threshold; // 0x20
    s_tag_block usage_override; // 0x24
    s_tag_block manual_sequences; // 0x30
    s_tag_block tight_bounds; // 0x3C
    s_tag_data source_data; // 0x48
    s_tag_data pixel_data; // 0x5C
    s_tag_block sequences; // 0x70
    s_tag_block bitmaps; // 0x7C
    s_tag_data xenon_pixel_data; // 0x88
    s_tag_block xenon_bitmaps; // 0x9C
    s_tag_block hardware_textures; // 0xA8
    s_tag_block interleaved_hardware_textures; // 0xB4
};
static_assert(sizeof(bitmap_group) == 0xC0, "bitmap_group");

class c_rasterizer_texture_ref;

/* ---------- prototypes */

bool bitmap_group_get_bitmap_hardware_format(long bitmap_group_index, long bitmap_index, c_rasterizer_texture_ref * texture_ref);

/* ---------- globals */

/* ---------- public code */

#endif // __BITMAP_GROUP_H__

