#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\effects\\decal_definitions.cpp"
/* ---------- headers */

#include "omaha\effects\decal_definitions.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\tag_files\string_ids.h"
#include "omaha\bitmaps\bitmap_group.h"
#include "omaha\cseries\cseries.h"
#include "core\corelib\cseries\cseries_events.h"

#include <stdio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_block_definition decal_system_block; // "?decal_system_block@@3Us_tag_block_definition@@A"
// struct s_tag_group_legacy_vtable legacy_decal_system_vtable; // "?legacy_decal_system_vtable@@3Us_tag_group_legacy_vtable@@A"
// struct s_tag_group decal_system_group; // "?decal_system_group@@3Us_tag_group@@A"
// public: static float c_decal_definition::x_cull_angle_min; // "?x_cull_angle_min@c_decal_definition@@2MA"
// public: static float c_decal_definition::x_clamp_angle_max; // "?x_clamp_angle_max@c_decal_definition@@2MA"
// public: static float c_decal_definition::x_clamp_angle_default; // "?x_clamp_angle_default@c_decal_definition@@2MA"
// public: static float c_decal_definition::x_cull_angle_default; // "?x_cull_angle_default@c_decal_definition@@2MA"
// private: static float c_decal_system_definition::x_default_distance_fade_start; // "?x_default_distance_fade_start@c_decal_system_definition@@0MA"
// private: static float c_decal_system_definition::x_default_distance_fade_end; // "?x_default_distance_fade_end@c_decal_system_definition@@0MA"
// struct s_tag_group_stream_definition legacy_decal_system_stream_definition; // "?legacy_decal_system_stream_definition@@3Us_tag_group_stream_definition@@A"
// struct s_tag_group_sync_definition legacy_decal_system_xsync_declaration; // "?legacy_decal_system_xsync_declaration@@3Us_tag_group_sync_definition@@A"
// class c_legacy_tag_group_vtable_shim legacy_decal_system_vtable_shim; // "?legacy_decal_system_vtable_shim@@3Vc_legacy_tag_group_vtable_shim@@A"

// public: static bool c_decal_definition::new_block_proc(void *);
// public: static bool c_decal_definition::postprocess_block_proc(long, void *, bool);
// public: void c_decal_definition::set_tangent_frame_required(bool);
// public: void c_decal_definition::set_has_sprite(bool);
// public: void c_decal_definition::set_debug_border_color_white(bool);
// public: void c_decal_definition::set_pass(enum c_decal_definition::e_pass);
// public: void c_decal_definition::set_bitmap_aspect(float);
// public: static bool c_decal_system_definition::postprocess_proc(class c_tag_index, bool);
// public: void c_decal_definition::set_name(long);
// public: class c_decal_definition * c_decal_system_definition::get_decal_definition_modifiable(long);

bool c_decal_definition::new_block_proc(void * element)
{
    mangled_ppc("?new_block_proc@c_decal_definition@@SA_NPAX@Z");

    c_decal_definition * decal_definition = static_cast<c_decal_definition *>(element);
    decal_definition->m_clamp_angle = x_clamp_angle_default;
    decal_definition->m_cull_angle = x_cull_angle_default;

    return true;
};

bool c_decal_definition::postprocess_block_proc(long tag_index, void * element, bool for_editor)
{
    mangled_ppc("?postprocess_block_proc@c_decal_definition@@SA_NJPAX_N@Z");

    c_decal_definition * decal_definition = static_cast<c_decal_definition *>(element);
    decal_definition->m_shader.postprocess_as_child(tag_index, for_editor);

    if (decal_definition->m_cull_angle < x_cull_angle_min)
    {
        decal_definition->m_cull_angle = x_cull_angle_min;
    }
    if (decal_definition->m_clamp_angle > x_clamp_angle_max)
    {
        decal_definition->m_clamp_angle = x_clamp_angle_max;
    }
    if (decal_definition->m_cull_angle < decal_definition->m_clamp_angle)
    {
        decal_definition->m_clamp_angle = decal_definition->m_cull_angle;
    }
    if (decal_definition->m_radius_max < decal_definition->m_radius_min)
    {
        decal_definition->m_radius_max = decal_definition->m_radius_min;
    }
    if (decal_definition->m_lifespan_max < decal_definition->m_lifespan_min)
    {
        decal_definition->m_lifespan_max = decal_definition->m_lifespan_min;
    }
    if (decal_definition->m_decay_max < decal_definition->m_decay_min)
    {
        decal_definition->m_decay_max = decal_definition->m_decay_min;
    }

    if (!for_editor)
    {
        if (decal_definition->m_radius_max <= 0.0f)
        {
            decal_definition->m_radius_min = 0.1f;
            decal_definition->m_radius_max = 0.1f;
        }
        if (decal_definition->m_lifespan_max <= 0.0f)
        {
            decal_definition->m_lifespan_min = k_real_epsilon;
            decal_definition->m_lifespan_max = k_real_epsilon;
        }
        if (decal_definition->m_decay_max <= 0.0f)
        {
            decal_definition->m_decay_min = k_real_epsilon;
            decal_definition->m_decay_max = k_real_epsilon;
        }

        c_render_method_shader_decal const * render_method = decal_definition->get_shader();
        decal_definition->set_pass(static_cast<e_pass>(render_method->test_category_option("render_pass", "post_lighting") != false));

        bool requires_tangent_frame = render_method->test_category_option("bump_mapping", "standard") || !render_method->test_category_option("parallax", "off") || !render_method->test_category_option("interier", "off");
        decal_definition->set_tangent_frame_required(requires_tangent_frame);

        s_render_method_postprocess_definition const * postprocess_definition = render_method->get_postprocess_definition();
        s_tag_reference const * bitmap_reference = NULL;
        if ((postprocess_definition->query_bitmap_reference(s_render_method_postprocess_definition::_query_alpha_map, &bitmap_reference) ||
            postprocess_definition->query_bitmap_reference(s_render_method_postprocess_definition::_query_albedo_base_map_0, &bitmap_reference)) &&
            bitmap_reference->index != NONE)
        {
            bitmap_group const * bitmap = static_cast<bitmap_group const *>(tag_get(BITMAP_GROUP_TAG, bitmap_reference->index));
            decal_definition->set_has_sprite(bitmap->manual_sequences.count > 0 || bitmap->sequences.count > 0);

            bitmap_data const * bitmap_element = static_cast<bitmap_data const *>(tag_block_get_element_with_size(&bitmap->bitmaps, 0, sizeof(bitmap_data)));
            decal_definition->set_bitmap_aspect(static_cast<float>(bitmap_element->width) / static_cast<float>(bitmap_element->height));
        }
        else
        {
            decal_definition->set_bitmap_aspect(1.0f);
            event_wrapped(_event_error, "effects:decals:Couldn't query basemap for decal tag '%s', decal '%s'.  Either the render_method failed to compile, or you have runtime render_method compilation turned off.",
                tag_name_strip_path(tag_get_name(tag_index)),
                string_id_get_string_const(decal_definition->get_name()));
        }

        decal_definition->set_debug_border_color_white(
            render_method->test_category_option("blend_mode", "additive") ||
            render_method->test_category_option("blend_mode", "add_src_times_srcalpha") ||
            render_method->test_category_option("blend_mode", "add_src_times_dstalpha"));
    }

    return true;
};

//public: void c_decal_definition::set_tangent_frame_required(bool)
//{
//    mangled_ppc("?set_tangent_frame_required@c_decal_definition@@QAAX_N@Z");
//};

//public: void c_decal_definition::set_has_sprite(bool)
//{
//    mangled_ppc("?set_has_sprite@c_decal_definition@@QAAX_N@Z");
//};

//public: void c_decal_definition::set_debug_border_color_white(bool)
//{
//    mangled_ppc("?set_debug_border_color_white@c_decal_definition@@QAAX_N@Z");
//};

void c_decal_definition::set_pass(e_pass pass)
{
    mangled_ppc("?set_pass@c_decal_definition@@QAAXW4e_pass@1@@Z");

    m_pass = pass;
};

void c_decal_definition::set_bitmap_aspect(float bitmap_aspect)
{
    mangled_ppc("?set_bitmap_aspect@c_decal_definition@@QAAXM@Z");

    m_bitmap_aspect = bitmap_aspect;
};

bool c_decal_system_definition::postprocess_proc(c_tag_index tag_index, bool for_editor)
{
    mangled_ppc("?postprocess_proc@c_decal_system_definition@@SA_NVc_tag_index@@_N@Z");

    c_decal_system_definition * decal_system = static_cast<c_decal_system_definition *>(tag_get(k_tag_type, tag_index));
    decal_system->m_radius_max = 0.0f;
    for (long decal_index = 0; decal_index < decal_system->m_decals.count; decal_index++)
    {
        c_decal_definition * decal_definition = decal_system->get_decal_definition_modifiable(decal_index);
        char name_string[64];
        if (decal_definition->get_name() == 0)
        {
            long name;
            sprintf(name_string, "decal %d", decal_index);
            name = string_id_retrieve(name_string);
            if (name == -1)
            {
                name = string_id_new(name_string);
            }
            decal_definition->set_name(name);
        }
        decal_system->m_radius_max = MAX(decal_system->m_radius_max, decal_definition->get_radius_max() * FLOOR(decal_definition->get_bitmap_aspect(), 1.0f));
    }

    if (!TEST_BIT(decal_system->m_flags, _overlap_amount_normalized_bit))
    {
        if (decal_system->m_radius_max > k_real_epsilon)
        {
            decal_system->m_overlap_amount = decal_system->m_overlap_amount / decal_system->m_radius_max;
        }
        else
        {
            decal_system->m_overlap_amount = 0.0f;
        }
        SET_BIT(decal_system->m_flags, _overlap_amount_normalized_bit, true);
    }

    if (decal_system->m_distance_fade_start == 0.0f && decal_system->m_distance_fade_end == 0.0f)
    {
        decal_system->m_distance_fade_start = x_default_distance_fade_start;
        decal_system->m_distance_fade_end = x_default_distance_fade_end;
    }
    decal_system->m_distance_fade_end = MAX(decal_system->m_distance_fade_end, decal_system->m_distance_fade_start + k_real_epsilon);

    return true;
};

void c_decal_definition::set_name(long name)
{
    mangled_ppc("?set_name@c_decal_definition@@QAAXJ@Z");

    m_name = name;
};

c_decal_definition * c_decal_system_definition::get_decal_definition_modifiable(long block_index)
{
    mangled_ppc("?get_decal_definition_modifiable@c_decal_system_definition@@QAAPAVc_decal_definition@@J@Z");

    return static_cast<c_decal_definition *>(tag_block_get_element_with_size(&m_decals, block_index, sizeof(c_decal_definition)));
};

