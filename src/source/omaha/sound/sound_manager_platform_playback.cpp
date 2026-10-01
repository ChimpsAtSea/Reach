/* ---------- headers */

#include "omaha\sound\sound_manager_platform_playback.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\sound\platform_sound_effect_definitions.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\game\game_globals.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

long const k_string_id_global_dry = 0x12F; // STRING_ID(global, dry)
long const k_playback_type_shift = LONG_BITS - k_game_sound_platform_type_bits;
unsigned long const k_playback_index_mask = (1UL << k_playback_type_shift) - 1;

/* ---------- definitions */

/* ---------- prototypes */

static long playback_designator_from_type_and_index(e_game_sound_platform_playback_type type, long index);
static e_game_sound_platform_playback_type playback_type_from_designator(long playback_designator);
static long playback_index_from_designator(long playback_designator);
static long sound_effect_collection_find_playback(long sound_effect_collection_index, long name);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long game_sound_find_platform_playback_by_label(long);
// long playback_designator_from_type_and_index(enum e_game_sound_platform_playback_type, long);
// long game_sound_get_platform_playback_label(long);
// enum e_game_sound_platform_playback_type playback_type_from_designator(long);
// long playback_index_from_designator(long);
// long sound_effect_collection_find_playback(long, long);
// struct s_platform_sound_playback_definition const * game_sound_get_platform_playback_definition(long, long);
// struct s_platform_sound_playback_definition const * game_sound_get_default_platform_playback_definition(long);

long game_sound_find_platform_playback_by_label(long playback_label)
{
    mangled_ppc("?game_sound_find_platform_playback_by_label@@YAJJ@Z");

    long playback_designator = NONE;
    if (playback_label != _string_id_empty_string && playback_label != _string_id_invalid)
    {
        if (playback_label == k_string_id_global_dry)
        {
            playback_designator = playback_designator_from_type_and_index(_game_sound_platform_playback_suppress, 0);
        }
        else
        {
            scenario const * scenario = global_scenario_get();
            long scenario_playback_index = sound_effect_collection_find_playback(scenario->sound_effect_collection.index, playback_label);
            if (scenario_playback_index != NONE)
            {
                playback_designator = playback_designator_from_type_and_index(_game_sound_platform_playback_scenario, scenario_playback_index);
            }
        }
        if (playback_designator == NONE)
        {
            s_game_globals const * game_globals = scenario_get_game_globals();
            s_sound_globals_definition const * sound_globals = game_globals->sound_globals.count != 0 ? static_cast<s_sound_globals_definition const *>(tag_block_get_element_with_size(&game_globals->sound_globals, 0, sizeof(s_sound_globals_definition))) : NULL;
            if (sound_globals != NULL)
            {
                long global_playback_index = sound_effect_collection_find_playback(sound_globals->sound_effect_collection_reference.index, playback_label);
                if (global_playback_index != NONE)
                {
                    playback_designator = playback_designator_from_type_and_index(_game_sound_platform_playback_global, global_playback_index);
                }
            }
        }
    }

    return playback_designator;
};

static long playback_designator_from_type_and_index(e_game_sound_platform_playback_type type, long index)
{
    mangled_ppc("?playback_designator_from_type_and_index@@YAJW4e_game_sound_platform_playback_type@@J@Z");

    return (index & k_playback_index_mask) | ((type << k_playback_type_shift) & ~k_playback_index_mask);
};

long game_sound_get_platform_playback_label(long playback_designator)
{
    mangled_ppc("?game_sound_get_platform_playback_label@@YAJJ@Z");

    long playback_label = NONE;
    e_game_sound_platform_playback_type playback_type = playback_type_from_designator(playback_designator);
    switch (playback_type)
    {
    case _game_sound_platform_playback_global:
        {
            s_game_globals const * game_globals = scenario_get_game_globals();
            s_sound_globals_definition const * sound_globals = game_globals->sound_globals.count != 0 ? static_cast<s_sound_globals_definition const *>(tag_block_get_element_with_size(&game_globals->sound_globals, 0, sizeof(s_sound_globals_definition))) : NULL;
            if (sound_globals != NULL && sound_globals->sound_effect_collection_reference.index != NONE)
            {
                long playback_index = playback_index_from_designator(playback_designator);
                s_platform_sound_playback_collection const * sound_effect_collection = static_cast<s_platform_sound_playback_collection const *>(tag_get(SOUND_EFFECT_COLLECTION_TAG, sound_globals->sound_effect_collection_reference.index));
                playback_label = static_cast<s_platform_sound_playback_named_definition const *>(tag_block_get_element_with_size(&sound_effect_collection->playback_collection, playback_index, sizeof(s_platform_sound_playback_named_definition)))->name;
            }
        }
        break;
    case _game_sound_platform_playback_scenario:
        {
            scenario const * scenario = global_scenario_get();
            if (scenario->sound_effect_collection.index != NONE)
            {
                long playback_index = playback_index_from_designator(playback_designator);
                s_platform_sound_playback_collection const * sound_effect_collection = static_cast<s_platform_sound_playback_collection const *>(tag_get(SOUND_EFFECT_COLLECTION_TAG, scenario->sound_effect_collection.index));
                playback_label = static_cast<s_platform_sound_playback_named_definition const *>(tag_block_get_element_with_size(&sound_effect_collection->playback_collection, playback_index, sizeof(s_platform_sound_playback_named_definition)))->name;
            }
        }
        break;
    }

    return playback_label;
};

static e_game_sound_platform_playback_type playback_type_from_designator(long playback_designator)
{
    mangled_ppc("?playback_type_from_designator@@YA?AW4e_game_sound_platform_playback_type@@J@Z");

    return static_cast<e_game_sound_platform_playback_type>((playback_designator & ~k_playback_index_mask) >> k_playback_type_shift);
};

static long playback_index_from_designator(long playback_designator)
{
    mangled_ppc("?playback_index_from_designator@@YAJJ@Z");

    return playback_designator & k_playback_index_mask;
};

static long sound_effect_collection_find_playback(long sound_effect_collection_index, long name)
{
    mangled_ppc("?sound_effect_collection_find_playback@@YAJJJ@Z");

    long playback_index = NONE;
    if (sound_effect_collection_index != NONE)
    {
        s_platform_sound_playback_collection const * sound_effect_collection = static_cast<s_platform_sound_playback_collection const *>(tag_get(SOUND_EFFECT_COLLECTION_TAG, sound_effect_collection_index));
        for (long element_index = 0; element_index < sound_effect_collection->playback_collection.count; element_index++)
        {
            s_platform_sound_playback_named_definition const * named_playback = static_cast<s_platform_sound_playback_named_definition const *>(tag_block_get_element_with_size(&sound_effect_collection->playback_collection, element_index, sizeof(s_platform_sound_playback_named_definition)));
            if (named_playback->name == name)
            {
                playback_index = element_index;
                break;
            }
        }
    }

    return playback_index;
};

s_platform_sound_playback_definition const * game_sound_get_platform_playback_definition(long definition_index, long playback_designator)
{
    mangled_ppc("?game_sound_get_platform_playback_definition@@YAPBUs_platform_sound_playback_definition@@JJ@Z");

    s_platform_sound_playback_definition const * platform_playback = NULL;
    if (playback_designator == NONE)
    {
        if (definition_index != NONE && tag_get_group_tag(definition_index) == SOUND_TAG)
        {
            sound_definition * sound = static_cast<sound_definition *>(tag_get(SOUND_TAG, definition_index));
            platform_playback = sound_definition_try_and_get_platform_playback(sound);
        }
    }
    else
    {
        e_game_sound_platform_playback_type playback_type = playback_type_from_designator(playback_designator);
        switch (playback_type)
        {
        case _game_sound_platform_playback_tag:
            {
                if (tag_get_group_tag(definition_index) == SOUND_TAG)
                {
                    sound_definition * sound = static_cast<sound_definition *>(tag_get(SOUND_TAG, definition_index));
                    platform_playback = sound_definition_try_and_get_platform_playback(sound);
                }
            }
            break;
        case _game_sound_platform_playback_global:
            {
                s_game_globals const * game_globals = scenario_get_game_globals();
                s_sound_globals_definition const * sound_globals = game_globals->sound_globals.count != 0 ? static_cast<s_sound_globals_definition const *>(tag_block_get_element_with_size(&game_globals->sound_globals, 0, sizeof(s_sound_globals_definition))) : NULL;
                if (sound_globals != NULL && sound_globals->sound_effect_collection_reference.index != NONE)
                {
                    long playback_index = playback_index_from_designator(playback_designator);
                    s_platform_sound_playback_collection const * sound_effect_collection = static_cast<s_platform_sound_playback_collection const *>(tag_get(SOUND_EFFECT_COLLECTION_TAG, sound_globals->sound_effect_collection_reference.index));
                    platform_playback = &static_cast<s_platform_sound_playback_named_definition const *>(tag_block_get_element_with_size(&sound_effect_collection->playback_collection, playback_index, sizeof(s_platform_sound_playback_named_definition)))->playback;
                }
            }
            break;
        case _game_sound_platform_playback_scenario:
            {
                scenario const * scenario = global_scenario_get();
                if (scenario->sound_effect_collection.index != NONE)
                {
                    long playback_index = playback_index_from_designator(playback_designator);
                    s_platform_sound_playback_collection const * sound_effect_collection = static_cast<s_platform_sound_playback_collection const *>(tag_get(SOUND_EFFECT_COLLECTION_TAG, scenario->sound_effect_collection.index));
                    platform_playback = &static_cast<s_platform_sound_playback_named_definition const *>(tag_block_get_element_with_size(&sound_effect_collection->playback_collection, playback_index, sizeof(s_platform_sound_playback_named_definition)))->playback;
                }
            }
            break;
        }
    }

    return platform_playback;
};

s_platform_sound_playback_definition const * game_sound_get_default_platform_playback_definition(long definition_index)
{
    mangled_ppc("?game_sound_get_default_platform_playback_definition@@YAPBUs_platform_sound_playback_definition@@J@Z");

    return game_sound_get_platform_playback_definition(definition_index, NONE);
};
