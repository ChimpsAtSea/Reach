#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\system\\system_identity_xenon.cpp"
/* ---------- headers */

#include "foundation\baselib\system\system_identity_xenon.h"
#include "baselib\system_identity.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"
#include <xtl.h>
#include <xbdm.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_string<22>::k_index_not_found; // "?k_index_not_found@?$s_static_string@$0BG@@@2JB"
// public: static long const s_static_string<22>::k_element_count; // "?k_element_count@?$s_static_string@$0BG@@@2JB"

// void system_global_unique_identifier_create(struct s_system_global_unique_identifier *);
// bool system_global_unique_identifiers_equal(struct s_system_global_unique_identifier const *, struct s_system_global_unique_identifier const *);
// IsEqualGUID;
// void system_get_user_name(char *, long);
// void system_get_machine_name(char *, long);
// public: static long s_static_string<22>::max_length(void);
// public: char const * s_static_string<22>::operator char const *(void) const;
// public: char (& s_static_string<22>::get_buffer(void))[22];

void system_global_unique_identifier_create(s_system_global_unique_identifier * identifier)
{
    mangled_ppc("?system_global_unique_identifier_create@@YAXPAUs_system_global_unique_identifier@@@Z");

    csmemset(identifier, 0, sizeof(s_system_global_unique_identifier));
};

bool system_global_unique_identifiers_equal(s_system_global_unique_identifier const * identifier1, s_system_global_unique_identifier const * identifier2)
{
    mangled_ppc("?system_global_unique_identifiers_equal@@YA_NPBUs_system_global_unique_identifier@@0@Z");

    GUID const * guid1 = reinterpret_cast<GUID const *>(identifier1);
    GUID const * guid2 = reinterpret_cast<GUID const *>(identifier2);
    bool result = false;

    assert_tag_debug_untracked_jul_11_2011(46, identifier1);
    assert_tag_debug_untracked_jul_11_2011(47, identifier2);

    if (!memory_is_zeroed(guid1, sizeof(GUID)) && IsEqualGUID(*guid1, *guid2))
    {
        result = true;
    }

    return result;
};

void system_get_user_name(char * buffer, long buffer_size)
{
    mangled_ppc("?system_get_user_name@@YAXPADJ@Z");

    bool success = false;
    success = system_get_console_user_name(buffer, buffer_size);
    if (!success)
    {
        s_static_string<260> user_name;
        for (long user_index = 0; user_index < XUSER_MAX_COUNT; user_index++)
        {
            if (XUserGetName(user_index, user_name.get_buffer(), user_name.max_length()) == ERROR_SUCCESS)
            {
                csnzprintf(buffer, buffer_size, "pn-%s", user_name.get_string());
                success = true;
                break;
            }
        }
    }

    if (!success)
    {
        csstrnzcpy(buffer, "unknown_user", buffer_size);
    }
};

void system_get_machine_name(char * buffer, long buffer_size)
{
    mangled_ppc("?system_get_machine_name@@YAXPADJ@Z");

    bool success = false;

    {
        DWORD name_length = s_static_string<22>::max_length();
        s_static_string<22> name;
        if (DmGetXboxName(name.get_buffer(), &name_length) == XBDM_NOERR)
        {
            csstrnzcpy(buffer, name, buffer_size);
            success = true;
        }
    }

    if (!success)
    {
        XNADDR address;
        csmemset(&address, 0, sizeof(address));
        XNetGetTitleXnAddr(&address);
        if (!memory_is_zeroed(address.abEnet, sizeof(address.abEnet)))
        {
            csnzprintf(buffer, buffer_size, "%02X%02X%02X%02X%02X%02X", address.abEnet[0], address.abEnet[1], address.abEnet[2], address.abEnet[3], address.abEnet[4], address.abEnet[5]);
            success = true;
        }
    }

    if (!success)
    {
        csstrnzcpy(buffer, "unknown_xenon", buffer_size);
    }
};
