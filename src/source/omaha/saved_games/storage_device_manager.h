#pragma once
#ifndef __STORAGE_DEVICE_MANAGER_H__
#define __STORAGE_DEVICE_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\input\controllers.h"
#include "omaha\interface\c_controller.h"
#include "omaha\saved_games\storage_device.h"

/* ---------- constants */

/* ---------- definitions */

class c_dialog_result_message;

class c_storage_device_manager_controller_monitor :
    public c_controller_monitor
{
public:
    c_storage_device_manager_controller_monitor()
    {
        mangled_ppc("??0c_storage_device_manager_controller_monitor@@QAA@XZ");
    };

    virtual bool controller_should_be_monitored(e_controller_index controller_index, c_flags<e_controller_monitor_flags, unsigned char, k_number_of_controller_monitor_flags> flags);
    virtual void handle_controller_sign_in(e_controller_index controller_index);
    virtual void handle_controller_sign_out(e_controller_index controller_index);
};
static_assert(sizeof(c_storage_device_manager_controller_monitor) == 0x68, "c_storage_device_manager_controller_monitor");

struct s_storage_device_manager_main_thread_globals
{
    s_storage_device_manager_main_thread_globals()
    {
        mangled_ppc("??0s_storage_device_manager_main_thread_globals@@QAA@XZ");
    };

    c_storage_device_manager_controller_monitor controller_monitor; // 0x0
};
static_assert(sizeof(s_storage_device_manager_main_thread_globals) == 0x68, "s_storage_device_manager_main_thread_globals");

struct s_storage_device_manager_globals
{
    c_storage_device storage_devices[k_number_of_controllers]; // 0x0
};
static_assert(sizeof(s_storage_device_manager_globals) == 0xE0, "s_storage_device_manager_globals");

class c_storage_device_manager_globals_container
{
public:
    s_storage_device_manager_globals m_globals; // 0x0
};
static_assert(sizeof(c_storage_device_manager_globals_container) == 0xE0, "c_storage_device_manager_globals_container");

class c_storage_device_manager_globals_accessor
{
public:
    c_storage_device_manager_globals_accessor(void);
    ~c_storage_device_manager_globals_accessor(void);

    s_storage_device_manager_globals const * operator->(void) const;
    s_storage_device_manager_globals * operator->(void);
};

class c_storage_device_accessor
{
public:
    c_storage_device_accessor(void);
    c_storage_device_accessor(e_controller_index controller_index);
    ~c_storage_device_accessor(void);

    c_storage_device const * operator->(void) const;
    c_storage_device * operator->(void);

private:
    c_storage_device * m_storage_device; // 0x0
};
static_assert(sizeof(c_storage_device_accessor) == 0x4, "c_storage_device_accessor");

/* ---------- prototypes */

void storage_device_manager_initialize(void);
void storage_device_manager_dispose(void);
void storage_device_manager_update(void);
void storage_device_manager_storage_devices_changed(void);
void storage_device_manager_display_device_selection_guide_interface(e_controller_index controller_index);
bool storage_device_manager_handle_dialog_result_message(c_dialog_result_message const * dialog_result_message);
bool storage_device_manager_device_selection_active(e_controller_index controller_index);
bool storage_device_manager_device_selection_cancelled_by_user(e_controller_index controller_index);

/* ---------- globals */

extern c_storage_device_manager_globals_container g_storage_device_manager_globals;
extern s_storage_device_manager_main_thread_globals g_storage_device_manager_main_thread_globals;

/* ---------- public code */

#endif // __STORAGE_DEVICE_MANAGER_H__

