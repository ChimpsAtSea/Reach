#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_launch.cpp"
/* ---------- headers */

#include <stdio.h>
#include <string.h>
#include "omaha\game\game_launch.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_variant.h"
#include "omaha\game\game_options.h"
#include "omaha\main\main_game.h"
#include "omaha\saved_games\saved_film_manager.h"
#include "omaha\tag_files\files.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool game_options_get_launch_settings(struct s_game_options *, bool);
// public: s_game_options_launch_settings::s_game_options_launch_settings(void);
// bool game_launch_get_settings(struct s_game_options_launch_settings *);
// bool game_options_read_launch_settings_from_string(char const *, struct s_game_options_launch_settings *);
// bool game_launch_get_initial_script_name(class c_static_string<128> *);
// public: char * s_static_string<128>::copy_to(char *, unsigned int) const;

bool game_options_get_launch_settings(s_game_options * options, bool unused)
{
    mangled_ppc("?game_options_get_launch_settings@@YA_NPAUs_game_options@@_N@Z");

    assert_tag_debug_untracked_jul_11_2011(106, options);

    bool result = false;
    s_game_options_launch_settings settings;
    if (game_launch_get_settings(&settings))
    {
        game_options_new(options);
        csstrnzcpy(options->scenario_path, settings.scenario_path, sizeof(options->scenario_path));
        options->record_saved_film = saved_film_manager_should_record_film(options);
        options->unknownF9CC = settings.unknown104;
        options->game_mode = static_cast<e_game_mode>(settings.game_mode);
        switch (options->game_mode)
        {
        case _game_mode_campaign:
            {
                build_default_game_variant(&options->game_variant, _game_engine_type_campaign);
                game_load_variant_and_reset_map("campaign");
            }
            break;
        case _game_mode_survival:
            {
                build_default_game_variant(&options->game_variant, _game_engine_type_survival);
                game_load_variant_and_reset_map("firefight");
            }
            break;
        case _game_mode_multiplayer:
            {
                build_default_game_variant(&options->game_variant, _game_engine_type_megalo);
            }
            break;
        }

        settings.initial_script_name.copy_to(options->initial_script_name, sizeof(options->initial_script_name));
        game_options_setup_default_players(1, options);
        result = true;

        if (TEST_BIT(settings.flags, 1))
        {
            s_file_reference launch_file;
            file_reference_create_from_path(&launch_file, "d:\\launch_tags.txt", false);
            file_delete(&launch_file);
        }
    }

    return result;
};

s_game_options_launch_settings::s_game_options_launch_settings()
{
    mangled_ppc("??0s_game_options_launch_settings@@QAA@XZ");
};

bool game_launch_get_settings(s_game_options_launch_settings * out_settings)
{
    mangled_ppc("?game_launch_get_settings@@YA_NPAUs_game_options_launch_settings@@@Z");

    bool result = false;
    FILE * launch_tags_file = fopen("d:\\launch_tags.txt", "r");
    if (launch_tags_file)
    {
        c_static_string<1024> launch_string;
        if (fread_s(launch_string.get_buffer(), 1024, 1, 1024, launch_tags_file))
        {
            s_game_options_launch_settings settings;
            bool parsed = game_options_read_launch_settings_from_string(launch_string, &settings);
            if (parsed)
            {
                *out_settings = settings;
                result = true;
            }
        }
        fclose(launch_tags_file);
    }

    return result;
};

bool game_options_read_launch_settings_from_string(char const * string, s_game_options_launch_settings * out_settings)
{
    mangled_ppc("?game_options_read_launch_settings_from_string@@YA_NPBDPAUs_game_options_launch_settings@@@Z");

    bool parsed = false;
    s_game_options_launch_settings settings;
    if (sscanf_s(string, "%d\n%s\n%d\n%d\n%d\n%s\n%s\n",
        &settings.unknown0,
        settings.scenario_path.get_buffer(), 256,
        &settings.unknown104,
        &settings.game_mode,
        &settings.flags,
        settings.unknown110.get_buffer(), 128,
        settings.initial_script_name.get_buffer(), 128))
    {
        if (settings.unknown110.is_equal("-"))
        {
            settings.unknown110.clear();
        }
        if (settings.initial_script_name.is_equal("-"))
        {
            settings.initial_script_name.clear();
        }
        *out_settings = settings;
        parsed = true;
    }

    return parsed;
};

bool game_launch_get_initial_script_name(c_static_string<128> * out_initial_script_name)
{
    mangled_ppc("?game_launch_get_initial_script_name@@YA_NPAV?$c_static_string@$0IA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(164, out_initial_script_name);

    bool result = false;

    return result;
};


