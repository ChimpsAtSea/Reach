#pragma once
#ifndef __SCENARIO_CONTENT_STATUS_H__
#define __SCENARIO_CONTENT_STATUS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

enum e_scenario_content_source
{
    _scenario_content_source_content = 0,
    _scenario_content_source_local,

    k_number_of_scenario_content_sources
};

/* ---------- prototypes */

char const * scenario_content_source_sub_directory_get(e_scenario_content_source content_source);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_CONTENT_STATUS_H__

