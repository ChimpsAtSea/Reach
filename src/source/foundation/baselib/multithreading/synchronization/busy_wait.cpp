#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\busy_wait.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\busy_wait.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_busy_wait busy_wait_declare(long, struct s_busy_wait_definition const *);
// public: c_busy_wait_timer::c_busy_wait_timer(struct s_busy_wait);
// public: c_busy_wait_timer::~c_busy_wait_timer(void);

s_busy_wait busy_wait_declare(long synchronization_group_index, s_busy_wait_definition const * definition)
{
    mangled_ppc("?busy_wait_declare@@YA?AUs_busy_wait@@JPBUs_busy_wait_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(22, definition);
    assert_tag_debug_untracked_jul_11_2011(23, definition->name);

    s_busy_wait busy_wait;
    busy_wait.object_id = synchronization_declare_busy_wait(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(26, busy_wait.object_id != NONE, "too many busy-waits, increase k_maximum_busy_waits");

    return busy_wait;
};

c_busy_wait_timer::c_busy_wait_timer(s_busy_wait busy_wait)
{
    mangled_ppc("??0c_busy_wait_timer@@QAA@Us_busy_wait@@@Z");

    m_busy_wait = busy_wait;
};

c_busy_wait_timer::~c_busy_wait_timer(void)
{
    mangled_ppc("??1c_busy_wait_timer@@QAA@XZ");
};
