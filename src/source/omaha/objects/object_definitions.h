#pragma once
#ifndef __OBJECT_DEFINITIONS_H__
#define __OBJECT_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    OBJECT_TAG = 'obje',
};

/* ---------- definitions */

// Reach layout from global_object_attachment_block (tag json), size 0x20
struct object_attachment_definition
{
    s_tag_reference type; // 0x0
    long marker; // 0x10
    char change_color; // 0x14
    unsigned char flags; // 0x15
    unsigned char pad16[2]; // 0x16
    long primary_scale; // 0x18
    long secondary_scale; // 0x1C
};
static_assert(sizeof(object_attachment_definition) == 0x20, "object_attachment_definition");

// $TODO: only the leading fields are reversed; layout from object_struct_definition (tag json), size 0x178
struct _object_definition
{
    short runtime_object_type; // 0x0
    unsigned char pad0[2]; // 0x2
    unsigned long flags; // 0x4
    real bounding_radius; // 0x8
    real_point3d bounding_offset; // 0xC
    real horizontal_acceleration_scale; // 0x18
    real vertical_acceleration_scale; // 0x1C
    real angular_acceleration_scale; // 0x20
    unsigned char unknown24[0x64 - 0x24]; // 0x24
    s_tag_reference model; // 0x64
    unsigned char unknown74[0x108 - 0x74]; // 0x74
    s_tag_block attachments; // 0x108 object_attachment_definition (postprocess_sound_scenery_definition)
    s_tag_block hull_surfaces; // 0x114
    s_tag_block jetwash; // 0x120 s_jetwash_definition (jetwash_emitter_should_pulse)
    unsigned char unknown12C[0x150 - 0x12C]; // 0x12C
    s_tag_block multiplayer_object; // 0x150
    unsigned char unknown15C[0x178 - 0x15C]; // 0x15C
};
static_assert(sizeof(_object_definition) == 0x178, "_object_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __OBJECT_DEFINITIONS_H__

