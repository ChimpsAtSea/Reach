#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cseries\\cseries_security_xenon.cpp"
/* ---------- headers */

#include "omaha\cseries\cseries_security_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\networking\transport\transport_security.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern "C" int XTitleHash(void const * key_data, unsigned long key_size, void * digest_data, unsigned long digest_size);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void security_generate_title_hash(void *, long, bool, struct s_security_title_hash *);
// void security_run_unit_tests(void);

void security_generate_title_hash(void * data, long data_size, bool unknown, s_security_title_hash * out_hash)
{
    mangled_ppc("?security_generate_title_hash@@YAXPAXJ_NPAUs_security_title_hash@@@Z");

    memset(out_hash, 0, sizeof(s_security_title_hash));
    if (!XTitleHash(data, data_size, out_hash, sizeof(s_security_title_hash)))
    {
        event_wrapped(_event_critical, "networking:security: XTitleHash failed!");
    }
};

void security_run_unit_tests(void)
{
    mangled_ppc("?security_run_unit_tests@@YAXXZ");

    unsigned char salt[16];
    s_security_title_hash hash;

    event_wrapped(_event_message, "networking:security: starting unit tests");

    memset(&hash, 0, sizeof(hash));
    memset(salt, 0, sizeof(salt));
    if (!XTitleHash(salt, sizeof(salt), &hash, sizeof(hash)))
    {
        event_wrapped(_event_error, "networking:security: XTitleHash failed!");
    }
    else
    {
        event_wrapped(_event_message, "networking:security: XTitleHash complete (salt %I64x... %d bytes, hash %I64x...)", *reinterpret_cast<unsigned __int64 const *>(salt), sizeof(salt), *reinterpret_cast<unsigned __int64 const *>(&hash));
    }

    transport_secure_random(sizeof(salt), salt);
    if (!XTitleHash(salt, sizeof(salt), &hash, sizeof(hash)))
    {
        event_wrapped(_event_error, "networking:security: XTitleHash failed!");
    }
    else
    {
        event_wrapped(_event_message, "networking:security: XTitleHash complete (salt %I64x... %d bytes, hash %I64x...)", *reinterpret_cast<unsigned __int64 const *>(salt), sizeof(salt), *reinterpret_cast<unsigned __int64 const *>(&hash));
    }

    for (long test_index = 0; test_index < 8; test_index++)
    {
        s_security_title_hash test_hash;

        memset(&test_hash, 0, sizeof(test_hash));
        if (!XTitleHash(salt, sizeof(salt), &test_hash, sizeof(test_hash)))
        {
            event_wrapped(_event_error, "networking:security: XTitleHash failed!");
        }

        dassert_tag_debug_untracked_jul_11_2011(500, memcmp(&hash, &test_hash, sizeof(hash)) == 0, "security unit test failed!");
    }
};
