#pragma once
#ifndef __BIPED_DEFINITIONS_H__
#define __BIPED_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\physics\character_physics_definitions.h"
#include "omaha\units\unit_definitions.h"

/* ---------- constants */

enum
{
    BIPED_DEFINITION_TAG = 'bipd',
};

/* ---------- definitions */

// $TODO: only physics is reversed; layout from biped_group$2 (haloreach_tagtest_x360.json, 1992 bytes total, biped part follows the unit struct)
struct _biped_definition
{
    unsigned char unknown0[0x110]; // 0x0 (0x518 in biped_definition)
    s_character_physics_definition physics; // 0x110 (object_get_default_material reads 0x644/0x646 of biped_definition)
    unsigned char unknown1C8[0x2B0 - 0x1C8]; // 0x1C8
};
static_assert(sizeof(_biped_definition) == 0x2B0, "_biped_definition");

struct biped_definition
{
    _unit_definition unit; // 0x0
    _biped_definition biped; // 0x518
};
static_assert(sizeof(biped_definition) == 0x7C8, "biped_definition");

/* ---------- prototypes */

void biped_definition_fixup(long biped_definition_index);
void biped_definition_teardown(long biped_definition_index);

/* ---------- globals */

/* ---------- public code */

#endif // __BIPED_DEFINITIONS_H__

