#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_synchronous_utilities_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_synchronous_utilities_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_utilities.h"
#include "foundation\baselib\files\file_time_windows.h"

/* ---------- constants */

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES (static_cast<unsigned long>(-1))
#endif

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * const k_find_files_default_search_spec = "*.*";

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<void *, 16>::k_element_count; // "?k_element_count@?$s_static_array@PAX$0BA@@@2JB"
// char const *const k_find_files_default_search_spec; // "?k_find_files_default_search_spec@@3PBDB"

// bool file_exists(class c_file_path const *);
// bool file_is_read_only(class c_file_path const *);
// bool file_set_read_only(class c_file_path const *, bool);
// bool file_get_size(class c_file_path const *, unsigned int *);
// bool file_create(class c_file_path const *, enum e_file_overwrite_mode);
// bool file_delete(class c_file_path const *);
// bool file_rename(class c_file_path const *, char const *);
// bool file_copy(class c_file_path const *, class c_file_path const *, enum e_file_overwrite_mode);
// bool file_move(class c_file_path const *, class c_file_path const *, enum e_file_overwrite_mode);
// bool file_build_temporary_path(char const *, class c_file_path *);
// bool directory_exists(class c_file_path const *);
// bool directory_create(class c_file_path const *);
// bool directory_delete_recursive(class c_file_path const *);
// bool directory_rename(class c_file_path const *, char const *);
// bool directory_move(class c_file_path const *, class c_file_path const *, enum e_file_overwrite_mode);
// void find_files_start(class s_flags<enum e_find_files_flags, unsigned long, 3>, class c_file_path const *, char const *, struct s_find_files_data *);
// void find_files_end(struct s_find_files_data *);
// bool find_files_next(struct s_find_files_data *, class c_file_path *, struct s_file_time *);
// public: void s_static_array<void *, 16>::set_all(void *const &);
// public: bool s_flags<enum e_find_files_flags, unsigned long, 3>::test(enum e_find_files_flags) const;
// public: bool s_flags<enum e_find_files_flags, unsigned long, 3>::valid(void) const;
// public: void *& s_static_array<void *, 16>::operator[]<long>(long);
// public: static bool s_flags<enum e_find_files_flags, unsigned long, 3>::valid_bit(enum e_find_files_flags);
// private: static unsigned long s_flags<enum e_find_files_flags, unsigned long, 3>::flag_size_type(enum e_find_files_flags);
// private: static unsigned long s_flags<enum e_find_files_flags, unsigned long, 3>::make_mask_with_all_valid_bits_on_size_type(void);
// public: static bool s_static_array<void *, 16>::valid<long>(long);
// private: static unsigned long s_flags<enum e_find_files_flags, unsigned long, 3>::make_N_bit_mask_size_type(enum e_find_files_flags);

bool file_exists(c_file_path const * path)
{
    mangled_ppc("?file_exists@@YA_NPBVc_file_path@@@Z");

    bool exists = false;
    s_static_string<256> full_path;
    path->get_full_path(&full_path);
    if (GetFileAttributesA(full_path) != INVALID_FILE_ATTRIBUTES)
    {
        exists = true;
    }
    else
    {
        unsigned long error = GetLastError();
        if (error == ERROR_ACCESS_DENIED)
        {
            exists = true;
        }

        if (!exists && error != ERROR_FILE_NOT_FOUND && error != ERROR_PATH_NOT_FOUND)
        {
            file_utility_error("file_exists", _file_error_mode_report, path, NULL);
        }
    }

    return exists;
};

bool file_is_read_only(c_file_path const * path)
{
    mangled_ppc("?file_is_read_only@@YA_NPBVc_file_path@@@Z");

    bool read_only = false;
    s_static_string<256> full_path;
    path->get_full_path(&full_path);
    unsigned long attributes = GetFileAttributesA(full_path);
    if (attributes != INVALID_FILE_ATTRIBUTES)
    {
        read_only = (attributes & FILE_ATTRIBUTE_READONLY) != 0;
    }
    else
    {
        file_utility_error("file_is_read_only", _file_error_mode_report, path, NULL);
    }

    return read_only;
};

bool file_set_read_only(c_file_path const * path, bool read_only)
{
    mangled_ppc("?file_set_read_only@@YA_NPBVc_file_path@@_N@Z");

    bool success = false;
    if (path->is_directory())
    {
        success = true;
    }
    else
    {
        unsigned long attributes = 0;
        s_static_string<256> full_path;
        path->get_full_path(&full_path);
        attributes = GetFileAttributesA(full_path);
        if (attributes != INVALID_FILE_ATTRIBUTES)
        {
            unsigned long new_attributes = attributes;
            read_only ? (new_attributes |= FILE_ATTRIBUTE_READONLY) : (new_attributes &= ~FILE_ATTRIBUTE_READONLY);
            if (new_attributes == attributes)
            {
                success = true;
            }
            else if (SetFileAttributesA(full_path, attributes))
            {
                success = true;
            }
        }
    }

    if (!success)
    {
        file_utility_error("file_set_read_only", _file_error_mode_report, path, NULL);
    }

    return success;
};

bool file_get_size(c_file_path const * path, unsigned int * out_size)
{
    mangled_ppc("?file_get_size@@YA_NPBVc_file_path@@PAI@Z");

    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(170, out_size);

    s_static_string<256> full_path;
    WIN32_FILE_ATTRIBUTE_DATA data;
    path->get_full_path(&full_path);
    if (GetFileAttributesExA(full_path, GetFileExInfoStandard, &data))
    {
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            *out_size = 0;
            success = true;
        }
        else
        {
            if (sizeof(*out_size) == sizeof(unsigned long))
            {
                *out_size = data.nFileSizeLow;
            }
            else if (sizeof(*out_size) == sizeof(unsigned __int64))
            {
                *out_size = static_cast<unsigned int>((static_cast<unsigned __int64>(data.nFileSizeHigh) << 32) | data.nFileSizeLow);
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(192, false, "unreachable");
            }

            success = true;
        }
    }
    else
    {
        file_utility_error("file_get_size", _file_error_mode_report, path, NULL);
    }

    return success;
};

bool file_create(c_file_path const * path, e_file_overwrite_mode overwrite_mode)
{
    mangled_ppc("?file_create@@YA_NPBVc_file_path@@W4e_file_overwrite_mode@@@Z");

    bool success = false;
    s_static_string<256> full_path;
    path->get_full_path(&full_path);
    if (path->is_directory())
    {
        if (CreateDirectoryA(full_path, NULL))
        {
            success = true;
        }
    }
    else
    {
        unsigned long creation_disposition = overwrite_mode == _file_overwrite_mode_overwrite ? CREATE_ALWAYS : CREATE_NEW;
        HANDLE file_handle = CreateFileA(full_path, GENERIC_WRITE, 0, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file_handle != NULL && file_handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(file_handle);
            success = true;
        }
    }

    if (success)
    {
    }
    else
    {
        file_utility_error("file_create", _file_error_mode_report, path, NULL);
    }

    return success;
};

bool file_delete(c_file_path const * path)
{
    mangled_ppc("?file_delete@@YA_NPBVc_file_path@@@Z");

    bool success = false;
    s_static_string<256> full_path;
    path->get_full_path(&full_path);
    if (path->is_directory())
    {
        if (RemoveDirectoryA(full_path))
        {
            success = true;
        }
    }
    else if (SetFileAttributesA(full_path, FILE_ATTRIBUTE_NORMAL) && DeleteFileA(full_path))
    {
        success = true;
    }

    if (success)
    {
    }
    else
    {
        file_utility_error("file_delete", _file_error_mode_report, path, NULL);
    }

    return success;
};

bool file_rename(c_file_path const * path, char const * new_name)
{
    mangled_ppc("?file_rename@@YA_NPBVc_file_path@@PBD@Z");

    bool success = false;
    s_static_string<256> old_full_path;
    path->get_full_path(&old_full_path);

    c_file_path new_file;
    new_file.copy(path);
    if (new_file.is_directory())
    {
        new_file.remove_directory();
        new_file.add_directory(new_name);
    }
    else
    {
        new_file.remove_filename();
        new_file.set_filename(new_name);
    }

    s_static_string<256> destination_full_path;
    new_file.get_full_path(&destination_full_path);
    if (MoveFileA(old_full_path, destination_full_path))
    {
        success = true;
    }
    else
    {
        file_utility_error("file_rename", _file_error_mode_report, path, &new_file);
    }

    return success;
};

bool file_copy(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode)
{
    mangled_ppc("?file_copy@@YA_NPBVc_file_path@@0W4e_file_overwrite_mode@@@Z");

    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(362, !source_path->is_directory());
    assert_tag_debug_untracked_jul_11_2011(363, !destination_path->is_directory());

    file_create_parent_directories(destination_path);

    s_static_string<256> source_full_path;
    s_static_string<256> destination_full_path;
    source_path->get_full_path(&source_full_path);
    destination_path->get_full_path(&destination_full_path);
    if (CopyFileA(source_full_path, destination_full_path, overwrite_mode == _file_overwrite_mode_fail_if_exists))
    {
        success = true;
    }
    else
    {
        file_utility_error("file_copy", _file_error_mode_report, source_path, destination_path);
    }

    return success;
};

bool file_move(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode)
{
    mangled_ppc("?file_move@@YA_NPBVc_file_path@@0W4e_file_overwrite_mode@@@Z");

    unsigned long move_flags = overwrite_mode == _file_overwrite_mode_overwrite ? MOVEFILE_REPLACE_EXISTING : 0;
    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(405, source_path->is_directory()==destination_path->is_directory());

    file_create_parent_directories(destination_path);

    s_static_string<256> source_full_path;
    s_static_string<256> destination_full_path;
    source_path->get_full_path(&source_full_path);
    destination_path->get_full_path(&destination_full_path);
    if (MoveFileExA(source_full_path, destination_full_path, move_flags))
    {
        success = true;
    }
    else
    {
        file_utility_error("file_move", _file_error_mode_report, source_path, destination_path);
    }

    return success;
};

bool file_build_temporary_path(char const * name, c_file_path * out_path)
{
    mangled_ppc("?file_build_temporary_path@@YA_NPBDPAVc_file_path@@@Z");

    bool success = false;

    return success;
};

bool directory_exists(c_file_path const * path)
{
    mangled_ppc("?directory_exists@@YA_NPBVc_file_path@@@Z");

    return file_exists(path);
};

bool directory_create(c_file_path const * path)
{
    mangled_ppc("?directory_create@@YA_NPBVc_file_path@@@Z");

    return file_create(path, _file_overwrite_mode_fail_if_exists);
};

bool directory_delete_recursive(c_file_path const * path)
{
    mangled_ppc("?directory_delete_recursive@@YA_NPBVc_file_path@@@Z");

    return file_delete(path);
};

bool directory_rename(c_file_path const * path, char const * new_name)
{
    mangled_ppc("?directory_rename@@YA_NPBVc_file_path@@PBD@Z");

    return file_rename(path, new_name);
};

bool directory_move(c_file_path const * source_path, c_file_path const * destination_path, e_file_overwrite_mode overwrite_mode)
{
    mangled_ppc("?directory_move@@YA_NPBVc_file_path@@0W4e_file_overwrite_mode@@@Z");

    return file_move(source_path, destination_path, overwrite_mode);
};

void find_files_start(s_flags<e_find_files_flags, unsigned long, k_find_files_flags_count> flags, c_file_path const * directory, char const * search_spec, s_find_files_data * find_files_data)
{
    mangled_ppc("?find_files_start@@YAXV?$s_flags@W4e_find_files_flags@@K$02@@PBVc_file_path@@PBDPAUs_find_files_data@@@Z");

    s_find_files_data * state = find_files_data;
    assert_tag_debug_untracked_jul_11_2011(538, state);
    assert_tag_debug_untracked_jul_11_2011(539, flags.valid());
    assert_tag_debug_untracked_jul_11_2011(540, directory->is_directory());

    csmemset(state, 0, sizeof(s_find_files_data));
    state->flags = flags;
    state->directory.copy(directory);
    state->depth = 0;
    state->handles.set_all(INVALID_HANDLE_VALUE);
    if (search_spec == NULL)
    {
        state->search_spec.set(k_find_files_default_search_spec);
    }
    else
    {
        state->search_spec.set(search_spec);
    }
};

void find_files_end(s_find_files_data * find_files_data)
{
    mangled_ppc("?find_files_end@@YAXPAUs_find_files_data@@@Z");

    s_find_files_data * state = find_files_data;
    for (long depth = state->depth; depth >= 0; depth--)
    {
        if (state->handles[depth] != NULL && state->handles[depth] != INVALID_HANDLE_VALUE)
        {
            CloseHandle(state->handles[depth]);
            state->handles[depth] = INVALID_HANDLE_VALUE;
        }
    }

    state->depth = 0;
};

bool find_files_next(s_find_files_data * find_files_data, c_file_path * out_path, s_file_time * out_time)
{
    mangled_ppc("?find_files_next@@YA_NPAUs_find_files_data@@PAVc_file_path@@PAUs_file_time@@@Z");

    s_find_files_data * state = find_files_data;
    long depth = state->depth;
    WIN32_FIND_DATAA * data = &state->find_data;
    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(583, out_path);

    while (depth >= 0 && !success)
    {
        if (state->handles[depth] == NULL || state->handles[depth] == INVALID_HANDLE_VALUE)
        {
            c_file_path search_path;
            search_path.copy(&state->directory);
            search_path.set_filename(state->search_spec);
            s_static_string<256> search_full_path;
            search_path.get_full_path(&search_full_path);
            state->handles[depth] = FindFirstFileA(search_full_path, data);
        }
        else if (!FindNextFileA(state->handles[depth], data))
        {
            CloseHandle(state->handles[depth]);
            state->handles[depth] = INVALID_HANDLE_VALUE;
        }

        if (state->handles[depth] != NULL && state->handles[depth] != INVALID_HANDLE_VALUE)
        {
            if (data->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (strcmp_debug(data->cFileName, k_file_current_directory_string) != 0 && strcmp_debug(data->cFileName, k_file_parent_directory_string) != 0)
                {
                    bool added_path = false;
                    if (state->flags.test(_find_files_recursive_bit))
                    {
                        if (depth < k_find_files_maximum_search_depth - 1)
                        {
                            state->directory.add_directory(data->cFileName);
                            added_path = true;
                            depth++;
                        }
                        else
                        {
                            s_static_string<256> directory_path;
                            event(_event_error, "files: exceeded k_find_files_maximum_search_depth (%d) searching '%s'", k_find_files_maximum_search_depth, state->directory.get_full_path(&directory_path));
                        }
                    }

                    if (state->flags.test(_find_files_enumerate_directories_bit) || state->flags.test(_find_files_enumerate_files_with_directories_bit))
                    {
                        out_path->copy(&state->directory);
                        if (!added_path)
                        {
                            out_path->add_directory(data->cFileName);
                        }

                        if (out_time)
                        {
                            assert_tag_debug_untracked_jul_11_2011(630, sizeof(*out_time) == sizeof(data->ftLastWriteTime));
                            csmemcpy(out_time, &data->ftLastWriteTime, sizeof(*out_time));
                        }

                        success = true;
                    }
                }
            }
            else if (state->flags.test(_find_files_enumerate_files_with_directories_bit) || !state->flags.test(_find_files_enumerate_directories_bit))
            {
                out_path->copy(&state->directory);
                out_path->set_filename(data->cFileName);
                if (out_time)
                {
                    assert_tag_debug_untracked_jul_11_2011(645, sizeof(*out_time) == sizeof(data->ftLastWriteTime));
                    csmemcpy(out_time, &data->ftLastWriteTime, sizeof(*out_time));
                }

                success = true;
            }
        }
        else
        {
            if (depth > 0)
            {
                state->directory.remove_directory();
            }

            depth--;
        }
    }

    state->depth = depth;

    return success;
};

