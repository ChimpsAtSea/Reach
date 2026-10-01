#pragma once
#ifndef __ONLINE_ACHIEVEMENTS_H__
#define __ONLINE_ACHIEVEMENTS_H__

/* ---------- headers */

/* ---------- constants */

// Reach: c_enum_no_init<e_achievement, char, 0, 79> (k_maximum_value_plus_one = 79); enumerator names not reversed
enum e_achievement
{
    _achievement_first = 0,

    k_achievement_count = 79,
    k_invalid_achievement = -1
};

/* ---------- definitions */

enum e_controller_index;

/* ---------- prototypes */

void controller_grant_achievement(e_controller_index controller_index, e_achievement achievement);
void controller_grant_achievement_by_name(e_controller_index controller_index, long achievement_name);

/* ---------- globals */

/* ---------- public code */

#endif // __ONLINE_ACHIEVEMENTS_H__
