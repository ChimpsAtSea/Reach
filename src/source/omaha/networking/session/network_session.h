#ifndef __NETWORK_SESSION_H__
#define __NETWORK_SESSION_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

long const k_network_maximum_sessions = 4;

/* ---------- definitions */

struct s_transport_secure_identifier;

// $TODO layout (H3 size 0x75998)
class c_network_session
{
public:
    bool get_session_id(s_transport_secure_identifier * session_id) const;
    bool time_exists() const;
    unsigned long time_get() const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __NETWORK_SESSION_H__

