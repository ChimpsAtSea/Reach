#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\havok_entity_iterator.cpp"
/* ---------- headers */

#include "omaha\physics\havok_entity_iterator.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\physics\havok_component.h"
#include "havok\hkpdynamics\hkpWorld.h"
#include "havok\hkpdynamics\hkpSimulationIsland.h"
#include "havok\hkpdynamics\hkpEntity.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

short c_havok_entity_iterator::g_num_entity_iterators_in_use;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// private: static short c_havok_entity_iterator::g_num_entity_iterators_in_use; // "?g_num_entity_iterators_in_use@c_havok_entity_iterator@@0FA"

// public: c_havok_entity_iterator::c_havok_entity_iterator(class hkpWorld *, enum c_havok_entity_iterator::e_iteration_type);
// public: c_havok_entity_iterator::~c_havok_entity_iterator(void);
// public: static void c_havok_entity_iterator::notify_entity_activation_change(void);
// public: void c_havok_entity_iterator::begin(void);
// public: void c_havok_entity_iterator::end(void);
// public: class hkpEntity * c_havok_entity_iterator::get_entity(void);
// public: long c_havok_entity_iterator::get_object_index(void);
// public: bool c_havok_entity_iterator::next(void);

c_havok_entity_iterator::c_havok_entity_iterator(hkpWorld * world, e_iteration_type iteration_type) :
    m_world(world),
    m_iteration_type(iteration_type)
{
    mangled_ppc("??0c_havok_entity_iterator@@QAA@PAVhkpWorld@@W4e_iteration_type@0@@Z");

    assert_tag_debug_untracked_jul_11_2011(25, m_world != NULL);
    assert_tag_debug_untracked_jul_11_2011(26, VALID_INDEX(iteration_type, k_iteration_type_count));

    m_iterating = false;
};

c_havok_entity_iterator::~c_havok_entity_iterator(void)
{
    mangled_ppc("??1c_havok_entity_iterator@@QAA@XZ");

    dassert_tag_debug_untracked_jul_11_2011(36, !m_iterating, "you must call end before finishing with this iterator");
};

void c_havok_entity_iterator::notify_entity_activation_change(void)
{
    mangled_ppc("?notify_entity_activation_change@c_havok_entity_iterator@@SAXXZ");

    dassert_tag_debug_untracked_jul_11_2011(45, g_num_entity_iterators_in_use == 0, "there are c_havok_entity_iterator's in use.  Adding or remoing entities from the world or activating or deactivating entites won't fly right now.");
};

void c_havok_entity_iterator::begin(void)
{
    mangled_ppc("?begin@c_havok_entity_iterator@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(54, m_world != NULL);
    assert_tag_debug_untracked_jul_11_2011(55, !m_iterating);

    m_active_islands_processed = false;
    m_island_index = NONE;
    m_entity_index = NONE;
    m_iterating = true;
    g_num_entity_iterators_in_use++;
};

void c_havok_entity_iterator::end(void)
{
    mangled_ppc("?end@c_havok_entity_iterator@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(70, m_iterating);

    m_iterating = false;
    g_num_entity_iterators_in_use--;
};

hkpEntity * c_havok_entity_iterator::get_entity(void)
{
    mangled_ppc("?get_entity@c_havok_entity_iterator@@QAAPAVhkpEntity@@XZ");

    assert_tag_debug_untracked_jul_11_2011(82, m_iterating);
    assert_tag_debug_untracked_jul_11_2011(83, m_world != NULL);
    assert_tag_debug_untracked_jul_11_2011(84, m_island_index != NONE && m_entity_index != NONE);

    hkpEntity * entity = NULL;
    if (!m_active_islands_processed)
    {
        entity = m_world->getActiveSimulationIslands()[m_island_index]->getEntities()[m_entity_index];
    }
    else
    {
        entity = m_world->getInactiveSimulationIslands()[m_island_index]->getEntities()[m_entity_index];
    }

    return entity;
};

long c_havok_entity_iterator::get_object_index(void)
{
    mangled_ppc("?get_object_index@c_havok_entity_iterator@@QAAJXZ");

    assert_tag_debug_untracked_jul_11_2011(102, m_iterating);

    hkpEntity const * entity = get_entity();
    long const havok_component_index = havok_entity_get_havok_component_index(entity);
    c_havok_component const * havok_component = get_havok_component(havok_component_index);

    return havok_component->get_object_index();
};

bool c_havok_entity_iterator::next(void)
{
    mangled_ppc("?next@c_havok_entity_iterator@@QAA_NXZ");

    bool result = false;

    assert_tag_debug_untracked_jul_11_2011(116, m_iterating);
    assert_tag_debug_untracked_jul_11_2011(117, m_world != NULL);

    if (m_island_index == NONE)
    {
        m_island_index = 0;
        m_entity_index = 0;
        if (m_iteration_type == _iteration_type_inactive_entities)
        {
            m_active_islands_processed = true;
        }
    }
    else
    {
        m_entity_index++;
    }

    if (!m_active_islands_processed)
    {
        while (m_island_index < m_world->getActiveSimulationIslands().getSize())
        {
            if (m_entity_index < m_world->getActiveSimulationIslands()[m_island_index]->getEntities().getSize())
            {
                result = true;
                break;
            }
            else
            {
                m_island_index++;
                m_entity_index = 0;
            }
        }

        if (!result)
        {
            m_active_islands_processed = true;
            m_island_index = 0;
            m_entity_index = 0;
        }
    }

    if (m_active_islands_processed && (m_iteration_type == _iteration_type_all_entities || m_iteration_type == _iteration_type_inactive_entities))
    {
        assert_tag_debug_untracked_jul_11_2011(165, !result);

        while (m_island_index < m_world->getInactiveSimulationIslands().getSize())
        {
            if (m_entity_index < m_world->getInactiveSimulationIslands()[m_island_index]->getEntities().getSize())
            {
                result = true;
                break;
            }
            else
            {
                m_island_index++;
                m_entity_index = 0;
            }
        }
    }

    return result;
};
