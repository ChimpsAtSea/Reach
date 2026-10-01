#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\text\\xenon_string.cpp"
/* ---------- headers */

#include "omaha\text\xenon_string.h"
#include "core\corelib\cseries\cseries_asserts.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const * xenon_strchr(char const *, int);
// char const * xenon_strstr(char const *, char const *);

char const* xenon_strchr(char const* string, int character)
{
    mangled_ppc("?xenon_strchr@@YAPBDPBDH@Z");

    char const* result = NULL;

    assert_tag_debug_untracked_jul_11_2011(21, string!=NULL);

    for (long index = 0; string[index] != '\0'; index++)
    {
        if (string[index] == character)
        {
            result = &string[index];
            break;
        }
    }

    return result;
};

char const* xenon_strstr(char const* string, char const* character_set)
{
    mangled_ppc("?xenon_strstr@@YAPBDPBD0@Z");

    char const* result;

    assert_tag_debug_untracked_jul_11_2011(40, string!=NULL);
    assert_tag_debug_untracked_jul_11_2011(41, character_set!=NULL);

    if (*character_set == '0')
    {
        result = string;
    }
    else
    {
        long length = strlen(character_set);

        result = NULL;
        for (; *string != '0'; string++)
        {
            if (*string == *character_set && memcmp(string, character_set, length) == 0)
            {
                result = string;
                break;
            }
        }
    }

    return result;
};

