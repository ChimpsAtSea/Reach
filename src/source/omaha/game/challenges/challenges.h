#pragma once
#ifndef __CHALLENGES_H__
#define __CHALLENGES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\input\controllers.h"
#include "omaha\networking\tools\network_blf.h"

/* ---------- constants */

/* ---------- definitions */

// 'chpr' blf chunk; contents not reversed yet
struct s_challenge_progress_chunk
{
    enum
    {
        k_chunk_type = 'chpr',
        k_version_major = 2,
    };

    s_blf_header header; // 0x0
    unsigned char data[0x58]; // 0xC
};
static_assert(sizeof(s_challenge_progress_chunk) == 0x64, "s_challenge_progress_chunk");

/* ---------- prototypes */

void challenges_notify_user_file_received(e_controller_index controller_index);
void challenges_inject_controller_progress(e_controller_index controller_index, s_challenge_progress_chunk const * progress_chunk);
bool challenge_progress(e_controller_index controller_index, long challenge_name);

/* ---------- globals */

/* ---------- public code */

#endif // __CHALLENGES_H__

