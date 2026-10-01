#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_effect_definition.cpp"
/* ---------- headers */

#include "omaha\sound\sound_effect_definition.h"
#include "core\corelib\cseries\cseries_asserts.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// char const **sound_effect_input_string_list_definition_strings; // "?sound_effect_input_string_list_definition_strings@@3PAPBDA"
// struct s_string_list_definition sound_effect_input_string_list_definition; // "?sound_effect_input_string_list_definition@@3Us_string_list_definition@@A"
// struct s_tag_reference_definition sound_effect_template_reference; // "?sound_effect_template_reference@@3Us_tag_reference_definition@@A"
// struct s_tag_field *g_sound_effect_override_parameters_fields_v1; // "?g_sound_effect_override_parameters_fields_v1@@3PAUs_tag_field@@A"
// struct s_tag_field *g_sound_effect_override_parameters_fields_v2; // "?g_sound_effect_override_parameters_fields_v2@@3PAUs_tag_field@@A"
// struct s_tag_struct_definition sound_effect_struct_definition; // "?sound_effect_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_field *g_sound_effect_template_fields; // "?g_sound_effect_template_fields@@3PAUs_tag_field@@A"
// struct s_tag_block_definition sound_effect_template_additional_sound_input_block; // "?sound_effect_template_additional_sound_input_block@@3Us_tag_block_definition@@A"
// struct s_tag_struct_definition sound_effect_template_additional_sound_input_block_struct_definition; // "?sound_effect_template_additional_sound_input_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition sound_effect_template_block; // "?sound_effect_template_block@@3Us_tag_block_definition@@A"
// struct s_tag_group sound_effect_template_group; // "?sound_effect_template_group@@3Us_tag_group@@A"
// struct s_tag_group_legacy_vtable legacy_sound_effect_template_vtable; // "?legacy_sound_effect_template_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group_stream_definition legacy_sound_effect_template_stream_definition; // "?legacy_sound_effect_template_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_sound_effect_template_xsync_declaration; // "?legacy_sound_effect_template_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_sound_effect_template_vtable_shim; // "?legacy_sound_effect_template_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// bool convert_legacy_sound_effect_override(unsigned long, struct s_tag_field const *, long, long, void *, struct s_tag_field const *, long, long, void *);
// bool create_default_sound_effect_override(void *);
// bool create_sound_effect_template_parameter(void *);
// bool create_sound_effect_template_sound_input(void *);

// $TODO nonmatching (stack slot order of success/editor; depends on local names)
bool convert_legacy_sound_effect_override(unsigned long group_tag, s_tag_field const * old_fields, long old_count, long old_element_size, void * old_element, s_tag_field const * new_fields, long new_count, long new_element_size, void * new_element)
{
    mangled_ppc("?convert_legacy_sound_effect_override@@YA_NKPBUs_tag_field@@JJPAX0JJ1@Z");

    assert_tag_debug_untracked_jul_11_2011(122, old_fields==g_sound_effect_override_parameters_fields_v1);
    assert_tag_debug_untracked_jul_11_2011(123, new_fields==g_sound_effect_override_parameters_fields_v2);
    assert_tag_debug_untracked_jul_11_2011(124, old_count==1);
    assert_tag_debug_untracked_jul_11_2011(125, new_count==1);
    assert_tag_debug_untracked_jul_11_2011(126, old_count==new_count);
    assert_tag_debug_untracked_jul_11_2011(127, old_element_size==sizeof(s_sound_effect_override_parameter_v1));
    assert_tag_debug_untracked_jul_11_2011(128, new_element_size==sizeof(s_sound_effect_override_parameter));

    bool success = true;
    s_sound_effect_override_parameter_v1 * old_override = static_cast<s_sound_effect_override_parameter_v1 *>(old_element);
    s_sound_effect_override_parameter * new_override = static_cast<s_sound_effect_override_parameter *>(new_element);
    new_override->integer_value = old_override->integer_value;
    new_override->real_value = old_override->real_value;

    c_function_definition_editor editor(&new_override->function_value);
    editor.set_function_type(c_function_definition::_function_type_constant);
    editor.set_color_graph_type(c_function_definition::_function_color_graph_type_scalar);
    editor.set_constant(0, old_override->integer_value != 0 ? static_cast<float>(old_override->integer_value) : (old_override->real_value != 0.0f ? old_override->real_value : 0.0f));

    new_override->input = 0x1B5; // $TODO string_id name unknown
    new_override->time_period = 1.0f;
    new_override->name = old_override->name;

    return success;
};

bool create_default_sound_effect_override(void * element)
{
    mangled_ppc("?create_default_sound_effect_override@@YA_NPAX@Z");

    s_sound_effect_override_parameter * override_parameter = static_cast<s_sound_effect_override_parameter *>(element);
    override_parameter->time_period = 1.0f;
    override_parameter->input = 0x1B5; // $TODO string_id name unknown
    return true;
};

bool create_sound_effect_template_parameter(void * element)
{
    mangled_ppc("?create_sound_effect_template_parameter@@YA_NPAX@Z");

    s_sound_effect_template_parameter_definition * parameter = static_cast<s_sound_effect_template_parameter_definition *>(element);
    {
        c_function_definition_editor editor(&parameter->default_function);
        editor.set_function_type(c_function_definition::_function_type_constant);
        editor.set_ranged(false);
    }
    return true;
};

bool create_sound_effect_template_sound_input(void * element)
{
    mangled_ppc("?create_sound_effect_template_sound_input@@YA_NPAX@Z");

    s_sound_effect_template_sound_input_definition * sound_input = static_cast<s_sound_effect_template_sound_input_definition *>(element);
    {
        c_function_definition_editor editor(&sound_input->low_frequency_sound);
        editor.set_function_type(c_function_definition::_function_type_periodic);
        editor.set_ranged(false);
        editor.set_function_index(0, 2);
        editor.set_amplitude_range_min(0, 0.0f);
        editor.set_amplitude_range_max(0, 1.0f);
        editor.set_clamp_range_min(0.0f);
        editor.set_clamp_range_max(1.0f);
    }
    sound_input->time_period = 1.0f;
    return true;
};
