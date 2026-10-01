#pragma once
#ifndef __CSERIES_ASSERTS_H__
#define __CSERIES_ASSERTS_H__

/* ---------- headers */

/* ---------- constants */

#define assert(expression) if(!(expression) && !assert_handle(#expression, __FILE__, __LINE__)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define assert_decomp(expression, file, line) if(!(expression) && !assert_handle(#expression, file, line)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define dassert_decomp(expression, diagnostic, file, line) if(!(expression) && !assert_handle(diagnostic, file, line)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
#define assert_tag_debug_untracked_jul_11_2011(LINE, ...) if(!(__VA_ARGS__) && !assert_handle(#__VA_ARGS__, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
// assert with an explicit diagnostic string instead of the stringized expression (H3 dassert)
#define dassert_tag_debug_untracked_jul_11_2011(LINE, expression, diagnostic) if(!(expression) && !assert_handle(diagnostic, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }
// assert with a formatted diagnostic built by a c_assert_string temporary (H3 vassert)
#define vassert_tag_debug_untracked_jul_11_2011(LINE, expression, ...) if(!(expression) && !assert_handle(c_assert_string(__VA_ARGS__), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)) { if(assert_is_debugger_present()) { __debugbreak(); } else { assert_halt(); } }

/* ---------- definitions */

struct s_slim_assert_info
{
    char const * expression;
    char const * file;
    long line;
};

class c_assert_string
{
public:
    c_assert_string(char const * format, ...);
    operator char const *() const;

private:
    static long const k_maximum_size = 1024;

    char m_string[k_maximum_size];
};

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
