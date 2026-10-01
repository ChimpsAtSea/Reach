/* ---------- headers */

#include "omaha\animations\codecs\uncompressed_static_data_codec.h"
#include "omaha\animations\animation_compute_orientations_interface.h"
#include "omaha\animations\codecs\quantized_data_types.h"
#include "omaha\memory\byte_swapping.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static void c_uncompressed_static_data_codec::byteswap_animation(struct s_animation_codec_header *, long, bool);

void c_uncompressed_static_data_codec::byteswap_animation(s_animation_codec_header *header, long animation_data_size, bool swapping_to_native_endian_format)
{
    mangled_ppc("?byteswap_animation@c_uncompressed_static_data_codec@@SAXPAUs_animation_codec_header@@J_N@Z");

    if (swapping_to_native_endian_format)
    {
        byte_swap_type(header, 1);
    }

    if (header->total_rotated_nodes)
    {
        byte_swap_type(const_cast<c_quantized_quaternion_8byte *>(get_node_rotation_list(header, 0)), header->total_rotated_nodes);
    }

    if (header->total_translated_nodes)
    {
        byte_swap_type(const_cast<real_point3d *>(get_node_translation_list(header, 0)), header->total_translated_nodes);
    }

    if (header->total_scaled_nodes)
    {
        byte_swap_type(const_cast<float *>(get_node_scale_list(header, 0)), header->total_scaled_nodes);
    }

    if (!swapping_to_native_endian_format)
    {
        byte_swap_type(header, 1);
    }
};

