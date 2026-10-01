#pragma once
#ifndef __PLAYER_GRADES_H__
#define __PLAYER_GRADES_H__

/* ---------- headers */

#include "omaha\input\controllers.h"
#include "omaha\game\player_rewards\player_grade_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

e_player_grade player_rewards_get_controller_grade(e_controller_index controller_index);
e_player_sub_grade player_rewards_get_controller_sub_grade(e_controller_index controller_index);
bool player_rewards_grade_and_subgrade_available(e_controller_index controller_index);

/* ---------- globals */

/* ---------- public code */

#endif // __PLAYER_GRADES_H__

