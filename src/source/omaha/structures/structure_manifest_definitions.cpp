#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\structures\\structure_manifest_definitions.cpp"
/* ---------- headers */

#include "omaha\structures\structure_manifest_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\structures\structure_bsp_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition structure_manifest_build_identifier_struct; // "?structure_manifest_build_identifier_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition structure_manifest_struct; // "?structure_manifest_struct@@3Us_tag_struct_definition@@A"

// struct s_structure_manifest_bsp_definition const * structure_manifest_find_bsp_manifest(struct s_structure_manifest_definition const *, char const *);
// void structure_manifest_build_identifier_initialize(struct s_structure_manifest_build_identifier_definition *);
// bool structure_manifest_build_identifiers_match(struct s_structure_manifest_build_identifier_definition const *, struct s_structure_manifest_build_identifier_definition const *);
// char const * structure_manifest_build_content_source_structure_seam_path(enum e_scenario_content_source, char const *, char *, long);
// char const * structure_manifest_build_content_source_bsp_path(enum e_scenario_content_source, char const *, char *, long);
// char const * structure_manifest_build_content_source_structure_design_path(enum e_scenario_content_source, char const *, char *, long);
// char const * structure_manifest_build_content_source_lighting_info_tag_path(enum e_scenario_content_source, char const *, char *, long);

s_structure_manifest_bsp_definition const * structure_manifest_find_bsp_manifest(s_structure_manifest_definition const * manifest, char const * bsp_name)
{
    mangled_ppc("?structure_manifest_find_bsp_manifest@@YAPBUs_structure_manifest_bsp_definition@@PBUs_structure_manifest_definition@@PBD@Z");

    char const * c = bsp_name;
    s_structure_manifest_bsp_definition const * result = NULL;
    while (*c)
    {
        if (*c == '\\')
        {
            bsp_name = c + 1;
        }
        c++;
    }

    for (long bsp_index = 0; bsp_index < manifest->bsp_manifest.count; bsp_index++)
    {
        s_structure_manifest_bsp_definition const * bsp_manifest = static_cast<s_structure_manifest_bsp_definition const *>(tag_block_get_element_with_size(&manifest->bsp_manifest, bsp_index, sizeof(s_structure_manifest_bsp_definition)));
        if (csstricmp(bsp_manifest->bsp_name, bsp_name) == 0)
        {
            result = bsp_manifest;
            break;
        }
    }

    return result;
};

void structure_manifest_build_identifier_initialize(s_structure_manifest_build_identifier_definition * build_identifier)
{
    mangled_ppc("?structure_manifest_build_identifier_initialize@@YAXPAUs_structure_manifest_build_identifier_definition@@@Z");

    build_identifier->build_index = NONE;
    build_identifier->structure_importer_version = structure_bsp_get_import_version();
    system_global_unique_identifier_create(&build_identifier->manifest_id);
};

bool structure_manifest_build_identifiers_match(s_structure_manifest_build_identifier_definition const * build_identifier0, s_structure_manifest_build_identifier_definition const * build_identifier1)
{
    mangled_ppc("?structure_manifest_build_identifiers_match@@YA_NPBUs_structure_manifest_build_identifier_definition@@0@Z");

    return build_identifier0->build_index == build_identifier1->build_index && system_global_unique_identifiers_equal(&build_identifier0->manifest_id, &build_identifier1->manifest_id);
};

char const * structure_manifest_build_content_source_structure_seam_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size)
{
    mangled_ppc("?structure_manifest_build_content_source_structure_seam_path@@YAPBDW4e_scenario_content_source@@PBDPADJ@Z");

    char const * sub_directory = scenario_content_source_sub_directory_get(content_source);
    char const * result = path;
    if (sub_directory)
    {
        char const * c = path;
        char const * slash = NULL;
        while (*c)
        {
            if (*c == '\\')
            {
                slash = c;
            }
            c++;
        }

        if (slash)
        {
            unsigned long length = address_from_pointer(slash) - address_from_pointer(path);
            char director_buffer[1024];
            assert_tag_debug_untracked_jul_11_2011(126, length+1<NUMBEROF(director_buffer));
            memcpy(director_buffer, path, length);
            director_buffer[length] = 0;
            csnzprintf(buffer, buffer_size, "%s\\%s\\%s", director_buffer, sub_directory, slash + 1);
        }
        else
        {
            csnzprintf(buffer, buffer_size, "%s\\%s", sub_directory, path);
        }

        result = buffer;
    }

    return result;
};

char const * structure_manifest_build_content_source_bsp_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size)
{
    mangled_ppc("?structure_manifest_build_content_source_bsp_path@@YAPBDW4e_scenario_content_source@@PBDPADJ@Z");

    return structure_manifest_build_content_source_structure_seam_path(content_source, path, buffer, buffer_size);
};

char const * structure_manifest_build_content_source_structure_design_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size)
{
    mangled_ppc("?structure_manifest_build_content_source_structure_design_path@@YAPBDW4e_scenario_content_source@@PBDPADJ@Z");

    return structure_manifest_build_content_source_structure_seam_path(content_source, path, buffer, buffer_size);
};

char const * structure_manifest_build_content_source_lighting_info_tag_path(e_scenario_content_source content_source, char const * path, char * buffer, long buffer_size)
{
    mangled_ppc("?structure_manifest_build_content_source_lighting_info_tag_path@@YAPBDW4e_scenario_content_source@@PBDPADJ@Z");

    return structure_manifest_build_content_source_structure_seam_path(content_source, path, buffer, buffer_size);
};

