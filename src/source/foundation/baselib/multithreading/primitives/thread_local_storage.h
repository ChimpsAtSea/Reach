#pragma once
#ifndef __THREAD_LOCAL_STORAGE_H__
#define __THREAD_LOCAL_STORAGE_H__

/* ---------- headers */

/* ---------- constants */

// thread local data declared with __declspec(thread); expands to the variable itself
#define TLS_DATA_GET_VALUE_REFERENCE(name) (name)

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __THREAD_LOCAL_STORAGE_H__

