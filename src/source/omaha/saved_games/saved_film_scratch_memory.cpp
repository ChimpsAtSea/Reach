#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\saved_film_scratch_memory.cpp"
/* ---------- headers */

#include "omaha\saved_games\saved_film_scratch_memory.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\physical_memory_map.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static c_physical_memory_allocation g_physical_memory_allocation(_memory_stage_map_configuration, "history");

c_saved_film_scratch_memory g_saved_film_scratch_memory;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_saved_film_scratch_memory g_saved_film_scratch_memory; // "?g_saved_film_scratch_memory@@3Vc_saved_film_scratch_memory@@A"

// public: c_saved_film_scratch_memory::c_saved_film_scratch_memory(void);
// public: c_saved_film_scratch_memory::s_system_data::s_system_data(void);
// public: static class c_saved_film_scratch_memory * c_saved_film_scratch_memory::get(void);
// public: void c_saved_film_scratch_memory::initialize(void);
// public: void c_saved_film_scratch_memory::dispose(void);
// public: void c_saved_film_scratch_memory::memory_initialize(void);
// public: void c_saved_film_scratch_memory::memory_dispose(void);
// public: void c_saved_film_scratch_memory::update(void);
// public: struct c_saved_film_scratch_memory::s_system_data * c_saved_film_scratch_memory::acquire(enum c_saved_film_scratch_memory::e_system);
// public: struct c_saved_film_scratch_memory::s_system_data * c_saved_film_scratch_memory::try_and_acquire(enum c_saved_film_scratch_memory::e_system);
// public: void c_saved_film_scratch_memory::release(enum c_saved_film_scratch_memory::e_system);
// public: void c_saved_film_scratch_memory::block_until_not_busy(void);
// public: c_async_single_buffer<13, 6>::c_async_single_buffer<13, 6>(void);
// public: c_saved_film_scratch_memory::~c_saved_film_scratch_memory(void);
// public: c_saved_film_scratch_memory::s_system_data::~s_system_data(void);
// public: c_async_single_buffer<13, 6>::~c_async_single_buffer<13, 6>(void);
// void g_saved_film_scratch_memory::`dynamic atexit destructor'(void);

c_saved_film_scratch_memory::c_saved_film_scratch_memory(void) :
    m_initialized(false)
{
    mangled_ppc("??0c_saved_film_scratch_memory@@QAA@XZ");

    for (long system_index = 0; static_cast<unsigned long>(system_index) < NUMBEROF(m_systems); system_index++)
    {
        m_systems[system_index].state = _system_state_none;
        m_systems[system_index].reference_count = 0;
        m_systems[system_index].buffer = NULL;
        m_systems[system_index].buffer_length = 0;
    }
};

c_saved_film_scratch_memory * c_saved_film_scratch_memory::get(void)
{
    mangled_ppc("?get@c_saved_film_scratch_memory@@SAPAV1@XZ");

    return &g_saved_film_scratch_memory;
};

void c_saved_film_scratch_memory::initialize(void)
{
    mangled_ppc("?initialize@c_saved_film_scratch_memory@@QAAXXZ");
};

void c_saved_film_scratch_memory::dispose(void)
{
    mangled_ppc("?dispose@c_saved_film_scratch_memory@@QAAXXZ");
};

void c_saved_film_scratch_memory::memory_initialize(void)
{
    mangled_ppc("?memory_initialize@c_saved_film_scratch_memory@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(60, !m_initialized);
    m_buffer_length = 0xA70000;
    m_buffer = static_cast<char *>(g_physical_memory_allocation.allocate(m_buffer_length, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 63, NULL, NULL, "film scratch"));
    if (m_buffer != NULL)
    {
        for (long system_index = 0; static_cast<unsigned long>(system_index) < NUMBEROF(m_systems); system_index++)
        {
            m_systems[system_index].buffer_set.use_external_storage(&m_buffer, 1, m_buffer_length);
        }
        m_initialized = true;
    }
};

void c_saved_film_scratch_memory::memory_dispose(void)
{
    mangled_ppc("?memory_dispose@c_saved_film_scratch_memory@@QAAXXZ");

    if (m_initialized)
    {
        for (long system_index = 0; static_cast<unsigned long>(system_index) < NUMBEROF(m_systems); system_index++)
        {
            assert_tag_debug_untracked_jul_11_2011(85, m_systems[system_index].state == _system_state_none);
            m_systems[system_index].buffer_set.release_storage(NULL);
        }
        g_physical_memory_allocation.deallocate(m_buffer, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 89);
        m_buffer = NULL;
        m_buffer_length = 0;
        m_initialized = false;
    }
};

void c_saved_film_scratch_memory::update(void)
{
    mangled_ppc("?update@c_saved_film_scratch_memory@@QAAXXZ");
};

c_saved_film_scratch_memory::s_system_data * c_saved_film_scratch_memory::acquire(e_system system)
{
    mangled_ppc("?acquire@c_saved_film_scratch_memory@@QAAPAUs_system_data@1@W4e_system@1@@Z");

    s_system_data * system_data = try_and_acquire(system);
    assert_tag_debug_untracked_jul_11_2011(109, system_data);
    return system_data;
};

c_saved_film_scratch_memory::s_system_data * c_saved_film_scratch_memory::try_and_acquire(e_system system)
{
    mangled_ppc("?try_and_acquire@c_saved_film_scratch_memory@@QAAPAUs_system_data@1@W4e_system@1@@Z");

    s_system_data * system_data = NULL;
    if (m_initialized)
    {
        if (m_systems[system].state == _system_state_acquired)
        {
            m_systems[system].buffer = m_buffer;
            m_systems[system].buffer_length = m_buffer_length;
            m_systems[system].reference_count++;
            system_data = &m_systems[system];
        }
        else
        {
            bool in_use = false;
            for (long system_index = 0; system_index < k_system_count; system_index++)
            {
                if (m_systems[system_index].state != _system_state_none)
                {
                    in_use = true;
                    break;
                }
            }
            if (!in_use)
            {
                m_systems[system].buffer = m_buffer;
                m_systems[system].buffer_length = m_buffer_length;
                assert_tag_debug_untracked_jul_11_2011(147, m_systems[system].reference_count == 0);
                m_systems[system].reference_count = 1;
                m_systems[system].state = _system_state_acquired;
                system_data = &m_systems[system];
            }
        }
    }
    return system_data;
};

void c_saved_film_scratch_memory::release(e_system system)
{
    mangled_ppc("?release@c_saved_film_scratch_memory@@QAAXW4e_system@1@@Z");

    assert_tag_debug_untracked_jul_11_2011(161, m_systems[system].state == _system_state_acquired);
    m_systems[system].reference_count--;
    if (m_systems[system].reference_count == 0)
    {
        m_systems[system].state = _system_state_none;
    }
};

void c_saved_film_scratch_memory::block_until_not_busy(void)
{
    mangled_ppc("?block_until_not_busy@c_saved_film_scratch_memory@@QAAXXZ");

    for (long system_index = 0; system_index < k_system_count; system_index++)
    {
        m_systems[system_index].buffer_set.block_until_not_busy();
    }
};
