#pragma once
#ifndef __BITMAPS_H__
#define __BITMAPS_H__

/* ---------- headers */

#include "omaha\math\integer_math.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct bitmap_data
{
    short width; // 0x0
    short height; // 0x2
    char depth; // 0x4
    unsigned char more_flags; // 0x5
    char type; // 0x6
    char four_times_log2_size; // 0x7
    short format; // 0x8
    unsigned char flags; // 0xA
    char exponent_bias; // 0xB
    point2d registration_point; // 0xC
    char mipmap_count_excluding_highest; // 0x10
    char curve; // 0x11
    char interleaved_interop_index; // 0x12
    char interleaved_texture_index; // 0x13
    long pixels_offset; // 0x14
    long pixels_size; // 0x18
    long high_res_pixels_offset; // 0x1C
    long high_res_pixels_size; // 0x20
    long hardware_format; // 0x24
    void * base_address; // 0x28
};
static_assert(sizeof(bitmap_data) == 0x2C, "bitmap_data");

/* ---------- prototypes */

void bitmap_delete(bitmap_data * bitmap);
bool bitmap_verify(bitmap_data const * bitmap, bool import);
void bitmap_rebuild(bitmap_data * bitmap);

/* ---------- globals */

/* ---------- public code */

#endif // __BITMAPS_H__

