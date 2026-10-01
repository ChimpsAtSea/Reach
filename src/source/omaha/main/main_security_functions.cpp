#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\main\\main_security_functions.cpp"
/* ---------- headers */

#include "omaha\main\main_security_functions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\security_functions.h"
#include "omaha\main\main.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool security_calculate_hash_and_pump_main_loop_pregame(void const *, unsigned long, bool, struct s_network_http_request_hash *);

bool security_calculate_hash_and_pump_main_loop_pregame(void const * buffer, unsigned long buffer_size, bool use_secret_hash_salt, s_network_http_request_hash * hash)
{
    mangled_ppc("?security_calculate_hash_and_pump_main_loop_pregame@@YA_NPBXK_NPAUs_network_http_request_hash@@@Z");

    char working_memory[88];
    bool success = false;
    if (security_incremental_hash_begin(working_memory, sizeof(working_memory), use_secret_hash_salt, NULL, 0))
    {
        long const chunk_size = 0x100000;
        {
            long chunk_count = (buffer_size + chunk_size - 1) / chunk_size;
            long remaining_bytes_to_hash = buffer_size;
            for (long chunk_index = 0; chunk_index < chunk_count; chunk_index++)
            {
                long bytes_to_hash = int_min(remaining_bytes_to_hash, chunk_size);
                main_loop_pregame();
                security_incremental_hash_update(working_memory, sizeof(working_memory), static_cast<char const *>(buffer) + chunk_index * chunk_size, bytes_to_hash);
                remaining_bytes_to_hash -= bytes_to_hash;
            }
            assert_tag_debug_untracked_jul_11_2011(68, remaining_bytes_to_hash==0);
        }

        security_incremental_hash_finish(working_memory, sizeof(working_memory), hash);
        success = true;
    }

    return success;
};

