#pragma once
#ifndef __STORAGE_DEVICE_H__
#define __STORAGE_DEVICE_H__

/* ---------- headers */

#include "omaha\cseries\async_xoverlapped.h"
#include "omaha\input\controllers.h"
#include "omaha\memory\static_arrays.h"

/* ---------- constants */

/* ---------- definitions */

class c_storage_device;

class c_storage_device_selector_overlapped_task :
    public c_overlapped_task
{
public:
    c_storage_device_selector_overlapped_task(char const * file, long line);
    virtual char const * get_context_string() const;
    virtual unsigned long start(void * platform_handle);
    virtual void success(unsigned long return_result);
    virtual void failure(unsigned long calling_result, unsigned long overlapped_error, unsigned long overlapped_extended_error);
    void initialize(c_storage_device * storage_device, e_controller_index controller_index, unsigned long minimum_required_bytes, unsigned long * device_id);
    e_controller_index get_controller_index() const;

private:
    c_storage_device * m_storage_device; // 0x18
    e_controller_index m_controller_index; // 0x1C
    unsigned long m_minimum_required_bytes; // 0x20
    unsigned long * m_device_id; // 0x24
    bool m_always_show; // 0x28
};
static_assert(sizeof(c_storage_device_selector_overlapped_task) == 0x2C, "c_storage_device_selector_overlapped_task");

class c_storage_device
{
public:
    enum e_storage_device_flag
    {
        _valid_bit = 0,
        _most_recent_device_selection_cancelled_bit,

        k_number_of_storage_device_flags
    };

    c_storage_device();

    void select_device(unsigned long required_free_space_bytes);
    void release();

    // verified (storage_device_manager.obj)
    bool is_being_selected() const
    {
        mangled_ppc("?is_being_selected@c_storage_device@@QBA_NXZ");

        return m_device_selector_task.busy();
    };

    // verified (storage_device_manager.obj)
    bool device_selection_cancelled() const
    {
        mangled_ppc("?device_selection_cancelled@c_storage_device@@QBA_NXZ");

        return m_flags.test(_most_recent_device_selection_cancelled_bit);
    };

    // verified (storage_device_manager.obj)
    void set_controller_index(e_controller_index controller_index)
    {
        mangled_ppc("?set_controller_index@c_storage_device@@QAAXW4e_controller_index@@@Z");

        m_controller_index = controller_index;
    };

private:
    c_flags<e_storage_device_flag, unsigned char, k_number_of_storage_device_flags> m_flags; // 0x0
    unsigned long m_device_id; // 0x4
    e_controller_index m_controller_index; // 0x8
    c_storage_device_selector_overlapped_task m_device_selector_task; // 0xC
};
static_assert(sizeof(c_storage_device) == 0x38, "c_storage_device");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __STORAGE_DEVICE_H__

