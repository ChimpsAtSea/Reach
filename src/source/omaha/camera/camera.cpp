#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\camera\\camera.cpp"
/* ---------- headers */

#include "omaha\camera\camera.h"
#include "omaha\camera\observer.h"
#include "omaha\cseries\cseries.h"
#include "omaha\editor\editor_stubs.h"
#include "omaha\input\input.h"
#include "omaha\interface\cui\cui_screen_manager.h"
#include "omaha\interface\debug_menu\debug_menu_main.h"
#include "omaha\interface\gui_screens\scoreboard\gui_screen_scoreboard.h"
#include "omaha\interface\user_interface_mapping.h"
#include "omaha\main\main.h"
#include "omaha\objects\objects.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

char const * global_camera_mode_names[k_number_of_camera_modes] =
{
    "following",
    "orbiting",
    "flying",
    "first person",
    "dead",
    "static",
    "scripted",
    "authored",
    "respawning",
    "animated trick",
    "tracked target",
    "sandbox",
    "space_fighter"
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **global_camera_mode_names; // "?global_camera_mode_names@@3PAPBDA"

// bool camera_input_inhibited(enum e_controller_index);
// public: class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> c_cui_screen_manager::get_active_category_flags(enum e_window_index) const;
// public: class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> c_cui_screen_manager::get_closing_category_flags(enum e_window_index) const;
// public: c_camera::c_camera(void);
// public: void c_camera::pre_update(void);
// public: void c_camera::post_update(struct s_observer_command *);
// public: void c_camera::set_next_move_instantly(void);
// public: virtual long c_camera::get_target(void) const;
// public: virtual void c_camera::set_target(long);
// public: virtual void c_camera::handle_deleted_player(long);
// public: virtual void c_camera::handle_deleted_object(long);
// public: virtual void c_camera::assemble_screen_effects(class c_global_screen_effect_state *);
// public: void c_flags_no_init<enum c_camera::e_base_camera_flags, long, 1, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum c_camera::e_base_camera_flags, long, 1, struct s_default_enum_string_resolver>::test(enum c_camera::e_base_camera_flags) const;
// public: void c_flags_no_init<enum c_camera::e_base_camera_flags, long, 1, struct s_default_enum_string_resolver>::set(enum c_camera::e_base_camera_flags, bool);
// public: bool c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::is_clear(void) const;
// public: void c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::set_all(void);
// public: void c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::set(enum e_cui_screen_category, bool);
// public: class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::operator&(class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> const &) const;
// public: class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::operator|(class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> const &) const;
// public: static bool c_flags_no_init<enum c_camera::e_base_camera_flags, long, 1, struct s_default_enum_string_resolver>::valid_bit(enum c_camera::e_base_camera_flags);
// private: static long c_flags_no_init<enum c_camera::e_base_camera_flags, long, 1, struct s_default_enum_string_resolver>::flag_size_type(enum c_camera::e_base_camera_flags);
// public: static class c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver> c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::make_mask_from_range(enum e_cui_screen_category, enum e_cui_screen_category);
// public: void c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::set_unsafe(unsigned long);
// private: static unsigned long c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// public: bool c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::valid(void) const;
// private: static unsigned long c_flags_no_init<enum e_cui_screen_category, unsigned long, 18, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_cui_screen_category);

bool camera_input_inhibited(e_controller_index controller_index)
{
    mangled_ppc("?camera_input_inhibited@@YA_NW4e_controller_index@@@Z");

    bool camera_input_inhibited = false;
    c_cui_screen_manager * manager = cui_screen_manager_get();
    e_window_index window_index = user_interface_get_window_for_controller(controller_index);

    c_cui_screen_category_flags active_categories = manager->get_active_category_flags(_console_window) | manager->get_active_category_flags(window_index);
    c_cui_screen_category_flags closing_screen_categories = manager->get_closing_category_flags(_console_window) | manager->get_closing_category_flags(window_index);

    c_cui_screen_category_flags blocking_screen_categories;
    blocking_screen_categories.set_all();
    blocking_screen_categories.set(_cui_screen_category4, false);
    blocking_screen_categories.set(_cui_screen_category5, false);
    blocking_screen_categories.set(_cui_screen_category8, false);
    blocking_screen_categories.set(_cui_screen_category1, c_gui_screen_scoreboard::is_scoreboard_interactive(controller_index));
    blocking_screen_categories.set(_cui_screen_category14, false);

    c_cui_screen_category_flags closing_blocking_categories = blocking_screen_categories;
    closing_blocking_categories.set(_cui_screen_category0, false);

    camera_input_inhibited |= !((active_categories & blocking_screen_categories) | (closing_screen_categories & closing_blocking_categories)).is_clear();
    camera_input_inhibited |= main_events_pending();
    camera_input_inhibited |= game_in_editor() && (input_get_mouse_state() == NULL || editor_input_inhibited());
    camera_input_inhibited |= debug_menu_get_active();

    return camera_input_inhibited;
};

c_camera::c_camera()
{
    mangled_ppc("??0c_camera@@QAA@XZ");

    m_base_camera_flags.clear();
    m_target_object_index = NONE;
    m_move_instant_ticks = 0;
};

void c_camera::pre_update()
{
    mangled_ppc("?pre_update@c_camera@@QAAXXZ");

    get_target();
};

void c_camera::post_update(s_observer_command * result)
{
    mangled_ppc("?post_update@c_camera@@QAAXPAUs_observer_command@@@Z");

    if (m_base_camera_flags.test(_move_instantly))
    {
        result->timer = 0.0f;
        long move_instant_ticks = m_move_instant_ticks - 1;
        m_move_instant_ticks = move_instant_ticks;
        if (move_instant_ticks == 0)
        {
            m_base_camera_flags.set(_move_instantly, false);
        }
    }
};

void c_camera::set_next_move_instantly()
{
    mangled_ppc("?set_next_move_instantly@c_camera@@QAAXXZ");

    m_move_instant_ticks = 5;
    m_base_camera_flags.set(_move_instantly, true);
};

long c_camera::get_target() const
{
    mangled_ppc("?get_target@c_camera@@UBAJXZ");

    return m_target_object_index;
};

void c_camera::set_target(long object_index)
{
    mangled_ppc("?set_target@c_camera@@UAAXJ@Z");

    assert_tag_debug_untracked_jul_11_2011(145, object_index==NONE || object_get(object_index)!=NULL);
    m_target_object_index = object_index;
};

void c_camera::handle_deleted_player(long player_index)
{
    mangled_ppc("?handle_deleted_player@c_camera@@UAAXJ@Z");
};

void c_camera::handle_deleted_object(long object_index)
{
    mangled_ppc("?handle_deleted_object@c_camera@@UAAXJ@Z");

    if (m_target_object_index == object_index)
    {
        m_target_object_index = NONE;
    }
};

void c_camera::assemble_screen_effects(c_global_screen_effect_state * screen_effect_state)
{
    mangled_ppc("?assemble_screen_effects@c_camera@@UAAXPAVc_global_screen_effect_state@@@Z");
};
