#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_listener.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_listener.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\errors\events\event_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_event_listener::c_event_listener(void);
// public: c_event_listener::c_event_listener(char const *);
// public: c_event_listener::~c_event_listener(void);
// public: char const * c_event_listener::get_category_name(void) const;
// public: void c_event_listener::set_category_name(char const *);
// public: enum e_event_category c_event_listener::get_category_index(void) const;
// public: enum e_event_listener c_event_listener::get_listener_index(void) const;
// public: void c_event_listener::set_category_index(enum e_event_category);
// public: void c_event_listener::set_listener_index(enum e_event_listener);
// public: void c_event_listener::register_listener(void);
// public: void c_event_listener::unregister_listener(void);

c_event_listener::c_event_listener(void)
{
    mangled_ppc("??0c_event_listener@@QAA@XZ");

    m_category_name.clear();
    m_category_index = k_event_category_invalid;
    m_listener_index = k_event_listener_invalid;
};

c_event_listener::c_event_listener(char const * category_name)
{
    mangled_ppc("??0c_event_listener@@QAA@PBD@Z");

    m_category_name.set(category_name);
    m_category_index = k_event_category_invalid;
    m_listener_index = k_event_listener_invalid;
};

c_event_listener::~c_event_listener(void)
{
    mangled_ppc("??1c_event_listener@@QAA@XZ");

    if (m_listener_index != k_event_listener_invalid)
    {
        unregister_listener();
    }
};

char const * c_event_listener::get_category_name(void) const
{
    mangled_ppc("?get_category_name@c_event_listener@@QBAPBDXZ");

    return m_category_name.get_string();
};

void c_event_listener::set_category_name(char const * category_name)
{
    mangled_ppc("?set_category_name@c_event_listener@@QAAXPBD@Z");

    bool registered = m_listener_index != k_event_listener_invalid;

    assert_tag_debug_untracked_jul_11_2011(54, category_name!=NULL);

    if (registered)
    {
        unregister_listener();
    }

    m_category_name.set(category_name);

    if (registered)
    {
        register_listener();
    }
};

e_event_category c_event_listener::get_category_index(void) const
{
    mangled_ppc("?get_category_index@c_event_listener@@QBA?AW4e_event_category@@XZ");

    return m_category_index;
};

e_event_listener c_event_listener::get_listener_index(void) const
{
    mangled_ppc("?get_listener_index@c_event_listener@@QBA?AW4e_event_listener@@XZ");

    return m_listener_index;
};

void c_event_listener::set_category_index(e_event_category category_index)
{
    mangled_ppc("?set_category_index@c_event_listener@@QAAXW4e_event_category@@@Z");

    m_category_index = category_index;
};

void c_event_listener::set_listener_index(e_event_listener listener_index)
{
    mangled_ppc("?set_listener_index@c_event_listener@@QAAXW4e_event_listener@@@Z");

    m_listener_index = listener_index;
};

void c_event_listener::register_listener(void)
{
    mangled_ppc("?register_listener@c_event_listener@@QAAXXZ");

    bool const registered = events_register_listener(this);
    dassert_tag_debug_untracked_jul_11_2011(98, registered, "tried to register an event listener before event system was initialized");
};

void c_event_listener::unregister_listener(void)
{
    mangled_ppc("?unregister_listener@c_event_listener@@QAAXXZ");

    events_unregister_listener(this);
};

