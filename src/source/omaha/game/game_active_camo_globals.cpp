/* ---------- headers */

#include "omaha\game\game_active_camo_globals.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition active_camo_globals_block_struct_definition; // "?active_camo_globals_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition active_camo_globals_block; // "?active_camo_globals_block@@3Us_tag_block_definition@@A"

// char * format_active_camo_level(long, __int64, struct s_tag_block *, long, char *, long);

char * format_active_camo_level(long block_index, __int64 flags, s_tag_block * block, long element_index, char * buffer, long buffer_size)
{
    mangled_ppc("?format_active_camo_level@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    switch (element_index)
    {
    case _active_camo_level_none:
        csstrnzcpy(buffer, "none", buffer_size);
        break;
    case _active_camo_level_poor:
        csstrnzcpy(buffer, "poor", buffer_size);
        break;
    case _active_camo_level_good:
        csstrnzcpy(buffer, "good", buffer_size);
        break;
    case _active_camo_level_excellent:
        csstrnzcpy(buffer, "excellent", buffer_size);
        break;
    case _active_camo_level_invisible:
        csstrnzcpy(buffer, "invisible", buffer_size);
        break;
    case _active_camo_level_ai:
        csstrnzcpy(buffer, "ai", buffer_size);
        break;
    }

    return buffer;
};

