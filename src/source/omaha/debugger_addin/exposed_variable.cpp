/* ---------- headers */

#include "omaha\debugger_addin\exposed_variable.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

long const s_exposed_variable::x_var_ids[] =
{
    'TIDA'
};
s_exposed_variable s_exposed_variable::x_global_array[256];

static void *g_DebugData = NULL;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static long const *const const s_exposed_variable::x_var_ids; // "?x_var_ids@s_exposed_variable@@0QBJB"
// private: static struct s_exposed_variable *s_exposed_variable::x_global_array; // "?x_global_array@s_exposed_variable@@0PAU1@A"

// public: static void s_exposed_variable::add(enum s_exposed_variable::e_var, void *);
// private: s_exposed_variable::s_exposed_variable(void);

void s_exposed_variable::add(e_var var, void *address)
{
    mangled_ppc("?add@s_exposed_variable@@SAXW4e_var@1@PAX@Z");

    g_DebugData = x_global_array;

    x_global_array[var].m_id = x_var_ids[var];
    x_global_array[var].m_address = address;
};

