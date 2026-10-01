#pragma once
#ifndef __MATERIALS_DEFINITIONS_H__
#define __MATERIALS_DEFINITIONS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\game\materials.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

// names from the Reach global_material_flags_definition string list
enum e_global_material_bit
{
    _global_material_flammable_bit = 0,
    _global_material_biomass_bit,
    _global_material_rad_xfer_interior_bit,
    _global_material_used_directly_bit,
    _global_material_used_by_children_bit,

    k_global_material_bit_count
};

/* ---------- definitions */

struct s_global_material_underwater_proxy
{
    long underwater_material; // 0x0
    long proxy_material; // 0x4
    c_global_material_type underwater_material_type; // 0x8
    c_global_material_type proxy_material_type; // 0xA
};
static_assert(sizeof(s_global_material_underwater_proxy) == 0xC, "s_global_material_underwater_proxy");

struct s_global_material_wet_proxy
{
    long wet_material; // 0x0
    short runtime_proxy_material_index; // 0x4
    unsigned char pad6[2]; // 0x6
};
static_assert(sizeof(s_global_material_wet_proxy) == 0x8, "s_global_material_wet_proxy");

// $TODO: split of the 8 pad bytes between "pad default" and "pad none" unverified
struct s_material_physics_properties
{
    long flags; // 0x0
    real friction; // 0x4
    real restitution; // 0x8
    real density; // 0xC
    s_tag_reference water_physics_drag_properties; // 0x10
    s_tag_block drag_overrides; // 0x20
    unsigned char pad2C[4]; // 0x2C
    real super_floater; // 0x30
    real floater; // 0x34
    real neutral; // 0x38
    real sinker; // 0x3C
    real super_sinker; // 0x40
    unsigned char pad44[4]; // 0x44
};
static_assert(sizeof(s_material_physics_properties) == 0x48, "s_material_physics_properties");

struct s_global_material_sweeteners_definition
{
    s_tag_reference sound_sweetener_small; // 0x0
    s_tag_reference sound_sweetener_medium; // 0x10
    s_tag_reference sound_sweetener_large; // 0x20
    s_tag_reference sound_sweetener_rolling; // 0x30
    s_tag_reference sound_sweetener_grinding; // 0x40
    s_tag_reference sound_sweetener_melee_small; // 0x50
    s_tag_reference sound_sweetener_melee; // 0x60
    s_tag_reference sound_sweetener_melee_large; // 0x70
    s_tag_reference effect_sweetener_small; // 0x80
    s_tag_reference effect_sweetener_medium; // 0x90
    s_tag_reference effect_sweetener_large; // 0xA0
    s_tag_reference effect_sweetener_rolling; // 0xB0
    s_tag_reference effect_sweetener_grinding; // 0xC0
    s_tag_reference effect_sweetener_melee; // 0xD0
    s_tag_reference water_ripple_small; // 0xE0
    s_tag_reference water_ripple_medium; // 0xF0
    s_tag_reference water_ripple_large; // 0x100
    unsigned long sweetener_inheritance_flags; // 0x110
};
static_assert(sizeof(s_global_material_sweeteners_definition) == 0x114, "s_global_material_sweeteners_definition");

struct s_global_material_definition
{
    long name; // 0x0
    long parent_name; // 0x4
    c_global_material_type runtime_material_index; // 0x8 (parent material type: global_material_is_family walks it)
    c_flags<e_global_material_bit, unsigned short, k_global_material_bit_count> flags; // 0xA
    long general_armor; // 0xC
    long specific_armor; // 0x10
    s_global_material_wet_proxy wet_proxies; // 0x14
    short runtime_dry_base_material_index; // 0x1C
    unsigned char pad1E[2]; // 0x1E
    s_material_physics_properties physics_properties; // 0x20
    s_tag_reference breakable_surface; // 0x68
    s_global_material_sweeteners_definition sweeteners; // 0x78
    s_tag_reference material_effects; // 0x18C
    s_tag_block underwater_proxies; // 0x19C
};
static_assert(sizeof(s_global_material_definition) == 0x1A8, "s_global_material_definition");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MATERIALS_DEFINITIONS_H__

