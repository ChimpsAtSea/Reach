#ifndef __COMPRESSION_TOOLS_H__
#define __COMPRESSION_TOOLS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\animations\animation_compute_orientations_interface.h"

/* ---------- constants */

/* ---------- definitions */

struct s_fullframe_codec_header :
    public s_animation_codec_header
{
    unsigned long rotation_stride; // 0x14
    unsigned long translation_stride; // 0x18
    unsigned long scale_stride; // 0x1C
};
static_assert(sizeof(s_fullframe_codec_header) == 0x20, "s_fullframe_codec_header");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __COMPRESSION_TOOLS_H__

