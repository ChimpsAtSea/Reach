#pragma once
#ifndef __INCIDENT_RESPONSE_DEFINITION_H__
#define __INCIDENT_RESPONSE_DEFINITION_H__

/* ---------- headers */

#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\memory\static_arrays.h"
#include "omaha\memory\wrapped_arrays.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\tag_files\tag_group_definitions.h"
#include "omaha\game\game_mode_definitions.h"

/* ---------- constants */

enum
{
    MAXIMUM_GAME_INCIDENT_RESPONSES_PER_BLOCK = 32,
    MAXIMUM_CHALLENGES_TO_PROGRESS_PER_BLOCK = 64,
};

/* ---------- definitions */

// game_incident_daily_challenge_to_increment_block
struct s_daily_challenge_to_increment
{
    long daily_challenge; // 0x0 string_id
};
static_assert(sizeof(s_daily_challenge_to_increment) == 0x4, "s_daily_challenge_to_increment");

// game_incident_response_block_v1 (upgraded by c_game_incident_response_block_vtable::fixup_old_struct_proc)
struct s_game_incident_response_v1
{
    c_flags<e_game_type_legacy, unsigned char, k_game_type_legacy_count> allowed_game_types; // 0x0
    unsigned char pad1[3]; // 0x1
    long heat_award; // 0x4
    long game_engine_event; // 0x8 string_id
    long medal; // 0xC string_id
    long commendation; // 0x10 string_id
    long achievement; // 0x14 string_id
    s_tag_block challenges; // 0x18 s_daily_challenge_to_increment
    long hs_script; // 0x24 string_id
    short internal_hs_script_index; // 0x28
    unsigned char pad2A[2]; // 0x2A
};
static_assert(sizeof(s_game_incident_response_v1) == 0x2C, "s_game_incident_response_v1");

// game_incident_response_block
struct s_game_incident_response
{
    s_game_mode_flags allowed_game_modes; // 0x0
    long heat_award; // 0x4
    long game_engine_event; // 0x8 string_id
    long medal; // 0xC string_id
    long commendation; // 0x10 string_id
    long achievement; // 0x14 string_id
    long avatar_award; // 0x18 string_id
    s_tag_block challenges; // 0x1C s_daily_challenge_to_increment
    long hs_script; // 0x28 string_id
    short internal_hs_script_index; // 0x2C
    unsigned char pad2E[2]; // 0x2E
};
static_assert(sizeof(s_game_incident_response) == 0x30, "s_game_incident_response");

/* ---------- prototypes */

char * format_game_incident_response_block(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size);
bool postprocess_game_incident_response_block(long tag_index, void * data, bool for_editor);

/* ---------- globals */

// $TODO file-static in the target (0x85314480, not in the map); tag definition data not reconstructed yet
extern s_tag_block_definition game_incident_response_block_v1;

/* ---------- tag struct vtables */

class c_game_incident_response_block_vtable :
    public c_tag_struct_vtable_defaults
{
public:
    static bool postprocess_proc(long tag_index, void * data, bool for_editor)
    {
        mangled_ppc("?postprocess_proc@c_game_incident_response_block_vtable@@SA_NJPAX_N@Z");

        return postprocess_game_incident_response_block(tag_index, data, for_editor);
    }

    static char * format_proc(long tag_index, __int64 field_id, s_tag_block * block, long element_index, char * buffer, long buffer_size)
    {
        mangled_ppc("?format_proc@c_game_incident_response_block_vtable@@SAPADJ_JPAUs_tag_block@@JPADJ@Z");

        return format_game_incident_response_block(tag_index, field_id, block, element_index, buffer, buffer_size);
    }

    static s_tag_struct_definition * get_fixup_source_definition_proc(void)
    {
        mangled_ppc("?get_fixup_source_definition_proc@c_game_incident_response_block_vtable@@SAPAUs_tag_struct_definition@@XZ");

        return const_cast<s_tag_struct_definition *>(game_incident_response_block_v1.struct_definition);
    }

    static bool fixup_old_struct_proc(c_basic_buffer<void> & old_buffer, s_tag_struct_definition const * old_definition, c_basic_buffer<void> & new_buffer, s_tag_struct_definition const * new_definition, c_tag_allocator * allocator, bool byte_swap)
    {
        mangled_ppc("?fixup_old_struct_proc@c_game_incident_response_block_vtable@@SA_NAAV?$c_basic_buffer@X@@PBUs_tag_struct_definition@@01PAVc_tag_allocator@@_N@Z");

        s_game_incident_response_v1 * old_response = old_buffer.checked_cast();
        s_game_incident_response * new_response = new_buffer.checked_cast();
        new_response->heat_award = old_response->heat_award;
        new_response->game_engine_event = old_response->game_engine_event;
        new_response->medal = old_response->medal;
        new_response->commendation = old_response->commendation;
        new_response->achievement = old_response->achievement;
        duplicate_recursive_tag_block_elements(&old_response->challenges, &new_response->challenges);
        new_response->hs_script = old_response->hs_script;
        new_response->internal_hs_script_index = old_response->internal_hs_script_index;
        version_old_allowed_game_type_flags_to_new_flags(&old_response->allowed_game_types, 0, NULL, &new_response->allowed_game_modes);
        return true;
    }
};

/* ---------- globals */

extern c_tag_struct_vtable<c_game_incident_response_block_vtable> game_incident_response_block_struct_struct_vtable;

/* ---------- public code */

#endif // __INCIDENT_RESPONSE_DEFINITION_H__

