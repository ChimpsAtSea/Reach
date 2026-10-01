#pragma once
#ifndef __EVENT_LISTENER_H__
#define __EVENT_LISTENER_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

enum e_event_category;
enum e_event_level;

enum e_event_listener
{
    k_event_listener_invalid = -1,
};

/* ---------- definitions */

class c_event_listener
{
public:
    c_event_listener(void);
    c_event_listener(char const * category_name);
    ~c_event_listener(void);

    virtual void handle_event(e_event_level level, char const * event_text) = 0; // vtable slot 0 (H3 name)

    char const * get_category_name(void) const;
    void set_category_name(char const * category_name);
    e_event_category get_category_index(void) const;
    e_event_listener get_listener_index(void) const;
    void set_category_index(e_event_category category_index);
    void set_listener_index(e_event_listener listener_index);
    void register_listener(void);
    void unregister_listener(void);

protected:
    s_static_string<64> m_category_name;
    e_event_category m_category_index;
    e_event_listener m_listener_index;
};
static_assert(sizeof(c_event_listener) == 0x4C, "c_event_listener");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_LISTENER_H__

