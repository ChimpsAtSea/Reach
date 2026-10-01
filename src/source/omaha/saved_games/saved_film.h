#pragma once
#ifndef __SAVED_FILM_H__
#define __SAVED_FILM_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_game_options;

// $TODO: layout not reversed (H3: s_blffile_saved_game_file + film header/data chunks)
struct s_blf_saved_film
{
    bool copy_to_and_validate(s_game_options * game_options, long * out_length_in_ticks, long * out_start_tick, bool * out_was_valid) const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SAVED_FILM_H__

