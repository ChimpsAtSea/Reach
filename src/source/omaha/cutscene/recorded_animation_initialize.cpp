#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cutscene\\recorded_animation_initialize.cpp"
/* ---------- headers */

#include "omaha\cutscene\recorded_animation_initialize.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\byte_swapping.h"
#include "omaha\units\units.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

struct unit_control_data_entry
{
    byte_swap_definition * bs_def; // 0x0
    long size; // 0x4
    long offset; // 0x8
};
static_assert(sizeof(unit_control_data_entry) == 0xC, "unit_control_data_entry");

/* ---------- prototypes */

/* ---------- globals */

extern long const real_vector2d_bs_codes[2] = { _4byte, _4byte };
extern long const real_vector3d_bs_codes[3] = { _4byte, _4byte, _4byte };

static byte_swap_definition real_vector2d_bs_definition =
{
    "real_vector2d",
    sizeof(vector2d),
    real_vector2d_bs_codes,
    __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__,
    18,
    BYTE_SWAP_DEFINITION_SIGNATURE,
    false
};

static byte_swap_definition real_vector3d_bs_definition =
{
    "real_vector3d",
    sizeof(vector3d),
    real_vector3d_bs_codes,
    __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__,
    23,
    BYTE_SWAP_DEFINITION_SIGNATURE,
    false
};

static unit_control_data_entry unit_control_v1_map[] =
{
    { &byte_bs_definition, sizeof(long), OFFSETOF(unit_control_data, animation_seat) },
    { &byte_bs_definition, sizeof(short), OFFSETOF(unit_control_data, aiming_speed) },
    { &word_bs_definition, sizeof(unsigned __int64), OFFSETOF(unit_control_data, control_flags) },
    { &word_bs_definition, sizeof(short), OFFSETOF(unit_control_data, weapon_set.set_identifier) },
    { &byte_bs_definition, sizeof(char), OFFSETOF(unit_control_data, weapon_set.weapon_indices[0]) },
    { &byte_bs_definition, sizeof(char), OFFSETOF(unit_control_data, weapon_set.weapon_indices[1]) },
    { &word_bs_definition, sizeof(short), NONE }, // skipped: no destination field
    { &real_vector2d_bs_definition, sizeof(vector2d), OFFSETOF(unit_control_data, throttle) },
    { &real_vector3d_bs_definition, sizeof(vector3d), OFFSETOF(unit_control_data, facing_vector) },
    { &real_vector3d_bs_definition, sizeof(vector3d), OFFSETOF(unit_control_data, aiming_vector) },
    { &real_vector3d_bs_definition, sizeof(vector3d), OFFSETOF(unit_control_data, looking_vector) },
    { NULL, NONE, NONE }
};

static unit_control_data_entry unit_control_v2_map[] =
{
    { &long_bs_definition, sizeof(real), OFFSETOF(unit_control_data, primary_trigger) },
    { NULL, NONE, NONE }
};

static unit_control_data_entry unit_control_v3_map[] =
{
    { &word_bs_definition, sizeof(short), OFFSETOF(unit_control_data, grenade_index) },
    { NULL, NONE, NONE }
};

static unit_control_data_entry unit_control_v4_map[] =
{
    { &word_bs_definition, sizeof(short), OFFSETOF(unit_control_data, zoom_level) },
    { NULL, NONE, NONE }
};

static unit_control_data_entry * unit_control_data_map[] =
{
    unit_control_v1_map,
    unit_control_v2_map,
    unit_control_v3_map,
    unit_control_v4_map
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long const *const const real_vector2d_bs_codes; // "?real_vector2d_bs_codes@@3QBJB"
// long const *const const real_vector3d_bs_codes; // "?real_vector3d_bs_codes@@3QBJB"

// void recorded_animation_byteswap_unit_control(char **, unsigned char);
// void recorded_animation_initialize_unit_control(struct unit_control_data *, char const **, unsigned char);
// void recorded_animation_write_unit_control(struct unit_control_data *, char **, unsigned char);

void recorded_animation_byteswap_unit_control(char ** playback_stream, unsigned char unit_version)
{
    mangled_ppc("?recorded_animation_byteswap_unit_control@@YAXPAPADE@Z");

    assert_tag_debug_untracked_jul_11_2011(77, unit_version <= NUMBEROF(unit_control_data_map));

    for (short map_entry_index = 0; map_entry_index < MAX(unit_version, 1); map_entry_index++)
    {
        unit_control_data_entry * offset_entry = unit_control_data_map[map_entry_index];
        while (offset_entry->size != NONE)
        {
            byte_swap_data(offset_entry->bs_def, *playback_stream, 1);
            *playback_stream += offset_entry->size;
            offset_entry++;
        }
    }
};

void recorded_animation_initialize_unit_control(unit_control_data * control, char const ** playback_stream, unsigned char unit_version)
{
    mangled_ppc("?recorded_animation_initialize_unit_control@@YAXPAUunit_control_data@@PAPBDE@Z");

    memset(control, 0, sizeof(unit_control_data));
    control->zoom_level = NONE;

    assert_tag_debug_untracked_jul_11_2011(103, unit_version <= NUMBEROF(unit_control_data_map));

    for (short map_entry_index = 0; map_entry_index < MAX(unit_version, 1); map_entry_index++)
    {
        unit_control_data_entry const * offset_entry = unit_control_data_map[map_entry_index];
        while (offset_entry->size != NONE)
        {
            if (offset_entry->offset != NONE)
            {
                memcpy(reinterpret_cast<char *>(control) + offset_entry->offset, *playback_stream, offset_entry->size);
            }

            *playback_stream += offset_entry->size;
            offset_entry++;
        }
    }
};

void recorded_animation_write_unit_control(unit_control_data * control, char ** playback_stream, unsigned char unit_version)
{
    mangled_ppc("?recorded_animation_write_unit_control@@YAXPAUunit_control_data@@PAPADE@Z");

    assert_tag_debug_untracked_jul_11_2011(129, unit_version <= NUMBEROF(unit_control_data_map));

    for (short map_entry_index = 0; map_entry_index < MAX(unit_version, 1); map_entry_index++)
    {
        unit_control_data_entry const * offset_entry = unit_control_data_map[map_entry_index];
        while (offset_entry->size != NONE)
        {
            memcpy(*playback_stream, reinterpret_cast<char *>(control) + offset_entry->offset, offset_entry->size);
            *playback_stream += offset_entry->size;
            offset_entry++;
        }
    }
};
