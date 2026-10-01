#pragma once
#ifndef __CSERIES_ERRORS_H__
#define __CSERIES_ERRORS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void errors_initialize(void);
void errors_dispose(void);
bool errors_add_fatal_error_callback(void (*callback)(void));
void call_fatal_error_callbacks(void);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_ERRORS_H__

