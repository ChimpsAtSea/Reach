/* ---------- headers */

#include "omaha\sound\sound_remote.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\data_packets.h"
#include "omaha\memory\data_packet_groups.h"
#include "omaha\networking\tools\remote_command.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

enum
{
    k_maximum_encoded_sound_command_length = 1024,
    k_maximum_decoded_sound_command_length = 1024,
    k_remote_sound_command_version = 1,
};

enum
{
    _sound_packet_class_command = 0,

    k_number_of_sound_packet_classes
};

/* ---------- definitions */

/* ---------- prototypes */

static bool process_looping_sound_command(long sound_command, long tag_index, void * command_data);
static bool process_impulse_sound_command(long sound_command, long tag_index, void * command_data);
static long sound_tag_load(unsigned long group_tag, char const * tag_name);

/* ---------- globals */

static data_packet_field start_sound_command_packet_definition_fields[] =
{
    { __pack_long, 1 }, // group_tag
    { __pack_string, 256 }, // tag_name
    { __pack_long, 1 },
    { __pack_end },
};

static data_packet_definition start_sound_command_packet_definition =
{
    "start_sound_command_packet_definition",
    0,
    264,
    k_remote_sound_command_version,
    start_sound_command_packet_definition_fields,
};

static data_packet_field stop_sound_command_packet_definition_fields[] =
{
    { __pack_long, 1 }, // group_tag
    { __pack_string, 256 }, // tag_name
    { __pack_char, 1 },
    { __pack_pad, 3 },
    { __pack_end },
};

static data_packet_definition stop_sound_command_packet_definition =
{
    "stop_sound_command_packet_definition",
    0,
    264,
    k_remote_sound_command_version,
    stop_sound_command_packet_definition_fields,
};

static data_packet_field set_scale_sound_command_packet_definition_fields[] =
{
    { __pack_long, 1 }, // group_tag
    { __pack_string, 256 }, // tag_name
    { __pack_long, 1 },
    { __pack_end },
};

static data_packet_definition set_scale_sound_command_packet_definition =
{
    "set_scale_sound_command_packet_definition",
    0,
    264,
    k_remote_sound_command_version,
    set_scale_sound_command_packet_definition_fields,
};

static data_packet_field set_alternate_sound_command_packet_definition_fields[] =
{
    { __pack_long, 1 }, // group_tag
    { __pack_string, 256 }, // tag_name
    { __pack_char, 1 },
    { __pack_pad, 3 },
    { __pack_end },
};

static data_packet_definition set_alternate_sound_command_packet_definition =
{
    "set_alternate_sound_command_packet_definition",
    0,
    264,
    k_remote_sound_command_version,
    set_alternate_sound_command_packet_definition_fields,
};

static data_packet_group_packet remote_sound_command_packets_group_packets[k_number_of_remote_sound_commands] =
{
    { _sound_packet_class_command, &start_sound_command_packet_definition }, // _sound_command_start_sound
    { _sound_packet_class_command, &stop_sound_command_packet_definition }, // _sound_command_stop_sound
    { _sound_packet_class_command, &set_scale_sound_command_packet_definition }, // _sound_command_set_scale
    { _sound_packet_class_command, &set_alternate_sound_command_packet_definition }, // _sound_command_set_alternate
};

static data_packet_group_definition remote_sound_command_packets_group =
{
    "remote_sound_command_packets_group",
    k_number_of_remote_sound_commands,
    k_number_of_sound_packet_classes,
    k_maximum_decoded_sound_command_length,
    k_maximum_encoded_sound_command_length,
    remote_sound_command_packets_group_packets,
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool process_remote_sound_command(long, void const *, long);
// bool send_remote_sound_command(long, void const *, long);
// void sound_command_update_remote_parameter(long, long, long, long, float, float, float);
// bool process_looping_sound_command(long, long, void *);
// bool process_impulse_sound_command(long, long, void *);
// long sound_tag_load(unsigned long, char const *);

bool process_remote_sound_command(long sound_command, void const * command_data, long command_length)
{
    mangled_ppc("?process_remote_sound_command@@YA_NJPBXJ@Z");

    bool success = false;
    {
        short decoded_length = static_cast<short>(command_length);
        short decoded_command_type;
        unsigned char decoded_command_data[k_maximum_decoded_sound_command_length];
        short decoded_command_version;
        if (data_packet_group_decode_packet(&remote_sound_command_packets_group, decoded_command_data, const_cast<void *>(command_data), &decoded_length, &decoded_command_type, &decoded_command_version, _sound_packet_class_command)
            && decoded_command_version == k_remote_sound_command_version
            && decoded_command_type == sound_command)
        {
            s_sound_command_header const * header = reinterpret_cast<s_sound_command_header const *>(decoded_command_data);
            if (header->group_tag == SOUND_TAG || header->group_tag == SOUND_LOOPING_TAG)
            {
                long tag_index = sound_tag_load(header->group_tag, header->tag_name);
                if (tag_index != NONE)
                {
                    switch (header->group_tag)
                    {
                    case SOUND_TAG:
                        success = process_impulse_sound_command(sound_command, tag_index, decoded_command_data);
                        break;
                    case SOUND_LOOPING_TAG:
                        success = process_looping_sound_command(sound_command, tag_index, decoded_command_data);
                        break;
                    default:
                        event(_event_critical, "vwarn: '%s'", "trying to run a sound command on an invalid tag type");
                        if (assert_is_debugger_present())
                        {
                            __debugbreak();
                        }
                        break;
                    }
                }
                else
                {
                    s_tag_group const * group = tag_group_get(header->group_tag);
                    event_wrapped(_event_warning, "could not load '%s.%s'", tag_name_strip_path(header->tag_name), group ? group->name : "");
                    success = true;
                }
            }
        }

    }

    return success;
};

bool send_remote_sound_command(long sound_command, void const * command_data, long command_length)
{
    mangled_ppc("?send_remote_sound_command@@YA_NJPBXJ@Z");

    bool success = false;
    short encoded_length = static_cast<short>(command_length);
    unsigned char encoded_command_data[k_maximum_encoded_sound_command_length];
    if (data_packet_group_encode_packet(&remote_sound_command_packets_group, const_cast<void *>(command_data), encoded_command_data, &encoded_length, static_cast<short>(sound_command), k_remote_sound_command_version))
    {
        success = remote_sound_command(sound_command, encoded_command_data, encoded_length);
    }

    return success;
};

void sound_command_update_remote_parameter(long tag_index, long parameter0, long parameter1, long parameter2, float value0, float value1, float value2)
{
    mangled_ppc("?sound_command_update_remote_parameter@@YAXJJJJMMM@Z");

    c_static_string<1024> command;
    command.print("sound_set_tag_parameter_unsafe \"%s\" \"%s\" %d %d %d %f %f %f", tag_get_name(tag_index), tag_group_get(tag_get_group_tag(tag_index))->name, parameter0, parameter1, parameter2, value0, value1, value2);
    remote_hs_expression_send(command.get_string());
};

static bool process_looping_sound_command(long sound_command, long tag_index, void * command_data)
{
    mangled_ppc("?process_looping_sound_command@@YA_NJJPAX@Z");

    bool success = true;
    return success;
};

static bool process_impulse_sound_command(long sound_command, long tag_index, void * command_data)
{
    mangled_ppc("?process_impulse_sound_command@@YA_NJJPAX@Z");

    bool success = true;
    return success;
};

static long sound_tag_load(unsigned long group_tag, char const * tag_name)
{
    mangled_ppc("?sound_tag_load@@YAJKPBD@Z");

    return tag_load(group_tag, tag_name, 0x82);
};
