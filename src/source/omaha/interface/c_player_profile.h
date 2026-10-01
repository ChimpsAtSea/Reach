#ifndef __C_PLAYER_PROFILE_H__
#define __C_PLAYER_PROFILE_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO: layout not reversed; only the methods used so far are declared
class c_player_profile_interface
{
public:
    void set_recently_advanced_grades(bool recently_advanced); // player_grades.obj
    void set_recently_advanced_sub_grades(bool recently_advanced); // player_grades.obj
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __C_PLAYER_PROFILE_H__

