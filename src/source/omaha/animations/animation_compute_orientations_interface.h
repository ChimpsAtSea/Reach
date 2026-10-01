#ifndef __ANIMATION_COMPUTE_ORIENTATIONS_INTERFACE_H__
#define __ANIMATION_COMPUTE_ORIENTATIONS_INTERFACE_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_animation_codec_header
{
    unsigned char compression_type;
    unsigned char total_rotated_nodes;
    unsigned char total_translated_nodes;
    unsigned char total_scaled_nodes;
    float error_value;
    float compression_rate;
    unsigned long translation_offset;
    unsigned long scale_offset;
};
static_assert(sizeof(s_animation_codec_header) == 0x14, "s_animation_codec_header");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ANIMATION_COMPUTE_ORIENTATIONS_INTERFACE_H__

