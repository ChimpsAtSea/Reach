#pragma once
#ifndef __VIRTUAL_GUARD_BLOCK_H__
#define __VIRTUAL_GUARD_BLOCK_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_object.h"

/* ---------- constants */

/* ---------- definitions */

struct s_virtual_guard_block
{
    unsigned long object_id;
};
static_assert(sizeof(s_virtual_guard_block) == 0x4, "s_virtual_guard_block");

struct s_virtual_guard_block_definition
{
    char const * name;
};
static_assert(sizeof(s_virtual_guard_block_definition) == 0x4, "s_virtual_guard_block_definition");

/* ---------- prototypes */

extern void virtual_guard_block_create(c_synchronization_object * guard_block, unsigned long object_id, long lock_node_index, s_virtual_guard_block_definition const * definition);
extern void virtual_guard_block_destroy(c_synchronization_object * guard_block);
extern void virtual_guard_block_enter(s_virtual_guard_block guard_block);
extern void virtual_guard_block_leave(s_virtual_guard_block guard_block);

/* ---------- globals */

extern s_virtual_guard_block const k_virtual_guard_block_invalid;

/* ---------- public code */

class c_virtual_guard_block_scope
{
public:
    c_virtual_guard_block_scope(s_virtual_guard_block guard_block)
    {
        mangled_ppc("??0c_virtual_guard_block_scope@@QAA@Us_virtual_guard_block@@@Z");

        m_guard_block = guard_block;
        virtual_guard_block_enter(m_guard_block);
    }

    ~c_virtual_guard_block_scope(void)
    {
        mangled_ppc("??1c_virtual_guard_block_scope@@QAA@XZ");

        virtual_guard_block_leave(m_guard_block);
    }

private:
    s_virtual_guard_block m_guard_block;
};
static_assert(sizeof(c_virtual_guard_block_scope) == 0x4, "c_virtual_guard_block_scope");

#endif // __VIRTUAL_GUARD_BLOCK_H__

