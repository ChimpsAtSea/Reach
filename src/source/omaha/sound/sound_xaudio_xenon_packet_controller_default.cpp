#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_xaudio_xenon_packet_controller_default.cpp"
/* ---------- headers */

#include "omaha\sound\sound_xaudio_xenon_packet_controller_default.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cache\xbox_sound_cache.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_xaudio_xenon_source.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "core\corelib\cseries\cseries_events.h"
#include "omaha\cseries\cseries.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\sound\sound_xaudio_xenon.h"
#include <xtl.h>

/* ---------- constants */

unsigned long const XAUDIOPACKETSTATUS_XMA_BUFFER_ERROR = 0x80040001;
unsigned long const XAUDIOPACKETSTATUS_XMA_PARSER_ERROR = 0x80040002;
unsigned long const XAUDIOPACKETSTATUS_XMA_DECODER_HANG = 0x80040003;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static void c_platform_source_packet_controller::set_owner(class c_platform_source_datum const *);
// public: static void c_platform_source_packet_controller::notify_first_packet(class c_platform_source_datum const *);
// public: static void c_platform_source_packet_controller::debug_hardware_references(class c_platform_source_datum *, class c_sound_cache_debugger *);
// public: static bool c_platform_source_packet_controller::acquire_packet(class c_platform_source_datum *, struct s_platform_source_packet *);
// public: static void c_platform_source_packet_controller::success_packet(class c_platform_source_datum *, struct s_platform_source_packet const *);
// public: static void c_platform_source_packet_controller::failed_packet(class c_platform_source_datum *, struct s_platform_source_packet const *);
// public: static void c_platform_source_packet_controller::finished_packet(class c_platform_source_datum *, void *, unsigned long);
// public: static void c_platform_source_packet_controller::flush(void);
// public: static bool c_platform_source_packet_controller::more_sound_data_available(class c_platform_source_datum const *, bool);

void c_platform_source_packet_controller::set_owner(c_platform_source_datum const * owner)
{
    mangled_ppc("?set_owner@c_platform_source_packet_controller@@SAXPBVc_platform_source_datum@@@Z");

    assert_tag_debug_untracked_jul_11_2011(25, owner);
};

void c_platform_source_packet_controller::notify_first_packet(c_platform_source_datum const * owner)
{
    mangled_ppc("?notify_first_packet@c_platform_source_packet_controller@@SAXPBVc_platform_source_datum@@@Z");

    assert_tag_debug_untracked_jul_11_2011(32, owner);
};

void c_platform_source_packet_controller::debug_hardware_references(c_platform_source_datum * owner, c_sound_cache_debugger * debugger)
{
    mangled_ppc("?debug_hardware_references@c_platform_source_packet_controller@@SAXPAVc_platform_source_datum@@PAVc_sound_cache_debugger@@@Z");

    assert_tag_debug_untracked_jul_11_2011(40, owner);
    assert_tag_debug_untracked_jul_11_2011(41, debugger);

    for (long queue_index = 0; queue_index < owner->m_queued_sound_count; queue_index++)
    {
        if (queue_index < owner->m_playing_sound_count)
        {
            assert_tag_debug_untracked_jul_11_2011(47, VALID_INDEX(queue_index, NUMBEROF(owner->m_sound_queue)));
            debugger->lock_sound(owner->m_sound_queue[queue_index]);
        }
    }
};

bool c_platform_source_packet_controller::acquire_packet(c_platform_source_datum * owner, s_platform_source_packet * out_packet)
{
    mangled_ppc("?acquire_packet@c_platform_source_packet_controllerSA_NPAVc_platform_source_datumPAUs_platform_source_packet@Z");

    assert_tag_debug_untracked_jul_11_2011(59, owner);
    assert_tag_debug_untracked_jul_11_2011(60, out_packet);

    long queue_index = owner->m_playing_sound_count;
    s_sound_permutation_chunk * permutation = owner->m_sound_queue[queue_index];
    assert_tag_debug_untracked_jul_11_2011(64, sound_cache_sound_loaded(permutation));

    unsigned long hardware_size;
    void * hardware_buffer = sound_cache_sound_hardware_lock(permutation, &hardware_size);
    void * packet_completion_event = sound_xaudio_xenon_allocate_packet_completion_event(permutation);
    if (sound_cache_sound_uses_xma2(permutation))
    {
        s_xma2_packet_info packet_info;
        s_xma2_packet_info full_packet_info;
        sound_cache_sound_get_xma2_info(permutation, &packet_info);
        sound_cache_sound_get_full_xma2_info(permutation, &full_packet_info);

        out_packet->type = 1;
        out_packet->buffer = hardware_buffer;
        out_packet->source_buffer.pContext = packet_completion_event;
        out_packet->buffer_size = hardware_size;
        out_packet->source_buffer.Flags = 0;

        unsigned long aligned_sample_offset = align_down(MIN(MAX(owner->m_initial_sample_offset, 0), full_packet_info.block_sample_end - full_packet_info.block_sample_start - 128), 7);
        if (owner->m_initial_sample_offset != 0)
        {
            owner->m_actual_sample_offset = aligned_sample_offset;
        }
        out_packet->source_buffer.PlayBegin = packet_info.block_sample_start + aligned_sample_offset;
        out_packet->source_buffer.PlayLength = packet_info.block_sample_end;
        assert_tag_debug_untracked_jul_11_2011(95, out_packet->source_buffer.PlayBegin + 128 <= full_packet_info.block_sample_end);

        event_wrapped(_event_status, "sound:xaudio:xma2:packet_info: source[%p]: %s[%d], (%d, %d)",
            owner,
            sound_permutation_chunk_get_debug_name(permutation),
            sound_permutation_chunk_get_debug_index(permutation),
            packet_info.block_sample_start,
            packet_info.block_sample_end);
    }
    else
    {
        out_packet->type = 0;
        out_packet->buffer = hardware_buffer;
        out_packet->pcm_source_buffer.pContext = packet_completion_event;
        out_packet->buffer_size = hardware_size;
        out_packet->pcm_source_buffer.Flags = 0;
    }

    return true;
};

void c_platform_source_packet_controller::success_packet(c_platform_source_datum * owner, s_platform_source_packet const * packet)
{
    mangled_ppc("?success_packet@c_platform_source_packet_controller@@SAXPAVc_platform_source_datum@@PBUs_platform_source_packet@@@Z");

    assert_tag_debug_untracked_jul_11_2011(125, owner);
    assert_tag_debug_untracked_jul_11_2011(126, packet);

    owner->m_playing_sound_count++;
};

void c_platform_source_packet_controller::failed_packet(c_platform_source_datum * owner, s_platform_source_packet const * packet)
{
    mangled_ppc("?failed_packet@c_platform_source_packet_controller@@SAXPAVc_platform_source_datum@@PBUs_platform_source_packet@@@Z");

    assert_tag_debug_untracked_jul_11_2011(137, owner);
    assert_tag_debug_untracked_jul_11_2011(138, packet);

    long queue_index = owner->m_playing_sound_count;
    assert_tag_debug_untracked_jul_11_2011(141, VALID_INDEX(queue_index, NUMBEROF(owner->m_sound_queue)));
    s_sound_permutation_chunk * permutation = owner->m_sound_queue[queue_index];
    sound_cache_sound_hardware_unlock(permutation);
};

void c_platform_source_packet_controller::finished_packet(c_platform_source_datum * owner, void * packet_context, unsigned long packet_status)
{
    mangled_ppc("?finished_packet@c_platform_source_packet_controller@@SAXPAVc_platform_source_datum@@PAXK@Z");

    assert_tag_debug_untracked_jul_11_2011(152, owner);
    assert_tag_debug_untracked_jul_11_2011(153, packet_context);

    s_sound_permutation_chunk * permutation = static_cast<s_sound_permutation_chunk *>(packet_context);
    if (FAILED(packet_status) && packet_status != E_ABORT)
    {
        c_static_string<256> error_string;
        switch (packet_status)
        {
        case XAUDIOPACKETSTATUS_XMA_DECODER_HANG:
        {
            c_static_string<256> status_string("XAUDIOPACKETSTATUS_XMA_DECODER_HANG");
            error_string = status_string;
            break;
        }
        case XAUDIOPACKETSTATUS_XMA_PARSER_ERROR:
        {
            c_static_string<256> status_string("XAUDIOPACKETSTATUS_XMA_PARSER_ERROR");
            error_string = status_string;
            break;
        }
        case XAUDIOPACKETSTATUS_XMA_BUFFER_ERROR:
        {
            c_static_string<256> status_string("XAUDIOPACKETSTATUS_XMA_BUFFER_ERROR");
            error_string = status_string;
            break;
        }
        default:
            error_string.print("UNKNOWN: 0x%08x", packet_status);
            break;
        }
        sound_cache_sound_spit_out_error(permutation, error_string);
    }

    owner->dequeue_sound(permutation);
    sound_cache_sound_hardware_unlock(permutation);
};

void c_platform_source_packet_controller::flush(void)
{
    mangled_ppc("?flush@c_platform_source_packet_controller@@SAXXZ");
};

bool c_platform_source_packet_controller::more_sound_data_available(c_platform_source_datum const * owner, bool unknown)
{
    mangled_ppc("?more_sound_data_available@c_platform_source_packet_controller@@SA_NPBVc_platform_source_datum@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(204, owner->m_playing_sound_count<=owner->m_queued_sound_count);

    return owner->m_queued_sound_count > owner->m_playing_sound_count;
};

