/* ---------- headers */

#include "baselib\system_identity.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\multithreading\datatypes\initialization_lock.h"
#include "foundation\baselib\system\system_identity_xenon.h"

/* ---------- constants */

/* ---------- definitions */

struct s_system_identity_globals
{
    s_static_string<260> console_user_name;
};
static_assert(sizeof(s_system_identity_globals) == 0x104, "s_system_identity_globals");

/* ---------- prototypes */

/* ---------- globals */

static t_initialization_lock<s_system_identity_globals> g_system_identity_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void system_get_system_identifier(char *, long);
// void system_set_console_user_name(char const *);
// bool system_get_console_user_name(char *, long);
// public: bool s_static_string<260>::is_empty(void) const;
// public: static long s_static_string<260>::max_length(void);
// public: struct s_system_identity_globals const * t_initialization_lock<struct s_system_identity_globals>::get_const(void) const;
// public: struct s_system_identity_globals * t_initialization_lock<struct s_system_identity_globals>::get_writable_UNSAFE(void);

void system_get_system_identifier(char * buffer, long buffer_size)
{
    mangled_ppc("?system_get_system_identifier@@YAXPADJ@Z");

    s_static_string<260> user_name;
    s_static_string<32> machine_name;

    system_get_user_name(user_name.get_buffer(), user_name.max_length());
    system_get_machine_name(machine_name.get_buffer(), machine_name.max_length());
    csnzprintf(buffer, buffer_size, "%s@%s@%s", "xe", user_name.get_string(), machine_name.get_string());
};

void system_set_console_user_name(char const * user_name)
{
    mangled_ppc("?system_set_console_user_name@@YAXPBD@Z");

    s_system_identity_globals * globals = g_system_identity_globals.get_writable_UNSAFE();
    globals->console_user_name.set(user_name);
};

bool system_get_console_user_name(char * buffer, long buffer_size)
{
    mangled_ppc("?system_get_console_user_name@@YA_NPADJ@Z");

    bool result = false;
    s_system_identity_globals const * globals = g_system_identity_globals.get_const();
    if (!globals->console_user_name.is_empty())
    {
        csstrnzcpy(buffer, globals->console_user_name.get_string(), buffer_size);
        result = true;
    }

    return result;
};
