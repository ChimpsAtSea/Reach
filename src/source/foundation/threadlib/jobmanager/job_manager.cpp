#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\threadlib\\jobmanager\\job_manager.cpp"
/* ---------- headers */

#include "foundation\threadlib\jobmanager\job_manager.h"
#include "baselib\thread_execution_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\jobmanager\work_unit\work_unit.h"

/* ---------- constants */

unsigned long const k_jm_max_work_units = 1;

/* ---------- definitions */

struct s_job_manager_internal
{
    s_job_manager_internal()
    {
        mangled_ppc("??0s_job_manager_internal@@QAA@XZ");
    };

    ~s_job_manager_internal()
    {
        mangled_ppc("??1s_job_manager_internal@@QAA@XZ");
    };

    unsigned long acquire_handle()
    {
        mangled_ppc("?acquire_handle@s_job_manager_internal@@QAAKXZ");

        if (m_num_used_work_units < k_jm_max_work_units)
        {
            for (unsigned long index = 0; index < k_jm_max_work_units; index++)
            {
                if (!m_work_units[index].is_used())
                {
                    m_num_used_work_units++;
                    m_work_units[index].set_used();
                    return index;
                }
            }
        }

        return 0xFFFFFFFF;
    };

    void release_handle(unsigned long index)
    {
        mangled_ppc("?release_handle@s_job_manager_internal@@QAAXK@Z");

        assert_tag_debug_untracked_jul_11_2011(108, index < k_jm_max_work_units);
        m_work_units[index].unset_flag(1);
        m_num_used_work_units--;
    };

    c_work_unit * get_work_unit(unsigned long index)
    {
        mangled_ppc("?get_work_unit@s_job_manager_internal@@QAAPAVc_work_unit@@K@Z");

        assert_tag_debug_untracked_jul_11_2011(117, index < k_jm_max_work_units);
        return &m_work_units[index];
    };

    c_work_unit m_work_units[k_jm_max_work_units];
    unsigned long m_unknown50098;
    unsigned long m_num_used_work_units;
};
static_assert(sizeof(s_job_manager_internal) == 0x500A0, "s_job_manager_internal");

/* ---------- prototypes */

s_job_manager_internal * get_internal_data(void);

/* ---------- globals */

static c_job_manager g_job_manager;
c_jm_work_unit_handle g_default_work_unit;
s_job_manager_internal g_jm_internal_data;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_jm_work_unit_handle g_default_work_unit; // "?g_default_work_unit@@3Vc_jm_work_unit_handle@@A"
// struct s_job_manager_internal g_jm_internal_data; // "?g_jm_internal_data@@3Us_job_manager_internal@@A"

// class c_job_manager & get_job_manager(void);
// void job_manager_initialize(struct s_critical_section const &, struct s_critical_section const &, struct s_critical_section const &, struct s_semaphore const &, struct s_semaphore const &);
// void job_manager_dispose(void);
// void job_manager_set_default_work_unit(class c_jm_work_unit_handle const &);
// class c_jm_work_unit_handle & job_manager_get_default_work_unit(void);
// struct s_job_manager_internal * get_internal_data(void);
// public: bool c_job_manager::initialize(struct s_critical_section const &, struct s_critical_section const &, struct s_critical_section const &, struct s_semaphore const &, struct s_semaphore const &);
// public: void c_job_manager::dispose(void);
// public: static class c_jm_work_unit_handle c_job_manager::create_work_unit(struct s_work_unit_params const &);
// public: unsigned long s_job_manager_internal::acquire_handle(void);
// public: bool c_work_unit::is_used(void);
// public: void c_work_unit::set_used(void);
// public: void c_work_unit::set_flag(unsigned long);
// public: class c_work_unit * s_job_manager_internal::get_work_unit(unsigned long);
// public: static void c_job_manager::destroy_work_unit(class c_jm_work_unit_handle &);
// public: void s_job_manager_internal::release_handle(unsigned long);
// public: void c_work_unit::unset_flag(unsigned long);
// public: void c_job_manager::register_block_callback(void (*)(void));
// public: void c_job_manager::invoke_block_callback(void);
// public: c_job_manager::c_job_manager(void);
// public: s_job_manager_internal::s_job_manager_internal(void);
// public: c_work_unit::c_work_unit(void);
// public: c_scheduler_fifo::c_scheduler_fifo(void);
// public: c_job_list::c_job_list(void);
// public: c_job_handle_internal::c_job_handle_internal(void);
// public: c_indexed_pool<struct s_il_node, 4096>::c_indexed_pool<struct s_il_node, 4096>(void);
// public: c_job_manager::~c_job_manager(void);
// public: s_job_manager_internal::~s_job_manager_internal(void);
// public: c_work_unit::~c_work_unit(void);
// public: c_scheduler_fifo::~c_scheduler_fifo(void);
// public: c_job_list::~c_job_list(void);
// public: c_job_handle_internal::~c_job_handle_internal(void);
// public: c_indexed_pool<struct s_il_node, 4096>::~c_indexed_pool<struct s_il_node, 4096>(void);
// void g_job_manager::`dynamic atexit destructor'(void);
// void g_default_work_unit::`dynamic atexit destructor'(void);
// void g_jm_internal_data::`dynamic atexit destructor'(void);

c_job_manager & get_job_manager(void)
{
    mangled_ppc("?get_job_manager@@YAAAVc_job_manager@@XZ");

    return g_job_manager;
};

void job_manager_initialize(s_critical_section const & activelist_critical_section, s_critical_section const & freelist_critical_section, s_critical_section const & deps_critical_section, s_semaphore const & semaphore0, s_semaphore const & semaphore1)
{
    mangled_ppc("?job_manager_initialize@@YAXABUs_critical_section@@00ABUs_semaphore@@1@Z");

    g_job_manager.initialize(activelist_critical_section, freelist_critical_section, deps_critical_section, semaphore0, semaphore1);
};

void job_manager_dispose(void)
{
    mangled_ppc("?job_manager_dispose@@YAXXZ");

    g_job_manager.dispose();
};

void job_manager_set_default_work_unit(c_jm_work_unit_handle const & work_unit)
{
    mangled_ppc("?job_manager_set_default_work_unit@@YAXABVc_jm_work_unit_handle@@@Z");

    g_default_work_unit = work_unit;
};

c_jm_work_unit_handle & job_manager_get_default_work_unit(void)
{
    mangled_ppc("?job_manager_get_default_work_unit@@YAAAVc_jm_work_unit_handle@@XZ");

    assert_tag_debug_untracked_jul_11_2011(67, g_default_work_unit.valid());
    return g_default_work_unit;
};

s_job_manager_internal * get_internal_data(void)
{
    mangled_ppc("?get_internal_data@@YAPAUs_job_manager_internal@@XZ");

    return &g_jm_internal_data;
};

bool c_job_manager::initialize(s_critical_section const & activelist_critical_section, s_critical_section const & freelist_critical_section, s_critical_section const & deps_critical_section, s_semaphore const & semaphore0, s_semaphore const & semaphore1)
{
    mangled_ppc("?initialize@c_job_manager@@QAA_NABUs_critical_section@@00ABUs_semaphore@@1@Z");

    m_critical_sections[0] = activelist_critical_section;
    m_critical_sections[1] = freelist_critical_section;
    m_critical_sections[2] = deps_critical_section;
    m_semaphores[0] = semaphore0;
    m_semaphores[1] = semaphore1;

    return true;
};

void c_job_manager::dispose(void)
{
    mangled_ppc("?dispose@c_job_manager@@QAAXXZ");
};

c_jm_work_unit_handle c_job_manager::create_work_unit(s_work_unit_params const & params)
{
    mangled_ppc("?create_work_unit@c_job_manager@@SA?AVc_jm_work_unit_handle@@ABUs_work_unit_params@@@Z");

    c_jm_work_unit_handle handle;
    unsigned long index = get_internal_data()->acquire_handle();
    if (index != 0xFFFFFFFF)
    {
        handle.m_handle = index;
        c_work_unit * work_unit = get_internal_data()->get_work_unit(index);
        handle.m_work_unit = work_unit;
        work_unit->initialize(params);
    }

    return handle;
};

void c_job_manager::destroy_work_unit(c_jm_work_unit_handle & handle)
{
    mangled_ppc("?destroy_work_unit@c_job_manager@@SAXAAVc_jm_work_unit_handle@@@Z");

    if (handle.valid())
    {
        c_work_unit * work_unit = get_internal_data()->get_work_unit(handle.m_handle);
        work_unit->dispose();
        get_internal_data()->release_handle(handle.m_handle);
        thread_sleep(200);
    }

    handle.m_handle = 0xFFFFFFFF;
};

void c_job_manager::register_block_callback(job_manager_block_callback_t callback)
{
    mangled_ppc("?register_block_callback@c_job_manager@@QAAXP6AXXZ@Z");

    m_block_callback = callback;
};

void c_job_manager::invoke_block_callback(void)
{
    mangled_ppc("?invoke_block_callback@c_job_manager@@QAAXXZ");

    if (m_block_callback)
    {
        m_block_callback();
    }
};

