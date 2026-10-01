#pragma once
#ifndef __FONT_FALLBACK_H__
#define __FONT_FALLBACK_H__

/* ---------- headers */

#include "omaha\text\unicode.h"

/* ---------- constants */

/* ---------- definitions */

struct s_font_header;
struct s_font_character;

/* ---------- prototypes */

extern void fallback_font_initialize(void);
extern s_font_header const* fallback_font_get_header(void);
extern bool fallback_font_get_character(e_utf32 utf_character, s_font_character const** out_character, void const** out_pixel_data);

/* ---------- globals */

extern unsigned char k_fallback_font_data[4500];
extern s_font_header const* const g_fallback_font_header;

/* ---------- public code */

#endif // __FONT_FALLBACK_H__

