/* ---------- headers */

#include "blamlib\megalogamengine_map_permissions.h"
#include <string.h>
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_megalogamengine_map_permissions::initialize(void);
// public: bool c_megalogamengine_map_permissions::is_valid(void) const;
// public: void c_megalogamengine_map_permissions::encode(class c_bitstream *) const;
// public: void c_megalogamengine_map_permissions::decode(class c_bitstream *);
// public: bool c_megalogamengine_map_permissions::is_default_map_allowed(enum e_map_id) const;
// private: bool c_megalogamengine_map_permissions::map_in_exception_list(enum e_map_id) const;
// public: long c_static_stack<short, 32>::count(void) const;
// public: void c_static_stack<short, 32>::resize(long);
// public: short const & c_static_stack<short, 32>::operator[](long) const;
// public: short & c_static_stack<short, 32>::operator[](long);
// public: bool c_static_stack<short, 32>::valid(void) const;
// public: bool c_static_stack<short, 32>::valid(long) const;
// public: void c_bitstream::write_count<32, long>(char const *, long);
// public: long c_bitstream::read_count<32>(char const *);

void c_megalogamengine_map_permissions::initialize(void)
{
    mangled_ppc("?initialize@c_megalogamengine_map_permissions@@QAAXXZ");

    memset(this, 0, sizeof(*this));
    m_default_permission = true;
};

bool c_megalogamengine_map_permissions::is_valid(void) const
{
    mangled_ppc("?is_valid@c_megalogamengine_map_permissions@@QBA_NXZ");

    return IN_RANGE_INCLUSIVE(m_exception_map_ids.count(), 0, 32);
};

void c_megalogamengine_map_permissions::encode(c_bitstream * packet) const
{
    mangled_ppc("?encode@c_megalogamengine_map_permissions@@QBAXPAVc_bitstream@@@Z");

    packet->write_count<32>("exception-count", m_exception_map_ids.count());
    for (long exception_index = 0; exception_index < m_exception_map_ids.count(); exception_index++)
    {
        packet->write_signed_integer("map-id", m_exception_map_ids[exception_index], 16);
    }
    packet->write_bool("default-permission", m_default_permission);
};

void c_megalogamengine_map_permissions::decode(c_bitstream * packet)
{
    mangled_ppc("?decode@c_megalogamengine_map_permissions@@QAAXPAVc_bitstream@@@Z");

    initialize();
    long exception_count = packet->read_count<32>("exception-count");
    if (VALID_COUNT(exception_count, 32))
    {
        m_exception_map_ids.resize(exception_count);
        for (long exception_index = 0; exception_index < exception_count; exception_index++)
        {
            m_exception_map_ids[exception_index] = static_cast<short>(packet->read_signed_integer("map-id", 16));
        }
        m_default_permission = packet->read_bool("default-permission");
    }
    else
    {
        event_wrapped(_event_error, "megalogamengine:map_permissions: read out-of-range exception count %d", exception_count);
    }
};

bool c_megalogamengine_map_permissions::is_default_map_allowed(e_map_id map_id) const
{
    mangled_ppc("?is_default_map_allowed@c_megalogamengine_map_permissions@@QBA_NW4e_map_id@@@Z");

    bool allowed = m_default_permission;
    if (map_in_exception_list(map_id))
    {
        allowed = !allowed;
    }
    return allowed;
};

bool c_megalogamengine_map_permissions::map_in_exception_list(e_map_id map_id) const
{
    mangled_ppc("?map_in_exception_list@c_megalogamengine_map_permissions@@ABA_NW4e_map_id@@@Z");

    bool result = false;
    for (long exception_index = 0; exception_index < m_exception_map_ids.count(); exception_index++)
    {
        if (m_exception_map_ids[exception_index] == map_id)
        {
            result = true;
            break;
        }
    }
    return result;
};









