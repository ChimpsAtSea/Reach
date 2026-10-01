#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_tag_resource_location_handler.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_tag_resource_location_handler.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cache\cache_file_bulk_reader.h"
#include "omaha\cache\cache_file_tag_resource_checksum.h"
#include "omaha\cache\cache_file_tag_resource_location_table.h"
#include "omaha\cache\security_functions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

bool allow_insecure_resources = true;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool allow_insecure_resources; // "?allow_insecure_resources@@3_NA"

// public: void c_cache_file_tag_resource_location_handler::initialize_for_new_map(class c_cache_file_resource_uber_location_table const *);
// public: void c_cache_file_tag_resource_location_handler::dispose_from_old_map(void);
// public: virtual bool c_cache_file_tag_resource_location_handler::get_location_sub_location(struct s_tag_resource_location_handle_struct *, struct s_indirect_cache_file_sub_location *);
// public: virtual unsigned long c_cache_file_tag_resource_location_handler::get_location_memory_size(struct s_tag_resource_location_handle_struct *);
// public: virtual bool c_cache_file_tag_resource_location_handler::try_to_get_location_checksum(struct s_tag_resource_location_handle_struct *, struct s_cache_file_resource_checksum *);
// public: virtual unsigned __int64 c_cache_file_tag_resource_location_handler::get_location_indirect_identifier(struct s_tag_resource_location_handle_struct *);
// public: virtual unsigned long c_cache_file_tag_resource_location_handler::get_location_file_sort_key(struct s_tag_resource_location_handle_struct *);
// public: virtual bool c_cache_file_tag_resource_location_handler::allow_non_checksumed_resources(void);
// public: virtual bool c_cache_file_tag_resource_location_handler::describe_location(struct s_tag_resource_location_handle_struct *, class c_wrapped_array<char>);
// public: void c_cache_file_tag_resource_location_handler::get_physical_location(unsigned __int64, struct s_cache_file_resource_physical_location *) const;
// public: void c_cache_file_tag_resource_location_handler::get_sublocation_table_entry(unsigned __int64, struct s_cache_file_resource_streaming_sublocation_table const **) const;

void c_cache_file_tag_resource_location_handler::initialize_for_new_map(c_cache_file_resource_uber_location_table const * location_table)
{
    mangled_ppc("?initialize_for_new_map@c_cache_file_tag_resource_location_handler@@QAAXPBVc_cache_file_resource_uber_location_table@@@Z");

    m_location_table = location_table;
};

void c_cache_file_tag_resource_location_handler::dispose_from_old_map()
{
    mangled_ppc("?dispose_from_old_map@c_cache_file_tag_resource_location_handler@@QAAXXZ");

    m_location_table = NULL;
};

bool c_cache_file_tag_resource_location_handler::get_location_sub_location(s_tag_resource_location_handle_struct * location_handle, s_indirect_cache_file_sub_location * out_sub_location)
{
    mangled_ppc("?get_location_sub_location@c_cache_file_tag_resource_location_handler@@UAA_NPAUs_tag_resource_location_handle_struct@@PAUs_indirect_cache_file_sub_location@@@Z");

    s_cache_file_resource_physical_location physical_location;
    bool must_succeed = m_location_table->get_physical_location_from_handle(location_handle, &physical_location);
    assert_tag_debug_untracked_jul_11_2011(38, must_succeed);

    out_sub_location->offset = 0;
    out_sub_location->unaligned_read_size = physical_location.file_size;

    s_network_http_request_hash const * checksum = m_location_table->try_to_get_location_checksum_from_handle(location_handle);
    if (checksum)
    {
        out_sub_location->checksum = *checksum;
        out_sub_location->valid_checksum = true;
    }
    else
    {
        out_sub_location->valid_checksum = false;
    }

    out_sub_location->used_storage_size = physical_location.memory_size;
    out_sub_location->decompressor_identifier = m_location_table->get_location_decompressor_identifier(location_handle);

    return true;
};

unsigned long c_cache_file_tag_resource_location_handler::get_location_memory_size(s_tag_resource_location_handle_struct * location_handle)
{
    mangled_ppc("?get_location_memory_size@c_cache_file_tag_resource_location_handler@@UAAKPAUs_tag_resource_location_handle_struct@@@Z");

    s_cache_file_resource_physical_location physical_location;
    bool must_succeed = m_location_table->get_physical_location_from_handle(location_handle, &physical_location);
    assert_tag_debug_untracked_jul_11_2011(66, must_succeed);

    return physical_location.memory_size;
};

bool c_cache_file_tag_resource_location_handler::try_to_get_location_checksum(s_tag_resource_location_handle_struct * location_handle, s_cache_file_resource_checksum * out_checksum)
{
    mangled_ppc("?try_to_get_location_checksum@c_cache_file_tag_resource_location_handler@@UAA_NPAUs_tag_resource_location_handle_struct@@PAUs_cache_file_resource_checksum@@@Z");

    bool valid_checksum = false;
    s_cache_file_resource_checksum const * checksum = m_location_table->try_to_get_location_full_checksum_from_handle(location_handle);
    if (checksum)
    {
        *out_checksum = *checksum;
        valid_checksum = true;
    }

    return valid_checksum;
};

unsigned __int64 c_cache_file_tag_resource_location_handler::get_location_indirect_identifier(s_tag_resource_location_handle_struct * location_handle)
{
    mangled_ppc("?get_location_indirect_identifier@c_cache_file_tag_resource_location_handler@@UAA_KPAUs_tag_resource_location_handle_struct@@@Z");

    return reinterpret_cast<unsigned __int64>(location_handle);
};

unsigned long c_cache_file_tag_resource_location_handler::get_location_file_sort_key(s_tag_resource_location_handle_struct * location_handle)
{
    mangled_ppc("?get_location_file_sort_key@c_cache_file_tag_resource_location_handler@@UAAKPAUs_tag_resource_location_handle_struct@@@Z");

    return m_location_table->get_location_sort_key(location_handle);
};

bool c_cache_file_tag_resource_location_handler::allow_non_checksumed_resources()
{
    mangled_ppc("?allow_non_checksumed_resources@c_cache_file_tag_resource_location_handler@@UAA_NXZ");

    return allow_insecure_resources;
};

//public: virtual bool c_cache_file_tag_resource_location_handler::describe_location(struct s_tag_resource_location_handle_struct *, class c_wrapped_array<char>)
//{
//    mangled_ppc("?describe_location@c_cache_file_tag_resource_location_handler@@UAA_NPAUs_tag_resource_location_handle_struct@@V?$c_wrapped_array@D@@@Z");
//};

void c_cache_file_tag_resource_location_handler::get_physical_location(unsigned __int64 indirect_location_identifier, s_cache_file_resource_physical_location * out_physical_location) const
{
    mangled_ppc("?get_physical_location@c_cache_file_tag_resource_location_handler@@QBAX_KPAUs_cache_file_resource_physical_location@@@Z");

    bool must_succeed = m_location_table->get_physical_location_from_handle(reinterpret_cast<s_tag_resource_location_handle_struct *>(indirect_location_identifier), out_physical_location);
    assert_tag_debug_untracked_jul_11_2011(122, must_succeed);
};

void c_cache_file_tag_resource_location_handler::get_sublocation_table_entry(unsigned __int64 indirect_location_identifier, s_cache_file_resource_streaming_sublocation_table const ** out_sublocation_table) const
{
    mangled_ppc("?get_sublocation_table_entry@c_cache_file_tag_resource_location_handler@@QBAX_KPAPBUs_cache_file_resource_streaming_sublocation_table@@@Z");

    bool must_succeed = m_location_table->get_streaming_sublocation_table_from_handle(reinterpret_cast<s_tag_resource_location_handle_struct *>(indirect_location_identifier), out_sublocation_table);
    assert_tag_debug_untracked_jul_11_2011(133, must_succeed);
};

