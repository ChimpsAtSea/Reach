#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_resource_handle_persist.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_resource_handle_persist.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\persist.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\chunk_persist_stream_helpers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool save_or_load_resource_handle_datum(class c_basic_buffer<void>, struct s_tag_persistent_identifier *, class c_persist_stream *, enum e_chunk_archive_action);
// bool save_resource_handle_datum(class c_basic_buffer<void const>, struct s_tag_resource_definition const *, class c_persist_stream *);
// bool load_resource_handle_datum(class c_basic_buffer<void>, struct s_tag_resource_definition const **, class c_tag_resource_definition_dictionary *, class c_persist_stream *);
// class c_raw_buffer_chunk_section_archiver make_raw_section_archiver<struct s_tag_persistent_identifier>(char const *, unsigned long, long, struct s_tag_persistent_identifier *);

bool save_or_load_resource_handle_datum(c_basic_buffer<void> datum, s_tag_persistent_identifier * persistent_identifier, c_persist_stream * persist_stream, e_chunk_archive_action action)
{
    mangled_ppc("?save_or_load_resource_handle_datum@@YA_NV?$c_basic_buffer@X@@PAUs_tag_persistent_identifier@@PAVc_persist_stream@@W4e_chunk_archive_action@@@Z");

    s_persist_archiver_holder section_archivers[] =
    {
        s_persist_archiver_holder::make(make_raw_buffer_archiver("resource handle datum layout", 'rhdl', 0, datum)),
        s_persist_archiver_holder::make(make_raw_section_archiver("resource handle datum identifier", 'rhdi', 0, persistent_identifier))
    };
    c_chunk_with_sections_archiver section_archiver("resource handle datum structure archiver", 'rhds', 0, section_archivers);
    c_typed_pointer_holder null_holder(static_cast<void *>(NULL));

    return save_or_restore_with_archiver(&section_archiver, null_holder, persist_stream, action);
};

bool save_resource_handle_datum(c_basic_buffer<void const> datum, s_tag_resource_definition const * resource_definition, c_persist_stream * persist_stream)
{
    mangled_ppc("?save_resource_handle_datum@@YA_NV?$c_basic_buffer@$$CBX@@PBUs_tag_resource_definition@@PAVc_persist_stream@@@Z");

    s_tag_persistent_identifier persistent_identifier = resource_definition->get_persistent_identifier();

    return save_or_load_resource_handle_datum(c_basic_buffer<void>(const_cast<void *>(datum.begin()), datum.size()), &persistent_identifier, persist_stream, _chunk_archive_action_save);
};

bool load_resource_handle_datum(c_basic_buffer<void> datum, s_tag_resource_definition const ** out_resource_definition, c_tag_resource_definition_dictionary * dictionary, c_persist_stream * persist_stream)
{
    mangled_ppc("?load_resource_handle_datum@@YA_NV?$c_basic_buffer@X@@PAPBUs_tag_resource_definition@@PAVc_tag_resource_definition_dictionary@@PAVc_persist_stream@@@Z");

    s_tag_persistent_identifier persistent_identifier;
    assert_tag_debug_untracked_jul_11_2011(57, buffer_in_buffer(c_const_buffer(out_resource_definition, out_resource_definition + 1), datum));

    bool success = false;
    if (save_or_load_resource_handle_datum(datum, &persistent_identifier, persist_stream, _chunk_archive_action_load))
    {
        s_tag_resource_definition const * resource_definition = dictionary->lookup_resource_definition(persistent_identifier);
        if (resource_definition)
        {
            *out_resource_definition = resource_definition;
            success = true;
        }
    }

    return success;
};

