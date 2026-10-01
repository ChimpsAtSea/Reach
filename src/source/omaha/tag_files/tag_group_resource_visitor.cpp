#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\tag_files\\tag_group_resource_visitor.cpp"
/* ---------- headers */

#include "omaha\tag_files\tag_group_resource_visitor.h"
#include "omaha\tag_files\tag_field_visitor.h"
#include "omaha\tag_files\tag_field_scan.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_resource_runtime.h"
#include "omaha\memory\wrapped_arrays.h"
#include "blamlib\tag_marker.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"

/* ---------- constants */

/* ---------- definitions */

class c_tag_recursive_resource_visitor :
    public c_tag_field_visitor
{
public:
    c_tag_recursive_resource_visitor(long tag_index, s_tag_resource_visit_context const * context, s_tag_resource_traversal_location const * parent_location, c_tag_resource_visit_redirector * redirector);

private:
    virtual void initialize_tag_scanner(c_tag_field_scanner * scanner);
    virtual bool visit_field(s_tag_field const * field, c_basic_buffer<void> & buffer);

    long m_tag_index; // 0xB68
    s_tag_resource_visit_context const * m_context; // 0xB6C
    bool m_visit_individual_resources; // 0xB70
    s_tag_resource_traversal_location const * m_parent_location; // 0xB74
    c_tag_resource_visit_redirector * m_redirector; // 0xB78
};
static_assert(sizeof(c_tag_recursive_resource_visitor) == 0xB80, "c_tag_recursive_resource_visitor");

class c_tag_resource_visitor_recursive_visit :
    public c_tag_resource_visitor
{
public:
    c_tag_resource_visitor_recursive_visit(s_tag_resource_visit_context const * context);

    virtual void visit_tag_resource_owner(long owner_tag_index);
    virtual void visit_tag_resource(long owner_tag_index, s_tag_resource const * resource, char const * scope_string);

private:
    s_tag_resource_visit_context const * m_context; // 0x4
};
static_assert(sizeof(c_tag_resource_visitor_recursive_visit) == 0x8, "c_tag_resource_visitor_recursive_visit");

/* ---------- prototypes */

c_tag_resource_visit_redirector * get_redirector(long tag_index, s_tag_resource_visit_context const * context, c_tag_resource_visit_redirector * default_redirector);
void tag_visit_resources_recursive_internal(long tag_index, s_tag_resource_visit_context const * context);
bool is_tag_reference_resource_dependency(s_tag_field const * field);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long volatile `private: virtual bool __cdecl c_tag_recursive_resource_visitor::visit_field(struct s_tag_field const *, class c_basic_buffer<void> &)'::`25'::x_event_category_index; // "?x_event_category_index@?BJ@??visit_field@c_tag_recursive_resource_visitor@@EAA_NPBUs_tag_field@@AAV?$c_basic_buffer@X@@@Z@4JC"

// class c_tag_resource_visit_redirector * get_redirector(long, struct s_tag_resource_visit_context const *, class c_tag_resource_visit_redirector *);
// void tag_visit_resources_recursive(long, class c_tag_marker const *, class c_tag_resource_visitor *, class c_tag_resource_visit_itinerary *);
// void tag_visit_resources_recursive_internal(long, struct s_tag_resource_visit_context const *);
// public: c_tag_recursive_resource_visitor::c_tag_recursive_resource_visitor(long, struct s_tag_resource_visit_context const *, struct s_tag_resource_traversal_location const *, class c_tag_resource_visit_redirector *);
// private: virtual void c_tag_recursive_resource_visitor::initialize_tag_scanner(class c_tag_field_scanner *);
// private: virtual bool c_tag_recursive_resource_visitor::visit_field(struct s_tag_field const *, class c_basic_buffer<void> &);
// bool is_tag_reference_resource_dependency(struct s_tag_field const *);
// public: c_tag_resource_visitor_recursive_visit::c_tag_resource_visitor_recursive_visit(struct s_tag_resource_visit_context const *);
// public: virtual void c_tag_resource_visitor_recursive_visit::visit_tag_resource_owner(long);
// public: virtual void c_tag_resource_visitor_recursive_visit::visit_tag_resource(long, struct s_tag_resource const *, char const *);
// void tag_visit_resources_with_redirect(long, class c_tag_marker const *, class c_tag_resource_visitor *, class c_tag_resource_visit_itinerary *, class c_tag_resource_redirect_directory *);
// public: struct s_tag_resource const * c_basic_buffer<void>::c_basic_buffer_checked_caster::operatorcast<struct s_tag_resource const>(void);
// public: struct s_tag_resource const * c_basic_buffer<void>::get_as_type<struct s_tag_resource const>(void);
// public: struct s_tag_resource const * c_basic_buffer<void>::get_as_type_from_offset<struct s_tag_resource const>(unsigned long);

c_tag_resource_visit_redirector * get_redirector(long tag_index, s_tag_resource_visit_context const * context, c_tag_resource_visit_redirector * default_redirector)
{
    mangled_ppc("?get_redirector@@YAPAVc_tag_resource_visit_redirector@@JPBUs_tag_resource_visit_context@@PAV1@@Z");

    c_tag_resource_visit_redirector * redirector = context->redirect_directory ? context->redirect_directory->get_redirector(tag_index) : default_redirector;
    if (!redirector)
    {
        redirector = default_redirector;
    }

    return redirector;
};

void tag_visit_resources_recursive(long tag_index, c_tag_marker const * excluded_tags, c_tag_resource_visitor * visitor, c_tag_resource_visit_itinerary * itinerary)
{
    mangled_ppc("?tag_visit_resources_recursive@@YAXJPBVc_tag_marker@@PAVc_tag_resource_visitor@@PAVc_tag_resource_visit_itinerary@@@Z");

    if (itinerary->should_visit_tag(tag_index))
    {
        c_tag_marker visited_tags;
        if (excluded_tags)
        {
            visited_tags = *excluded_tags;
        }

        s_tag_resource_visit_context context;
        context.excluded_tags = excluded_tags;
        context.visited_tags = &visited_tags;
        context.visitor = visitor;
        context.itinerary = itinerary;
        context.redirect_directory = NULL;
        tag_visit_resources_recursive_internal(tag_index, &context);
    }
};

void tag_visit_resources_recursive_internal(long tag_index, s_tag_resource_visit_context const * context)
{
    mangled_ppc("?tag_visit_resources_recursive_internal@@YAXJPBUs_tag_resource_visit_context@@@Z");

    if (context->itinerary->should_visit_tag(tag_index))
    {
        c_tag_recursive_resource_visitor visitor(tag_index, context, NULL, NULL);
        visitor.visit_tag_block(tag_get_root_block(tag_index));
    }
};

c_tag_recursive_resource_visitor::c_tag_recursive_resource_visitor(long tag_index, s_tag_resource_visit_context const * context, s_tag_resource_traversal_location const * parent_location, c_tag_resource_visit_redirector * redirector)
{
    mangled_ppc("??0c_tag_recursive_resource_visitor@@QAA@JPBUs_tag_resource_visit_context@@PBUs_tag_resource_traversal_location@@PAVc_tag_resource_visit_redirector@@@Z");

    m_tag_index = tag_index;
    m_context = context;
    m_visit_individual_resources = m_context->itinerary->should_visit_individual_resources(tag_index);
    m_parent_location = parent_location;
    m_redirector = get_redirector(tag_index, context, redirector);
};

void c_tag_recursive_resource_visitor::initialize_tag_scanner(c_tag_field_scanner * scanner)
{
    mangled_ppc("?initialize_tag_scanner@c_tag_recursive_resource_visitor@@EAAXPAVc_tag_field_scanner@@@Z");

    scanner->add_scan_type(_field_block);
    scanner->add_scan_type(_field_tag_reference);
    if (m_visit_individual_resources)
    {
        scanner->add_scan_type(_field_pageable_resource);
    }
};

// $TODO nonmatching (99.96%: visit/location stack slots swapped)
bool c_tag_recursive_resource_visitor::visit_field(s_tag_field const * field, c_basic_buffer<void> & buffer)
{
    mangled_ppc("?visit_field@c_tag_recursive_resource_visitor@@EAA_NPBUs_tag_field@@AAV?$c_basic_buffer@X@@@Z");

    bool success = visit_field_default(field, buffer);
    assert_tag_debug_untracked_jul_11_2011(130, success);

    switch (field->type)
    {
    case _field_pageable_resource:
    {
        m_context->visitor->visit_tag_resource(m_tag_index, buffer.checked_cast(), get_scope_string());
    }
    break;
    case _field_tag_reference:
    {
        if (is_tag_reference_resource_dependency(field))
        {
            s_tag_reference * reference = buffer.checked_cast();
            if (reference->index != NONE && m_context->visited_tags->mark_tag(reference->index))
            {
                event_wrapped(_event_status, "tags:resources:register:traversal: VISITING through %s.%s:%s => %s.%s",
                    tag_get_name(m_tag_index),
                    tag_group_get_name(tag_get_group_tag(m_tag_index)),
                    get_scope_string(),
                    reference->name,
                    tag_group_get_name(reference->group_tag));

                bool visit = true;
                s_tag_resource_traversal_location location;
                location.parent = m_parent_location;
                location.tag_index = m_tag_index;
                location.reference = reference;
                if (m_redirector)
                {
                    long redirect_result;
                    c_tag_resource_visitor_recursive_visit recursive_visitor(m_context);
                    redirect_result = m_redirector->redirect(&location);
                    visit = redirect_result == 0;
                }

                if (visit)
                {
                    if (!m_context->excluded_tags || !m_context->excluded_tags->tag_is_marked(reference->index))
                    {
                        m_context->visitor->add_traversal_link(m_tag_index, reference->index);
                    }

                    m_context->visitor->visit_tag_resource_owner(reference->index);
                    if (reference->index != NONE && m_context->itinerary->should_visit_tag(reference->index))
                    {
                        c_tag_recursive_resource_visitor visitor(reference->index, m_context, &location, m_redirector);
                        visitor.visit_tag_block(tag_get_root_block(reference->index));
                    }
                }
            }
        }
    }
    break;
    }

    return success;
};

bool is_tag_reference_resource_dependency(s_tag_field const * field)
{
    mangled_ppc("?is_tag_reference_resource_dependency@@YA_NPBUs_tag_field@@@Z");

    bool result = false;
    {
        s_tag_reference_definition * definition = get_field_definition<_field_tag_reference>(field);
        if (!TEST_BIT(definition->flags, 0) && !TEST_BIT(definition->flags, 4))
        {
            result = true;
        }
    }

    return result;
};

c_tag_resource_visitor_recursive_visit::c_tag_resource_visitor_recursive_visit(s_tag_resource_visit_context const * context)
{
    mangled_ppc("??0c_tag_resource_visitor_recursive_visit@@QAA@PBUs_tag_resource_visit_context@@@Z");

    m_context = context;
};

void c_tag_resource_visitor_recursive_visit::visit_tag_resource_owner(long owner_tag_index)
{
    mangled_ppc("?visit_tag_resource_owner@c_tag_resource_visitor_recursive_visit@@UAAXJ@Z");

    tag_visit_resources_recursive_internal(owner_tag_index, m_context);
};

void c_tag_resource_visitor_recursive_visit::visit_tag_resource(long owner_tag_index, s_tag_resource const * resource, char const * scope_string)
{
    mangled_ppc("?visit_tag_resource@c_tag_resource_visitor_recursive_visit@@UAAXJPBUs_tag_resource@@PBD@Z");

    m_context->visitor->visit_tag_resource(owner_tag_index, resource, scope_string);
};

void tag_visit_resources_with_redirect(long tag_index, c_tag_marker const * excluded_tags, c_tag_resource_visitor * visitor, c_tag_resource_visit_itinerary * itinerary, c_tag_resource_redirect_directory * redirect_directory)
{
    mangled_ppc("?tag_visit_resources_with_redirect@@YAXJPBVc_tag_marker@@PAVc_tag_resource_visitor@@PAVc_tag_resource_visit_itinerary@@PAVc_tag_resource_redirect_directory@@@Z");

    if (itinerary->should_visit_tag(tag_index))
    {
        c_tag_marker visited_tags;
        if (excluded_tags)
        {
            visited_tags = *excluded_tags;
        }

        s_tag_resource_visit_context context;
        context.excluded_tags = excluded_tags;
        context.visited_tags = &visited_tags;
        context.visitor = visitor;
        context.itinerary = itinerary;
        context.redirect_directory = redirect_directory;
        tag_visit_resources_recursive_internal(tag_index, &context);
    }
};




