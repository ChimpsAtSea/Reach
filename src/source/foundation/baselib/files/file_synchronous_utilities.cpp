#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_synchronous_utilities.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_synchronous_utilities.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_io.h"
#include "foundation\baselib\files\file_synchronous_utilities_windows.h"
#include "foundation\baselib\memory\allocation_interface.h"

/* ---------- constants */

/* ---------- definitions */

// $TODO every s_find_files_data local in the target occupies 0x3D0 bytes of stack (0x40 more than
// sizeof(s_find_files_data) == 0x390 as memset by find_files_start); this wrapper reproduces that footprint
struct s_find_files_data_stack
{
    s_find_files_data data;
    unsigned char unused[0x40];
};
static_assert(sizeof(s_find_files_data_stack) == 0x3D0, "s_find_files_data_stack");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool file_is_readable(class c_file_path const *);
// bool file_create_parent_directories(class c_file_path const *);
// bool file_read_into_memory(class c_file_path const *, class c_allocation_interface *, unsigned int, void **, unsigned int *, unsigned int *);
// bool file_read_into_buffer(class c_file_path const *, void *, unsigned int, unsigned int *, unsigned int *);
// bool file_trim(class c_file_path const *, unsigned int);
// bool file_trim_fast(class c_file_path const *, unsigned int, void *, unsigned int);
// bool directory_create_and_delete_contents(class c_file_path const *);
// bool directory_create_recursive(class c_file_path const *);
// bool directory_copy_recursive(class c_file_path const *, class c_file_path const *, enum e_file_overwrite_mode);
// long find_files(class s_flags<enum e_find_files_flags, unsigned long, 3>, class c_file_path const *, char const *, long, class c_file_path *);
// public: c_flags_zero_init<enum e_file_open_flags, unsigned long, 8>::c_flags_zero_init<enum e_file_open_flags, unsigned long, 8>(void);
// public: void s_flags<enum e_file_open_flags, unsigned long, 8>::clear(void);
// public: void s_flags<enum e_file_open_flags, unsigned long, 8>::set(enum e_file_open_flags, bool);
// public: char * c_file_path::get_name<256>(unsigned long, class s_static_string<256> *) const;
// public: void s_flags<enum e_find_files_flags, unsigned long, 3>::set(enum e_find_files_flags, bool);
// public: char * c_file_path::get_parent_directory<256>(class s_static_string<256> *) const;
// public: char * c_file_path::get_parent_directory(char *, long) const;
// public: static bool s_flags<enum e_file_open_flags, unsigned long, 8>::valid_bit(enum e_file_open_flags);
// public: bool s_flags<enum e_file_open_flags, unsigned long, 8>::valid(void) const;
// private: static unsigned long s_flags<enum e_file_open_flags, unsigned long, 8>::flag_size_type(enum e_file_open_flags);
// private: static unsigned long s_flags<enum e_file_open_flags, unsigned long, 8>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_file_open_flags, unsigned long, 8>::make_N_bit_mask_size_type(enum e_file_open_flags);

bool file_is_readable(c_file_path const * path)
{
    mangled_ppc("?file_is_readable@@YA_NPBVc_file_path@@@Z");

    c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> open_flags;
    s_file_accessor file;
    bool readable = false;

    open_flags.set(_file_open_read_bit, true);
    if (file_open(path, open_flags, _file_error_mode_silent, &file))
    {
        file_close(&file);
        readable = true;
    }

    return readable;
};

bool file_create_parent_directories(c_file_path const * path)
{
    mangled_ppc("?file_create_parent_directories@@YA_NPBVc_file_path@@@Z");

    char * current_directory;
    c_file_path directory_path;
    s_static_string<256> original_directory;
    bool success = true;

    path->get_name(FLAG(_file_path_get_directory_bit) | FLAG(_file_path_get_location_relative_bit), &original_directory);
    current_directory = original_directory.get_buffer();
    while (success)
    {
        char * next_directory;
        bool unc = false;

        next_directory = current_directory;
        while (*next_directory == '\\')
        {
            next_directory++;
        }

        if (next_directory == current_directory + 2 && *(next_directory - 2) == '\\' && *(next_directory - 1) == '\\')
        {
            unc = true;
        }

        while (*next_directory != '\0' && *next_directory != '\\')
        {
            next_directory++;
        }

        while (*next_directory == '\\')
        {
            next_directory++;
        }

        if (next_directory == current_directory)
        {
            break;
        }

        current_directory = next_directory;
        if (!unc)
        {
            long length = current_directory - original_directory.get_buffer();
            s_static_string<256> creation_directory;

            creation_directory.set_bounded(original_directory, length);
            if (creation_directory[length - 1] != '\\')
            {
                creation_directory.append(k_file_directory_string);
            }

            directory_path.set_directory_path(path->get_location(), creation_directory);
            if (!directory_exists(&directory_path))
            {
                success = directory_create(&directory_path);
            }
        }
    }

    return success;
};

bool file_read_into_memory(c_file_path const * path, c_allocation_interface * allocator, unsigned int extra_padding_size, void ** out_buffer, unsigned int * out_buffer_size, unsigned int * out_allocation_size)
{
    mangled_ppc("?file_read_into_memory@@YA_NPBVc_file_path@@PAVc_allocation_interface@@IPAPAXPAI3@Z");

    c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> open_flags;
    unsigned int data_size = 0;
    unsigned int allocation_size = 0;
    void * buffer = NULL;
    bool succeeded = false;
    s_file_accessor file;

    assert_tag_debug_untracked_jul_11_2011(136, path);
    assert_tag_debug_untracked_jul_11_2011(137, allocator);
    assert_tag_debug_untracked_jul_11_2011(138, extra_padding_size>=0);
    assert_tag_debug_untracked_jul_11_2011(139, out_buffer);

    open_flags.set(_file_open_read_bit, true);
    if (file_open(path, open_flags, _file_error_mode_report, &file) == _file_open_result_success)
    {
        unsigned int size = file_get_eof(&file);

        allocation_size = size + extra_padding_size;
        if (allocation_size == 0)
        {
            succeeded = true;
        }
        else
        {
            buffer = allocator->allocate(allocation_size, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 154, "file_read_into_memory", NULL, NULL);
            if (buffer != NULL)
            {
                if (file_read(&file, size, _file_error_mode_report, buffer))
                {
                    if (extra_padding_size > 0)
                    {
                        csmemset(offset_pointer(buffer, size), 0, extra_padding_size);
                    }

                    data_size = allocation_size;
                    succeeded = true;
                }
                else
                {
                    allocator->deallocate(buffer, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 170);
                    buffer = NULL;
                    data_size = 0;
                    allocation_size = 0;
                }
            }
        }

        file_close(&file);
    }

    *out_buffer = buffer;
    if (out_buffer_size)
    {
        *out_buffer_size = data_size;
    }

    if (out_allocation_size)
    {
        *out_allocation_size = allocation_size;
    }

    return succeeded;
};

bool file_read_into_buffer(c_file_path const * path, void * buffer, unsigned int buffer_size, unsigned int * out_bytes_read, unsigned int * out_file_size)
{
    mangled_ppc("?file_read_into_buffer@@YA_NPBVc_file_path@@PAXIPAI2@Z");

    c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> open_flags;
    unsigned int bytes_read = 0;
    unsigned int size = 0;
    bool succeeded = false;
    s_file_accessor file;

    assert_tag_debug_untracked_jul_11_2011(205, path);
    assert_tag_debug_untracked_jul_11_2011(206, buffer);
    assert_tag_debug_untracked_jul_11_2011(207, buffer_size>0);

    open_flags.set(_file_open_read_bit, true);
    if (file_open(path, open_flags, _file_error_mode_report, &file) == _file_open_result_success)
    {
        size = file_get_eof(&file);
        if (buffer_size >= size)
        {
            if (file_read(&file, size, _file_error_mode_report, buffer))
            {
                bytes_read = size;
                succeeded = true;
            }
            else
            {
                size = 0;
            }
        }

        file_close(&file);
    }

    if (out_bytes_read)
    {
        *out_bytes_read = bytes_read;
    }

    if (out_file_size)
    {
        *out_file_size = size;
    }

    return succeeded;
};

bool file_trim(c_file_path const * path, unsigned int maximum_size)
{
    mangled_ppc("?file_trim@@YA_NPBVc_file_path@@I@Z");

    unsigned int const k_working_buffer_size = 1024;
    char buffer[k_working_buffer_size];

    return file_trim_fast(path, maximum_size, buffer, k_working_buffer_size);
};

bool file_trim_fast(c_file_path const * path, unsigned int maximum_size, void * working_buffer, unsigned int working_buffer_size)
{
    mangled_ppc("?file_trim_fast@@YA_NPBVc_file_path@@IPAXI@Z");

    c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> open_flags;
    bool succeeded = false;
    s_file_accessor file;

    assert_tag_debug_untracked_jul_11_2011(269, working_buffer);
    assert_tag_debug_untracked_jul_11_2011(270, working_buffer_size>0);

    open_flags.set(_file_open_read_bit, true);
    open_flags.set(_file_open_write_bit, true);
    if (file_open(path, open_flags, _file_error_mode_report, &file) == _file_open_result_success)
    {
        unsigned int size = file_get_eof(&file);

        succeeded = true;
        if (size > maximum_size)
        {
            unsigned int bytes_remaining = maximum_size;
            unsigned int position_to_read = size - maximum_size;
            unsigned int write_position = 0;

            while (succeeded && bytes_remaining > 0)
            {
                unsigned int bytes_to_move = int_min(bytes_remaining, working_buffer_size);

                succeeded = succeeded && file_read_from_position(&file, position_to_read, bytes_to_move, _file_error_mode_report, working_buffer);
                succeeded = succeeded && file_write_to_position(&file, write_position, bytes_to_move, _file_error_mode_report, working_buffer);
                if (succeeded)
                {
                    position_to_read += bytes_to_move;
                    write_position += bytes_to_move;
                    bytes_remaining -= bytes_to_move;
                }
            }

            if (succeeded)
            {
                file_set_eof(&file, maximum_size);
            }
        }

        file_close(&file);
    }

    return succeeded;
};

bool directory_create_and_delete_contents(c_file_path const * path)
{
    mangled_ppc("?directory_create_and_delete_contents@@YA_NPBVc_file_path@@@Z");

    bool ok = false;
    s_find_files_data_stack find_data;
    s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> find_files_flags;
    c_file_path path_to_delete;

    if (directory_exists(path))
    {
        find_files_flags.clear();
        find_files_start(find_files_flags, path, NULL, &find_data.data);
        while (find_files_next(&find_data.data, &path_to_delete, NULL))
        {
            file_delete(&path_to_delete);
        }

        find_files_end(&find_data.data);
        ok = true;
    }
    else
    {
        ok = directory_create_recursive(path);
    }

    return ok;
};

bool directory_create_recursive(c_file_path const * path)
{
    mangled_ppc("?directory_create_recursive@@YA_NPBVc_file_path@@@Z");

    return file_create_parent_directories(path);
};

bool directory_copy_recursive(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode)
{
    mangled_ppc("?directory_copy_recursive@@YA_NPBVc_file_path@@0W4e_file_overwrite_mode@@@Z");

    s_find_files_data_stack search_state;
    c_file_path destination_file_path;
    c_file_path file_path;
    s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> copy_flags;
    bool all_succeeded = true;

    assert_tag_debug_untracked_jul_11_2011(362, source_path->is_directory());
    assert_tag_debug_untracked_jul_11_2011(363, destination_path->is_directory());

    file_create_parent_directories(destination_path);
    copy_flags.clear();
    copy_flags.set(_find_files_enumerate_files_with_directories_bit, true);
    find_files_start(copy_flags, source_path, NULL, &search_state.data);
    while (find_files_next(&search_state.data, &file_path, NULL))
    {
        s_static_string<256> name;
        destination_file_path.copy(destination_path);
        if (file_path.is_directory())
        {
            file_path.get_parent_directory(&name);
            destination_file_path.add_directory(name);
            if (!directory_copy_recursive(&file_path, &destination_file_path, overwrite_mode))
            {
                all_succeeded = false;
                break;
            }
        }
        else
        {
            file_path.get_filename(&name);
            destination_file_path.set_filename(name);
            if (!file_copy(&file_path, &destination_file_path, overwrite_mode))
            {
                all_succeeded = false;
                break;
            }
            else
            {
                file_set_read_only(&destination_file_path, false);
            }
        }
    }

    find_files_end(&search_state.data);
    if (all_succeeded && !directory_exists(destination_path))
    {
        all_succeeded = directory_create(destination_path);
    }

    return all_succeeded;
};

long find_files(s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> flags, c_file_path const * directory, char const * search_spec, long maximum_result_count, c_file_path * out_results)
{
    mangled_ppc("?find_files@@YAJV?$s_flags@W4e_find_files_flags@@K$02@@PBVc_file_path@@PBDJPAV2@@Z");

    long result_count = 0;
    s_find_files_data_stack state;

    assert_tag_debug_untracked_jul_11_2011(436, maximum_result_count>0);
    assert_tag_debug_untracked_jul_11_2011(437, out_results);

    find_files_start(flags, directory, search_spec, &state.data);
    while (result_count < maximum_result_count && find_files_next(&state.data, &out_results[result_count], NULL))
    {
        result_count++;
    }

    find_files_end(&state.data);

    assert_tag_debug_untracked_jul_11_2011(446, result_count<=maximum_result_count);

    return result_count;
};

