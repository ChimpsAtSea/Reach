#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\synchronization\\lock_hierarchy.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\lock_hierarchy.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\files\simple_file.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_lock_node const *, 8>::k_element_count; // "?k_element_count@?$s_static_array@PBUs_lock_node@@$07@@2JB"

// public: void c_lock_hierarchy::initialize(class c_allocation_interface *);
// public: long c_lock_hierarchy::declare_object(unsigned long, char const *);
// public: void c_lock_hierarchy::declare_blocking_dependency(long, long);
// public: c_path_finder::c_path_finder(void);
// public: void c_lock_hierarchy::declare_optional_dependency(long, long);
// public: void c_lock_hierarchy::declare_reverse_dependency(long, long);
// public: void c_lock_hierarchy::finalize(void);
// public: void c_lock_hierarchy::dispose(void);
// public: enum e_lock_relationship c_lock_hierarchy::query_blocking_relationship(long, long, long, long *, unsigned long *, long *) const;
// public: bool c_lock_hierarchy::query_optional_dependency(long, long) const;
// public: bool c_lock_hierarchy::query_reverse_dependency(long, long) const;
// public: long c_lock_hierarchy::query_prerequisites(long, long, long *, unsigned long *) const;
// public: long c_lock_hierarchy::query_optional_acquisition(long, long, long const *, long, long *, unsigned long *) const;
// public: void c_lock_hierarchy::dump_as_text(class c_simple_file *) const;
// public: c_hierarchy_dumper::c_hierarchy_dumper(void);
// public: void c_lock_hierarchy::dump_as_graphviz(class c_simple_file *) const;
// public: struct s_lock_node * c_lock_hierarchy::node_get(long);
// public: struct s_lock_link * c_lock_hierarchy::link_get(long);
// public: struct s_lock_node const * c_lock_hierarchy::node_get_const(long) const;
// public: struct s_lock_link const * c_lock_hierarchy::link_get_const(long) const;
// public: struct s_data_array const * c_lock_hierarchy::node_array_get_const(void) const;
// private: void c_lock_hierarchy::validate(void) const;
// enum e_lock_link_type operator++(enum e_lock_link_type &, int);
// private: void c_lock_hierarchy::validate_prerequisite_chain(long) const;
// private: long c_lock_hierarchy::find_link(long, long, enum e_lock_link_type) const;
// private: long c_lock_hierarchy::find_or_add_link(long, long, enum e_lock_link_type);
// private: void c_lock_hierarchy::build_ancestors_and_descendants_beneath_node(long);
// private: void c_lock_hierarchy::add_reverse_dependency(long, long);
// private: void c_lock_hierarchy::add_ancestor_prerequisites(long, long, class c_static_stack<long, 128> *);
// private: void c_lock_hierarchy::add_prerequisite(long, long);
// private: void c_lock_hierarchy::add_prerequisite_dependencies(long);
// private: void c_lock_hierarchy::declare_prerequisite_dependency(long, long, long);
// public: void c_path_finder::reset(void);
// public: bool c_path_finder::visited_node(long) const;
// public: void c_path_finder::find_cycles(class c_lock_hierarchy const *, long);
// public: class s_static_bitarray<128> const * c_path_finder::find_children(class c_lock_hierarchy const *, long);
// public: bool c_path_finder::find_path(class c_lock_hierarchy const *, long, long, long, long *, long *);
// private: void c_path_finder::recurse(class c_lock_hierarchy const *, long, long, long, long *, long *);
// public: void c_hierarchy_dumper::dump(enum c_hierarchy_dumper::e_dump_type, class c_lock_hierarchy const *, class c_simple_file *);
// private: void c_hierarchy_dumper::recurse(enum c_hierarchy_dumper::e_dump_type, class c_lock_hierarchy const *, long, class c_simple_file *, long *, long *);
// public: long const * s_static_array<long, 8>::get_elements(void) const;
// public: static unsigned int s_static_array<long, 8>::get_element_size(void);
// public: unsigned long const * s_static_array<unsigned long, 8>::get_elements(void) const;
// public: static unsigned int s_static_array<unsigned long, 8>::get_element_size(void);
// public: bool c_static_stack<long, 128>::empty(void) const;
// public: long c_static_stack<long, 128>::top(void) const;
// public: long c_static_stack<long, 128>::count(void) const;
// public: void c_static_stack<long, 128>::clear(void);
// public: void c_static_stack<long, 128>::push_back(long const &);
// public: void c_static_stack<long, 128>::pop(void);
// public: long & c_static_stack<long, 128>::operator[](long);
// public: long & c_static_stack<long, 128>::get_element(long);
// public: long * c_static_stack<long, 128>::get_elements(void);
// public: c_static_stack<long, 128>::c_static_stack<long, 128>(void);
// public: void c_data_iterator<struct s_lock_node>::begin(struct s_data_array *);
// public: bool c_data_iterator<struct s_lock_node>::next(void);
// public: struct s_lock_node * c_data_iterator<struct s_lock_node>::get_datum(void) const;
// public: long c_data_iterator<struct s_lock_node>::get_index(void) const;
// public: void c_data_iterator<struct s_lock_link>::begin(struct s_data_array *);
// public: bool c_data_iterator<struct s_lock_link>::next(void);
// public: long c_data_iterator<struct s_lock_link>::get_absolute_index(void) const;
// public: void c_data_iterator_const<struct s_lock_node>::begin(struct s_data_array const *);
// public: bool c_data_iterator_const<struct s_lock_node>::next(void);
// public: struct s_lock_node const * c_data_iterator_const<struct s_lock_node>::get_datum(void) const;
// public: long c_data_iterator_const<struct s_lock_node>::get_index(void) const;
// public: long c_data_iterator_const<struct s_lock_node>::get_absolute_index(void) const;
// public: bool c_static_stack<long, 128>::valid(void) const;
// public: bool c_static_stack<long, 128>::valid(long) const;
// public: long c_static_stack<long, 128>::push(void);
// public: long * c_static_stack<long, 128>::get(long);
// public: bool c_static_stack<long, 128>::full(void) const;
// public: long const & s_static_array<long, 4>::operator[]<enum e_lock_link_type>(enum e_lock_link_type) const;
// public: long & s_static_array<long, 128>::operator[]<int>(int);
// public: struct s_lock_node const *& s_static_array<struct s_lock_node const *, 8>::operator[]<long>(long);
// public: long & s_static_array<long, 4>::operator[]<enum e_lock_link_type>(enum e_lock_link_type);
// public: bool const s_static_bitarray<128>::operator[]<long>(long) const;
// public: static bool s_static_array<long, 4>::valid<enum e_lock_link_type>(enum e_lock_link_type);
// public: static bool s_static_array<long, 128>::valid<int>(int);
// public: static bool s_static_array<struct s_lock_node const *, 8>::valid<long>(long);
// public: static bool s_static_bitarray<128>::valid<long>(long);

void c_lock_hierarchy::initialize(c_allocation_interface * allocator)
{
    mangled_ppc("?initialize@c_lock_hierarchy@@QAAXPAVc_allocation_interface@@@Z");

    assert_tag_debug_untracked_jul_11_2011(138, !m_initialized);
    assert_tag_debug_untracked_jul_11_2011(139, allocator);

    m_finalized = false;

    m_nodes = data_new("lock hierarchy nodes", k_maximum_lock_nodes, sizeof(s_lock_node), 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 143, allocator);
    assert_tag_debug_untracked_jul_11_2011(144, m_nodes!=NULL);
    data_make_valid(m_nodes);

    m_links = data_new("lock hierarchy links", k_maximum_lock_links, sizeof(s_lock_link), 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 147, allocator);
    assert_tag_debug_untracked_jul_11_2011(148, m_links!=NULL);
    data_make_valid(m_links);

    m_initialized = true;
};

long c_lock_hierarchy::declare_object(unsigned long object_id, char const * name)
{
    mangled_ppc("?declare_object@c_lock_hierarchy@@QAAJKPBD@Z");

    assert_tag_debug_untracked_jul_11_2011(161, m_initialized);
    assert_tag_debug_untracked_jul_11_2011(162, !m_finalized);

    long node_index = datum_new(m_nodes);
    dassert_tag_debug_untracked_jul_11_2011(165, node_index != NONE, "overflowed k_maximum_lock_nodes");

    s_lock_node * node = node_get(node_index);
    node->object_id = object_id;
    node->name = name;
    node->first_parent_link.set_all(NONE);
    node->first_child_link.set_all(NONE);
    node->prerequisite_count = 0;

    return node_index;
};

void c_lock_hierarchy::declare_blocking_dependency(long parent_node_index, long child_node_index)
{
    mangled_ppc("?declare_blocking_dependency@c_lock_hierarchy@@QAAXJJ@Z");

    long link_index = find_or_add_link(parent_node_index, child_node_index, _lock_link_type_blocking);
    s_lock_link const * link = link_get_const(link_index);
    c_path_finder path_finder;

    assert_tag_debug_untracked_jul_11_2011(196, link->parent_node_index==parent_node_index);
    assert_tag_debug_untracked_jul_11_2011(197, link->child_node_index==child_node_index);

    path_finder.reset();
    path_finder.find_cycles(this, link->parent_node_index);
};

c_path_finder::c_path_finder(void)
{
    mangled_ppc("??0c_path_finder@@QAA@XZ");
};

void c_lock_hierarchy::declare_optional_dependency(long parent_node_index, long child_node_index)
{
    mangled_ppc("?declare_optional_dependency@c_lock_hierarchy@@QAAXJJ@Z");

    find_or_add_link(parent_node_index, child_node_index, _lock_link_type_optional);
};

void c_lock_hierarchy::declare_reverse_dependency(long parent_node_index, long child_node_index)
{
    mangled_ppc("?declare_reverse_dependency@c_lock_hierarchy@@QAAXJJ@Z");

    find_or_add_link(parent_node_index, child_node_index, _lock_link_type_reverse);
};

void c_lock_hierarchy::finalize(void)
{
    mangled_ppc("?finalize@c_lock_hierarchy@@QAAXXZ");

    assert_tag_debug_untracked_jul_11_2011(230, m_initialized);
    assert_tag_debug_untracked_jul_11_2011(231, !m_finalized);

    validate();

    c_path_finder path_finder;
    path_finder.reset();

    {
        c_data_iterator<s_lock_node> iterator;
        iterator.begin(m_nodes);
        while (iterator.next())
        {
            long node_index = iterator.get_index();
            if (!path_finder.visited_node(node_index))
            {
                path_finder.find_cycles(this, node_index);
            }
        }
    }

    {
        c_data_iterator<s_lock_node> iterator;
        iterator.begin(m_nodes);
        while (iterator.next())
        {
            build_ancestors_and_descendants_beneath_node(iterator.get_index());
        }
    }

    {
        long link_count;
        do
        {
            link_count = data_get_count(m_links);

            c_data_iterator<s_lock_node> iterator;
            iterator.begin(m_nodes);
            while (iterator.next())
            {
                long node_index = iterator.get_index();
                s_lock_node const * node = iterator.get_datum();
                long link_index;
                long next_link_index;
                for (link_index = node->first_child_link[_lock_link_type_reverse]; link_index != NONE; link_index = next_link_index)
                {
                    s_lock_link const * link = link_get_const(link_index);
                    add_reverse_dependency(node_index, link->child_node_index);
                    next_link_index = link->next_child_link;
                }
            }
        } while (data_get_count(m_links) != link_count);
    }

    {
        c_data_iterator<s_lock_node> iterator;
        iterator.begin(m_nodes);
        while (iterator.next())
        {
            validate_prerequisite_chain(iterator.get_index());
        }
    }

    m_finalized = true;
};

void c_lock_hierarchy::dispose(void)
{
    mangled_ppc("?dispose@c_lock_hierarchy@@QAAXXZ");

    if (m_initialized)
    {
        m_initialized = false;

        data_dispose(m_nodes, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 324);
        m_nodes = NULL;

        data_dispose(m_links, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 327);
        m_links = NULL;
    }
};

e_lock_relationship c_lock_hierarchy::query_blocking_relationship(long node_a_index, long node_b_index, long maximum_chain_length, long * out_chain_node_indices, unsigned long * out_chain_object_ids, long * out_chain_length) const
{
    mangled_ppc("?query_blocking_relationship@c_lock_hierarchy@@QBA?AW4e_lock_relationship@@JJJPAJPAK0@Z");

    s_lock_node const * node_a = node_get_const(node_a_index);
    s_lock_node const * node_b = node_get_const(node_b_index);
    long node_a_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(node_a_index);
    long node_b_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(node_b_index);
    e_lock_relationship relationship = _lock_relationship_unrelated;

    if (node_a_index == node_b_index)
    {
        relationship = _lock_relationship_same;
    }
    else if (node_a->descendant_array.test(node_b_absolute_index))
    {
        assert_tag_debug_untracked_jul_11_2011(357, node_b->ancestor_array.test(node_a_absolute_index));

        if (find_link(node_a_index, node_b_index, _lock_link_type_blocking) != NONE)
        {
            relationship = _lock_relationship_parent;
        }
        else
        {
            relationship = _lock_relationship_ancestor;
        }
    }
    else if (node_a->ancestor_array.test(node_b_absolute_index))
    {
        assert_tag_debug_untracked_jul_11_2011(370, node_b->descendant_array.test(node_a_absolute_index));

        if (find_link(node_b_index, node_a_index, _lock_link_type_blocking) != NONE)
        {
            relationship = _lock_relationship_child;
        }
        else
        {
            relationship = _lock_relationship_descendant;
        }
    }
    else
    {
        long watermark = data_get_watermark(m_nodes);
        bool common_ancestor = false;
        bool common_descendant = false;
        for (long absolute_index = 0; absolute_index < watermark; absolute_index++)
        {
            if (node_a->ancestor_array.test(absolute_index) && node_b->ancestor_array.test(absolute_index))
            {
                common_ancestor = true;
            }
            else if (node_a->descendant_array.test(absolute_index) && node_b->descendant_array.test(absolute_index))
            {
                common_descendant = true;
            }
        }

        if (common_descendant)
        {
            relationship = _lock_relationship_common_descendant;
        }
        else if (common_ancestor)
        {
            relationship = _lock_relationship_common_ancestor;
        }
    }

    if (maximum_chain_length > 0)
    {
        long chain_length = 0;
        s_static_array<long, k_maximum_lock_nodes> chain_node_indices;
        c_path_finder traversal;
        bool path_found = false;

        switch (relationship)
        {
        case _lock_relationship_parent:
        {
            chain_length = 2;
            chain_node_indices[0] = node_a_index;
            chain_node_indices[1] = node_b_index;
        }
        break;
        case _lock_relationship_ancestor:
        {
            path_found = traversal.find_path(this, node_a_index, node_b_index, chain_node_indices.get_count(), &chain_length, chain_node_indices.get_elements());
            assert_tag_debug_untracked_jul_11_2011(432, path_found);
            assert_tag_debug_untracked_jul_11_2011(433, chain_length>=2);
            assert_tag_debug_untracked_jul_11_2011(434, chain_node_indices[0]==node_a_index);
            assert_tag_debug_untracked_jul_11_2011(435, chain_node_indices[chain_length-1]==node_b_index);
        }
        break;
        case _lock_relationship_child:
        {
            chain_length = 2;
            chain_node_indices[0] = node_b_index;
            chain_node_indices[1] = node_a_index;
        }
        break;
        case _lock_relationship_descendant:
        {
            path_found = traversal.find_path(this, node_b_index, node_a_index, chain_node_indices.get_count(), &chain_length, chain_node_indices.get_elements());
            assert_tag_debug_untracked_jul_11_2011(446, path_found);
            assert_tag_debug_untracked_jul_11_2011(447, chain_length>=2);
            assert_tag_debug_untracked_jul_11_2011(448, chain_node_indices[0]==node_b_index);
            assert_tag_debug_untracked_jul_11_2011(449, chain_node_indices[chain_length-1]==node_a_index);
        }
        break;
        }

        assert_tag_debug_untracked_jul_11_2011(459, maximum_chain_length>=chain_length);
        assert_tag_debug_untracked_jul_11_2011(460, out_chain_node_indices);
        assert_tag_debug_untracked_jul_11_2011(461, out_chain_object_ids);
        assert_tag_debug_untracked_jul_11_2011(462, out_chain_length);

        *out_chain_length = chain_length;
        for (long chain_index = 0; chain_index < chain_length; chain_index++)
        {
            long chain_node_index = chain_node_indices[chain_index];
            s_lock_node const * chain_node = node_get_const(chain_node_index);
            out_chain_node_indices[chain_index] = chain_node_index;
            out_chain_object_ids[chain_index] = chain_node->object_id;
        }
    }

    return relationship;
};

bool c_lock_hierarchy::query_optional_dependency(long parent_node_index, long child_node_index) const
{
    mangled_ppc("?query_optional_dependency@c_lock_hierarchy@@QBA_NJJ@Z");

    long link_index = find_link(parent_node_index, child_node_index, _lock_link_type_optional);
    return link_index != NONE;
};

bool c_lock_hierarchy::query_reverse_dependency(long parent_node_index, long child_node_index) const
{
    mangled_ppc("?query_reverse_dependency@c_lock_hierarchy@@QBA_NJJ@Z");

    long link_index = find_link(parent_node_index, child_node_index, _lock_link_type_reverse);
    return link_index != NONE;
};

long c_lock_hierarchy::query_prerequisites(long node_index, long maximum_prerequisites, long * out_prerequisite_node_indices, unsigned long * out_prerequisite_object_ids) const
{
    mangled_ppc("?query_prerequisites@c_lock_hierarchy@@QBAJJJPAJPAK@Z");

    s_lock_node const * node = node_get_const(node_index);
    assert_tag_debug_untracked_jul_11_2011(507, maximum_prerequisites>=k_maximum_lock_prerequisites);

    if (node->prerequisite_count > 0)
    {
        if (out_prerequisite_node_indices)
        {
            csmemcpy(out_prerequisite_node_indices, node->prerequisite_node_indices.get_elements(), node->prerequisite_count * node->prerequisite_node_indices.get_element_size());
        }

        if (out_prerequisite_object_ids)
        {
            csmemcpy(out_prerequisite_object_ids, node->prerequisite_object_ids.get_elements(), node->prerequisite_count * node->prerequisite_object_ids.get_element_size());
        }
    }

    return node->prerequisite_count;
};

long c_lock_hierarchy::query_optional_acquisition(long node_index, long context_node_count, long const * context_node_indices, long maximum_requirements, long * out_requirement_node_indices, unsigned long * out_requirement_object_ids) const
{
    mangled_ppc("?query_optional_acquisition@c_lock_hierarchy@@QBAJJJPBJJPAJPAK@Z");

    s_lock_node const * node = node_get_const(node_index);
    long node_count = 0;

    assert_tag_debug_untracked_jul_11_2011(552, context_node_count==0 || context_node_indices!=NULL);
    assert_tag_debug_untracked_jul_11_2011(553, maximum_requirements>0);
    assert_tag_debug_untracked_jul_11_2011(554, out_requirement_node_indices);
    assert_tag_debug_untracked_jul_11_2011(555, out_requirement_object_ids);

    node_count = query_prerequisites(node_index, maximum_requirements, out_requirement_node_indices, out_requirement_object_ids);
    assert_tag_debug_untracked_jul_11_2011(561, node_count<maximum_requirements);

    out_requirement_node_indices[node_count] = node_index;
    out_requirement_object_ids[node_count] = node->object_id;

    node_count++;

    return node_count;
};

void c_lock_hierarchy::dump_as_text(c_simple_file * file) const
{
    mangled_ppc("?dump_as_text@c_lock_hierarchy@@QBAXPAVc_simple_file@@@Z");

    c_hierarchy_dumper dumper;
    dumper.dump(c_hierarchy_dumper::_dump_type_text, this, file);
};

c_hierarchy_dumper::c_hierarchy_dumper(void)
{
    mangled_ppc("??0c_hierarchy_dumper@@QAA@XZ");
};

void c_lock_hierarchy::dump_as_graphviz(c_simple_file * file) const
{
    mangled_ppc("?dump_as_graphviz@c_lock_hierarchy@@QBAXPAVc_simple_file@@@Z");

    c_hierarchy_dumper dumper;
    dumper.dump(c_hierarchy_dumper::_dump_type_graphviz, this, file);
};

s_lock_node * c_lock_hierarchy::node_get(long node_index)
{
    mangled_ppc("?node_get@c_lock_hierarchy@@QAAPAUs_lock_node@@J@Z");

    return &static_cast<s_lock_node *>(*static_cast<void **>(offset_pointer(m_nodes, OFFSETOF(s_data_array, data))))[DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index)];
};

s_lock_link * c_lock_hierarchy::link_get(long link_index)
{
    mangled_ppc("?link_get@c_lock_hierarchy@@QAAPAUs_lock_link@@J@Z");

    return &static_cast<s_lock_link *>(*static_cast<void **>(offset_pointer(m_links, OFFSETOF(s_data_array, data))))[DATUM_INDEX_TO_ABSOLUTE_INDEX(link_index)];
};

s_lock_node const * c_lock_hierarchy::node_get_const(long node_index) const
{
    mangled_ppc("?node_get_const@c_lock_hierarchy@@QBAPBUs_lock_node@@J@Z");

    return &static_cast<s_lock_node const *>(*static_cast<void **>(offset_pointer(m_nodes, OFFSETOF(s_data_array, data))))[DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index)];
};

s_lock_link const * c_lock_hierarchy::link_get_const(long link_index) const
{
    mangled_ppc("?link_get_const@c_lock_hierarchy@@QBAPBUs_lock_link@@J@Z");

    return &static_cast<s_lock_link const *>(*static_cast<void **>(offset_pointer(m_links, OFFSETOF(s_data_array, data))))[DATUM_INDEX_TO_ABSOLUTE_INDEX(link_index)];
};

s_data_array const * c_lock_hierarchy::node_array_get_const(void) const
{
    mangled_ppc("?node_array_get_const@c_lock_hierarchy@@QBAPBUs_data_array@@XZ");

    return m_nodes;
};

void c_lock_hierarchy::validate(void) const
{
    mangled_ppc("?validate@c_lock_hierarchy@@ABAXXZ");

    s_static_bitarray<k_maximum_lock_links> visited_links_from_parent;
    s_static_bitarray<k_maximum_lock_links> visited_links_from_child;
    visited_links_from_parent.clear();
    visited_links_from_child.clear();

    {
        c_data_iterator<s_lock_node> iterator;
        iterator.begin(m_nodes);
        while (iterator.next())
        {
            s_lock_node const * node = iterator.get_datum();
            assert_tag_debug_untracked_jul_11_2011(646, node->object_id!=NONE);

            for (e_lock_link_type link_type = _lock_link_type_blocking; link_type < k_lock_link_type_count; link_type++)
            {
                long link_index;
                long next_link_index;
                for (link_index = node->first_parent_link[link_type]; link_index != NONE; link_index = next_link_index)
                {
                    s_lock_link const * link = link_get_const(link_index);
                    long link_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(link_index);
                    assert_tag_debug_untracked_jul_11_2011(658, link->child_node_index==iterator.get_index());
                    assert_tag_debug_untracked_jul_11_2011(659, !visited_links_from_child.test(link_absolute_index));
                    visited_links_from_child.set(link_absolute_index, true);
                    next_link_index = link->next_parent_link;
                }

                for (link_index = node->first_child_link[link_type]; link_index != NONE; link_index = next_link_index)
                {
                    s_lock_link const * link = link_get_const(link_index);
                    long link_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(link_index);
                    assert_tag_debug_untracked_jul_11_2011(671, link->parent_node_index==iterator.get_index());
                    assert_tag_debug_untracked_jul_11_2011(672, !visited_links_from_parent.test(link_absolute_index));
                    visited_links_from_parent.set(link_absolute_index, true);
                    next_link_index = link->next_child_link;
                }
            }
        }
    }

    {
        c_data_iterator<s_lock_link> iterator;
        iterator.begin(m_links);
        while (iterator.next())
        {
            long link_absolute_index = iterator.get_absolute_index();
            assert_tag_debug_untracked_jul_11_2011(690, visited_links_from_parent.test(link_absolute_index));
            assert_tag_debug_untracked_jul_11_2011(691, visited_links_from_child.test(link_absolute_index));
        }
    }
};

e_lock_link_type operator++(e_lock_link_type & link_type, int)
{
    mangled_ppc("??E@YA?AW4e_lock_link_type@@AAW40@H@Z");

    e_lock_link_type result = link_type;
    link_type = static_cast<e_lock_link_type>(link_type + 1);
    return result;
};

void c_lock_hierarchy::validate_prerequisite_chain(long node_index) const
{
    mangled_ppc("?validate_prerequisite_chain@c_lock_hierarchy@@ABAXJ@Z");

    s_lock_node const * node = node_get_const(node_index);
    s_static_array<s_lock_node const *, k_maximum_lock_prerequisites> prerequisite_nodes;
    s_static_array<long, k_maximum_lock_prerequisites> prerequisite_absolute_indices;

    assert_tag_debug_untracked_jul_11_2011(705, VALID_COUNT(node->prerequisite_count, node->prerequisite_node_indices.get_count()));

    for (long prerequisite_index = 0; prerequisite_index < node->prerequisite_count; prerequisite_index++)
    {
        prerequisite_nodes[prerequisite_index] = node_get_const(node->prerequisite_node_indices[prerequisite_index]);
        prerequisite_absolute_indices[prerequisite_index] = DATUM_INDEX_TO_ABSOLUTE_INDEX(node->prerequisite_node_indices[prerequisite_index]);
        assert_tag_debug_untracked_jul_11_2011(712, node->prerequisite_object_ids[prerequisite_index]==prerequisite_nodes[prerequisite_index]->object_id);
    }

    for (long prerequisite_index = 0; prerequisite_index < node->prerequisite_count; prerequisite_index++)
    {
        for (long following_index = prerequisite_index + 1; following_index < node->prerequisite_count; following_index++)
        {
            assert_tag_debug_untracked_jul_11_2011(721, prerequisite_nodes[following_index]!=prerequisite_nodes[prerequisite_index]);
            assert_tag_debug_untracked_jul_11_2011(724, !prerequisite_nodes[prerequisite_index]->ancestor_array.test(prerequisite_absolute_indices[following_index]));
            assert_tag_debug_untracked_jul_11_2011(725, !prerequisite_nodes[following_index]->descendant_array.test(prerequisite_absolute_indices[prerequisite_index]));
        }
    }
};

long c_lock_hierarchy::find_link(long parent_node_index, long child_node_index, e_lock_link_type link_type) const
{
    mangled_ppc("?find_link@c_lock_hierarchy@@ABAJJJW4e_lock_link_type@@@Z");

    s_lock_node const * parent_node = node_get_const(parent_node_index);
    long link_index;
    long next_link_index;
    for (link_index = parent_node->first_child_link[link_type]; link_index != NONE; link_index = next_link_index)
    {
        s_lock_link const * link = link_get_const(link_index);
        assert_tag_debug_untracked_jul_11_2011(747, link->parent_node_index==parent_node_index);

        if (link->child_node_index == child_node_index)
        {
            break;
        }

        next_link_index = link->next_child_link;
    }

    return link_index;
};

long c_lock_hierarchy::find_or_add_link(long parent_node_index, long child_node_index, e_lock_link_type link_type)
{
    mangled_ppc("?find_or_add_link@c_lock_hierarchy@@AAAJJJW4e_lock_link_type@@@Z");

    long link_index = find_link(parent_node_index, child_node_index, link_type);
    if (link_index == NONE)
    {
        s_lock_node * parent_node = node_get(parent_node_index);
        s_lock_node * child_node = node_get(child_node_index);

        link_index = datum_new(m_links);
        dassert_tag_debug_untracked_jul_11_2011(777, link_index != NONE, "overflowed k_maximum_lock_links");

        s_lock_link * link = link_get(link_index);
        link->parent_node_index = parent_node_index;
        link->child_node_index = child_node_index;
        link->next_child_link = parent_node->first_child_link[link_type];
        parent_node->first_child_link[link_type] = link_index;
        link->next_parent_link = child_node->first_parent_link[link_type];
        child_node->first_parent_link[link_type] = link_index;

        validate();
    }

    return link_index;
};

void c_lock_hierarchy::build_ancestors_and_descendants_beneath_node(long node_index)
{
    mangled_ppc("?build_ancestors_and_descendants_beneath_node@c_lock_hierarchy@@AAAXJ@Z");

    long node_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index);
    s_lock_node * node = node_get(node_index);
    c_path_finder path_finder;
    s_static_bitarray<k_maximum_lock_nodes> const * children = path_finder.find_children(this, node_index);

    for (long child_absolute_index = 0; child_absolute_index < data_get_watermark(m_nodes); child_absolute_index++)
    {
        if (children->test(child_absolute_index) && child_absolute_index != node_absolute_index)
        {
            s_lock_node * child_node = static_cast<s_lock_node *>(datum_get_absolute(m_nodes, child_absolute_index));
            assert_tag_debug_untracked_jul_11_2011(817, !node->ancestor_array.test(child_absolute_index));
            assert_tag_debug_untracked_jul_11_2011(818, !child_node->descendant_array.test(node_absolute_index));
            node->descendant_array.set(child_absolute_index, true);
            child_node->ancestor_array.set(node_absolute_index, true);
        }
    }
};

void c_lock_hierarchy::add_reverse_dependency(long parent_node_index, long child_node_index)
{
    mangled_ppc("?add_reverse_dependency@c_lock_hierarchy@@AAAXJJ@Z");

    s_lock_node const * parent_node = node_get(parent_node_index);
    s_lock_node * target_lock_node = node_get(child_node_index);
    long child_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(child_node_index);

    vassert_tag_debug_untracked_jul_11_2011(852, !parent_node->descendant_array.test(child_absolute_index), "reverse dependency from %s to %s is illegal because it is our child", parent_node->name, target_lock_node->name);
    vassert_tag_debug_untracked_jul_11_2011(853, parent_node->ancestor_array.test(child_absolute_index), "reverse dependency from %s to %s is illegal because it is not our ancestor", parent_node->name, target_lock_node->name);

    c_static_stack<long, 128> stack;
    stack.clear();
    add_ancestor_prerequisites(child_node_index, parent_node_index, &stack);

    for (long prerequisite_index = 0; prerequisite_index < parent_node->prerequisite_count; prerequisite_index++)
    {
        add_prerequisite_dependencies(parent_node->prerequisite_node_indices[prerequisite_index]);
    }

    add_prerequisite_dependencies(parent_node_index);
};

// $TODO nonmatching (stack slot order of node/stack_node_index/following_link_index)
void c_lock_hierarchy::add_ancestor_prerequisites(long node_index, long target_node_index, c_static_stack<long, 128> * stack)
{
    mangled_ppc("?add_ancestor_prerequisites@c_lock_hierarchy@@AAAXJJPAV?$c_static_stack@J$0IA@@@@Z");

    s_lock_node * parent_node = node_get(node_index);
    long element_index;
    long stack_node_index;

    for (element_index = 0; element_index < stack->count(); element_index++)
    {
        stack_node_index = stack->get_element(element_index);
        assert_tag_debug_untracked_jul_11_2011(890, parent_node->ancestor_array.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(stack_node_index)));
        add_prerequisite(node_index, stack_node_index);
    }

    long target_node_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(target_node_index);
    stack->push_back(node_index);

    long link_index;
    long following_link_index;
    for (link_index = parent_node->first_child_link[_lock_link_type_blocking]; link_index != NONE; link_index = following_link_index)
    {
        s_lock_link const * link = link_get_const(link_index);
        s_lock_node * child_node = node_get(link->child_node_index);
        if (link->child_node_index == target_node_index || child_node->descendant_array.test(target_node_absolute_index))
        {
            add_ancestor_prerequisites(link->child_node_index, target_node_index, stack);
        }
        following_link_index = link->next_child_link;
    }

    stack->pop();
};

void c_lock_hierarchy::add_prerequisite(long node_index, long ancestor_node_index)
{
    mangled_ppc("?add_prerequisite@c_lock_hierarchy@@AAAXJJ@Z");

    s_lock_node * node = node_get(node_index);
    s_lock_node * ancestor_node = node_get(ancestor_node_index);
    long ancestor_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(ancestor_node_index);
    long insert_index = 0;
    bool found = false;

    assert_tag_debug_untracked_jul_11_2011(932, node->ancestor_array.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(ancestor_node_index)));

    validate_prerequisite_chain(node_index);

    for (long prerequisite_index = 0; prerequisite_index < node->prerequisite_count; prerequisite_index++)
    {
        long child_node_index = node->prerequisite_node_indices[prerequisite_index];
        long prerequisite_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(child_node_index);

        if (child_node_index == ancestor_node_index)
        {
            found = true;
            break;
        }
        else if (ancestor_node->ancestor_array.test(prerequisite_absolute_index))
        {
            insert_index = prerequisite_index + 1;
        }
        else if (node_get(child_node_index)->ancestor_array.test(ancestor_absolute_index))
        {
            break;
        }
        else if (ancestor_absolute_index > prerequisite_absolute_index)
        {
            insert_index = prerequisite_index + 1;
        }
        else
        {
            break;
        }
    }

    if (!found)
    {
        vassert_tag_debug_untracked_jul_11_2011(979, node->prerequisite_count < node->prerequisite_node_indices.get_count(), "%s overflowed k_maximum_lock_prerequisites", node->name);
        assert_tag_debug_untracked_jul_11_2011(980, node->prerequisite_node_indices.valid(insert_index));

        if (insert_index < node->prerequisite_count)
        {
            csmemmove(&node->prerequisite_node_indices[insert_index + 1], &node->prerequisite_node_indices[insert_index], (node->prerequisite_count - insert_index) * node->prerequisite_node_indices.get_element_size());
            csmemmove(&node->prerequisite_object_ids[insert_index + 1], &node->prerequisite_object_ids[insert_index], (node->prerequisite_count - insert_index) * node->prerequisite_object_ids.get_element_size());
        }

        node->prerequisite_node_indices[insert_index] = ancestor_node_index;
        node->prerequisite_object_ids[insert_index] = ancestor_node->object_id;
        node->prerequisite_count++;
    }

    validate_prerequisite_chain(node_index);
};

void c_lock_hierarchy::add_prerequisite_dependencies(long node_index)
{
    mangled_ppc("?add_prerequisite_dependencies@c_lock_hierarchy@@AAAXJ@Z");

    s_lock_node const * node = node_get(node_index);
    if (node->prerequisite_count > 0)
    {
        for (long prerequisite_index = 0; prerequisite_index < node->prerequisite_count; prerequisite_index++)
        {
            for (long following_index = prerequisite_index + 1; following_index < node->prerequisite_count; following_index++)
            {
                declare_prerequisite_dependency(node->prerequisite_node_indices[prerequisite_index], node->prerequisite_node_indices[following_index], node_index);
            }
        }

        declare_prerequisite_dependency(node->prerequisite_node_indices[node->prerequisite_count - 1], node_index, node_index);
        build_ancestors_and_descendants_beneath_node(node->prerequisite_node_indices[0]);

        long link_index;
        long next_link_index;
        for (link_index = node->first_parent_link[_lock_link_type_blocking]; link_index != NONE; link_index = next_link_index)
        {
            s_lock_link const * link = link_get_const(link_index);
            bool found = false;
            for (long prerequisite_index = 0; prerequisite_index < node->prerequisite_count; prerequisite_index++)
            {
                if (node->prerequisite_node_indices[prerequisite_index] == link->parent_node_index)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                declare_prerequisite_dependency(link->parent_node_index, node->prerequisite_node_indices[0], node_index);
                build_ancestors_and_descendants_beneath_node(link->parent_node_index);
            }

            next_link_index = link->next_parent_link;
        }
    }
};

void c_lock_hierarchy::declare_prerequisite_dependency(long parent_node_index, long child_node_index, long owner_node_index)
{
    mangled_ppc("?declare_prerequisite_dependency@c_lock_hierarchy@@AAAXJJJ@Z");

    s_lock_node * parent_node = node_get(parent_node_index);
    s_lock_node * child_node = node_get(child_node_index);
    s_lock_node * owner_node = node_get(owner_node_index);

    vassert_tag_debug_untracked_jul_11_2011(1077, !(parent_node->ancestor_array.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(child_node_index)) || child_node->descendant_array.test(DATUM_INDEX_TO_ABSOLUTE_INDEX(parent_node_index))), "created a cyclic dependency while creating prerequisites for %s. (cycle includes %s and %s)", owner_node->name, parent_node->name, child_node->name);

    declare_blocking_dependency(parent_node_index, child_node_index);
};

void c_path_finder::reset(void)
{
    mangled_ppc("?reset@c_path_finder@@QAAXXZ");

    m_visited_nodes.clear();
    m_active_nodes.clear();
    m_stack.clear();
};

bool c_path_finder::visited_node(long node_index) const
{
    mangled_ppc("?visited_node@c_path_finder@@QBA_NJ@Z");

    return m_visited_nodes[DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index)];
};

void c_path_finder::find_cycles(c_lock_hierarchy const * hierarchy, long node_index)
{
    mangled_ppc("?find_cycles@c_path_finder@@QAAXPBVc_lock_hierarchy@@J@Z");

    m_active_nodes.clear();
    m_stack.clear();
    recurse(hierarchy, node_index, NONE, 0, NULL, NULL);
    assert_tag_debug_untracked_jul_11_2011(1108, m_stack.count()==0);
};

s_static_bitarray<k_maximum_lock_nodes> const * c_path_finder::find_children(c_lock_hierarchy const * hierarchy, long node_index)
{
    mangled_ppc("?find_children@c_path_finder@@QAAPBV?$s_static_bitarray@$0IA@@@PBVc_lock_hierarchy@@J@Z");

    reset();
    recurse(hierarchy, node_index, NONE, 0, NULL, NULL);
    return &m_visited_nodes;
};

bool c_path_finder::find_path(c_lock_hierarchy const * hierarchy, long start_node_index, long goal_node_index, long maximum_path_length, long * out_path_length, long * out_path_indices)
{
    mangled_ppc("?find_path@c_path_finder@@QAA_NPBVc_lock_hierarchy@@JJJPAJ1@Z");

    bool path_found = false;

    assert_tag_debug_untracked_jul_11_2011(1132, maximum_path_length>0);
    assert_tag_debug_untracked_jul_11_2011(1133, out_path_length);
    assert_tag_debug_untracked_jul_11_2011(1134, out_path_indices);

    reset();
    recurse(hierarchy, start_node_index, goal_node_index, maximum_path_length, out_path_length, out_path_indices);
    assert_tag_debug_untracked_jul_11_2011(1138, m_stack.count()==0);

    if (*out_path_length > 0)
    {
        assert_tag_debug_untracked_jul_11_2011(1142, out_path_indices[0]==start_node_index);
        assert_tag_debug_untracked_jul_11_2011(1143, out_path_indices[*out_path_length-1]==goal_node_index);
        path_found = true;
    }

    return path_found;
};

void c_path_finder::recurse(c_lock_hierarchy const * hierarchy, long node_index, long goal_node_index, long maximum_path_length, long * out_path_length, long * out_path_indices)
{
    mangled_ppc("?recurse@c_path_finder@@AAAXPBVc_lock_hierarchy@@JJJPAJ1@Z");

    long node_absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index);
    s_lock_node const * node = hierarchy->node_get_const(node_index);

    if (m_active_nodes[node_absolute_index])
    {
        s_static_string<1024> loop_string;
        loop_string.print("loop is: ");
        for (long stack_index = 0; stack_index < m_stack.count(); stack_index++)
        {
            s_lock_node const * stack_node = hierarchy->node_get_const(m_stack[stack_index]);
            loop_string.append_print("%s%s", stack_index == 0 ? "" : "->", stack_node->name);
        }
        loop_string.append_print("->%s", node->name);

        vassert_tag_debug_untracked_jul_11_2011(1175, false, "loop detected in lock hierarchy (%s)", loop_string.get_string());
    }

    if (!m_visited_nodes[node_absolute_index])
    {
        m_stack.push_back(node_index);
        m_active_nodes.set(node_absolute_index, true);
        m_visited_nodes.set(node_absolute_index, true);

        if (node_index == goal_node_index)
        {
            long path_length = int_min(m_stack.count(), maximum_path_length);

            assert_tag_debug_untracked_jul_11_2011(1193, out_path_length);
            assert_tag_debug_untracked_jul_11_2011(1194, out_path_indices);
            dassert_tag_debug_untracked_jul_11_2011(1195, m_stack.count() <= maximum_path_length, "c_path_finder::recurse: returning truncated path");

            if (*out_path_length == 0 || path_length < *out_path_length)
            {
                *out_path_length = path_length;
                csmemcpy(out_path_indices, m_stack.get_elements(), path_length * sizeof(long));
            }
        }

        long link_index;
        long next_link_index;
        for (link_index = node->first_child_link[_lock_link_type_blocking]; link_index != NONE; link_index = next_link_index)
        {
            s_lock_link const * link = hierarchy->link_get_const(link_index);
            recurse(hierarchy, link->child_node_index, goal_node_index, maximum_path_length, out_path_length, out_path_indices);
            next_link_index = link->next_child_link;
        }

        m_stack.pop();
        m_active_nodes.set(node_absolute_index, false);
    }
};

void c_hierarchy_dumper::dump(e_dump_type dump_type, c_lock_hierarchy const * hierarchy, c_simple_file * file)
{
    mangled_ppc("?dump@c_hierarchy_dumper@@QAAXW4e_dump_type@1@PBVc_lock_hierarchy@@PAVc_simple_file@@@Z");

    assert_tag_debug_untracked_jul_11_2011(1226, VALID_INDEX(dump_type, k_dump_type_count));

    m_visited_nodes.clear();
    m_stack.clear();

    switch (dump_type)
    {
    case _dump_type_text:
        file->print("LOCK HIERARCHY DUMP\r\n");
        file->print("===================\r\n\r\n");
        file->print("each node is traversed only once, subsequent hits just print (depth/count)\r\n\r\n");
        break;
    case _dump_type_graphviz:
        file->print("digraph lock_hierarchy\r\n");
        file->print("{\r\n");
        break;
    }

    c_data_iterator_const<s_lock_node> iterator;
    iterator.begin(hierarchy->node_array_get_const());
    while (iterator.next())
    {
        long node_absolute_index = iterator.get_absolute_index();
        long node_index = iterator.get_index();
        s_lock_node const * node = iterator.get_datum();

        if (node->first_parent_link[_lock_link_type_blocking] == NONE)
        {
            assert_tag_debug_untracked_jul_11_2011(1258, !m_visited_nodes[node_absolute_index]);
            recurse(dump_type, hierarchy, node_index, file, NULL, NULL);
            file->print("\r\n");
        }
    }

    iterator.begin(hierarchy->node_array_get_const());
    while (iterator.next())
    {
        assert_tag_debug_untracked_jul_11_2011(1268, m_visited_nodes[iterator.get_absolute_index()]);
    }

    if (dump_type == _dump_type_graphviz)
    {
        file->print("}\r\n");
    }
};

void c_hierarchy_dumper::recurse(e_dump_type dump_type, c_lock_hierarchy const * hierarchy, long node_index, c_simple_file * file, long * out_depth, long * out_count)
{
    mangled_ppc("?recurse@c_hierarchy_dumper@@AAAXW4e_dump_type@1@PBVc_lock_hierarchy@@JPAVc_simple_file@@PAJ3@Z");

    long absolute_index = DATUM_INDEX_TO_ABSOLUTE_INDEX(node_index);
    s_lock_node const * node = hierarchy->node_get_const(node_index);
    s_lock_node const * parent = m_stack.empty() ? NULL : hierarchy->node_get_const(m_stack[m_stack.top()]);
    long deepest = 1;
    long descendant_count = 1;

    file->printf("%*s", 4 * m_stack.count(), "");

    if (m_visited_nodes[absolute_index])
    {
        deepest = m_node_depths[absolute_index];
        descendant_count = m_node_counts[absolute_index];

        switch (dump_type)
        {
        case _dump_type_text:
            file->printf("%s... (%d/%d)\r\n", node->name, deepest, descendant_count);
            break;
        case _dump_type_graphviz:
            assert_tag_debug_untracked_jul_11_2011(1307, parent);
            file->printf("\"%s\" -> \"%s\";\r\n", parent->name, node->name);
            break;
        }
    }
    else
    {
        m_stack.push_back(node_index);
        m_visited_nodes.set(absolute_index, true);

        switch (dump_type)
        {
        case _dump_type_text:
            file->printf("%s\r\n", node->name);
            break;
        case _dump_type_graphviz:
            file->printf("\"%s\";", node->name);
            if (parent)
            {
                file->printf(" \"%s\" -> \"%s\";", parent->name, node->name);
            }
            file->print("\r\n");
            break;
        }

        long link_index;
        long next_link_index;
        for (link_index = node->first_child_link[_lock_link_type_blocking]; link_index != NONE; link_index = next_link_index)
        {
            s_lock_link const * link = hierarchy->link_get_const(link_index);
            long child_depth;
            long child_count;
            recurse(dump_type, hierarchy, link->child_node_index, file, &child_depth, &child_count);
            deepest = int_max(deepest, child_depth + 1);
            descendant_count += child_count;
            next_link_index = link->next_child_link;
        }

        m_node_depths[absolute_index] = deepest;
        m_node_counts[absolute_index] = descendant_count;
        m_stack.pop();
    }

    if (out_depth)
    {
        *out_depth = deepest;
    }
    if (out_count)
    {
        *out_count = descendant_count;
    }
};

