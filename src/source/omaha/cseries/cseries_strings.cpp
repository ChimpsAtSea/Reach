#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\omaha\cseries\cseries_strings.cpp"
/* ---------- headers */

#include "omaha\cseries\cseries_strings.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\wrapped_arrays.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const * find_string_end(char const *, char const *);
// char const * find_string_end_not_in_delimiter(char const *, char const *);
// void string_terminate_at_first_delimiter(char *, char const *);
// bool string_is_not_empty(char const *);
// long string_list_find(char const *, long, char const *const *const);
// long string_list_find_explicit(class c_wrapped_array<char const> const &, class c_wrapped_array<char const *> const &);
// void string_replace_character(char *, char, char);
// char * strchr(char *, int);
// void string_copy_until_delimiter(class c_wrapped_array<char>, char const *, char const *);
// void string_copy_bounded(class c_wrapped_array<char>, class c_wrapped_array<char const>);
// void parse_flags_string(char const *, class c_wrapped_array<char const *> const &, class c_wrapped_flags);
// public: void c_bit_vector_operator_interface<class c_wrapped_flags>::set(long, bool);
// public: long c_wrapped_array_no_init<char const *>::count(void) const;
// public: char const *const & c_array_operator_interface<class c_wrapped_array_no_init<char const *>, char const *>::operator[](long) const;
// public: c_wrapped_array<char const>::c_wrapped_array<char const>(char const *, char const *);
// public: char const * c_wrapped_array_no_init<char const>::begin(void) const;
// public: long c_wrapped_array_no_init<char const>::count(void) const;
// public: char const * c_array_operator_interface<class c_wrapped_array_no_init<char const>, char const>::get_elements(void) const;
// private: bool c_bit_vector_operator_interface<class c_wrapped_flags>::verify_index(unsigned long) const;
// private: unsigned long * c_bit_vector_operator_interface<class c_wrapped_flags>::get_bit_storage(void);
// private: unsigned long * c_wrapped_flags::get_bit_storage(void);
// public: class c_wrapped_flags * c_recursive_template_pattern<class c_wrapped_flags>::get_super_class(void);
// public: char const *const * c_wrapped_array_no_init<char const *>::begin(void) const;
// public: bool c_array_operator_interface<class c_wrapped_array_no_init<char const *>, char const *>::valid_index(long) const;
// public: class c_wrapped_array_no_init<char const *> const * c_recursive_template_pattern<class c_wrapped_array_no_init<char const *> >::get_super_class(void) const;
// public: void c_wrapped_array_no_init<char const>::set_elements(char const *, long);
// public: char const * c_array_operator_interface<class c_wrapped_array_no_init<char const>, char const>::begin(void) const;
// public: long c_bit_vector_operator_interface<class c_wrapped_flags>::bit_count(void) const;
// public: long c_wrapped_flags::bit_count(void) const;
// public: long c_array_operator_interface<class c_wrapped_array_no_init<char const *>, char const *>::count(void) const;
// public: class c_wrapped_array_no_init<char const> const * c_recursive_template_pattern<class c_wrapped_array_no_init<char const> >::get_super_class(void) const;
// public: class c_wrapped_flags const * c_recursive_template_pattern<class c_wrapped_flags>::get_super_class(void) const;

char const * find_string_end(char const * string, char const * delimiters)
{
    mangled_ppc("?find_string_end@@YAPBDPBD0@Z");

    assert_tag_debug_untracked_jul_11_2011(14, string);
    assert_tag_debug_untracked_jul_11_2011(15, delimiters);

    size_t end_offset = strcspn(string, delimiters);
    char const * end = &string[end_offset];
    return end;
};

char const * find_string_end_not_in_delimiter(char const * string, char const * delimiters)
{
    mangled_ppc("?find_string_end_not_in_delimiter@@YAPBDPBD0@Z");

    assert_tag_debug_untracked_jul_11_2011(27, string);
    assert_tag_debug_untracked_jul_11_2011(28, delimiters);

    size_t end_offset = strspn(string, delimiters);
    char const * end = &string[end_offset];
    return end;
};

void string_terminate_at_first_delimiter(char * string, char const * delimiters)
{
    mangled_ppc("?string_terminate_at_first_delimiter@@YAXPADPBD@Z");

    size_t end_offset = strcspn(string, delimiters);
    string[end_offset] = 0;
};

bool string_is_not_empty(char const * string)
{
    mangled_ppc("?string_is_not_empty@@YA_NPBD@Z");

    return string != NULL && *string != 0;
};

long string_list_find(char const * string, long list_count, char const * const * const string_list)
{
    mangled_ppc("?string_list_find@@YAJPBDJQBQBD@Z");

    long result_list_index = NONE;
    for (long list_index = 0; list_index < list_count; list_index++)
    {
        if (ascii_stricmp(string, string_list[list_index]) == 0)
        {
            result_list_index = list_index;
            break;
        }
    }
    return result_list_index;
};

long string_list_find_explicit(c_wrapped_array<char const> const & string, c_wrapped_array<char const *> const & string_list)
{
    mangled_ppc("?string_list_find_explicit@@YAJABV?$c_wrapped_array@$$CBD@@ABV?$c_wrapped_array@PBD@@@Z");

    long result_list_index = NONE;
    for (long list_index = 0; list_index < string_list.count(); list_index++)
    {
        char const * list_string = string_list[list_index];
        long list_string_length = strlen(list_string);
        if (list_string_length == string.count() && ascii_strnicmp(string.get_elements(), list_string, string.count()) == 0)
        {
            result_list_index = list_index;
            break;
        }
    }
    return result_list_index;
};

void string_replace_character(char * string, char old_character, char new_character)
{
    mangled_ppc("?string_replace_character@@YAXPADDD@Z");

    char * next_old_character = string;
    while ((next_old_character = strchr(next_old_character, old_character)) != NULL)
    {
        *next_old_character = new_character;
        next_old_character++;
    }
};

void string_copy_until_delimiter(c_wrapped_array<char> out_dest_string, char const * source_string, char const * delimiters)
{
    mangled_ppc("?string_copy_until_delimiter@@YAXV?$c_wrapped_array@D@@PBD1@Z");

    csstrnzcpy(out_dest_string.begin(), source_string, out_dest_string.count());
    string_terminate_at_first_delimiter(out_dest_string.begin(), delimiters);
};

void string_copy_bounded(c_wrapped_array<char> out_dest_string, c_wrapped_array<char const> const in_source_string)
{
    mangled_ppc("?string_copy_bounded@@YAXV?$c_wrapped_array@D@@V?$c_wrapped_array@$$CBD@@@Z");

    assert_tag_debug_untracked_jul_11_2011(124, out_dest_string.count()>0);

    long copy_count = CEILING(out_dest_string.count() - 1, in_source_string.count());
    _memccpy(out_dest_string.begin(), in_source_string.begin(), 0, copy_count);
    out_dest_string[copy_count] = 0;
};

void parse_flags_string(char const * flags_string, c_wrapped_array<char const *> const & flag_names, c_wrapped_flags flags)
{
    mangled_ppc("?parse_flags_string@@YAXPBDABV?$c_wrapped_array@PBD@@Vc_wrapped_flags@@@Z");

    char const * current = flags_string;
    while (string_is_not_empty(current))
    {
        char const * end = find_string_end(current, "|");
        c_wrapped_array<char const> flag_name(current, end);
        long flag_index = string_list_find_explicit(flag_name, flag_names);
        if (flag_index != NONE)
        {
            flags.set(flag_index, true);
        }
        current = (end != NULL && string_is_not_empty(end)) ? end + 1 : end;
    }
};
