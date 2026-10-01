#pragma once
#ifndef __CSERIES_SECURITY_XENON_H__
#define __CSERIES_SECURITY_XENON_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct s_security_title_hash
{
    unsigned char data[20]; // 0x0
};
static_assert(sizeof(s_security_title_hash) == 0x14, "s_security_title_hash");

/* ---------- prototypes */

void security_generate_title_hash(void * data, long data_size, bool unknown, s_security_title_hash * out_hash);
void security_run_unit_tests(void);

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_SECURITY_XENON_H__

