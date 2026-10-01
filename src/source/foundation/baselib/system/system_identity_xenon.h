#pragma once
#ifndef __SYSTEM_IDENTITY_XENON_H__
#define __SYSTEM_IDENTITY_XENON_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_system_global_unique_identifier
{
    unsigned char data[16];
};
static_assert(sizeof(s_system_global_unique_identifier) == 0x10, "s_system_global_unique_identifier");

/* ---------- prototypes */

void system_global_unique_identifier_create(s_system_global_unique_identifier * identifier);
bool system_global_unique_identifiers_equal(s_system_global_unique_identifier const * identifier1, s_system_global_unique_identifier const * identifier2);
void system_get_user_name(char * buffer, long buffer_size);
void system_get_machine_name(char * buffer, long buffer_size);

/* ---------- globals */

/* ---------- public code */

#endif // __SYSTEM_IDENTITY_XENON_H__

