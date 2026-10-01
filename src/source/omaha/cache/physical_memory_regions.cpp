#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cache\\physical_memory_regions.cpp"
/* ---------- headers */

#include "omaha\cache\physical_memory_regions.h"
#include "omaha\cache\physical_memory_map.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"

/* ---------- constants */

/* ---------- definitions */

struct s_physical_memory_allocation_region_definition
{
    char const * name;
    unsigned long size;
    bool write_combined;
};
static_assert(sizeof(s_physical_memory_allocation_region_definition) == 0xC, "s_physical_memory_allocation_region_definition");

/* ---------- prototypes */

/* ---------- globals */

static s_physical_memory_allocation_region_definition const k_physical_memory_allocation_region_definitions[k_physical_memory_allocation_region_count] =
{
    { "xaudio physical", 0x1B0000, false },
};

s_physical_memory_allocation_region_globals g_physical_memory_allocation_region_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<class c_physical_memory_allocation_region, 1>::k_element_count; // "?k_element_count@?$s_static_array@Vc_physical_memory_allocation_region@@$00@@2JB"
// struct s_physical_memory_allocation_region_globals g_physical_memory_allocation_region_globals; // "?g_physical_memory_allocation_region_globals@@3Us_physical_memory_allocation_region_globals@@A"

// void physical_memory_regions_initialize(void);
// class c_physical_memory_allocation_region * get_allocation_region(enum e_physical_memory_allocation_region);
// void physical_memory_regions_dispose(void);
// void * _physical_memory_region_allocate(enum e_physical_memory_allocation_region, unsigned long, long, char const *);
// public: void c_physical_memory_allocation_region::initialize(class c_basic_buffer<void>);
// public: void * c_physical_memory_allocation_region::allocate(char const *, char const *, unsigned long, long);
// public: void c_basic_buffer<void>::advance_start(unsigned long);
// public: class c_physical_memory_allocation_region & s_static_array<class c_physical_memory_allocation_region, 1>::operator[]<enum e_physical_memory_allocation_region>(enum e_physical_memory_allocation_region);
// public: static bool s_static_array<class c_physical_memory_allocation_region, 1>::valid<enum e_physical_memory_allocation_region>(enum e_physical_memory_allocation_region);
// public: s_physical_memory_allocation_region_globals::s_physical_memory_allocation_region_globals(void);
// public: s_static_array<class c_physical_memory_allocation_region, 1>::s_static_array<class c_physical_memory_allocation_region, 1>(void);
// public: c_physical_memory_allocation_region::c_physical_memory_allocation_region(void);

void physical_memory_regions_initialize(void)
{
    mangled_ppc("?physical_memory_regions_initialize@@YAXXZ");

    for (long region_index = 0; region_index < k_physical_memory_allocation_region_count; region_index++)
    {
        s_physical_memory_allocation_region_definition const * definition = &k_physical_memory_allocation_region_definitions[region_index];
        c_physical_memory_allocation_region * allocation_region = get_allocation_region(static_cast<e_physical_memory_allocation_region>(region_index));
        void * allocation = _physical_memory_malloc(_memory_stage_game_initialize, definition->name, definition->size, FLAG(_physical_memory_allocation_tracked_externally_bit), __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 74);
        assert_tag_debug_untracked_jul_11_2011(83, allocation);

        if (definition->size && definition->write_combined)
        {
            physical_memory_make_range_write_combined(allocation, definition->size);
        }

        c_basic_buffer<void> buffer(allocation, definition->size);
        allocation_region->initialize(buffer);
    }
};

c_physical_memory_allocation_region * get_allocation_region(e_physical_memory_allocation_region region)
{
    mangled_ppc("?get_allocation_region@@YAPAVc_physical_memory_allocation_region@@W4e_physical_memory_allocation_region@@@Z");

    return &g_physical_memory_allocation_region_globals.regions[region];
};

void physical_memory_regions_dispose(void)
{
    mangled_ppc("?physical_memory_regions_dispose@@YAXXZ");
};

void * _physical_memory_region_allocate(e_physical_memory_allocation_region region, unsigned long size, long alignment_bits, char const * name)
{
    mangled_ppc("?_physical_memory_region_allocate@@YAPAXW4e_physical_memory_allocation_region@@KJPBD@Z");

    c_physical_memory_allocation_region * allocation_region = get_allocation_region(region);
    return allocation_region->allocate(k_physical_memory_allocation_region_definitions[region].name, name, size, alignment_bits);
};

void c_physical_memory_allocation_region::initialize(c_basic_buffer<void> allocation_range)
{
    mangled_ppc("?initialize@c_physical_memory_allocation_region@@QAAXV?$c_basic_buffer@X@@@Z");

    assert_tag_debug_untracked_jul_11_2011(125, m_allocation_range.empty());

    m_allocation_range = allocation_range;
    m_range_left = m_allocation_range;
};

void * c_physical_memory_allocation_region::allocate(char const * region_name, char const * name, unsigned long size, long alignment_bits)
{
    mangled_ppc("?allocate@c_physical_memory_allocation_region@@QAAPAXPBD0KJ@Z");

    void * unaligned = m_range_left.begin();
    void * result = align_pointer(unaligned, alignment_bits);
    m_range_left.advance_start(pointer_distance32(unaligned, result));
    assert_tag_debug_untracked_jul_11_2011(146, m_range_left.size()>=size);
    m_range_left.advance_start(size);

    event_wrapped(_event_message, "system:physical_memory_region: region %s malloc %s %ld (alignment %d) at 0x%08X, remaining: %ld", region_name, name, size, pointer_distance32(unaligned, result), result, m_range_left.size());

    return result;
};

