#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\saved_games\\storage_device_manager.cpp"
/* ---------- headers */

#include <xtl.h>

#include "omaha\saved_games\storage_device_manager.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "omaha\input\controllers.h"
#include "omaha\interface\c_controller.h"
#include "omaha\interface\content\user_interface_content.h"
#include "omaha\interface\user_interface_messages.h"
#include "omaha\multithreading\synchronization_spasm.h"
#include "omaha\multithreading\threads.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

s_storage_device_manager_main_thread_globals * get_main_thread_globals(void);

/* ---------- globals */

c_storage_device_manager_globals_container g_storage_device_manager_globals;
s_storage_device_manager_main_thread_globals g_storage_device_manager_main_thread_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_storage_device_manager_globals_container g_storage_device_manager_globals; // "?g_storage_device_manager_globals@@3Vc_storage_device_manager_globals_container@@A"
// struct s_storage_device_manager_main_thread_globals g_storage_device_manager_main_thread_globals; // "?g_storage_device_manager_main_thread_globals@@3Us_storage_device_manager_main_thread_globals@@A"

// void storage_device_manager_initialize(void);
// public: void c_storage_device::set_controller_index(enum e_controller_index);
// void storage_device_manager_dispose(void);
// void storage_device_manager_update(void);
// void storage_device_manager_storage_devices_changed(void);
// public: void c_controller_interface::set_storage_device_selection_performed(bool);
// void storage_device_manager_display_device_selection_guide_interface(enum e_controller_index);
// public: bool c_storage_device::is_being_selected(void) const;
// bool storage_device_manager_handle_dialog_result_message(class c_dialog_result_message const *);
// public: enum e_controller_index c_message::get_controller(void) const;
// public: enum e_gui_dialog_choice c_dialog_result_message::get_dialog_result(void) const;
// bool storage_device_manager_device_selection_active(enum e_controller_index);
// bool storage_device_manager_device_selection_cancelled_by_user(enum e_controller_index);
// public: bool c_storage_device::device_selection_cancelled(void) const;
// public: c_storage_device_manager_globals_accessor::c_storage_device_manager_globals_accessor(void);
// public: c_storage_device_manager_globals_accessor::~c_storage_device_manager_globals_accessor(void);
// public: struct s_storage_device_manager_globals const * c_storage_device_manager_globals_accessor::operator->(void) const;
// public: struct s_storage_device_manager_globals * c_storage_device_manager_globals_accessor::operator->(void);
// public: c_storage_device_accessor::c_storage_device_accessor(void);
// public: c_storage_device_accessor::c_storage_device_accessor(enum e_controller_index);
// public: c_storage_device_accessor::~c_storage_device_accessor(void);
// public: class c_storage_device const * c_storage_device_accessor::operator->(void) const;
// public: class c_storage_device * c_storage_device_accessor::operator->(void);
// struct s_storage_device_manager_main_thread_globals * get_main_thread_globals(void);
// public: virtual bool c_storage_device_manager_controller_monitor::controller_should_be_monitored(enum e_controller_index, class c_flags<enum e_controller_monitor_flags, unsigned char, 3, struct s_default_enum_string_resolver>);
// public: virtual void c_storage_device_manager_controller_monitor::handle_controller_sign_in(enum e_controller_index);
// public: virtual void c_storage_device_manager_controller_monitor::handle_controller_sign_out(enum e_controller_index);
// public: bool c_flags_no_init<enum c_storage_device::e_storage_device_flag, unsigned char, 2, struct s_default_enum_string_resolver>::test(enum c_storage_device::e_storage_device_flag) const;
// public: void c_flags_no_init<enum e_controller_state_flags, unsigned long, 21, struct s_default_enum_string_resolver>::set(enum e_controller_state_flags, bool);
// void zero_and_reconstruct<struct s_storage_device_manager_main_thread_globals>(struct s_storage_device_manager_main_thread_globals *);
// public: static bool c_flags_no_init<enum c_storage_device::e_storage_device_flag, unsigned char, 2, struct s_default_enum_string_resolver>::valid_bit(enum c_storage_device::e_storage_device_flag);
// private: static unsigned char c_flags_no_init<enum c_storage_device::e_storage_device_flag, unsigned char, 2, struct s_default_enum_string_resolver>::flag_size_type(enum c_storage_device::e_storage_device_flag);
// void reconstruct<struct s_storage_device_manager_main_thread_globals>(struct s_storage_device_manager_main_thread_globals *);
// public: s_storage_device_manager_main_thread_globals::s_storage_device_manager_main_thread_globals(void);
// public: c_storage_device_manager_controller_monitor::c_storage_device_manager_controller_monitor(void);
// public: c_storage_device_manager_globals_container::c_storage_device_manager_globals_container(void);
// public: s_storage_device_manager_globals::s_storage_device_manager_globals(void);
// public: c_storage_device_manager_globals_container::~c_storage_device_manager_globals_container(void);
// public: s_storage_device_manager_globals::~s_storage_device_manager_globals(void);
// public: c_storage_device::~c_storage_device(void);
// public: virtual c_storage_device_selector_overlapped_task::~c_storage_device_selector_overlapped_task(void);
// void g_storage_device_manager_globals::`dynamic atexit destructor'(void);

void storage_device_manager_initialize(void)
{
    mangled_ppc("?storage_device_manager_initialize@@YAXXZ");

    s_storage_device_manager_main_thread_globals * main_thread_globals = get_main_thread_globals();
    for (e_controller_index controller_index = first_controller(); controller_index != k_no_controller; controller_index = next_controller(controller_index))
    {
        c_storage_device_accessor storage_device(controller_index);
        storage_device->set_controller_index(controller_index);
    }

    zero_and_reconstruct(main_thread_globals);
    controller_change_notification_register(&main_thread_globals->controller_monitor);
};

void storage_device_manager_dispose(void)
{
    mangled_ppc("?storage_device_manager_dispose@@YAXXZ");

    s_storage_device_manager_main_thread_globals * main_thread_globals = get_main_thread_globals();
    for (e_controller_index controller_index = first_controller(); controller_index != k_no_controller; controller_index = next_controller(controller_index))
    {
        c_storage_device_accessor storage_device(controller_index);
        storage_device->release();
    }

    controller_change_notification_unregister(&main_thread_globals->controller_monitor);
};

void storage_device_manager_update(void)
{
    mangled_ppc("?storage_device_manager_update@@YAXXZ");
};

void storage_device_manager_storage_devices_changed(void)
{
    mangled_ppc("?storage_device_manager_storage_devices_changed@@YAXXZ");

    for (e_controller_index controller_index = first_controller(); controller_index != k_no_controller; controller_index = next_controller(controller_index))
    {
        c_controller_interface * controller = controller_get(controller_index);
        if (!storage_device_manager_device_selection_active(controller_index))
        {
            controller->set_storage_device_selection_performed(false);
        }

        user_interface_content_invalidate_cache(controller_index);

        c_storage_device_accessor storage_device(controller_index);
        storage_device->release();
    }
};

void storage_device_manager_display_device_selection_guide_interface(e_controller_index controller_index)
{
    mangled_ppc("?storage_device_manager_display_device_selection_guide_interface@@YAXW4e_controller_index@@@Z");

    c_controller_interface const * controller = controller_get(controller_index);
    if (controller->is_signed_in_to_machine() && !controller->is_unsigned_in_user() && !controller->is_guest())
    {
        bool device_selection_already_active = false;
        for (e_controller_index test_controller_index = first_controller(); test_controller_index != k_no_controller; test_controller_index = next_controller(test_controller_index))
        {
            c_storage_device_accessor storage_device(test_controller_index);
            if (storage_device->is_being_selected())
            {
                event_wrapped(_event_message, "storage_device_manager: device selector UI already active for controller #%d", test_controller_index);
                device_selection_already_active = true;
                break;
            }
        }

        if (!device_selection_already_active && !user_interface_xbox_guide_is_active())
        {
            c_storage_device_accessor storage_device(controller_index);
            unsigned long const required_free_space_bytes = static_cast<unsigned long>(XContentCalculateSize(12 * 1024 * 1024, 0));
            storage_device->select_device(required_free_space_bytes);
        }
    }
    else
    {
        event_wrapped(_event_message, "storage_device_manager: controller #%d is not allowed to select a storage device - skipping device selection", controller_index);
    }
};

bool storage_device_manager_handle_dialog_result_message(c_dialog_result_message const * dialog_result_message)
{
    mangled_ppc("?storage_device_manager_handle_dialog_result_message@@YA_NPBVc_dialog_result_message@@@Z");

    assert_tag_debug_untracked_jul_11_2011(199, dialog_result_message!=NULL);

    switch (dialog_result_message->get_dialog_result())
    {
    case _gui_dialog_choice_first:
        storage_device_manager_display_device_selection_guide_interface(dialog_result_message->get_controller());
        break;
    }

    return true;
};

bool storage_device_manager_device_selection_active(e_controller_index controller_index)
{
    mangled_ppc("?storage_device_manager_device_selection_active@@YA_NW4e_controller_index@@@Z");

    c_storage_device_accessor storage_device(controller_index);
    assert_tag_debug_untracked_jul_11_2011(220, VALID_CONTROLLER(controller_index));

    return storage_device->is_being_selected();
};

bool storage_device_manager_device_selection_cancelled_by_user(e_controller_index controller_index)
{
    mangled_ppc("?storage_device_manager_device_selection_cancelled_by_user@@YA_NW4e_controller_index@@@Z");

    c_storage_device_accessor storage_device(controller_index);
    assert_tag_debug_untracked_jul_11_2011(230, VALID_CONTROLLER(controller_index));

    return storage_device->device_selection_cancelled();
};

c_storage_device_manager_globals_accessor::c_storage_device_manager_globals_accessor(void)
{
    mangled_ppc("??0c_storage_device_manager_globals_accessor@@QAA@XZ");

    critical_section_enter_internal(g_omaha_critical_sections[k_crit_section_storage_device_manager], _critical_section_non_recursive);
};

c_storage_device_manager_globals_accessor::~c_storage_device_manager_globals_accessor(void)
{
    mangled_ppc("??1c_storage_device_manager_globals_accessor@@QAA@XZ");

    critical_section_leave_internal(g_omaha_critical_sections[k_crit_section_storage_device_manager], _critical_section_non_recursive);
};

s_storage_device_manager_globals const * c_storage_device_manager_globals_accessor::operator->(void) const
{
    mangled_ppc("??Cc_storage_device_manager_globals_accessor@@QBAPBUs_storage_device_manager_globals@@XZ");

    return &g_storage_device_manager_globals.m_globals;
};

s_storage_device_manager_globals * c_storage_device_manager_globals_accessor::operator->(void)
{
    mangled_ppc("??Cc_storage_device_manager_globals_accessor@@QAAPAUs_storage_device_manager_globals@@XZ");

    return &g_storage_device_manager_globals.m_globals;
};

c_storage_device_accessor::c_storage_device_accessor(void)
{
    mangled_ppc("??0c_storage_device_accessor@@QAA@XZ");

    m_storage_device = NULL;
};

c_storage_device_accessor::c_storage_device_accessor(e_controller_index controller_index)
{
    mangled_ppc("??0c_storage_device_accessor@@QAA@W4e_controller_index@@@Z");

    c_storage_device_manager_globals_accessor globals;
    assert_tag_debug_untracked_jul_11_2011(273, VALID_CONTROLLER(controller_index));

    m_storage_device = &globals->storage_devices[controller_index];
    critical_section_enter_internal(g_omaha_critical_sections[k_crit_section_storage_device_manager], _critical_section_non_recursive);
};

c_storage_device_accessor::~c_storage_device_accessor(void)
{
    mangled_ppc("??1c_storage_device_accessor@@QAA@XZ");

    if (m_storage_device != NULL)
    {
        critical_section_leave_internal(g_omaha_critical_sections[k_crit_section_storage_device_manager], _critical_section_non_recursive);
    }
};

c_storage_device const * c_storage_device_accessor::operator->(void) const
{
    mangled_ppc("??Cc_storage_device_accessor@@QBAPBVc_storage_device@@XZ");

    return m_storage_device;
};

c_storage_device * c_storage_device_accessor::operator->(void)
{
    mangled_ppc("??Cc_storage_device_accessor@@QAAPAVc_storage_device@@XZ");

    return m_storage_device;
};

s_storage_device_manager_main_thread_globals * get_main_thread_globals(void)
{
    mangled_ppc("?get_main_thread_globals@@YAPAUs_storage_device_manager_main_thread_globals@@XZ");

    assert_tag_debug_untracked_jul_11_2011(305, is_main_thread());

    return &g_storage_device_manager_main_thread_globals;
};

bool c_storage_device_manager_controller_monitor::controller_should_be_monitored(e_controller_index controller_index, c_flags<e_controller_monitor_flags, unsigned char, k_number_of_controller_monitor_flags> flags)
{
    mangled_ppc("?controller_should_be_monitored@c_storage_device_manager_controller_monitor@@UAA_NW4e_controller_index@@V?$c_flags@W4e_controller_monitor_flags@@E$02Us_default_enum_string_resolver@@@@@Z");

    bool result = false;
    result = flags.test(_controller_monitor_flag1_bit);

    return result;
};

void c_storage_device_manager_controller_monitor::handle_controller_sign_in(e_controller_index controller_index)
{
    mangled_ppc("?handle_controller_sign_in@c_storage_device_manager_controller_monitor@@UAAXW4e_controller_index@@@Z");
};

void c_storage_device_manager_controller_monitor::handle_controller_sign_out(e_controller_index controller_index)
{
    mangled_ppc("?handle_controller_sign_out@c_storage_device_manager_controller_monitor@@UAAXW4e_controller_index@@@Z");

    c_storage_device_accessor storage_device(controller_index);
    storage_device->release();
};
