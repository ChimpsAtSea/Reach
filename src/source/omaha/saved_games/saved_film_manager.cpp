#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\saved_film_manager.cpp"
/* ---------- headers */

#include "omaha\saved_games\saved_film_manager.h"
#include <xtl.h>
#include <string.h>
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "omaha\cseries\cseries.h"
#include "omaha\input\controllers.h"
#include "omaha\saved_games\content\content.h"
#include "omaha\saved_games\saved_game_files.h"
#include "omaha\text\unicode.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: s_saved_film_reference::s_saved_film_reference(void);
// public: s_saved_film_reference::s_saved_film_reference(char const *, wchar_t const *);
// public: s_saved_film_reference::s_saved_film_reference(enum e_controller_index, enum e_content_item_type, struct s_content_item_platform_handle const *);
// public: s_saved_film_description::s_saved_film_description(void);
// bool saved_film_reference_get_filename(struct s_saved_film_reference const *, class c_static_string<256> *);
// wchar_t const * saved_film_reference_get_display_name(struct s_saved_film_reference const *);
// void saved_film_reference_set_display_name(struct s_saved_film_reference *, wchar_t const *);

s_saved_film_reference::s_saved_film_reference(void)
{
    mangled_ppc("??0s_saved_film_reference@@QAA@XZ");

    type = _saved_film_reference_type_none;
    memset(&file, 0, sizeof(file));
    memset(&content_item, 0, sizeof(content_item));
};

s_saved_film_reference::s_saved_film_reference(char const * filename, wchar_t const * display_name)
{
    mangled_ppc("??0s_saved_film_reference@@QAA@PBDPB_W@Z");

    type = _saved_film_reference_type_file;
    assert_tag_debug_untracked_jul_11_2011(34, filename);

    memset(&content_item, 0, sizeof(content_item));
    csstrnzcpy(file.filename, filename, sizeof(file.filename));
    memset(file.display_name, 0, sizeof(file.display_name));
    if (display_name)
    {
        ustrnzcpy(file.display_name, display_name, NUMBEROF(file.display_name));
    }
};

s_saved_film_reference::s_saved_film_reference(e_controller_index controller_index, e_content_item_type content_item_type, s_content_item_platform_handle const * platform_handle)
{
    mangled_ppc("??0s_saved_film_reference@@QAA@W4e_controller_index@@W4e_content_item_type@@PBUs_content_item_platform_handle@@@Z");

    type = _saved_film_reference_type_content_item;
    assert_tag_debug_untracked_jul_11_2011(54, platform_handle);

    memset(&file, 0, sizeof(file));
    content_item.controller_index = controller_index;
    content_item.content_item_type = content_item_type;
    *content_item.platform_handle.get() = *platform_handle;
};

s_saved_film_description::s_saved_film_description(void)
{
    mangled_ppc("??0s_saved_film_description@@QAA@XZ");

    unknown204 = 0;
    unknown208 = NONE;
    unknown20C = NONE;
    unknown210 = 0;
    unknown214 = 0;
    unknown218 = 0;
    unknown21C = 0;
    unknown220 = 0;
};

bool saved_film_reference_get_filename(s_saved_film_reference const * reference, c_static_string<256> * out_filename)
{
    mangled_ppc("?saved_film_reference_get_filename@@YA_NPBUs_saved_film_reference@@PAV?$c_static_string@$0BAA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(79, reference);
    assert_tag_debug_untracked_jul_11_2011(80, out_filename);

    bool result = false;
    if (reference->type == _saved_film_reference_type_file)
    {
        out_filename->set(reference->file.filename);
        result = true;
    }
    else if (reference->type == _saved_film_reference_type_content_item)
    {
        s_static_string<256> extension;
        extension.set(saved_game_files_get_filename_for_type(reference->content_item.content_item_type));
        s_static_string<256> filename;
        content_build_filename(reference->content_item.platform_handle.get_const(), &extension, &filename);
        out_filename->set(filename.get_string());
        result = true;
    }

    return result;
};

wchar_t const * saved_film_reference_get_display_name(s_saved_film_reference const * reference)
{
    mangled_ppc("?saved_film_reference_get_display_name@@YAPB_WPBUs_saved_film_reference@@@Z");

    assert_tag_debug_untracked_jul_11_2011(108, reference);

    wchar_t const * display_name = NULL;
    if (reference->type == _saved_film_reference_type_file)
    {
        display_name = reference->file.display_name;
    }
    else if (reference->type == _saved_film_reference_type_content_item)
    {
        display_name = reference->content_item.platform_handle.get_const()->content_data.get_const()->szDisplayName;
    }

    return display_name;
};

void saved_film_reference_set_display_name(s_saved_film_reference * reference, wchar_t const * display_name)
{
    mangled_ppc("?saved_film_reference_set_display_name@@YAXPAUs_saved_film_reference@@PB_W@Z");

    assert_tag_debug_untracked_jul_11_2011(130, reference);
    assert_tag_debug_untracked_jul_11_2011(131, display_name);

    if (reference->type == _saved_film_reference_type_file)
    {
        memset(reference->file.display_name, 0, sizeof(reference->file.display_name));
        ustrnzcpy(reference->file.display_name, display_name, NUMBEROF(reference->file.display_name));
    }
    else if (reference->type == _saved_film_reference_type_content_item)
    {
        memset(reference->content_item.platform_handle.get()->content_data.get()->szDisplayName, 0, sizeof(reference->content_item.platform_handle.get()->content_data.get()->szDisplayName));
        ustrnzcpy(reference->content_item.platform_handle.get()->content_data.get()->szDisplayName, display_name, NUMBEROF(reference->content_item.platform_handle.get()->content_data.get()->szDisplayName));
    }
};

