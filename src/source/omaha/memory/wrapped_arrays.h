#ifndef __WRAPPED_ARRAYS_H__
#define __WRAPPED_ARRAYS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\tag_files\tag_groups.h"

#include <new>
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

template<typename t_type>
class c_basic_buffer
{
public:
    // ??$?0X@?$c_basic_buffer@$$CBX@@QAA@ABV?$c_basic_buffer@X@@@Z
    template<typename t_other>
    c_basic_buffer(c_basic_buffer<t_other> const & rhs)
    {
        m_buffer_start = rhs.begin();
        m_size = rhs.size();
    };

    // ??0?$c_basic_buffer@X@@QAA@PAXK@Z
    c_basic_buffer(t_type * start, unsigned long size) :
        m_buffer_start(start),
        m_size(size)
    {
    };

    // ??0?$c_basic_buffer@X@@QAA@PAX0@Z
    c_basic_buffer(t_type * start, t_type * end)
    {
        m_buffer_start = start;
        m_size = pointer_distance32(start, end);
        assert_decomp(start<=end, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 588);
    };

    // ??0?$c_basic_buffer@X@@QAA@XZ
    c_basic_buffer() :
        m_buffer_start(0),
        m_size(0)
    {
    };

    // ?begin@?$c_basic_buffer@X@@QBAPAXXZ
    t_type * begin() const
    {
        return m_buffer_start;
    };

    // ?end@?$c_basic_buffer@X@@QBAPAXXZ
    t_type * end() const
    {
        return offset_pointer(m_buffer_start, m_size);
    };

    // ?empty@?$c_basic_buffer@X@@QBA_NXZ
    bool empty() const
    {
        return m_size == 0;
    };

    // ?size@?$c_basic_buffer@X@@QBAKXZ
    unsigned long size() const
    {
        return m_size;
    };

    // ?advance_start@?$c_basic_buffer@X@@QAAXK@Z
    void advance_start(unsigned long offset)
    {
        assert_decomp(offset<=m_size, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 671);
        m_buffer_start = offset_pointer(m_buffer_start, offset);
        m_size -= offset;
    };

    // ?clear@?$c_basic_buffer@X@@QAAXXZ
    void clear()
    {
        m_buffer_start = NULL;
        m_size = 0;
    };

    // ?set_buffer@?$c_basic_buffer@X@@QAAXPAXK@Z
    void set_buffer(t_type * start, unsigned long size)
    {
        assert_decomp(start || size==0, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 610);
        m_buffer_start = start;
        m_size = size;
    };

    // ?get_range@?$c_basic_buffer@X@@QAAPAXKK@Z (body not reversed yet)
    t_type * get_range(unsigned long offset, unsigned long size);

    // verified for s_platform_sound_playback_definition (platform_sound_effect_definitions.obj)
    template<typename T>
    T * get_as_type_from_offset(unsigned long offset)
    {
        return static_cast<T *>(get_range(offset, sizeof(T)));
    };

    // verified for s_platform_sound_playback_definition (platform_sound_effect_definitions.obj)
    template<typename T>
    T * get_as_type()
    {
        assert_decomp(size()==sizeof(T), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 749);
        return get_as_type_from_offset<T>(0);
    };

    class c_basic_buffer_checked_caster
    {
    public:
        // verified for s_platform_sound_playback_definition (platform_sound_effect_definitions.obj)
        template<typename T>
        operator T *()
        {
            return m_buffer->get_as_type<T>();
        };

    private:
        c_basic_buffer * m_buffer; // 0x0
    };

    // ?checked_cast@?$c_basic_buffer@X@@QAA?AVc_basic_buffer_checked_caster@1@XZ (body not reversed yet)
    c_basic_buffer_checked_caster checked_cast();

private:
    t_type * m_buffer_start; // 0x0
    unsigned long m_size; // 0x4
};
static_assert(sizeof(c_basic_buffer<void>) == 0x8, "c_basic_buffer<void>");

typedef c_basic_buffer<void const> c_const_buffer;

template<typename t_array>
class c_recursive_template_pattern
{
public:
    // ?get_super_class@?$c_recursive_template_pattern@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@@@QBAPBV?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@XZ
    t_array const * get_super_class() const
    {
        return reinterpret_cast<t_array const *>(this);
    };

    // ?get_super_class@?$c_recursive_template_pattern@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@@@QAAPAV?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@XZ
    t_array * get_super_class()
    {
        return reinterpret_cast<t_array *>(this);
    };
};

template<typename t_array, typename t_type>
class c_array_operator_interface :
    private c_recursive_template_pattern<t_array>
{
public:
    // ??A?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QBAABV?$s_static_array@M$0BAA@@@J@Z
    t_type const & operator[](long index) const
    {
        assert_decomp(valid_index(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 42);
        return get_super_class()->begin()[index];
    };

    // ??A?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QAAAAV?$s_static_array@M$0BAA@@@J@Z
    t_type & operator[](long index)
    {
        assert_decomp(valid_index(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 36);
        return get_super_class()->begin()[index];
    };

    // ?begin@?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QAAPAV?$s_static_array@M$0BAA@@@XZ
    t_type * begin()
    {
        return get_super_class()->begin();
    };

    // ?begin@?$c_array_operator_interface@V?$c_wrapped_array_no_init@$$CBD@@$$CBD@@QBAPBDXZ
    t_type const * begin() const
    {
        return get_super_class()->begin();
    };

    t_type const * get_element(long index) const;
    t_type * get_element(long index);

    // ?get_elements@?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QAAPAV?$s_static_array@M$0BAA@@@XZ
    t_type * get_elements()
    {
        return begin();
    };

    // ?get_elements@?$c_array_operator_interface@V?$c_wrapped_array_no_init@$$CBD@@$$CBD@@QBAPBDXZ
    t_type const * get_elements() const
    {
        return begin();
    };

    // ?get_total_element_size@?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QBAJXZ
    long get_total_element_size() const
    {
        return count() * sizeof(t_type);
    };

    // ?valid_index@?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QBA_NJ@Z
    bool valid_index(long index) const
    {
        return static_cast<unsigned long>(index) < static_cast<unsigned long>(count());
    };

    // ?count@?$c_array_operator_interface@V?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@V?$s_static_array@M$0BAA@@@@@QBAJXZ
    long count() const
    {
        return get_super_class()->count();
    };
};

template<typename t_type>
class c_wrapped_array_no_init :
    public c_array_operator_interface<c_wrapped_array_no_init<t_type>, t_type>
{
public:
    // ?set_elements@?$c_wrapped_array_no_init@PBUs_tag_resource_definition@@@@QAAXPAPBUs_tag_resource_definition@@J@Z
    void set_elements(t_type * elements, long element_count)
    {
        assert_decomp(element_count>=0, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 233);
        m_elements = elements;
        m_element_count = element_count;
    };

    // ?begin@?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@QBAPBV?$s_static_array@M$0BAA@@@XZ
    t_type const * begin() const
    {
        return m_elements;
    };

    // ?begin@?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@QAAPAV?$s_static_array@M$0BAA@@@XZ
    t_type * begin()
    {
        return m_elements;
    };

    // ?count@?$c_wrapped_array_no_init@V?$s_static_array@M$0BAA@@@@@QBAJXZ
    long count() const
    {
        return m_element_count;
    };

protected:
    long m_element_count; // 0x0
    t_type * m_elements; // 0x4
};
static_assert(sizeof(c_wrapped_array_no_init<long>) == 0x8, "c_wrapped_array_no_init<long>");

template<typename t_type>
class c_wrapped_array :
    public c_wrapped_array_no_init<t_type>
{
public:
    // ??0?$c_wrapped_array@$$CBF@@QAA@XZ
    c_wrapped_array()
    {
        set_elements(NULL, 0);
    };

    // ??$?0$08@?$c_wrapped_array@PBUs_tag_resource_definition@@@@QAA@AAY08PBUs_tag_resource_definition@@@Z
    template<long k_element_count>
    c_wrapped_array(t_type (&elements)[k_element_count])
    {
        set_elements(elements, k_element_count);
    };

    // ??0?$c_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@QAA@PAUXAUDIOVOICEOUTPUTENTRY@@J@Z
    c_wrapped_array(t_type * elements, long element_count)
    {
        set_elements(elements, element_count);
    };

    // ??0?$c_wrapped_array@$$CBD@@QAA@PBD0@Z
    c_wrapped_array(t_type * begin, t_type * end)
    {
        set_elements(begin, end - begin);
    };

    // ??$?0D@?$c_wrapped_array@D@@QAA@AAV0@@Z (inline, owned by tag_resource_runtime.obj)
    template<typename t_other>
    c_wrapped_array(c_wrapped_array<t_other> & rhs);

    // ??$?0M@?$c_wrapped_array@$$CBM@@QAA@ABV?$c_wrapped_array@M@@@Z (inline, owned by voice_ring_buffer_effect.obj)
    template<typename t_other>
    c_wrapped_array(c_wrapped_array<t_other> const & rhs)
    {
        set_elements(rhs.get_elements(), rhs.count());
    };
};
static_assert(sizeof(c_wrapped_array<long>) == 0x8, "c_wrapped_array<long>");

// ??$make_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@YA?AV?$c_wrapped_array@UXAUDIOVOICEOUTPUTENTRY@@@@PAUXAUDIOVOICEOUTPUTENTRY@@J@Z
template<typename t_type>
c_wrapped_array<t_type> make_wrapped_array(t_type * elements, long element_count)
{
    return c_wrapped_array<t_type>(elements, element_count);
};

template<typename t_array, typename t_type>
class c_resizeable_array_operator_interface :
    public c_array_operator_interface<t_array, t_type>
{
};

// $TODO method bodies not reversed yet (inline in the target, e.g. sound_xaudio_xenon_mix_master.obj)
template<typename t_type, long k_count>
class c_static_sized_dynamic_array :
    public c_resizeable_array_operator_interface<c_static_sized_dynamic_array<t_type, k_count>, t_type>
{
public:
    typedef t_type const * const_iterator;

    c_static_sized_dynamic_array();

    // ?begin@?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@QBAPBUs_cache_file_codec_definition@@XZ
    t_type const * begin() const
    {
        return m_storage.begin();
    };

    // ?begin@?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@QAAPAUs_cache_file_codec_definition@@XZ
    t_type * begin()
    {
        return m_storage.begin();
    };

    // ?end@?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@QBAPBUs_cache_file_codec_definition@@XZ
    t_type const * end() const
    {
        return begin() + m_count;
    };

    // ?count@?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@QBAJXZ
    long count() const
    {
        return m_count;
    };

    // ?new_element_index@?$c_static_sized_dynamic_array@Us_cache_file_codec_definition@@$0HP@@@QAAJXZ
    long new_element_index()
    {
        long new_index = m_count;
        assert_decomp(m_storage.valid(new_index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 476);
        m_count++;
        return new_index;
    };

    void resize(long new_size);

    s_static_array<t_type, k_count> m_storage; // 0x0
    long m_count; // sizeof(m_storage)
};

template<typename t_type>
class c_typed_tag_block :
    public c_resizeable_array_operator_interface<c_typed_tag_block<t_type>, t_type>,
    public s_tag_block
{
public:
    t_type const * begin() const;
    t_type * begin();
    long count() const;
};
static_assert(sizeof(c_typed_tag_block<long>) == 0xC, "c_typed_tag_block<long>");

template<typename t_type, long k_size = sizeof(t_type), long k_alignment_bytes = __alignof(t_type)>
class c_opaque_data
{
public:
    // ?get@?$c_opaque_data@Vc_wrapped_flags@@$07$03@@QAAPAVc_wrapped_flags@@XZ
    t_type * get()
    {
        t_type * result = reinterpret_cast<t_type *>((reinterpret_cast<unsigned long>(m_opaque_data) + (k_alignment_bytes - 1)) & ~(k_alignment_bytes - 1));
        return result;
    };

    // ?get_const@?$c_opaque_data@Vc_function_definition@@$0BE@$03@@QBAPBVc_function_definition@@XZ
    t_type const * get_const() const
    {
        t_type const * result = reinterpret_cast<t_type const *>((reinterpret_cast<unsigned long>(m_opaque_data) + (k_alignment_bytes - 1)) & ~(k_alignment_bytes - 1));
        return result;
    };

private:
    unsigned char m_opaque_data[k_size]; // 0x0
};

template<typename t_type, long k_size = sizeof(t_type), long k_alignment_bytes = __alignof(t_type)>
class c_typed_opaque_data
{
public:
    // ??0?$c_typed_opaque_data@Vc_wrapped_flags@@$07$03@@QAA@XZ
    c_typed_opaque_data() :
        m_live_object(NULL)
    {
    };

    // ??1?$c_typed_opaque_data@Us_content_task_private_data@@$0CE@$03@@QAA@XZ
    ~c_typed_opaque_data()
    {
        if (m_live_object)
        {
            destruct();
        }
    };

    // ?construct@?$c_typed_opaque_data@Us_content_task_private_data@@$0CE@$03@@QAAPAUs_content_task_private_data@@XZ
    t_type * construct()
    {
        assert_decomp(!m_live_object, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1015);
        m_live_object = new (m_opaque_storage.get()) t_type();
        return m_live_object;
    };

    // ?destruct@?$c_typed_opaque_data@Us_content_task_private_data@@$0CE@$03@@QAAXXZ
    void destruct()
    {
        assert_decomp(m_live_object, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1077);
        m_live_object->~t_type();
        m_live_object = NULL;
    };

    // ??$construct@Vc_wrapped_flags@@@?$c_typed_opaque_data@Vc_wrapped_flags@@$07$03@@QAAPAVc_wrapped_flags@@V1@@Z
    template<typename t_argument>
    t_type * construct(t_argument argument)
    {
        assert_decomp(!m_live_object, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1024);
        m_live_object = new (m_opaque_storage.get()) t_type(argument);
        return m_live_object;
    };

    // ?get@?$c_typed_opaque_data@Vc_wrapped_flags@@$07$03@@QAAPAVc_wrapped_flags@@XZ
    t_type * get()
    {
        assert_decomp(m_live_object, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1087);
        return m_live_object;
    };

    // ?get_const@?$c_typed_opaque_data@Us_content_task_private_data@@$0CE@$03@@QBAPBUs_content_task_private_data@@XZ
    t_type const * get_const() const
    {
        assert_decomp(m_live_object, "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1094);
        return m_live_object;
    };

    // ?alive@?$c_typed_opaque_data@Vc_wrapped_flags@@$07$03@@QBA_NXZ
    bool alive() const
    {
        return m_live_object != NULL;
    };

private:
    c_opaque_data<t_type, k_size, k_alignment_bytes> m_opaque_storage; // 0x0
    t_type * m_live_object;
};

template<typename t_type>
class c_bit_vector_operator_interface :
    private c_recursive_template_pattern<t_type>
{
public:
    void clear();

    // ?set_all@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@QAAXXZ
    void set_all()
    {
        long bit_count;
        unsigned long * bit_storage = get_bit_storage();
        bit_count = this->bit_count();
        memset(bit_storage, -1, sizeof(unsigned long) * ((static_cast<unsigned long>(bit_count) + (LONG_BITS - 1)) >> 5));
    };

    // ?test@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@QBA_NJ@Z (f i, owned by game_sound_transmission.obj, body not reversed yet)
    bool test(long index) const;

    // $TODO nonmatching (85.82% in cseries_strings.obj: target keeps each branch's assigned value in its own stack temporary)
    // ?set@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@QAAXJ_N@Z
    void set(long index, bool value)
    {
        assert_decomp(verify_index(index), "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\memory\\wrapped_arrays.h", 1148);
        unsigned long * bit_storage = get_bit_storage();
        BIT_VECTOR_SET_FLAG(bit_storage, index, value);
    };

    unsigned long const * get_bits() const;
    unsigned long * get_bits_unsafe();

    // ?bit_count@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@QBAJXZ
    long bit_count() const
    {
        return get_super_class()->bit_count();
    };

private:
    // ?verify_index@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@ABA_NK@Z
    bool verify_index(unsigned long index) const
    {
        return VALID_INDEX(index, static_cast<unsigned long>(bit_count()));
    };

    unsigned long const * get_bit_storage() const;

    // ?get_bit_storage@?$c_bit_vector_operator_interface@Vc_wrapped_flags@@@@AAAPAKXZ
    unsigned long * get_bit_storage()
    {
        return get_super_class()->get_bit_storage();
    };
};

class c_wrapped_flags :
    public c_bit_vector_operator_interface<c_wrapped_flags>
{
public:
    friend class c_bit_vector_operator_interface<c_wrapped_flags>;

    // ??0c_wrapped_flags@@QAA@XZ (f i, owned by game_sound_transmission.obj, body not reversed yet)
    c_wrapped_flags();

    // ?bit_count@c_wrapped_flags@@QBAJXZ
    long bit_count() const
    {
        return m_bit_count;
    };

private:
    unsigned long const * get_bit_storage() const;

    // ?get_bit_storage@c_wrapped_flags@@AAAPAKXZ
    unsigned long * get_bit_storage()
    {
        return m_bit_storage;
    };

    unsigned long * m_bit_storage; // 0x0
    unsigned long m_bit_count; // 0x4
};
static_assert(sizeof(c_wrapped_flags) == 0x8, "c_wrapped_flags");

/* ---------- prototypes */

class c_allocation_interface;

extern c_basic_buffer<void> allocate_scratch_buffer(c_allocation_interface * allocator, unsigned long size);
extern c_basic_buffer<void> allocate_tracked_scratch_buffer(c_allocation_interface * allocator, unsigned long size, char const * name);
extern void free_scratch_buffer(c_allocation_interface * allocator, c_basic_buffer<void> * buffer);
extern bool address_in_buffer(void const * address, c_basic_buffer<void const> buffer);
extern bool buffer_in_buffer(c_basic_buffer<void const> inner_buffer, c_basic_buffer<void const> outer_buffer);
extern bool buffer_contents_equal(c_basic_buffer<void const> lhs_buffer, c_basic_buffer<void const> rhs_buffer);
extern void copy_buffer(c_basic_buffer<void> dest_buffer, c_basic_buffer<void const> source_buffer);
extern void move_buffer(c_basic_buffer<void> dest_buffer, c_basic_buffer<void const> source_buffer);

/* ---------- globals */

/* ---------- public code */

#endif // __WRAPPED_ARRAYS_H__
