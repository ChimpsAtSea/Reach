#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\toolbox\\file_helpers.cpp"
/* ---------- headers */

#include "omaha\toolbox\file_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_file_finder::c_file_finder(unsigned long, struct s_file_reference const *);
// public: c_file_finder::c_file_finder(unsigned long, struct s_file_reference const *, char const *);
// public: c_file_finder::~c_file_finder(void);
// public: bool c_file_finder::next(struct s_file_reference *, struct s_file_last_modification_date *);
// public: c_aligned_buffered_file_writer::c_aligned_buffered_file_writer(void);
// public: void c_aligned_buffered_file_writer::initialize(struct s_file_reference *, char *, long);
// private: unsigned long c_aligned_buffered_file_writer::get_physical_file_size(void);
// private: bool c_aligned_buffered_file_writer::get_is_at_end_of_phyisical_file(void);
// public: bool c_aligned_buffered_file_writer::write(char const *, long);
// private: bool c_aligned_buffered_file_writer::read_current_block_into_buffer(void);
// public: bool c_aligned_buffered_file_writer::flush(void);
// public: unsigned long c_aligned_buffered_file_writer::get_position(void);
// public: bool c_aligned_buffered_file_writer::set_position(unsigned long);

c_file_finder::c_file_finder(unsigned long flags, s_file_reference const * starting_directory)
{
    mangled_ppc("??0c_file_finder@@QAA@KPBUs_file_reference@@@Z");

    find_files_start(&m_find_file_data, flags, starting_directory);
};

c_file_finder::c_file_finder(unsigned long flags, s_file_reference const * starting_directory, char const * file_spec)
{
    mangled_ppc("??0c_file_finder@@QAA@KPBUs_file_reference@@PBD@Z");

    find_files_start_with_search_spec(&m_find_file_data, flags, starting_directory, file_spec);
};

c_file_finder::~c_file_finder(void)
{
    mangled_ppc("??1c_file_finder@@QAA@XZ");

    find_files_end(&m_find_file_data);
};

bool c_file_finder::next(s_file_reference * out_file_reference, s_file_last_modification_date * out_modification_date)
{
    mangled_ppc("?next@c_file_finder@@QAA_NPAUs_file_reference@@PAUs_file_last_modification_date@@@Z");

    return find_files_next(&m_find_file_data, out_file_reference, out_modification_date);
};

c_aligned_buffered_file_writer::c_aligned_buffered_file_writer(void)
{
    mangled_ppc("??0c_aligned_buffered_file_writer@@QAA@XZ");

    m_write_buffer = NULL;
    m_write_buffer_size = 0;
    m_write_buffer_count = 0;
};

void c_aligned_buffered_file_writer::initialize(s_file_reference * file, char * write_buffer, long write_buffer_size)
{
    mangled_ppc("?initialize@c_aligned_buffered_file_writer@@QAAXPAUs_file_reference@@PADJ@Z");

    m_file = file;
    m_write_buffer = write_buffer;
    m_write_buffer_size = write_buffer_size;
    m_write_buffer_count = 0;
};

unsigned long c_aligned_buffered_file_writer::get_physical_file_size(void)
{
    mangled_ppc("?get_physical_file_size@c_aligned_buffered_file_writer@@AAAKXZ");

    return file_get_eof(m_file);
};

bool c_aligned_buffered_file_writer::get_is_at_end_of_phyisical_file(void)
{
    mangled_ppc("?get_is_at_end_of_phyisical_file@c_aligned_buffered_file_writer@@AAA_NXZ");

    bool result = false;
    result = file_get_position(m_file) == get_physical_file_size();
    return result;
};

bool c_aligned_buffered_file_writer::write(char const * data, long count)
{
    mangled_ppc("?write@c_aligned_buffered_file_writer@@QAA_NPBDJ@Z");

    bool result = true;
    char const * position = data;
    while (result && count > 0)
    {
        long bytes_to_copy = count > m_write_buffer_size - m_write_buffer_count ? m_write_buffer_size - m_write_buffer_count : count;
        if (m_write_buffer_count == 0 && !read_current_block_into_buffer())
        {
            result = false;
            break;
        }
        memcpy(&m_write_buffer[m_write_buffer_count], position, bytes_to_copy);
        m_write_buffer_count += bytes_to_copy;
        if (m_write_buffer_count == m_write_buffer_size)
        {
            result = file_write(m_file, m_write_buffer_size, m_write_buffer);
            m_write_buffer_count = 0;
        }
        count -= bytes_to_copy;
        position += bytes_to_copy;
    }
    return result;
};

bool c_aligned_buffered_file_writer::read_current_block_into_buffer(void)
{
    mangled_ppc("?read_current_block_into_buffer@c_aligned_buffered_file_writer@@AAA_NXZ");

    bool result = true;
    unsigned long bytes_to_read = 0;
    assert_tag_debug_untracked_jul_11_2011(109, m_write_buffer_count == 0);
    if (!get_is_at_end_of_phyisical_file())
    {
        unsigned long original_offset = file_get_position(m_file);
        bytes_to_read = get_physical_file_size() > static_cast<unsigned long>(m_write_buffer_size) ? m_write_buffer_size : get_physical_file_size();
        if (!file_read(m_file, bytes_to_read, true, m_write_buffer) || !file_set_position(m_file, original_offset, true))
        {
            result = false;
        }
    }
    memset(m_write_buffer, 0, m_write_buffer_size - bytes_to_read);
    return result;
};

bool c_aligned_buffered_file_writer::flush(void)
{
    mangled_ppc("?flush@c_aligned_buffered_file_writer@@QAA_NXZ");

    bool result = true;
    if (m_write_buffer_count > 0)
    {
        result = file_write(m_file, m_write_buffer_size, m_write_buffer);
        m_write_buffer_count = 0;
    }
    return result;
};

unsigned long c_aligned_buffered_file_writer::get_position(void)
{
    mangled_ppc("?get_position@c_aligned_buffered_file_writer@@QAAKXZ");

    return file_get_position(m_file) + m_write_buffer_count;
};

bool c_aligned_buffered_file_writer::set_position(unsigned long offset)
{
    mangled_ppc("?set_position@c_aligned_buffered_file_writer@@QAA_NK@Z");

    bool result = false;
    if (flush())
    {
        unsigned long aligned_position = offset & ~(m_write_buffer_size - 1);
        assert_tag_debug_untracked_jul_11_2011(157, VALID_INDEX(offset-aligned_position, m_write_buffer_size));
        if (file_get_position(m_file) == offset)
        {
            result = true;
        }
        else if (file_set_position(m_file, aligned_position, true))
        {
            if (aligned_position == offset)
            {
                result = true;
            }
            else if (read_current_block_into_buffer())
            {
                m_write_buffer_count = offset - aligned_position;
                assert_tag_debug_untracked_jul_11_2011(175, get_position() == offset);
                assert_tag_debug_untracked_jul_11_2011(176, file_get_position(m_file)+m_write_buffer_count == offset);
                result = true;
            }
        }
    }
    return result;
};

