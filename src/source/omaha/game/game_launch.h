#pragma once
#ifndef __GAME_LAUNCH_H__
#define __GAME_LAUNCH_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_options;

// read from "d:\launch_tags.txt" as "%d\n%s\n%d\n%d\n%d\n%s\n%s\n"; field names unverified
struct s_game_options_launch_settings
{
    s_game_options_launch_settings();

    long unknown0; // 0x0
    c_static_string<256> scenario_path; // 0x4
    long unknown104; // 0x104 copied to s_game_options 0xF9CC
    long game_mode; // 0x108
    unsigned long flags; // 0x10C bit 1: delete the launch file once consumed
    c_static_string<128> unknown110; // 0x110
    c_static_string<128> initial_script_name; // 0x190
};
static_assert(sizeof(s_game_options_launch_settings) == 0x210, "s_game_options_launch_settings");

/* ---------- prototypes */

extern bool game_options_get_launch_settings(s_game_options * options, bool unused);
extern bool game_launch_get_settings(s_game_options_launch_settings * out_settings);
extern bool game_options_read_launch_settings_from_string(char const * string, s_game_options_launch_settings * out_settings);
extern bool game_launch_get_initial_script_name(c_static_string<128> * out_initial_script_name);

/* ---------- globals */

/* ---------- public code */

#endif // __GAME_LAUNCH_H__

