#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\file_output_buffer.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\file_output_buffer.h"
#include "baselib\file_interface.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\files\file_errors.h"
#include "foundation\baselib\files\file_synchronous_io.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_file_output_buffer::c_file_output_buffer(void);
// public: c_file_output_buffer::~c_file_output_buffer(void);
// public: void c_file_output_buffer::attach_file(struct s_file_accessor *);
// public: void c_file_output_buffer::release_file(void);
// public: void c_file_output_buffer::write(long, void const *);
// public: void c_file_output_buffer::flush(void);
// private: void c_file_output_buffer::write_internal(long, void const *);
// public: static long s_static_array<unsigned char, 16384>::get_count(void);
// public: unsigned char & s_static_array<unsigned char, 16384>::operator[]<long>(long);

c_file_output_buffer::c_file_output_buffer(void) :
    m_file(NULL),
    m_buffer_length(0)
{
    mangled_ppc("??0c_file_output_buffer@@QAA@XZ");
};

c_file_output_buffer::~c_file_output_buffer(void)
{
    mangled_ppc("??1c_file_output_buffer@@QAA@XZ");

    release_file();
};

void c_file_output_buffer::attach_file(s_file_accessor * file)
{
    mangled_ppc("?attach_file@c_file_output_buffer@@QAAXPAUs_file_accessor@@@Z");

    release_file();
    assert_tag_debug_untracked_jul_11_2011(34, file_valid(file));
    assert_tag_debug_untracked_jul_11_2011(35, m_file==NULL);

    m_file = file;
};

void c_file_output_buffer::release_file(void)
{
    mangled_ppc("?release_file@c_file_output_buffer@@QAAXXZ");

    if (m_file != NULL)
    {
        flush();
        m_file = NULL;
    }
};

void c_file_output_buffer::write(long buffer_size, void const * buffer)
{
    mangled_ppc("?write@c_file_output_buffer@@QAAXJPBX@Z");

    if (m_file != NULL)
    {
        if (m_buffer_length + buffer_size > m_buffer.get_count())
        {
            flush();
        }

        if (m_buffer_length + buffer_size <= m_buffer.get_count())
        {
            csmemcpy(&m_buffer[m_buffer_length], buffer, buffer_size);
            m_buffer_length += buffer_size;
        }
        else
        {
            assert_tag_debug_untracked_jul_11_2011(67, m_buffer_length==0);
            write_internal(buffer_size, buffer);
        }
    }
};

void c_file_output_buffer::flush(void)
{
    mangled_ppc("?flush@c_file_output_buffer@@QAAXXZ");

    if (m_buffer_length > 0)
    {
        assert_tag_debug_untracked_jul_11_2011(78, m_file!=NULL);

        write_internal(m_buffer_length, m_buffer.get_elements());
        m_buffer_length = 0;
    }
};

void c_file_output_buffer::write_internal(long buffer_size, void const * buffer)
{
    mangled_ppc("?write_internal@c_file_output_buffer@@AAAXJPBX@Z");

    assert_tag_debug_untracked_jul_11_2011(88, m_file!=NULL);

    file_write(m_file, buffer_size, _file_error_mode_report, buffer);
};
