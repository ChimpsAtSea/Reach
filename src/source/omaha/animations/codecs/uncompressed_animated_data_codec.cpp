#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\animations\\codecs\\uncompressed_animated_data_codec.cpp"
/* ---------- headers */

#include "omaha\animations\codecs\uncompressed_animated_data_codec.h"
#include "omaha\animations\animation_compute_orientations_interface.h"
#include "omaha\animations\codecs\compression_tools.h"
#include "omaha\animations\curve_codec\curve_codec.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\byte_swapping.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

static real32_quaternion const *get_node_rotation_list(s_animation_codec_header const *header, long node);
static real_point3d const *get_node_translation_list(s_animation_codec_header const *header, long node);
static float const *get_node_scale_list(s_animation_codec_header const *header, long node);

template<> void byte_swap_type<real32_quaternion>(real32_quaternion *data, long count);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static void c_uncompressed_animated_data_codec::decompress_rotation(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// struct real32_quaternion const * get_node_rotation_list(struct s_animation_codec_header const *, long);
// public: static void c_uncompressed_animated_data_codec::fast_decompress_rotation(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// public: static void c_uncompressed_animated_data_codec::decompress_translation(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// union real_point3d const * get_node_translation_list(struct s_animation_codec_header const *, long);
// public: static void c_uncompressed_animated_data_codec::fast_decompress_translation(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// public: static void c_uncompressed_animated_data_codec::decompress_scale(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// float const * get_node_scale_list(struct s_animation_codec_header const *, long);
// public: static void c_uncompressed_animated_data_codec::fast_decompress_scale(unsigned int *, struct s_animation_codec_header &volatile, long, long, long, float, float, unsigned int *, struct real_orientation &);
// public: static void c_uncompressed_animated_data_codec::byteswap_animation(struct s_animation_codec_header *, long, bool);
// void byte_swap_type<struct real32_quaternion>(struct real32_quaternion *, long);

void c_uncompressed_animated_data_codec::decompress_rotation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?decompress_rotation@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(53, VALID_INDEX(node_index, data_header->total_rotated_nodes));

    real32_quaternion const *rotation_list = get_node_rotation_list(data_header, node_index);
    output->rotation = rotation_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(56, valid_real_quaternion(&output->rotation));
    }
};

static real32_quaternion const *get_node_rotation_list(s_animation_codec_header const *header, long node)
{
    mangled_ppc("?get_node_rotation_list@@YAPBUreal32_quaternion@@PBUs_animation_codec_header@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(18, VALID_INDEX(node, header->total_rotated_nodes));

    s_fullframe_codec_header const *local_header = static_cast<s_fullframe_codec_header const *>(header);
    return reinterpret_cast<real32_quaternion const *>(reinterpret_cast<char const *>(local_header + 1) + node * local_header->rotation_stride);
};

void c_uncompressed_animated_data_codec::fast_decompress_rotation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?fast_decompress_rotation@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(68, VALID_INDEX(node_index, data_header->total_rotated_nodes));

    real32_quaternion const *rotation_list = get_node_rotation_list(data_header, node_index);
    output->rotation = rotation_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(71, valid_real_quaternion(&output->rotation));
    }
};

void c_uncompressed_animated_data_codec::decompress_translation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?decompress_translation@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(83, VALID_INDEX(node_index, data_header->total_translated_nodes));

    real_point3d const *translation_list = get_node_translation_list(data_header, node_index);
    output->translation = translation_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(86, valid_real_point3d(&output->translation));
    }
};

static real_point3d const *get_node_translation_list(s_animation_codec_header const *header, long node)
{
    mangled_ppc("?get_node_translation_list@@YAPBTreal_point3d@@PBUs_animation_codec_header@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(27, VALID_INDEX(node, header->total_translated_nodes));

    s_fullframe_codec_header const *local_header = static_cast<s_fullframe_codec_header const *>(header);
    return reinterpret_cast<real_point3d const *>(reinterpret_cast<char const *>(local_header) + local_header->translation_offset + node * local_header->translation_stride);
};

void c_uncompressed_animated_data_codec::fast_decompress_translation(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?fast_decompress_translation@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(98, VALID_INDEX(node_index, data_header->total_translated_nodes));

    real_point3d const *translation_list = get_node_translation_list(data_header, node_index);
    output->translation = translation_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(101, valid_real_point3d(&output->translation));
    }
};

void c_uncompressed_animated_data_codec::decompress_scale(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?decompress_scale@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(113, VALID_INDEX(node_index, data_header->total_scaled_nodes));

    float const *scale_list = get_node_scale_list(data_header, node_index);
    output->scale = scale_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(116, valid_real(output->scale));
    }
};

static float const *get_node_scale_list(s_animation_codec_header const *header, long node)
{
    mangled_ppc("?get_node_scale_list@@YAPBMPBUs_animation_codec_header@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(36, VALID_INDEX(node, header->total_scaled_nodes));

    s_fullframe_codec_header const *local_header = static_cast<s_fullframe_codec_header const *>(header);
    return reinterpret_cast<float const *>(reinterpret_cast<char const *>(local_header) + local_header->scale_offset + node * local_header->scale_stride);
};

void c_uncompressed_animated_data_codec::fast_decompress_scale(s_animation_codec_header const *__restrict data_header, long node_index, long frame_index_a, long frame_index_b, float blend_t, float blend_v, real_orientation *__restrict output)
{
    mangled_ppc("?fast_decompress_scale@c_uncompressed_animated_data_codec@@SAXPIBUs_animation_codec_header@@JJJMMPIAUreal_orientation@@@Z");

    assert_tag_debug_untracked_jul_11_2011(128, VALID_INDEX(node_index, data_header->total_scaled_nodes));

    float const *scale_list = get_node_scale_list(data_header, node_index);
    output->scale = scale_list[frame_index_a];

    if (is_debug_animation_solving_enabled())
    {
        assert_tag_debug_untracked_jul_11_2011(131, valid_real(output->scale));
    }
};

void c_uncompressed_animated_data_codec::byteswap_animation(s_animation_codec_header *header, long animation_data_size, bool swapping_to_native_endian_format)
{
    mangled_ppc("?byteswap_animation@c_uncompressed_animated_data_codec@@SAXPAUs_animation_codec_header@@J_N@Z");

    typedef real32_quaternion R;
    typedef real_point3d T;
    typedef float S;

    s_fullframe_codec_header *actual_header = static_cast<s_fullframe_codec_header *>(header);

    if (swapping_to_native_endian_format)
    {
        byte_swap_type(actual_header, 1);
    }

    assert_tag_debug_untracked_jul_11_2011(152, actual_header->rotation_stride%sizeof(R)==0);
    assert_tag_debug_untracked_jul_11_2011(153, actual_header->translation_stride%sizeof(T)==0);
    assert_tag_debug_untracked_jul_11_2011(154, actual_header->scale_stride%sizeof(S)==0);

    long rotation_count = actual_header->rotation_stride / sizeof(R) * header->total_rotated_nodes;
    long translation_count = actual_header->translation_stride / sizeof(T) * header->total_translated_nodes;
    long scale_count = actual_header->scale_stride / sizeof(S) * header->total_scaled_nodes;

    if (rotation_count)
    {
        byte_swap_type(const_cast<R *>(get_node_rotation_list(header, 0)), rotation_count);
    }

    if (translation_count)
    {
        byte_swap_type(const_cast<T *>(get_node_translation_list(header, 0)), translation_count);
    }

    if (scale_count)
    {
        byte_swap_type(const_cast<S *>(get_node_scale_list(header, 0)), scale_count);
    }

    if (!swapping_to_native_endian_format)
    {
        byte_swap_type(actual_header, 1);
    }
};

template<> void byte_swap_type<real32_quaternion>(real32_quaternion *data, long count)
{
    mangled_ppc("??$byte_swap_type@Ureal32_quaternion@@@@YAXPAUreal32_quaternion@@J@Z");

    byte_swap_data(c_byte_swap_traits<real32_quaternion>::g_bs_definition, data, count);
};
