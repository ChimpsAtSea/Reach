#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_resource_cache_interfaces.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_resource_cache_interfaces.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual void * c_tag_resource_cache_file_datum_handler::get_permanent_resource_root_address(long, bool);

void * c_tag_resource_cache_file_datum_handler::get_permanent_resource_root_address(long resource_handle, bool is_optional)
{
    mangled_ppc("?get_permanent_resource_root_address@c_tag_resource_cache_file_datum_handler@@UAAPAXJ_N@Z");

    c_tag_resource_fixup root_address_fixup = get_root_address_fixup(resource_handle);
    c_basic_buffer<void> control_data = get_control_data(resource_handle, is_optional);

    assert_tag_debug_untracked_jul_11_2011(15, root_address_fixup.get_type()==_tag_resource_fixup_control_offset || root_address_fixup.get_type()==_tag_resource_fixup_value);

    void * root_address = get_address_from_fixup(root_address_fixup, control_data, NULL, NULL);

    return root_address;
};

