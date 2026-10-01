#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\xenon\\dsp\\remote_voice_ring_buffer_effect.cpp"
/* ---------- headers */

#include "omaha\sound\xenon\dsp\remote_voice_ring_buffer_effect.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\sound\xenon\dsp\xaudio_output_ring_buffer.h"

#include <xtl.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static float TWO_PI = 2.0f * k_pi;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_remote_voice_ring_buffer_effect::c_remote_voice_ring_buffer_effect(enum e_remote_voice_ring_buffer_mode, void *);
// public: virtual long c_remote_voice_ring_buffer_effect::Initialize(struct XAUDIOFXINIT const *, struct IXAudioBatchAllocator *);
// public: virtual long c_remote_voice_ring_buffer_effect::Process(struct IXAudioFrameBuffer *, struct IXAudioFrameBuffer *);
// public: virtual long c_remote_voice_ring_buffer_effect::GetInfo(struct XAUDIOFXINFO *);
// public: virtual long c_remote_voice_ring_buffer_effect::GetParam(unsigned char, unsigned char, union XAUDIOFXPARAM *);
// public: virtual long c_remote_voice_ring_buffer_effect::SetParam(unsigned char, unsigned char, union XAUDIOFXPARAM const *);
// public: virtual long c_remote_voice_ring_buffer_effect::GetContext(void **);
// public: static long c_remote_voice_ring_buffer_effect::xaudio_fx_query_size(struct XAUDIOFXINIT const *, unsigned long *);
// public: static long c_remote_voice_ring_buffer_effect::xaudio_fx_create_mixbin_effect(struct XAUDIOFXINIT const *, struct IXAudioBatchAllocator *, struct IXAudioEffect **);
// public: static void * c_remote_voice_ring_buffer_effect::operator new(unsigned int, struct IXAudioBatchAllocator *);
// public: static long c_remote_voice_ring_buffer_effect::xaudio_fx_create_output_effect(struct XAUDIOFXINIT const *, struct IXAudioBatchAllocator *, struct IXAudioEffect **);
// public: virtual unsigned long c_remote_voice_ring_buffer_effect::AddRef(void);
// public: virtual unsigned long c_remote_voice_ring_buffer_effect::Release(void);
// public: static void c_remote_voice_ring_buffer_effect::operator delete(void *);

c_remote_voice_ring_buffer_effect::c_remote_voice_ring_buffer_effect(e_remote_voice_ring_buffer_mode mode, void * pContext)
{
    mangled_ppc("??0c_remote_voice_ring_buffer_effect@@QAA@W4e_remote_voice_ring_buffer_mode@@PAX@Z");

    m_mode = mode;
    m_context = pContext;
    m_reference_count = 1;
    m_ring_buffer = static_cast<c_xaudio_output_ring_buffer *>(pContext);
    m_ring_index = NONE;
};

long c_remote_voice_ring_buffer_effect::Initialize(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator)
{
    mangled_ppc("?Initialize@c_remote_voice_ring_buffer_effect@@UAAJPBUXAUDIOFXINIT@@PAUIXAudioBatchAllocator@@@Z");

    long result = S_OK;

    return result;
};

long c_remote_voice_ring_buffer_effect::Process(IXAudioFrameBuffer * pInputBuffer, IXAudioFrameBuffer * pOutputBuffer)
{
    mangled_ppc("?Process@c_remote_voice_ring_buffer_effect@@UAAJPAUIXAudioFrameBuffer@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(60, pInputBuffer);

    XAUDIOFRAMEBUFDATA FrameBufferData;
    unsigned short frame_sample_count = XAUDIOFRAMESIZE_NATIVE;
    long result = S_OK;
    pInputBuffer->GetProcessingData(&FrameBufferData);
    assert_tag_debug_untracked_jul_11_2011(67, XAUDIOSAMPLETYPE_NATIVE == FrameBufferData.Format.SampleType);

    XAudioLock(XAUDIOLOCKTYPE_LOCK);
    long ring_buffer_index = m_ring_index;
    XAudioLock(XAUDIOLOCKTYPE_UNLOCK);

    if (m_ring_buffer && ring_buffer_index != NONE)
    {
        if (m_mode == _remote_voice_ring_buffer_mode_mixbin)
        {
            assert_tag_debug_untracked_jul_11_2011(78, !pOutputBuffer);
            assert_tag_debug_untracked_jul_11_2011(79, FrameBufferData.Format.ChannelCount==1);

            m_ring_buffer->accumulate_current_frame_output(ring_buffer_index, make_wrapped_array(FrameBufferData.pSampleBuffer, frame_sample_count));
        }
        else if (m_mode == _remote_voice_ring_buffer_mode_output)
        {
            assert_tag_debug_untracked_jul_11_2011(86, FrameBufferData.Format.ChannelCount==1);

            float const * last_frame_output = m_ring_buffer->get_last_frame_output(ring_buffer_index);
            if (last_frame_output)
            {
                c_wrapped_array<float> samples(FrameBufferData.pSampleBuffer, frame_sample_count);
                for (long sample_index = 0; sample_index < frame_sample_count; sample_index++)
                {
                    samples[sample_index] += last_frame_output[sample_index];
                }
            }
        }
    }

    return result;
};

long c_remote_voice_ring_buffer_effect::GetInfo(XAUDIOFXINFO * pInfo)
{
    mangled_ppc("?GetInfo@c_remote_voice_ring_buffer_effect@@UAAJPAUXAUDIOFXINFO@@@Z");

    assert_tag_debug_untracked_jul_11_2011(113, pInfo);

    pInfo->DataFlow = m_mode == _remote_voice_ring_buffer_mode_mixbin ? XAUDIOFXDATAFLOW_SINK : (m_mode == _remote_voice_ring_buffer_mode_output ? XAUDIOFXDATAFLOW_INPLACE : XAUDIOFXDATAFLOW_SINK);
    pInfo->TrailFrames = 0;

    return S_OK;
};

long c_remote_voice_ring_buffer_effect::GetParam(XAUDIOFXPARAMID nParamId, XAUDIOFXPARAMTYPE nParamType, XAUDIOFXPARAM * pParam)
{
    mangled_ppc("?GetParam@c_remote_voice_ring_buffer_effect@@UAAJEEPATXAUDIOFXPARAM@@@Z");

    assert_tag_debug_untracked_jul_11_2011(126, pParam);

    XAUDIOFXPARAM param = { 0.0f };
    long result = S_OK;

    XAudioLock(XAUDIOLOCKTYPE_LOCK);
    switch (nParamId)
    {
    default:
        result = E_FAIL;
        break;
    }
    *pParam = param;
    XAudioLock(XAUDIOLOCKTYPE_UNLOCK);

    return result;
};

long c_remote_voice_ring_buffer_effect::SetParam(XAUDIOFXPARAMID nParamId, XAUDIOFXPARAMTYPE nParamType, XAUDIOFXPARAM const * pParam)
{
    mangled_ppc("?SetParam@c_remote_voice_ring_buffer_effect@@UAAJEEPBTXAUDIOFXPARAM@@@Z");

    long result = S_OK;
    assert_tag_debug_untracked_jul_11_2011(153, pParam);

    switch (nParamId)
    {
    case 0:
        assert_tag_debug_untracked_jul_11_2011(157, nParamType==XAUDIOFXPARAMTYPE_FLAG);
        break;
    }

    XAudioLock(XAUDIOLOCKTYPE_LOCK);
    switch (nParamId)
    {
    case 0:
        m_ring_index = pParam->Value;
        break;
    default:
        result = E_FAIL;
        break;
    }
    XAudioLock(XAUDIOLOCKTYPE_UNLOCK);

    return result;
};

long c_remote_voice_ring_buffer_effect::GetContext(void ** ppvContext)
{
    mangled_ppc("?GetContext@c_remote_voice_ring_buffer_effect@@UAAJPAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(186, ppvContext);

    *ppvContext = m_context;

    return S_OK;
};

long c_remote_voice_ring_buffer_effect::xaudio_fx_query_size(XAUDIOFXINIT const * pInit, unsigned long * pEffectSize)
{
    mangled_ppc("?xaudio_fx_query_size@c_remote_voice_ring_buffer_effect@@SAJPBUXAUDIOFXINIT@@PAK@Z");

    assert_tag_debug_untracked_jul_11_2011(200, pInit);
    assert_tag_debug_untracked_jul_11_2011(201, pEffectSize);

    *pEffectSize = sizeof(c_remote_voice_ring_buffer_effect);

    return S_OK;
};

long c_remote_voice_ring_buffer_effect::xaudio_fx_create_mixbin_effect(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect)
{
    mangled_ppc("?xaudio_fx_create_mixbin_effect@c_remote_voice_ring_buffer_effect@@SAJPBUXAUDIOFXINIT@@PAUIXAudioBatchAllocator@@PAPAUIXAudioEffect@@@Z");

    assert_tag_debug_untracked_jul_11_2011(217, pInit);
    assert_tag_debug_untracked_jul_11_2011(218, ppEffect);
    assert_tag_debug_untracked_jul_11_2011(219, pAllocator);

    long result = S_OK;
    c_remote_voice_ring_buffer_effect * remote_voice_ring_buffer_effect = NULL;
    remote_voice_ring_buffer_effect = new(pAllocator) c_remote_voice_ring_buffer_effect(_remote_voice_ring_buffer_mode_mixbin, pInit->pContext);
    remote_voice_ring_buffer_effect->Initialize(pInit, pAllocator);
    *ppEffect = remote_voice_ring_buffer_effect;

    return result;
};

long c_remote_voice_ring_buffer_effect::xaudio_fx_create_output_effect(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect)
{
    mangled_ppc("?xaudio_fx_create_output_effect@c_remote_voice_ring_buffer_effect@@SAJPBUXAUDIOFXINIT@@PAUIXAudioBatchAllocator@@PAPAUIXAudioEffect@@@Z");

    assert_tag_debug_untracked_jul_11_2011(237, pInit);
    assert_tag_debug_untracked_jul_11_2011(238, ppEffect);
    assert_tag_debug_untracked_jul_11_2011(239, pAllocator);

    long result = S_OK;
    c_remote_voice_ring_buffer_effect * remote_voice_ring_buffer_effect = NULL;
    remote_voice_ring_buffer_effect = new(pAllocator) c_remote_voice_ring_buffer_effect(_remote_voice_ring_buffer_mode_output, pInit->pContext);
    remote_voice_ring_buffer_effect->Initialize(pInit, pAllocator);
    *ppEffect = remote_voice_ring_buffer_effect;

    return result;
};

unsigned long c_remote_voice_ring_buffer_effect::AddRef(void)
{
    mangled_ppc("?AddRef@c_remote_voice_ring_buffer_effect@@UAAKXZ");

    unsigned long reference_count = m_reference_count + 1;
    m_reference_count = reference_count;

    return reference_count;
};

// $TODO nonmatching (stack slots of reference_count and the delete temporary are swapped)
unsigned long c_remote_voice_ring_buffer_effect::Release(void)
{
    mangled_ppc("?Release@c_remote_voice_ring_buffer_effect@@UAAKXZ");

    unsigned long reference_count = m_reference_count - 1;
    m_reference_count = reference_count;
    if (reference_count == 0)
    {
        delete this;
        return 0;
    }
    else
    {
        return m_reference_count;
    }
};
