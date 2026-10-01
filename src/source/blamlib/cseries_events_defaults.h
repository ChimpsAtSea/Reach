#pragma once
#ifndef __CSERIES_EVENTS_DEFAULTS_H__
#define __CSERIES_EVENTS_DEFAULTS_H__

/* ---------- headers */

#include "foundation\baselib\errors\events\event_manager.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void build_networking_buffer_for_log(char * buffer, long buffer_size);

/* ---------- globals */

extern s_event_category_default_configuration const k_event_category_default_configurations[];
extern long const k_event_category_default_configuration_count;

/* ---------- public code */

#endif // __CSERIES_EVENTS_DEFAULTS_H__

