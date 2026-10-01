#pragma once
#ifndef __SCREENSHOT_MOVIE_H__
#define __SCREENSHOT_MOVIE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void movie_record_distributed(short frame_rate, long seconds_to_record, short movie_screen_size_multiple, long mod_count, long mod_index);
extern void movie_record(short frame_rate, float seconds_to_record, short width, short height);
extern void movie_stop();
extern bool movie_recording();
extern bool movie_record_this_frame();
extern float movie_recording_timestep();
extern bool movie_advance_frame();
extern void movie_build_filename(char * filename, long max_filename_length);

/* ---------- globals */

/* ---------- public code */

#endif // __SCREENSHOT_MOVIE_H__

