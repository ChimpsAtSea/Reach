#pragma once
#ifndef __SOUND_XAUDIO_XENON_SOURCE_H__
#define __SOUND_XAUDIO_XENON_SOURCE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_sound_permutation_chunk;

// $TODO layout only partially known (from c_platform_source_packet_controller::acquire_packet); size unverified
struct s_platform_source_packet
{
    long type; // 0x0 (1 = xma2)
    void * buffer; // 0x4
    unsigned long buffer_size; // 0x8
    union
    {
        struct
        {
            unsigned long Flags; // 0xC
            unsigned long unknown10; // 0x10
            unsigned long unknown14; // 0x14
            unsigned long PlayBegin; // 0x18
            unsigned long PlayLength; // 0x1C
            void * pContext; // 0x20
        } source_buffer;

        struct
        {
            unsigned long Flags; // 0xC
            unsigned long unknown10[18]; // 0x10
            void * pContext; // 0x58
        } pcm_source_buffer;
    };
};

// $TODO layout only partially known (from the packet controller); size unverified
class c_platform_source_datum
{
public:
    void dequeue_sound(s_sound_permutation_chunk * permutation);

    // bitfields are allocated from the most significant bit on this compiler
    short m_state : 4; // 0x0 bits 15-12
    unsigned short m_sound_channel_count : 3; // 0x0 bits 11-9
    short m_queued_sound_count : 3; // 0x0 bits 8-6
    short m_playing_sound_count : 3; // 0x0 bits 5-3
    short m_unknown0 : 3; // 0x0 bits 2-0 $TODO
    unsigned short m_flags; // 0x2 $TODO c_flags_no_init<e_platform_source_xenon_bit, unsigned short, 11>
    s_sound_permutation_chunk * m_sound_queue[2]; // 0x4
    unsigned long m_unknownC; // 0xC $TODO
    unsigned long m_unknown10; // 0x10 $TODO
    long m_initial_sample_offset; // 0x14
    unsigned long m_actual_sample_offset; // 0x18
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_SOURCE_H__

