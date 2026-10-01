#ifndef __CHUNK_PERSIST_STREAM_HELPERS_H__
#define __CHUNK_PERSIST_STREAM_HELPERS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\persist.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\toolbox\chunk_persist_streams.h"

/* ---------- constants */

enum e_chunk_archive_action
{
    _chunk_archive_action_load = 0,
    _chunk_archive_action_save,

    k_number_of_chunk_archive_actions
};

/* ---------- definitions */

class type_info;
class c_persist_archiver_visitor;

// layout from ??$?0X@c_typed_pointer_holder@@QAA@PAX@Z (pointer, then RTTI type descriptor)
class c_typed_pointer_holder
{
public:
    // $TODO inline ("f i"), body not yet recovered
    template<typename t_type>
    c_typed_pointer_holder(t_type * pointer);

private:
    void * m_pointer; // 0x0
    type_info const * m_type; // 0x4
};
static_assert(sizeof(c_typed_pointer_holder) == 0x8, "c_typed_pointer_holder");

// vtable order from ??_7c_persist_archiver@@6B@ (0x82147414)
class c_persist_archiver
{
public:
    virtual bool persist(c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const = 0;
    virtual bool restore(s_persist_chunk_header const * chunk_header, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const = 0;
    virtual bool visit(c_typed_pointer_holder & pointer_holder) const;
    virtual bool traverse(c_persist_archiver_visitor * visitor) const;
    virtual char const * get_description(void) const = 0;
    virtual unsigned long get_chunk_tag(void) const = 0;
    virtual long get_chunk_version(void) const = 0;
    virtual bool can_handle_chunk(unsigned long chunk_tag, long chunk_version) const = 0;
};
static_assert(sizeof(c_persist_archiver) == 0x4, "c_persist_archiver");

// $TODO layout unverified beyond size (0x40 byte archiver storage at 0x4, see ??$make@...s_persist_archiver_holder)
struct s_persist_archiver_holder
{
    s_persist_archiver_holder(void);
    s_persist_archiver_holder(s_persist_archiver_holder const & other);

    // $TODO inline ("f i"), body not yet recovered
    template<typename t_archiver>
    static s_persist_archiver_holder make(t_archiver archiver);

    c_persist_archiver const * archiver; // 0x0
    unsigned char archiver_storage[0x40]; // 0x4
};
static_assert(sizeof(s_persist_archiver_holder) == 0x44, "s_persist_archiver_holder");

// vtable order from ??_7c_chunk_with_sections_archiver@@6B@ (0x821473F4); member names unverified
class c_chunk_with_sections_archiver :
    public c_persist_archiver
{
public:
    c_chunk_with_sections_archiver(char const * description, unsigned long chunk_tag, long chunk_version, c_wrapped_array<s_persist_archiver_holder> sections);

    virtual bool persist(c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const;
    virtual bool restore(s_persist_chunk_header const * chunk_header, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const;
    virtual bool traverse(c_persist_archiver_visitor * visitor) const;
    virtual char const * get_description(void) const;
    virtual unsigned long get_chunk_tag(void) const;
    virtual long get_chunk_version(void) const;
    virtual bool can_handle_chunk(unsigned long chunk_tag, long chunk_version) const;

private:
    char const * m_description; // 0x4
    unsigned long m_chunk_tag; // 0x8
    long m_chunk_version; // 0xC
    c_wrapped_array<s_persist_archiver_holder> m_sections; // 0x10
};
static_assert(sizeof(c_chunk_with_sections_archiver) == 0x18, "c_chunk_with_sections_archiver");

// vtable ??_7c_raw_buffer_chunk_section_archiver@@6B@ (0x822E62E8) is owned by tag_resource_cache_datum_persist.obj; member names unverified
class c_raw_buffer_chunk_section_archiver :
    public c_persist_archiver
{
public:
    c_raw_buffer_chunk_section_archiver(char const * description, unsigned long chunk_tag, long chunk_version, c_basic_buffer<void> buffer);

    virtual bool persist(c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const;
    virtual bool restore(s_persist_chunk_header const * chunk_header, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream) const;
    virtual char const * get_description(void) const;
    virtual unsigned long get_chunk_tag(void) const;
    virtual long get_chunk_version(void) const;
    virtual bool can_handle_chunk(unsigned long chunk_tag, long chunk_version) const;

private:
    char const * m_description; // 0x4
    unsigned long m_chunk_tag; // 0x8
    long m_chunk_version; // 0xC
    c_basic_buffer<void> m_buffer; // 0x10
};
static_assert(sizeof(c_raw_buffer_chunk_section_archiver) == 0x18, "c_raw_buffer_chunk_section_archiver");

/* ---------- prototypes */

extern bool persist_chunk_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_chunk_writer * chunk_writer);
extern bool persist_chunk_with_archiver_explicit(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream);
extern bool restore_chunk_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_chunk_iterator * chunk_iterator);
extern bool restore_chunk_with_archiver_explicit(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, s_persist_chunk_header const * chunk_header, c_persist_stream * persist_stream);
extern bool save_or_restore_with_archiver(c_persist_archiver const * archiver, c_typed_pointer_holder & pointer_holder, c_persist_stream * persist_stream, e_chunk_archive_action action);
extern c_raw_buffer_chunk_section_archiver make_raw_buffer_archiver(char const * description, unsigned long chunk_tag, long chunk_version, c_basic_buffer<void> buffer); // $TODO inline ("f i"), owned by tag_resource_cache_datum_persist.obj

// ??$make_raw_section_archiver@Us_tag_persistent_identifier@@@@YA?AVc_raw_buffer_chunk_section_archiver@@PBDKJPAUs_tag_persistent_identifier@@@Z
template<typename t_type>
c_raw_buffer_chunk_section_archiver make_raw_section_archiver(char const * description, unsigned long chunk_tag, long chunk_version, t_type * section)
{
    return c_raw_buffer_chunk_section_archiver(description, chunk_tag, chunk_version, c_basic_buffer<void>(section, sizeof(t_type)));
};

/* ---------- globals */

/* ---------- public code */

#endif // __CHUNK_PERSIST_STREAM_HELPERS_H__

