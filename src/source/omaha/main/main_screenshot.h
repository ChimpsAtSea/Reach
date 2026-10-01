#pragma once
#ifndef __MAIN_SCREENSHOT_H__
#define __MAIN_SCREENSHOT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern bool screenshot_in_progress(void);

extern bool init_screenshot(short width, short height, char const * name);
extern float screenshot_get_frame_update_time_delta();

/* ---------- globals */

/* ---------- public code */

#endif // __MAIN_SCREENSHOT_H__

