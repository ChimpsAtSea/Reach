#pragma once
#ifndef __PLAYER_COOKIE_PURCHASE_DEFINITIONS_H__
#define __PLAYER_COOKIE_PURCHASE_DEFINITIONS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

// cookie_purchase_definition_block
struct s_cookie_purchase_definition
{
    long purchase_id; // 0x0 string_id
    long display_name; // 0x4 string_id
    long display_description; // 0x8 string_id
    unsigned char flags; // 0xC
    char pad1[0x3]; // 0xD
    s_tag_reference display_bitmap; // 0x10
    long sprite_index; // 0x20
    long cookie_cost; // 0x24
    char unknown28[0x94]; // 0x28 $TODO: purchase player appearance, visible/purchasable prerequisites
};
static_assert(sizeof(s_cookie_purchase_definition) == 0xBC, "s_cookie_purchase_definition");

/* ---------- prototypes */

long cookie_purchase_get_global_item_count();
unsigned long cookie_purchase_definition_generate_checksum();
s_cookie_purchase_definition const * cookie_purchase_global_item_get_definition(long item_index);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_COOKIE_PURCHASE_DEFINITIONS_H__

