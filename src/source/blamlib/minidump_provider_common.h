#pragma once
#ifndef __MINIDUMP_PROVIDER_COMMON_H__
#define __MINIDUMP_PROVIDER_COMMON_H__

/* ---------- headers */

#include "omaha\cseries\minidump_writer.h"

/* ---------- constants */

/* ---------- definitions */

class c_minidump_provider_common :
    public c_minidump_provider_interface
{
public:
    c_minidump_provider_common();

    virtual void get_minidump_header(_MINIDUMP_HEADER * header, unsigned long number_of_streams);
    virtual void get_misc_information(_MINIDUMP_MISC_INFO * misc_info);
    virtual void get_system_information(_MINIDUMP_SYSTEM_INFO * system_info);
    virtual void get_system_version_string(char * buffer, unsigned long buffer_size);

protected:
    static unsigned long const k_minidump_header_version = 0x600EA793;
    static int const k_minidump_header_signature = 0x504D444D; // 'PMDM'
    static char const * const k_system_version_string;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MINIDUMP_PROVIDER_COMMON_H__

