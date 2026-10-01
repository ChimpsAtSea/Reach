#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_runtime_codecs.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_runtime_codecs.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\cache_file_eslib_codec.h"
#include "omaha\cache\cache_file_xor_codec.h"
#include "omaha\tag_files\tag_group_definitions.h"

/* ---------- constants */

/* ---------- definitions */

struct s_cache_file_runtime_decompressor_table_entry
{
    s_tag_persistent_identifier const * identifier; // 0x0
    c_cache_file_decompressor_service * (*get_decompressor_service_proc)(void); // 0x4
};
static_assert(sizeof(s_cache_file_runtime_decompressor_table_entry) == 0x8, "s_cache_file_runtime_decompressor_table_entry");

/* ---------- prototypes */

/* ---------- globals */

static s_cache_file_runtime_decompressor_table_entry const k_runtime_decompressor_table[] =
{
    { &k_xor_codec_identifier, get_xor_cache_file_runtime_decompressor_service },
    { &k_eslib_codec_identifier, get_eslib_cache_file_runtime_decompressor_service },
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual class c_cache_file_decompressor_service * c_cache_file_runtime_decompressor_registry::find_decompressor_service(struct s_tag_persistent_identifier const &);
// public: virtual long c_cache_file_runtime_decompressor_registry::get_decompressor_service_count(void);
// public: virtual struct s_tag_persistent_identifier c_cache_file_runtime_decompressor_registry::get_decompressor_service_identifier(long);

c_cache_file_decompressor_service * c_cache_file_runtime_decompressor_registry::find_decompressor_service(s_tag_persistent_identifier const & decompressor_identifier)
{
    mangled_ppc("?find_decompressor_service@c_cache_file_runtime_decompressor_registry@@UAAPAVc_cache_file_decompressor_service@@ABUs_tag_persistent_identifier@@@Z");

    c_cache_file_decompressor_service * runtime_decompressor_service = 0;
    for (long runtime_decompressor_index = 0; runtime_decompressor_index < NUMBEROF(k_runtime_decompressor_table); runtime_decompressor_index++)
    {
        if (tag_persistent_identifiers_equal(decompressor_identifier, *k_runtime_decompressor_table[runtime_decompressor_index].identifier))
        {
            runtime_decompressor_service = k_runtime_decompressor_table[runtime_decompressor_index].get_decompressor_service_proc();
        }
    }

    return runtime_decompressor_service;
};

long c_cache_file_runtime_decompressor_registry::get_decompressor_service_count(void)
{
    mangled_ppc("?get_decompressor_service_count@c_cache_file_runtime_decompressor_registry@@UAAJXZ");

    return NUMBEROF(k_runtime_decompressor_table);
};

s_tag_persistent_identifier c_cache_file_runtime_decompressor_registry::get_decompressor_service_identifier(long decompressor_service_index)
{
    mangled_ppc("?get_decompressor_service_identifier@c_cache_file_runtime_decompressor_registry@@UAA?AUs_tag_persistent_identifier@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(48, VALID_INDEX(decompressor_service_index, NUMBEROF(k_runtime_decompressor_table)));

    return *k_runtime_decompressor_table[decompressor_service_index].identifier;
};
