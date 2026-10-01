#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\file_synchronous_io_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\files\file_synchronous_io_windows.h"
#include "baselib\file_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_path.h"
#include "foundation\baselib\files\file_synchronous_io.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// enum e_file_open_result file_open(class c_file_path const *, class c_flags_zero_init<enum e_file_open_flags, unsigned long, 8>, enum e_file_error_mode, struct s_file_accessor *);
// bool file_close(struct s_file_accessor *);
// bool file_get_read_only(struct s_file_accessor *);
// bool file_set_position(struct s_file_accessor *, unsigned int, enum e_file_error_mode);
// bool file_set_position_eof(struct s_file_accessor *);
// unsigned int file_get_eof(struct s_file_accessor *);
// bool file_set_eof(struct s_file_accessor *, unsigned int);
// bool file_at_eof(struct s_file_accessor *);
// bool file_flush(struct s_file_accessor *);
// bool file_read(struct s_file_accessor *, unsigned int, enum e_file_error_mode, void *);
// bool file_write(struct s_file_accessor *, unsigned int, enum e_file_error_mode, void const *);
// public: bool s_flags<enum e_file_open_flags, unsigned long, 8>::test(enum e_file_open_flags) const;

e_file_open_result file_open(c_file_path const * path, c_flags_zero_init<e_file_open_flags, unsigned long, k_file_open_flag_count> flags, e_file_error_mode error_mode, s_file_accessor * out_file)
{
    mangled_ppc("?file_open@@YA?AW4e_file_open_result@@PBVc_file_path@@V?$c_flags_zero_init@W4e_file_open_flags@@K$07@@W4e_file_error_mode@@PAUs_file_accessor@@@Z");

    e_file_open_result result = _file_open_result_success;
    DWORD access_flags = 0;
    DWORD share_mode = 0;
    DWORD flags_and_attributes = FILE_ATTRIBUTE_NORMAL;
    assert_tag_debug_untracked_jul_11_2011(110, path);
    assert_tag_debug_untracked_jul_11_2011(111, flags.valid());
    assert_tag_debug_untracked_jul_11_2011(112, flags.test(_file_open_read_bit) || flags.test(_file_open_write_bit));
    assert_tag_debug_untracked_jul_11_2011(113, flags.test(_file_open_write_bit) || !flags.test(_file_open_write_append_bit));
    assert_tag_debug_untracked_jul_11_2011(114, flags.test(_file_open_write_bit) || !flags.test(_file_open_write_allow_read_bit));
    assert_tag_debug_untracked_jul_11_2011(115, !(flags.test(_file_open_random_access_bit) && flags.test(_file_open_sequential_scan_bit)));
    assert_tag_debug_untracked_jul_11_2011(116, VALID_INDEX(error_mode, k_file_error_mode_count));
    assert_tag_debug_untracked_jul_11_2011(117, out_file);

    file_invalidate(out_file);

    s_static_string<256> filename;
    path->get_full_path(&filename);

    access_flags |= flags.test(_file_open_read_bit) ? GENERIC_READ : 0;
    access_flags |= flags.test(_file_open_write_bit) ? GENERIC_WRITE : 0;

    if (!flags.test(_file_open_write_bit) || flags.test(_file_open_write_allow_read_bit))
    {
        share_mode = FILE_SHARE_READ;
    }

    if (flags.test(_file_open_temporary_bit))
    {
        flags_and_attributes &= ~FILE_ATTRIBUTE_NORMAL;
        flags_and_attributes |= FILE_ATTRIBUTE_TEMPORARY;
    }

    flags_and_attributes |= flags.test(_file_open_delete_on_close_bit) ? FILE_FLAG_DELETE_ON_CLOSE : 0;
    flags_and_attributes |= flags.test(_file_open_random_access_bit) ? FILE_FLAG_RANDOM_ACCESS : 0;
    flags_and_attributes |= flags.test(_file_open_sequential_scan_bit) ? FILE_FLAG_SEQUENTIAL_SCAN : 0;

    HANDLE handle = CreateFileA(filename, access_flags, share_mode, NULL, OPEN_EXISTING, flags_and_attributes, NULL);
    if (handle != NULL && handle != INVALID_HANDLE_VALUE)
    {
        out_file->handle = handle;
        out_file->location = path->get_location();
        out_file->position = 0;
        out_file->path.set(filename);
    }
    else
    {
        DWORD last_error = GetLastError();
        switch (last_error)
        {
        case ERROR_FILE_NOT_FOUND:
            result = _file_open_result_file_not_found;
            break;
        case ERROR_ACCESS_DENIED:
            result = _file_open_result_access_denied;
            break;
        case ERROR_INVALID_NAME:
            result = _file_open_result_invalid_name;
            break;
        case ERROR_PATH_NOT_FOUND:
            result = _file_open_result_path_not_found;
            break;
        case ERROR_INVALID_DRIVE:
            result = _file_open_result_invalid_drive;
            break;
        case ERROR_SHARING_VIOLATION:
            result = _file_open_result_sharing_violation;
            break;
        default:
            event(_event_error, "files:file_open: unknown file error 0x%08X", last_error);
            result = _file_open_result_unknown_error;
            break;
        }
    }

    if (result == _file_open_result_success && flags.test(_file_open_write_append_bit))
    {
        if (file_set_position_eof(out_file))
        {
        }
        else
        {
            file_close(out_file);
            result = _file_open_result_append_failed;
        }
    }

    if (result != _file_open_result_success)
    {
        file_utility_error("file_open", error_mode, path, NULL);
    }

    return result;
};

bool file_close(s_file_accessor * file)
{
    mangled_ppc("?file_close@@YA_NPAUs_file_accessor@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(223, file_valid(file));

    if (CloseHandle(file->handle))
    {
        file_invalidate(file);
        result = true;
    }
    else
    {
        file_error("file_close", _file_error_mode_report, file);
    }

    return result;
};

bool file_get_read_only(s_file_accessor * file)
{
    mangled_ppc("?file_get_read_only@@YA_NPAUs_file_accessor@@@Z");

    bool result = false;
    BY_HANDLE_FILE_INFORMATION file_information;
    assert_tag_debug_untracked_jul_11_2011(255, file_valid(file));

    if (GetFileInformationByHandle(file->handle, &file_information) && file_information.dwFileAttributes != INVALID_FILE_ATTRIBUTES)
    {
        result = (file_information.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0;
    }
    else
    {
        file_error("file_get_read_only", _file_error_mode_report, file);
    }

    return result;
};

bool file_set_position(s_file_accessor * file, unsigned int position, e_file_error_mode error_mode)
{
    mangled_ppc("?file_set_position@@YA_NPAUs_file_accessor@@IW4e_file_error_mode@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(279, file_valid(file));

    if (file->position == position)
    {
        result = true;
    }
    else
    {
        file->position = SetFilePointer(file->handle, position, NULL, FILE_BEGIN);
        result = file->position != INVALID_SET_FILE_POINTER;
        if (result)
        {
        }
        else
        {
            file_error("file_set_position", error_mode, file);
        }
    }

    return result;
};

bool file_set_position_eof(s_file_accessor * file)
{
    mangled_ppc("?file_set_position_eof@@YA_NPAUs_file_accessor@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(331, file_valid(file));

    file->position = SetFilePointer(file->handle, 0, NULL, FILE_END);
    if (file->position != INVALID_SET_FILE_POINTER)
    {
        result = true;
    }
    else
    {
        file_error("file_set_position_eof", _file_error_mode_report, file);
    }

    return result;
};

unsigned int file_get_eof(s_file_accessor * file)
{
    mangled_ppc("?file_get_eof@@YAIPAUs_file_accessor@@@Z");

    unsigned int eof = INVALID_FILE_SIZE;
    assert_tag_debug_untracked_jul_11_2011(361, file_valid(file));

    eof = GetFileSize(file->handle, NULL);
    if (eof == INVALID_FILE_SIZE)
    {
        file_error("file_get_eof", _file_error_mode_report, file);
    }

    return eof;
};

bool file_set_eof(s_file_accessor * file, unsigned int size)
{
    mangled_ppc("?file_set_eof@@YA_NPAUs_file_accessor@@I@Z");

    bool result = file_set_position(file, size, _file_error_mode_report);
    if (result)
    {
        result = SetEndOfFile(file->handle) != 0;
    }

    if (!result)
    {
        file_error("file_set_eof", _file_error_mode_report, file);
    }

    return result;
};

bool file_at_eof(s_file_accessor * file)
{
    mangled_ppc("?file_at_eof@@YA_NPAUs_file_accessor@@@Z");

    bool result = false;
    unsigned int eof = file_get_eof(file);
    if (eof != INVALID_FILE_SIZE && file->position == eof)
    {
        result = true;
    }

    return result;
};

bool file_flush(s_file_accessor * file)
{
    mangled_ppc("?file_flush@@YA_NPAUs_file_accessor@@@Z");

    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(427, file_valid(file));

    if (FlushFileBuffers(file->handle))
    {
        result = true;
    }
    else
    {
        file_error("file_flush", _file_error_mode_report, file);
    }

    return result;
};

bool file_read(s_file_accessor * file, unsigned int count, e_file_error_mode error_mode, void * buffer)
{
    mangled_ppc("?file_read@@YA_NPAUs_file_accessor@@IW4e_file_error_mode@@PAX@Z");

    DWORD bytes_to_read = 0;
    DWORD bytes_read = 0;
    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(456, count>0 && count<=k_uint32_max);
    assert_tag_debug_untracked_jul_11_2011(457, buffer);
    assert_tag_debug_untracked_jul_11_2011(458, file_valid(file));

    bytes_to_read = count;
    if (ReadFile(file->handle, buffer, bytes_to_read, &bytes_read, NULL))
    {
        if (bytes_read == bytes_to_read)
        {
            success = true;
        }
        else
        {
            SetLastError(ERROR_HANDLE_EOF);
        }
    }

    file->position += bytes_read;
    if (!success)
    {
        file_error("file_read", error_mode, file);
    }

    return success;
};

bool file_write(s_file_accessor * file, unsigned int count, e_file_error_mode error_mode, void const * buffer)
{
    mangled_ppc("?file_write@@YA_NPAUs_file_accessor@@IW4e_file_error_mode@@PBX@Z");

    DWORD bytes_to_write = 0;
    DWORD bytes_written = 0;
    bool result = false;
    assert_tag_debug_untracked_jul_11_2011(498, count>0 && count<=k_uint32_max);
    assert_tag_debug_untracked_jul_11_2011(499, buffer);
    assert_tag_debug_untracked_jul_11_2011(500, file_valid(file));

    bytes_to_write = count;
    if (WriteFile(file->handle, buffer, bytes_to_write, &bytes_written, NULL) && bytes_written == bytes_to_write)
    {
        result = true;
    }
    else
    {
        file_error("file_write", error_mode, file);
    }

    file->position += bytes_written;

    return result;
};

