#pragma once
#ifndef __ANIMATION_STATISTICS_H__
#define __ANIMATION_STATISTICS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void animation_statistics_dump(void);
void animation_statistic_initialize_for_new_map(void);
void animation_statistic_dispose_from_old_map(void);
void animation_statistic_initialize(void);
void animation_statistic_dispose(void);

/* ---------- globals */

extern bool g_animation_statistic_accumulator_enabled;

/* ---------- public code */

#endif // __ANIMATION_STATISTICS_H__

