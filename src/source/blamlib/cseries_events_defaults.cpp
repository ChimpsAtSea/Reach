/* ---------- headers */

#include "blamlib\cseries_events_defaults.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\networking\network_time.h"
#include "omaha\networking\session\network_session.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static e_event_level const k_shaders_datamine_level = _event_warning;

s_event_category_default_configuration const k_event_category_default_configurations[] =
{
    {
        "lifecycle:",
        k_event_level_none,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "crash:",
        _event_message,
        { 1.0f, 0.1f, 0.1f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "animation:",
        k_event_level_none,
        { 1.0f, 1.0f, 0.0f },
        k_event_level_none,
        "animation_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "ai:",
        k_event_level_none,
        { 1.0f, 0.63f, 0.48f },
        k_event_level_none,
        "ai_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "shaders:",
        k_event_level_none,
        { 0.0f, 0.0f, 1.0f },
        k_event_level_none,
        "shaders_debug.txt",
        NULL,
        int_max(_event_critical, k_shaders_datamine_level)
    },
    {
        "render:",
        k_event_level_none,
        { 0.0f, 0.0f, 1.0f },
        k_event_level_none,
        "shaders_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "geometry:",
        k_event_level_none,
        { 0.0f, 0.0f, 0.8f },
        k_event_level_none,
        "geometry_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "environment:",
        k_event_level_none,
        { 0.0f, 0.0f, 0.6f },
        k_event_level_none,
        "environment_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "objects:",
        k_event_level_none,
        { 0.4f, 0.1f, 0.4f },
        k_event_level_none,
        "objects_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "networking:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        "networking_debug.txt",
        build_networking_buffer_for_log,
        _event_message
    },
    {
        "xoverlapped:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "networking:leaderboards:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        "leaderboard_debug.txt",
        NULL,
        _event_message
    },
    {
        "networking:stream_manager:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        "stream_manager_debug.txt",
        NULL,
        _event_message
    },
    {
        "networking:spawning:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        build_networking_buffer_for_log,
        k_event_level_none
    },
    {
        "networking:camera:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        build_networking_buffer_for_log,
        k_event_level_none
    },
    {
        "networking:bandwidth:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        "bandwidth_debug.txt",
        NULL,
        _event_message
    },
    {
        "datamine:",
        _event_warning,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        build_networking_buffer_for_log,
        _event_message
    },
    {
        "switching:",
        _event_warning,
        { 1.0f, 0.7f, 0.4f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "tags:",
        _event_error,
        { 1.0f, 0.0f, 1.0f },
        _event_warning,
        "tag_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "ui:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        k_event_level_none,
        "ui_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "ui:window_manager:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "ui:memory_peak:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "ui:alert:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "ui:dialog:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "ui:custom_bitmaps:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "ui:profile:campaign:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "campaign:",
        k_event_level_none,
        { 1.0f, 0.5f, 0.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
    {
        "sound:",
        k_event_level_none,
        { 0.7f, 0.7f, 0.7f },
        _event_warning,
        "sound_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "multiplayer:",
        k_event_level_none,
        { 0.8f, 0.1f, 0.6f },
        k_event_level_none,
        "multiplayer_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "effects:",
        _event_warning,
        { 0.0f, 0.0f, 0.8f },
        k_event_level_none,
        "effects_debug.txt",
        NULL,
        _event_error
    },
    {
        "animation_audio_content:",
        k_event_level_none,
        { 0.7f, 0.7f, 0.5f },
        k_event_level_none,
        "animation_audio_content_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "environment_materials:",
        k_event_level_none,
        { 0.0f, 0.0f, 0.6f },
        k_event_level_none,
        "environment_materials_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "object_materials:",
        k_event_level_none,
        { 0.4f, 0.1f, 0.4f },
        k_event_level_none,
        "object_materials_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "design:",
        k_event_level_none,
        { 1.0f, 0.63f, 0.48f },
        k_event_level_none,
        "design_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "localization:",
        k_event_level_none,
        { 0.0f, 0.0f, 0.0f },
        k_event_level_none,
        "localization_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "hs:",
        _event_warning,
        { 0.5f, 0.8f, 0.3f },
        _event_message,
        "hs_log.txt",
        NULL,
        k_event_level_none
    },
    {
        "tags:xsync:",
        k_event_level_none,
        { 1.0f, 1.0f, 0.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "tags:cache_builder:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "system:",
        _event_warning,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "system_log.txt",
        NULL,
        k_event_level_none
    },
    {
        "memory:",
        _event_warning,
        { 1.0f, 1.0f, 1.0f },
        k_event_level_none,
        "system_log.txt",
        NULL,
        _event_warning
    },
    {
        "cache:",
        k_event_level_none,
        { 1.0f, 0.4f, 0.7f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "debugger:",
        k_event_level_none,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "player_rewards:",
        _event_error,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "player_rewards_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "player_rewards:incident:",
        _event_error,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "incident_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "lightmapper:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "tool:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "inspection:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "cheats:",
        _event_warning,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "automation:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        k_event_level_none,
        NULL,
        NULL,
        k_event_level_none
    },
    {
        "challenges:",
        _event_error,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "challenges_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "content:",
        _event_error,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        _event_warning
    },
    {
        "game:grief:",
        _event_error,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "griefing_debug.txt",
        NULL,
        k_event_level_none
    },
    {
        "render:command_buffer:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "command_buffer_debug.txt",
        NULL,
        _event_message
    },
    {
        "animation:import:frame_event:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "frame_event_debug.txt",
        NULL,
        _event_message
    },
    {
        "render:shield_instrumentation:",
        _event_message,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        "render_shield_debug.txt",
        NULL,
        _event_message
    },
    {
        "log_and_datamine:",
        _event_critical,
        { 1.0f, 1.0f, 1.0f },
        _event_message,
        NULL,
        NULL,
        _event_message
    },
};
long const k_event_category_default_configuration_count = NUMBEROF(k_event_category_default_configurations);

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_string<2048>::k_index_not_found; // "?k_index_not_found@?$s_static_string@$0IAA@@@2JB"
// public: static long const s_static_string<2048>::k_element_count; // "?k_element_count@?$s_static_string@$0IAA@@@2JB"
// public: static long const s_static_array<enum e_event_log_index, 5>::k_element_count; // "?k_element_count@?$s_static_array@W4e_event_log_index@@$04@@2JB"
// public: static long const s_static_array<class c_event_listener *, 8>::k_element_count; // "?k_element_count@?$s_static_array@PAVc_event_listener@@$07@@2JB"
// private: static long const c_event_manager::k_maximum_event_category_count; // "?k_maximum_event_category_count@c_event_manager@@0JB"
// private: static long const c_event_manager::k_maximum_spamming_event_count; // "?k_maximum_spamming_event_count@c_event_manager@@0JB"
// public: static long const s_static_array<struct s_spamming_event, 64>::k_element_count; // "?k_element_count@?$s_static_array@Us_spamming_event@@$0EA@@@2JB"
// long const k_event_category_default_configuration_count; // "?k_event_category_default_configuration_count@@3JB"
// struct s_event_category_default_configuration const *const const k_event_category_default_configurations; // "?k_event_category_default_configurations@@3QBUs_event_category_default_configuration@@B"

// void build_networking_buffer_for_log(char *, long);
// enum e_event_level int_max<enum e_event_level>(enum e_event_level const &, enum e_event_level const &);

void build_networking_buffer_for_log(char * buffer, long buffer_size)
{
    mangled_ppc("?build_networking_buffer_for_log@@YAXPADJ@Z");

    csnzprintf(buffer, buffer_size, "networking info");
    for (long session_index = 0; session_index < k_network_maximum_sessions; session_index++)
    {
        unsigned long session_timestamp = 0;
        char session_timestamp_string[256];
        s_transport_secure_identifier session_id;
        if (network_session_time_get_id_and_time(session_index, &session_id, &session_timestamp))
        {
            long session_msec = session_timestamp;
            long session_sec = session_msec / 1000;
            long session_min = session_sec / 60;
            long session_hour = session_min / 60;
            session_msec %= 1000;
            session_sec %= 60;
            session_min %= 60;
            csnzprintf(session_timestamp_string, NUMBEROF(session_timestamp_string), "%02d:%02d:%02d.%03d%s", session_hour, session_min, session_sec, session_msec, session_index == k_network_maximum_sessions - 1 ? "" : " ");
        }
        else
        {
            csnzprintf(session_timestamp_string, NUMBEROF(session_timestamp_string), "            %s", session_index == k_network_maximum_sessions - 1 ? "" : " ");
        }
        csstrnzcat(buffer, session_timestamp_string, buffer_size);
    }
};


