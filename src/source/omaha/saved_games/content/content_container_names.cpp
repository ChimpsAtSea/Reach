#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\content\\content_container_names.cpp"
/* ---------- headers */

#include "omaha\saved_games\content\content_container_names.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void content_build_container_name_from_raw_container_name(class c_static_string<43> *, char const *const);
// void content_build_raw_container_name_from_container_name(char *const, class c_static_string<43> const *);
// void content_extract_type_prefix_from_container_name(class c_static_string<43> *, class c_static_string<43> const *);
// void content_extract_encoded_portion_from_container_name(class s_static_string<42> *, class c_static_string<43> const *);
// void content_build_container_name_from_type_prefix_and_encoded_portion(class c_static_string<43> *, class c_static_string<43> const *, class s_static_string<42> const *);
// public: void s_static_string<43>::null_terminate(void);
// public: bool s_static_string<43>::substring(long, long, class s_static_string<43> *) const;
// public: char (& s_static_string<43>::get_buffer(void))[43];
// public: void s_static_string<42>::set(char const *);

void content_build_container_name_from_raw_container_name(c_static_string<43> * out_container_name, char const * const raw_container_name)
{
    mangled_ppc("?content_build_container_name_from_raw_container_name@@YAXPAV?$c_static_string@$0CL@@@QBD@Z");

    out_container_name->set_bounded(raw_container_name, k_content_container_name_length_without_null);
    unsigned char * buffer = reinterpret_cast<unsigned char *>(out_container_name->get_buffer());
    buffer[0] &= 0x7F;
    out_container_name->null_terminate();
};

void content_build_raw_container_name_from_container_name(char * const out_raw_container_name, c_static_string<43> const * container_name)
{
    mangled_ppc("?content_build_raw_container_name_from_container_name@@YAXQADPBV?$c_static_string@$0CL@@@@Z");

    memcpy(out_raw_container_name, container_name->get_string(), k_content_container_name_length_without_null);
};

void content_extract_type_prefix_from_container_name(c_static_string<43> * out_type_prefix, c_static_string<43> const * container_name)
{
    mangled_ppc("?content_extract_type_prefix_from_container_name@@YAXPAV?$c_static_string@$0CL@@@PBV1@@Z");

    container_name->substring(0, k_content_container_name_type_prefix_length_without_null, out_type_prefix);
};

void content_extract_encoded_portion_from_container_name(s_static_string<42> * out_encoded_portion, c_static_string<43> const * container_name)
{
    mangled_ppc("?content_extract_encoded_portion_from_container_name@@YAXPAV?$s_static_string@$0CK@@@PBV?$c_static_string@$0CL@@@@Z");

    long container_name_length = container_name->length();
    long chars_of_encoded_data = container_name_length - k_content_container_name_type_prefix_length_without_null;
    out_encoded_portion->clear();
    if (chars_of_encoded_data < 0 || chars_of_encoded_data > k_content_container_name_encoded_portion_length - 1)
    {
        event_wrapped(_event_error, "content:filenames: Filename %s doesn't have a valid encoded portion.", container_name->get_string());
    }
    else
    {
        char const * encoded_data = container_name->get_string();
        encoded_data += k_content_container_name_type_prefix_length_without_null;
        assert_tag_debug_untracked_jul_11_2011(82, chars_of_encoded_data < out_encoded_portion->max_length());
        out_encoded_portion->set(encoded_data);
    }
};

void content_build_container_name_from_type_prefix_and_encoded_portion(c_static_string<43> * out_container_name, c_static_string<43> const * type_prefix_string, s_static_string<42> const * encoded_portion)
{
    mangled_ppc("?content_build_container_name_from_type_prefix_and_encoded_portion@@YAXPAV?$c_static_string@$0CL@@@PBV1@PBV?$s_static_string@$0CK@@@@Z");

    char * encoded_portion_buffer = out_container_name->get_buffer();
    encoded_portion_buffer += k_content_container_name_type_prefix_length_without_null;
    assert_tag_debug_untracked_jul_11_2011(110, type_prefix_string->length()==k_content_container_name_type_prefix_length_without_null);
    out_container_name->set(type_prefix_string->get_string());
    csstrnzcpy(encoded_portion_buffer, encoded_portion->get_string(), k_content_container_name_encoded_portion_length);
};

