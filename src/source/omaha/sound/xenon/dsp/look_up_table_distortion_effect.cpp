#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\xenon\\dsp\\look_up_table_distortion_effect.cpp"
/* ---------- headers */

#include "omaha\sound\xenon\dsp\look_up_table_distortion_effect.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\math\real_math.h"

#include <xtl.h>
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static float TWO_PI = 2.0f * k_pi;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_look_up_table_distortion_effect::c_look_up_table_distortion_effect(void *);
// public: c_look_up_table_distortion_effect::~c_look_up_table_distortion_effect(void);
// public: virtual long c_look_up_table_distortion_effect::Process(struct IXAudioFrameBuffer *, struct IXAudioFrameBuffer *);
// public: virtual long c_look_up_table_distortion_effect::GetInfo(struct XAUDIOFXINFO *);
// public: virtual long c_look_up_table_distortion_effect::GetParam(unsigned char, unsigned char, union XAUDIOFXPARAM *);
// public: virtual long c_look_up_table_distortion_effect::SetParam(unsigned char, unsigned char, union XAUDIOFXPARAM const *);
// public: virtual long c_look_up_table_distortion_effect::GetContext(void **);
// public: static long c_look_up_table_distortion_effect::EffectSize(struct XAUDIOFXINIT const *, unsigned long *);
// public: static long c_look_up_table_distortion_effect::CreateInstance(struct XAUDIOFXINIT const *, struct IXAudioBatchAllocator *, struct IXAudioEffect **);
// public: static void * c_look_up_table_distortion_effect::operator new(unsigned int, struct IXAudioBatchAllocator *);
// public: virtual unsigned long c_look_up_table_distortion_effect::AddRef(void);
// public: virtual unsigned long c_look_up_table_distortion_effect::Release(void);
// public: void * c_look_up_table_distortion_effect::`scalar deleting destructor'(unsigned int);
// public: static void c_look_up_table_distortion_effect::operator delete(void *);

c_look_up_table_distortion_effect::c_look_up_table_distortion_effect(void * pContext) :
    m_look_up_table(),
    m_look_up_table_slopes(),
    m_interpolate(false),
    m_context(pContext),
    m_reference_count(0)
{
    mangled_ppc("??0c_look_up_table_distortion_effect@@QAA@PAX@Z");
};

c_look_up_table_distortion_effect::~c_look_up_table_distortion_effect(void)
{
    mangled_ppc("??1c_look_up_table_distortion_effect@@QAA@XZ");
};

// $TODO nonmatching: constant loads of the sign ternary are scheduled after mfcr (target loads -1.0f/1.0f before it)
long c_look_up_table_distortion_effect::Process(IXAudioFrameBuffer * pInputBuffer, IXAudioFrameBuffer * pOutputBuffer)
{
    mangled_ppc("?Process@c_look_up_table_distortion_effect@@UAAJPAUIXAudioFrameBuffer@@0@Z");

    assert_tag_debug_untracked_jul_11_2011(38, pInputBuffer);
    assert_tag_debug_untracked_jul_11_2011(39, !pOutputBuffer);

    long result = S_OK;
    long look_up_table_count = m_look_up_table.count();
    if (look_up_table_count > 0)
    {
        XAUDIOFRAMEBUFDATA frame_buffer_data;
        pInputBuffer->GetProcessingData(&frame_buffer_data);
        assert_tag_debug_untracked_jul_11_2011(49, XAUDIOSAMPLETYPE_NATIVE == frame_buffer_data.Format.SampleType);
        assert_tag_debug_untracked_jul_11_2011(50, frame_buffer_data.Format.ChannelCount==1);

        long sample_count = frame_buffer_data.Format.ChannelCount * XAUDIOFRAMESIZE_NATIVE;
        if (m_interpolate)
        {
            for (long sample_index = 0; sample_index < sample_count; sample_index++)
            {
                float sample = frame_buffer_data.pSampleBuffer[sample_index];
                float sign = sample < 0.0f ? -1.0f : 1.0f;
                float value = sign * sample;
                long table_index = static_cast<long>(value * look_up_table_count);
                frame_buffer_data.pSampleBuffer[sample_index] = sign * (table_index < look_up_table_count ? m_look_up_table[table_index] + (value - m_look_up_table[table_index]) * m_look_up_table_slopes[table_index] : 1.0f);
            }
        }
        else
        {
            for (long sample_index = 0; sample_index < sample_count; sample_index++)
            {
                float sample = frame_buffer_data.pSampleBuffer[sample_index];
                float sign = sample < 0.0f ? -1.0f : 1.0f;
                float value = sign * sample;
                long table_index = static_cast<long>(value * look_up_table_count);
                frame_buffer_data.pSampleBuffer[sample_index] = sign * (table_index < look_up_table_count ? m_look_up_table[table_index] : 1.0f);
            }
        }
    }

    return result;
};

long c_look_up_table_distortion_effect::GetInfo(XAUDIOFXINFO * pInfo)
{
    mangled_ppc("?GetInfo@c_look_up_table_distortion_effect@@UAAJPAUXAUDIOFXINFO@@@Z");

    assert_tag_debug_untracked_jul_11_2011(93, pInfo);

    pInfo->DataFlow = XAUDIOFXDATAFLOW_INPLACE;
    pInfo->TrailFrames = 0;

    return S_OK;
};

long c_look_up_table_distortion_effect::GetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM * pParam)
{
    mangled_ppc("?GetParam@c_look_up_table_distortion_effect@@UAAJEEPATXAUDIOFXPARAM@@@Z");

    assert_tag_debug_untracked_jul_11_2011(106, pParam);

    long result = E_FAIL;

    return result;
};

long c_look_up_table_distortion_effect::SetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM const * pParam)
{
    mangled_ppc("?SetParam@c_look_up_table_distortion_effect@@UAAJEEPBTXAUDIOFXPARAM@@@Z");

    assert_tag_debug_untracked_jul_11_2011(124, pParam);

    long result = E_FAIL;
    if (ParamId == 0 && ParamType == 3)
    {
        XAudioLock(XAUDIOLOCKTYPE_LOCK);

        long look_up_table_count = pParam->Buffer.BufferSize / sizeof(float);
        m_look_up_table.resize(look_up_table_count);
        memcpy(m_look_up_table.get_elements(), pParam->Buffer.pBuffer, pParam->Buffer.BufferSize);
        m_look_up_table_slopes.resize(look_up_table_count);
        for (long index = 0; index < look_up_table_count - 1; index++)
        {
            m_look_up_table_slopes[index] = (m_look_up_table[index + 1] - m_look_up_table[index]) * look_up_table_count;
        }
        m_look_up_table_slopes[look_up_table_count - 1] = (1.0f - m_look_up_table[look_up_table_count - 1]) * look_up_table_count;

        XAudioLock(XAUDIOLOCKTYPE_UNLOCK);
        result = S_OK;
    }
    else if (ParamId == 0 && ParamType == 2)
    {
        XAudioLock(XAUDIOLOCKTYPE_LOCK);
        m_interpolate = pParam->Value != 0;
        XAudioLock(XAUDIOLOCKTYPE_UNLOCK);
        result = S_OK;
    }

    return result;
};

long c_look_up_table_distortion_effect::GetContext(void ** ppvContext)
{
    mangled_ppc("?GetContext@c_look_up_table_distortion_effect@@UAAJPAPAX@Z");

    assert_tag_debug_untracked_jul_11_2011(167, ppvContext);

    *ppvContext = m_context;

    return S_OK;
};

long c_look_up_table_distortion_effect::EffectSize(XAUDIOFXINIT const * pInit, unsigned long * pEffectSize)
{
    mangled_ppc("?EffectSize@c_look_up_table_distortion_effect@@SAJPBUXAUDIOFXINIT@@PAK@Z");

    assert_tag_debug_untracked_jul_11_2011(179, pInit);
    assert_tag_debug_untracked_jul_11_2011(180, pEffectSize);

    *pEffectSize = sizeof(c_look_up_table_distortion_effect);

    return S_OK;
};

long c_look_up_table_distortion_effect::CreateInstance(XAUDIOFXINIT const * pInit, IXAudioBatchAllocator * pAllocator, IXAudioEffect ** ppEffect)
{
    mangled_ppc("?CreateInstance@c_look_up_table_distortion_effect@@SAJPBUXAUDIOFXINIT@@PAUIXAudioBatchAllocator@@PAPAUIXAudioEffect@@@Z");

    *ppEffect = new(pAllocator) c_look_up_table_distortion_effect(pInit->pContext);

    return S_OK;
};

unsigned long c_look_up_table_distortion_effect::AddRef(void)
{
    mangled_ppc("?AddRef@c_look_up_table_distortion_effect@@UAAKXZ");

    long reference_count = m_reference_count + 1;
    m_reference_count = reference_count;

    return reference_count;
};

// $TODO nonmatching: target keeps the decremented count in a compiler temp at 0x58 (after the delete temps)
unsigned long c_look_up_table_distortion_effect::Release(void)
{
    mangled_ppc("?Release@c_look_up_table_distortion_effect@@UAAKXZ");

    long reference_count = m_reference_count - 1;
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
