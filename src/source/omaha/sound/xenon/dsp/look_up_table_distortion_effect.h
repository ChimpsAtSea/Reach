#pragma once
#ifndef __LOOK_UP_TABLE_DISTORTION_EFFECT_H__
#define __LOOK_UP_TABLE_DISTORTION_EFFECT_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "xdk\xaudiod\xaudio.h"

/* ---------- constants */

/* ---------- definitions */

class c_look_up_table_distortion_effect :
    public IXAudioEffect
{
public:
    c_look_up_table_distortion_effect(void * pContext);
    ~c_look_up_table_distortion_effect(void);

    virtual unsigned long AddRef(void);
    virtual unsigned long Release(void);
    virtual long GetInfo(XAUDIOFXINFO * pInfo);
    virtual long GetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM * pParam);
    virtual long SetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM const * pParam);
    virtual long GetContext(void ** ppvContext);
    virtual long Process(IXAudioFrameBuffer * pInputBuffer, IXAudioFrameBuffer * pOutputBuffer);

    static long EffectSize(XAUDIOFXINIT const * pInit, unsigned long * pEffectSize);
    static long CreateInstance(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect);

    static void * operator new(unsigned int size, IXAudioBatchAllocator * pAllocator)
    {
        mangled_ppc("??2c_look_up_table_distortion_effect@@SAPAXIPAUIXAudioBatchAllocator@@@Z");

        return pAllocator->Alloc(size);
    }

    static void operator delete(void * pointer)
    {
        mangled_ppc("??3c_look_up_table_distortion_effect@@SAXPAX@Z");
    }

private:
    c_static_stack<float, 256> m_look_up_table; // 0x4
    c_static_stack<float, 256> m_look_up_table_slopes; // 0x408
    bool m_interpolate; // 0x80C
    void * m_context; // 0x810
    long m_reference_count; // 0x814
};
static_assert(sizeof(c_look_up_table_distortion_effect) == 0x818, "c_look_up_table_distortion_effect");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __LOOK_UP_TABLE_DISTORTION_EFFECT_H__

