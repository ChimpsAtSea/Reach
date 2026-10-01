#pragma once
#ifndef __HS_DUMP_H__
#define __HS_DUMP_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct s_file_reference;

void hs_scenario_report_scripts(void);
void hs_dump_script_to_file(long scenario_index, long source_file_index, s_file_reference const * file);

/* ---------- globals */

/* ---------- public code */

#endif // __HS_DUMP_H__

