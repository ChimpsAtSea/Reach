#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\physics\\collision_bsp_physics_definitions.cpp"
/* ---------- headers */

#include "omaha\physics\collision_bsp_physics_definitions.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_memory.h"
#include "havok\hkpinternal\hkpMoppCodeClass.h"
#include "omaha\physics\havok_mopp_code_definitions.h"
#include "omaha\physics\havok_utilities.h"
#include "havok\hkpcollide\hkpMoppCompilerInput.h"
#include "havok\hkpcollide\hkpMoppUtility.h"
#include "omaha\cseries\cseries.h"
#include "omaha\physics\havok.h"
#include "omaha\physics\havok_memory.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_struct_definition collision_geometry_shape_struct; // "?collision_geometry_shape_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition mopp_bv_tree_shape_struct; // "?mopp_bv_tree_shape_struct@@3Us_tag_struct_definition@@A"
// struct s_tag_struct_definition collision_bsp_physics_block_struct_definition; // "?collision_bsp_physics_block_struct_definition@@3Us_tag_struct_definition@@A"
// struct s_tag_block_definition collision_bsp_physics_block; // "?collision_bsp_physics_block@@3Us_tag_block_definition@@A"
// class c_tag_struct_vtable<class c_null_tag_vtable> collision_geometry_shape_struct_struct_vtable; // "?collision_geometry_shape_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_null_tag_vtable@@@@A"
// class c_tag_struct_vtable<class c_null_tag_vtable> mopp_bv_tree_shape_struct_struct_vtable; // "?mopp_bv_tree_shape_struct_struct_vtable@@3V?$c_tag_struct_vtable@Vc_null_tag_vtable@@@@A"

// bool collision_bsp_physics_build(struct s_collision_bsp_physics_definition *, bool, long, struct s_tag_block *, class c_collision_bsp_reference, float, long);
// bool collision_bsp_physics_fixup(struct s_collision_bsp_physics_definition *, long, long, struct s_tag_block *, class c_collision_bsp_reference);
// void collision_bsp_physics_fixup(struct s_collision_bsp_physics_definition *, long, class hkpMoppCode const *, class c_collision_bsp_reference);

bool collision_bsp_physics_build(s_collision_bsp_physics_definition * collision_bsp_physics_definition, bool build_mopp_codes, long mopp_code_index, s_tag_block * mopp_codes, c_collision_bsp_reference bsp_reference, float scale, long model_definition_index)
{
    mangled_ppc("?collision_bsp_physics_build@@YA_NPAUs_collision_bsp_physics_definition@@_NJPAUs_tag_block@@Vc_collision_bsp_reference@@MJ@Z");

    bool success = false;

    if (bsp_reference.get_surface_count() > 0)
    {
        new (&collision_bsp_physics_definition->collision_geometry_shape) c_collision_geometry_shape(c_collision_geometry_shape::_collision_geometry_shape_type_none, bsp_reference, NONE, NONE, model_definition_index, scale, true, NULL, NULL);

        if (build_mopp_codes)
        {
            hkpMoppCompilerInput mopp_input;
            mopp_input.setAbsoluteFitToleranceOfTriangles(0.0625f);

            havok_prepare_fpu_for_update();
            c_havok_memory_enable_system_allocator enable_system_allocator;
            havok_can_modify_state_allow();

            hkpMoppCode * moppCode = hkpMoppUtility::buildCode(&collision_bsp_physics_definition->collision_geometry_shape, mopp_input, NULL);
            tag_block_resize(mopp_codes, mopp_code_index);
            havok_mopp_code_definitions_append_mopp_code(mopp_codes, moppCode);
            assert_tag_debug_untracked_jul_11_2011(136, moppCode->getReferenceCount()==1);
            moppCode->removeReference();
            moppCode = NULL;

            havok_can_modify_state_disallow();
            havok_restore_fpu_from_update();
        }

        {
            hkpMoppCode * mopp_code = havok_mopp_code_definitions_get_mopp_code(mopp_codes, mopp_code_index);

            assert_tag_debug_untracked_jul_11_2011(153, mopp_code->getReferenceCount()==k_minimum_physics_model_shape_reference_count);

            new (&collision_bsp_physics_definition->mopp_bv_tree_shape) c_mopp_bv_tree_shape(&collision_bsp_physics_definition->collision_geometry_shape, mopp_code, scale, true);

            assert_tag_debug_untracked_jul_11_2011(157, mopp_code->getReferenceCount()==k_minimum_physics_model_shape_reference_count);

            assert_tag_debug_untracked_jul_11_2011(160, pointer_is_aligned(&collision_bsp_physics_definition->collision_geometry_shape, k_havok_alignment_bits));
            assert_tag_debug_untracked_jul_11_2011(161, pointer_is_aligned(&collision_bsp_physics_definition->collision_geometry_shape, k_havok_alignment_bits));
        }

        success = true;
    }

    return success;
};

bool collision_bsp_physics_fixup(s_collision_bsp_physics_definition * collision_bsp_physics_definition, long model_definition_index, long mopp_code_index, s_tag_block * mopp_codes, c_collision_bsp_reference bsp_reference)
{
    mangled_ppc("?collision_bsp_physics_fixup@@YA_NPAUs_collision_bsp_physics_definition@@JJPAUs_tag_block@@Vc_collision_bsp_reference@@@Z");

    bool success = false;

    if (bsp_reference.get_surface_count() > 0)
    {
        havok_mopp_code_definitions_fixup(mopp_codes);

        hkpMoppCode * mopp_code = havok_mopp_code_definitions_get_mopp_code(mopp_codes, mopp_code_index);

        collision_bsp_physics_fixup(collision_bsp_physics_definition, model_definition_index, mopp_code, bsp_reference);

        assert_tag_debug_untracked_jul_11_2011(187, mopp_code->getReferenceCount()==k_minimum_physics_model_shape_reference_count);

        success = true;
    }

    return success;
};

void collision_bsp_physics_fixup(s_collision_bsp_physics_definition * collision_bsp_physics_definition, long model_definition_index, hkpMoppCode const * mopp_code, c_collision_bsp_reference bsp_reference)
{
    mangled_ppc("?collision_bsp_physics_fixup@@YAXPAUs_collision_bsp_physics_definition@@JPBVhkpMoppCode@@Vc_collision_bsp_reference@@@Z");

    new (&collision_bsp_physics_definition->collision_geometry_shape) c_collision_geometry_shape(finish_loaded_object_flag_get(true), bsp_reference);
    new (&collision_bsp_physics_definition->mopp_bv_tree_shape) c_mopp_bv_tree_shape(finish_loaded_object_flag_get(true), 0, &collision_bsp_physics_definition->collision_geometry_shape, mopp_code);

    collision_bsp_physics_definition->collision_geometry_shape.m_model_definition_index = model_definition_index;

    assert_tag_debug_untracked_jul_11_2011(205, pointer_is_aligned(&collision_bsp_physics_definition->collision_geometry_shape, k_havok_alignment_bits));
    assert_tag_debug_untracked_jul_11_2011(206, pointer_is_aligned(&collision_bsp_physics_definition->collision_geometry_shape, k_havok_alignment_bits));
};

