#pragma once
#ifndef __SCENARIO_RESOURCE_PREDICTION_H__
#define __SCENARIO_RESOURCE_PREDICTION_H__

/* ---------- headers */

#include "omaha\tag_files\tag_resource_runtime.h"
#include "omaha\cache\predicted_resources.h"

/* ---------- constants */

/* ---------- definitions */

class c_scenario_tag_resource_prediction_filter :
    public c_tag_resource_prediction_filter
{
public:
    c_scenario_tag_resource_prediction_filter()
    {
        mangled_ppc("??0c_scenario_tag_resource_prediction_filter@@QAA@XZ");
    };

    virtual bool should_predict_through_tag(long tag_index)
    {
        mangled_ppc("?should_predict_through_tag@c_scenario_tag_resource_prediction_filter@@UAA_NJ@Z");

        return predicted_resources_can_predict_through_tag(tag_index);
    };
};

/* ---------- prototypes */

void scenario_resource_prediction_initialize();
void scenario_resource_prediction_dispose();

/* ---------- globals */

extern c_scenario_tag_resource_prediction_filter g_scenario_prediction_filter;

/* ---------- public code */

#endif // __SCENARIO_RESOURCE_PREDICTION_H__

