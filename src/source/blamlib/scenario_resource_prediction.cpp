/* ---------- headers */

#include "blamlib\scenario_resource_prediction.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_scenario_tag_resource_prediction_filter g_scenario_prediction_filter;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_scenario_tag_resource_prediction_filter g_scenario_prediction_filter; // "?g_scenario_prediction_filter@@3Vc_scenario_tag_resource_prediction_filter@@A"

// void scenario_resource_prediction_initialize(void);
// void scenario_resource_prediction_dispose(void);
// public: c_scenario_tag_resource_prediction_filter::c_scenario_tag_resource_prediction_filter(void);
// public: virtual bool c_scenario_tag_resource_prediction_filter::should_predict_through_tag(long);
// public: c_tag_resource_prediction_filter::c_tag_resource_prediction_filter(void);

void scenario_resource_prediction_initialize()
{
    mangled_ppc("?scenario_resource_prediction_initialize@@YAXXZ");

    tag_resources_set_prediction_filter(&g_scenario_prediction_filter);
};

void scenario_resource_prediction_dispose()
{
    mangled_ppc("?scenario_resource_prediction_dispose@@YAXXZ");

    tag_resources_set_prediction_filter(NULL);
};
