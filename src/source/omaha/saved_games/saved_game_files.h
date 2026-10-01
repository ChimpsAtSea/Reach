#pragma once
#ifndef __SAVED_GAME_FILES_H__
#define __SAVED_GAME_FILES_H__

/* ---------- headers */

#include "omaha\saved_games\content\content_item_metadata.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

char const * saved_game_files_get_filename_for_type(e_content_item_type content_item_type);
char const * saved_game_files_get_extension_for_type(e_content_item_type content_item_type, bool include_dot);

/* ---------- globals */

/* ---------- public code */

#endif // __SAVED_GAME_FILES_H__

