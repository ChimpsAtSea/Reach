#pragma once
#ifndef __EDIT_TEXT_H__
#define __EDIT_TEXT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct key_stroke;

struct edit_text
{
    char * buffer; // 0x0
    short maximum_length; // 0x4
    short insertion_point_index; // 0x6
    short selection_start_index; // 0x8
};
static_assert(sizeof(edit_text) == 0xC, "edit_text");

/* ---------- prototypes */

void edit_text_new(edit_text * edit);
void edit_text_handle_key(edit_text * edit, key_stroke const * key);
void edit_text_selection_reset(edit_text * edit);
unsigned char edit_text_get_selection_indices(edit_text * edit, short * start_index, short * end_index);

/* ---------- globals */

/* ---------- public code */

#endif // __EDIT_TEXT_H__

