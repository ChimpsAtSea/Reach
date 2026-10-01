#pragma once
#ifndef __XAUDIO_OUTPUT_RING_BUFFER_H__
#define __XAUDIO_OUTPUT_RING_BUFFER_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\memory\wrapped_arrays.h"

/* ---------- constants */

#ifndef XAUDIOFRAMESIZE_NATIVE
#define XAUDIOFRAMESIZE_NATIVE 256
#endif

/* ---------- definitions */

// XAudio (xaudiod:api.obj) engine callback registration
typedef void * XAUDIOENGINECALLBACKHANDLE;
typedef void (*LPFNXAUDIOENGINECALLBACK)(void * context);

extern "C" long XAudioRegisterEngineCallback(long type, LPFNXAUDIOENGINECALLBACK callback, void * context, XAUDIOENGINECALLBACKHANDLE * handle);

class c_xaudio_output_ring_buffer
{
public:
    void initialize(char const * name, long ring_count);
    long get_ring_count() const;
    float const * get_last_frame_output(long ring_index) const;
    void accumulate_current_frame_output(long ring_index, c_wrapped_array<float const> samples) const;
    void update_on_frame_start();
    void reset();
    void register_engine_callbacks();

private:
    static void xaudio_frame_start_callback(void * context);

    s_static_array<c_wrapped_array<s_static_array<float, XAUDIOFRAMESIZE_NATIVE> >, 2> m_ring_buffers; // 0x0
    long m_ring_count; // 0x10
    long m_current_ring_buffer_index; // 0x14
    c_wrapped_array<s_static_array<float, XAUDIOFRAMESIZE_NATIVE> > const * m_last_frame_ring_buffer; // 0x18
    c_wrapped_array<s_static_array<float, XAUDIOFRAMESIZE_NATIVE> > * m_current_frame_ring_buffer; // 0x1C
    XAUDIOENGINECALLBACKHANDLE m_frame_start_callback_handle; // 0x20
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __XAUDIO_OUTPUT_RING_BUFFER_H__

