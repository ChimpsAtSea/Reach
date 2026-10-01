#pragma once
#ifndef __EXPOSED_VARIABLE_H__
#define __EXPOSED_VARIABLE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_exposed_variable
{
    enum e_var
    {
        k_global_tag_instances = 0,

        k_max_var
    };

    static void add(e_var var, void *address);

private:
    s_exposed_variable(void) :
        m_id(),
        m_address()
    {
        mangled_ppc("??0s_exposed_variable@@AAA@XZ");
    }

    static long const x_var_ids[];
    static long const x_max;
    static s_exposed_variable x_global_array[];

    long m_id;
    void *m_address;
};
static_assert(sizeof(s_exposed_variable) == 0x8, "s_exposed_variable");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EXPOSED_VARIABLE_H__

