#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\SD\Reach\Publishing\Main\shared\engine\source\foundation\baselib\multithreading\synchronization\virtual_guard_block.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\synchronization\virtual_guard_block.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\multithreading\synchronization\lock_tracker.h"
#include "foundation\baselib\multithreading\synchronization\synchronization_manager.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_virtual_guard_block const k_virtual_guard_block_invalid = { k_synchronization_object_id_invalid };

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_virtual_guard_block const k_virtual_guard_block_invalid; // "?k_virtual_guard_block_invalid@@3Us_virtual_guard_block@@B"

// struct s_virtual_guard_block virtual_guard_block_declare(long, struct s_virtual_guard_block_definition const *);
// void virtual_guard_block_enter(struct s_virtual_guard_block);
// void virtual_guard_block_leave(struct s_virtual_guard_block);
// void virtual_guard_block_create(class c_synchronization_object *, unsigned long, long, struct s_virtual_guard_block_definition const *);
// public: void c_synchronization_object::initialize(unsigned long);
// public: void c_synchronization_object::set_lock_node_index(long);
// public: void c_synchronization_object::reset(void);
// void virtual_guard_block_destroy(class c_synchronization_object *);
// public: void s_flags<enum e_synchronization_object_flags, unsigned long, 1>::clear(void);

s_virtual_guard_block virtual_guard_block_declare(long synchronization_group_index, s_virtual_guard_block_definition const * definition)
{
    mangled_ppc("?virtual_guard_block_declare@@YA?AUs_virtual_guard_block@@JPBUs_virtual_guard_block_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(27, definition);
    assert_tag_debug_untracked_jul_11_2011(28, definition->name);

    s_virtual_guard_block guard_block;
    guard_block.object_id = synchronization_declare_virtual_guard_block(synchronization_group_index, definition);
    dassert_tag_debug_untracked_jul_11_2011(31, guard_block.object_id != NONE, "too many virtual guard blocks, increase k_maximum_virtual_guard_blocks");

    return guard_block;
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker (li 0x4C0) differs, it is resolved at link time
void virtual_guard_block_enter(s_virtual_guard_block guard_block)
{
    mangled_ppc("?virtual_guard_block_enter@@YAXUs_virtual_guard_block@@@Z");

    c_synchronization_object * virtual_guard_block_object = synchronization_get_virtual_guard_block(guard_block.object_id);
    g_synchronization_lock_tracker->verify_push(virtual_guard_block_object);
    g_synchronization_lock_tracker->push(virtual_guard_block_object);
};

// $TODO nonmatching: only the TLS offset of g_synchronization_lock_tracker (li 0x4C0) differs, it is resolved at link time
void virtual_guard_block_leave(s_virtual_guard_block guard_block)
{
    mangled_ppc("?virtual_guard_block_leave@@YAXUs_virtual_guard_block@@@Z");

    c_synchronization_object * virtual_guard_block_object = synchronization_get_virtual_guard_block(guard_block.object_id);
    g_synchronization_lock_tracker->pop(virtual_guard_block_object);
};

void virtual_guard_block_create(c_synchronization_object * virtual_guard_block_object, unsigned long object_id, long lock_node_index, s_virtual_guard_block_definition const * definition)
{
    mangled_ppc("?virtual_guard_block_create@@YAXPAVc_synchronization_object@@KJPBUs_virtual_guard_block_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(73, virtual_guard_block_object);
    assert_tag_debug_untracked_jul_11_2011(74, object_id!=k_synchronization_object_id_invalid);
    assert_tag_debug_untracked_jul_11_2011(75, !(SYNCHRONIZATION_OBJECT_GROUP(object_id)==k_synchronization_group_base && lock_node_index==NONE));
    assert_tag_debug_untracked_jul_11_2011(76, definition);
    assert_tag_debug_untracked_jul_11_2011(77, definition->name);

    virtual_guard_block_object->initialize(object_id);
    virtual_guard_block_object->set_lock_node_index(lock_node_index);
};

void virtual_guard_block_destroy(c_synchronization_object * virtual_guard_block_object)
{
    mangled_ppc("?virtual_guard_block_destroy@@YAXPAVc_synchronization_object@@@Z");

    assert_tag_debug_untracked_jul_11_2011(86, virtual_guard_block_object);
};
