#pragma once
#ifndef __CSERIES_ASSERTS_H__
#define __CSERIES_ASSERTS_H__

/* ---------- headers */

/* ---------- constants */

#define assert(expression) if(!(expression) && !assert_handle(#expression, __FILE__, __LINE__)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define assert_decomp(expression, file, line) if(!(expression) && !assert_handle(#expression, file, line)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define assert_tag_debug_untracked_jul_11_2011(LINE, ...) if(!(__VA_ARGS__) && !assert_handle(#__VA_ARGS__, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define vassert_tag_debug_untracked_jul_11_2011(LINE, EXPRESSION, MESSAGE) if(!(EXPRESSION) && !assert_handle(MESSAGE, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }

/* ---------- definitions */

struct s_slim_assert_info;
class c_assert_string;

/* ---------- prototypes */

extern long register_tracked_assert(char const * arg1, long arg2);
extern void log_tracked_assert(long arg1);
extern bool assert_handle(char const * expression, char const * file, long line);
extern void assert_halt(void);
extern bool assert_is_debugger_present(void);
extern void assert_handle_slim_constant(s_slim_assert_info const * info);
extern void assert_handle_slim_dynamic(s_slim_assert_info const * info, c_assert_string const & arg2);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_ASSERTS_H__
