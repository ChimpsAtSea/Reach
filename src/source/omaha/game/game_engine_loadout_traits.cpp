#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_loadout_traits.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_loadout_traits.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_engine_util.h"
#include "omaha\game\loadout_definition.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_loadout_palette_tag_definition const * loadout_palette_get_by_name(long);
// public: void c_loadout_traits::set(struct s_loadout_tag_definition const *);
// public: long c_loadout_traits::get_name(void) const;
// public: char c_loadout_traits::get_name_absolute_index(void) const;
// public: void c_loadout_traits::set_name(long);
// public: long c_loadout_traits::get_initial_primary_weapon(void) const;
// public: void c_loadout_traits::set_initial_primary_weapon(long);
// public: long c_loadout_traits::get_initial_secondary_weapon(void) const;
// public: void c_loadout_traits::set_initial_secondary_weapon(long);
// public: long c_loadout_traits::get_initial_equipment(void) const;
// public: void c_loadout_traits::set_initial_equipment(long);
// public: void c_loadout_palette_traits::set(struct s_loadout_palette_tag_definition const *);
// public: void c_game_engine_loadout_traits::set(struct s_game_engine_loadout_definition const *);

s_loadout_palette_tag_definition const * loadout_palette_get_by_name(long palette_name)
{
    mangled_ppc("?loadout_palette_get_by_name@@YAPBUs_loadout_palette_tag_definition@@J@Z");

    s_loadout_palette_tag_definition const * result = NULL;

    {
        s_loadout_globals_tag_definition const * loadout_globals = try_and_get_loadout_globals();
        if (loadout_globals != NULL)
        {
            for (long palette_index = 0; result == NULL && palette_index < loadout_globals->loadout_palettes.count; palette_index++)
            {
                s_loadout_palette_tag_definition const * loadout_palette = static_cast<s_loadout_palette_tag_definition const *>(tag_block_get_element_with_size(&loadout_globals->loadout_palettes, palette_index, sizeof(s_loadout_palette_tag_definition)));
                if (loadout_palette->palette_name == palette_name)
                {
                    result = loadout_palette;
                }
            }

            if (result == NULL)
            {
                event_wrapped(_event_error, "player_loadouts: get_player_loadout_palette_by_name: loadout palette '%s' not found among the %i loadout palettes in tags", string_id_get_string_const(palette_name), loadout_globals->loadout_palettes.count);
            }
        }
        else
        {
            event_wrapped(_event_error, "player_loadouts: get_player_loadout_palette_by_name: no loadout globals tag found");
        }
    }

    return result;
};

void c_loadout_traits::set(s_loadout_tag_definition const * loadout_definition)
{
    mangled_ppc("?set@c_loadout_traits@@QAAXPBUs_loadout_tag_definition@@@Z");

    m_flags.set(_enabled_bit, true);
    set_name(loadout_definition->loadout_name);
    m_initial_primary_weapon_absolute_index = static_cast<char>(game_engine_get_multiplayer_weapon_selection_absolute_index(loadout_definition->initial_primary_weapon));
    m_initial_secondary_weapon_absolute_index = static_cast<char>(game_engine_get_multiplayer_weapon_selection_absolute_index(loadout_definition->initial_secondary_weapon));
    m_initial_equipment_absolute_index = static_cast<char>(game_engine_get_multiplayer_equipment_selection_absolute_index(loadout_definition->initial_equipment));
    m_initial_grenade_count = loadout_definition->initial_grenade_count;
};

long c_loadout_traits::get_name(void) const
{
    mangled_ppc("?get_name@c_loadout_traits@@QBAJXZ");

    return loadout_tag_get_loadout_name(get_name_absolute_index());
};

char c_loadout_traits::get_name_absolute_index(void) const
{
    mangled_ppc("?get_name_absolute_index@c_loadout_traits@@QBADXZ");

    return m_name_absolute_index;
};

void c_loadout_traits::set_name(long name)
{
    mangled_ppc("?set_name@c_loadout_traits@@QAAXJ@Z");

    long name_absolute_index = loadout_tag_find_loadout_name_absolute_index(name);
    set_name_absolute_index(static_cast<char>(name_absolute_index));
};

long c_loadout_traits::get_initial_primary_weapon(void) const
{
    mangled_ppc("?get_initial_primary_weapon@c_loadout_traits@@QBAJXZ");

    return game_engine_get_multiplayer_weapon_selection_name(get_initial_primary_weapon_absolute_index());
};

void c_loadout_traits::set_initial_primary_weapon(long initial_primary_weapon)
{
    mangled_ppc("?set_initial_primary_weapon@c_loadout_traits@@QAAXJ@Z");

    short initial_primary_weapon_absolute_index = static_cast<short>(game_engine_get_multiplayer_weapon_selection_absolute_index(initial_primary_weapon));
    set_initial_primary_weapon_absolute_index(static_cast<char>(initial_primary_weapon_absolute_index));
};

long c_loadout_traits::get_initial_secondary_weapon(void) const
{
    mangled_ppc("?get_initial_secondary_weapon@c_loadout_traits@@QBAJXZ");

    return game_engine_get_multiplayer_weapon_selection_name(get_initial_secondary_weapon_absolute_index());
};

void c_loadout_traits::set_initial_secondary_weapon(long initial_secondary_weapon)
{
    mangled_ppc("?set_initial_secondary_weapon@c_loadout_traits@@QAAXJ@Z");

    long initial_secondary_weapon_absolute_index = game_engine_get_multiplayer_weapon_selection_absolute_index(initial_secondary_weapon);
    set_initial_secondary_weapon_absolute_index(static_cast<char>(initial_secondary_weapon_absolute_index));
};

long c_loadout_traits::get_initial_equipment(void) const
{
    mangled_ppc("?get_initial_equipment@c_loadout_traits@@QBAJXZ");

    return game_engine_get_multiplayer_equipment_selection_name(get_initial_equipment_absolute_index());
};

void c_loadout_traits::set_initial_equipment(long initial_equipment)
{
    mangled_ppc("?set_initial_equipment@c_loadout_traits@@QAAXJ@Z");

    long initial_equipment_absolute_index = game_engine_get_multiplayer_equipment_selection_absolute_index(initial_equipment);
    set_initial_equipment_absolute_index(static_cast<char>(initial_equipment_absolute_index));
};

void c_loadout_palette_traits::set(s_loadout_palette_tag_definition const * loadout_palette_definition)
{
    mangled_ppc("?set@c_loadout_palette_traits@@QAAXPBUs_loadout_palette_tag_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(134, loadout_palette_definition->loadouts.count<=NUMBEROF(m_loadouts));

    for (long loadout_index = 0; loadout_index < loadout_palette_definition->loadouts.count; loadout_index++)
    {
        s_loadout_tag_reference const * loadout_reference = static_cast<s_loadout_tag_reference const *>(tag_block_get_element_with_size(&loadout_palette_definition->loadouts, loadout_index, sizeof(s_loadout_tag_reference)));
        if (loadout_reference->loadout_index != NONE)
        {
            s_loadout_globals_tag_definition const * loadout_globals = try_and_get_loadout_globals();
            if (loadout_globals != NULL)
            {
                s_loadout_tag_definition const * loadout_definition = static_cast<s_loadout_tag_definition const *>(tag_block_get_element_with_size(&loadout_globals->loadouts, loadout_reference->loadout_index, sizeof(s_loadout_tag_definition)));
                m_loadouts[loadout_index].set(loadout_definition);
            }
        }
    }
};

void c_game_engine_loadout_traits::set(s_game_engine_loadout_definition const * loadout_traits_definition)
{
    mangled_ppc("?set@c_game_engine_loadout_traits@@QAAXPBUs_game_engine_loadout_definition@@@Z");

    assert_tag_debug_untracked_jul_11_2011(159, loadout_traits_definition->loadout_palettes.count<=NUMBEROF(m_loadout_palettes));

    m_flags = loadout_traits_definition->flags;
    for (long palette_index = 0; palette_index < loadout_traits_definition->loadout_palettes.count; palette_index++)
    {
        s_loadout_palette_entry_definition const * palette_entry = static_cast<s_loadout_palette_entry_definition const *>(tag_block_get_element_with_size(&loadout_traits_definition->loadout_palettes, palette_index, sizeof(s_loadout_palette_entry_definition)));
        if (palette_entry->palette_name != -1)
        {
            s_loadout_palette_tag_definition const * loadout_palette_definition = loadout_palette_get_by_name(palette_entry->palette_name);
            if (loadout_palette_definition != NULL)
            {
                m_loadout_palettes[palette_index].set(loadout_palette_definition);
            }
        }
    }
};

