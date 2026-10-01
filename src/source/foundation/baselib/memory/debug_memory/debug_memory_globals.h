#ifndef __DEBUG_MEMORY_GLOBALS_H__
#define __DEBUG_MEMORY_GLOBALS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\hash_table.h"

/* ---------- constants */

enum e_debug_memory_flags
{
    _debug_memory_exclude_from_minidump_bit = 0,
    _debug_memory_free_implicitly_on_exit_bit,
    _debug_memory_pretrack_nonheap_bit,

    k_debug_memory_flags_count
};

unsigned int const k_maximum_pointer_size = 0x30000000;
long const k_maximum_alignment_bits = 20;

unsigned long const k_pointer_header_signature = '--->';
unsigned long const k_pointer_header_signature_disposed = '<BAD';
unsigned long const k_pointer_trailer_signature = '<---';

/* ---------- definitions */

typedef unsigned long debug_memory_checksum_function(void const * data, unsigned int size);
typedef unsigned short debug_memory_random_function(void);

struct s_header_tracking_info
{
    char const * file;
    long line;
    char const * type;
    char const * subtype;
    char const * name;
};

struct s_pointer_header
{
    unsigned long signature;
    long identifier;
    s_pointer_header * next;
    s_pointer_header * previous;
    unsigned int size;
    long offset;
    unsigned int total_free_at_allocation;
    s_header_tracking_info * tracking;
    void const * nonheap_resource;
    long freed_externally_on_exit : 1;
    long exclude_from_minidump : 1;
    long alignment_bits : 6;
    long actual_size_offset : 24;
    long type_identifier;
    unsigned long checksum;
};
static_assert(sizeof(s_pointer_header) == 0x30, "s_pointer_header");

struct s_pointer_trailer
{
    unsigned long signature;
};
static_assert(sizeof(s_pointer_trailer) == 0x4, "s_pointer_trailer");

struct s_debug_memory_information
{
    unsigned int current_heap_size; // 0x0
    unsigned int current_nonheap_size; // 0x4
    unsigned int largest_heap_size; // 0x8
    unsigned int largest_nonheap_size; // 0xC
    unsigned int pretracked_nonheap_size; // 0x10
};
static_assert(sizeof(s_debug_memory_information) == 0x14, "s_debug_memory_information");

/* ---------- prototypes */

void debug_memory_manager_initialize(debug_memory_checksum_function * const checksum_function, debug_memory_random_function * const local_random_function);
void debug_memory_begin_exit(void);
bool thread_can_use_debug_memory(void);
void debug_memory_free_emergency_reserve(void);
void check_debug_memory_manager(char const * file, long line);
void check_header(s_pointer_header const * header, char const * file, long line);
void check_pointer(void const * pointer, char const * file, long line);
void check_nonheap_resource(s_pointer_header const * header, char const * file, long line);
void build_header_and_trailer(void * user_pointer, unsigned int size, long alignment_bits, long offset, e_debug_memory_flags flags, char const * file, long line, long type_identifier, unsigned int actual_size, char const * type, char const * subtype, char const * name, void const * nonheap_resource, bool freed_externally_on_exit);
void dequeue_header(s_pointer_header * header, char const * file, long line);
s_pointer_header * query_nonheap_header(void const * nonheap_resource);
void force_release_header(s_pointer_header * header, char const * file, long line);
void track_heap_allocation_size(unsigned int old_size, unsigned int new_size);
void track_nonheap_allocation_size(unsigned int old_size, unsigned int new_size);
void pretrack_nonheap_allocation_size(unsigned int old_size, unsigned int new_size);
char const * make_constant_string(char const * string);
char const * strip_source_directory(char const * file);
void debug_verify_memory(char const * file, long line);
void debug_memory_get_memory_information(s_debug_memory_information * out_information);
s_pointer_header const * get_heap_queue(void);
s_pointer_header const * get_free_queue(void);
char const * safe_printable_string(char const * string);
bool query_possible_header(s_pointer_header const * header);
void debug_checkpoint_memory(char const * name, char const * file, long line);
void debug_notify_out_of_memory(char const * file, long line);

/* ---------- globals */

extern char const * const k_source_directory_string;
extern c_hash_table<s_pointer_header *, void> g_nonheap_hash_table;

/* ---------- public code */

inline void * get_user_pointer_from_header(s_pointer_header * header)
{
    mangled_ppc("?get_user_pointer_from_header@@YAPAXPAUs_pointer_header@@@Z");

    return header + 1;
};

inline void const * get_user_pointer_from_header_const(s_pointer_header const * header)
{
    mangled_ppc("?get_user_pointer_from_header_const@@YAPBXPBUs_pointer_header@@@Z");

    return get_user_pointer_from_header(const_cast<s_pointer_header *>(header));
};

inline s_pointer_header * get_header_from_user_pointer(void * pointer)
{
    mangled_ppc("?get_header_from_user_pointer@@YAPAUs_pointer_header@@PAX@Z");

    return static_cast<s_pointer_header *>(pointer) - 1;
};

inline s_pointer_header const * get_header_from_user_pointer_const(void const * pointer)
{
    mangled_ppc("?get_header_from_user_pointer_const@@YAPBUs_pointer_header@@PBX@Z");

    return get_header_from_user_pointer(const_cast<void *>(pointer));
};

inline s_pointer_trailer * get_trailer_from_header(s_pointer_header * header)
{
    mangled_ppc("?get_trailer_from_header@@YAPAUs_pointer_trailer@@PAUs_pointer_header@@@Z");

    return static_cast<s_pointer_trailer *>(offset_pointer(get_user_pointer_from_header(header), header->nonheap_resource ? 0 : header->size));
};

inline s_pointer_trailer const * get_trailer_from_header_const(s_pointer_header const * header)
{
    mangled_ppc("?get_trailer_from_header_const@@YAPBUs_pointer_trailer@@PBUs_pointer_header@@@Z");

    return get_trailer_from_header(const_cast<s_pointer_header *>(header));
};

inline void * get_base_pointer_from_header(s_pointer_header * header)
{
    mangled_ppc("?get_base_pointer_from_header@@YAPAXPAUs_pointer_header@@@Z");

    return offset_pointer(header, -header->offset);
};

inline unsigned int header_get_actual_size(s_pointer_header const * header)
{
    mangled_ppc("?header_get_actual_size@@YAIPBUs_pointer_header@@@Z");

    assert_decomp(header, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib/memory/debug_memory/debug_memory_globals.h", 176);

    return header->size + header->actual_size_offset;
};

inline void const * get_base_pointer_from_header_const(s_pointer_header const * header)
{
    mangled_ppc("?get_base_pointer_from_header_const@@YAPBXPBUs_pointer_header@@@Z");

    return offset_pointer(header, -header->offset);
};

#endif // __DEBUG_MEMORY_GLOBALS_H__

