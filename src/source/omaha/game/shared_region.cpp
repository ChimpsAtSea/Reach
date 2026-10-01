#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\shared_region.cpp"
/* ---------- headers */

#include "omaha\game\shared_region.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\cache\physical_memory_map.h"
#include "omaha\cache\restricted_memory_regions.h"
#include "omaha\cache\restricted_memory_section.h"
#include "omaha\multithreading\synchronization_spasm.h"

/* ---------- constants */

long const k_shared_region_section_size = 0x90000;
long const k_shared_region_total_size = (k_shared_region_mirror_count + 1) * k_shared_region_section_size;
long const k_audio_region_size = 0x30000;

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

void * g_restricted_global_shared_memory;
void * g_restricted_global_audio_memory;
c_restricted_section g_restricted_global_shared_memory_section;
c_restricted_section g_restricted_global_audio_memory_section;
c_restricted_section g_restricted_global_shared_memory_mirror_sections[k_shared_region_mirror_count];

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void *g_restricted_global_shared_memory; // "?g_restricted_global_shared_memory@@3PAXA"
// void *g_restricted_global_audio_memory; // "?g_restricted_global_audio_memory@@3PAXA"
// class c_restricted_section g_restricted_global_shared_memory_section; // "?g_restricted_global_shared_memory_section@@3Vc_restricted_section@@A"
// class c_restricted_section g_restricted_global_audio_memory_section; // "?g_restricted_global_audio_memory_section@@3Vc_restricted_section@@A"
// class c_restricted_section *g_restricted_global_shared_memory_mirror_sections; // "?g_restricted_global_shared_memory_mirror_sections@@3PAVc_restricted_section@@A"

// void shared_region_initialize(void);
// void shared_region_dispose(void);
// void audio_region_initialize(void);
// void audio_region_dispose(void);
// void g_restricted_global_shared_memory_section::`dynamic atexit destructor'(void);
// void g_restricted_global_shared_memory_mirror_sections::`dynamic atexit destructor'(void);
// void g_restricted_global_audio_memory_section::`dynamic atexit destructor'(void);

void shared_region_initialize(void)
{
    mangled_ppc("?shared_region_initialize@@YAXXZ");

    g_restricted_global_shared_memory = _physical_memory_malloc(_memory_stage_game_initialize, "shared region data", k_shared_region_total_size, 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 48);
    g_restricted_global_shared_memory_section.initialize(g_restricted_global_shared_memory, k_shared_region_section_size, k_crit_section_shared_subsection, k_invalid_semaphore);
    g_restricted_global_shared_memory_mirror_sections[0].initialize(offset_pointer(g_restricted_global_shared_memory, k_shared_region_section_size), k_shared_region_section_size, k_crit_section_shared_subsection_mirror0, k_invalid_semaphore);
    g_restricted_global_shared_memory_mirror_sections[1].initialize(offset_pointer(g_restricted_global_shared_memory, 2 * k_shared_region_section_size), k_shared_region_section_size, k_crit_section_shared_subsection_mirror1, k_invalid_semaphore);
    restricted_region_create(k_global_shared_region, &g_restricted_global_shared_memory_section, k_crit_section_shared_region, NULL);
    restricted_region_add_mirror(k_global_shared_region, &g_restricted_global_shared_memory_mirror_sections[0]);
    restricted_region_add_mirror(k_global_shared_region, &g_restricted_global_shared_memory_mirror_sections[1]);
    restricted_region_lock_primary(k_global_shared_region);
};

void shared_region_dispose(void)
{
    mangled_ppc("?shared_region_dispose@@YAXXZ");

    restricted_region_unlock_primary(k_global_shared_region);
    restricted_region_destroy(k_global_shared_region);
    if (g_restricted_global_shared_memory != NULL)
    {
        physical_memory_free(g_restricted_global_shared_memory);
        g_restricted_global_shared_memory = NULL;
    }
};

void audio_region_initialize(void)
{
    mangled_ppc("?audio_region_initialize@@YAXXZ");

    g_restricted_global_audio_memory = _physical_memory_malloc(_memory_stage_game_initialize, "audio region data", k_audio_region_size, 0, __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 102);
    g_restricted_global_audio_memory_section.initialize(g_restricted_global_audio_memory, k_audio_region_size, k_crit_section_audio_subsection, k_invalid_semaphore);
    restricted_region_create(k_global_audio_region, &g_restricted_global_audio_memory_section, k_crit_section_audio_region, NULL);
    restricted_region_lock_primary(k_global_audio_region);
};

void audio_region_dispose(void)
{
    mangled_ppc("?audio_region_dispose@@YAXXZ");

    restricted_region_destroy(k_global_audio_region);

    // the target frees the shared region allocation here, not the audio one
    if (g_restricted_global_shared_memory != NULL)
    {
        physical_memory_free(g_restricted_global_shared_memory);
        g_restricted_global_shared_memory = NULL;
    }
};
