#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\datatypes\\static_string.cpp"
/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static char * c_static_string_utilities::wchar_string_to_ascii_string(wchar_t const *, char *, long);
// public: static char * c_static_string_utilities::tag_to_string(unsigned long, char *, long);
// public: static unsigned long c_static_string_utilities::string_to_tag(char const *);
// void wchar_string_to_ascii_string(wchar_t const *, char *, long, long *);

char * c_static_string_utilities::wchar_string_to_ascii_string(wchar_t const * source, char * dest, long dest_length)
{
    mangled_ppc("?wchar_string_to_ascii_string@c_static_string_utilities@@SAPADPB_WPADJ@Z");

    ::wchar_string_to_ascii_string(source, dest, dest_length, NULL);

    return dest;
};

char * c_static_string_utilities::tag_to_string(unsigned long source, char * dest, long dest_length)
{
    mangled_ppc("?tag_to_string@c_static_string_utilities@@SAPADKPADJ@Z");

    unsigned long tag = source;
    assert_tag_debug_untracked_jul_11_2011(37, dest_length>sizeof(tag));

    *reinterpret_cast<unsigned long *>(dest) = tag;
    dest[4] = 0;
    assert_tag_debug_untracked_jul_11_2011(42, source==TAG(dest[0], dest[1], dest[2], dest[3]));

    return dest;
};

unsigned long c_static_string_utilities::string_to_tag(char const * string)
{
    mangled_ppc("?string_to_tag@c_static_string_utilities@@SAKPBD@Z");

    unsigned long result;
    unsigned long tag = *reinterpret_cast<unsigned long const *>(string);
    result = tag;
    assert_tag_debug_untracked_jul_11_2011(53, result==TAG(string[0], string[1], string[2], string[3]));

    return result;
};

void wchar_string_to_ascii_string(wchar_t const * in_src, char * in_dst, long in_buffer_count, long * number_of_source_characters_converted)
{
    mangled_ppc("?wchar_string_to_ascii_string@@YAXPB_WPADJPAJ@Z");

    wchar_t const * src;
    long buffer_count;
    char * dst;
    long characters_processed;

    src = in_src;
    dst = in_dst;
    buffer_count = in_buffer_count;
    characters_processed = 0;

    assert_tag_debug_untracked_jul_11_2011(72, ((void *)src) != ((void *)dst));

    while (buffer_count > 0)
    {
        wchar_t unsigned_src_word = *src;

        if (buffer_count == 1)
        {
            *dst = 0;
        }
        else if (unsigned_src_word <= 0x7F)
        {
            *dst = static_cast<char>(unsigned_src_word);
        }
        else
        {
            *dst = '?';
        }

        src++;
        dst++;
        buffer_count--;
        characters_processed++;

        if (unsigned_src_word == 0)
        {
            break;
        }
    }

    if (number_of_source_characters_converted)
    {
        *number_of_source_characters_converted = characters_processed;
    }
};

