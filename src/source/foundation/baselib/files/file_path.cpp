#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_path.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_path.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const k_file_extension_string = ".";
char const * const k_file_directory_string = "\\";
char const * const k_file_current_directory_string = ".";
char const * const k_file_parent_directory_string = "..";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const *const k_file_extension_string; // "?k_file_extension_string@@3PBDB"
// char const *const k_file_directory_string; // "?k_file_directory_string@@3PBDB"
// char const *const k_file_current_directory_string; // "?k_file_current_directory_string@@3PBDB"
// char const *const k_file_parent_directory_string; // "?k_file_parent_directory_string@@3PBDB"

// public: void c_file_path::clear(void);
// public: void c_file_path::set_root(enum e_file_location);
// public: void c_file_path::set_file_path(enum e_file_location, char const *);
// public: void c_file_path::set_directory_path(enum e_file_location, char const *);
// public: void c_file_path::copy(class c_file_path const *);
// public: bool c_file_path::is_directory(void) const;
// public: bool c_file_path::is_equal(class c_file_path const *) const;
// public: enum e_file_location c_file_path::get_location(void) const;
// public: char const * c_file_path::get_filename_direct(void) const;
// public: void c_file_path::add_directory(char const *);
// public: void c_file_path::remove_directory(void);
// public: void c_file_path::set_filename(char const *);
// public: void c_file_path::remove_filename(void);
// public: char * c_file_path::get_full_path(char *, long) const;
// public: char * c_file_path::get(unsigned long, char *, long) const;
// private: void c_file_path::initialize(enum e_file_location);
// private: static void c_file_path::path_add_name(char *, long, char const *);
// private: static void c_file_path::path_add_extension(char *, long, char const *);
// private: static void c_file_path::path_remove_name(char *);
// private: static void c_file_path::path_split(char *, char **, char **, char **, char **, bool);
// public: void s_static_string<256>::replace(char, char);
// public: void s_static_string<256>::strip_leading(char);
// public: void s_static_string<256>::strip_trailing(char);
// public: void s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::clear(void);
// public: bool s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::test(enum c_file_path::e_file_path_flags) const;
// public: void s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::set(enum c_file_path::e_file_path_flags, bool);
// public: bool s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::valid(void) const;
// public: static bool s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::valid_bit(enum c_file_path::e_file_path_flags);
// private: static unsigned long s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::flag_size_type(enum c_file_path::e_file_path_flags);
// private: static unsigned long s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum c_file_path::e_file_path_flags, unsigned long, 1>::make_N_bit_mask_size_type(enum c_file_path::e_file_path_flags);

void c_file_path::clear(void)
{
    mangled_ppc("?clear@c_file_path@@QAAXXZ");

    initialize(k_file_location_invalid);
};

void c_file_path::set_root(e_file_location location)
{
    mangled_ppc("?set_root@c_file_path@@QAAXW4e_file_location@@@Z");

    assert_tag_debug_untracked_jul_11_2011(30, VALID_INDEX(location, k_file_location_count));

    initialize(location);
};

void c_file_path::set_file_path(e_file_location location, char const * path)
{
    mangled_ppc("?set_file_path@c_file_path@@QAAXW4e_file_location@@PBD@Z");

    assert_tag_debug_untracked_jul_11_2011(38, VALID_INDEX(location, k_file_location_count));
    assert_tag_debug_untracked_jul_11_2011(39, path);

    initialize(location);
    set_filename(path);
};

void c_file_path::set_directory_path(e_file_location location, char const * path)
{
    mangled_ppc("?set_directory_path@c_file_path@@QAAXW4e_file_location@@PBD@Z");

    assert_tag_debug_untracked_jul_11_2011(48, VALID_INDEX(location, k_file_location_count));
    assert_tag_debug_untracked_jul_11_2011(49, path);

    initialize(location);
    add_directory(path);
};

void c_file_path::copy(c_file_path const * source)
{
    mangled_ppc("?copy@c_file_path@@QAAXPBV1@@Z");

    assert_tag_debug_untracked_jul_11_2011(57, source);

    csmemcpy(this, source, sizeof(c_file_path));
};

bool c_file_path::is_directory(void) const
{
    mangled_ppc("?is_directory@c_file_path@@QBA_NXZ");

    return !m_flags.test(_file_path_has_filename_bit);
};

bool c_file_path::is_equal(c_file_path const * path) const
{
    mangled_ppc("?is_equal@c_file_path@@QBA_NPBV1@@Z");

    assert_tag_debug_untracked_jul_11_2011(70, path);

    bool result = path->get_location() == m_location && strncmp_debug(path->get_filename_direct(), m_path, k_maximum_filename_length) == 0;

    return result;
};

e_file_location c_file_path::get_location(void) const
{
    mangled_ppc("?get_location@c_file_path@@QBA?AW4e_file_location@@XZ");

    return m_location;
};

char const * c_file_path::get_filename_direct(void) const
{
    mangled_ppc("?get_filename_direct@c_file_path@@QBAPBDXZ");

    return m_path.get_string();
};

void c_file_path::add_directory(char const * directory)
{
    mangled_ppc("?add_directory@c_file_path@@QAAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(92, directory);

    assert_tag_debug_untracked_jul_11_2011(95, !m_flags.test(_file_path_has_filename_bit));

    path_add_name(m_path.get_buffer(), m_path.max_length(), directory);
};

void c_file_path::remove_directory(void)
{
    mangled_ppc("?remove_directory@c_file_path@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(103, !m_flags.test(_file_path_has_filename_bit));

    path_remove_name(m_path.get_buffer());
};

void c_file_path::set_filename(char const * name)
{
    mangled_ppc("?set_filename@c_file_path@@QAAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(110, name);

    remove_filename();
    path_add_name(m_path.get_buffer(), m_path.max_length(), name);
    m_flags.set(_file_path_has_filename_bit, true);
};

void c_file_path::remove_filename(void)
{
    mangled_ppc("?remove_filename@c_file_path@@QAAXXZ");

    if (m_flags.test(_file_path_has_filename_bit))
    {
        path_remove_name(m_path.get_buffer());
        m_flags.set(_file_path_has_filename_bit, false);
    }
};

char * c_file_path::get_full_path(char * out_name, long name_length) const
{
    mangled_ppc("?get_full_path@c_file_path@@QBAPADPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(135, out_name);
    assert_tag_debug_untracked_jul_11_2011(136, m_location==k_file_location_invalid || VALID_INDEX(m_location, k_file_location_count));

    char const * root_absolute_path = file_location_get_root_absolute_path(m_location);
    csstrnzcpy(out_name, root_absolute_path, name_length);
    csstrnzcat(out_name, m_path, name_length);

    return out_name;
};

char * c_file_path::get(unsigned long path_flags, char * out_name, long name_length) const
{
    mangled_ppc("?get@c_file_path@@QBAPADKPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(156, path_flags!=0);

    assert_tag_debug_untracked_jul_11_2011(158, !((TEST_BIT(path_flags, _file_path_get_extension_bit) && !TEST_BIT(path_flags, _file_path_get_filename_bit)) && (TEST_BIT(path_flags, _file_path_get_directory_bit) || TEST_BIT(path_flags, _file_path_get_parent_directory_bit))));
    assert_tag_debug_untracked_jul_11_2011(159, !(TEST_BIT(path_flags, _file_path_get_directory_bit) && TEST_BIT(path_flags, _file_path_get_parent_directory_bit)));

    assert_tag_debug_untracked_jul_11_2011(161, !(TEST_BIT(path_flags, _file_path_get_location_relative_bit) && !TEST_BIT(path_flags, _file_path_get_directory_bit) && !TEST_BIT(path_flags, _file_path_get_parent_directory_bit)));

    assert_tag_debug_untracked_jul_11_2011(163, out_name);
    assert_tag_debug_untracked_jul_11_2011(164, name_length>=k_maximum_filename_length);

    assert_tag_debug_untracked_jul_11_2011(166, m_flags.valid());

    s_static_string<256> path;
    char * filename;
    char * directory;
    char * parent_directory;
    char * extension;

    if (TEST_BIT(path_flags, _file_path_get_location_relative_bit))
    {
        path.set(m_path.get_string());
    }
    else
    {
        get_full_path(&path);
    }

    path_split(path.get_buffer(), &directory, &parent_directory, &filename, &extension, m_flags.test(_file_path_has_filename_bit));
    csstrnzcpy(out_name, "", name_length);

    if (TEST_BIT(path_flags, _file_path_get_directory_bit))
    {
        path_add_name(out_name, name_length, directory);
    }

    if (TEST_BIT(path_flags, _file_path_get_parent_directory_bit))
    {
        path_add_name(out_name, name_length, parent_directory);
    }

    if (TEST_BIT(path_flags, _file_path_get_filename_bit))
    {
        path_add_name(out_name, name_length, filename);
    }

    if (TEST_BIT(path_flags, _file_path_get_extension_bit))
    {
        path_add_extension(out_name, name_length, extension);
    }

    return out_name;
};

void c_file_path::initialize(e_file_location location)
{
    mangled_ppc("?initialize@c_file_path@@AAAXW4e_file_location@@@Z");

    assert_tag_debug_untracked_jul_11_2011(208, location==k_file_location_invalid || VALID_INDEX(location, k_file_location_count));

    m_path.clear();
    m_location = location;
    m_flags.clear();
};

void c_file_path::path_add_name(char * path, long path_length, char const * name)
{
    mangled_ppc("?path_add_name@c_file_path@@CAXPADJPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(229, path);
    assert_tag_debug_untracked_jul_11_2011(230, name);

    if (name[0])
    {
        s_static_string<256> clean_name;
        clean_name.set(name);
        clean_name.strip_leading('\\');
        clean_name.strip_trailing('\\');
        clean_name.replace('/', '\\');

        if (!clean_name.is_empty())
        {
            size_t length = csstrnlen(path, path_length);
            if (length > 0 && path[length - 1] != '\\')
            {
                path[length++] = '\\';
                path[length] = 0;
            }

            csstrnzcpy(path + length, clean_name.get_string(), path_length - length);
        }
    }
};

void c_file_path::path_add_extension(char * path, long path_length, char const * extension)
{
    mangled_ppc("?path_add_extension@c_file_path@@CAXPADJPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(275, path);
    assert_tag_debug_untracked_jul_11_2011(276, extension);

    if (extension[0])
    {
        size_t length = csstrnlen(path, path_length);
        if (length > 0)
        {
            path[length++] = '.';
            path[length] = 0;
        }

        csstrnzcpy(path + length, extension, path_length - length);
    }
};

void c_file_path::path_remove_name(char * path)
{
    mangled_ppc("?path_remove_name@c_file_path@@CAXPAD@Z");

    assert_tag_debug_untracked_jul_11_2011(300, path);

    if (path[0])
    {
        long index = strlen_debug(path) - 2;
        index = int_max(index, 0);
        while (index > 0 && path[index] != '\\')
        {
            index--;
        }

        path[index] = 0;
    }
};

void c_file_path::path_split(char * path, char ** out_directory, char ** out_parent_directory, char ** out_filename, char ** out_extension, bool split_filename)
{
    mangled_ppc("?path_split@c_file_path@@CAXPADPAPAD111_N@Z");

    assert_tag_debug_untracked_jul_11_2011(335, path);
    assert_tag_debug_untracked_jul_11_2011(336, out_directory);
    assert_tag_debug_untracked_jul_11_2011(337, out_parent_directory);
    assert_tag_debug_untracked_jul_11_2011(338, out_filename);
    assert_tag_debug_untracked_jul_11_2011(339, out_extension);

    size_t index = strlen_debug(path);
    *out_directory = path + index;
    *out_parent_directory = path + index;
    *out_filename = path + index;
    *out_extension = path + index;

    for (; index > 0; index--)
    {
        char character = path[index];
        if (character == '.')
        {
            if (split_filename && !**out_filename && !**out_extension)
            {
                path[index] = 0;
                *out_extension = path + index + 1;
            }
        }
        else if (character == '\\')
        {
            if (split_filename && !**out_filename)
            {
                path[index] = 0;
                *out_filename = path + index + 1;
            }
            else if (!**out_parent_directory)
            {
                *out_parent_directory = path + index + 1;
            }
        }
    }

    if (split_filename && !**out_filename)
    {
        *out_filename = path;
    }

    if (*out_filename != path)
    {
        *out_directory = path;
    }
};
