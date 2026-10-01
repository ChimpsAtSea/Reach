#pragma once
#ifndef __CACHE_FILE_XOR_CODEC_H__
#define __CACHE_FILE_XOR_CODEC_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_persistent_identifier;

class c_cache_file_decompressor_service;

/* ---------- prototypes */

extern c_cache_file_decompressor_service * get_xor_cache_file_runtime_decompressor_service(void);

/* ---------- globals */

extern s_tag_persistent_identifier const k_xor_codec_identifier;

/* ---------- public code */

#endif // __CACHE_FILE_XOR_CODEC_H__

