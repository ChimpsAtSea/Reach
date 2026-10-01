#pragma once
#ifndef __USER_INTERFACE_MESSAGES_H__
#define __USER_INTERFACE_MESSAGES_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\input\controllers.h"

/* ---------- constants */

enum e_ui_message_type;
enum e_window_index;

enum e_gui_dialog_choice
{
    _gui_dialog_choice_first = 0,
    _gui_dialog_choice_second,
    _gui_dialog_choice_third,
    _gui_dialog_choice_fourth,

    k_gui_dialog_choice_count,

    k_gui_dialog_choice_ok = _gui_dialog_choice_first,
    k_gui_dialog_choice_cancel = _gui_dialog_choice_second
};

/* ---------- definitions */

// layout from ??0c_message@@QAA@W4e_ui_message_type@@JW4e_controller_index@@W4e_window_index@@@Z
class c_message
{
public:
    c_message(e_ui_message_type type, long screen_name, e_controller_index controller, e_window_index window);
    virtual ~c_message();
    virtual void initialize();
    virtual void update();

    // verified (storage_device_manager.obj)
    e_controller_index get_controller() const
    {
        mangled_ppc("?get_controller@c_message@@QBA?AW4e_controller_index@@XZ");

        return m_controller;
    };

private:
    long m_game_time_at_creation; // 0x4

protected:
    e_ui_message_type m_type; // 0x8
    long m_screen_name; // 0xC
    e_controller_index m_controller; // 0x10
    e_window_index m_window; // 0x14
};
static_assert(sizeof(c_message) == 0x18, "c_message");

class c_dialog_result_message :
    public c_message
{
public:
    c_dialog_result_message(long screen_name, e_controller_index controller, e_window_index window, long dialog_name, e_gui_dialog_choice dialog_result);
    virtual ~c_dialog_result_message();

    // verified (storage_device_manager.obj)
    e_gui_dialog_choice get_dialog_result() const
    {
        mangled_ppc("?get_dialog_result@c_dialog_result_message@@QBA?AW4e_gui_dialog_choice@@XZ");

        return m_dialog_result;
    };

protected:
    e_gui_dialog_choice m_dialog_result; // 0x18
    long m_dialog_name; // 0x1C (H3 order; not verified in Reach)
    long m_dispose_on_success_screen_index; // 0x20 (H3 order; not verified in Reach)
};

/* ---------- prototypes */

bool user_interface_xbox_guide_is_active();

/* ---------- globals */

/* ---------- public code */

#endif // __USER_INTERFACE_MESSAGES_H__

