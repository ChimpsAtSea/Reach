#pragma once
#ifndef __TRANSPORT_SECURITY_H__
#define __TRANSPORT_SECURITY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_transport_secure_identifier
{
    unsigned char data[8];
};
static_assert(sizeof(s_transport_secure_identifier) == 0x8, "s_transport_secure_identifier");

/* ---------- prototypes */

extern void transport_secure_random(long random_length, unsigned char * random_data);

/* ---------- globals */

/* ---------- public code */

#endif // __TRANSPORT_SECURITY_H__

