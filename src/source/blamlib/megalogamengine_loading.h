#pragma once
#ifndef __MEGALOGAMENGINE_LOADING_H__
#define __MEGALOGAMENGINE_LOADING_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

class c_game_engine_custom_variant;
class c_game_variant;
struct s_file_reference;

extern void megalogamengine_load_binary_game_engine_from_file(char const * filename);
extern void megalogamengine_loading_initialize_for_new_round(void);
extern bool megalogamengine_load_binary_variant(char const * filename, c_game_engine_custom_variant * variant);
extern bool megalogamengine_load_binary_variant_full_filename(char const * filename, c_game_engine_custom_variant * variant);
extern bool load_variant_from_file(s_file_reference * file, c_game_engine_custom_variant * variant);
extern bool megalogamengine_try_and_load_variant(char const * filename, c_game_variant * game_variant);
extern void megalo_convert_variant_files(char ** arguments);

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_LOADING_H__

