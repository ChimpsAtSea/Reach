#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\files\\simple_file.cpp"
/* ---------- headers */

#include "foundation\baselib\files\simple_file.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\files\debug_paths.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_synchronous_utilities_windows.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_simple_file::c_simple_file(void);
// public: c_simple_file::c_simple_file(char const *);
// public: c_simple_file::c_simple_file(class c_file_path const *);
// public: c_simple_file::~c_simple_file(void);
// public: enum e_file_error_mode c_simple_file::get_error_mode(void) const;
// public: bool c_simple_file::is_silent(void) const;
// public: void c_simple_file::set_debug_filename(char const *);
// public: void c_simple_file::set_path(class c_file_path const *);
// public: bool c_simple_file::open(long);
// public: void c_simple_file::close(void);
// public: unsigned int c_simple_file::get_position(void);
// public: bool c_simple_file::set_position(unsigned int);
// public: bool c_simple_file::set_position_eof(void);
// public: bool c_simple_file::at_eof(void);
// public: void c_simple_file::flush(void);
// public: void c_simple_file::print(char const *);
// public: void c_simple_file::printf(char const *, ...);
// public: void c_simple_file::vprintf(char const *, char *);
// public: bool c_simple_file::read(unsigned int, void *);
// public: bool c_simple_file::write(unsigned int, void const *);
// public: bool c_simple_file::read_from_position(unsigned int, unsigned int, void *);
// public: bool c_simple_file::write_to_position(unsigned int, unsigned int, void const *);
// struct _iobuf * platform_fopen(char const *, char const *);
// unsigned int platform_fseek(struct _iobuf *, unsigned int, long);
// __int64 platform_ftell(struct _iobuf *);

c_simple_file::c_simple_file(void)
{
    mangled_ppc("??0c_simple_file@@QAA@XZ");

    m_flags = 0;
    m_file_handle = NULL;
    m_path.clear();
};

c_simple_file::c_simple_file(char const * debug_filename)
{
    mangled_ppc("??0c_simple_file@@QAA@PBD@Z");

    m_flags = 0;
    m_file_handle = NULL;
    set_debug_filename(debug_filename);
};

c_simple_file::c_simple_file(c_file_path const * path)
{
    mangled_ppc("??0c_simple_file@@QAA@PBVc_file_path@@@Z");

    m_flags = 0;
    m_file_handle = NULL;
    set_path(path);
};

c_simple_file::~c_simple_file(void)
{
    mangled_ppc("??1c_simple_file@@QAA@XZ");

    close();
};

e_file_error_mode c_simple_file::get_error_mode(void) const
{
    mangled_ppc("?get_error_mode@c_simple_file@@QBA?AW4e_file_error_mode@@XZ");

    return is_silent() ? _file_error_mode_silent : _file_error_mode_report;
};

bool c_simple_file::is_silent(void) const
{
    mangled_ppc("?is_silent@c_simple_file@@QBA_NXZ");

    return TEST_BIT(m_flags, _simple_file_silent_bit);
};

void c_simple_file::set_debug_filename(char const * filename)
{
    mangled_ppc("?set_debug_filename@c_simple_file@@QAAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(72, filename);
    assert_tag_debug_untracked_jul_11_2011(73, m_file_handle==NULL);

    c_debug_path debug_path;
    debug_path.get_path(filename, &m_path);
};

void c_simple_file::set_path(c_file_path const * path)
{
    mangled_ppc("?set_path@c_simple_file@@QAAXPBVc_file_path@@@Z");

    assert_tag_debug_untracked_jul_11_2011(87, path);
    assert_tag_debug_untracked_jul_11_2011(88, m_file_handle==NULL);

    m_path.copy(path);
};

bool c_simple_file::open(long flags)
{
    mangled_ppc("?open@c_simple_file@@QAA_NJ@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(100, m_file_handle==NULL);
    assert_tag_debug_untracked_jul_11_2011(101, TEST_BIT(flags, _simple_file_open_read_bit) || TEST_BIT(flags, _simple_file_open_write_bit));
    assert_tag_debug_untracked_jul_11_2011(102, !(TEST_BIT(flags, _simple_file_open_read_bit) && TEST_BIT(flags, _simple_file_open_write_bit)));
    assert_tag_debug_untracked_jul_11_2011(104, TEST_BIT(flags, _simple_file_open_write_bit) || !(TEST_BIT(flags, _simple_file_open_write_append_bit) || TEST_BIT(flags, _simple_file_open_write_allow_read_bit)));

    s_static_string<16> mode;
    mode.clear();
    if (TEST_BIT(flags, _simple_file_open_read_bit))
    {
        mode.append("r");
    }
    else
    {
        assert_tag_debug_untracked_jul_11_2011(113, TEST_BIT(flags, _simple_file_open_write_bit));

        mode.append(TEST_BIT(flags, _simple_file_open_write_append_bit) ? "a" : "w");
        if (TEST_BIT(flags, _simple_file_open_write_allow_read_bit) || (TEST_BIT(flags, _simple_file_open_write_append_bit) && !TEST_BIT(flags, _simple_file_open_binary_bit)))
        {
            mode.append("+");
        }
    }
    mode.append(TEST_BIT(flags, _simple_file_open_binary_bit) ? "b" : "t");

    s_static_string<256> path;
    m_path.get_full_path(&path);
    FILE * handle = platform_fopen(path, mode);
    if (handle != NULL)
    {
        SET_BIT(m_flags, _simple_file_silent_bit, TEST_BIT(flags, _simple_file_open_silent_bit));
        SET_BIT(m_flags, _simple_file_delete_on_close_bit, TEST_BIT(flags, _simple_file_open_delete_on_close_bit));
        SET_BIT(m_flags, _simple_file_reading_bit, TEST_BIT(flags, _simple_file_open_read_bit) || TEST_BIT(flags, _simple_file_open_write_allow_read_bit));
        SET_BIT(m_flags, _simple_file_writing_bit, TEST_BIT(flags, _simple_file_open_write_bit));
        m_file_handle = handle;
        success = true;
    }
    else
    {
        file_utility_error("c_simple_file::open", get_error_mode(), &m_path, NULL);
    }

    return success;
};

void c_simple_file::close(void)
{
    mangled_ppc("?close@c_simple_file@@QAAXXZ");

    if (m_file_handle != NULL)
    {
        unsigned char delete_on_close = TEST_BIT(m_flags, _simple_file_delete_on_close_bit);
        fclose(m_file_handle);
        m_file_handle = NULL;
        m_flags = 0;
        if (delete_on_close)
        {
            file_delete(&m_path);
        }
    }
};

unsigned int c_simple_file::get_position(void)
{
    mangled_ppc("?get_position@c_simple_file@@QAAIXZ");

    assert_tag_debug_untracked_jul_11_2011(173, m_file_handle!=NULL);

    __int64 position = platform_ftell(m_file_handle);
    if (position < 0)
    {
        file_utility_error("c_simple_file::get_position", get_error_mode(), &m_path, NULL);
        position = 0;
    }

    return static_cast<unsigned int>(position);
};

bool c_simple_file::set_position(unsigned int position)
{
    mangled_ppc("?set_position@c_simple_file@@QAA_NI@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(190, m_file_handle!=NULL);

    if (platform_fseek(m_file_handle, position, SEEK_SET) == 0)
    {
        success = true;
    }
    else
    {
        file_utility_error("c_simple_file::set_position", get_error_mode(), &m_path, NULL);
    }

    return success;
};

bool c_simple_file::set_position_eof(void)
{
    mangled_ppc("?set_position_eof@c_simple_file@@QAA_NXZ");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(208, m_file_handle!=NULL);

    if (platform_fseek(m_file_handle, 0, SEEK_END) == 0)
    {
        success = true;
    }
    else
    {
        file_utility_error("c_simple_file::set_position_eof", get_error_mode(), &m_path, NULL);
    }

    return success;
};

bool c_simple_file::at_eof(void)
{
    mangled_ppc("?at_eof@c_simple_file@@QAA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(224, m_file_handle!=NULL);

    return feof(m_file_handle) != 0;
};

void c_simple_file::flush(void)
{
    mangled_ppc("?flush@c_simple_file@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(231, m_file_handle!=NULL);

    fflush(m_file_handle);
};

void c_simple_file::print(char const * string)
{
    mangled_ppc("?print@c_simple_file@@QAAXPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(238, string);
    assert_tag_debug_untracked_jul_11_2011(239, m_file_handle!=NULL);
    assert_tag_debug_untracked_jul_11_2011(240, TEST_BIT(m_flags, _simple_file_writing_bit));

    if (fputs(string, m_file_handle) != 0)
    {
        file_utility_error("c_simple_file::print", get_error_mode(), &m_path, NULL);
    }
};

void c_simple_file::printf(char const * format, ...)
{
    mangled_ppc("?printf@c_simple_file@@QAAXPBDZZ");

    va_list arglist;
    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);
};

void c_simple_file::vprintf(char const * format, char * arglist)
{
    mangled_ppc("?vprintf@c_simple_file@@QAAXPBDPAD@Z");

    s_static_string<1024> string;
    string.print_va(format, arglist);
    print(string.get_string());
};

bool c_simple_file::read(unsigned int size, void * buffer)
{
    mangled_ppc("?read@c_simple_file@@QAA_NIPAX@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(275, buffer);
    assert_tag_debug_untracked_jul_11_2011(276, m_file_handle!=NULL);
    assert_tag_debug_untracked_jul_11_2011(277, TEST_BIT(m_flags, _simple_file_reading_bit));

    unsigned int size_read = fread(buffer, 1, size, m_file_handle);
    if (size_read == size)
    {
        success = true;
    }
    else
    {
        file_utility_error("c_simple_file::read", get_error_mode(), &m_path, NULL);
    }

    return success;
};

bool c_simple_file::write(unsigned int size, void const * buffer)
{
    mangled_ppc("?write@c_simple_file@@QAA_NIPBX@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(299, buffer);
    assert_tag_debug_untracked_jul_11_2011(300, m_file_handle!=NULL);
    assert_tag_debug_untracked_jul_11_2011(301, TEST_BIT(m_flags, _simple_file_writing_bit));

    unsigned int bytes_written = fwrite(buffer, 1, size, m_file_handle);
    if (bytes_written == size)
    {
        success = true;
    }
    else
    {
        file_utility_error("c_simple_file::write", get_error_mode(), &m_path, NULL);
    }

    return success;
};

bool c_simple_file::read_from_position(unsigned int position, unsigned int size, void * buffer)
{
    mangled_ppc("?read_from_position@c_simple_file@@QAA_NIIPAX@Z");

    return set_position(position) && read(size, buffer);
};

bool c_simple_file::write_to_position(unsigned int position, unsigned int size, void const * buffer)
{
    mangled_ppc("?write_to_position@c_simple_file@@QAA_NIIPBX@Z");

    return set_position(position) && write(size, buffer);
};

FILE * platform_fopen(char const * filename, char const * mode)
{
    mangled_ppc("?platform_fopen@@YAPAU_iobuf@@PBD0@Z");

    FILE * file = NULL;
    fopen_s(&file, filename, mode);

    return file;
};

unsigned int platform_fseek(FILE * file, unsigned int offset, long origin)
{
    mangled_ppc("?platform_fseek@@YAIPAU_iobuf@@IJ@Z");

    return _fseeki64(file, offset, origin);
};

__int64 platform_ftell(FILE * file)
{
    mangled_ppc("?platform_ftell@@YA_JPAU_iobuf@@@Z");

    return _ftelli64(file);
};
