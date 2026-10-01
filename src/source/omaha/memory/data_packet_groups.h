#pragma once
#ifndef __DATA_PACKET_GROUPS_H__
#define __DATA_PACKET_GROUPS_H__

/* ---------- headers */

#include "omaha\memory\data_packets.h"

/* ---------- constants */

/* ---------- definitions */

struct data_packet_group_packet
{
    short packet_class; // 0x0
    data_packet_definition * definition; // 0x4
};
static_assert(sizeof(data_packet_group_packet) == 0x8, "data_packet_group_packet");

struct data_packet_group_definition
{
    char const * name; // 0x0
    short packet_type_count; // 0x4
    short packet_class_count; // 0x6
    long maximum_decoded_packet_size; // 0x8
    long maximum_encoded_packet_size; // 0xC
    data_packet_group_packet * packets; // 0x10
};
static_assert(sizeof(data_packet_group_definition) == 0x14, "data_packet_group_definition");

/* ---------- prototypes */

void data_packet_group_initialize(data_packet_group_definition * group_definition);
char * data_packet_groups_get_error(void);
unsigned char data_packet_group_decode_packet(data_packet_group_definition * group_definition, void * decoded_packet, void * encoded_packet, short * encoded_packet_size, short * packet_type, short * packet_version, short expected_packet_class);
unsigned char data_packet_group_encode_packet(data_packet_group_definition * group_definition, void * decoded_packet, void * encoded_packet, short * encoded_packet_size, short packet_type, short packet_version);
unsigned char data_packet_group_append_packet_header(data_packet_group_definition const * group_definition, void * encoded_packet, short * encoded_packet_size, short packet_type);

/* ---------- globals */

/* ---------- public code */

#endif // __DATA_PACKET_GROUPS_H__

