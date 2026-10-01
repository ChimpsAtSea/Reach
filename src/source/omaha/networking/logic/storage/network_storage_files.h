#ifndef __NETWORK_STORAGE_FILES_H__
#define __NETWORK_STORAGE_FILES_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// layout not reversed yet; only what callers need
template<long k_buffer_size>
class c_stored_buffer_network_storage_file
{
public:
    unsigned char const * get(long * buffer_size) const; // inline in the target (f i), asserts ready_with_data() at network_storage_files.h:418
};

template<long k_buffer_size>
class c_network_storage_file_user :
    public c_stored_buffer_network_storage_file<k_buffer_size>
{
};

// ctor: c_network_storage_file_user<11029> at 0x0, c_network_storage_file_recent_players<s_files_user_recent_players> at 0x5D10
struct s_network_storage_user_files
{
    c_network_storage_file_user<11029> user_file; // 0x0
};

/* ---------- prototypes */

s_network_storage_user_files * network_storage_files_get_user_files(unsigned __int64 xuid);
extern bool create_configuration_file(char const * filename, void const * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_STORAGE_FILES_H__

