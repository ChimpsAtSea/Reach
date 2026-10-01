#pragma once
#ifndef __SCENARIO_LOAD_PARAMETERS_H__
#define __SCENARIO_LOAD_PARAMETERS_H__

/* ---------- headers */

#include "omaha\tag_files\tag_groups.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_scenario_load_parameters
{
    s_tag_reference scenario; // 0x0
    s_tag_data parameters; // 0x10
    unsigned char pad[32]; // 0x24
};
static_assert(sizeof(s_scenario_load_parameters) == 0x44, "s_scenario_load_parameters");

/* ---------- prototypes */

void scenario_load_parameters_begin(char const * scenario_path);
void scenario_load_parameters_end(void);
s_scenario_load_parameters const * scenario_load_parameters_get(long tag_index, s_tag_block const * parameters_block);
bool scenario_load_parameters_parse_string(s_tag_data const * parameters_text, long * string_offset, long command_buffer_length, char * command_buffer, long argument_buffer_length, char * argument_buffer);

/* ---------- globals */

extern char g_scenario_load_path[256];
extern bool g_scenario_load_in_progress;

/* ---------- public code */

#endif // __SCENARIO_LOAD_PARAMETERS_H__

