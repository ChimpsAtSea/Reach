#pragma once
#ifndef __SCENARIO_ZONE_RESOURCE_ATTACHMENT_H__
#define __SCENARIO_ZONE_RESOURCE_ATTACHMENT_H__

/* ---------- headers */

/* ---------- constants */

enum e_scenario_bsp_resource_attachment_type;

/* ---------- definitions */

struct s_tag_block;

// vtable owned by scenario_zone_resources.obj (implicit inline constructor); slots 0-2 pure
// (overridden by c_scenario_zone_bsp_itinerary_registrar)
class c_scenario_structure_bsp_resource_registrar
{
public:
    virtual void begin_group(char const * group_name) = 0;
    virtual void end_group(void) = 0;
    virtual bool visit_tag(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, long tag_index) = 0;
    virtual bool register_tag_variant(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, long tag_index, long variant_name);
    virtual void visit_tag_block_element(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, s_tag_block const * block, long element_index);
    virtual void visit_entire_tag_block(char const * name, e_scenario_bsp_resource_attachment_type attachment_type, s_tag_block const * block);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_ZONE_RESOURCE_ATTACHMENT_H__

