#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_player_globals.cpp"
/* ---------- headers */

#include "omaha\game\game_player_globals.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char const * global_player_character_type_names[k_player_character_type_count] =
{
    "spartan",
    "elite",
    "monitor",
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_string_list_definition global_player_character_enum; // "?global_player_character_enum@@3Us_string_list_definition@@A"
// struct s_tag_block_definition player_information_block; // "?player_information_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition player_information_block_struct_definition; // "?player_information_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition player_representation_block; // "?player_representation_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition player_representation_block_struct_definition; // "?player_representation_block_struct_definition@@3Us_tag_struct_definition@@A"

// char * format_player_character_block_names(long, __int64, struct s_tag_block *, long, char *, long);
// void prune_player_information(struct s_game_globals_player_information *);
// void prune_player_representation(struct s_game_globals_player_representation *);

char * format_player_character_block_names(long tag_index, __int64 tag_group, s_tag_block * block, long block_index, char * buffer, long buffer_length)
{
    mangled_ppc("?format_player_character_block_names@@YAPADJ_JPAUs_tag_block@@JPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(40, VALID_INDEX(block_index, k_player_character_type_count));

    return csstrnzcpy(buffer, global_player_character_type_names[block_index], buffer_length);
};

void prune_player_information(s_game_globals_player_information * player_information)
{
    mangled_ppc("?prune_player_information@@YAXPAUs_game_globals_player_information@@@Z");

    tag_reference_clear(&player_information->coop_countdown_sound);
    tag_reference_clear(&player_information->coop_respawn_sound);
    tag_reference_clear(&player_information->coop_respawn_effect);
    tag_reference_clear(&player_information->hologram_death_effect);
    for (long index = 0; index < 2; index++)
    {
        tag_reference_clear(&player_information->night_vision_sounds[index]);
    }
};

void prune_player_representation(s_game_globals_player_representation * player_representation)
{
    mangled_ppc("?prune_player_representation@@YAXPAUs_game_globals_player_representation@@@Z");

    tag_reference_clear(&player_representation->chud);
    tag_reference_clear(&player_representation->first_person_hands);
    tag_reference_clear(&player_representation->first_person_body);
    tag_reference_clear(&player_representation->third_person_unit);
    tag_reference_clear(&player_representation->binoculars_zoom_in_sound);
    tag_reference_clear(&player_representation->binoculars_zoom_out_sound);
};

