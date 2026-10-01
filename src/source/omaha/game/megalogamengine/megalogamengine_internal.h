#pragma once
#ifndef __MEGALOGAMENGINE_INTERNAL_H__
#define __MEGALOGAMENGINE_INTERNAL_H__

/* ---------- headers */

#include "omaha\game\game_constants.h"

/* ---------- constants */

// values from get_disposition_between_team_designators; names $TODO unverified
enum e_disposition
{
    _disposition_neutral = 0,
    _disposition_friendly,
    _disposition_enemy,

    k_disposition_count
};

/* ---------- definitions */

/* ---------- prototypes */

extern bool megalogamengine_initialize_for_new_script(void);
extern e_disposition get_disposition_between_team_designators(e_multiplayer_team_designator team_designator, e_multiplayer_team_designator other_team_designator);

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_INTERNAL_H__

