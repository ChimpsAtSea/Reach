/* ---------- headers */

#include "baselib\system_exception_windows.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

// platform layout behind the opaque s_exception_information storage (only 0xA68 bytes are filled)
struct s_exception_information_windows
{
    unsigned long thread_id;
    CONTEXT context;
    unsigned long exception_code;
    unsigned long exception_flags;
    void * exception_address;
    unsigned long number_parameters;
    unsigned long exception_information[4];
};
static_assert(sizeof(s_exception_information_windows) == 0xA68, "s_exception_information_windows");
static_assert(sizeof(s_exception_information_windows) <= sizeof(s_exception_information), "s_exception_information_windows");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void system_build_exception_information(struct s_exception_pointers *, struct s_exception_information *);
// unsigned long int_min(int, unsigned long);

void system_build_exception_information(s_exception_pointers * exception_pointers, s_exception_information * exception_information)
{
    mangled_ppc("?system_build_exception_information@@YAXPAUs_exception_pointers@@PAUs_exception_information@@@Z");

    if (exception_information)
    {
        EXCEPTION_POINTERS * pointers = reinterpret_cast<EXCEPTION_POINTERS *>(exception_pointers);
        s_exception_information_windows * information = reinterpret_cast<s_exception_information_windows *>(exception_information);

        csmemset(information, 0, sizeof(*information));
        if (exception_pointers)
        {
            information->thread_id = GetCurrentThreadId();
            information->context = *pointers->ContextRecord;
            information->exception_code = pointers->ExceptionRecord->ExceptionCode;
            information->exception_flags = pointers->ExceptionRecord->ExceptionFlags;
            information->exception_address = pointers->ExceptionRecord->ExceptionAddress;
            if (pointers->ExceptionRecord->ExceptionInformation)
            {
                unsigned long parameter_count = int_min(NUMBEROF(information->exception_information), pointers->ExceptionRecord->NumberParameters);
                information->number_parameters = parameter_count;
                csmemcpy(information->exception_information, pointers->ExceptionRecord->ExceptionInformation, parameter_count * sizeof(unsigned long));
            }
        }
    }
};

