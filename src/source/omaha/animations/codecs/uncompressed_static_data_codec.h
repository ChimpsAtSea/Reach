#ifndef __UNCOMPRESSED_STATIC_DATA_CODEC_H__
#define __UNCOMPRESSED_STATIC_DATA_CODEC_H__
#pragma once

/* ---------- headers */

#include "omaha\math\real_math.h"

/* ---------- constants */

/* ---------- definitions */

struct s_animation_codec_header;
class c_quantized_quaternion_8byte;

class c_uncompressed_static_data_codec
{
public:
    static void byteswap_animation(s_animation_codec_header *header, long animation_data_size, bool swapping_to_native_endian_format);

private:
    static c_quantized_quaternion_8byte const *get_node_rotation_list(s_animation_codec_header const *header, long node);
    static real_point3d const *get_node_translation_list(s_animation_codec_header const *header, long node);
    static float const *get_node_scale_list(s_animation_codec_header const *header, long node);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __UNCOMPRESSED_STATIC_DATA_CODEC_H__

