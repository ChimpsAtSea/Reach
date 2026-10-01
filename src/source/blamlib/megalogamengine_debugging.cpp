/* ---------- headers */

#include "blamlib\megalogamengine_debugging.h"
#include <string.h>
#include "blamlib\megalogamengine.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_engine.h"
#include "omaha\game\game_engine_megalo.h"
#include "omaha\render\simple_font.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_megalogamengine_profiling_state g_profiling_state;
long megalo_profiling_mode;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static long const s_static_array<struct s_frame_info, 60>::k_element_count; // "?k_element_count@?$s_static_array@Us_frame_info@@$0DM@@@2JB"
// struct s_megalogamengine_profiling_state g_profiling_state; // "?g_profiling_state@@3Us_megalogamengine_profiling_state@@A"
// long megalo_profiling_mode; // "?megalo_profiling_mode@@3JA"

// void megalogamengine_debugging_initialize(void);
// void megalogamengine_debugging_update_before_engine(void);
// void megalogamengine_render_debug_profiling_info(void);
// public: c_megalogamengine_profiling_info_iterator::c_megalogamengine_profiling_info_iterator(void);
// public: megalogamengine_log_trigger_execution::megalogamengine_log_trigger_execution(long);
// public: megalogamengine_log_trigger_execution::~megalogamengine_log_trigger_execution(void);
// public: virtual void c_megalogamengine_profiling_info_iterator::begin_all_series(void);
// public: virtual bool c_megalogamengine_profiling_info_iterator::next_series(class c_static_string<256> *);
// public: virtual bool c_megalogamengine_profiling_info_iterator::next_data_point_in_series(union real_point2d *);
// public: long c_static_stack<class c_trigger, 320>::count(void) const;
// public: struct s_frame_info & s_static_array<struct s_frame_info, 60>::operator[]<long>(long);
// public: static bool s_static_array<struct s_frame_info, 60>::valid<long>(long);

void megalogamengine_debugging_initialize(void)
{
    mangled_ppc("?megalogamengine_debugging_initialize@@YAXXZ");

    memset(&g_profiling_state, 0, sizeof(g_profiling_state));
};

void megalogamengine_debugging_update_before_engine(void)
{
    mangled_ppc("?megalogamengine_debugging_update_before_engine@@YAXXZ");

    g_profiling_state.previous_frame_index = g_profiling_state.current_frame_index;
    g_profiling_state.current_frame_index = (g_profiling_state.current_frame_index + 1) % k_megalo_profiling_frame_count;
    memset(&g_profiling_state.frames[g_profiling_state.current_frame_index], 0, sizeof(s_frame_info));
};

void megalogamengine_render_debug_profiling_info(void)
{
    mangled_ppc("?megalogamengine_render_debug_profiling_info@@YAXXZ");

    if (get_current_game_engine_index() == _game_engine_type_megalo && megalo_profiling_mode != _megalo_profiling_mode_none)
    {
        s_render_debug_graph_config config;
        c_simple_font_screen_display display;
        config.initialize_to_defaults();
        if (display.open_session(1.0f))
        {
            if (megalo_profiling_mode == _megalo_profiling_mode_elapsed_time)
            {
                config.name.print("megalo time elapsed per trigger");
                config.range_units.print("ms");
                config.range_bounds.upper = g_profiling_state.max_elapsed_time;
            }
            else if (megalo_profiling_mode == _megalo_profiling_mode_execution_count)
            {
                config.name.print("megalo execution count per trigger");
                config.range_units.print("#");
                config.range_bounds.upper = static_cast<real>(g_profiling_state.max_execution_count);
            }
            config.domain_units.print("ticks");
            config.bounds.x0 = 0;
            config.bounds.x1 = static_cast<short>(display.get_max_column());
            config.bounds.y0 = static_cast<short>(display.get_max_row() / 5 - 1);
            config.bounds.y1 = static_cast<short>(4 * display.get_max_row() / 5 + 1);
            config.domain_bounds.lower = 0.0f;
            config.domain_bounds.upper = 60.0f;
            config.range_bounds.lower = 0.0f;
            config.domain_tick_spacing = 15.0f;
            config.range_tick_spacing = config.range_bounds.upper / 4.0f;
            config.columns.set_all();
            config.unknown_E4 = 3;
            config.unknown_E8 = 2;
            c_megalogamengine_profiling_info_iterator iterator;
            config.iterator = &iterator;
            render_debug_graph(&config);
        }
    }
};

c_megalogamengine_profiling_info_iterator::c_megalogamengine_profiling_info_iterator(void)
{
    mangled_ppc("??0c_megalogamengine_profiling_info_iterator@@QAA@XZ");
};

megalogamengine_log_trigger_execution::megalogamengine_log_trigger_execution(long trigger_index)
{
    mangled_ppc("??0megalogamengine_log_trigger_execution@@QAA@J@Z");

    m_trigger_index = trigger_index;
};

megalogamengine_log_trigger_execution::~megalogamengine_log_trigger_execution(void)
{
    mangled_ppc("??1megalogamengine_log_trigger_execution@@QAA@XZ");

    real elapsed_time = m_stop_watch.total_elapsed_time_in_seconds() * 1000.0f;
    s_trigger_profile_info * trigger_info = &g_profiling_state.frames[g_profiling_state.current_frame_index].triggers[m_trigger_index];
    trigger_info->execution_count++;
    trigger_info->elapsed_time += elapsed_time;
    g_profiling_state.max_execution_count = int_max(g_profiling_state.max_execution_count, trigger_info->execution_count);
    g_profiling_state.max_elapsed_time = real_max(g_profiling_state.max_elapsed_time, trigger_info->elapsed_time);
};

void c_megalogamengine_profiling_info_iterator::begin_all_series(void)
{
    mangled_ppc("?begin_all_series@c_megalogamengine_profiling_info_iterator@@UAAXXZ");

    m_trigger_index = NONE;
    m_frame_offset = 0;
};

bool c_megalogamengine_profiling_info_iterator::next_series(c_static_string<256> * series_name)
{
    mangled_ppc("?next_series@c_megalogamengine_profiling_info_iterator@@UAA_NPAV?$c_static_string@$0BAA@@@@Z");

    bool result = false;
    m_trigger_index++;
    m_frame_offset = 0;
    if (m_trigger_index < get_custom_game_engine_definition()->triggers.count())
    {
        result = true;
        series_name->print("%d", m_trigger_index);
    }

    return result;
};

bool c_megalogamengine_profiling_info_iterator::next_data_point_in_series(real_point2d * point)
{
    mangled_ppc("?next_data_point_in_series@c_megalogamengine_profiling_info_iterator@@UAA_NPATreal_point2d@@@Z");

    bool result = false;
    if (m_frame_offset < k_megalo_profiling_frame_count)
    {
        long frame_index = (g_profiling_state.current_frame_index + m_frame_offset) % k_megalo_profiling_frame_count;
        s_trigger_profile_info const * trigger_info = &g_profiling_state.frames[frame_index].triggers[m_trigger_index];
        point->x = static_cast<real>(m_frame_offset);
        if (megalo_profiling_mode == _megalo_profiling_mode_execution_count)
        {
            point->y = static_cast<real>(trigger_info->execution_count);
        }
        else
        {
            point->y = trigger_info->elapsed_time;
        }
        result = true;
    }
    m_frame_offset++;

    return result;
};
