#pragma once
#ifndef __XBOX_SOUND_CACHE_H__
#define __XBOX_SOUND_CACHE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_sound_permutation_chunk;

struct s_xma2_packet_info
{
    unsigned long block_sample_start; // 0x0
    unsigned long block_sample_end; // 0x4
};
static_assert(sizeof(s_xma2_packet_info) == 0x8, "s_xma2_packet_info");

class c_sound_cache_debugger
{
public:
    void lock_sound(s_sound_permutation_chunk * sound);
};

/* ---------- prototypes */

bool sound_cache_sound_loaded(s_sound_permutation_chunk * sound);
void * sound_cache_sound_hardware_lock(s_sound_permutation_chunk * sound, unsigned long * out_size);
void sound_cache_sound_hardware_unlock(s_sound_permutation_chunk * sound);
bool sound_cache_sound_uses_xma2(s_sound_permutation_chunk * sound);
void sound_cache_sound_get_xma2_info(s_sound_permutation_chunk * sound, s_xma2_packet_info * out_packet_info);
void sound_cache_sound_get_full_xma2_info(s_sound_permutation_chunk * sound, s_xma2_packet_info * out_packet_info);
void sound_cache_sound_spit_out_error(s_sound_permutation_chunk * sound, char const * error_string);

/* ---------- globals */

/* ---------- public code */

#endif // __XBOX_SOUND_CACHE_H__

