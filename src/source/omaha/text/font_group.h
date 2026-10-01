#pragma once
#ifndef __FONT_GROUP_H__
#define __FONT_GROUP_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

long const k_font_character_page_size = 8;
long const k_font_character_page_size_bits = 3;
long const k_font_location_page_index_bits = 21;
long const k_font_location_page_count_bits = 11;
unsigned long const k_font_location_invalid = 0xFFFFFFFF;
long const k_font_character_maximum_pages = 1026;

/* ---------- definitions */

struct s_kerning_pair
{
    unsigned char second_character; // 0x0
    char offset; // 0x1
};
static_assert(sizeof(s_kerning_pair) == 0x2, "s_kerning_pair");

struct s_font_character
{
    short character_width; // 0x0
    unsigned short packed_size; // 0x2
    short bitmap_width; // 0x4
    short bitmap_height; // 0x6
    short initial_offset; // 0x8
    short bitmap_origin_y; // 0xA
};
static_assert(sizeof(s_font_character) == 0xC, "s_font_character");

struct s_font_header
{
    long version; // 0x0
    char debug_name[32]; // 0x4
    short ascending_height; // 0x24
    short descending_height; // 0x26
    short leading_height; // 0x28
    short leading_width; // 0x2A
    long kerning_pairs_offset; // 0x2C
    long kerning_pair_count; // 0x30
    unsigned char character_first_kerning_pair_index[256]; // 0x34
    long location_table_offset; // 0x134
    long location_table_count; // 0x138
    long character_count; // 0x13C
    long character_data_offset; // 0x140
    long character_data_size_bytes; // 0x144
    unsigned long no_such_character_data_location; // 0x148
    long maximum_packed_pixel_size_bytes; // 0x14C
    long maximum_unpacked_pixel_size_bytes; // 0x150
    long total_packed_pixel_size_bytes; // 0x154
    long total_unpacked_pixel_size_bytes; // 0x158
};
static_assert(sizeof(s_font_header) == 0x15C, "s_font_header");

/* ---------- prototypes */

extern void font_header_byteswap(s_font_header* header);
extern void font_kerning_pairs_byteswap(s_kerning_pair* kerning_pairs, long kerning_pair_count);
extern void font_character_byteswap(s_font_character* character);
extern bool font_header_validate(s_font_header const* header);
extern bool font_character_validate(s_font_character const* character);

/* ---------- globals */

/* ---------- public code */

#endif // __FONT_GROUP_H__

