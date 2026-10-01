#pragma once
#ifndef __SOUND_EFFECT_MANAGER_H__
#define __SOUND_EFFECT_MANAGER_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

long sound_effect_manager_create_manual(long playback_designator, float scale, unsigned long playback_flags);
void sound_effect_manager_set_scale_manual(long sound_effect_index, float scale);
void sound_effect_manager_stop_manual(long sound_effect_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_EFFECT_MANAGER_H__

