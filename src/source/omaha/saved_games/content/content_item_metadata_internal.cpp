#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\content\\content_item_metadata_internal.cpp"
/* ---------- headers */

#include <xtl.h>
#include <string.h>
#include <time.h>
#include "omaha\saved_games\content\content_item_metadata_internal.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game.h"
#include "omaha\game\game_options.h"
#include "omaha\interface\c_controller.h"
#include "omaha\saved_games\content\content_item_metadata.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// unsigned __int64 content_item_metadata_generate_uid(void);
// void content_item_metadata_set_from_game_options(struct s_content_item_metadata *, struct s_game_options const *);
// public: long c_game_engine_custom_variant::get_category_index(void) const;
// void content_item_metadata_set_from_current_game_options(struct s_content_item_metadata *);
// void content_item_metadata_initialize_history(struct s_content_item_history *, enum e_controller_index);
// public: void c_flags_no_init<enum e_content_item_author_flag, unsigned char, 1, struct s_default_enum_string_resolver>::clear(void);
// time;

unsigned __int64 content_item_metadata_generate_uid(void)
{
    mangled_ppc("?content_item_metadata_generate_uid@@YA_KXZ");

    unsigned __int64 uid;
    XNetRandom(reinterpret_cast<unsigned char *>(&uid), sizeof(uid));

    return uid;
};

void content_item_metadata_set_from_game_options(s_content_item_metadata * metadata, s_game_options const * options)
{
    mangled_ppc("?content_item_metadata_set_from_game_options@@YAXPAUs_content_item_metadata@@PBUs_game_options@@@Z");

    assert_tag_debug_untracked_jul_11_2011(37, metadata);
    assert_tag_debug_untracked_jul_11_2011(38, options);

    s_content_item_metadata * general = metadata;
    general->game_instance = options->game_instance;
    switch (options->game_mode)
    {
    case _game_mode_multiplayer:
        if (options->game_variant.get_game_engine_index() == _game_engine_type_sandbox)
        {
            general->gui_game_mode = _gui_game_mode_mapeditor;
        }
        else
        {
            general->gui_game_mode = _gui_game_mode_multiplayer;
        }
        break;
    case _game_mode_campaign:
        general->gui_game_mode = _gui_game_mode_campaign;
        break;
    case _game_mode_survival:
        general->gui_game_mode = _gui_game_mode_survival;
        break;
    }

    if (options->unknownFA50)
    {
        general->gui_game_mode = _gui_game_mode_theater;
    }

    general->game_mode = options->game_mode;
    general->game_engine_type = options->game_variant.get_game_engine_index();
    general->unknown2C = options->map_id;
    general->unknown30 = static_cast<char>(general->game_engine_type == _game_engine_type_megalo ? options->game_variant.get_custom_variant()->get_category_index() : NONE);

    if (options->unknownFA50)
    {
        general->gui_game_mode = _gui_game_mode_theater;
        metadata->unknown290 = options->unknownFA56;
    }

    if (options->game_mode == _game_mode_campaign)
    {
        s_content_item_campaign_metadata * campaign = &metadata->campaign;
        campaign->campaign_id = static_cast<char>(options->campaign_id);
        campaign->difficulty = static_cast<e_campaign_difficulty_level>(options->unknownF9CC);
        campaign->metagame_scoring = options->campaign_metagame_scoring;
        campaign->insertion_point = static_cast<char>(options->campaign_insertion_point);
        campaign->skulls = options->skulls.get_unsafe();
    }
    else if (options->game_mode == _game_mode_survival)
    {
        s_content_item_survival_metadata * survival = &metadata->survival;
        survival->difficulty = static_cast<e_campaign_difficulty_level>(options->unknownF9CC);
        survival->skulls = options->skulls.get_unsafe();
    }
};

void content_item_metadata_set_from_current_game_options(s_content_item_metadata * metadata)
{
    mangled_ppc("?content_item_metadata_set_from_current_game_options@@YAXPAUs_content_item_metadata@@@Z");

    s_game_options const * options = game_options_get();
    content_item_metadata_set_from_game_options(metadata, options);
};

void content_item_metadata_initialize_history(s_content_item_history * history, e_controller_index controller_index)
{
    mangled_ppc("?content_item_metadata_initialize_history@@YAXPAUs_content_item_history@@W4e_controller_index@@@Z");

    bool clear_author = true;
    history->timestamp = time(NULL);
    if (VALID_CONTROLLER(controller_index))
    {
        c_controller_interface * controller = controller_get(controller_index);
        if (controller->in_use())
        {
            history->author_id = controller->get_player_xuid();
            wchar_string_to_ascii_string(controller->get_display_name(), history->author_name, NUMBEROF(history->author_name), NULL);
            history->author_flags.set(_content_item_author_signed_in_to_live_bit, controller->is_signed_in_to_live());
            clear_author = false;
        }
    }

    if (clear_author)
    {
        history->author_id = 0;
        memset(history->author_name, 0, sizeof(history->author_name));
        history->author_flags.clear();
    }
};

