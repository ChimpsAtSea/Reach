#pragma once
#ifndef __C_CONTROLLER_H__
#define __C_CONTROLLER_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_array.h"
#include "omaha\input\controllers.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

// Reach has 21 controller state flags (global enum); bits 3/4 verified (set_storage_device_selection_performed), names follow H3
enum e_controller_state_flags
{
    _controller_state_attached_bit = 0,
    _controller_state_has_voice_bit,
    _controller_state_temporary_bit,
    _controller_state_storage_device_selection_performed_bit,
    _controller_state_storage_device_always_show_device_selector_ui_bit,

    k_number_of_controller_state_flags = 21
};

// 3 flags built from controller state bits 16/17/18 in c_controller_monitor::build_flags_from_controller_state_flags; names not recovered
enum e_controller_monitor_flags
{
    _controller_monitor_flag0_bit = 0,
    _controller_monitor_flag1_bit,
    _controller_monitor_flag2_bit,

    k_number_of_controller_monitor_flags
};

/* ---------- definitions */

class c_player_profile_interface;

// $TODO: layout not reversed; only the methods used so far are declared
class c_controller_interface
{
public:
    c_player_profile_interface * get_player_profile_interface_writable();
    bool in_use() const;
    unsigned __int64 const get_player_xuid() const;
    wchar_t const * get_display_name() const;
    bool is_signed_in_to_live() const;
    bool is_signed_in_to_machine() const;
    bool is_unsigned_in_user() const;
    bool is_guest() const;

    // verified (storage_device_manager.obj)
    void set_storage_device_selection_performed(bool performed)
    {
        mangled_ppc("?set_storage_device_selection_performed@c_controller_interface@@QAAX_N@Z");

        m_state_flags.set(_controller_state_storage_device_selection_performed_bit, performed);
        if (performed)
        {
            m_state_flags.set(_controller_state_storage_device_always_show_device_selector_ui_bit, true);
        }
    };

private:
    c_flags_no_init<e_controller_state_flags, unsigned long, k_number_of_controller_state_flags> m_state_flags; // 0x0
};

// layout from ??0c_controller_monitor@@QAA@XZ (c_controller.obj); vtable has 3 pure virtuals
class c_controller_monitor
{
public:
    enum e_controller_change_notification_flags
    {
        k_number_of_controller_change_notification_flags = 1
    };

    struct s_controller_monitor_controller
    {
        c_flags<e_controller_change_notification_flags, unsigned char, k_number_of_controller_change_notification_flags> flags; // 0x0
        unsigned char data[0x17]; // 0x1 $TODO not reversed
    };
    static_assert(sizeof(s_controller_monitor_controller) == 0x18, "s_controller_monitor_controller");

    c_controller_monitor();

    virtual bool controller_should_be_monitored(e_controller_index controller_index, c_flags<e_controller_monitor_flags, unsigned char, k_number_of_controller_monitor_flags> flags) = 0;
    virtual void handle_controller_sign_in(e_controller_index controller_index) = 0;
    virtual void handle_controller_sign_out(e_controller_index controller_index) = 0;

private:
    long m_unknown4; // 0x4
    s_static_array<s_controller_monitor_controller, k_number_of_controllers> m_controllers; // 0x8
};
static_assert(sizeof(c_controller_monitor) == 0x68, "c_controller_monitor");

/* ---------- prototypes */

bool controller_change_notification_register(c_controller_monitor * monitor);
bool controller_change_notification_unregister(c_controller_monitor * monitor);

c_controller_interface * controller_get(enum e_controller_index controller_index);

e_controller_index get_controller_index_from_xuid(unsigned __int64 xuid);

/* ---------- globals */

/* ---------- public code */

#endif // __C_CONTROLLER_H__

