#pragma once
#ifndef __SOUND_REMOTE_H__
#define __SOUND_REMOTE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

enum
{
    _sound_command_start_sound = 0,
    _sound_command_stop_sound,
    _sound_command_set_scale,
    _sound_command_set_alternate,

    k_number_of_remote_sound_commands
};

/* ---------- definitions */

struct s_sound_command_header
{
    unsigned long group_tag; // 0x0
    char tag_name[256]; // 0x4
};
static_assert(sizeof(s_sound_command_header) == 0x104, "s_sound_command_header");

/* ---------- prototypes */

bool process_remote_sound_command(long sound_command, void const * command_data, long command_length);
bool send_remote_sound_command(long sound_command, void const * command_data, long command_length);
void sound_command_update_remote_parameter(long tag_index, long parameter0, long parameter1, long parameter2, float value0, float value1, float value2);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_REMOTE_H__
