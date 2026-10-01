#pragma once
#ifndef __TAG_FILE_INTERFACE_H__
#define __TAG_FILE_INTERFACE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_block;
class c_tag_persist_context;

/* ---------- prototypes */

bool tag_block_load_from_context(s_tag_block * block, c_tag_persist_context * context);
bool tag_block_save_into_context(s_tag_block * block, c_tag_persist_context * context);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_FILE_INTERFACE_H__

