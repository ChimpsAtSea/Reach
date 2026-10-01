#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\data_packet_groups.cpp"
/* ---------- headers */

#include "omaha\memory\data_packet_groups.h"
#include "omaha\memory\byte_swapping.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

struct packet_header
{
    char type; // 0x0
};
static_assert(sizeof(packet_header) == 0x1, "packet_header");

/* ---------- prototypes */

/* ---------- globals */

long const packet_header_bs_codes[] = { _begin_bs_array, 1, _1byte, _end_bs_array };

static char * global_data_packet_groups_error_string;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long const *const const packet_header_bs_codes; // "?packet_header_bs_codes@@3QBJB"

// void data_packet_group_initialize(struct data_packet_group_definition *);
// char * data_packet_groups_get_error(void);
// unsigned char data_packet_group_decode_packet(struct data_packet_group_definition *, void *, void *, short *, short *, short *, short);
// unsigned char data_packet_group_encode_packet(struct data_packet_group_definition *, void *, void *, short *, short, short);
// unsigned char data_packet_group_append_packet_header(struct data_packet_group_definition const *, void *, short *, short);

void data_packet_group_initialize(data_packet_group_definition * group_definition)
{
    mangled_ppc("?data_packet_group_initialize@@YAXPAUdata_packet_group_definition@@@Z");

    for (short packet_type = 0; packet_type < group_definition->packet_type_count; packet_type++)
    {
        data_packet_group_packet * packet = &group_definition->packets[packet_type];
        if (packet->definition != NULL)
        {
            assert_tag_debug_untracked_jul_11_2011(40, packet->packet_class>=0 && packet->packet_class<group_definition->packet_class_count);
            assert_tag_debug_untracked_jul_11_2011(41, packet->definition->size>=0 && packet->definition->size<=group_definition->maximum_decoded_packet_size);
            assert_tag_debug_untracked_jul_11_2011(42, packet->definition->size + sizeof(struct packet_header)<=group_definition->maximum_encoded_packet_size);

            data_packet_verify(packet->definition);
        }
    }
};

char * data_packet_groups_get_error(void)
{
    mangled_ppc("?data_packet_groups_get_error@@YAPADXZ");

    char * result = global_data_packet_groups_error_string;
    global_data_packet_groups_error_string = NULL;

    assert_tag_debug_untracked_jul_11_2011(57, result);

    return result;
};

unsigned char data_packet_group_decode_packet(data_packet_group_definition * group_definition, void * decoded_packet, void * encoded_packet, short * encoded_packet_size, short * packet_type, short * packet_version, short expected_packet_class)
{
    mangled_ppc("?data_packet_group_decode_packet@@YAEPAUdata_packet_group_definition@@PAX1PAF22F@Z");

    char * error_string = NULL;

    assert_tag_debug_untracked_jul_11_2011(73, decoded_packet);
    assert_tag_debug_untracked_jul_11_2011(74, encoded_packet && encoded_packet_size);
    assert_tag_debug_untracked_jul_11_2011(75, packet_type && packet_version);
    assert_tag_debug_untracked_jul_11_2011(77, expected_packet_class>=0 && expected_packet_class<group_definition->packet_class_count);

    if (*encoded_packet_size >= sizeof(packet_header))
    {
        packet_header * header = reinterpret_cast<packet_header *>(static_cast<char *>(encoded_packet) + *encoded_packet_size) - 1;

        if (header->type >= 0 && header->type < group_definition->packet_type_count)
        {
            data_packet_group_packet * packet = &group_definition->packets[header->type];
            if (packet->packet_class == expected_packet_class)
            {
                *encoded_packet_size -= sizeof(packet_header);

                if (packet->definition == NULL || data_packet_decode(packet->definition, encoded_packet, *encoded_packet_size, decoded_packet, packet_version, NULL))
                {
                    *packet_type = header->type;
                }
                else
                {
                    error_string = "got packet which wouldn't decode";
                }
            }
            else
            {
                error_string = "got packet with mismatched class";
            }
        }
        else
        {
            error_string = "got packet with bad type";
        }
    }
    else
    {
        error_string = "got packet with no header";
    }

    global_data_packet_groups_error_string = error_string;

    return error_string == NULL;
};

unsigned char data_packet_group_encode_packet(data_packet_group_definition * group_definition, void * decoded_packet, void * encoded_packet, short * encoded_packet_size, short packet_type, short packet_version)
{
    mangled_ppc("?data_packet_group_encode_packet@@YAEPAUdata_packet_group_definition@@PAX1PAFFF@Z");

    char * error_string = NULL;

    assert_tag_debug_untracked_jul_11_2011(132, group_definition);
    assert_tag_debug_untracked_jul_11_2011(133, packet_type>=0 && packet_type<group_definition->packet_type_count);
    assert_tag_debug_untracked_jul_11_2011(134, encoded_packet && encoded_packet_size);

    data_packet_group_packet * packet = &group_definition->packets[packet_type];

    assert_tag_debug_untracked_jul_11_2011(139, packet->definition);

    if (data_packet_encode(packet->definition, packet_version, decoded_packet, encoded_packet, encoded_packet_size, static_cast<short>(group_definition->maximum_encoded_packet_size)))
    {
        if (data_packet_group_append_packet_header(group_definition, encoded_packet, encoded_packet_size, packet_type))
        {
        }
        else
        {
            error_string = global_data_packet_groups_error_string;
        }
    }
    else
    {
        error_string = "couldn't encode packet";
    }

    global_data_packet_groups_error_string = error_string;

    return error_string == NULL;
};

unsigned char data_packet_group_append_packet_header(data_packet_group_definition const * group_definition, void * encoded_packet, short * encoded_packet_size, short packet_type)
{
    mangled_ppc("?data_packet_group_append_packet_header@@YAEPBUdata_packet_group_definition@@PAXPAFF@Z");

    packet_header * header = reinterpret_cast<packet_header *>(static_cast<char *>(encoded_packet) + *encoded_packet_size);
    char * error_string = NULL;

    assert_tag_debug_untracked_jul_11_2011(172, group_definition->maximum_encoded_packet_size>=0);
    assert_tag_debug_untracked_jul_11_2011(173, encoded_packet && encoded_packet_size);
    assert_tag_debug_untracked_jul_11_2011(174, *encoded_packet_size>=0);
    assert_tag_debug_untracked_jul_11_2011(175, packet_type>=0 && packet_type<group_definition->packet_type_count);

    if (*encoded_packet_size + sizeof(packet_header) < group_definition->maximum_encoded_packet_size)
    {
        header->type = static_cast<char>(packet_type);
        *encoded_packet_size += sizeof(packet_header);
    }
    else
    {
        error_string = "couldn't append header to encoded packet";
    }

    global_data_packet_groups_error_string = error_string;

    return error_string == NULL;
};

