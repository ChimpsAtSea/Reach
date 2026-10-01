#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\memory\\debug_memory\\debug_memory_allocators.cpp"
/* ---------- headers */

#include "foundation\baselib\memory\debug_memory\debug_memory_allocators.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "foundation\baselib\datatypes\hash_table.h"
#include "foundation\baselib\memory\base\base_memory_windows.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_globals.h"
#include "foundation\baselib\memory\debug_memory\debug_memory_reporting.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

static void const * const k_unspecified_nonheap_resource = reinterpret_cast<void const *>(NONE);

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void * debug_malloc(unsigned int, enum e_debug_memory_flags, char const *, long, long, char const *, char const *, char const *);
// void debug_free(void *, char const *, long);
// void * debug_realloc(void *, unsigned int, enum e_debug_memory_flags, char const *, long, long, char const *, char const *, char const *);
// void * debug_malloc_aligned(unsigned int, long, enum e_debug_memory_flags, char const *, long, long, char const *, char const *, char const *);
// void debug_free_aligned(void *, char const *, long);
// void * debug_realloc_aligned(void *, unsigned int, long, enum e_debug_memory_flags, char const *, long, long, char const *, char const *, char const *);
// void debug_pretrack_nonheap_alloc_static(void const *, unsigned int);
// void debug_track_nonheap_alloc(void const *, unsigned int, enum e_debug_memory_flags, char const *, long, long, char const *, char const *, char const *);
// void debug_track_nonheap_free(void const *, char const *, long);
// void debug_begin_tracking_nonheap_allocation(struct s_base_memory_information *);
// void debug_end_tracking_nonheap_allocation(struct s_base_memory_information const *, struct s_base_memory_information const *, void const *, char const *, long, long, char const *, char const *, char const *);
// void debug_initialize_memory(void *, long, unsigned int);
// public: bool c_hash_table<struct s_pointer_header *, void>::add(void const *, struct s_pointer_header *const *);

void * debug_malloc(unsigned int size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_malloc@@YAPAXIW4e_debug_memory_flags@@PBDJJ111@Z");

    return debug_malloc_aligned(size, 0, flags, file, line, type_identifier, type, subtype, name);
};

void debug_free(void * pointer, char const * file, long line)
{
    mangled_ppc("?debug_free@@YAXPAXPBDJ@Z");

    debug_free_aligned(pointer, file, line);
};

void * debug_realloc(void * pointer, unsigned int new_size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_realloc@@YAPAXPAXIW4e_debug_memory_flags@@PBDJJ222@Z");

    return debug_realloc_aligned(pointer, new_size, 0, flags, file, line, type_identifier, type, subtype, name);
};

void * debug_malloc_aligned(unsigned int size, long alignment_bits, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_malloc_aligned@@YAPAXIJW4e_debug_memory_flags@@PBDJJ111@Z");

    char const * stripped_file = strip_source_directory(file);
    long safe_line = line;
    long identifier = type_identifier;
    char const * local_type = make_constant_string(type);
    char const * alloc_subtype = make_constant_string(subtype);
    char const * constant_name = make_constant_string(name);
    void * user_pointer = NULL;

    assert_tag_debug_untracked_jul_11_2011(99, size>=0 && size<k_maximum_pointer_size);
    assert_tag_debug_untracked_jul_11_2011(100, alignment_bits>=0 && alignment_bits<=k_maximum_alignment_bits);
    assert_tag_debug_untracked_jul_11_2011(101, !TEST_BIT(flags, _debug_memory_free_implicitly_on_exit_bit));
    check_debug_memory_manager(stripped_file, safe_line);

    {
        long alignment = 1 << alignment_bits;
        unsigned int base_size = alignment - 1 + sizeof(s_pointer_header) + size + sizeof(s_pointer_trailer);
        void * base_pointer = base_malloc(base_size);
        if (base_pointer)
        {
            unsigned long base_address = address_from_pointer(base_pointer);
            unsigned long user_address = (base_address + (alignment - 1) + sizeof(s_pointer_header)) & ~(alignment - 1);
            unsigned long header_address = user_address - sizeof(s_pointer_header);
            long offset = header_address - base_address;
            unsigned int actual_size = base_memory_get_used_memory_size(base_pointer);

            assert_tag_debug_untracked_jul_11_2011(117, (user_address&(alignment-1))==0);
            assert_tag_debug_untracked_jul_11_2011(118, base_address<=user_address-sizeof(s_pointer_header));
            assert_tag_debug_untracked_jul_11_2011(119, user_address+size+sizeof(s_pointer_trailer)<=base_address+base_size);

            user_pointer = pointer_from_address(user_address);
            debug_initialize_memory(user_pointer, 0xCD, size);
            build_header_and_trailer(user_pointer, size, alignment_bits, offset, flags, stripped_file, safe_line, identifier, actual_size, local_type, alloc_subtype, constant_name, NULL, false);
            track_heap_allocation_size(0, size);
        }
        else
        {
            debug_alloc_failed(size, 0, _alloc_failed_heap, stripped_file, safe_line, identifier, local_type, alloc_subtype, constant_name);
        }
    }

    return user_pointer;
};

void debug_free_aligned(void * pointer, char const * file, long line)
{
    mangled_ppc("?debug_free_aligned@@YAXPAXPBDJ@Z");

    if (pointer)
    {
        char const * stripped_file = strip_source_directory(file);
        s_pointer_header * header = get_header_from_user_pointer(pointer);

        check_debug_memory_manager(stripped_file, line);
        check_header(header, stripped_file, line);
        check_pointer(pointer, stripped_file, line);
        check_nonheap_resource(header, stripped_file, line);
        track_heap_allocation_size(header->size, 0);
        dequeue_header(header, stripped_file, line);
        debug_initialize_memory(pointer, 0xDD, header->size);
        base_free(get_base_pointer_from_header(header));
    }
};

void * debug_realloc_aligned(void * pointer, unsigned int new_size, long alignment_bits, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_realloc_aligned@@YAPAXPAXIJW4e_debug_memory_flags@@PBDJJ222@Z");

    char const * stripped_file = strip_source_directory(file);
    long safe_line = line;
    long identifier = type_identifier;
    char const * local_type = make_constant_string(type);
    char const * alloc_subtype = make_constant_string(subtype);
    char const * constant_name = make_constant_string(name);
    void * new_user_pointer = NULL;

    check_debug_memory_manager(stripped_file, line);
    assert_tag_debug_untracked_jul_11_2011(195, new_size>=0 && new_size<k_maximum_pointer_size);
    assert_tag_debug_untracked_jul_11_2011(196, alignment_bits>=0 && alignment_bits<=k_maximum_alignment_bits);

    if (new_size > 0)
    {
        if (pointer)
        {
            s_pointer_header * old_header = get_header_from_user_pointer(pointer);
            check_header(old_header, stripped_file, safe_line);
            check_pointer(pointer, stripped_file, safe_line);
            check_nonheap_resource(old_header, stripped_file, safe_line);
            dassert_tag_debug_untracked_jul_11_2011(249, old_header->alignment_bits == alignment_bits, "what kind of a jackass tries to reallocate with a different alignment???");
            dassert_tag_debug_untracked_jul_11_2011(250, !old_header->freed_externally_on_exit, "heap resource has implicit-free-on-exit set, which is disallowed");

            unsigned int old_size = old_header->size;
            unsigned int old_actual_size = old_header->size + old_header->actual_size_offset;
            long old_offset = old_header->offset;
            stripped_file = old_header->tracking->file;
            safe_line = old_header->tracking->line;
            local_type = old_header->tracking->type;
            alloc_subtype = old_header->tracking->subtype;
            constant_name = old_header->tracking->name;
            void * old_base_pointer = get_base_pointer_from_header(old_header);
            dequeue_header(old_header, stripped_file, safe_line);

            long alignment = 1 << alignment_bits;
            unsigned int new_base_size = alignment - 1 + sizeof(s_pointer_header) + new_size + sizeof(s_pointer_trailer);
            if (alignment < old_offset && old_offset + old_size < alignment - 1 + new_size)
            {
                csmemmove(offset_pointer(old_base_pointer, alignment - 1 + sizeof(s_pointer_header)), pointer, old_size);
                old_offset = alignment - 1;
            }

            void * new_base_pointer = base_realloc(old_base_pointer, new_base_size);
            if (new_base_pointer)
            {
                unsigned long new_base_address = address_from_pointer(new_base_pointer);
                unsigned long new_user_address = (new_base_address + (alignment - 1) + sizeof(s_pointer_header)) & ~(alignment - 1);
                unsigned long new_header_address = new_user_address - sizeof(s_pointer_header);
                unsigned int new_actual_size = base_memory_get_used_memory_size(new_base_pointer);
                long new_offset = new_header_address - new_base_address;

                assert_tag_debug_untracked_jul_11_2011(291, (new_user_address&(alignment-1))==0);
                assert_tag_debug_untracked_jul_11_2011(292, new_base_address<=new_user_address-sizeof(s_pointer_header));
                assert_tag_debug_untracked_jul_11_2011(293, new_user_address+new_size+sizeof(s_pointer_trailer)<=new_base_address+new_base_size);

                new_user_pointer = pointer_from_address(new_user_address);
                if (new_offset != old_offset)
                {
                    unsigned long data_address = new_base_address + old_offset + sizeof(s_pointer_header);
                    unsigned int data_size = int_min(new_size, old_size);

                    assert_tag_debug_untracked_jul_11_2011(305, new_base_address<=data_address-sizeof(s_pointer_header));
                    assert_tag_debug_untracked_jul_11_2011(306, data_address+data_size<=new_base_address+new_base_size);

                    csmemmove(new_user_pointer, pointer_from_address(data_address), data_size);
                }

                if (new_size > old_size)
                {
                    debug_initialize_memory(offset_pointer(new_user_pointer, old_size), 0xCD, new_size - old_size);
                }

                build_header_and_trailer(new_user_pointer, new_size, alignment_bits, new_offset, flags, stripped_file, safe_line, identifier, new_actual_size, local_type, alloc_subtype, constant_name, NULL, false);
                track_heap_allocation_size(old_size, new_size);
            }
            else
            {
                if (pointer != offset_pointer(old_base_pointer, old_offset + sizeof(s_pointer_header)))
                {
                    csmemmove(pointer, offset_pointer(old_base_pointer, old_offset + sizeof(s_pointer_header)), old_size);
                    old_offset = pointer_distance(old_base_pointer, pointer) - sizeof(s_pointer_header);
                }

                build_header_and_trailer(pointer, old_size, alignment_bits, old_offset, flags, stripped_file, safe_line, identifier, old_actual_size, local_type, alloc_subtype, constant_name, NULL, false);
                debug_alloc_failed(new_size, old_size, _alloc_failed_heap, stripped_file, safe_line, identifier, local_type, alloc_subtype, constant_name);
            }
        }
        else
        {
            new_user_pointer = debug_malloc_aligned(new_size, alignment_bits, flags, stripped_file, safe_line, identifier, local_type, alloc_subtype, constant_name);
        }
    }
    else if (pointer)
    {
        debug_free_aligned(pointer, stripped_file, safe_line);
    }

    return new_user_pointer;
};

void debug_pretrack_nonheap_alloc_static(void const * nonheap_resource, unsigned int size)
{
    mangled_ppc("?debug_pretrack_nonheap_alloc_static@@YAXPBXI@Z");

    pretrack_nonheap_allocation_size(0, size);
};

void debug_track_nonheap_alloc(void const * nonheap_resource, unsigned int size, e_debug_memory_flags flags, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_track_nonheap_alloc@@YAXPBXIW4e_debug_memory_flags@@PBDJJ222@Z");

    char const * stripped_file = strip_source_directory(file);
    long safe_line = line;
    long identifier = type_identifier;
    char const * local_type = make_constant_string(type);
    char const * alloc_subtype = make_constant_string(subtype);
    char const * constant_name = make_constant_string(name);

    assert_tag_debug_untracked_jul_11_2011(389, size>=0 && size<k_maximum_pointer_size);
    check_debug_memory_manager(stripped_file, safe_line);

    event(_event_status, "memory:debug_memory: nonheap allocation %d bytes %s #%d %s(%d) %s %s", size, stripped_file, safe_line, local_type ? local_type : "", identifier, alloc_subtype ? alloc_subtype : "", constant_name ? constant_name : "");

    s_pointer_header * header = static_cast<s_pointer_header *>(base_malloc(sizeof(s_pointer_header) + sizeof(s_pointer_trailer)));
    if (header)
    {
        unsigned int actual_size = size + base_memory_get_used_memory_size(header);
        bool free_on_exit = TEST_BIT(flags, _debug_memory_free_implicitly_on_exit_bit);

        if (!g_nonheap_hash_table.is_created())
        {
            free_on_exit = true;
        }

        if (!nonheap_resource)
        {
            nonheap_resource = k_unspecified_nonheap_resource;
            free_on_exit = true;
        }

        build_header_and_trailer(get_user_pointer_from_header(header), size, 0, 0, flags, stripped_file, safe_line, NONE, actual_size, local_type, alloc_subtype, constant_name, nonheap_resource, free_on_exit);

        if (!free_on_exit)
        {
            s_pointer_header * existing_header = NULL;
            void const * found = g_nonheap_hash_table.find(nonheap_resource, &existing_header);

            assert_tag_debug_untracked_jul_11_2011(427, nonheap_resource);

            if (!found)
            {
                if (g_nonheap_hash_table.add(nonheap_resource, &header))
                {
                }
                else
                {
                    dassert_tag_debug_untracked_jul_11_2011(436, false, "the debug memory nonheap hash table is full, increase k_maximum_nonheap_resources");
                }
            }
            else
            {
                dassert_tag_debug_untracked_jul_11_2011(441, false, "duplicate nonheap resource address");
            }
        }

        if (TEST_BIT(flags, _debug_memory_pretrack_nonheap_bit))
        {
            pretrack_nonheap_allocation_size(size, 0);
        }
        track_nonheap_allocation_size(0, size);
    }
    else
    {
        debug_alloc_failed(0, 0, _alloc_failed_nonheap, stripped_file, safe_line, NONE, local_type, alloc_subtype, constant_name);
    }
};

void debug_track_nonheap_free(void const * nonheap_resource, char const * file, long line)
{
    mangled_ppc("?debug_track_nonheap_free@@YAXPBXPBDJ@Z");

    char const * stripped_file = strip_source_directory(file);
    s_pointer_header * header = NULL;

    assert_tag_debug_untracked_jul_11_2011(468, nonheap_resource!=NULL);
    assert_tag_debug_untracked_jul_11_2011(469, nonheap_resource!=k_unspecified_nonheap_resource);
    check_debug_memory_manager(stripped_file, line);

    if (g_nonheap_hash_table.is_created())
    {
        void const * old_nonheap_resource = g_nonheap_hash_table.find(nonheap_resource, &header);
        if (old_nonheap_resource)
        {
            assert_tag_debug_untracked_jul_11_2011(480, header!=NULL);
            assert_tag_debug_untracked_jul_11_2011(481, header->nonheap_resource==nonheap_resource);
        }
    }

    if (header)
    {
        force_release_header(header, stripped_file, line);
    }
    else
    {
        s_pointer_header * nonheap_header = query_nonheap_header(nonheap_resource);
        if (nonheap_header)
        {
            dassert_tag_debug_untracked_jul_11_2011(508, nonheap_header->freed_externally_on_exit, "nonheap resource must be implicitly-free-on-exit");
        }
        else
        {
            event(_event_error, "memory:debug_memory: tracked free of unknown nonheap resource@%p (mismatched free?)", nonheap_resource);
        }
    }
};

void debug_begin_tracking_nonheap_allocation(s_base_memory_information * start_information)
{
    mangled_ppc("?debug_begin_tracking_nonheap_allocation@@YAXPAUs_base_memory_information@@@Z");

    base_memory_information_get(start_information);
};

void debug_end_tracking_nonheap_allocation(s_base_memory_information const * initial_memory, s_base_memory_information const * final_memory, void const * nonheap_resource, char const * file, long line, long type_identifier, char const * type, char const * subtype, char const * name)
{
    mangled_ppc("?debug_end_tracking_nonheap_allocation@@YAXPBUs_base_memory_information@@0PBXPBDJJ222@Z");

    long tracked_heap_allocations;
    long tracked_nonheap_allocations;

    assert_tag_debug_untracked_jul_11_2011(538, initial_memory);
    assert_tag_debug_untracked_jul_11_2011(539, final_memory);

    long memory_allocated = initial_memory->free - final_memory->free;
    tracked_heap_allocations = final_memory->tracked_heap_allocations - initial_memory->tracked_heap_allocations;
    tracked_nonheap_allocations = final_memory->tracked_nonheap_allocations - initial_memory->tracked_nonheap_allocations;
    memory_allocated -= tracked_heap_allocations;
    memory_allocated -= tracked_nonheap_allocations;

    if (memory_allocated > 0)
    {
        dassert_tag_debug_untracked_jul_11_2011(553, nonheap_resource, "tracking_nonheap_allocation needs to record a nonheap allocation but was not given a resource to associate it with");
        if (nonheap_resource)
        {
            debug_track_nonheap_alloc(nonheap_resource, memory_allocated, static_cast<e_debug_memory_flags>(FLAG(_debug_memory_free_implicitly_on_exit_bit)), file, line, type_identifier, type, subtype, name);
        }
    }
};

void debug_initialize_memory(void * pointer, long value, unsigned int size)
{
    mangled_ppc("?debug_initialize_memory@@YAXPAXJI@Z");

    csmemset(pointer, value, size);
};

