#pragma once
#ifndef __SOUND_XAUDIO_XENON_PACKET_CONTROLLER_DEFAULT_H__
#define __SOUND_XAUDIO_XENON_PACKET_CONTROLLER_DEFAULT_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_platform_source_datum;
class c_sound_cache_debugger;
struct s_platform_source_packet;

class c_platform_source_packet_controller
{
public:
    static void set_owner(c_platform_source_datum const * owner);
    static void notify_first_packet(c_platform_source_datum const * owner);
    static void debug_hardware_references(c_platform_source_datum * owner, c_sound_cache_debugger * debugger);
    static bool acquire_packet(c_platform_source_datum * owner, s_platform_source_packet * out_packet);
    static void success_packet(c_platform_source_datum * owner, s_platform_source_packet const * packet);
    static void failed_packet(c_platform_source_datum * owner, s_platform_source_packet const * packet);
    static void finished_packet(c_platform_source_datum * owner, void * packet_context, unsigned long packet_status);
    static void flush(void);
    static bool more_sound_data_available(c_platform_source_datum const * owner, bool unknown);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_XAUDIO_XENON_PACKET_CONTROLLER_DEFAULT_H__

