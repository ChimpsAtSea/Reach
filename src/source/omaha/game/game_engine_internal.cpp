/* ---------- headers */

#include "omaha\game\game_engine_internal.h"
#include "foundation\baselib\multithreading\synchronization\critical_section_windows.h"
#include "omaha\multithreading\synchronization_spasm.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_game_engine_scope_lock::c_game_engine_scope_lock(void);
// public: c_game_engine_scope_lock::~c_game_engine_scope_lock(void);

c_game_engine_scope_lock::c_game_engine_scope_lock()
{
    mangled_ppc("??0c_game_engine_scope_lock@@QAA@XZ");

    critical_section_enter_internal(g_omaha_critical_sections[k_crit_section_game_engine], _critical_section_non_recursive);
};

c_game_engine_scope_lock::~c_game_engine_scope_lock()
{
    mangled_ppc("??1c_game_engine_scope_lock@@QAA@XZ");

    critical_section_leave_internal(g_omaha_critical_sections[k_crit_section_game_engine], _critical_section_non_recursive);
};

