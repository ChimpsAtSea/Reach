#ifndef __SAVED_FILM_MANAGER_H__
#define __SAVED_FILM_MANAGER_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\saved_games\content\content.h"

/* ---------- constants */

// names unverified; values per the s_saved_film_reference constructors
enum e_saved_film_reference_type
{
    _saved_film_reference_type_none = 0,
    _saved_film_reference_type_file,
    _saved_film_reference_type_content_item,

    k_saved_film_reference_type_count
};

/* ---------- definitions */

enum e_controller_index;
enum e_content_item_type;
struct s_game_options;

struct s_saved_film_reference_file
{
    char filename[256]; // 0x0
    wchar_t display_name[128]; // 0x100
};
static_assert(sizeof(s_saved_film_reference_file) == 0x200, "s_saved_film_reference_file");

struct s_saved_film_reference_content_item
{
    e_controller_index controller_index; // 0x0
    e_content_item_type content_item_type; // 0x4
    c_opaque_data<s_content_item_platform_handle, 0x134, 4> platform_handle; // 0x8
};
static_assert(sizeof(s_saved_film_reference_content_item) == 0x13C, "s_saved_film_reference_content_item");

struct s_saved_film_reference
{
    s_saved_film_reference(void);
    s_saved_film_reference(char const * filename, wchar_t const * display_name);
    s_saved_film_reference(e_controller_index controller_index, e_content_item_type content_item_type, s_content_item_platform_handle const * platform_handle);

    long type; // 0x0 e_saved_film_reference_type
    union
    {
        s_saved_film_reference_file file;
        s_saved_film_reference_content_item content_item;
    }; // 0x4
};
static_assert(sizeof(s_saved_film_reference) == 0x204, "s_saved_film_reference");

// $TODO: only the fields set by the constructor are known; total size unverified (IDA type is the stale H3 layout)
struct s_saved_film_description : s_saved_film_reference
{
    s_saved_film_description(void);

    long unknown204; // 0x204
    long unknown208; // 0x208 NONE
    long unknown20C; // 0x20C NONE
    long unknown210; // 0x210
    long unknown214; // 0x214
    long unknown218; // 0x218
    long unknown21C; // 0x21C
    long unknown220; // 0x220
};

/* ---------- prototypes */

// f i (owned by life_cycle_handler_in_game.obj); always false in this build
inline bool saved_film_manager_should_record_film(s_game_options const * options)
{
    return false;
};

struct s_simulation_camera_update;

// f i (owned by authored_camera.obj); no camera updates in this build
inline unsigned long saved_film_manager_get_simulation_camera_update_mask(void)
{
    mangled_ppc("?saved_film_manager_get_simulation_camera_update_mask@@YAKXZ");

    return 0;
};

// f i (owned by authored_camera.obj); no camera updates in this build
inline bool saved_film_manager_get_simulation_camera_updates(long user_index, s_simulation_camera_update * camera_update)
{
    mangled_ppc("?saved_film_manager_get_simulation_camera_updates@@YA_NJPAUs_simulation_camera_update@@@Z");

    return false;
};

bool saved_film_reference_get_filename(s_saved_film_reference const * reference, c_static_string<256> * out_filename);
wchar_t const * saved_film_reference_get_display_name(s_saved_film_reference const * reference);
void saved_film_reference_set_display_name(s_saved_film_reference * reference, wchar_t const * display_name);
long saved_film_manager_get_current_tick_estimate(void); // $TODO inline in the target (f i, rasterizer_globals.obj); body not reversed yet

/* ---------- globals */

/* ---------- public code */

#endif // __SAVED_FILM_MANAGER_H__

