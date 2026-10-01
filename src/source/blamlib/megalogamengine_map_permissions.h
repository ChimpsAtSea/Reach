#pragma once
#ifndef __MEGALOGAMENGINE_MAP_PERMISSIONS_H__
#define __MEGALOGAMENGINE_MAP_PERMISSIONS_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_stack.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

enum e_map_id;
class c_bitstream;

class c_megalogamengine_map_permissions
{
public:
    void initialize(void);
    bool is_valid(void) const;
    void encode(c_bitstream * packet) const;
    void decode(c_bitstream * packet);
    bool is_default_map_allowed(e_map_id map_id) const;

private:
    bool map_in_exception_list(e_map_id map_id) const;

protected:
    c_static_stack<short, 32> m_exception_map_ids; // 0x0
    bool m_default_permission; // 0x44
};
static_assert(sizeof(c_megalogamengine_map_permissions) == 0x48, "c_megalogamengine_map_permissions");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_MAP_PERMISSIONS_H__

