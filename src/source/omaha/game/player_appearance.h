#pragma once
#ifndef __PLAYER_APPEARANCE_H__
#define __PLAYER_APPEARANCE_H__

/* ---------- headers */

#include "omaha\game\game_globals.h"
#include "omaha\game\player_model_customization.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\objects\emblems.h"

/* ---------- constants */

enum e_player_appearance_flags
{
    _player_appearance_flag_female_voice = 0,

    k_player_appearance_flags_count
};

long const k_player_appearance_service_tag_length = 5;

/* ---------- definitions */

typedef c_flags_no_init<e_player_appearance_flags, unsigned char, k_player_appearance_flags_count> c_player_appearance_flags;

struct s_player_appearance
{
    c_player_appearance_flags flags; // 0x0
    c_player_color_index change_color_index[3]; // 0x1
    c_player_model_choice player_model_choice; // 0x4
    unsigned char unknown5[3]; // 0x5 $TODO unknown
    s_emblem_info emblem_info; // 0x8
    char model_area_selections[k_player_model_customization_area_count]; // 0x10
    char non_model_selections[k_player_non_model_customization_count]; // 0x18
    wchar_t service_tag[k_player_appearance_service_tag_length]; // 0x1C $TODO unverified
    unsigned short pad; // 0x26
};
static_assert(sizeof(s_player_appearance) == 0x28, "s_player_appearance");

/* ---------- prototypes */

void player_appearance_initialize(s_player_appearance * player_appearance);
bool player_appearance_valid(s_player_appearance const * player_appearance);
void player_appearance_randomize(s_player_appearance * player_appearance);
void player_appearance_override_for_debug(s_player_appearance * player_appearance);
void player_appearance_force_model_area(long area, long selection);
void player_appearance_force_model_area_disable(long area);

/* ---------- globals */

extern e_player_model_customization_area g_force_model_area_override[k_player_model_customization_area_count];
extern bool g_randomize_player_appearance;
extern bool g_force_model_area[k_player_model_customization_area_count];

/* ---------- public code */

#endif // __PLAYER_APPEARANCE_H__

