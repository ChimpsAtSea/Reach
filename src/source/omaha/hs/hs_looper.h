#pragma once
#ifndef __HS_LOOPER_H__
#define __HS_LOOPER_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\static_string.h"

/* ---------- constants */

/* ---------- definitions */

class c_hs_looper
{
public:
    c_hs_looper();
    void reinitialize();
    void set_loop_expression(char const * new_loop_expression);
    void clear();
    void game_tick();
    void reboot_loop();
    void handle_thread_delete(long thread_index);
    void restore_from_saved_game();

private:
    long create_suspended_loop_thread();

    c_static_string<4096> m_loop_expression; // 0x0
    long m_loop_thread_index; // 0x1000
    bool m_loop_enabled; // 0x1004
};
static_assert(sizeof(c_hs_looper) == 0x1008, "c_hs_looper");

/* ---------- prototypes */

void hs_looper_setup(char const * expression);
void hs_looper_clear();
void hs_looper_handle_thread_delete(long thread_index);
void hs_looper_game_tick();
void hs_looper_reboot();
void hs_looper_reinitialize();
void hs_looper_restore_from_saved_game();

/* ---------- globals */

extern c_hs_looper g_hs_looper;

/* ---------- public code */

#endif // __HS_LOOPER_H__

