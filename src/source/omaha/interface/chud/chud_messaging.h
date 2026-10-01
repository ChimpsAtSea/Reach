#pragma once
#ifndef __CHUD_MESSAGING_H__
#define __CHUD_MESSAGING_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_commendation_progression_level;

/* ---------- prototypes */

void chud_messaging_post_commendation_callout(long user_index, long commendation_name, float display_time, e_commendation_progression_level new_level);
void chud_messaging_post_medal(long player_index, long medal_name);

/* ---------- globals */

/* ---------- public code */

#endif // __CHUD_MESSAGING_H__

