#pragma once
#ifndef __MEGALOGAMENGINE_STRING_ID_TABLE_H__
#define __MEGALOGAMENGINE_STRING_ID_TABLE_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\memory\array.h"

/* ---------- constants */

enum
{
    k_megalo_string_id_table_definition_tag = 'msit',
};

/* ---------- definitions */

struct s_megalo_string_id_table_definition
{
    s_tag_block string_ids; // 0x0 (long string_id elements)
};
static_assert(sizeof(s_megalo_string_id_table_definition) == 0xC, "s_megalo_string_id_table_definition");

/* ---------- prototypes */

long megalo_string_id_table_get_count(void);
long megalo_string_id_table_get_string_id(long index);
s_megalo_string_id_table_definition const * try_and_get_global_megalo_string_id_table(void);
void megalo_string_id_table_add_to_list(array_template<long> * list);

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_STRING_ID_TABLE_H__

