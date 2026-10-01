#pragma once
#ifndef __REMOTE_COMMAND_H__
#define __REMOTE_COMMAND_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void remote_command_send_hs_result(long result, long result_type);
extern bool remote_sound_command(long sound_command, void * command_data, long command_length);
extern bool remote_hs_expression_send(char const * expression);

/* ---------- globals */

/* ---------- public code */

#endif // __REMOTE_COMMAND_H__

