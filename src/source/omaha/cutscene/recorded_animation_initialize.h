#pragma once
#ifndef __RECORDED_ANIMATION_INITIALIZE_H__
#define __RECORDED_ANIMATION_INITIALIZE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct unit_control_data;

/* ---------- prototypes */

void recorded_animation_byteswap_unit_control(char ** playback_stream, unsigned char unit_version);
void recorded_animation_initialize_unit_control(unit_control_data * control, char const ** playback_stream, unsigned char unit_version);
void recorded_animation_write_unit_control(unit_control_data * control, char ** playback_stream, unsigned char unit_version);

/* ---------- globals */

extern long const real_vector2d_bs_codes[2];
extern long const real_vector3d_bs_codes[3];

/* ---------- public code */

#endif // __RECORDED_ANIMATION_INITIALIZE_H__

