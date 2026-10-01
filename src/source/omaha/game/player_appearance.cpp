#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\player_appearance.cpp"
/* ---------- headers */

#include "omaha\game\player_appearance.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\player_model_customization.h"
#include "omaha\math\random_math.h"
#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

e_player_model_customization_area g_force_model_area_override[k_player_model_customization_area_count];
bool g_randomize_player_appearance;
bool g_force_model_area[k_player_model_customization_area_count];

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// enum e_player_model_customization_area *g_force_model_area_override; // "?g_force_model_area_override@@3PAW4e_player_model_customization_area@@A"
// bool g_randomize_player_appearance; // "?g_randomize_player_appearance@@3_NA"
// bool *g_force_model_area; // "?g_force_model_area@@3PA_NA"

// void player_appearance_initialize(struct s_player_appearance *);
// bool player_appearance_valid(struct s_player_appearance const *);
// enum e_player_model_customization_area & operator++(enum e_player_model_customization_area &);
// enum e_player_non_model_customization & operator++(enum e_player_non_model_customization &);
// void player_appearance_randomize(struct s_player_appearance *);
// void player_appearance_override_for_debug(struct s_player_appearance *);
// void player_appearance_force_model_area(long, long);
// public: s_player_customization_description::s_player_customization_description(enum e_player_model_customization_area);
// void player_appearance_force_model_area_disable(long);
// public: class c_enum_no_init<enum e_player_color_index, char, -1, 32, struct s_default_enum_string_resolver> & c_enum_no_init<enum e_player_color_index, char, -1, 32, struct s_default_enum_string_resolver>::operator=(enum e_player_color_index);
// public: void c_flags_no_init<enum e_emblem_info_flags, unsigned char, 3, struct s_default_enum_string_resolver>::set(enum e_emblem_info_flags, bool);

void player_appearance_initialize(s_player_appearance * player_appearance)
{
    mangled_ppc("?player_appearance_initialize@@YAXPAUs_player_appearance@@@Z");

    memset(player_appearance, 0, sizeof(*player_appearance));
};

bool player_appearance_valid(s_player_appearance const * player_appearance)
{
    mangled_ppc("?player_appearance_valid@@YA_NPBUs_player_appearance@@@Z");

    bool valid = true;
    for (unsigned long change_color_index = 0; change_color_index < NUMBEROF(player_appearance->change_color_index); change_color_index++)
    {
        valid = valid && player_appearance->change_color_index[change_color_index].in_range();
    }

    valid = valid && VALID_INDEX(player_appearance->player_model_choice, k_player_model_choice_count);
    valid = valid && VALID_INDEX(player_appearance->emblem_info.foreground_emblem_index, k_emblem_foreground_index_count);
    valid = valid && VALID_INDEX(player_appearance->emblem_info.background_emblem_index, k_emblem_background_index_count);
    for (e_player_model_customization_area area = _player_model_customization_area_first; area < NUMBEROF(player_appearance->model_area_selections); ++area)
    {
        valid = valid && (player_appearance->model_area_selections[area] == NONE || VALID_INDEX(player_appearance->model_area_selections[area], k_maximum_number_of_model_customization_selections_per_area));
    }
    for (e_player_non_model_customization customization = _player_non_model_customization_first; customization < NUMBEROF(player_appearance->non_model_selections); ++customization)
    {
        valid = valid && (player_appearance->non_model_selections[customization] == NONE || VALID_INDEX(player_appearance->non_model_selections[customization], k_maximum_number_of_model_customization_selections_per_area));
    }

    valid = valid && player_appearance->emblem_info.emblem_info_flags.valid();
    valid = valid && VALID_INDEX(player_appearance->emblem_info.primary_color_index, k_player_color_index_count);
    valid = valid && VALID_INDEX(player_appearance->emblem_info.secondary_color_index, k_player_color_index_count);
    valid = valid && VALID_INDEX(player_appearance->emblem_info.background_color_index, k_player_color_index_count);
    valid = valid && !player_appearance->emblem_info.pad;

    return valid;
};

void player_appearance_randomize(s_player_appearance * player_appearance)
{
    mangled_ppc("?player_appearance_randomize@@YAXPAUs_player_appearance@@@Z");

    s_player_model_customization_globals_definition const * customization_globals = customization_globals_try_and_get();
    assert_tag_debug_untracked_jul_11_2011(94, player_appearance_valid(player_appearance));

    if (customization_globals != NULL)
    {
        for (unsigned long change_color_index = 0; change_color_index < NUMBEROF(player_appearance->change_color_index); change_color_index++)
        {
            player_appearance->change_color_index[change_color_index] = static_cast<e_player_color_index>(_random_range(get_random_seed_address(), "player-model-customization-randomize-change-color-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 100, 0, k_player_color_index_count));
        }

        player_appearance->player_model_choice = static_cast<e_player_model_choice>(_random_range(get_random_seed_address(), "player-model-customization-randomize-model", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 103, 0, k_player_model_choice_count));
        player_appearance->emblem_info.foreground_emblem_index = static_cast<unsigned char>(_random_range(get_random_seed_address(), "player-model-customization-randomize-foreground-emblem-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 104, 0, k_emblem_foreground_index_count));
        player_appearance->emblem_info.background_emblem_index = static_cast<unsigned char>(_random_range(get_random_seed_address(), "player-model-customization-randomize-background-emblem-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 105, 0, k_emblem_background_index_count));

        for (e_player_model_customization_area area = _player_model_customization_area_first; area < NUMBEROF(player_appearance->model_area_selections); area++)
        {
            player_appearance->model_area_selections[area] = static_cast<char>(_random_range(get_random_seed_address(), "player-model-customization-randomize-model-area", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 114, 0, k_maximum_number_of_model_customization_selections_per_area));
        }

        for (e_player_non_model_customization customization = _player_non_model_customization_first; customization < NUMBEROF(player_appearance->non_model_selections); customization++)
        {
            player_appearance->non_model_selections[customization] = static_cast<char>(_random_range(get_random_seed_address(), "player-model-customization-randomize-non-model-area", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 124, 0, k_maximum_number_of_model_customization_selections_per_area));
        }

        for (long flag_index = 0; flag_index < k_emblem_info_flags_count; flag_index++)
        {
            player_appearance->emblem_info.emblem_info_flags.set(static_cast<e_emblem_info_flags>(flag_index), _random_boolean(get_random_seed_address(), "player-model-customization-randomize-emblem-flag", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 129));
        }

        player_appearance->emblem_info.primary_color_index = static_cast<e_player_color_index>(_random_range(get_random_seed_address(), "player-model-customization-randomize-primary-color-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 132, 0, k_player_color_index_count));
        player_appearance->emblem_info.secondary_color_index = static_cast<e_player_color_index>(_random_range(get_random_seed_address(), "player-model-customization-randomize-secondary-color-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 133, 0, k_player_color_index_count));
        player_appearance->emblem_info.background_color_index = static_cast<e_player_color_index>(_random_range(get_random_seed_address(), "player-model-customization-randomize-background-color-index", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 134, 0, k_player_color_index_count));
        player_appearance->flags.set(_player_appearance_flag_female_voice, _random_boolean(get_random_seed_address(), "player-model-customization-randomize-female-voice", __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, 136));
    }

    assert_tag_debug_untracked_jul_11_2011(140, player_appearance_valid(player_appearance));
};

void player_appearance_override_for_debug(s_player_appearance * player_appearance)
{
    mangled_ppc("?player_appearance_override_for_debug@@YAXPAUs_player_appearance@@@Z");

    if (g_randomize_player_appearance)
    {
        player_appearance_randomize(player_appearance);
    }

    for (e_player_model_customization_area area = _player_model_customization_area_first; area < NUMBEROF(g_force_model_area); area++)
    {
        if (g_force_model_area[area])
        {
            player_appearance->model_area_selections[area] = static_cast<char>(g_force_model_area_override[area]);
        }
    }
};

void player_appearance_force_model_area(long area, long selection)
{
    mangled_ppc("?player_appearance_force_model_area@@YAXJJ@Z");

    s_player_customization_description description(static_cast<e_player_model_customization_area>(area));
    g_force_model_area_override[area] = static_cast<e_player_model_customization_area>(player_model_customization_get_player_customization_selection_index(&description, selection));
    g_force_model_area[area] = true;
};

// the target resolved this g_force_model_area reference without a relocation (lis 0x8636 / subi), so 99.29% is the ceiling
void player_appearance_force_model_area_disable(long area)
{
    mangled_ppc("?player_appearance_force_model_area_disable@@YAXJ@Z");

    g_force_model_area[area] = false;
};
