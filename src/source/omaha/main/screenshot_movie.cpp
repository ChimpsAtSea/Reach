#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\main\\screenshot_movie.cpp"
/* ---------- headers */

#include "omaha\main\screenshot_movie.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\cseries\cseries_windows_debug.h"
#include "omaha\game\game_time.h"
#include "omaha\main\main_screenshot.h"
#include "omaha\rasterizer\rasterizer_main.h"
#include "omaha\tag_files\files.h"

#include <ppcintrinsics.h>

/* ---------- constants */

/* ---------- definitions */

struct s_movie_globals
{
    volatile bool in_progress;
    long recording_start_tick;
    long recording_stop_tick;
    volatile long recording_frame_index;
    volatile long recording_frame_mod_index;
    volatile long recording_frame_mod_count;
    float recording_dt;
    bool distributed_recording;
};
static_assert(sizeof(s_movie_globals) == 0x20, "s_movie_globals");

/* ---------- prototypes */

/* ---------- globals */

static s_movie_globals movie_globals;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void movie_record_distributed(short, long, short, long, long);
// void movie_record(short, float, short, short);
// void movie_stop(void);
// bool movie_recording(void);
// bool movie_record_this_frame(void);
// float movie_recording_timestep(void);
// bool movie_advance_frame(void);
// void movie_build_filename(char *, long);

void movie_record_distributed(short frame_rate, long seconds_to_record, short movie_screen_size_multiple, long mod_count, long mod_index)
{
    mangled_ppc("?movie_record_distributed@@YAXFJFJJ@Z");

    movie_record(frame_rate, static_cast<float>(seconds_to_record),
        static_cast<short>(c_rasterizer::render_globals.k_render_resolution_x * movie_screen_size_multiple),
        static_cast<short>(c_rasterizer::render_globals.k_render_resolution_y * movie_screen_size_multiple));
    movie_globals.recording_frame_mod_count = MAX(mod_count, 1);
    movie_globals.recording_frame_mod_index = PIN(mod_index, 0, movie_globals.recording_frame_mod_count);
    movie_globals.distributed_recording = true;
};

void movie_record(short frame_rate, float seconds_to_record, short width, short height)
{
    mangled_ppc("?movie_record@@YAXFMFF@Z");

    assert_tag_debug_untracked_jul_11_2011(61, !movie_globals.in_progress);

    directory_create_or_delete_contents("movie");
    if (init_screenshot(width, height, ""))
    {
        movie_globals.recording_frame_index = 0;
        movie_globals.recording_dt = frame_rate == 0 ? game_tick_length() : 1.0f / static_cast<float>(frame_rate);
        movie_globals.recording_start_tick = game_time_get();
        movie_globals.recording_stop_tick = game_time_get() + game_seconds_to_ticks_round(seconds_to_record);
        movie_globals.distributed_recording = false;
        __lwsync();
        movie_globals.in_progress = true;
        game_time_set_speed(1.0f);
    }
};

void movie_stop()
{
    mangled_ppc("?movie_stop@@YAXXZ");

    movie_globals.in_progress = false;
};

bool movie_recording()
{
    mangled_ppc("?movie_recording@@YA_NXZ");

    return movie_globals.in_progress;
};

bool movie_record_this_frame()
{
    mangled_ppc("?movie_record_this_frame@@YA_NXZ");

    return movie_recording() && (!movie_globals.distributed_recording || movie_globals.recording_frame_index % movie_globals.recording_frame_mod_count == movie_globals.recording_frame_mod_index);
};

float movie_recording_timestep()
{
    mangled_ppc("?movie_recording_timestep@@YAMXZ");

    return movie_recording() ? movie_globals.recording_dt : 0.0f;
};

bool movie_advance_frame()
{
    mangled_ppc("?movie_advance_frame@@YA_NXZ");

    bool result = false;
    if (movie_recording())
    {
        movie_globals.recording_frame_index++;
        if (movie_globals.recording_stop_tick <= game_time_get())
        {
            movie_stop();
        }
        else
        {
            result = true;
        }
    }

    return result;
};

void movie_build_filename(char * filename, long max_filename_length)
{
    mangled_ppc("?movie_build_filename@@YAXPADJ@Z");

    long directory_index = movie_globals.recording_frame_index / 2048 * 2048;

    c_debug_output_path debug_output_path;
    csnzprintf(filename, max_filename_length, "%s%s\\frames%06d\\frame%06d.tif", debug_output_path.get_root(), "movie", directory_index, movie_globals.recording_frame_index);
};

