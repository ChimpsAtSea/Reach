#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\hs\\hs_scenario_definitions.cpp"
/* ---------- headers */

#include "omaha\hs\hs_scenario_definitions.h"
#include "omaha\hs\hs.h"
#include "omaha\cache\cache_file_builder_stream.h"
#include "omaha\memory\byte_swapping.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long const *const const data_array_header_bs_codes; // "?data_array_header_bs_codes@@3QBJB"
// long const *const const syntax_node_bs_codes; // "?syntax_node_bs_codes@@3QBJB"
// struct s_string_list_definition hs_script_types_enum; // "?hs_script_types_enum@@3Us_string_list_definition@@A"
// struct s_string_list_definition hs_types_enum; // "?hs_types_enum@@3Us_string_list_definition@@A"
// struct s_tag_struct_definition hs_scripts_block_struct_definition; // "?hs_scripts_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition hs_scripts_block; // "?hs_scripts_block@@3Us_tag_block_definition@@A"
// struct s_tag_block_definition hs_globals_block; // "?hs_globals_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition hs_globals_block_struct_definition; // "?hs_globals_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition hs_references_block; // "?hs_references_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition hs_references_block_struct_definition; // "?hs_references_block_struct_definition@@3Us_tag_struct_definition@@A"
// char const **hs_source_file_flags_strings; // "?hs_source_file_flags_strings@@3PAPBDA"
// struct s_string_list_definition hs_source_file_flags; // "?hs_source_file_flags@@3Us_string_list_definition@@A"
// struct s_tag_block_definition hs_source_files_block; // "?hs_source_files_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition hs_source_files_block_struct_definition; // "?hs_source_files_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_data_definition hs_old_syntax_data_definition; // "?hs_old_syntax_data_definition@@3Us_tag_data_definition@@A"
// struct s_tag_data_definition hs_string_data_definition; // "?hs_string_data_definition@@3Us_tag_data_definition@@A"
// struct s_tag_block_definition hs_syntax_datum_block; // "?hs_syntax_datum_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition hs_syntax_datum_block_struct_definition; // "?hs_syntax_datum_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition hs_unit_seat_block_struct_definition; // "?hs_unit_seat_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition hs_unit_seat_block; // "?hs_unit_seat_block@@3Us_tag_block_definition@@A"

// bool postprocess_hs_source_file(long, void *, bool);
// void write_hs_syntax_data_to_cache_file(long, struct s_tag_block *, struct s_cache_file_builder_stream_context const *, void **, void **);

bool postprocess_hs_source_file(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_hs_source_file@@YA_NJPAX_N@Z");

    if (!for_editor)
    {
        hs_source_file * source_file = static_cast<hs_source_file *>(element);
        tag_block_delete_all_elements(&source_file->external_references);
    }

    return true;
};

void write_hs_syntax_data_to_cache_file(long tag_index, s_tag_block * block, s_cache_file_builder_stream_context const * context, void ** data_address, void ** out_virtual_base_address)
{
    mangled_ppc("?write_hs_syntax_data_to_cache_file@@YAXJPAUs_tag_block@@PBUs_cache_file_builder_stream_context@@PAPAX2@Z");

    c_cache_file_scratch_allocator * cache_file_allocator = context->cache_file_allocator;
    char * string_data = static_cast<char *>(static_cast<scenario *>(tag_get(SCENARIO_GROUP_TAG, tag_index))->script_string_data.address);

    if (cache_file_allocator->byte_swap_destination())
    {
        for (long node_index = 0; node_index < block->count; node_index++)
        {
            hs_syntax_node * writable_node;
            hs_syntax_node * node = static_cast<hs_syntax_node *>(tag_block_get_element_with_size(block, node_index, sizeof(hs_syntax_node)));
            writable_node = node;
            if (node->type >= FIRST_HS_TYPE && node->type < NUMBER_OF_HS_NODE_TYPES && TEST_BIT(node->flags, _hs_syntax_node_primitive_bit) && !TEST_BIT(node->flags, _hs_syntax_node_variable_bit))
            {
                if (writable_node->type == _hs_type_string)
                {
                    writable_node->data = writable_node->source_offset;
                }
                long type_size = hs_type_sizes[node->constant_type];
                long data_size = sizeof(writable_node->data);
                if (type_size != 0 && type_size != 4)
                {
                    if (type_size > 1)
                    {
                        byte_swap_memory(&writable_node->data, 1, -type_size);
                    }
                    byte_swap_memory(&writable_node->data, 1, _4byte);
                }
            }
        }
    }

    cache_file_builder_stream_tag_block_default(tag_index, block, context, out_virtual_base_address);

    if (cache_file_allocator->byte_swap_destination())
    {
        for (long node_index = 0; node_index < block->count; node_index++)
        {
            hs_syntax_node * writable_node;
            hs_syntax_node * node = static_cast<hs_syntax_node *>(tag_block_get_element_with_size(block, node_index, sizeof(hs_syntax_node)));
            writable_node = node;
            if (node->type >= FIRST_HS_TYPE && node->type < NUMBER_OF_HS_NODE_TYPES && TEST_BIT(node->flags, _hs_syntax_node_primitive_bit) && !TEST_BIT(node->flags, _hs_syntax_node_variable_bit))
            {
                long type_size = hs_type_sizes[node->constant_type];
                long data_size = sizeof(writable_node->data);
                if (type_size != 0 && type_size != 4)
                {
                    byte_swap_memory(&writable_node->data, 1, _4byte);
                    if (type_size > 1)
                    {
                        byte_swap_memory(&writable_node->data, 1, -type_size);
                    }
                }
                if (writable_node->type == _hs_type_string)
                {
                    writable_node->data = reinterpret_cast<unsigned long>(string_data + writable_node->source_offset);
                }
            }
        }
    }
};

