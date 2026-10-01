#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\foundation\\baselib\\errors\\events\\event_manager.cpp"
/* ---------- headers */

#include "foundation\baselib\errors\events\event_manager.h"
#include "baselib\system_time_xenon.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "core\corelib\cseries\cseries_string.h"
#include "foundation\baselib\errors\events\event_globals.h"
#include "foundation\baselib\errors\events\event_listener.h"

/* ---------- constants */

// the target's assert text uses strnlen(), which resolves to csstrnlen() in this build
#define strnlen csstrnlen

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// ?initialize@c_event_manager@@QAAXQ6A?AW4e_event_log_index@@PBD@Z@Z;
// public: void c_event_manager::dispose(void);
// public: enum e_event_level c_event_manager::get_minimum_level(void) const;
// public: struct s_event_category const * c_event_manager::get_category_const(enum e_event_category) const;
// public: struct s_event_category * c_event_manager::get_category_writable(enum e_event_category);
// public: void c_event_manager::set_default_categories(long, struct s_event_category_default_configuration const *);
// public: void c_event_manager::set_output_level(enum e_event_level);
// public: void c_event_manager::set_log_level(enum e_event_level);
// public: void c_event_manager::set_debug_level(enum e_event_level);
// public: void c_event_manager::set_datamine_level(enum e_event_level);
// public: void c_event_manager::register_event_log(enum e_event_manager_tracked_log, enum e_event_log_index);
// public: static void c_event_manager::build_correct_category_name(char const *, char *, long);
// public: void c_event_manager::visit_categories_recursive(enum e_event_category, class c_event_category_visitor *) const;
// public: void c_event_manager::describe_category(enum e_event_category, char *, long) const;
// public: enum e_event_category c_event_manager::find_category_from_name(char const *) const;
// public: enum e_event_category c_event_manager::create_category_from_name(char const *);
// public: void c_event_manager::set_category_level_by_name(char const *, enum e_event_manager_category_set_level, enum e_event_level, class c_event_category_visitor *);
// public: bool c_event_manager::register_listener(class c_event_listener *);
// public: void c_event_manager::unregister_listener(class c_event_listener *);
// public: class s_flags<enum e_event_response_flags, unsigned long, 8> c_event_manager::query_event(enum e_event_level, enum e_event_category, class c_flags_zero_init<enum e_event_generation_flags, unsigned long, 1>) const;
// public: void c_event_manager::finalize_event(enum e_event_level, enum e_event_category, class s_flags<enum e_event_response_flags, unsigned long, 8>, class s_static_string<2048> const *, struct s_event_response *);
// public: bool c_event_manager::get_spam_suppression_enabled(void) const;
// public: bool c_event_manager::get_current_desired_output(void) const;
// public: long c_event_manager::update_spam_lines(long, char const **) const;
// private: void c_event_manager::recalculate_minimum_level(void);
// private: void c_event_manager::recalculate_minimum_category_level(void);
// private: void c_event_manager::update_minimum_category_level(enum e_event_level);
// private: void c_event_manager::visit_categories_recursive(enum e_event_category, class c_event_category_visitor *, enum e_event_manager_recurse_siblings) const;
// private: void c_event_manager::set_category_properties_recursive(enum e_event_category, enum e_event_level, class c_flags_zero_init<enum e_event_manager_category_set_level, unsigned long, 7>, unsigned long, unsigned long, enum e_event_manager_recurse_siblings, class c_event_category_visitor *);
// private: enum e_event_category c_event_manager::find_or_create_category_from_name_internal(char const *, enum e_event_manager_allow_category_creation);
// private: long c_event_manager::parse_category_substrings(char const *, long, long, char (*const)[64]) const;
// private: enum e_event_category c_event_manager::find_or_create_category_from_substrings_recursive(enum e_event_category, long, char const (*const)[64], enum e_event_manager_allow_category_creation);
// private: bool c_event_manager::query_event_spam_suppression(enum e_event_level, enum e_event_category, class s_static_string<2048> const *, unsigned long);
// private: void c_event_manager::add_event_to_spamming_list(class s_static_string<2048> const *, unsigned long, struct s_event_spamming_list_add_result *);
// public: static long s_static_array<enum e_event_log_index, 5>::get_count(void);
// public: void s_static_array<class c_event_listener *, 8>::set_memory(long);
// public: bool c_static_stack<struct s_event_category, 1024>::empty(void) const;
// public: bool c_static_stack<struct s_event_category, 1024>::full(void) const;
// public: long c_static_stack<struct s_event_category, 1024>::count(void) const;
// public: void c_static_stack<struct s_event_category, 1024>::clear(void);
// public: long c_static_stack<struct s_event_category, 1024>::push(void);
// public: struct s_event_category const * c_static_stack<struct s_event_category, 1024>::get(long) const;
// public: struct s_event_category * c_static_stack<struct s_event_category, 1024>::get(long);
// public: static long s_static_array<struct s_spamming_event, 64>::get_count(void);
// public: void s_static_array<struct s_spamming_event, 64>::set_memory(long);
// public: c_flags_zero_init<enum e_event_manager_category_set_level, unsigned long, 7>::c_flags_zero_init<enum e_event_manager_category_set_level, unsigned long, 7>(void);
// public: bool c_static_stack<struct s_event_category, 1024>::valid(void) const;
// public: bool c_static_stack<struct s_event_category, 1024>::valid(long) const;
// public: void s_static_string<2048>::set(char const *);
// public: bool s_static_string<2048>::is_equal(char const *) const;
// public: void s_flags<enum e_event_response_flags, unsigned long, 8>::clear(void);
// public: void s_flags<enum e_event_response_flags, unsigned long, 8>::set(enum e_event_response_flags, bool);
// public: enum e_event_log_index & s_static_array<enum e_event_log_index, 5>::operator[]<enum e_event_manager_tracked_log>(enum e_event_manager_tracked_log);
// public: void s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::clear(void);
// public: bool s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::test(enum e_event_manager_category_set_level) const;
// public: void s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::set(enum e_event_manager_category_set_level, bool);
// public: class c_event_listener *& s_static_array<class c_event_listener *, 8>::operator[]<long>(long);
// public: class c_event_listener *& s_static_array<class c_event_listener *, 8>::operator[]<enum e_event_listener>(enum e_event_listener);
// public: bool s_flags<enum e_event_generation_flags, unsigned long, 1>::test(enum e_event_generation_flags) const;
// public: enum e_event_log_index & s_static_array<enum e_event_log_index, 5>::operator[]<long>(long);
// public: struct s_spamming_event const & s_static_array<struct s_spamming_event, 64>::operator[]<long>(long) const;
// enum e_event_level int_min<enum e_event_level>(enum e_event_level const &, enum e_event_level const &);
// public: struct s_spamming_event & s_static_array<struct s_spamming_event, 64>::operator[]<long>(long);
// public: bool s_flags<enum e_event_response_flags, unsigned long, 8>::valid(void) const;
// public: static bool s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::valid_bit(enum e_event_manager_category_set_level);
// public: bool s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::valid(void) const;
// private: static unsigned long s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::flag_size_type(enum e_event_manager_category_set_level);
// public: static bool s_static_array<class c_event_listener *, 8>::valid<enum e_event_listener>(enum e_event_listener);
// public: static bool s_flags<enum e_event_generation_flags, unsigned long, 1>::valid_bit(enum e_event_generation_flags);
// private: static unsigned long s_flags<enum e_event_generation_flags, unsigned long, 1>::flag_size_type(enum e_event_generation_flags);
// public: static bool s_static_array<enum e_event_log_index, 5>::valid<long>(long);
// public: static bool s_static_array<struct s_spamming_event, 64>::valid<long>(long);
// private: static unsigned long s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned long s_flags<enum e_event_manager_category_set_level, unsigned long, 7>::make_N_bit_mask_size_type(enum e_event_manager_category_set_level);

void c_event_manager::initialize(event_log_create_function_t const create_event_log_function)
{
    mangled_ppc("?initialize@c_event_manager@@QAAXQ6A?AW4e_event_log_index@@PBD@Z@Z");

    m_events_enabled = true;
    m_spam_suppression_enabled = true;
    m_output_suppression_enabled = true;
    m_event_suppression_enabled = true;
    m_log_trimming_enabled = true;
    m_logs_enabled = true;
    m_output_level = _event_message;
    m_log_level = _event_message;
    m_debug_level = _event_message;
    m_datamine_level = _event_message;
    m_last_event_time = 0;
    m_listeners.set_memory(0);
    m_spamming_events.set_memory(0);
    m_create_event_log_function = create_event_log_function;
    m_event_log_indices.set_all(k_event_log_invalid);

    assert_tag_debug_untracked_jul_11_2011(73, m_categories.empty());

    s_event_category * root_category = m_categories.get(m_categories.push());
    csmemset(root_category, 0, sizeof(s_event_category));
    root_category->event_log_index = k_event_log_invalid;
    root_category->current_output_level = k_event_level_none;
    root_category->current_output_color.red = 1.0f;
    root_category->current_output_color.green = 1.0f;
    root_category->current_output_color.blue = 1.0f;
    root_category->current_log_level = k_event_level_none;
    root_category->current_debug_level = k_event_level_none;
    root_category->current_datamine_level = k_event_level_none;
    root_category->current_debugger_break_level = k_event_level_none;
    root_category->current_halt_level = k_event_level_none;
    root_category->current_force_output_level = k_event_level_none;
    root_category->parent_index = k_event_category_invalid;
    root_category->first_child_index = k_event_category_invalid;
    root_category->sibling_index = k_event_category_invalid;

    recalculate_minimum_category_level();
    recalculate_minimum_level();
};

void c_event_manager::dispose(void)
{
    mangled_ppc("?dispose@c_event_manager@@QAAXXZ");

    m_categories.clear();
};

e_event_level c_event_manager::get_minimum_level(void) const
{
    mangled_ppc("?get_minimum_level@c_event_manager@@QBA?AW4e_event_level@@XZ");

    return m_minimum_level;
};

s_event_category const * c_event_manager::get_category_const(e_event_category category_index) const
{
    mangled_ppc("?get_category_const@c_event_manager@@QBAPBUs_event_category@@W4e_event_category@@@Z");

    return m_categories.get(category_index);
};

s_event_category * c_event_manager::get_category_writable(e_event_category category_index)
{
    mangled_ppc("?get_category_writable@c_event_manager@@QAAPAUs_event_category@@W4e_event_category@@@Z");

    return m_categories.get(category_index);
};

void c_event_manager::set_default_categories(long default_category_count, s_event_category_default_configuration const * default_categories)
{
    mangled_ppc("?set_default_categories@c_event_manager@@QAAXJPBUs_event_category_default_configuration@@@Z");

    for (long default_category_index = 0; default_category_index < default_category_count; default_category_index++)
    {
        s_event_category_default_configuration const * default_category = &default_categories[default_category_index];
        e_event_category category_index = find_or_create_category_from_name_internal(default_category->name, _event_manager_allow_category_creation_yes);
        s_event_category * category = get_category_writable(category_index);

        category->current_output_level = default_category->initial_output_level;
        category->current_output_color = default_category->initial_output_color;
        category->current_log_level = default_category->initial_log_level;
        category->log_format_function = default_category->log_format_function;
        category->current_datamine_level = default_category->initial_datamine_level;
        category->current_debug_level = default_category->initial_output_level;

        if (default_category->log_name && m_create_event_log_function)
        {
            category->event_log_index = m_create_event_log_function(default_category->log_name);
            if (category->event_log_index != k_event_log_invalid)
            {
                category->log_name.set(default_category->log_name);
            }
            else
            {
                events_internal_error("events: initial category creation failed to create log file '%s'", default_category->log_name);
            }
        }
    }

    recalculate_minimum_category_level();
    recalculate_minimum_level();
};

void c_event_manager::set_output_level(e_event_level level)
{
    mangled_ppc("?set_output_level@c_event_manager@@QAAXW4e_event_level@@@Z");

    assert_tag_debug_untracked_jul_11_2011(174, VALID_INDEX(level, k_event_level_count));

    m_output_level = level;
    recalculate_minimum_level();
};

void c_event_manager::set_log_level(e_event_level level)
{
    mangled_ppc("?set_log_level@c_event_manager@@QAAXW4e_event_level@@@Z");

    assert_tag_debug_untracked_jul_11_2011(182, VALID_INDEX(level, k_event_level_count));

    m_log_level = level;
    recalculate_minimum_level();
};

void c_event_manager::set_debug_level(e_event_level level)
{
    mangled_ppc("?set_debug_level@c_event_manager@@QAAXW4e_event_level@@@Z");

    assert_tag_debug_untracked_jul_11_2011(190, VALID_INDEX(level, k_event_level_count));

    m_debug_level = level;
    recalculate_minimum_level();
};

void c_event_manager::set_datamine_level(e_event_level level)
{
    mangled_ppc("?set_datamine_level@c_event_manager@@QAAXW4e_event_level@@@Z");

    assert_tag_debug_untracked_jul_11_2011(198, VALID_INDEX(level, k_event_level_count));

    m_datamine_level = level;
    recalculate_minimum_level();
};

void c_event_manager::register_event_log(e_event_manager_tracked_log tracked_log_index, e_event_log_index event_log_index)
{
    mangled_ppc("?register_event_log@c_event_manager@@QAAXW4e_event_manager_tracked_log@@W4e_event_log_index@@@Z");

    assert_tag_debug_untracked_jul_11_2011(207, m_event_log_indices[tracked_log_index]==k_event_log_invalid);

    m_event_log_indices[tracked_log_index] = event_log_index;
};

void c_event_manager::build_correct_category_name(char const * category, char * category_out, long category_out_max_size)
{
    mangled_ppc("?build_correct_category_name@c_event_manager@@SAXPBDPADJ@Z");

    assert_tag_debug_untracked_jul_11_2011(217, category);
    assert_tag_debug_untracked_jul_11_2011(218, category_out);
    assert_tag_debug_untracked_jul_11_2011(219, category_out_max_size>0);

    unsigned int category_length = strlen_debug(category);
    bool append_separator = false;
    if (category_length > 0)
    {
        append_separator = category[category_length - 1] != ':';
    }

    csnzprintf(category_out, category_out_max_size, "%s%s", category, append_separator ? ":" : "");
};

void c_event_manager::visit_categories_recursive(e_event_category category_index, c_event_category_visitor * visitor) const
{
    mangled_ppc("?visit_categories_recursive@c_event_manager@@QBAXW4e_event_category@@PAVc_event_category_visitor@@@Z");

    e_event_category start_category_index = category_index;
    if (start_category_index == k_event_category_invalid)
    {
        assert_tag_debug_untracked_jul_11_2011(242, !m_categories.empty());

        start_category_index = _event_category_root;
    }

    visit_categories_recursive(start_category_index, visitor, _event_manager_recurse_siblings_no);
};

void c_event_manager::describe_category(e_event_category category_index, char * buffer, long buffer_length) const
{
    mangled_ppc("?describe_category@c_event_manager@@QBAXW4e_event_category@@PADJ@Z");

    e_event_category current_category = category_index;
    long category_count = 0;
    e_event_category category_indices[k_event_category_maximum_depth];

    assert_tag_debug_untracked_jul_11_2011(259, buffer_length>0);
    assert_tag_debug_untracked_jul_11_2011(260, buffer);

    while (current_category != k_event_category_invalid)
    {
        s_event_category const * category = get_category_const(current_category);
        if (category->depth == 0)
        {
            assert_tag_debug_untracked_jul_11_2011(270, category->parent_index==k_event_category_invalid);
            break;
        }
        else
        {
            assert_tag_debug_untracked_jul_11_2011(275, category_count<NUMBEROF(category_indices));

            category_indices[category_count] = current_category;
            category_count++;
            current_category = category->parent_index;
        }
    }

    csstrnzcpy(buffer, "", buffer_length);
    for (long describe_index = category_count - 1; describe_index >= 0; describe_index--)
    {
        s_event_category const * category = get_category_const(category_indices[describe_index]);
        csstrnzcat(buffer, category->name, buffer_length);
        if (describe_index > 0)
        {
            csstrnzcat(buffer, ":", buffer_length);
        }
    }
};

e_event_category c_event_manager::find_category_from_name(char const * category_name) const
{
    mangled_ppc("?find_category_from_name@c_event_manager@@QBA?AW4e_event_category@@PBD@Z");

    c_event_manager * manager = const_cast<c_event_manager *>(this);
    return manager->find_or_create_category_from_name_internal(category_name, _event_manager_allow_category_creation_no);
};

e_event_category c_event_manager::create_category_from_name(char const * category_name)
{
    mangled_ppc("?create_category_from_name@c_event_manager@@QAA?AW4e_event_category@@PBD@Z");

    return find_or_create_category_from_name_internal(category_name, _event_manager_allow_category_creation_yes);
};

void c_event_manager::set_category_level_by_name(char const * category_name, e_event_manager_category_set_level category_level, e_event_level event_level, c_event_category_visitor * visitor)
{
    mangled_ppc("?set_category_level_by_name@c_event_manager@@QAAXPBDW4e_event_manager_category_set_level@@W4e_event_level@@PAVc_event_category_visitor@@@Z");

    e_event_category category_index = k_event_category_invalid;

    assert_tag_debug_untracked_jul_11_2011(327, VALID_INDEX(category_level, k_event_manager_category_set_level_count));

    s_static_string<256> correct_category_name;
    build_correct_category_name(category_name, correct_category_name.get_buffer(), correct_category_name.max_length());
    category_index = find_or_create_category_from_name_internal(correct_category_name, _event_manager_allow_category_creation_yes);
    if (category_index != k_event_category_invalid)
    {
        c_event_manager_category_set_level_flags set_level_flags;
        set_level_flags.set(category_level, true);
        set_category_properties_recursive(category_index, event_level, set_level_flags, 0, 0, _event_manager_recurse_siblings_no, visitor);
        recalculate_minimum_category_level();
        recalculate_minimum_level();
    }
    else
    {
        events_internal_error("events: failed to set event category level, '%s' is not a valid category", category_name);
    }
};

bool c_event_manager::register_listener(c_event_listener * listener)
{
    mangled_ppc("?register_listener@c_event_manager@@QAA_NPAVc_event_listener@@@Z");

    e_event_listener listener_index = listener->get_listener_index();
    if (listener_index == k_event_listener_invalid)
    {
        for (long index = 0; index < m_listeners.get_count(); index++)
        {
            if (m_listeners[index] == NULL)
            {
                listener_index = static_cast<e_event_listener>(index);
                m_listeners[index] = listener;
                listener->set_listener_index(listener_index);
                break;
            }
        }

        if (listener_index != k_event_listener_invalid)
        {
            char const * category_name = listener->get_category_name();
            e_event_category category_index = k_event_category_invalid;

            assert_tag_debug_untracked_jul_11_2011(373, listener->get_category_index()==k_event_category_invalid);

            s_static_string<256> correct_category_name;
            build_correct_category_name(category_name, correct_category_name.get_buffer(), correct_category_name.max_length());
            category_index = find_or_create_category_from_name_internal(correct_category_name, _event_manager_allow_category_creation_yes);
            if (category_index != k_event_category_invalid)
            {
                unsigned long event_listener_mask = FLAG(listener_index);
                unsigned long event_listener_value = event_listener_mask;
                c_event_manager_category_set_level_flags set_level_flags;
                set_category_properties_recursive(category_index, k_event_level_none, set_level_flags, event_listener_mask, event_listener_value, _event_manager_recurse_siblings_no, NULL);
                listener->set_category_index(category_index);
            }
            else
            {
                events_internal_error("events: failed to attach event listener, '%s' is not a valid category", category_name);
            }
        }
        else
        {
            events_internal_error("events: failed to register listener, too many listeners (max '%d')", m_listeners.get_count());
        }
    }
    else
    {
        assert_tag_debug_untracked_jul_11_2011(402, m_listeners[listener_index]==listener);
    }

    return listener_index != k_event_listener_invalid;
};

void c_event_manager::unregister_listener(c_event_listener * listener)
{
    mangled_ppc("?unregister_listener@c_event_manager@@QAAXPAVc_event_listener@@@Z");

    e_event_listener listener_index = listener->get_listener_index();
    if (listener_index != k_event_listener_invalid)
    {
        e_event_category category_index = listener->get_category_index();

        assert_tag_debug_untracked_jul_11_2011(417, m_listeners[listener_index]==listener);

        if (category_index != k_event_category_invalid)
        {
            unsigned long event_listener_mask = FLAG(listener_index);
            unsigned long const event_listener_value = 0;
            c_event_manager_category_set_level_flags set_level_flags;
            set_category_properties_recursive(category_index, k_event_level_none, set_level_flags, event_listener_mask, event_listener_value, _event_manager_recurse_siblings_no, NULL);
            listener->set_category_index(k_event_category_invalid);
        }

        m_listeners[listener_index] = NULL;
        listener->set_listener_index(k_event_listener_invalid);
    }
    else
    {
        assert_tag_debug_untracked_jul_11_2011(437, m_listeners[listener_index]==listener);
    }

    assert_tag_debug_untracked_jul_11_2011(441, listener->get_listener_index()==k_event_listener_invalid);
    assert_tag_debug_untracked_jul_11_2011(442, listener->get_category_index()==k_event_category_invalid);
};

c_event_response_flags c_event_manager::query_event(e_event_level event_level, e_event_category category_index, c_event_generation_flags generation_flags) const
{
    mangled_ppc("?query_event@c_event_manager@@QBA?AV?$s_flags@W4e_event_response_flags@@K$07@@W4e_event_level@@W4e_event_category@@V?$c_flags_zero_init@W4e_event_generation_flags@@K$00@@@Z");

    c_event_response_flags response_flags;
    response_flags.clear();

    if (m_output_level != k_event_level_none)
    {
        response_flags.set(_event_response_output, event_level >= m_output_level);
    }

    if (m_log_level != k_event_level_none)
    {
        response_flags.set(_event_response_log, event_level >= m_log_level);
        response_flags.set(_event_response_log_primary, event_level >= m_log_level);
    }

    if (m_debug_level != k_event_level_none)
    {
        response_flags.set(_event_response_debug, event_level >= m_debug_level);
    }

    if (m_datamine_level != k_event_level_none)
    {
        response_flags.set(_event_response_datamine, event_level >= m_datamine_level);
    }

    if (category_index != k_event_category_invalid)
    {
        s_event_category const * category = get_category_const(category_index);

        if (category->current_output_level != k_event_level_none)
        {
            response_flags.set(_event_response_output, event_level >= category->current_output_level);
        }

        if (category->current_log_level != k_event_level_none)
        {
            bool log_primary = response_flags.test(_event_response_log_primary);
            response_flags.set(_event_response_log, event_level >= category->current_log_level);
            response_flags.set(_event_response_log_primary, event_level >= category->current_log_level && log_primary);
        }

        if (category->current_debug_level != k_event_level_none)
        {
            response_flags.set(_event_response_debug, event_level >= category->current_debug_level);
        }

        if (category->current_datamine_level != k_event_level_none)
        {
            response_flags.set(_event_response_datamine, event_level >= category->current_datamine_level);
        }

        if (category->current_debugger_break_level != k_event_level_none)
        {
            response_flags.set(_event_response_debugger_break, event_level >= category->current_debugger_break_level);
        }

        if (category->current_halt_level != k_event_level_none)
        {
            response_flags.set(_event_response_halt, event_level >= category->current_halt_level);
        }

        if (category->current_force_output_level != k_event_level_none)
        {
            response_flags.set(_event_response_force_output, event_level >= category->current_force_output_level);
        }
    }

    if (m_event_suppression_enabled && generation_flags.test(_event_generation_suppressible))
    {
        response_flags.set(_event_response_output, false);
    }

    if (!m_logs_enabled)
    {
        response_flags.set(_event_response_log, false);
        response_flags.set(_event_response_log_primary, false);
    }

    return response_flags;
};

void c_event_manager::finalize_event(e_event_level event_level, e_event_category category_index, c_event_response_flags response_flags, s_static_string<2048> const * event_text, s_event_response * out_response)
{
    mangled_ppc("?finalize_event@c_event_manager@@QAAXW4e_event_level@@W4e_event_category@@V?$s_flags@W4e_event_response_flags@@K$07@@PBV?$s_static_string@$0IAA@@@PAUs_event_response@@@Z");

    assert_tag_debug_untracked_jul_11_2011(557, out_response);

    csmemset(out_response, 0, sizeof(s_event_response));
    out_response->response_flags = response_flags;
    out_response->event_index = m_event_index;
    m_event_index++;
    out_response->event_log_index = k_event_log_invalid;

    if (out_response->response_flags.test(_event_response_output))
    {
        unsigned long event_time = system_milliseconds();
        bool is_spam = false;

        m_last_event_time = event_time;
        if (get_spam_suppression_enabled() && !out_response->response_flags.test(_event_response_force_output) && event_level < _event_critical)
        {
            is_spam = query_event_spam_suppression(event_level, category_index, event_text, event_time);
        }

        if (is_spam)
        {
            out_response->response_flags.clear();
        }

        else if (get_output_suppression_enabled())
        {
            out_response->response_flags.set(_event_response_output, false);
        }
    }

    // separate scope: matches the target's stack slot order
    {
        s_event_category const * category = get_category_const(category_index);
        out_response->output_color = category->current_output_color;
        out_response->event_listeners = category->event_listeners;
        if (out_response->response_flags.test(_event_response_log))
        {
            out_response->log_format_function = category->log_format_function;
            out_response->event_log_index = category->event_log_index;
        }

        for (long log_index = 0; log_index < m_event_log_indices.get_count(); log_index++)
        {
            out_response->event_log_indices[log_index] = m_event_log_indices[log_index];
        }

        for (long listener_index = 0; listener_index < m_listeners.get_count(); listener_index++)
        {
            out_response->listeners[listener_index] = m_listeners[listener_index];
        }
    }
};

bool c_event_manager::get_spam_suppression_enabled(void) const
{
    mangled_ppc("?get_spam_suppression_enabled@c_event_manager@@QBA_NXZ");

    return m_spam_suppression_enabled;
};

bool c_event_manager::get_current_desired_output(void) const
{
    mangled_ppc("?get_current_desired_output@c_event_manager@@QBA_NXZ");

    unsigned long current_time = system_milliseconds();
    bool const desired_output = current_time - m_last_event_time <= 1000;

    return desired_output;
};

long c_event_manager::update_spam_lines(long maximum_spam_lines, char const ** out_spam_lines) const
{
    mangled_ppc("?update_spam_lines@c_event_manager@@QBAJJPAPBD@Z");

    unsigned long current_time = system_milliseconds();
    long spam_line_count = 0;

    assert_tag_debug_untracked_jul_11_2011(636, maximum_spam_lines>0);
    assert_tag_debug_untracked_jul_11_2011(637, out_spam_lines);

    for (long spam_index = 0; spam_index < m_spamming_events.get_count(); spam_index++)
    {
        s_spamming_event const * spamming_event = &m_spamming_events[spam_index];
        if (spamming_event->hit_count > 0 && current_time - spamming_event->last_spam_time < 3000 && spamming_event->hit_count >= 2 && spam_line_count < maximum_spam_lines)
        {
            out_spam_lines[spam_line_count] = spamming_event->spam_text.get_string();
            spam_line_count++;
        }
    }

    assert_tag_debug_untracked_jul_11_2011(655, spam_line_count<=maximum_spam_lines);

    return spam_line_count;
};

void c_event_manager::recalculate_minimum_level(void)
{
    mangled_ppc("?recalculate_minimum_level@c_event_manager@@AAAXXZ");

    m_minimum_level = m_minimum_category_level;
    if (m_output_level != k_event_level_none)
    {
        m_minimum_level = int_min(m_minimum_level, m_output_level);
    }

    if (m_log_level != k_event_level_none)
    {
        m_minimum_level = int_min(m_minimum_level, m_log_level);
    }

    if (m_debug_level != k_event_level_none)
    {
        m_minimum_level = int_min(m_minimum_level, m_debug_level);
    }

    if (m_datamine_level != k_event_level_none)
    {
        m_minimum_level = int_min(m_minimum_level, m_datamine_level);
    }
};

void c_event_manager::recalculate_minimum_category_level(void)
{
    mangled_ppc("?recalculate_minimum_category_level@c_event_manager@@AAAXXZ");

    m_minimum_category_level = _event_critical;
    for (long category_index = 0; category_index < m_categories.count(); category_index++)
    {
        s_event_category * category = m_categories.get(category_index);
        update_minimum_category_level(category->current_output_level);
        update_minimum_category_level(category->current_log_level);
        update_minimum_category_level(category->current_debug_level);
        update_minimum_category_level(category->current_datamine_level);
        update_minimum_category_level(category->current_debugger_break_level);
        update_minimum_category_level(category->current_halt_level);
        update_minimum_category_level(category->current_force_output_level);
    }
};

void c_event_manager::update_minimum_category_level(e_event_level level)
{
    mangled_ppc("?update_minimum_category_level@c_event_manager@@AAAXW4e_event_level@@@Z");

    if (level != k_event_level_none)
    {
        m_minimum_category_level = int_min(m_minimum_category_level, level);
    }
};

void c_event_manager::visit_categories_recursive(e_event_category category_index, c_event_category_visitor * visitor, e_event_manager_recurse_siblings recurse_siblings) const
{
    mangled_ppc("?visit_categories_recursive@c_event_manager@@ABAXW4e_event_category@@PAVc_event_category_visitor@@W4e_event_manager_recurse_siblings@@@Z");

    e_event_category current_category = category_index;

    assert_tag_debug_untracked_jul_11_2011(725, visitor);
    assert_tag_debug_untracked_jul_11_2011(726, VALID_INDEX(recurse_siblings, k_event_manager_recurse_siblings_count));

    while (current_category != k_event_category_invalid)
    {
        s_event_category const * category = get_category_const(current_category);
        visitor->visit_category(this, current_category, category);
        visit_categories_recursive(category->first_child_index, visitor, _event_manager_recurse_siblings_yes);
        if (recurse_siblings == _event_manager_recurse_siblings_yes)
        {
            current_category = category->sibling_index;
        }
        else
        {
            current_category = k_event_category_invalid;
        }
    }
};

void c_event_manager::set_category_properties_recursive(e_event_category category_index, e_event_level level, c_event_manager_category_set_level_flags set_level_flags, unsigned long event_listener_mask, unsigned long event_listener_value, e_event_manager_recurse_siblings recurse_siblings, c_event_category_visitor * visitor)
{
    mangled_ppc("?set_category_properties_recursive@c_event_manager@@AAAXW4e_event_category@@W4e_event_level@@V?$c_flags_zero_init@W4e_event_manager_category_set_level@@K$06@@KKW4e_event_manager_recurse_siblings@@PAVc_event_category_visitor@@@Z");

    e_event_category current_category = category_index;

    assert_tag_debug_untracked_jul_11_2011(758, VALID_INDEX(recurse_siblings, k_event_manager_recurse_siblings_count));

    while (current_category != k_event_category_invalid)
    {
        s_event_category * category = get_category_writable(current_category);

        if (set_level_flags.test(_event_manager_category_set_output_level))
        {
            category->current_output_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_force_output_level))
        {
            category->current_force_output_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_log_level))
        {
            category->current_log_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_debug_level))
        {
            category->current_debug_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_datamine_level))
        {
            category->current_datamine_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_debugger_break_level))
        {
            category->current_debugger_break_level = level;
        }

        if (set_level_flags.test(_event_manager_category_set_halt_level))
        {
            category->current_halt_level = level;
        }

        if (event_listener_mask)
        {
            assert_tag_debug_untracked_jul_11_2011(802, (event_listener_value&(~event_listener_mask))==0);

            category->event_listeners = (category->event_listeners & ~event_listener_mask) | event_listener_value;
        }

        if (visitor)
        {
            visitor->visit_category(this, current_category, category);
        }

        set_category_properties_recursive(category->first_child_index, level, set_level_flags, event_listener_mask, event_listener_value, _event_manager_recurse_siblings_yes, visitor);
        if (recurse_siblings == _event_manager_recurse_siblings_yes)
        {
            current_category = category->sibling_index;
        }
        else
        {
            current_category = k_event_category_invalid;
        }
    }
};

e_event_category c_event_manager::find_or_create_category_from_name_internal(char const * category_name, e_event_manager_allow_category_creation allow_creation)
{
    mangled_ppc("?find_or_create_category_from_name_internal@c_event_manager@@AAA?AW4e_event_category@@PBDW4e_event_manager_allow_category_creation@@@Z");

    e_event_category category_index = k_event_category_invalid;

    assert_tag_debug_untracked_jul_11_2011(837, category_name);
    assert_tag_debug_untracked_jul_11_2011(838, VALID_INDEX(allow_creation, k_event_manager_allow_category_creation_count));

    char category_names[k_event_category_maximum_depth][k_event_category_name_length];
    long category_count = parse_category_substrings(category_name, k_event_category_maximum_depth, k_event_category_name_length, category_names);
    if (category_count > 0)
    {
        assert_tag_debug_untracked_jul_11_2011(850, !m_categories.empty());

        category_index = find_or_create_category_from_substrings_recursive(_event_category_root, category_count, category_names, allow_creation);
    }
    else
    {
        category_index = _event_category_root;
    }

    return category_index;
};

// $TODO nonmatching: complete/count stack slots swapped (local names and declaration order drive /Od slot order)
long c_event_manager::parse_category_substrings(char const * category_name, long maximum_category_count, long maximum_category_name_length, char (* const category_names)[k_event_category_name_length]) const
{
    mangled_ppc("?parse_category_substrings@c_event_manager@@ABAJPBDJJQAY0EA@D@Z");

    char const * category = category_name;
    long count = 0;
    long separator_count = 0;
    bool complete = false;
    bool error = false;
    long result = 0;

    do
    {
        char const * substring = category;
        long substring_length = 0;
        bool substring_done = false;

        do
        {
            char c = *category;
            if (substring_length >= maximum_category_name_length)
            {
                events_internal_error("events: can't parse category '%s', substring #%d '%s' exceeded %d characters", category_name, count, substring, maximum_category_name_length);
                error = true;
            }
            else if (ascii_isalnum(c) || c == '-' || c == '_')
            {
                category++;
                substring_length++;
            }
            else
            {
                substring_done = true;
                if (c == ':')
                {
                    category++;
                    separator_count++;
                }
            }
        } while (!substring_done && !error);

        if (substring_done)
        {
            if (substring_length == 0)
            {
                complete = true;
            }
            else if (count >= maximum_category_count)
            {
                events_internal_error("events: can't parse category '%s', category #%d '%s' exceeded %d category substrings", category_name, count, category, maximum_category_count);
                error = true;
            }
            else
            {
                csstrnzcpy(category_names[count], substring, maximum_category_name_length);
                category_names[count][substring_length] = 0;
                ascii_strnlwr(category_names[count], substring_length);
                count++;
            }
        }
    } while (!complete && !error);

    if (error)
    {
        events_internal_error("events: failed to parse category '%s'", category_name);
    }

    result = int_min(count, separator_count);

    return result;
};

e_event_category c_event_manager::find_or_create_category_from_substrings_recursive(e_event_category parent_category_index, long category_count, char const (* const category_names)[k_event_category_name_length], e_event_manager_allow_category_creation allow_creation)
{
    mangled_ppc("?find_or_create_category_from_substrings_recursive@c_event_manager@@AAA?AW4e_event_category@@W42@JQAY0EA@$$CBDW4e_event_manager_allow_category_creation@@@Z");

    e_event_category category_index = k_event_category_invalid;

    assert_tag_debug_untracked_jul_11_2011(966, category_count>0);
    assert_tag_debug_untracked_jul_11_2011(967, strnlen(category_names[0], NUMBEROF(category_names[0]))>0);

    s_event_category const * parent_category_const = get_category_const(parent_category_index);
    e_event_category child_index = parent_category_const->first_child_index;
    while (child_index != k_event_category_invalid)
    {
        s_event_category const * child_category = get_category_const(child_index);
        if (strncmp_debug(child_category->name, category_names[0], child_category->name.max_length()) == 0)
        {
            category_index = child_index;
            break;
        }

        child_index = child_category->sibling_index;
    }

    if (category_index == k_event_category_invalid && allow_creation == _event_manager_allow_category_creation_yes)
    {
        s_event_category * parent = get_category_writable(parent_category_index);
        s_event_category * category = NULL;

        if (parent->depth + 1 < k_event_category_maximum_depth)
        {
            if (!m_categories.full())
            {
                category_index = static_cast<e_event_category>(m_categories.push());
                category = m_categories.get(category_index);
            }
            else
            {
                events_internal_error("event_find_category_recursive: ran out of categories creating '%s'", category_names[0]);
            }
        }
        else
        {
            events_internal_error("event_find_category_recursive: exceeded maximum category depth '%d/%d'", parent->depth + 1, k_event_category_maximum_depth);
        }

        if (category)
        {
            csmemset(category, 0, sizeof(s_event_category));
            category->name.set(category_names[0]);
            category->log_name.set(parent->log_name);
            category->current_output_level = parent->current_output_level;
            category->current_output_color = parent->current_output_color;
            category->current_log_level = parent->current_log_level;
            category->current_debug_level = parent->current_debug_level;
            category->current_datamine_level = parent->current_datamine_level;
            category->current_debugger_break_level = parent->current_debugger_break_level;
            category->current_halt_level = parent->current_halt_level;
            category->current_force_output_level = parent->current_force_output_level;
            category->depth = parent->depth + 1;
            category->parent_index = parent_category_index;
            category->first_child_index = k_event_category_invalid;
            category->sibling_index = parent->first_child_index;
            category->event_log_index = parent->event_log_index;
            category->log_format_function = parent->log_format_function;
            category->event_listeners = parent->event_listeners;
            parent->first_child_index = category_index;
        }
    }

    if (category_index != k_event_category_invalid && category_count > 1)
    {
        category_index = find_or_create_category_from_substrings_recursive(category_index, category_count - 1, category_names + 1, allow_creation);
    }

    return category_index;
};

bool c_event_manager::query_event_spam_suppression(e_event_level event_level, e_event_category category_index, s_static_string<2048> const * event_text, unsigned long event_time)
{
    mangled_ppc("?query_event_spam_suppression@c_event_manager@@AAA_NW4e_event_level@@W4e_event_category@@PBV?$s_static_string@$0IAA@@@K@Z");

    s_event_category * category = get_category_writable(category_index);
    bool suppress = false;

    if (event_time >= category->last_event_time + 10000)
    {
        category->possible_spam_event_count = 0;
    }

    category->possible_spam_event_count++;
    category->last_event_time = event_time;
    if (category->possible_spam_event_count >= 5)
    {
        s_event_spamming_list_add_result add_result;
        add_event_to_spamming_list(event_text, event_time, &add_result);
        if (add_result.hit_count > 1)
        {
            suppress = true;
        }
    }

    return suppress;
};

void c_event_manager::add_event_to_spamming_list(s_static_string<2048> const * event_text, unsigned long event_time, s_event_spamming_list_add_result * out_result)
{
    mangled_ppc("?add_event_to_spamming_list@c_event_manager@@AAAXPBV?$s_static_string@$0IAA@@@KPAUs_event_spamming_list_add_result@@@Z");

    long oldest_spam_index = -1;
    long empty_index = -1;

    assert_tag_debug_untracked_jul_11_2011(1088, event_text);
    assert_tag_debug_untracked_jul_11_2011(1089, out_result);

    csmemset(out_result, 0, sizeof(s_event_spamming_list_add_result));
    for (long spam_index = 0; spam_index < m_spamming_events.get_count(); spam_index++)
    {
        s_spamming_event * spamming_event = &m_spamming_events[spam_index];
        if (spamming_event->hit_count > 0)
        {
            if (event_text->is_equal(spamming_event->spam_text.get_string()))
            {
                out_result->hit_count = spamming_event->hit_count;
                out_result->last_spam_time = spamming_event->last_spam_time;
                spamming_event->last_spam_time = event_time;
                spamming_event->hit_count++;
                break;
            }
            else if (event_time - spamming_event->last_spam_time > 3000)
            {
                csmemset(spamming_event, 0, sizeof(s_spamming_event));
            }
        }

        if (spamming_event->hit_count == 0 && empty_index == -1)
        {
            empty_index = spam_index;
        }
    }

    if (out_result->hit_count == 0 && empty_index != -1)
    {
        s_spamming_event * spamming_event = &m_spamming_events[empty_index];

        assert_tag_debug_untracked_jul_11_2011(1132, spamming_event->hit_count==0);

        spamming_event->hit_count = 1;
        spamming_event->last_spam_time = event_time;
        spamming_event->spam_text.set(event_text->get_string());
    }
};

