#pragma once
#ifndef __PROFILER_H__
#define __PROFILER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

// opens a profiled scope: guarded function-static definition index + c_profile_instance local (end() is called explicitly)
// verified in jetwash.cpp (jetwash_emitter_should_pulse / jetwash_prepare_for_particle_spawn)
#define PROFILER_SCOPE_BEGIN(LINE, name, instance) \
    static long name##_profiler_definition_index = profiler_add_new_definition(#name, 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE); \
    c_profile_instance instance(name##_profiler_definition_index); \
    if (g_profiler_collection_enabled) \
    { \
        instance.begin(); \
    }

// same as PROFILER_SCOPE_BEGIN with an explicit category argument (auxilary_channel.cpp: category 2)
#define PROFILER_SCOPE_BEGIN_CATEGORY(LINE, name, category, instance) \
    static long name##_profiler_definition_index = profiler_add_new_definition(#name, category, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE); \
    c_profile_instance instance(name##_profiler_definition_index); \
    if (g_profiler_collection_enabled) \
    { \
        instance.begin(); \
    }

// same as PROFILER_SCOPE_BEGIN, static named _unique_profile_definition_<name> (map symbols in async_xoverlapped_memory.obj)
#define PROFILER_UNIQUE_SCOPE_BEGIN(LINE, name, instance) \
    static long _unique_profile_definition_##name = profiler_add_new_definition(#name, 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE); \
    c_profile_instance instance(_unique_profile_definition_##name); \
    if (g_profiler_collection_enabled) \
    { \
        instance.begin(); \
    }

// $TODO: layout not reversed (0x0 c_profiler_timing_report, 0x4C definition index); ctor/dtor are inline in the target (f i, shell.obj), bodies not reversed yet
class c_profile_instance
{
public:
    c_profile_instance(long definition_index);
    ~c_profile_instance(void);

    void begin(void);
    void end(void);

private:
    unsigned char m_storage[0x78]; // 0x0
};
static_assert(sizeof(c_profile_instance) == 0x78, "c_profile_instance");

/* ---------- prototypes */

void profiler_initialize_system(void);
void profiler_pause_reporting(void);
long profiler_add_new_definition(char const * name, long category, char const * file, long line);

/* ---------- globals */

extern bool g_profiler_collection_enabled;

/* ---------- public code */

#endif // __PROFILER_H__

