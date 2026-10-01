/* ---------- headers */

#include "omaha\physics\havok_profile.h"
#include "omaha\physics\havok.h"
#include "omaha\physics\havok_memory.h"
#include "omaha\game\game.h"
#include "omaha\saved_games\saved_film_manager.h"
#include "core\corelib\cseries\cseries_string.h"
#include "havok\hkpdynamics\hkpWorld.h"
#include "havok\hkpdynamics\hkpSimulationIsland.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

long g_havok_profile_start_tick = NONE;
long g_havok_profile_stop_tick = NONE;

static s_havok_statistics g_havok_statistics;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long g_havok_profile_start_tick; // "?g_havok_profile_start_tick@@3JA"
// long g_havok_profile_stop_tick; // "?g_havok_profile_stop_tick@@3JA"

// void havok_profile_fetch(long *, long *, long *, long *, long *, long *);
// void havok_profile_display(char *, long);
// void havok_profile_start(void);
// void havok_profile_update(void);
// void havok_simulation_statistics_update(struct s_havok_statistics *);
// void havok_profile_stop(void);
// void havok_profile_range(long, long);

// $TODO nonmatching: only the unresolved target relocation to g_havok_statistics (0x8647F900, subi vs addi) differs
void havok_profile_fetch(long * active_entity_count, long * inactive_entity_count, long * fixed_entity_count, long * total_entity_count, long * active_island_count, long * total_island_count)
{
    mangled_ppc("?havok_profile_fetch@@YAXPAJ00000@Z");

    *active_entity_count = g_havok_statistics.active_entity_count;
    *inactive_entity_count = g_havok_statistics.inactive_entity_count;
    *fixed_entity_count = g_havok_statistics.fixed_entity_count;
    *total_entity_count = g_havok_statistics.total_entity_count;
    *active_island_count = g_havok_statistics.active_island_count;
    *total_island_count = g_havok_statistics.total_island_count;
};

void havok_profile_display(char * buffer, long buffer_size)
{
    mangled_ppc("?havok_profile_display@@YAXPADJ@Z");

    long active_entity_count;
    long inactive_entity_count;
    long total_entity_count;
    long total_island_count;
    long fixed_entity_count;
    long active_island_count;

    havok_profile_fetch(&active_entity_count, &inactive_entity_count, &fixed_entity_count, &total_entity_count, &active_island_count, &total_island_count);

    csnzappendf(buffer, buffer_size, "%d/%d/%d/%d(active/inactive/fixed/total) entities (%d/%d islands(active/total))|n", active_entity_count, inactive_entity_count, fixed_entity_count, total_entity_count, active_island_count, total_island_count);
};

void havok_profile_start(void)
{
    mangled_ppc("?havok_profile_start@@YAXXZ");

    havok_profile_stop();

    c_havok_memory_enable_system_allocator allocator;
};

void havok_profile_update(void)
{
    mangled_ppc("?havok_profile_update@@YAXXZ");

    if (!game_in_progress())
    {
        return;
    }

    havok_simulation_statistics_update(&g_havok_statistics);

    if (saved_film_manager_get_current_tick_estimate() == g_havok_profile_start_tick)
    {
        havok_profile_start();
    }
    else if (saved_film_manager_get_current_tick_estimate() == g_havok_profile_stop_tick)
    {
        havok_profile_stop();

        g_havok_profile_start_tick = NONE;
        g_havok_profile_stop_tick = NONE;
    }
    else
    {
        c_havok_memory_enable_system_allocator allocator;
    }
};

void havok_simulation_statistics_update(s_havok_statistics * statistics)
{
    mangled_ppc("?havok_simulation_statistics_update@@YAXPAUs_havok_statistics@@@Z");

    statistics->active_island_count = 0;
    statistics->total_island_count = 0;
    statistics->active_entity_count = 0;
    statistics->total_entity_count = 0;
    statistics->inactive_entity_count = 0;
    statistics->fixed_entity_count = 0;

    if (g_havok_world != NULL)
    {
        hkArray<hkpSimulationIsland *, hkContainerHeapAllocator> const & inactive_islands = g_havok_world->getInactiveSimulationIslands();
        hkArray<hkpSimulationIsland *, hkContainerHeapAllocator> const & active_islands = g_havok_world->getActiveSimulationIslands();

        long inactive_island_count = inactive_islands.getSize();
        for (long island_index = 0; island_index < inactive_island_count; island_index++)
        {
            statistics->inactive_entity_count += inactive_islands[island_index]->getEntities().getSize();
        }

        statistics->active_island_count = active_islands.getSize();
        for (long island_index = 0; island_index < statistics->active_island_count; island_index++)
        {
            statistics->active_entity_count += active_islands[island_index]->getEntities().getSize();
        }

        statistics->fixed_entity_count = g_havok_world->getFixedIsland()->getEntities().getSize();
        statistics->total_island_count = inactive_island_count + statistics->active_island_count;
        statistics->total_entity_count = statistics->inactive_entity_count + statistics->active_entity_count + statistics->fixed_entity_count;
    }
};

void havok_profile_stop(void)
{
    mangled_ppc("?havok_profile_stop@@YAXXZ");

    c_havok_memory_enable_system_allocator allocator;
};

void havok_profile_range(long tick_start, long tick_stop)
{
    mangled_ppc("?havok_profile_range@@YAXJJ@Z");

    g_havok_profile_start_tick = tick_start;
    g_havok_profile_stop_tick = tick_stop;
};

