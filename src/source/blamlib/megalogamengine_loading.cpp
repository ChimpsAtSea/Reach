/* ---------- headers */

#include "blamlib\megalogamengine_loading.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\memory\bitstream.h"
#include "omaha\tag_files\files.h"
#include "omaha\text\unicode.h"
#include "omaha\game\game.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_megalo.h"
#include "omaha\game\game_variant.h"
#include "omaha\game\megalogamengine\megalogamengine_internal.h"
#include "omaha\networking\logic\network_session_parameter_interface.h"
#include "blamlib\megalogamengine.h"
#include "omaha\game\game_engine_variant.h"
#include "omaha\networking\logic\storage\network_storage_files.h"
#include "omaha\networking\logic\storage\game\network_storage_matchmaking_file_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

static char g_megalogamengine_pending_variant_filename[256];

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void megalogamengine_load_binary_game_engine_from_file(char const *);
// void megalogamengine_loading_initialize_for_new_round(void);
// bool megalogamengine_load_binary_variant(char const *, class c_game_engine_custom_variant *);
// bool megalogamengine_load_binary_variant_full_filename(char const *, class c_game_engine_custom_variant *);
// bool load_variant_from_file(struct s_file_reference *, class c_game_engine_custom_variant *);
// bool megalogamengine_try_and_load_variant(char const *, class c_game_variant *);
// void megalo_convert_variant_files(char **);
// public: c_static_wchar_string<128>::c_static_wchar_string<128>(char const *);
// char * file_reference_get_name<260>(struct s_file_reference const *, unsigned long, char (&)[260]);
// char * file_reference_get_directory<260>(struct s_file_reference const *, char (&)[260]);

void megalogamengine_load_binary_game_engine_from_file(char const * filename)
{
    mangled_ppc("?megalogamengine_load_binary_game_engine_from_file@@YAXPBD@Z");

    if (game_in_progress())
    {
        if (game_is_ui_shell())
        {
            c_game_variant game_variant;
            game_variant.set_game_engine_index(_game_engine_type_megalo);
            c_game_engine_custom_variant * custom_variant = game_variant.get_custom_variant_writeable();
            megalogamengine_load_binary_variant(filename, custom_variant);
            if (ustrlen(custom_variant->get_name()) == 0)
            {
                c_static_wchar_string<128> variant_name(filename);
                custom_variant->set_name(variant_name.get_string());
            }

            if (!network_squad_session_set_game_variant(&game_variant))
            {
                event_wrapped(_event_error, "megalogamengine:failed to set network session game variant");
            }
        }
        else if (game_is_multiplayer())
        {
            if (get_current_game_engine_index() == _game_engine_type_megalo || get_current_game_engine_index() == _game_engine_type_sandbox)
            {
                csnzprintf(g_megalogamengine_pending_variant_filename, sizeof(g_megalogamengine_pending_variant_filename), filename);
                game_engine_end_round_with_winner(NONE, false, _game_engine_round_end_editor_reset);
            }
            else
            {
                event_wrapped(_event_error, "megalogamengine:tried to load a megalo variant in a non-megalo game");
            }
        }
    }
    else
    {
        csnzprintf(g_megalogamengine_pending_variant_filename, sizeof(g_megalogamengine_pending_variant_filename), filename);
    }
};

void megalogamengine_loading_initialize_for_new_round(void)
{
    mangled_ppc("?megalogamengine_loading_initialize_for_new_round@@YAXXZ");

    if (g_megalogamengine_pending_variant_filename[0])
    {
        if (get_current_game_engine_index() == _game_engine_type_megalo || get_current_game_engine_index() == _game_engine_type_sandbox)
        {
            megalogamengine_load_binary_variant(g_megalogamengine_pending_variant_filename, const_cast<c_game_engine_custom_variant *>(get_custom_game_engine_variant()));
            megalogamengine_initialize_for_new_script();
        }
        g_megalogamengine_pending_variant_filename[0] = 0;
    }
};

bool megalogamengine_load_binary_variant(char const * filename, c_game_engine_custom_variant * variant)
{
    mangled_ppc("?megalogamengine_load_binary_variant@@YA_NPBDPAVc_game_engine_custom_variant@@@Z");

    char full_filename[256];
    csnzprintf(full_filename, sizeof(full_filename), "%s.mglo", filename);
    return megalogamengine_load_binary_variant_full_filename(full_filename, variant);
};

bool megalogamengine_load_binary_variant_full_filename(char const * filename, c_game_engine_custom_variant * variant)
{
    mangled_ppc("?megalogamengine_load_binary_variant_full_filename@@YA_NPBDPAVc_game_engine_custom_variant@@@Z");

    bool success = true;
    c_debug_output_path debug_output_path;
    char path[256];
    s_file_reference file_reference;
    csnzprintf(path, sizeof(path), "%s%s\\%s", debug_output_path.get_root(), k_megalogamengine_directory, filename);
    file_reference_create_from_path(&file_reference, path, false);
    if (!load_variant_from_file(&file_reference, variant))
    {
        success = false;
        event_wrapped(_event_error, "megalogamengine:failed to open file %s", filename);
    }
    variant->validate();

    return success;
};

bool load_variant_from_file(s_file_reference * file, c_game_engine_custom_variant * variant)
{
    mangled_ppc("?load_variant_from_file@@YA_NPAUs_file_reference@@PAVc_game_engine_custom_variant@@@Z");

    bool success = false;
    unsigned char file_buffer[0x5000];
    unsigned long size;
    variant->initialize();
    if (file_read_into_buffer(file, file_buffer, sizeof(file_buffer)) && file_get_size(file, &size))
    {
        c_bitstream bitstream(file_buffer, size);
        bitstream.begin_reading();
        variant->decode(&bitstream);
        bitstream.finish_reading();
        success = !bitstream.error_occurred();
    }

    return success;
};

bool megalogamengine_try_and_load_variant(char const * filename, c_game_variant * game_variant)
{
    mangled_ppc("?megalogamengine_try_and_load_variant@@YA_NPBDPAVc_game_variant@@@Z");

    bool success = false;
    c_debug_output_path debug_output_path;
    char path[256];
    s_file_reference file_reference;
    csnzprintf(path, sizeof(path), "%s%s\\%s.mglo", debug_output_path.get_root(), k_megalogamengine_directory, filename);
    file_reference_create_from_path(&file_reference, path, false);
    if (file_exists(&file_reference))
    {
        c_game_variant loaded_game_variant;
        loaded_game_variant.set_game_engine_index(_game_engine_type_megalo);
        if (megalogamengine_load_binary_variant(filename, loaded_game_variant.get_custom_variant_writeable()))
        {
            game_variant->copy_from_and_validate(&loaded_game_variant);
            success = true;
        }
    }

    return success;
};

void megalo_convert_variant_files(char ** arguments)
{
    mangled_ppc("?megalo_convert_variant_files@@YAXPAPAD@Z");

    s_find_file_data find_data;
    s_file_reference file;
    s_file_reference source_directory;
    s_file_reference destination_directory;
    file_reference_create_from_path(&source_directory, arguments[0], true);
    file_reference_create_from_path(&destination_directory, arguments[1], true);
    find_files_start_with_search_spec(&find_data, 0, &source_directory, "*.mglo");
    while (find_files_next(&find_data, &file, NULL))
    {
        c_game_variant game_variant;
        build_default_game_variant(&game_variant, _game_engine_type_megalo);
        if (!load_variant_from_file(&file, game_variant.get_custom_variant_writeable()))
        {
            event_wrapped(_event_critical, "failed to load megalo file!");
        }
        else
        {
            unsigned char packed_buffer[0x5000];
            long data_size = multiplayer_game_hopper_pack_game_variant(packed_buffer, sizeof(packed_buffer), &game_variant);
            char output_filename[260] = {0};
            char filename[260];
            file_reference_get_name(&file, FLAG(_name_filename_bit), filename);
            file_reference_get_directory(&destination_directory, output_filename);
            csnzappendf(output_filename, sizeof(output_filename), "\\%s_%03u.bin", filename, 54);
            if (!create_configuration_file(output_filename, packed_buffer, data_size))
            {
                event_wrapped(_event_critical, "failed to write megalo variant file!");
            }
        }
    }
    find_files_end(&find_data);
};
