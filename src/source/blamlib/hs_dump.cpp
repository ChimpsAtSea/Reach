/* ---------- headers */

#include "blamlib\hs_dump.h"
#include <string.h>
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\hs\hs_scenario_definitions.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\files.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\toolbox\file_helpers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void hs_scenario_report_scripts(void);
// void hs_dump_script_to_file(long, long, struct s_file_reference const *);
// public: c_transacted_file_reference::c_transacted_file_reference(struct s_file_reference const *);
// public: bool c_transacted_file_reference::begin(void);
// public: struct s_file_reference * c_transacted_file_reference::get_file(void);
// public: bool c_transacted_file_reference::commit(void);

void hs_scenario_report_scripts(void)
{
    mangled_ppc("?hs_scenario_report_scripts@@YAXXZ");

    scenario * scenario_definition = global_scenario_get();
    for (long source_file_index = 0; source_file_index < scenario_definition->source_files.count; source_file_index++)
    {
        s_file_reference file;
        hs_source_file * source_file = static_cast<hs_source_file *>(tag_block_get_element_with_size(&scenario_definition->source_files, source_file_index, sizeof(hs_source_file)));
        create_report_file_reference(&file, c_string_builder("%s.hsc", source_file->name), true);
        hs_dump_script_to_file(global_scenario_index_get(), source_file_index, &file);
    }
};

void hs_dump_script_to_file(long scenario_index, long source_file_index, s_file_reference const * file)
{
    mangled_ppc("?hs_dump_script_to_file@@YAXJJPBUs_file_reference@@@Z");

    scenario * scenario_definition = static_cast<scenario *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
    if (VALID_INDEX(source_file_index, scenario_definition->source_files.count))
    {
        hs_source_file * file_definition = static_cast<hs_source_file *>(tag_block_get_element_with_size(&scenario_definition->source_files, source_file_index, sizeof(hs_source_file)));
        char const * source = static_cast<char const *>(tag_data_get_pointer(&file_definition->source, 0, file_definition->source.size));
        c_transacted_file_reference transacted_file(file);
        unsigned long file_error = 0;
        transacted_file.begin();
        if (file_open(transacted_file.get_file(), FLAG(_permission_write_bit), &file_error))
        {
            file_write(transacted_file.get_file(), strlen(source), source);
            file_close(transacted_file.get_file());
        }
        transacted_file.commit();
    }
};

c_transacted_file_reference::c_transacted_file_reference(s_file_reference const * file) :
    m_file_is_open(false)
{
    mangled_ppc("??0c_transacted_file_reference@@QAA@PBUs_file_reference@@@Z");

    file_reference_create(&m_destination_file, NONE);
    file_reference_copy(&m_destination_file, file);
};

bool c_transacted_file_reference::begin(void)
{
    mangled_ppc("?begin@c_transacted_file_reference@@QAA_NXZ");

    bool success = true;
    m_temporary_file = m_destination_file;
    file_create(&m_temporary_file);
    if (success)
    {
        m_file_is_open = true;
    }

    return success;
};

s_file_reference * c_transacted_file_reference::get_file(void)
{
    mangled_ppc("?get_file@c_transacted_file_reference@@QAAPAUs_file_reference@@XZ");

    assert_decomp(m_file_is_open, __FILE_HELPERS_H_FILE__, 153);

    return &m_temporary_file;
};

bool c_transacted_file_reference::commit(void)
{
    mangled_ppc("?commit@c_transacted_file_reference@@QAA_NXZ");

    bool success = false;
    success = true;

    return success;
};

