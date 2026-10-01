#pragma once
#ifndef __LOCK_HIERARCHY_H__
#define __LOCK_HIERARCHY_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_bitarray.h"
#include "foundation\baselib\datatypes\static_stack.h"

/* ---------- constants */

long const k_maximum_lock_nodes = 128;
long const k_maximum_lock_links = 1024;
long const k_maximum_lock_prerequisites = 8;

enum e_lock_link_type
{
    _lock_link_type_blocking = 0,
    _lock_link_type_optional,
    _lock_link_type_reverse,
    _lock_link_type_prerequisite,

    k_lock_link_type_count
};

enum e_lock_relationship
{
    _lock_relationship_same = 0,
    _lock_relationship_parent,
    _lock_relationship_ancestor,
    _lock_relationship_child,
    _lock_relationship_descendant,
    _lock_relationship_common_descendant,
    _lock_relationship_common_ancestor,
    _lock_relationship_unrelated,

    k_lock_relationship_count
};

/* ---------- definitions */

class c_allocation_interface;
class c_simple_file;

struct s_lock_node
{
    s_datum_header header; // 0x0
    unsigned long object_id; // 0x4
    char const * name; // 0x8
    s_static_array<long, k_lock_link_type_count> first_parent_link; // 0xC (links where this node is the child)
    s_static_array<long, k_lock_link_type_count> first_child_link; // 0x1C (links where this node is the parent)
    s_static_bitarray<k_maximum_lock_nodes> ancestor_array; // 0x2C
    s_static_bitarray<k_maximum_lock_nodes> descendant_array; // 0x3C
    long prerequisite_count; // 0x4C
    s_static_array<long, k_maximum_lock_prerequisites> prerequisite_node_indices; // 0x50
    s_static_array<unsigned long, k_maximum_lock_prerequisites> prerequisite_object_ids; // 0x70
};
static_assert(sizeof(s_lock_node) == 0x90, "s_lock_node");

struct s_lock_link
{
    s_datum_header header; // 0x0
    long parent_node_index; // 0x4
    long child_node_index; // 0x8
    long next_child_link; // 0xC (next link in the parent's first_child_link list)
    long next_parent_link; // 0x10 (next link in the child's first_parent_link list)
};
static_assert(sizeof(s_lock_link) == 0x14, "s_lock_link");

class c_lock_hierarchy
{
public:
    c_lock_hierarchy(void)
    {
        mangled_ppc("??0c_lock_hierarchy@@QAA@XZ");
    };

    ~c_lock_hierarchy(void)
    {
        mangled_ppc("??1c_lock_hierarchy@@QAA@XZ");
    };

    void initialize(c_allocation_interface * allocator);
    long declare_object(unsigned long object_id, char const * name);
    void declare_blocking_dependency(long parent_node_index, long child_node_index);
    void declare_optional_dependency(long parent_node_index, long child_node_index);
    void declare_reverse_dependency(long parent_node_index, long child_node_index);
    void finalize(void);
    void dispose(void);
    e_lock_relationship query_blocking_relationship(long node_a_index, long node_b_index, long maximum_chain_length, long * out_chain_node_indices, unsigned long * out_chain_object_ids, long * out_chain_length) const;
    bool query_optional_dependency(long parent_node_index, long child_node_index) const;
    bool query_reverse_dependency(long parent_node_index, long child_node_index) const;
    long query_prerequisites(long node_index, long maximum_prerequisites, long * out_prerequisite_node_indices, unsigned long * out_prerequisite_object_ids) const;
    long query_optional_acquisition(long node_index, long context_node_count, long const * context_node_indices, long maximum_requirements, long * out_requirement_node_indices, unsigned long * out_requirement_object_ids) const;
    void dump_as_text(c_simple_file * file) const;
    void dump_as_graphviz(c_simple_file * file) const;
    s_lock_node * node_get(long node_index);
    s_lock_link * link_get(long link_index);
    s_lock_node const * node_get_const(long node_index) const;
    s_lock_link const * link_get_const(long link_index) const;
    s_data_array const * node_array_get_const(void) const;

    bool is_finalized(void) const
    {
        mangled_ppc("?is_finalized@c_lock_hierarchy@@QBA_NXZ");

        return m_finalized;
    };

private:
    void validate(void) const;
    void validate_prerequisite_chain(long node_index) const;
    long find_link(long parent_node_index, long child_node_index, e_lock_link_type link_type) const;
    long find_or_add_link(long parent_node_index, long child_node_index, e_lock_link_type link_type);
    void build_ancestors_and_descendants_beneath_node(long node_index);
    void add_reverse_dependency(long parent_node_index, long child_node_index);
    void add_ancestor_prerequisites(long node_index, long target_node_index, c_static_stack<long, 128> * stack);
    void add_prerequisite(long node_index, long ancestor_node_index);
    void add_prerequisite_dependencies(long node_index);
    void declare_prerequisite_dependency(long parent_node_index, long child_node_index, long owner_node_index);

    bool m_initialized; // 0x0
    bool m_finalized; // 0x1
    s_data_array * m_nodes; // 0x4
    s_data_array * m_links; // 0x8
};
static_assert(sizeof(c_lock_hierarchy) == 0xC, "c_lock_hierarchy");

class c_path_finder
{
public:
    c_path_finder(void);

    void reset(void);
    bool visited_node(long node_index) const;
    void find_cycles(c_lock_hierarchy const * hierarchy, long node_index);
    s_static_bitarray<k_maximum_lock_nodes> const * find_children(c_lock_hierarchy const * hierarchy, long node_index);
    bool find_path(c_lock_hierarchy const * hierarchy, long start_node_index, long goal_node_index, long maximum_path_length, long * out_path_length, long * out_path_indices);

private:
    void recurse(c_lock_hierarchy const * hierarchy, long node_index, long goal_node_index, long maximum_path_length, long * out_path_length, long * out_path_indices);

    s_static_bitarray<k_maximum_lock_nodes> m_visited_nodes; // 0x0
    s_static_bitarray<k_maximum_lock_nodes> m_active_nodes; // 0x10
    c_static_stack<long, 128> m_stack; // 0x20
};
static_assert(sizeof(c_path_finder) == 0x224, "c_path_finder");

class c_hierarchy_dumper
{
public:
    enum e_dump_type
    {
        _dump_type_text = 0,
        _dump_type_graphviz,

        k_dump_type_count
    };

    c_hierarchy_dumper(void);

    void dump(e_dump_type dump_type, c_lock_hierarchy const * hierarchy, c_simple_file * file);

private:
    void recurse(e_dump_type dump_type, c_lock_hierarchy const * hierarchy, long node_index, c_simple_file * file, long * out_depth, long * out_count);

    s_static_bitarray<k_maximum_lock_nodes> m_visited_nodes; // 0x0
    s_static_array<long, k_maximum_lock_nodes> m_node_depths; // 0x10
    s_static_array<long, k_maximum_lock_nodes> m_node_counts; // 0x210
    c_static_stack<long, 128> m_stack; // 0x410
};
static_assert(sizeof(c_hierarchy_dumper) == 0x614, "c_hierarchy_dumper");

/* ---------- prototypes */

e_lock_link_type operator++(e_lock_link_type & link_type, int);

/* ---------- globals */

/* ---------- public code */

#endif // __LOCK_HIERARCHY_H__

