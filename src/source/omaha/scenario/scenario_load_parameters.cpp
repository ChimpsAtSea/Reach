#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\scenario\\scenario_load_parameters.cpp"
/* ---------- headers */

#include "omaha\scenario\scenario_load_parameters.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_string.h"
#include <string.h>
#include <ctype.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char g_scenario_load_path[256];
bool g_scenario_load_in_progress;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition global_scenario_load_parameters_block_struct_definition; // "?global_scenario_load_parameters_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition global_scenario_load_parameters_block; // "?global_scenario_load_parameters_block@@3Us_tag_block_definition@@A"
// char *g_scenario_load_path; // "?g_scenario_load_path@@3PADA"
// bool g_scenario_load_in_progress; // "?g_scenario_load_in_progress@@3_NA"

// void scenario_load_parameters_begin(char const *);
// void scenario_load_parameters_end(void);
// struct s_scenario_load_parameters const * scenario_load_parameters_get(long, struct s_tag_block const *);
// bool scenario_load_parameters_parse_string(struct s_tag_data const *, long *, long, char *, long, char *);

void scenario_load_parameters_begin(char const * scenario_path)
{
    mangled_ppc("?scenario_load_parameters_begin@@YAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(56, scenario_path);
    assert_tag_debug_untracked_jul_11_2011(57, !g_scenario_load_in_progress);

    csstrnzcpy(g_scenario_load_path, scenario_path, NUMBEROF(g_scenario_load_path));
    g_scenario_load_in_progress = true;
};

void scenario_load_parameters_end(void)
{
    mangled_ppc("?scenario_load_parameters_end@@YAXXZ");

    assert_tag_debug_untracked_jul_11_2011(68, g_scenario_load_in_progress);

    g_scenario_load_in_progress = false;
};

s_scenario_load_parameters const * scenario_load_parameters_get(long tag_index, s_tag_block const * parameters_block)
{
    mangled_ppc("?scenario_load_parameters_get@@YAPBUs_scenario_load_parameters@@JPBUs_tag_block@@@Z");

    s_scenario_load_parameters const * result = NULL;
    assert_tag_debug_untracked_jul_11_2011(80, parameters_block);

    if (g_scenario_load_in_progress)
    {
        for (long parameters_index = 0; parameters_index < parameters_block->count; parameters_index++)
        {
            s_scenario_load_parameters const * parameters = static_cast<s_scenario_load_parameters const *>(tag_block_get_element_with_size(parameters_block, parameters_index, sizeof(s_scenario_load_parameters)));
            if (parameters->scenario.name_length > 0 && strncmp(parameters->scenario.name, g_scenario_load_path, NUMBEROF(g_scenario_load_path)) == 0)
            {
                if (result == NULL)
                {
                    result = parameters;
                }
                else
                {
                    event_wrapped(_event_error, "tag %s has more than one parameters block for scenario %s!", tag_get_name(tag_index), g_scenario_load_path);
                    break;
                }
            }
        }
    }

    return result;
};

bool scenario_load_parameters_parse_string(s_tag_data const * parameters_text, long * string_offset, long command_buffer_length, char * command_buffer, long argument_buffer_length, char * argument_buffer)
{
    mangled_ppc("?scenario_load_parameters_parse_string@@YA_NPBUs_tag_data@@PAJJPADJ2@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(121, parameters_text);
    assert_tag_debug_untracked_jul_11_2011(122, string_offset);
    assert_tag_debug_untracked_jul_11_2011(123, command_buffer_length>0);
    assert_tag_debug_untracked_jul_11_2011(124, command_buffer);
    assert_tag_debug_untracked_jul_11_2011(125, argument_buffer_length>0);
    assert_tag_debug_untracked_jul_11_2011(126, argument_buffer);

    if (parameters_text->size - *string_offset > 1)
    {
        assert_tag_debug_untracked_jul_11_2011(132, parameters_text->address);

        char const * current = static_cast<char const *>(parameters_text->address) + *string_offset;
        while (*current && isspace(*current))
        {
            current++;
        }

        char const * command = current;
        long command_length = 0;
        while (*current && !isspace(*current))
        {
            current++;
            command_length++;
        }
        command_length = command_length > command_buffer_length - 1 ? command_buffer_length - 1 : command_length;
        csstrnzcpy(command_buffer, command, command_length + 1);

        while (*current && *current != '\r' && *current != '\n' && isspace(*current))
        {
            current++;
        }

        char const * argument = current;
        long argument_len = 0;
        while (*current && *current != '\r' && *current != '\n')
        {
            current++;
            argument_len++;
        }
        argument_len = argument_len > argument_buffer_length - 1 ? argument_buffer_length - 1 : argument_len;
        csstrnzcpy(argument_buffer, argument, argument_len + 1);

        while (argument_len > 0 && isspace(argument_buffer[argument_len - 1]))
        {
            argument_buffer[--argument_len] = 0;
        }

        *string_offset = current - static_cast<char const *>(parameters_text->address);
        result = command_buffer[0] != 0;
    }

    return result;
};

