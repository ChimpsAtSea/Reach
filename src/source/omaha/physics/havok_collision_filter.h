#pragma once
#ifndef __HAVOK_COLLISION_FILTER_H__
#define __HAVOK_COLLISION_FILTER_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    k_havok_group_count = 27,
};

/* ---------- definitions */

struct s_havok_collision_filter_definition;

/* ---------- prototypes */

void havok_collision_filter_build(s_havok_collision_filter_definition * definition);
void havok_collision_filter_fixup(s_havok_collision_filter_definition * definition);

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_COLLISION_FILTER_H__

