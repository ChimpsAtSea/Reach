/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_string_id_table.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_globals.h"
#include "omaha\game\multiplayer_definitions.h"
#include "omaha\memory\array.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition megalo_string_id_table_block; // "?megalo_string_id_table_block@@3Us_tag_block_definition@@A"
// struct s_tag_reference_definition global_megalo_string_id_table_reference; // "?global_megalo_string_id_table_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_group megalo_string_id_table_group; // "?megalo_string_id_table_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_megalo_string_id_table_vtable; // "?legacy_megalo_string_id_table_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_megalo_string_id_table_stream_definition; // "?legacy_megalo_string_id_table_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_megalo_string_id_table_xsync_declaration; // "?legacy_megalo_string_id_table_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_megalo_string_id_table_vtable_shim; // "?legacy_megalo_string_id_table_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// long megalo_string_id_table_get_count(void);
// long megalo_string_id_table_get_string_id(long);
// struct s_megalo_string_id_table_definition const * try_and_get_global_megalo_string_id_table(void);
// void megalo_string_id_table_add_to_list(struct array_template<long> *);

long megalo_string_id_table_get_count(void)
{
    mangled_ppc("?megalo_string_id_table_get_count@@YAJXZ");

    s_megalo_string_id_table_definition const * string_id_table = try_and_get_global_megalo_string_id_table();
    long count = 0;
    if (string_id_table)
    {
        count = string_id_table->string_ids.count;
    }

    return count;
};

long megalo_string_id_table_get_string_id(long index)
{
    mangled_ppc("?megalo_string_id_table_get_string_id@@YAJJ@Z");

    s_megalo_string_id_table_definition const * megalo_string_id_table = try_and_get_global_megalo_string_id_table();
    long megalo_string_id = NONE;
    if (megalo_string_id_table && index >= 0 && index < megalo_string_id_table->string_ids.count)
    {
        megalo_string_id = *static_cast<long *>(tag_block_get_element_with_size(&megalo_string_id_table->string_ids, index, sizeof(long)));
    }

    return megalo_string_id;
};

s_megalo_string_id_table_definition const * try_and_get_global_megalo_string_id_table(void)
{
    mangled_ppc("?try_and_get_global_megalo_string_id_table@@YAPBUs_megalo_string_id_table_definition@@XZ");

    s_game_globals const * globals = static_cast<s_game_globals const *>(tag_get(GAME_GLOBALS_DEFINITION_TAG, global_scenario_game_globals_index_get()));
    long string_id_table_index;
    s_multiplayer_runtime_globals_definition const * runtime_data;
    s_multiplayer_globals_definition const * multiplayer_globals = globals->multiplayer_globals.index != NONE ? static_cast<s_multiplayer_globals_definition const *>(tag_get(k_multiplayer_globals_definition_tag, globals->multiplayer_globals.index)) : NULL;
    runtime_data = multiplayer_globals_try_and_get_runtime_data(multiplayer_globals);
    string_id_table_index = runtime_data ? runtime_data->megalo_string_id_table.index : NONE;

    return string_id_table_index == NONE ? NULL : static_cast<s_megalo_string_id_table_definition const *>(tag_get(k_megalo_string_id_table_definition_tag, string_id_table_index));
};

void megalo_string_id_table_add_to_list(array_template<long> * list)
{
    mangled_ppc("?megalo_string_id_table_add_to_list@@YAXPAU?$array_template@J@@@Z");

    s_megalo_string_id_table_definition const * string_id_table = try_and_get_global_megalo_string_id_table();
    if (string_id_table)
    {
        list->append(static_cast<long const *>(string_id_table->string_ids.address), string_id_table->string_ids.count);
    }
};

