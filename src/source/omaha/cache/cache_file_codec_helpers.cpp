#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_codec_helpers.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_codec_helpers.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\memory\persist.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_bufferred_output_stream::c_bufferred_output_stream(class c_persist_stream *);
// public: c_bufferred_output_stream::~c_bufferred_output_stream(void);
// public: class c_basic_buffer<void> c_bufferred_output_stream::get_buffer(void);
// public: void c_bufferred_output_stream::commit_buffer(class c_basic_buffer<void>);
// public: bool c_bufferred_output_stream::flush(void);
// public: void c_bufferred_output_stream::flunk(void);

c_bufferred_output_stream::c_bufferred_output_stream(c_persist_stream * stream) :
    m_stream(stream),
    m_failed(false),
    m_write_buffer(m_write_buffer_storage, k_write_buffer_size),
    m_buffer_left()
{
    mangled_ppc("??0c_bufferred_output_stream@@QAA@PAVc_persist_stream@@@Z");

    m_buffer_left = m_write_buffer;
};

c_bufferred_output_stream::~c_bufferred_output_stream(void)
{
    mangled_ppc("??1c_bufferred_output_stream@@QAA@XZ");

    dassert_tag_debug_untracked_jul_11_2011(26, m_failed || m_buffer_left.begin()==m_write_buffer.begin(), "forget to flush?");
};

c_basic_buffer<void> c_bufferred_output_stream::get_buffer(void)
{
    mangled_ppc("?get_buffer@c_bufferred_output_stream@@QAA?AV?$c_basic_buffer@X@@XZ");

    return m_buffer_left;
};

void c_bufferred_output_stream::commit_buffer(c_basic_buffer<void> finished_buffer)
{
    mangled_ppc("?commit_buffer@c_bufferred_output_stream@@QAAXV?$c_basic_buffer@X@@@Z");

    assert_tag_debug_untracked_jul_11_2011(41, !m_failed);
    assert_tag_debug_untracked_jul_11_2011(43, m_buffer_left.begin()==finished_buffer.begin());
    assert_tag_debug_untracked_jul_11_2011(44, buffer_in_buffer(finished_buffer, m_buffer_left));

    m_buffer_left.advance_start(finished_buffer.size());
    assert_tag_debug_untracked_jul_11_2011(47, m_buffer_left.begin()==finished_buffer.end());

    if (m_buffer_left.empty())
    {
        bool must_succeed = flush();
        assert_tag_debug_untracked_jul_11_2011(52, must_succeed);
    }

    assert_tag_debug_untracked_jul_11_2011(55, !m_buffer_left.empty());
};

bool c_bufferred_output_stream::flush(void)
{
    mangled_ppc("?flush@c_bufferred_output_stream@@QAA_NXZ");

    assert_tag_debug_untracked_jul_11_2011(63, !m_failed);
    assert_tag_debug_untracked_jul_11_2011(65, buffer_in_buffer(m_buffer_left, m_write_buffer));
    assert_tag_debug_untracked_jul_11_2011(66, m_buffer_left.end()==m_write_buffer.end());

    c_basic_buffer<void> finished_buffer(m_write_buffer.begin(), m_buffer_left.begin());
    bool success;
    if (finished_buffer.empty())
    {
        success = true;
    }
    else
    {
        success = m_stream->write(finished_buffer.begin(), finished_buffer.size());
        assert_tag_debug_untracked_jul_11_2011(79, success);
    }

    m_buffer_left = m_write_buffer;

    return success;
};

void c_bufferred_output_stream::flunk(void)
{
    mangled_ppc("?flunk@c_bufferred_output_stream@@QAAXXZ");

    m_failed = true;
};
