#pragma once
#ifndef __TAG_GROUP_RESOURCE_VISITOR_H__
#define __TAG_GROUP_RESOURCE_VISITOR_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_marker;
struct s_tag_reference;
struct s_tag_resource;

// vtable order from ??_7c_tag_resource_visitor@@6B@ (0x821A847C): add_traversal_link, _purecall, _purecall; names from c_tag_resource_prediction_visitor
class c_tag_resource_visitor
{
public:
    virtual void add_traversal_link(long parent_tag_index, long child_tag_index);
    virtual void visit_tag_resource_owner(long owner_tag_index) = 0;
    virtual void visit_tag_resource(long owner_tag_index, s_tag_resource const * resource, char const * scope_string) = 0;
};
static_assert(sizeof(c_tag_resource_visitor) == 0x4, "c_tag_resource_visitor");

// vtable order from ??_7c_tag_resource_visit_itinerary@@6B@ (0x821A8488): _purecall, _purecall, should_visit_through_tag_reference; names from c_tag_resource_prediction_visitor
class c_tag_resource_visit_itinerary
{
public:
    virtual bool should_visit_individual_resources(long tag_index) = 0;
    virtual bool should_visit_tag(long tag_index) = 0;
    virtual bool should_visit_through_tag_reference(s_tag_reference const * reference);
};
static_assert(sizeof(c_tag_resource_visit_itinerary) == 0x4, "c_tag_resource_visit_itinerary");

// offsets from c_tag_recursive_resource_visitor::visit_field; names unverified
struct s_tag_resource_traversal_location
{
    s_tag_resource_traversal_location const * parent; // 0x0
    long tag_index; // 0x4
    s_tag_reference const * reference; // 0x8
};
static_assert(sizeof(s_tag_resource_traversal_location) == 0xC, "s_tag_resource_traversal_location");

// no implementations in the target; slot 0 called from c_tag_recursive_resource_visitor::visit_field (0 = continue visiting), name unverified
class c_tag_resource_visit_redirector
{
public:
    virtual long redirect(s_tag_resource_traversal_location const * location) = 0;
};
static_assert(sizeof(c_tag_resource_visit_redirector) == 0x4, "c_tag_resource_visit_redirector");

// no implementations in the target; slot 0 called from get_redirector, name unverified
class c_tag_resource_redirect_directory
{
public:
    virtual c_tag_resource_visit_redirector * get_redirector(long tag_index) = 0;
};
static_assert(sizeof(c_tag_resource_redirect_directory) == 0x4, "c_tag_resource_redirect_directory");

// offsets from tag_visit_resources_recursive; names unverified
struct s_tag_resource_visit_context
{
    c_tag_marker const * excluded_tags; // 0x0
    c_tag_marker * visited_tags; // 0x4
    c_tag_resource_visitor * visitor; // 0x8
    c_tag_resource_visit_itinerary * itinerary; // 0xC
    c_tag_resource_redirect_directory * redirect_directory; // 0x10
};
static_assert(sizeof(s_tag_resource_visit_context) == 0x14, "s_tag_resource_visit_context");

/* ---------- prototypes */

void tag_visit_resources_recursive(long tag_index, c_tag_marker const * excluded_tags, c_tag_resource_visitor * visitor, c_tag_resource_visit_itinerary * itinerary);
void tag_visit_resources_with_redirect(long tag_index, c_tag_marker const * excluded_tags, c_tag_resource_visitor * visitor, c_tag_resource_visit_itinerary * itinerary, c_tag_resource_redirect_directory * redirect_directory);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUP_RESOURCE_VISITOR_H__

