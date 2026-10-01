#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\cache_file_tag_api_interop.cpp"
/* ---------- headers */

#include "omaha\cache\cache_file_tag_api_interop.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\bitmaps\bitmap_group_xenon_interop.h"
#include "omaha\cseries\cseries.h"
#include "omaha\math\integer_math.h"
#include "omaha\memory\contiguous_allocation.h"
#include "omaha\rasterizer\rasterizer_shader_definitions.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_vertex_buffers.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_cache_file_tag_interop_vtable const * g_cache_file_tag_interop_vtable[6] =
{
    &g_d3d_vertex_buffer_interop_vtable,
    &g_d3d_index_buffer_interop_vtable,
    &g_d3d_texture_interop_vtable,
    &g_d3d_texture_interleaved_interop_vtable,
    &g_d3d_vertex_shader_interop_vtable,
    &g_d3d_pixel_shader_interop_vtable,
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_cache_file_tag_interop_vtable const **g_cache_file_tag_interop_vtable; // "?g_cache_file_tag_interop_vtable@@3PAPBUs_cache_file_tag_interop_vtable@@A"

// long cache_file_tag_interop_get_type_count(void);
// char const * cache_file_tag_interop_get_type_name(long);
// struct s_cache_file_tag_interop_vtable const * cache_file_get_interop_vtable(long);
// struct s_tag_persistent_identifier cache_file_tag_interop_get_type_identifier(long);
// long cache_file_tag_interop_get_type_index(struct s_tag_persistent_identifier const &);
// unsigned long cache_file_tag_interop_get_object_size(long, unsigned long *);
// bool cache_file_tag_interop_fixup(long, struct s_tag_interop *, class c_tag_interop_verifier *);
// bool cache_file_tag_interop_teardown(long, struct s_tag_interop *);
// bool cache_file_tag_interop_locked(long, struct s_tag_interop *);
// public: c_tag_interop_object_type_info::c_tag_interop_object_type_info(struct s_tag_persistent_identifier const &);
// public: c_tag_interop_object_type_info::c_tag_interop_object_type_info(long);
// public: bool c_tag_interop_object_type_info::valid(void) const;
// public: unsigned long c_tag_interop_object_type_info::size(void) const;
// public: unsigned long c_tag_interop_object_type_info::alignment_bits(void) const;
// public: c_cache_file_tag_interop_bulk_sizer::c_cache_file_tag_interop_bulk_sizer(void);
// public: bool c_cache_file_tag_interop_bulk_sizer::add_type_with_identifier(struct s_tag_persistent_identifier const &);
// public: void c_cache_file_tag_interop_bulk_sizer::add_type_with_type_index(long);
// public: void c_cache_file_tag_interop_bulk_sizer::add_type_manually(unsigned long, unsigned long);
// public: unsigned long c_cache_file_tag_interop_bulk_sizer::get_size(void) const;
// public: unsigned long c_cache_file_tag_interop_bulk_sizer::get_alignment_bits(void) const;
// public: unsigned long c_cache_file_tag_interop_bulk_sizer::get_unaligned_total_allocation_size(void) const;
// public: unsigned long c_cache_file_tag_interop_bulk_sizer::get_next_offset(long) const;
// public: unsigned long c_cache_file_tag_interop_bulk_sizer::get_next_offset_manual(unsigned long) const;
// public: c_cache_file_tag_inteorp_bulk_allocator::c_cache_file_tag_inteorp_bulk_allocator(void *, unsigned long);
// public: bool c_cache_file_tag_inteorp_bulk_allocator::allocate_and_fixup(long, struct s_tag_interop *, class c_tag_interop_verifier *);

long cache_file_tag_interop_get_type_count(void)
{
    mangled_ppc("?cache_file_tag_interop_get_type_count@@YAJXZ");

    return NUMBEROF(g_cache_file_tag_interop_vtable);
};

char const * cache_file_tag_interop_get_type_name(long type_index)
{
    mangled_ppc("?cache_file_tag_interop_get_type_name@@YAPBDJ@Z");

    return cache_file_get_interop_vtable(type_index)->type_name;
};

s_cache_file_tag_interop_vtable const * cache_file_get_interop_vtable(long type_index)
{
    mangled_ppc("?cache_file_get_interop_vtable@@YAPBUs_cache_file_tag_interop_vtable@@J@Z");

    assert_tag_debug_untracked_jul_11_2011(31, VALID_INDEX(type_index, NUMBEROF(g_cache_file_tag_interop_vtable)));

    return g_cache_file_tag_interop_vtable[type_index];
};

s_tag_persistent_identifier cache_file_tag_interop_get_type_identifier(long type_index)
{
    mangled_ppc("?cache_file_tag_interop_get_type_identifier@@YA?AUs_tag_persistent_identifier@@J@Z");

    return cache_file_get_interop_vtable(type_index)->interop_identifier;
};

long cache_file_tag_interop_get_type_index(s_tag_persistent_identifier const & identifier)
{
    mangled_ppc("?cache_file_tag_interop_get_type_index@@YAJABUs_tag_persistent_identifier@@@Z");

    long actual_type_index = NONE;
    for (long type_index = 0; static_cast<unsigned long>(type_index) < NUMBEROF(g_cache_file_tag_interop_vtable); type_index++)
    {
        if (tag_persistent_identifiers_equal(identifier, cache_file_get_interop_vtable(type_index)->interop_identifier) ||
            tag_persistent_identifiers_equal(identifier, cache_file_get_interop_vtable(type_index)->mat_was_dumb_interop_identifier))
        {
            actual_type_index = type_index;
            break;
        }
    }

    return actual_type_index;
};

unsigned long cache_file_tag_interop_get_object_size(long type_index, unsigned long * out_alignment_bits)
{
    mangled_ppc("?cache_file_tag_interop_get_object_size@@YAKJPAK@Z");

    assert_tag_debug_untracked_jul_11_2011(78, VALID_INDEX(type_index, NUMBEROF(g_cache_file_tag_interop_vtable)));
    assert_tag_debug_untracked_jul_11_2011(79, out_alignment_bits);

    unsigned long size;
    s_cache_file_tag_interop_vtable const * interop_vtable = cache_file_get_interop_vtable(type_index);
    size = interop_vtable->interop_object_size;
    *out_alignment_bits = interop_vtable->interop_object_alignment_bits;

    return size;
};

bool cache_file_tag_interop_fixup(long type_index, s_tag_interop * in_out_interop, c_tag_interop_verifier * interop_verifier)
{
    mangled_ppc("?cache_file_tag_interop_fixup@@YA_NJPAUs_tag_interop@@PAVc_tag_interop_verifier@@@Z");

    assert_tag_debug_untracked_jul_11_2011(94, VALID_INDEX(type_index, NUMBEROF(g_cache_file_tag_interop_vtable)));
    assert_tag_debug_untracked_jul_11_2011(95, in_out_interop);

    s_cache_file_tag_interop_vtable const * interop_vtable = cache_file_get_interop_vtable(type_index);
    bool success = interop_vtable->on_fixup_interop == NULL;
    if (interop_vtable->on_fixup_interop != NULL)
    {
        success = interop_vtable->on_fixup_interop(in_out_interop, interop_verifier);
    }

    return success;
};

bool cache_file_tag_interop_teardown(long type_index, s_tag_interop * in_out_interop)
{
    mangled_ppc("?cache_file_tag_interop_teardown@@YA_NJPAUs_tag_interop@@@Z");

    assert_tag_debug_untracked_jul_11_2011(113, VALID_INDEX(type_index, NUMBEROF(g_cache_file_tag_interop_vtable)));
    assert_tag_debug_untracked_jul_11_2011(114, in_out_interop);

    s_cache_file_tag_interop_vtable const * interop_vtable = cache_file_get_interop_vtable(type_index);
    bool success = interop_vtable->on_teardown_interop == NULL;
    if (interop_vtable->on_teardown_interop != NULL)
    {
        success = interop_vtable->on_teardown_interop(in_out_interop);
    }

    return success;
};

bool cache_file_tag_interop_locked(long type_index, s_tag_interop * in_out_interop)
{
    mangled_ppc("?cache_file_tag_interop_locked@@YA_NJPAUs_tag_interop@@@Z");

    assert_tag_debug_untracked_jul_11_2011(133, VALID_INDEX(type_index, NUMBEROF(g_cache_file_tag_interop_vtable)));
    assert_tag_debug_untracked_jul_11_2011(134, in_out_interop);

    s_cache_file_tag_interop_vtable const * interop_vtable = cache_file_get_interop_vtable(type_index);
    bool is_locked = false;
    if (interop_vtable->check_if_interop_locked != NULL)
    {
        is_locked = interop_vtable->check_if_interop_locked(in_out_interop);
    }

    return is_locked;
};

c_tag_interop_object_type_info::c_tag_interop_object_type_info(s_tag_persistent_identifier const & type_identifier)
{
    mangled_ppc("??0c_tag_interop_object_type_info@@QAA@ABUs_tag_persistent_identifier@@@Z");

    m_type_index = cache_file_tag_interop_get_type_index(type_identifier);
    if (valid())
    {
        m_size = cache_file_tag_interop_get_object_size(m_type_index, &m_alignment_bits);
    }
};

c_tag_interop_object_type_info::c_tag_interop_object_type_info(long type_index)
{
    mangled_ppc("??0c_tag_interop_object_type_info@@QAA@J@Z");

    m_type_index = type_index;
    if (valid())
    {
        m_size = cache_file_tag_interop_get_object_size(m_type_index, &m_alignment_bits);
    }
};

bool c_tag_interop_object_type_info::valid(void) const
{
    mangled_ppc("?valid@c_tag_interop_object_type_info@@QBA_NXZ");

    return VALID_INDEX(m_type_index, NUMBEROF(g_cache_file_tag_interop_vtable));
};

unsigned long c_tag_interop_object_type_info::size(void) const
{
    mangled_ppc("?size@c_tag_interop_object_type_info@@QBAKXZ");

    assert_tag_debug_untracked_jul_11_2011(183, valid());

    return m_size;
};

unsigned long c_tag_interop_object_type_info::alignment_bits(void) const
{
    mangled_ppc("?alignment_bits@c_tag_interop_object_type_info@@QBAKXZ");

    assert_tag_debug_untracked_jul_11_2011(191, valid());

    return m_alignment_bits;
};

c_cache_file_tag_interop_bulk_sizer::c_cache_file_tag_interop_bulk_sizer(void) :
    m_alignment_bits(0),
    m_total_size(0)
{
    mangled_ppc("??0c_cache_file_tag_interop_bulk_sizer@@QAA@XZ");
};

bool c_cache_file_tag_interop_bulk_sizer::add_type_with_identifier(s_tag_persistent_identifier const & identifier)
{
    mangled_ppc("?add_type_with_identifier@c_cache_file_tag_interop_bulk_sizer@@QAA_NABUs_tag_persistent_identifier@@@Z");

    bool success = false;
    c_tag_interop_object_type_info interop_type(identifier);
    if (interop_type.valid())
    {
        add_type_manually(interop_type.size(), interop_type.alignment_bits());
        success = true;
    }

    return success;
};

void c_cache_file_tag_interop_bulk_sizer::add_type_with_type_index(long type_index)
{
    mangled_ppc("?add_type_with_type_index@c_cache_file_tag_interop_bulk_sizer@@QAAXJ@Z");

    unsigned long type_alignment_bits;
    unsigned long type_size = cache_file_tag_interop_get_object_size(type_index, &type_alignment_bits);
    add_type_manually(type_size, type_alignment_bits);
};

void c_cache_file_tag_interop_bulk_sizer::add_type_manually(unsigned long size, unsigned long alignment_bits)
{
    mangled_ppc("?add_type_manually@c_cache_file_tag_interop_bulk_sizer@@QAAXKK@Z");

    m_alignment_bits = MAX(m_alignment_bits, alignment_bits);
    m_total_size = align_up(m_total_size, m_alignment_bits);
    m_total_size += size;
};

unsigned long c_cache_file_tag_interop_bulk_sizer::get_size(void) const
{
    mangled_ppc("?get_size@c_cache_file_tag_interop_bulk_sizer@@QBAKXZ");

    return m_total_size;
};

unsigned long c_cache_file_tag_interop_bulk_sizer::get_alignment_bits(void) const
{
    mangled_ppc("?get_alignment_bits@c_cache_file_tag_interop_bulk_sizer@@QBAKXZ");

    return m_alignment_bits;
};

unsigned long c_cache_file_tag_interop_bulk_sizer::get_unaligned_total_allocation_size(void) const
{
    mangled_ppc("?get_unaligned_total_allocation_size@c_cache_file_tag_interop_bulk_sizer@@QBAKXZ");

    return get_unaligned_allocation_size(m_total_size, m_alignment_bits);
};

unsigned long c_cache_file_tag_interop_bulk_sizer::get_next_offset(long type_index) const
{
    mangled_ppc("?get_next_offset@c_cache_file_tag_interop_bulk_sizer@@QBAKJ@Z");

    unsigned long type_alignment_bits;
    unsigned long unused_type_size = cache_file_tag_interop_get_object_size(type_index, &type_alignment_bits);

    return get_next_offset_manual(type_alignment_bits);
};

unsigned long c_cache_file_tag_interop_bulk_sizer::get_next_offset_manual(unsigned long alignment_bits) const
{
    mangled_ppc("?get_next_offset_manual@c_cache_file_tag_interop_bulk_sizer@@QBAKK@Z");

    return align_up(m_total_size, alignment_bits);
};

c_cache_file_tag_inteorp_bulk_allocator::c_cache_file_tag_inteorp_bulk_allocator(void * base_address, unsigned long total_size) :
    m_interop_buffer(base_address, total_size),
    m_next_interop_offset(0)
{
    mangled_ppc("??0c_cache_file_tag_inteorp_bulk_allocator@@QAA@PAXK@Z");
};

bool c_cache_file_tag_inteorp_bulk_allocator::allocate_and_fixup(long cache_file_interop_type, s_tag_interop * in_out_interop, c_tag_interop_verifier * interop_verifier)
{
    mangled_ppc("?allocate_and_fixup@c_cache_file_tag_inteorp_bulk_allocator@@QAA_NJPAUs_tag_interop@@PAVc_tag_interop_verifier@@@Z");

    bool success = false;
    assert_tag_debug_untracked_jul_11_2011(293, in_out_interop->address==NULL);

    c_tag_interop_object_type_info interop_type_info(cache_file_interop_type);
    if (interop_type_info.valid())
    {
        void * next_address = m_interop_buffer.get_range(m_next_interop_offset, 0);
        unsigned long aligned_offset = m_next_interop_offset + pointer_distance32(next_address, align_pointer(next_address, interop_type_info.alignment_bits()));
        in_out_interop->address = m_interop_buffer.get_range(aligned_offset, interop_type_info.size());
        m_next_interop_offset = aligned_offset + interop_type_info.size();
        success = cache_file_tag_interop_fixup(cache_file_interop_type, in_out_interop, interop_verifier);
    }

    return success;
};
