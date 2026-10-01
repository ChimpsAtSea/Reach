#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_struct_fixup.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_struct_fixup.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<class c_basic_buffer<void>, 2>::k_element_count; // "?k_element_count@?$s_static_array@V?$c_basic_buffer@X@@$01@@2JB"

// void tag_struct_initialize(class c_basic_buffer<void> &, struct s_tag_struct_definition const *);
// void tag_struct_dispose(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *);
// bool tag_struct_fixup_manually(struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *, bool);
// public: c_tag_struct_fixup_iterator::c_tag_struct_fixup_iterator(class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_basic_buffer<void> &, struct s_tag_struct_definition const *, class c_tag_allocator *);
// public: c_tag_struct_fixup_iterator::~c_tag_struct_fixup_iterator(void);
// public: bool c_tag_struct_fixup_iterator::next(void);
// public: struct s_tag_struct_definition const * c_tag_struct_fixup_iterator::get_dest_struct_definition(void) const;
// public: struct s_tag_struct_definition const * c_tag_struct_fixup_iterator::get_source_struct_definition(void) const;
// public: class c_basic_buffer<void> & c_tag_struct_fixup_iterator::get_source_struct(void);
// public: class c_basic_buffer<void> & c_tag_struct_fixup_iterator::get_dest_struct(void);
// public: bool c_tag_struct_fixup_iterator::can_dispose_source_struct(void) const;
// public: s_static_array<class c_basic_buffer<void>, 2>::s_static_array<class c_basic_buffer<void>, 2>(void);
// public: class c_basic_buffer<void> & s_static_array<class c_basic_buffer<void>, 2>::operator[]<bool>(bool);
// public: static long s_static_array<class c_basic_buffer<void>, 2>::get_count(void);
// public: class c_basic_buffer<void> & s_static_array<class c_basic_buffer<void>, 2>::operator[]<int>(int);
// public: class c_basic_buffer<void> & s_static_array<class c_basic_buffer<void>, 2>::operator[]<long>(long);
// public: static bool s_static_array<class c_basic_buffer<void>, 2>::valid<long>(long);
// public: static bool s_static_array<class c_basic_buffer<void>, 2>::valid<int>(int);

void tag_struct_initialize(c_basic_buffer<void> & struct_buffer, s_tag_struct_definition const * struct_definition)
{
    mangled_ppc("?tag_struct_initialize@@YAXAAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@@Z");

    tag_struct_construct_in_place(struct_definition, struct_buffer, 1);
};

void tag_struct_dispose(c_basic_buffer<void> & struct_buffer, s_tag_struct_definition const * struct_definition, c_tag_allocator * allocator)
{
    mangled_ppc("?tag_struct_dispose@@YAXAAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@PAVc_tag_allocator@@@Z");

    tag_struct_destroy_in_place(struct_definition, struct_buffer, 1);
};

bool tag_struct_fixup_manually(s_tag_struct_definition const * original_struct_definition, c_basic_buffer<void> & root_source_struct, s_tag_struct_definition const * root_source_struct_definition, c_basic_buffer<void> & final_dest_struct, s_tag_struct_definition const * final_dest_struct_definition, c_tag_allocator * allocator, bool first_fixup)
{
    mangled_ppc("?tag_struct_fixup_manually@@YA_NPBUs_tag_struct_definition@@AAV?$c_basic_buffer@X@@010PAVc_tag_allocator@@_N@Z");

    bool result = true;
    c_tag_struct_fixup_iterator iterator(root_source_struct, root_source_struct_definition, final_dest_struct, final_dest_struct_definition, allocator);
    bool first = first_fixup;
    while (result && iterator.next())
    {
        c_basic_buffer<void> src_struct = iterator.get_source_struct();
        c_basic_buffer<void> dest_struct = iterator.get_dest_struct();
        s_tag_struct_definition const * dest_struct_definition = iterator.get_dest_struct_definition();
        s_tag_struct_definition const * source_struct_definition = iterator.get_source_struct_definition();

        assert_tag_debug_untracked_jul_11_2011(183, dest_struct_definition);
        assert_tag_debug_untracked_jul_11_2011(184, source_struct_definition);
        assert_tag_debug_untracked_jul_11_2011(186, dest_struct_definition->get_ancestor_definition()==source_struct_definition);
        assert_tag_debug_untracked_jul_11_2011(187, dest_struct_definition->get_struct_vtable()->has_fixup_old_struct_proc() || dest_struct_definition->get_struct_vtable()->has_fixup_old_struct_from_disk_proc());
        assert_tag_debug_untracked_jul_11_2011(188, dest_struct_definition->get_struct_vtable()->has_fixup_old_struct_definition());

        tag_struct_initialize(dest_struct, dest_struct_definition);
        if (dest_struct_definition->get_struct_vtable()->has_fixup_old_struct_proc())
        {
            result = dest_struct_definition->get_struct_vtable()->fixup_old_struct_thunk(src_struct, source_struct_definition, dest_struct, dest_struct_definition, allocator, first);
        }
        else
        {
            assert_tag_debug_untracked_jul_11_2011(198, dest_struct_definition->get_struct_vtable()->has_fixup_old_struct_from_disk_proc());
            result = dest_struct_definition->get_struct_vtable()->fixup_old_struct_from_disk_thunk(original_struct_definition, src_struct, source_struct_definition, dest_struct, dest_struct_definition, allocator, first);
        }

        if (iterator.can_dispose_source_struct())
        {
            tag_struct_dispose(src_struct, source_struct_definition, allocator);
        }
        first = false;
    }

    return result;
};

c_tag_struct_fixup_iterator::c_tag_struct_fixup_iterator(c_basic_buffer<void> & source_struct, s_tag_struct_definition const * source_struct_definition, c_basic_buffer<void> & dest_struct, s_tag_struct_definition const * dest_struct_definition, c_tag_allocator * allocator) :
    m_source_struct_definition(source_struct_definition),
    m_dest_struct_definition(dest_struct_definition),
    m_allocator(allocator),
    m_source_struct(source_struct),
    m_dest_struct(dest_struct),
    m_step_index(NONE)
{
    mangled_ppc("??0c_tag_struct_fixup_iterator@@QAA@AAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@01PAVc_tag_allocator@@@Z");

    long maximum_struct_size = 0;
    long maximum_alignment_bits = 0;
    long depth = 0;
    for (s_tag_struct_definition const * struct_definition_iterator = source_struct_definition; struct_definition_iterator != dest_struct_definition; struct_definition_iterator = struct_definition_iterator->get_descendent_definition(), depth++)
    {
        assert_tag_debug_untracked_jul_11_2011(56, struct_definition_iterator);
        maximum_struct_size = MAX(maximum_struct_size, struct_definition_iterator->get_struct_size());
        maximum_alignment_bits = MAX(maximum_alignment_bits, struct_definition_iterator->get_alignment_bits());
    }

    m_intermediate_alignment_bits = maximum_alignment_bits;
    if (depth > 1)
    {
        m_intermediate_structs[0].set_buffer(m_allocator->allocate_temporary(maximum_struct_size, maximum_alignment_bits, m_source_struct_definition->get_name()), maximum_struct_size);
    }
    if (depth > 2)
    {
        m_intermediate_structs[1].set_buffer(m_allocator->allocate_temporary(maximum_struct_size, maximum_alignment_bits, m_source_struct_definition->get_name()), maximum_struct_size);
    }

    m_current_source_struct_definition = NULL;
    m_current_dest_struct_definition = source_struct_definition;
};

c_tag_struct_fixup_iterator::~c_tag_struct_fixup_iterator(void)
{
    mangled_ppc("??1c_tag_struct_fixup_iterator@@QAA@XZ");

    for (long struct_index = 0; struct_index < m_intermediate_structs.get_count(); struct_index++)
    {
        if (!m_intermediate_structs[struct_index].empty())
        {
            m_allocator->deallocate_temporary(m_intermediate_structs[struct_index].begin(), m_intermediate_alignment_bits);
            m_intermediate_structs[struct_index].set_buffer(NULL, 0);
        }
    }
};

bool c_tag_struct_fixup_iterator::next(void)
{
    mangled_ppc("?next@c_tag_struct_fixup_iterator@@QAA_NXZ");

    m_step_index++;
    m_current_source_struct_definition = m_current_dest_struct_definition;
    m_current_dest_struct_definition = m_current_source_struct_definition->get_descendent_definition();

    return m_current_source_struct_definition != m_dest_struct_definition;
};

s_tag_struct_definition const * c_tag_struct_fixup_iterator::get_dest_struct_definition(void) const
{
    mangled_ppc("?get_dest_struct_definition@c_tag_struct_fixup_iterator@@QBAPBUs_tag_struct_definition@@XZ");

    return m_current_dest_struct_definition;
};

s_tag_struct_definition const * c_tag_struct_fixup_iterator::get_source_struct_definition(void) const
{
    mangled_ppc("?get_source_struct_definition@c_tag_struct_fixup_iterator@@QBAPBUs_tag_struct_definition@@XZ");

    return m_current_source_struct_definition;
};

c_basic_buffer<void> & c_tag_struct_fixup_iterator::get_source_struct(void)
{
    mangled_ppc("?get_source_struct@c_tag_struct_fixup_iterator@@QAAAAV?$c_basic_buffer@X@@XZ");

    return m_current_source_struct_definition == m_source_struct_definition ? m_source_struct : m_intermediate_structs[(m_step_index & 1) == 0];
};

c_basic_buffer<void> & c_tag_struct_fixup_iterator::get_dest_struct(void)
{
    mangled_ppc("?get_dest_struct@c_tag_struct_fixup_iterator@@QAAAAV?$c_basic_buffer@X@@XZ");

    return m_current_dest_struct_definition == m_dest_struct_definition ? m_dest_struct : m_intermediate_structs[m_step_index & 1];
};

bool c_tag_struct_fixup_iterator::can_dispose_source_struct(void) const
{
    mangled_ppc("?can_dispose_source_struct@c_tag_struct_fixup_iterator@@QBA_NXZ");

    return m_step_index != 0;
};

