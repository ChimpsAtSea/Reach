#pragma once
#ifndef __SOUND_CACHE_FILE_DEFINITIONS_H__
#define __SOUND_CACHE_FILE_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    SOUND_CACHE_FILE_GESTALT_TAG = 'ugh!'
};

/* ---------- definitions */

class c_cache_file_global_tag_registry;

/* ---------- prototypes */

bool build_cache_file_prepare_sound_gestalt(c_cache_file_global_tag_registry * registry);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_CACHE_FILE_DEFINITIONS_H__

