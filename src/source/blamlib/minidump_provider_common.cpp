/* ---------- headers */

#include "blamlib\minidump_provider_common.h"
#include "blamlib\xenon_minidump_endian.h"
#include "core\corelib\cseries\cseries_string.h"

#include <xtl.h>
#include <time.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

unsigned long const c_minidump_provider_common::k_minidump_header_version;
int const c_minidump_provider_common::k_minidump_header_signature;
char const * const c_minidump_provider_common::k_system_version_string = "Xenon";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// protected: static unsigned long const c_minidump_provider_common::k_minidump_header_version; // "?k_minidump_header_version@c_minidump_provider_common@@1KB"
// protected: static int const c_minidump_provider_common::k_minidump_header_signature; // "?k_minidump_header_signature@c_minidump_provider_common@@1HB"
// protected: static char const *const c_minidump_provider_common::k_system_version_string; // "?k_system_version_string@c_minidump_provider_common@@1PBDB"

// public: c_minidump_provider_common::c_minidump_provider_common(void);
// merged_836DCCA8;
// public: c_minidump_provider_interface::c_minidump_provider_interface(void);
// public: virtual void c_minidump_provider_common::get_minidump_header(struct _MINIDUMP_HEADER *, unsigned long);
// public: virtual void c_minidump_provider_common::get_misc_information(struct _MINIDUMP_MISC_INFO *);
// public: virtual void c_minidump_provider_common::get_system_information(struct _MINIDUMP_SYSTEM_INFO *);
// public: virtual void c_minidump_provider_common::get_system_version_string(char *, unsigned long);
// time;

c_minidump_provider_common::c_minidump_provider_common()
{
    mangled_ppc("??0c_minidump_provider_common@@QAA@XZ");
};

void c_minidump_provider_common::get_minidump_header(_MINIDUMP_HEADER * header, unsigned long number_of_streams)
{
    mangled_ppc("?get_minidump_header@c_minidump_provider_common@@UAAXPAU_MINIDUMP_HEADER@@K@Z");

    if (header)
    {
        time_t current_time;
        time(&current_time);

        header->Signature = k_minidump_header_signature;
        header->Version = k_minidump_header_version;
        header->NumberOfStreams = number_of_streams;
        header->StreamDirectoryRva = sizeof(MINIDUMP_HEADER);
        header->CheckSum = 0;
        header->TimeDateStamp = static_cast<unsigned int>(current_time);
        header->Flags = 0;
    }
};

void c_minidump_provider_common::get_misc_information(_MINIDUMP_MISC_INFO * misc_info)
{
    mangled_ppc("?get_misc_information@c_minidump_provider_common@@UAAXPAU_MINIDUMP_MISC_INFO@@@Z");

    if (misc_info)
    {
        misc_info->SizeOfInfo = sizeof(MINIDUMP_MISC_INFO);
        misc_info->Flags1 = MINIDUMP_MISC1_PROCESS_ID;
        misc_info->ProcessId = 0xA5C0B46F;
        misc_info->ProcessCreateTime = 0;
        misc_info->ProcessUserTime = 0;
        misc_info->ProcessKernelTime = 0;
    }
};

void c_minidump_provider_common::get_system_information(_MINIDUMP_SYSTEM_INFO * system_info)
{
    mangled_ppc("?get_system_information@c_minidump_provider_common@@UAAXPAU_MINIDUMP_SYSTEM_INFO@@@Z");

    if (system_info)
    {
        system_info->ProcessorArchitecture = PROCESSOR_ARCHITECTURE_PPC;
        system_info->ProcessorLevel = 1;
        system_info->ProcessorRevision = 1;
        system_info->NumberOfProcessors = 2;
        system_info->ProductType = 1;
        system_info->MajorVersion = 5;
        system_info->MinorVersion = 1;
        system_info->BuildNumber = 2920;
        system_info->PlatformId = 2;
        system_info->SuiteMask = 0;
        system_info->Cpu.OtherCpuInfo.ProcessorFeatures[0] = 0;
        system_info->Cpu.OtherCpuInfo.ProcessorFeatures[1] = 0;
        system_info->CSDVersionRva = 0;
    }
};

void c_minidump_provider_common::get_system_version_string(char * buffer, unsigned long buffer_size)
{
    mangled_ppc("?get_system_version_string@c_minidump_provider_common@@UAAXPADK@Z");

    if (buffer)
    {
        csstrnzcpy(buffer, k_system_version_string, buffer_size);
    }
};

