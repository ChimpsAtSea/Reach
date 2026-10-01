#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

#define halt_render_thread_and_lock_resources(LINE) _internal_halt_render_thread_and_lock_resources(__FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__, LINE)

// values 4/5 verified by minidump_progress_report (xenon_minidump.obj); rest from H3
enum e_main_pregame_frame
{
    _main_pregame_frame_none = 0,
    _main_pregame_frame_normal,
    _main_pregame_frame_loading_debug,
    _main_pregame_frame_cache_loading,
    _main_pregame_frame_crash_uploading,
    _main_pregame_frame_crash_done,
    _main_pregame_frame_upload,
    _main_pregame_frame_out_of_sync,
    _main_pregame_frame_loading_screen,

    k_main_pregame_frame_count
};

unsigned long _internal_halt_render_thread_and_lock_resources(char const * file, long line);
void unlock_resources_and_resume_render_thread(unsigned long unlock_token);

// ctor/dtor are "f i", owned by scenario.obj
class c_wait_for_render_thread
{
public:
    c_wait_for_render_thread(char const * file, long line) :
        m_token(_internal_halt_render_thread_and_lock_resources(file, line))
    {
    };

    ~c_wait_for_render_thread()
    {
        unlock_resources_and_resume_render_thread(m_token);
    };

private:
    unsigned long m_token; // 0x0
};

/* ---------- prototypes */

void main_halt_and_catch_fire(void);
void main_write_stack_to_crash_info_status_file(char const * crash_info, void * context);
unsigned long _internal_halt_render_thread_and_lock_resources(char const * file, long line);
void unlock_resources_and_resume_render_thread(unsigned long unlock_token);
void main_clear_global_pending_zone_activation(long game_state_proc_flags);
void main_set_active_designer_zone_mask(unsigned long designer_zone_mask);
extern void main_loop_pregame();
bool main_events_pending();

/* ---------- globals */

/* ---------- public code */

#endif // __MAIN_H__

