#pragma once
#ifndef __LEVELS_INTERNAL_H__
#define __LEVELS_INTERNAL_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_file_reference;
struct s_blf_chunk_campaign;
struct s_blf_chunk_scenario;

/* ---------- prototypes */

void levels_find_campaign_chunk(s_file_reference * file, char * const buffer, s_blf_chunk_campaign const ** out_campaign_chunk, bool * out_must_byte_swap);
void levels_find_scenario_chunk(s_file_reference * file, char * const buffer, s_blf_chunk_scenario const ** out_scenario_chunk, bool * out_must_byte_swap);

/* ---------- globals */

/* ---------- public code */

#endif // __LEVELS_INTERNAL_H__

