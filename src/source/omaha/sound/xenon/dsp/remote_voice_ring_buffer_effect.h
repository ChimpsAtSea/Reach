#pragma once
#ifndef __REMOTE_VOICE_RING_BUFFER_EFFECT_H__
#define __REMOTE_VOICE_RING_BUFFER_EFFECT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "xdk\xaudiod\xaudio.h"

/* ---------- constants */

enum e_remote_voice_ring_buffer_mode
{
    _remote_voice_ring_buffer_mode_mixbin = 0,
    _remote_voice_ring_buffer_mode_output,

    k_remote_voice_ring_buffer_mode_count
};

/* ---------- definitions */

class c_xaudio_output_ring_buffer;

class c_remote_voice_ring_buffer_effect :
    public IXAudioEffect
{
public:
    c_remote_voice_ring_buffer_effect(e_remote_voice_ring_buffer_mode mode, void * pContext);

    virtual unsigned long AddRef(void);
    virtual unsigned long Release(void);
    virtual long GetInfo(XAUDIOFXINFO * pInfo);
    virtual long GetParam(XAUDIOFXPARAMID nParamId, XAUDIOFXPARAMTYPE nParamType, XAUDIOFXPARAM * pParam);
    virtual long SetParam(XAUDIOFXPARAMID nParamId, XAUDIOFXPARAMTYPE nParamType, XAUDIOFXPARAM const * pParam);
    virtual long GetContext(void ** ppvContext);
    virtual long Process(IXAudioFrameBuffer * pInputBuffer, IXAudioFrameBuffer * pOutputBuffer);
    virtual long Initialize(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator);

    static long xaudio_fx_query_size(XAUDIOFXINIT const * pInit, unsigned long * pEffectSize);
    static long xaudio_fx_create_mixbin_effect(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect);
    static long xaudio_fx_create_output_effect(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect);

    static void * operator new(unsigned int size, IXAudioBatchAllocator * pAllocator)
    {
        mangled_ppc("??2c_remote_voice_ring_buffer_effect@@SAPAXIPAUIXAudioBatchAllocator@@@Z");

        return pAllocator->Alloc(size);
    }

    static void operator delete(void * pointer)
    {
        mangled_ppc("??3c_remote_voice_ring_buffer_effect@@SAXPAX@Z");
    }

private:
    void * m_context; // 0x4
    unsigned long m_reference_count; // 0x8
    long m_ring_index; // 0xC
    c_xaudio_output_ring_buffer * m_ring_buffer; // 0x10
    e_remote_voice_ring_buffer_mode m_mode; // 0x14
};
static_assert(sizeof(c_remote_voice_ring_buffer_effect) == 0x18, "c_remote_voice_ring_buffer_effect");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __REMOTE_VOICE_RING_BUFFER_EFFECT_H__

