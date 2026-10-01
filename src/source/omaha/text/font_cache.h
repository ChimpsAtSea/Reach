#pragma once
#ifndef __FONT_CACHE_H__
#define __FONT_CACHE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO: derives from c_font_cache_base (vtable at 0x0) and holds a c_font_cache_scope_lock at 0x4; virtuals not declared yet
class c_font_cache_mt_safe
{
public:
    c_font_cache_mt_safe();
    ~c_font_cache_mt_safe();

private:
    void * m_vftable_placeholder; // 0x0
    bool m_scope_lock; // 0x4
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __FONT_CACHE_H__

