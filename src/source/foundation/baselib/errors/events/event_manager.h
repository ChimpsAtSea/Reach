#pragma once
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "foundation\baselib\datatypes\flags.h"
#include "foundation\baselib\datatypes\static_array.h"
#include "foundation\baselib\datatypes\static_stack.h"
#include "foundation\baselib\datatypes\static_string.h"
#include "foundation\baselib\errors\events\event_listener.h"
#include "omaha\math\color_math.h"

/* ---------- constants */

// levels stored in the event manager and its categories use this to mean "no level set"
e_event_level const k_event_level_none = static_cast<e_event_level>(-1);

enum e_event_category
{
    _event_category_none = -1,
    k_event_category_invalid = -1,

    _event_category_root = 0,
};

enum e_event_log_index
{
    k_event_log_invalid = -1,
};

enum e_event_manager_tracked_log
{
    k_event_manager_tracked_log_count = 5
};

enum e_event_response_flags
{
    _event_response_output = 0,
    _event_response_force_output,
    _event_response_log,
    _event_response_log_primary,
    _event_response_debug,
    _event_response_datamine,
    _event_response_debugger_break,
    _event_response_halt,

    k_event_response_flags_count
};

enum e_event_generation_flags
{
    _event_generation_suppressible = 0,

    k_event_generation_flags_count
};

enum e_event_manager_recurse_siblings
{
    _event_manager_recurse_siblings_no = 0,
    _event_manager_recurse_siblings_yes,

    k_event_manager_recurse_siblings_count
};

enum e_event_manager_allow_category_creation
{
    _event_manager_allow_category_creation_no = 0,
    _event_manager_allow_category_creation_yes,

    k_event_manager_allow_category_creation_count
};

long const k_maximum_event_listener_count = 8;
long const k_event_category_name_length = 64;
long const k_event_category_maximum_depth = 8;

enum e_event_manager_category_set_level
{
    _event_manager_category_set_output_level = 0,
    _event_manager_category_set_force_output_level,
    _event_manager_category_set_log_level,
    _event_manager_category_set_debug_level,
    _event_manager_category_set_datamine_level,
    _event_manager_category_set_debugger_break_level,
    _event_manager_category_set_halt_level,

    k_event_manager_category_set_level_count
};

/* ---------- definitions */

class c_event_listener;
class c_event_manager;

typedef void (*event_log_format_function_t)(char * buffer, long buffer_size);
typedef e_event_log_index (*event_log_create_function_t)(char const * log_name);

typedef s_flags<e_event_response_flags, unsigned long, k_event_response_flags_count> c_event_response_flags;
typedef c_flags_zero_init<e_event_generation_flags, unsigned long, k_event_generation_flags_count> c_event_generation_flags;
typedef c_flags_zero_init<e_event_manager_category_set_level, unsigned long, k_event_manager_category_set_level_count> c_event_manager_category_set_level_flags;

struct s_event_category_default_configuration
{
    char const * name; // 0x0
    e_event_level initial_output_level; // 0x4
    real_rgb_color initial_output_color; // 0x8
    e_event_level initial_log_level; // 0x14
    char const * log_name; // 0x18
    event_log_format_function_t log_format_function; // 0x1C
    e_event_level initial_datamine_level; // 0x20
};
static_assert(sizeof(s_event_category_default_configuration) == 0x24, "s_event_category_default_configuration");

struct s_event_category
{
    long depth; // 0x0
    s_static_string<k_event_category_name_length> name; // 0x4
    e_event_level current_output_level; // 0x44
    real_rgb_color current_output_color; // 0x48
    unsigned long last_event_time; // 0x54
    long possible_spam_event_count; // 0x58
    e_event_level current_log_level; // 0x5C
    s_static_string<256> log_name; // 0x60
    event_log_format_function_t log_format_function; // 0x160
    e_event_log_index event_log_index; // 0x164
    e_event_level current_debug_level; // 0x168
    e_event_level current_datamine_level; // 0x16C
    e_event_level current_debugger_break_level; // 0x170
    e_event_level current_halt_level; // 0x174
    e_event_level current_force_output_level; // 0x178
    unsigned long event_listeners; // 0x17C
    e_event_category parent_index; // 0x180
    e_event_category first_child_index; // 0x184
    e_event_category sibling_index; // 0x188
};
static_assert(sizeof(s_event_category) == 0x18C, "s_event_category");

struct s_event_response
{
    c_event_response_flags response_flags; // 0x0
    long event_index; // 0x4
    event_log_format_function_t log_format_function; // 0x8
    e_event_log_index event_log_index; // 0xC
    real_rgb_color output_color; // 0x10
    s_static_array<e_event_log_index, k_event_manager_tracked_log_count> event_log_indices; // 0x1C
    unsigned long event_listeners; // 0x30
    s_static_array<c_event_listener *, k_maximum_event_listener_count> listeners; // 0x34
};
static_assert(sizeof(s_event_response) == 0x54, "s_event_response");

struct s_spamming_event
{
    long hit_count; // 0x0
    unsigned long last_spam_time; // 0x4
    s_static_string<2048> spam_text; // 0x8
};
static_assert(sizeof(s_spamming_event) == 0x808, "s_spamming_event");

struct s_event_spamming_list_add_result
{
    long hit_count; // 0x0
    unsigned long last_spam_time; // 0x4
};
static_assert(sizeof(s_event_spamming_list_add_result) == 0x8, "s_event_spamming_list_add_result");

class c_event_category_visitor
{
public:
    virtual void visit_category(c_event_manager const * manager, e_event_category category_index, s_event_category const * category) = 0;
};

class c_event_manager
{
public:
    void initialize(event_log_create_function_t const create_event_log_function);
    void dispose(void);
    e_event_level get_minimum_level(void) const;
    s_event_category const * get_category_const(e_event_category category_index) const;
    s_event_category * get_category_writable(e_event_category category_index);
    void set_default_categories(long default_category_count, s_event_category_default_configuration const * default_categories);
    void set_output_level(e_event_level level);
    void set_log_level(e_event_level level);
    void set_debug_level(e_event_level level);
    void set_datamine_level(e_event_level level);
    void register_event_log(e_event_manager_tracked_log tracked_log_index, e_event_log_index event_log_index);
    static void build_correct_category_name(char const * category_name, char * out_category_name, long out_category_name_length);
    void visit_categories_recursive(e_event_category category_index, c_event_category_visitor * visitor) const;
    void describe_category(e_event_category category_index, char * out_description, long out_description_length) const;
    e_event_category find_category_from_name(char const * category_name) const;
    e_event_category create_category_from_name(char const * category_name);
    void set_category_level_by_name(char const * category_name, e_event_manager_category_set_level set_level, e_event_level level, c_event_category_visitor * visitor);
    bool register_listener(c_event_listener * listener);
    void unregister_listener(c_event_listener * listener);
    c_event_response_flags query_event(e_event_level event_level, e_event_category category_index, c_event_generation_flags generation_flags) const;
    void finalize_event(e_event_level event_level, e_event_category category_index, c_event_response_flags response_flags, s_static_string<2048> const * event_text, s_event_response * out_response);
    bool get_spam_suppression_enabled(void) const;
    bool get_current_desired_output(void) const;
    long update_spam_lines(long line_count, char const ** out_lines) const;

    void set_events_enabled(bool enabled)
    {
        mangled_ppc("?set_events_enabled@c_event_manager@@QAAX_N@Z");

        m_events_enabled = enabled;
    };

    void set_event_suppression_enabled(bool enabled)
    {
        mangled_ppc("?set_event_suppression_enabled@c_event_manager@@QAAX_N@Z");

        m_event_suppression_enabled = enabled;
    };

    void set_spam_suppression_enabled(bool enabled)
    {
        mangled_ppc("?set_spam_suppression_enabled@c_event_manager@@QAAX_N@Z");

        m_spam_suppression_enabled = enabled;
    };

    void set_output_suppression_enabled(bool enabled)
    {
        mangled_ppc("?set_output_suppression_enabled@c_event_manager@@QAAX_N@Z");

        m_output_suppression_enabled = enabled;
    };

    bool get_output_suppression_enabled(void) const
    {
        mangled_ppc("?get_output_suppression_enabled@c_event_manager@@QBA_NXZ");

        return m_output_suppression_enabled;
    };

    bool get_log_trimming_enabled(void) const
    {
        mangled_ppc("?get_log_trimming_enabled@c_event_manager@@QBA_NXZ");

        return m_log_trimming_enabled;
    };

    void set_log_trimming_enabled(bool enabled)
    {
        mangled_ppc("?set_log_trimming_enabled@c_event_manager@@QAAX_N@Z");

        m_log_trimming_enabled = enabled;
    };

    void set_logs_enabled(bool enabled)
    {
        mangled_ppc("?set_logs_enabled@c_event_manager@@QAAX_N@Z");

        m_logs_enabled = enabled;
    };

private:
    static long const k_maximum_event_category_count = 1024;
    static long const k_maximum_spamming_event_count = 64;

    void recalculate_minimum_level(void);
    void recalculate_minimum_category_level(void);
    void update_minimum_category_level(e_event_level level);
    void visit_categories_recursive(e_event_category category_index, c_event_category_visitor * visitor, e_event_manager_recurse_siblings recurse_siblings) const;
    void set_category_properties_recursive(e_event_category category_index, e_event_level level, c_event_manager_category_set_level_flags set_level_flags, unsigned long event_listener_mask, unsigned long event_listener_value, e_event_manager_recurse_siblings recurse_siblings, c_event_category_visitor * visitor);
    e_event_category find_or_create_category_from_name_internal(char const * category_name, e_event_manager_allow_category_creation allow_creation);
    long parse_category_substrings(char const * category_name, long maximum_category_count, long maximum_category_name_length, char (* const category_names)[k_event_category_name_length]) const;
    e_event_category find_or_create_category_from_substrings_recursive(e_event_category parent_category_index, long category_count, char const (* const category_names)[k_event_category_name_length], e_event_manager_allow_category_creation allow_creation);
    bool query_event_spam_suppression(e_event_level event_level, e_event_category category_index, s_static_string<2048> const * event_text, unsigned long event_time);
    void add_event_to_spamming_list(s_static_string<2048> const * event_text, unsigned long event_time, s_event_spamming_list_add_result * out_result);

    bool m_events_enabled; // 0x0
    bool m_event_suppression_enabled; // 0x1
    bool m_spam_suppression_enabled; // 0x2
    bool m_output_suppression_enabled; // 0x3
    bool m_log_trimming_enabled; // 0x4
    bool m_logs_enabled; // 0x5
    e_event_level m_output_level; // 0x8
    e_event_level m_log_level; // 0xC
    e_event_level m_debug_level; // 0x10
    e_event_level m_datamine_level; // 0x14
    e_event_level m_minimum_level; // 0x18
    e_event_level m_minimum_category_level; // 0x1C
    long m_event_index; // 0x20
    unsigned long m_last_event_time; // 0x24
    c_static_stack<s_event_category, k_maximum_event_category_count> m_categories; // 0x28
    event_log_create_function_t m_create_event_log_function; // 0x6302C
    s_static_array<e_event_log_index, k_event_manager_tracked_log_count> m_event_log_indices; // 0x63030
    s_static_array<c_event_listener *, k_maximum_event_listener_count> m_listeners; // 0x63044
    s_static_array<s_spamming_event, k_maximum_spamming_event_count> m_spamming_events; // 0x63064
};
static_assert(sizeof(c_event_manager) == 0x83264, "c_event_manager");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __EVENT_MANAGER_H__
