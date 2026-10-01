#pragma once
#ifndef __HAVOK_MOPP_CODE_DEFINITIONS_H__
#define __HAVOK_MOPP_CODE_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block;
class hkpMoppCode;

/* ---------- prototypes */

bool havok_mopp_code_definitions_append_mopp_code(s_tag_block * mopp_codes, hkpMoppCode const * mopp_code);

void havok_mopp_code_definitions_fixup(s_tag_block * mopp_codes);
hkpMoppCode * havok_mopp_code_definitions_get_mopp_code(s_tag_block const * mopp_codes, long mopp_code_index);

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_MOPP_CODE_DEFINITIONS_H__

