#pragma once
#ifndef __XAUDIO_H__
#define __XAUDIO_H__

/* ---------- headers */

// XAudio (v1) public API types. The XDK 9328 install used by this project does not ship xaudio.h,
// so the pieces the engine needs are declared here (names follow the XAudio 1 SDK / target symbols).

/* ---------- constants */

#ifndef SUCCEEDED
#define SUCCEEDED(hr) (static_cast<long>(hr) >= 0)
#endif

/* ---------- definitions */

typedef unsigned char XAUDIOCHANNEL;
typedef float XAUDIOVOLUME;
typedef unsigned char XAUDIOVOICEINDEX;
typedef unsigned char XAUDIOFXINDEX;
typedef unsigned char XAUDIOFXPARAMID;
typedef unsigned char XAUDIOFXID;
typedef unsigned char XAUDIOSAMPLETYPE;
typedef unsigned long XAUDIOSAMPLERATE;

struct XAUDIOCHANNELVOLUMEENTRY;
struct XAUDIOVOICEOUTPUTVOLUME;
union XAUDIOFXPARAM;

struct IXAudioVoice
{
    unsigned long Release(void);
    long SetEffectParam(XAUDIOFXINDEX EffectIndex, XAUDIOFXPARAMID ParamId, unsigned char ParamType, XAUDIOFXPARAM const * pParam);
    inline long SetVoiceOutputVolume(XAUDIOVOICEOUTPUTVOLUME const * pVolume);
};

struct IXAudioSubmixVoice :
    public IXAudioVoice
{
};

struct XAUDIOCHANNELMAPENTRY
{
    XAUDIOCHANNEL InputChannel; // 0x0
    XAUDIOCHANNEL OutputChannel; // 0x1
    XAUDIOVOLUME Volume; // 0x4
};

struct XAUDIOCHANNELMAP
{
    XAUDIOCHANNEL EntryCount; // 0x0
    XAUDIOCHANNELMAPENTRY * paEntries; // 0x4
};

struct XAUDIOVOICEOUTPUTENTRY
{
    IXAudioVoice * pDestVoice; // 0x0
    XAUDIOCHANNELMAP * pChannelMap; // 0x4
};

struct XAUDIOVOICEOUTPUT
{
    XAUDIOVOICEINDEX OutputCount; // 0x0
    XAUDIOVOICEOUTPUTENTRY * paOutputs; // 0x4
};

struct XAUDIOCHANNELVOLUMEENTRY
{
    XAUDIOCHANNEL EntryIndex; // 0x0
    XAUDIOVOLUME Volume; // 0x4
};

struct XAUDIOCHANNELVOLUME
{
    XAUDIOCHANNEL EntryCount; // 0x0
    XAUDIOCHANNELVOLUMEENTRY * paEntries; // 0x4
};

struct XAUDIOVOICEOUTPUTVOLUMEENTRY
{
    XAUDIOVOICEINDEX OutputVoiceIndex; // 0x0
    XAUDIOCHANNELVOLUME * pVolume; // 0x4
};

struct XAUDIOVOICEOUTPUTVOLUME
{
    XAUDIOVOICEINDEX EntryCount; // 0x0
    XAUDIOVOICEOUTPUTVOLUMEENTRY * paEntries; // 0x4
};

struct XAUDIOFXINIT
{
    XAUDIOFXID FxId; // 0x0
    void * pContext; // 0x4
};

struct XAUDIOVOICEFXCHAIN
{
    XAUDIOFXINDEX EffectCount; // 0x0
    XAUDIOFXINIT const ** papEffects; // 0x4
};

// layout from c_xenon_audio_reverb_manager::initialize (size 0x1C); field names are best guesses
struct XAUDIOSUBMIXVOICEINIT
{
    XAUDIOSAMPLETYPE SampleType; // 0x0
    XAUDIOCHANNEL ChannelCount; // 0x1
    XAUDIOSAMPLERATE SampleRate; // 0x4
    XAUDIOVOICEINDEX MaxOutputVoiceCount; // 0x8
    XAUDIOCHANNEL MaxChannelMapEntryCount; // 0x9
    unsigned char SubmixStage; // 0xA
    XAUDIOVOICEFXCHAIN const * pEffectChain; // 0xC
    XAUDIOVOICEOUTPUT const * pVoiceOutput; // 0x10
    unsigned char unknown14[0x8]; // 0x14
};

struct XAUDIOFXPARAM_BUFFER
{
    void * pBuffer; // 0x0
    unsigned long BufferSize; // 0x4
};

// the first member is a float: `XAUDIOFXPARAM x = { 0.0f };` (remote_voice_ring_buffer_effect GetParam) loads a float constant
union XAUDIOFXPARAM
{
    float FloatValue;
    unsigned long Value;
    XAUDIOFXPARAM_BUFFER Buffer;
};

// I3DL2 reverb parameters (XAUDIOFXID reverb effect buffer parameter, size 0x30)
struct XAUDIOREVERBI3DL2SETTINGS
{
    long lRoom; // 0x0
    long lRoomHF; // 0x4
    float flRoomRolloffFactor; // 0x8
    float flDecayTime; // 0xC
    float flDecayHFRatio; // 0x10
    long lReflections; // 0x14
    float flReflectionsDelay; // 0x18
    long lReverb; // 0x1C
    float flReverbDelay; // 0x20
    float flDiffusion; // 0x24
    float flDensity; // 0x28
    float flHFReference; // 0x2C
};

extern "C" long XAudioCreateSubmixVoice(XAUDIOSUBMIXVOICEINIT const * pInit, IXAudioSubmixVoice ** ppVoice);
extern "C" long XAudioVoice_SetVoiceOutputVolume(IXAudioVoice * pVoice, XAUDIOVOICEOUTPUTVOLUME const * pVolume);

inline long IXAudioVoice::SetVoiceOutputVolume(XAUDIOVOICEOUTPUTVOLUME const * pVolume)
{
    mangled_ppc("?SetVoiceOutputVolume@IXAudioVoice@@QAAJPBUXAUDIOVOICEOUTPUTVOLUME@@@Z");

    return XAudioVoice_SetVoiceOutputVolume(this, pVolume);
}

// XAudio effect interfaces (used by the custom dsp effects in omaha\sound\xenon\dsp)

#define XAUDIOSAMPLETYPE_NATIVE 0
#define XAUDIOFRAMESIZE_NATIVE 256

// XAudioLock arguments (values from the target, names are best guesses)
#define XAUDIOLOCKTYPE_LOCK 0x00010001
#define XAUDIOLOCKTYPE_UNLOCK 0x00010003

// XAUDIOFXINFO::DataFlow value used by in-place effects (value from the target, name is a best guess)
#define XAUDIOFXDATAFLOW_INPLACE 1
// XAUDIOFXINFO::DataFlow value used by the remote voice mixbin effect (value from the target, name is a best guess)
#define XAUDIOFXDATAFLOW_SINK 2

// XAUDIOFXPARAMTYPE values (FLAG name from a target assert string; value from the target)
#define XAUDIOFXPARAMTYPE_FLAG 2

typedef float XAUDIOSAMPLE;
typedef unsigned char XAUDIOFXPARAMTYPE;
typedef unsigned char XAUDIOFXDATAFLOW;

struct XAUDIOFRAMEBUFFORMAT
{
    XAUDIOSAMPLETYPE SampleType; // 0x0
    XAUDIOCHANNEL ChannelCount; // 0x1
    XAUDIOSAMPLERATE SampleRate; // 0x4
};

struct XAUDIOFRAMEBUFDATA
{
    XAUDIOFRAMEBUFFORMAT Format; // 0x0
    XAUDIOSAMPLE * pSampleBuffer; // 0x8
};

struct XAUDIOFXINFO
{
    XAUDIOFXDATAFLOW DataFlow; // 0x0
    unsigned short TrailFrames; // 0x2
};

struct IXAudioFrameBuffer
{
    inline long GetProcessingData(XAUDIOFRAMEBUFDATA * pData);
};

// vtable order from ??_7CBatchAllocator@XAUDIO@@6BIXAudioBatchAllocator@@@
struct IXAudioBatchAllocator
{
    virtual unsigned long AddRef(void) = 0;
    virtual unsigned long Release(void) = 0;
    virtual void GrowHeap(unsigned long Size) = 0;
    virtual long CreateHeap(unsigned long Size) = 0;
    virtual unsigned long GetFreeHeapSize(void) = 0;
    virtual void * Alloc(unsigned long Size) = 0;
};

// vtable order from ??_7c_look_up_table_distortion_effect@@6B@
struct IXAudioEffect
{
    virtual unsigned long AddRef(void) = 0;
    virtual unsigned long Release(void) = 0;
    virtual long GetInfo(XAUDIOFXINFO * pInfo) = 0;
    virtual long GetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM * pParam) = 0;
    virtual long SetParam(XAUDIOFXPARAMID ParamId, XAUDIOFXPARAMTYPE ParamType, XAUDIOFXPARAM const * pParam) = 0;
    virtual long GetContext(void ** ppvContext) = 0;
    virtual long Process(IXAudioFrameBuffer * pInputBuffer, IXAudioFrameBuffer * pOutputBuffer) = 0;
};

extern "C" void XAudioLock(unsigned long LockType);
extern "C" long XAudioFrameBuffer_GetProcessingData(IXAudioFrameBuffer * pFrameBuffer, XAUDIOFRAMEBUFDATA * pData);

inline long IXAudioFrameBuffer::GetProcessingData(XAUDIOFRAMEBUFDATA * pData)
{
    mangled_ppc("?GetProcessingData@IXAudioFrameBuffer@@QAAJPAUXAUDIOFRAMEBUFDATA@@@Z");

    return XAudioFrameBuffer_GetProcessingData(this, pData);
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __XAUDIO_H__
