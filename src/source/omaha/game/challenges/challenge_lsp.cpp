#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\challenges\\challenge_lsp.cpp"
/* ---------- headers */

#include "omaha\game\challenges\challenge_lsp.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\game\challenges\challenges.h"
#include "omaha\input\controllers.h"
#include "omaha\interface\c_controller.h"
#include "omaha\networking\logic\storage\network_storage_files.h"
#include "omaha\networking\tools\network_blf.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool challenges_notify_user_user_file_updated(unsigned __int64, bool);

bool challenges_notify_user_user_file_updated(unsigned __int64 xuid, bool success)
{
    mangled_ppc("?challenges_notify_user_user_file_updated@@YA_N_K_N@Z");

    bool result = true;
    e_controller_index controller_index = get_controller_index_from_xuid(xuid);
    if (controller_index != k_no_controller)
    {
        if (!success)
        {
            event_wrapped(_event_message, "challenges:challenges_notify_user_user_file_updated: user file not found for controller %I64d / %d", xuid, controller_index);
        }
        else if (success)
        {
            char const * buffer = NULL;
            long buffer_length = 0;
            s_challenge_progress_chunk const * progress_chunk = NULL;
            {
                s_network_storage_user_files * user_files = network_storage_files_get_user_files(xuid);
                assert_tag_debug_untracked_jul_11_2011(51, user_files);

                buffer = reinterpret_cast<char const *>(user_files->user_file.get(&buffer_length));
                assert_tag_debug_untracked_jul_11_2011(55, buffer);
                assert_tag_debug_untracked_jul_11_2011(56, buffer_length > 0);

                {
                    bool must_byte_swap = false;
                    if (network_blf_verify_start_of_file(buffer, buffer_length, &must_byte_swap, NULL))
                    {
                        long chunk_size = 0;
                        char const * found_chunk = NULL;
                        if (network_blf_find_chunk(buffer, buffer_length, must_byte_swap, s_challenge_progress_chunk::k_chunk_type, s_challenge_progress_chunk::k_version_major, &chunk_size, &found_chunk, NULL, NULL, NULL))
                        {
                            assert_tag_debug_untracked_jul_11_2011(84, chunk_size==sizeof(s_challenge_progress_chunk));
                            event_wrapped(_event_message, "challenges:challenges_notify_user_user_file_updated: Got challenge progress chunk in user file for controller %d.", controller_index);
                            progress_chunk = reinterpret_cast<s_challenge_progress_chunk const *>(found_chunk - sizeof(s_blf_header));
                        }
                    }
                }
            }

            if (progress_chunk != NULL)
            {
                challenges_inject_controller_progress(controller_index, progress_chunk);
            }
        }

        challenges_notify_user_file_received(controller_index);
    }

    return result;
};

