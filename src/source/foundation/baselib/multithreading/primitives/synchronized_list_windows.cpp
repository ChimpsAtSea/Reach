#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\multithreading\\primitives\\synchronized_list_windows.cpp"
/* ---------- headers */

#include "foundation\baselib\multithreading\primitives\synchronized_list_windows.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"

#include <xtl.h>

/* ---------- constants */

long const k_synchronized_list_alignment_bits = 4;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void synchronized_list_initialize(struct s_synchronized_list_header *);
// void synchronized_list_entry_clear(struct s_synchronized_list_entry *);
// struct s_synchronized_list_entry * synchronized_list_entry_next(struct s_synchronized_list_entry *);
// struct s_synchronized_list_entry * synchronized_list_entry_set(struct s_synchronized_list_entry *, struct s_synchronized_list_entry *);
// void synchronized_list_push(struct s_synchronized_list_header *, struct s_synchronized_list_entry *);
// void synchronized_list_push_multiple(struct s_synchronized_list_header *, long, struct s_synchronized_list_entry **);
// struct s_synchronized_list_entry * synchronized_list_pop(struct s_synchronized_list_header *);
// struct s_synchronized_list_entry * synchronized_list_flush(struct s_synchronized_list_header *);
// long synchronized_list_get_count(struct s_synchronized_list_header *);

void synchronized_list_initialize(s_synchronized_list_header * header)
{
    mangled_ppc("?synchronized_list_initialize@@YAXPAUs_synchronized_list_header@@@Z");

    assert_tag_debug_untracked_jul_11_2011(31, header);
    InitializeSListHead(reinterpret_cast<PSLIST_HEADER>(header));
};

void synchronized_list_entry_clear(s_synchronized_list_entry * entry)
{
    mangled_ppc("?synchronized_list_entry_clear@@YAXPAUs_synchronized_list_entry@@@Z");

    PSLIST_ENTRY slist_entry = reinterpret_cast<PSLIST_ENTRY>(entry);
    slist_entry->Next = NULL;
};

s_synchronized_list_entry * synchronized_list_entry_next(s_synchronized_list_entry * entry)
{
    mangled_ppc("?synchronized_list_entry_next@@YAPAUs_synchronized_list_entry@@PAU1@@Z");

    PSLIST_ENTRY slist_entry = reinterpret_cast<PSLIST_ENTRY>(entry);
    return reinterpret_cast<s_synchronized_list_entry *>(slist_entry->Next);
};

s_synchronized_list_entry * synchronized_list_entry_set(s_synchronized_list_entry * entry, s_synchronized_list_entry * next)
{
    mangled_ppc("?synchronized_list_entry_set@@YAPAUs_synchronized_list_entry@@PAU1@0@Z");

    PSLIST_ENTRY slist_entry = reinterpret_cast<PSLIST_ENTRY>(entry);
    PSLIST_ENTRY slist_next = reinterpret_cast<PSLIST_ENTRY>(next);
    PSLIST_ENTRY previous_next = slist_entry->Next;
    slist_entry->Next = slist_next;
    return reinterpret_cast<s_synchronized_list_entry *>(previous_next);
};

void synchronized_list_push(s_synchronized_list_header * header, s_synchronized_list_entry * entry)
{
    mangled_ppc("?synchronized_list_push@@YAXPAUs_synchronized_list_header@@PAUs_synchronized_list_entry@@@Z");

    assert_tag_debug_untracked_jul_11_2011(70, header);
    assert_tag_debug_untracked_jul_11_2011(71, entry);
    assert_tag_debug_untracked_jul_11_2011(72, pointer_is_aligned(entry, k_synchronized_list_alignment_bits));
    __lwsync();
    InterlockedPushEntrySList(reinterpret_cast<PSLIST_HEADER>(header), reinterpret_cast<PSLIST_ENTRY>(entry));
};

void synchronized_list_push_multiple(s_synchronized_list_header * header, long entry_count, s_synchronized_list_entry ** entries)
{
    mangled_ppc("?synchronized_list_push_multiple@@YAXPAUs_synchronized_list_header@@JPAPAUs_synchronized_list_entry@@@Z");

    assert_tag_debug_untracked_jul_11_2011(85, header);
    assert_tag_debug_untracked_jul_11_2011(86, entries);
    __lwsync();
    for (long entry_index = 0; entry_index < entry_count; entry_index++)
    {
        s_synchronized_list_entry * entry = entries[entry_index];
        assert_tag_debug_untracked_jul_11_2011(93, entry);
        assert_tag_debug_untracked_jul_11_2011(94, pointer_is_aligned(entry, k_synchronized_list_alignment_bits));
        InterlockedPushEntrySList(reinterpret_cast<PSLIST_HEADER>(header), reinterpret_cast<PSLIST_ENTRY>(entry));
    }
};

s_synchronized_list_entry * synchronized_list_pop(s_synchronized_list_header * header)
{
    mangled_ppc("?synchronized_list_pop@@YAPAUs_synchronized_list_entry@@PAUs_synchronized_list_header@@@Z");

    s_synchronized_list_entry * entry = reinterpret_cast<s_synchronized_list_entry *>(InterlockedPopEntrySList(reinterpret_cast<PSLIST_HEADER>(header)));
    __lwsync();
    return entry;
};

s_synchronized_list_entry * synchronized_list_flush(s_synchronized_list_header * header)
{
    mangled_ppc("?synchronized_list_flush@@YAPAUs_synchronized_list_entry@@PAUs_synchronized_list_header@@@Z");

    s_synchronized_list_entry * entry = reinterpret_cast<s_synchronized_list_entry *>(InterlockedFlushSList(reinterpret_cast<PSLIST_HEADER>(header)));
    __lwsync();
    return entry;
};

long synchronized_list_get_count(s_synchronized_list_header * header)
{
    mangled_ppc("?synchronized_list_get_count@@YAJPAUs_synchronized_list_header@@@Z");

    return QueryDepthSList(reinterpret_cast<PSLIST_HEADER>(header));
};
