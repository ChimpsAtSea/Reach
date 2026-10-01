#pragma once
#ifndef __OBJECT_TYPES_H__
#define __OBJECT_TYPES_H__

/* ---------- headers */

/* ---------- constants */

// masks passed to object_get_and_verify_type (values verified in animated_trick_camera.cpp)
enum
{
    _object_mask_biped = 0x1,
    _object_mask_vehicle = 0x2,
    _object_mask_scenery = 0x40,
    _object_mask_sound_scenery = 0x200,
    _object_mask_giant = 0x1000,
    _object_mask_unit = _object_mask_biped | _object_mask_vehicle | _object_mask_giant,
};

enum
{
    NUMBER_OF_OBJECT_TYPES = 14,
};

/* ---------- definitions */

// Reach order; scenery/sound_scenery/giant consistent with the _object_mask_* bits above
enum e_object_type
{
    _object_type_biped = 0,
    _object_type_vehicle,
    _object_type_weapon,
    _object_type_equipment,
    _object_type_terminal,
    _object_type_projectile,
    _object_type_scenery,
    _object_type_machine,
    _object_type_control,
    _object_type_sound_scenery,
    _object_type_crate,
    _object_type_creature,
    _object_type_giant,
    _object_type_effect_scenery,
};

/* ---------- prototypes */

extern char const * object_type_get_name(e_object_type object_type);

/* ---------- globals */

/* ---------- public code */

#endif // __OBJECT_TYPES_H__

