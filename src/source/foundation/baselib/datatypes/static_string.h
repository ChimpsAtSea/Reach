#ifndef __STATIC_STRING_H__
#define __STATIC_STRING_H__
#pragma once

/* ---------- headers */

#include <stdarg.h>
#include <string.h>
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\text\unicode.h"

/* ---------- constants */

/* ---------- definitions */

template<long k_maximum_count>
class s_static_string
{
public:
    static long const k_index_not_found = -1;
    static long const k_element_count = k_maximum_count;

    void set(char const * s)
    {
        mangled_ppc("?set@?$s_static_string@$0CA@@@QAAXPBD@Z");

        csstrnzcpy(m_string, s, k_maximum_count);
    };

    // unverified: owned by levels.obj
    void set_bounded(char const * s, long length)
    {
        csstrnzcpy(m_string, s, int_min(k_maximum_count, length + 1));
    };

    // unverified: owned by online_error.obj
    char const * append(char const * s)
    {
        csstrnzcat(m_string, s, k_maximum_count);

        return m_string;
    };

    // verified for <128> (game_launch.obj)
    char * copy_to(char * out_string, unsigned int out_string_size) const
    {
        long copy_size = int_min(static_cast<long>(out_string_size), k_maximum_count);

        return csstrnzcpy(out_string, m_string, copy_size);
    };

    void clear()
    {
        m_string[0] = 0;
    };

    bool is_equal(char const * s) const
    {
        bool const result = strncmp_debug(m_string, s, k_maximum_count) == 0;

        return result;
    };

    bool is_empty() const
    {
        bool const result = !m_string[0];

        return result;
    };

    char const * get_string() const
    {
        return m_string;
    };

    operator char const *() const
    {
        return m_string;
    };

    char (&get_buffer())[k_maximum_count]
    {
        return m_string;
    };

    // verified for <43> (content_container_names.obj)
    void null_terminate()
    {
        m_string[k_maximum_count - 1] = 0;
    };

    static long max_length()
    {
        return k_maximum_count;
    };

    long length() const
    {
        return csstrnlen(m_string, k_maximum_count);
    };

    // unverified: owned by render_debug_graph.obj
    void set_length(long length)
    {
        if (length >= 0 && length < k_maximum_count - 1)
        {
            m_string[length] = 0;
        }
    };

    // unverified: owned by network_session.obj
    long next_index_of(char const * string, long start_index) const
    {
        long index = k_index_not_found;

        assert_decomp(string, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_string.h", 396);
        if (start_index < length())
        {
            char const * found = strstr(m_string + start_index, string);
            if (found)
            {
                index = pointer_distance32(m_string, found);
                assert_decomp(VALID_INDEX(index, k_maximum_count), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_string.h", 405);
            }
        }

        return index;
    };

    long index_of(char const * string) const
    {
        mangled_ppc("?index_of@?$s_static_string@$0CAA@@@QBAJPBD@Z");

        return next_index_of(string, 0);
    };

    bool substring(long start_index, long substring_length, s_static_string * out_string) const
    {
        mangled_ppc("?substring@?$s_static_string@$0CAA@@@QBA_NJJPAV1@@Z");

        bool result = false;
        if (start_index >= 0 && substring_length > 0 && start_index + substring_length <= length())
        {
            csstrnzcpy(out_string->m_string, m_string + start_index, int_min(substring_length + 1, k_maximum_count));
            result = true;
        }

        return result;
    };

    void replace(char find, char replace)
    {
        for (long index = 0; index < k_maximum_count; index++)
        {
            if (m_string[index] == find)
            {
                m_string[index] = replace;
            }
        }
    };

    void to_lower()
    {
        long string_length = length();
        char buffer[k_maximum_count];
        copy_to(buffer, string_length + 1);
        for (long index = 0; index < string_length; index++)
        {
            m_string[index] = static_cast<char>(ascii_tolower(buffer[index]));
        }
    };

    // unverified: owned by http_client.obj
    bool starts_with(char const * string) const
    {
        assert_decomp(string, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_string.h", 416);

        return strncmp(string, m_string, csstrnlen(string, k_maximum_count)) == 0;
    };

    // $TODO nonmatching: target has index at the lower stack slot (99.7%)
    void strip_leading(char c)
    {
        long string_length = length();
        long index = 0;
        while (index < string_length && m_string[index] == c)
        {
            index++;
        }

        if (index > 0)
        {
            csmemmove(m_string, m_string + index, string_length - index);
            m_string[string_length - index] = 0;
        }
    };

    void strip_trailing(char c)
    {
        long string_length = length();
        while (string_length > 0 && m_string[string_length - 1] == c)
        {
            m_string[string_length - 1] = 0;
            string_length--;
        }
    };

    char const * print(char const * format, ...)
    {
        va_list arglist;

        assert_decomp(format, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/datatypes/static_string.h", 140);

        va_start(arglist, format);
        cvsnzprintf(m_string, k_maximum_count, format, arglist);

        va_end(arglist);

        return m_string;
    };

    char const * append_print(char const * format, ...);

    void print_va(char const * format, va_list arglist)
    {
        cvsnzprintf(m_string, k_maximum_count, format, arglist);
    };

    char * from_tag(unsigned long tag)
    {
        return c_static_string_utilities::tag_to_string(tag, m_string, k_maximum_count);
    };

private:
    char m_string[k_maximum_count];
};

template<long k_maximum_count>
class c_static_string : public s_static_string<k_maximum_count>
{
public:
    // unverified: owned by the templates' users
    c_static_string()
    {
        s_static_string<k_maximum_count>::clear();
    };

    c_static_string(char const * s)
    {
        mangled_ppc("??0?$c_static_string@$0CAA@@@QAA@PBD@Z");

        s_static_string<k_maximum_count>::set(s);
    };
};

// constructor and destructor owned by render_mesh.obj
class c_string_builder : public c_static_string<256>
{
public:
    c_string_builder(char const * format, ...);
    ~c_string_builder(void);
};

template<long k_maximum_count>
class c_static_wchar_string
{
public:
    c_static_wchar_string()
    {
        m_string[0] = 0;
    };

    c_static_wchar_string(char const * string)
    {
        set_char(string);
    };

    void set(wchar_t const * s)
    {
        ustrnzcpy(m_string, s, k_maximum_count);
    };

    void set_char(char const * string);

    // f i, owned by game_engine.obj (<1024>); body not added yet
    void clear();

    // f i, owned by network_lsp_leaderboard.obj (<1024>); body not added yet
    wchar_t const * print(wchar_t const * format, ...);

    wchar_t const * get_string(void) const
    {
        return m_string;
    };

private:
    wchar_t m_string[k_maximum_count];
};

class c_static_string_utilities
{
public:
    static char * wchar_string_to_ascii_string(wchar_t const * source, char * dest, long dest_length);
    static char * tag_to_string(unsigned long source, char * dest, long dest_length);
    static unsigned long string_to_tag(char const * string);
};

/* ---------- prototypes */

void wchar_string_to_ascii_string(wchar_t const * src, char * dst, long buffer_count, long * number_of_source_characters_converted);

/* ---------- globals */

/* ---------- public code */

#endif // __STATIC_STRING_H__

