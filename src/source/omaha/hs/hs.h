#pragma once
#ifndef __HS_H__
#define __HS_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_macros.h"
#include <string.h>

/* ---------- constants */

// $todo remaining types (verify against Reach before extending)
enum e_hs_type
{
    _hs_unparsed = 0,
    _hs_special_form,
    _hs_function_name,
    _hs_passthrough,
    _hs_type_void,
    _hs_type_boolean, // verified against hs_type_names
    _hs_type_real,
    _hs_type_short_integer,
    _hs_type_long_integer,
    _hs_type_string,

    FIRST_HS_TYPE = _hs_type_void,
    NUMBER_OF_HS_NODE_TYPES = 89, // Reach (write_hs_syntax_data_to_cache_file)
};

enum
{
    _hs_syntax_node_primitive_bit = 0,
    _hs_syntax_node_script_bit,
    _hs_syntax_node_variable_bit,
    _hs_syntax_node_permanent_bit,
    _hs_syntax_node_parameter_bit,
    _hs_syntax_node_line_number_bit,
    _hs_syntax_node_stripped_bit,
    NUMBER_OF_HS_SYNTAX_NODE_FLAGS,
};

enum e_hs_thread_type
{
    _hs_thread_type_script = 0,
    _hs_thread_type_global_initialize,
    _hs_thread_type_runtime_evaluate,
    _hs_thread_type_runtime_internal_evaluate,
    _hs_thread_type_command_script,

    NUMBER_OF_HS_THREAD_TYPES,
};

// hs_thread::flags (bit 0 verified in hs_looper.obj)
enum
{
    _hs_thread_in_function_call_bit = 0,
};

/* ---------- definitions */

// layout from IDA (size 0x18)
struct hs_syntax_node
{
    short identifier; // 0x0
    union
    {
        short script_index; // 0x2
        short function_index; // 0x2
        short constant_type; // 0x2
    };
    short type; // 0x4
    unsigned short flags; // 0x6
    long next_node_index; // 0x8
    long source_offset; // 0xC
    unsigned long data; // 0x10
    short line_number; // 0x14
    short pad0; // 0x16
};
static_assert(sizeof(hs_syntax_node) == 0x18, "hs_syntax_node");

struct hs_global_external
{
    char const *name;
    e_hs_type type;
    void *pointer;
};

struct hs_destination_pointer
{
    short destination_type; // 0x0
    short runtime_global_index; // 0x2

    // owned by hs_runtime.obj
    hs_destination_pointer()
    {
        memset(this, 0, sizeof(*this));
    };
};
static_assert(sizeof(hs_destination_pointer) == 0x4, "hs_destination_pointer");

// Reach layout (size 0x52C from hs_runtime_initialize); unknown ranges left as padding
struct hs_thread
{
    short identifier; // 0x0
    short script_index; // 0x2
    short cleanup_script_index; // 0x4
    short pad6; // 0x6
    long sleep_until; // 0x8
    long latent_sleep_until; // 0xC
    unsigned char unknown10[0x10]; // 0x10
    unsigned char type; // 0x20
    unsigned char flags; // 0x21
    unsigned char unknown22[0x52C - 0x22]; // 0x22
};
static_assert(sizeof(hs_thread) == 0x52C, "hs_thread");

/* ---------- prototypes */

// void hs_initialize(void);
// bool hs_scenario_clean(struct scenario *);
// bool hs_scenario_merge(struct scenario *, struct scenario const *);
// void hs_find_or_add_tag_reference(struct scenario *, long);
// bool hs_scenario_postprocess(bool, bool, bool);
// void hs_initialize_for_new_map(void);
// void hs_initialize_for_new_map(bool, bool);
// void hs_dispose_from_old_map(void);
// void hs_reset_time(long);
// void hs_dispose(void);
// float hs_ticks_to_seconds(long);
// long hs_seconds_to_ticks(float);
// void hs_recompile(void);
// void hs_update(void);
// void hs_node_gc(void);
// struct hs_function_definition const * hs_function_get(short);
// short hs_find_script_by_name(long, short);
// short hs_find_tag_reference_by_index(long);
extern hs_global_external * hs_global_external_get(short global_index);
// extern short hs_global_get_type(short designator);
// extern char const * hs_global_get_name(short designator);
// extern short hs_script_find_parameter_by_name(long script_index, char const * name);
// short hs_find_global_by_name(char const *);
// short hs_find_function_by_name(char const *, short, short);
// short hs_verify_function(char const *, short, short);
// void hs_enumerate_special_form_names(void);
// void hs_tokens_enumerate_add_string(char const *);
// void hs_enumerate_script_type_names(void);
// void hs_enumerate_from_string_list(char const **, short, short);
// void hs_enumerate_type_names(void);
// void hs_enumerate_function_names(void);
// void hs_enumerate_script_names(void);
// void hs_enumerate_scenario_data_string_id(short, short, long);
// void hs_enumerate_block_data_string_id(struct s_tag_block const *, short, long);
// void hs_enumerate_variable_names(void);
// void hs_enumerate_scenario_data(short, short, long);
// void hs_enumerate_block_data(struct s_tag_block const *, short, long);
// void hs_enumerate_ai_names(void);
// void hs_enumerate_ai_command_list_names(void);
// void hs_enumerate_ai_command_script_names(void);
// void hs_enumerate_ai_behavior_names(void);
// void hs_enumerate_starting_profile_names(void);
// void hs_enumerate_conversation_names(void);
// void hs_enumerate_object_names(void);
// void hs_enumerate_trigger_volume_names(void);
// void hs_enumerate_cutscene_flag_names(void);
// void hs_enumerate_cutscene_camera_point_names(void);
// void hs_enumerate_cutscene_title_names(void);
// void hs_enumerate_cutscene_recording_names(void);
// void hs_enumerate_enum_skull_names(void);
// void hs_enumerate_enum_fp_evaluator_names(void);
// short hs_tokens_enumerate(char const *, long, char const **, short);
// bool sort_by_found_index(long, long, void const *);
// bool alphabetize(long, long, void const *);
// bool hs_initialize_source_file(struct hs_source_file *, struct s_file_reference *);
// bool hs_rebuild_source_file(struct hs_source_file *, struct s_file_reference const *);
// void hs_build_source_directory(char const *, char *, long, char *, long);
// bool hs_compile_register_error_listener(class c_hs_compile_error_listener *);
// void hs_compile_unregister_error_listener(class c_hs_compile_error_listener *);
// void hs_compile_source_error(char const *, char const *, char const *, char const *);
// void hs_help(char const *);
// void hs_doc(void);
// void hs_get_function_parameters_string(short, char *, long);
// void hs_get_function_documentation_string(short, char *, long);
// bool char_is_delimiter(char, char const *);
// void hs_validify_expression(char const *, char *, long);
// bool hs_compile_and_evaluate(enum e_event_level, char const *, char const *, bool);
// bool hs_compile_and_evaluate_no_networking(enum e_event_level, char const *, char const *, bool);
// void hs_make_interactive_scripts_deterministic(bool);
// bool hs_get_interactive_scripts_deterministic(void);
// void hs_set_executing_determinized_script(bool);
// bool hs_get_executing_determinized_script(void);
extern bool hs_compile_and_evaluate_result(e_event_level event_level, char const *source, char const *expression, bool interactive, bool deterministic, long *result, e_hs_type *result_type);
extern void hs_result_coerce_to_native(long *result, e_hs_type *result_type);
extern void hs_node_gc();
extern void hs_compile_source_error(char const *file_name, char const *error_message, char const *error_source, char const *source);
extern void hs_validify_expression(char const *expression, char *out_valid_expression, long out_valid_expression_size);
// void hs_rebuild_and_compile(char *, long, bool);
// void resize_scenario_syntax_data(long);
// public: c_wrapped_array<char>::ctor<4096>(char (&)[4096]);

/* ---------- globals */

extern short const hs_type_sizes[];

/* ---------- public code */

#endif // __HS_H__
