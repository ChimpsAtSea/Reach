#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\xenon\\dsp\\xaudio_output_ring_buffer.cpp"
/* ---------- headers */

#include "omaha\sound\xenon\dsp\xaudio_output_ring_buffer.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\runtime_state.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_xaudio_output_ring_buffer::initialize(char const *, long);
// public: long c_xaudio_output_ring_buffer::get_ring_count(void) const;
// public: float const * c_xaudio_output_ring_buffer::get_last_frame_output(long) const;
// public: void c_xaudio_output_ring_buffer::accumulate_current_frame_output(long, class c_wrapped_array<float const>) const;
// public: void c_xaudio_output_ring_buffer::update_on_frame_start(void);
// public: void c_xaudio_output_ring_buffer::reset(void);
// public: void c_xaudio_output_ring_buffer::register_engine_callbacks(void);
// private: static void c_xaudio_output_ring_buffer::xaudio_frame_start_callback(void *);
// public: static long s_static_array<class c_wrapped_array<class s_static_array<float, 256> >, 2>::get_count(void);
// public: class s_static_array<float, 256> & c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::operator[](long);
// public: class s_static_array<float, 256> const & c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::operator[](long) const;
// public: class s_static_array<float, 256> * c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::get_elements(void);
// public: long c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::get_total_element_size(void) const;
// public: bool c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::valid_index(long) const;
// public: float const * s_static_array<float, 256>::get_elements(void) const;
// public: float const * c_wrapped_array_no_init<float const>::begin(void);
// public: long c_wrapped_array_no_init<float const>::count(void) const;
// public: class s_static_array<float, 256> * c_wrapped_array_no_init<class s_static_array<float, 256> >::begin(void);
// public: class s_static_array<float, 256> const * c_wrapped_array_no_init<class s_static_array<float, 256> >::begin(void) const;
// public: class s_static_array<float, 256> * c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::begin(void);
// public: long c_array_operator_interface<class c_wrapped_array_no_init<class s_static_array<float, 256> >, class s_static_array<float, 256> >::count(void) const;
// public: class c_wrapped_array_no_init<class s_static_array<float, 256> > * c_recursive_template_pattern<class c_wrapped_array_no_init<class s_static_array<float, 256> > >::get_super_class(void);
// public: class c_wrapped_array_no_init<class s_static_array<float, 256> > const * c_recursive_template_pattern<class c_wrapped_array_no_init<class s_static_array<float, 256> > >::get_super_class(void) const;
// public: long c_wrapped_array_no_init<class s_static_array<float, 256> >::count(void) const;
// public: class c_wrapped_array<class s_static_array<float, 256> > & s_static_array<class c_wrapped_array<class s_static_array<float, 256> >, 2>::operator[]<long>(long);
// class c_wrapped_array<class s_static_array<float, 256> > make_wrapped_array<class s_static_array<float, 256> >(class s_static_array<float, 256> *, long);
// public: c_wrapped_array<class s_static_array<float, 256> >::c_wrapped_array<class s_static_array<float, 256> >(class s_static_array<float, 256> *, long);
// public: static bool s_static_array<class c_wrapped_array<class s_static_array<float, 256> >, 2>::valid<long>(long);

void c_xaudio_output_ring_buffer::initialize(char const * name, long ring_count)
{
    mangled_ppc("?initialize@c_xaudio_output_ring_buffer@@QAAXPBDJ@Z");

    m_ring_count = ring_count;
    long size = ring_count * sizeof(s_static_array<float, XAUDIOFRAMESIZE_NATIVE>) * NUMBEROF(m_ring_buffers.m_elements);
    s_static_array<float, XAUDIOFRAMESIZE_NATIVE> * ring_buffer_raw_data = static_cast<s_static_array<float, XAUDIOFRAMESIZE_NATIVE> *>(runtime_state_malloc_verbose(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 21, name, NULL, size));
    assert_tag_debug_untracked_jul_11_2011(23, ring_buffer_raw_data);
    m_current_ring_buffer_index = 0;
    for (long ring_buffer_index = 0; ring_buffer_index < NUMBEROF(m_ring_buffers.m_elements); ring_buffer_index++)
    {
        m_ring_buffers[ring_buffer_index] = make_wrapped_array(ring_buffer_raw_data + ring_buffer_index * ring_count, ring_count);
    }
    reset();
    register_engine_callbacks();
};

long c_xaudio_output_ring_buffer::get_ring_count() const
{
    mangled_ppc("?get_ring_count@c_xaudio_output_ring_buffer@@QBAJXZ");

    return m_ring_count;
};

float const * c_xaudio_output_ring_buffer::get_last_frame_output(long ring_index) const
{
    mangled_ppc("?get_last_frame_output@c_xaudio_output_ring_buffer@@QBAPBMJ@Z");

    return (m_last_frame_ring_buffer && m_last_frame_ring_buffer->valid_index(ring_index)) ? (*m_last_frame_ring_buffer)[ring_index].get_elements() : NULL;
};

void c_xaudio_output_ring_buffer::accumulate_current_frame_output(long ring_index, c_wrapped_array<float const> samples) const
{
    mangled_ppc("?accumulate_current_frame_output@c_xaudio_output_ring_buffer@@QBAXJV?$c_wrapped_array@$$CBM@@@Z");

    if (m_current_frame_ring_buffer && m_current_frame_ring_buffer->valid_index(ring_index))
    {
        assert_tag_debug_untracked_jul_11_2011(57, samples.count()==XAUDIOFRAMESIZE_NATIVE);
        float * output = (*m_current_frame_ring_buffer)[ring_index].get_elements();
        float const * input = samples.begin();
        for (long sample_index = 0; sample_index < XAUDIOFRAMESIZE_NATIVE; sample_index++)
        {
            output[sample_index] += input[sample_index];
        }
    }
};

void c_xaudio_output_ring_buffer::update_on_frame_start()
{
    mangled_ppc("?update_on_frame_start@c_xaudio_output_ring_buffer@@QAAXXZ");

    long next_ring_buffer_index = (m_current_ring_buffer_index + 1) % m_ring_buffers.get_count();
    m_last_frame_ring_buffer = &m_ring_buffers[m_current_ring_buffer_index];
    m_current_frame_ring_buffer = &m_ring_buffers[next_ring_buffer_index];
    memset(m_current_frame_ring_buffer->get_elements(), 0, m_current_frame_ring_buffer->get_total_element_size());
    m_current_ring_buffer_index = next_ring_buffer_index;
};

void c_xaudio_output_ring_buffer::reset()
{
    mangled_ppc("?reset@c_xaudio_output_ring_buffer@@QAAXXZ");

    for (long ring_buffer_index = 0; ring_buffer_index < NUMBEROF(m_ring_buffers.m_elements); ring_buffer_index++)
    {
        memset(m_ring_buffers[ring_buffer_index].get_elements(), 0, m_ring_buffers[ring_buffer_index].get_total_element_size());
    }
};

void c_xaudio_output_ring_buffer::register_engine_callbacks()
{
    mangled_ppc("?register_engine_callbacks@c_xaudio_output_ring_buffer@@QAAXXZ");

    XAudioRegisterEngineCallback(0, xaudio_frame_start_callback, this, &m_frame_start_callback_handle);
};

void c_xaudio_output_ring_buffer::xaudio_frame_start_callback(void * context)
{
    mangled_ppc("?xaudio_frame_start_callback@c_xaudio_output_ring_buffer@@CAXPAX@Z");

    c_xaudio_output_ring_buffer * ring_buffer = static_cast<c_xaudio_output_ring_buffer *>(context);
    ring_buffer->update_on_frame_start();
};
