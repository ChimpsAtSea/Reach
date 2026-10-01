#pragma once
#ifndef __HAVOK_ENTITY_ITERATOR_H__
#define __HAVOK_ENTITY_ITERATOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class hkpWorld;
class hkpEntity;

class c_havok_entity_iterator
{
public:
    enum e_iteration_type
    {
        _iteration_type_active_entities = 0,
        _iteration_type_inactive_entities,
        _iteration_type_all_entities,

        k_iteration_type_count
    };

    c_havok_entity_iterator(hkpWorld * world, e_iteration_type iteration_type);
    ~c_havok_entity_iterator(void);

    static void notify_entity_activation_change(void);

    void begin(void);
    void end(void);
    hkpEntity * get_entity(void);
    long get_object_index(void);
    bool next(void);

private:
    static short g_num_entity_iterators_in_use;

    bool m_iterating; // 0x0
    bool m_active_islands_processed; // 0x1
    int m_island_index; // 0x4
    int m_entity_index; // 0x8
    hkpWorld * m_world; // 0xC
    e_iteration_type const m_iteration_type; // 0x10
};
static_assert(sizeof(c_havok_entity_iterator) == 0x14, "c_havok_entity_iterator");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __HAVOK_ENTITY_ITERATOR_H__

