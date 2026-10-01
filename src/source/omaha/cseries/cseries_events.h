#pragma once
#ifndef __OMAHA_CSERIES_EVENTS_H__
#define __OMAHA_CSERIES_EVENTS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct s_file_reference;

s_file_reference * create_report_file_reference(s_file_reference * reference, char const * name, bool place_in_report_directory);
void events_disable_suppression(bool disable);

/* ---------- globals */

/* ---------- public code */

#endif // __OMAHA_CSERIES_EVENTS_H__

