/* ---------- headers */

#include "baselib\thread_manipulation.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\multithreading\primitives\thread_local_storage.h"
#include "foundation\baselib\multithreading\threads\thread_manipulation_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static __declspec(thread) unsigned long g_thread_user_index;
static __declspec(thread) char g_thread_name[128];
static __declspec(thread) bool g_thread_name_valid;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void thread_set_current_thread_user_index(unsigned long);
// unsigned long thread_get_current_thread_user_index(void);
// void thread_set_current_thread_name(char const *);
// char const * thread_get_current_thread_name(void);

void thread_set_current_thread_user_index(unsigned long user_index)
{
    mangled_ppc("?thread_set_current_thread_user_index@@YAXK@Z");

    TLS_DATA_GET_VALUE_REFERENCE(g_thread_user_index) = user_index;
};

unsigned long thread_get_current_thread_user_index(void)
{
    mangled_ppc("?thread_get_current_thread_user_index@@YAKXZ");

    return TLS_DATA_GET_VALUE_REFERENCE(g_thread_user_index);
};

void thread_set_current_thread_name(char const * name)
{
    mangled_ppc("?thread_set_current_thread_name@@YAXPBD@Z");

    csstrnzcpy(TLS_DATA_GET_VALUE_REFERENCE(g_thread_name), name, sizeof(g_thread_name));
    TLS_DATA_GET_VALUE_REFERENCE(g_thread_name_valid) = true;
    thread_set_current_thread_name_for_platform(name);
};

char const * thread_get_current_thread_name(void)
{
    mangled_ppc("?thread_get_current_thread_name@@YAPBDXZ");

    char const * name = NULL;
    if (TLS_DATA_GET_VALUE_REFERENCE(g_thread_name_valid))
    {
        name = TLS_DATA_GET_VALUE_REFERENCE(g_thread_name);
    }
    return name;
};

