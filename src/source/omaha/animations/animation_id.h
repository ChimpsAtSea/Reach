#pragma once
#ifndef __ANIMATION_ID_H__
#define __ANIMATION_ID_H__

/* ---------- headers */

#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_animation_id
{
public:
    c_animation_id() :
        m_subgraph(NONE),
        m_index(NONE)
    {
        mangled_ppc("??0c_animation_id@@QAA@XZ");
    }

    ~c_animation_id()
    {
        mangled_ppc("??1c_animation_id@@QAA@XZ");
    }

    bool valid() const;
    void clear();
    short get_index() const;
    short get_subgraph() const;
    void set_subgraph(short subgraph);
    void set_index(short index);
    bool operator==(c_animation_id const & other) const;
    bool operator!=(c_animation_id const & other) const;

private:
    short m_subgraph; // 0x0
    short m_index; // 0x2
};
static_assert(sizeof(c_animation_id) == 0x4, "c_animation_id");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __ANIMATION_ID_H__

