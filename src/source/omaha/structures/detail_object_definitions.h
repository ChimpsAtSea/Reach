#pragma once
#ifndef __DETAIL_OBJECT_DEFINITIONS_H__
#define __DETAIL_OBJECT_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\color_math.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    DETAIL_OBJECT_COLLECTION_TAG = 'dobc',
};

enum
{
    MAXIMUM_DETAIL_OBJECT_LAYERS_PER_STRUCTURE = 32,
    MAXIMUM_DETAIL_OBJECT_CELLS_PER_STRUCTURE = 262144,
    MAXIMUM_DETAIL_OBJECTS_PER_STRUCTURE = 2097152,
    MAXIMUM_DETAIL_OBJECTS_PER_CELL = 512,
    MAXIMUM_DETAIL_OBJECT_TYPES_PER_COLLECTION = 16,
    MAXIMUM_DETAIL_OBJECT_SPRITES_PER_TYPE = 16,
    MAXIMUM_DETAIL_OBJECT_SPRITES_PER_COLLECTION = 128,
    MAXIMUM_DETAIL_OBJECT_CELLS_PER_AXIS = 3,
    MAXIMUM_DETAIL_OBJECT_CELLS_PER_FRAME = 27,
    DETAIL_OBJECT_CELL_SIZE = 8,
    DETAIL_OBJECT_CELL_GRANULARITY = 255,
};

/* ---------- definitions */

struct bitmap_group;
struct scenario;

struct detail_object_type_definition
{
    char name[32]; // 0x0
    unsigned char sequence_index; // 0x20
    unsigned char type_flags; // 0x21
    unsigned char first_sprite_index; // 0x22
    unsigned char sprite_count; // 0x23
    real color_override_factor; // 0x24
    unsigned char pad28[8]; // 0x28
    real near_fade_distance; // 0x30
    real far_fade_distance; // 0x34
    real size; // 0x38
    unsigned char pad3C[4]; // 0x3C
    real_rgb_color minimum_color; // 0x40
    real_rgb_color maximum_color; // 0x4C
    unsigned long ambient_color; // 0x58 argb
    unsigned char pad5C[4]; // 0x5C
};
static_assert(sizeof(detail_object_type_definition) == 0x60, "detail_object_type_definition");

struct detail_object_collection_definition
{
    short collection_type; // 0x0
    unsigned char pad2[2]; // 0x2
    real global_z_offset; // 0x4
    unsigned char pad8[44]; // 0x8
    s_tag_reference sprite_plate; // 0x34
    s_tag_block types; // 0x44 detail_object_type_definition
    unsigned char pad50[48]; // 0x50
};
static_assert(sizeof(detail_object_collection_definition) == 0x80, "detail_object_collection_definition");

struct detail_object_cell_definition
{
    short cell_x; // 0x0
    short cell_y; // 0x2
    short cell_z; // 0x4
    short offset_z; // 0x6
    unsigned long valid_layers_flags; // 0x8
    long start_index; // 0xC
    long count_index; // 0x10
    unsigned char pad14[12]; // 0x14
};
static_assert(sizeof(detail_object_cell_definition) == 0x20, "detail_object_cell_definition");

struct detail_object_z_reference_vector
{
    real n[4]; // 0x0
};
static_assert(sizeof(detail_object_z_reference_vector) == 0x10, "detail_object_z_reference_vector");

struct structure_detail_object_data
{
    s_tag_block cells; // 0x0 detail_object_cell_definition
    s_tag_block instances; // 0xC
    s_tag_block counts; // 0x18
    s_tag_block z_reference_vectors; // 0x24 detail_object_z_reference_vector
    unsigned char pad30[4]; // 0x30
};
static_assert(sizeof(structure_detail_object_data) == 0x34, "structure_detail_object_data");

/* ---------- prototypes */

void postprocess_detail_objects(scenario * scenario, structure_detail_object_data * detail_objects);
bool postprocess_detail_object_collection(long tag_index, bool for_editor);
bool postprocess_detail_object_type(bitmap_group * bitmap, detail_object_type_definition * type, char const ** error_string);

/* ---------- globals */

/* ---------- public code */

#endif // __DETAIL_OBJECT_DEFINITIONS_H__

