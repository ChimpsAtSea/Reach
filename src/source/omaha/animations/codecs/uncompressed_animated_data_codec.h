#pragma once
#ifndef __UNCOMPRESSED_ANIMATED_DATA_CODEC_H__
#define __UNCOMPRESSED_ANIMATED_DATA_CODEC_H__

/* ---------- headers */

#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

struct s_animation_codec_header;

class c_uncompressed_animated_data_codec
{
public:
    static void decompress_rotation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void fast_decompress_rotation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void decompress_translation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void fast_decompress_translation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void decompress_scale(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void fast_decompress_scale(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output);
    static void byteswap_animation(s_animation_codec_header *header, long animation_data_size, bool swapping_to_native_endian_format);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __UNCOMPRESSED_ANIMATED_DATA_CODEC_H__
