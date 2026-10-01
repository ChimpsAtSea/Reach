#ifndef __SAVED_GAME_FILE_TASKS_H__
#define __SAVED_GAME_FILE_TASKS_H__
#pragma once

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\threadlib\async\async.h"

/* ---------- constants */

/* ---------- definitions */

struct s_file_reference;
struct s_content_item_metadata;
class c_synchronized_int32;

class c_saved_game_file_load_metadata_async
{
public:
    // state names unverified: read() switches to 3 on success, 2 on failure; both handled by close()
    enum e_state
    {
        _state_open = 0,
        _state_read,
        _state_close_failed,
        _state_close_succeeded,

        k_state_count
    };

    c_saved_game_file_load_metadata_async(void);
    e_async_pending_bool operator()(s_file_reference * file_reference, s_content_item_metadata * out_metadata, c_synchronized_int32 * cancel);

    // "f i", owned by autosave_queue_tasks.obj
    void reset(void)
    {
        mangled_ppc("?reset@c_saved_game_file_load_metadata_async@@QAAXXZ");

        m_state = _state_open;
    }

private:
    e_async_pending_bool open(s_file_reference * file_reference, c_synchronized_int32 * cancel);
    void switch_state(e_state state);
    e_async_pending_bool read(s_file_reference * file_reference, s_content_item_metadata * out_metadata, c_synchronized_int32 * cancel);
    e_async_pending_bool close(s_file_reference * file_reference);

    e_state m_state; // 0x0
};
static_assert(sizeof(c_saved_game_file_load_metadata_async) == 0x4, "c_saved_game_file_load_metadata_async");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SAVED_GAME_FILE_TASKS_H__

