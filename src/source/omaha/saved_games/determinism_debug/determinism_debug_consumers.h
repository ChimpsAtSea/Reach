#ifndef __DETERMINISM_DEBUG_CONSUMERS_H__
#define __DETERMINISM_DEBUG_CONSUMERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

struct s_game_state_consumer_iterator
{
    unsigned char data[128]; // 0x0
};
static_assert(sizeof(s_game_state_consumer_iterator) == 0x80, "s_game_state_consumer_iterator");

// vtable order verified: get_deterministic_item_data is slot 6 (0x18)
class c_game_state_consumer_interface
{
public:
    virtual void iterate_begin(s_game_state_consumer_iterator * iterator, void const * game_state_allocation_base) = 0;
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator) = 0;
    virtual long get_item_index(s_game_state_consumer_iterator const * iterator) = 0;
    virtual long get_item_size(s_game_state_consumer_iterator const * iterator) = 0;
    virtual void describe_item(s_game_state_consumer_iterator const * iterator, c_static_string<128> * description_out) = 0;
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address) = 0;
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out) = 0;
    virtual bool compare_deterministic_item_data(long item_1_index, long item_1_size, void const * item_1_data, long item_2_index, long item_2_size, void const * item_2_data) = 0;
};
static_assert(sizeof(c_game_state_consumer_interface) == 0x4, "c_game_state_consumer_interface");

// $TODO member bodies not reversed yet (f i, owned by determinism_debug_consumers.obj)
template<typename t_datum>
class c_game_state_consumer_datum_array :
    public c_game_state_consumer_interface
{
public:
    virtual void iterate_begin(s_game_state_consumer_iterator * iterator, void const * game_state_allocation_base);
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator);
    virtual bool iterate_next_in_range(s_game_state_consumer_iterator * iterator, long minimum_index, long count);
    virtual long get_item_index(s_game_state_consumer_iterator const * iterator);
    virtual long get_item_size(s_game_state_consumer_iterator const * iterator);
    virtual void describe_item(s_game_state_consumer_iterator const * iterator, c_static_string<128> * description_out);
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address);
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out);
    virtual bool compare_deterministic_item_data(long item_1_index, long item_1_size, void const * item_1_data, long item_2_index, long item_2_size, void const * item_2_data);
};

// $TODO member bodies not reversed yet (f i, owned by determinism_debug_consumers.obj)
template<typename t_datum, long k_count>
class c_game_state_consumer_generic :
    public c_game_state_consumer_interface
{
public:
    virtual void iterate_begin(s_game_state_consumer_iterator * iterator, void const * game_state_allocation_base);
    virtual bool iterate_next(s_game_state_consumer_iterator * iterator);
    virtual long get_item_index(s_game_state_consumer_iterator const * iterator);
    virtual long get_item_size(s_game_state_consumer_iterator const * iterator);
    virtual void describe_item(s_game_state_consumer_iterator const * iterator, c_static_string<128> * description_out);
    virtual unsigned long get_deterministic_item_checksum(unsigned long crc, long index, void const * game_state_base_address);
    virtual void get_deterministic_item_data(long index, void const * game_state_base_address, void * data_out, long max_size, long * size_out);
    virtual bool compare_deterministic_item_data(long item_1_index, long item_1_size, void const * item_1_data, long item_2_index, long item_2_size, void const * item_2_data);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __DETERMINISM_DEBUG_CONSUMERS_H__

