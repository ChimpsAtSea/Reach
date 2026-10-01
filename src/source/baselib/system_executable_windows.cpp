/* ---------- headers */

#include "baselib\system_executable_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char k_read_only_data_start;
char k_read_only_data_end;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool system_executable_is_address_constant_and_static(void const volatile *);

bool system_executable_is_address_constant_and_static(void const volatile * address)
{
    mangled_ppc("?system_executable_is_address_constant_and_static@@YA_NPDX@Z");
    return address >= &k_read_only_data_start && address <= &k_read_only_data_end;
};

