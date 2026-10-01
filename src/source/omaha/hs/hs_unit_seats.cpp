#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\hs\\hs_unit_seats.cpp"
/* ---------- headers */

#include "omaha\hs\hs_unit_seats.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"
#include "omaha\hs\hs_scenario_definitions.h"
#include "omaha\objects\objects.h"
#include "omaha\objects\object_types.h"
#include "omaha\scenario\scenario.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\unit_definitions.h"
#include "omaha\units\units.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

#define unit_definition_get(definition_index) static_cast< ::unit_definition *>(tag_get(UNIT_DEFINITION_TAG, definition_index))

/* ---------- prototypes */

bool hs_match_unit_seat_internal(long unit_index, long seat_index, long hs_unit_seat_designator);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long hs_get_unit_seats(long, long, enum e_vehicle_seat_desire, enum e_unit_seat_occupancy_type, struct unit_seat_source *, long);
// bool hs_unit_in_seat(long, long);
// bool hs_match_unit_seat_internal(long, long, long);
// long hs_encode_unit_seat_mapping(long, long);
// bool hs_get_unit_seats_from_substring(long, char const *, class c_big_flags_typed_no_init<long, 64> *);

long hs_get_unit_seats(long object_index, long hs_unit_seat_designator, e_vehicle_seat_desire seat_desire_type, e_unit_seat_occupancy_type occupancy_type, unit_seat_source * out_unit_seats, long maximum_seat_count)
{
    mangled_ppc("?hs_get_unit_seats@@YAJJJW4e_vehicle_seat_desire@@W4e_unit_seat_occupancy_type@@PAUunit_seat_source@@J@Z");

    long all_seat_count;
    long matching_seat_count = 0;
    unit_seat_source seat_array_all[64];

    all_seat_count = unit_get_all_seats(object_index, seat_array_all, NUMBEROF(seat_array_all), false);
    for (long unit_seat_index = 0; unit_seat_index < all_seat_count && matching_seat_count < maximum_seat_count; unit_seat_index++)
    {
        unit_seat_source const * source = &seat_array_all[unit_seat_index];
        if (hs_match_unit_seat_internal(source->unit_index, source->seat_index, hs_unit_seat_designator))
        {
            bool valid = true;
            switch (seat_desire_type)
            {
            case _vehicle_seat_desire_any_non_driver:
                {
                    valid = !source->seat->flags.test(_unit_seat_is_driver_bit);
                }
                break;
            case _vehicle_seat_desire_gunner:
                {
                    valid = source->seat->flags.test(_unit_seat_is_gunner_bit);
                }
                break;
            case _vehicle_seat_desire_passenger:
                {
                    valid = !source->seat->flags.test(_unit_seat_is_driver_bit) && !source->seat->flags.test(_unit_seat_is_gunner_bit);
                }
                break;
            case _vehicle_seat_desire_driver:
                {
                    valid = source->seat->flags.test(_unit_seat_is_driver_bit);
                }
                break;
            default:
                break;
            }
            if (valid)
            {
                switch (occupancy_type)
                {
                case _unit_seat_occupied:
                    {
                        valid = unit_seat_filled(source->unit_index, source->seat_index);
                    }
                    break;
                case _unit_seat_empty:
                    {
                        valid = !unit_seat_filled(source->unit_index, source->seat_index);
                    }
                    break;
                default:
                    {
                        valid = true;
                    }
                    break;
                }
                if (valid)
                {
                    out_unit_seats[matching_seat_count] = *source;
                    matching_seat_count++;
                }
            }
        }
    }

    return matching_seat_count;
};

bool hs_unit_in_seat(long unit_index, long hs_unit_seat_designator)
{
    mangled_ppc("?hs_unit_in_seat@@YA_NJJ@Z");

    bool in_matching_seat = false;
    unit_datum * unit = static_cast<unit_datum *>(object_get_and_verify_type(unit_index, _object_mask_unit));
    if (unit->object.parent_object_index != NONE && unit->parent_seat_index != NONE)
    {
        in_matching_seat = hs_match_unit_seat_internal(unit->object.parent_object_index, unit->parent_seat_index, hs_unit_seat_designator);
    }

    return in_matching_seat;
};

bool hs_match_unit_seat_internal(long unit_index, long seat_index, long hs_unit_seat_designator)
{
    mangled_ppc("?hs_match_unit_seat_internal@@YA_NJJJ@Z");

    bool success = false;

    assert_tag_debug_untracked_jul_11_2011(124, seat_index>= 0);
    assert_tag_debug_untracked_jul_11_2011(125, unit_index!=NONE);

    unit_datum * unit = static_cast<unit_datum *>(object_get_and_verify_type(unit_index, _object_mask_unit));
    long unit_definition_index = unit->definition_index;

    assert_tag_debug_untracked_jul_11_2011(128, seat_index<unit_definition_get(unit_definition_index)->unit.seats.count);

    if (hs_unit_seat_designator == -1)
    {
        success = true;
    }
    else
    {
        long seat_mapping_start_index = hs_unit_seat_designator & ((1 << k_hs_unit_seat_count_bits) - 1);
        long seat_mapping_count = static_cast<unsigned long>(hs_unit_seat_designator & ~((1 << k_hs_unit_seat_count_bits) - 1)) >> k_hs_unit_seat_count_bits;
        for (long seat_mapping_offset = 0; seat_mapping_offset < seat_mapping_count; seat_mapping_offset++)
        {
            long seat_mapping_index = seat_mapping_start_index + seat_mapping_offset;
            s_hs_unit_seat_mapping const * seat_mapping = static_cast<s_hs_unit_seat_mapping const *>(tag_block_get_element_with_size(&global_scenario_get()->hs_unit_seats, seat_mapping_index, sizeof(s_hs_unit_seat_mapping)));
            if (seat_mapping->unit_definition_index == unit_definition_index)
            {
                success = seat_mapping->unit_seats.test(seat_index);
                break;
            }
        }
    }

    return success;
};

long hs_encode_unit_seat_mapping(long unit_seat_start_index, long unit_seat_mapping_count)
{
    mangled_ppc("?hs_encode_unit_seat_mapping@@YAJJJ@Z");

    assert_tag_debug_untracked_jul_11_2011(160, VALID_INDEX(unit_seat_start_index, k_maximum_hs_unit_seat_mappings));
    assert_tag_debug_untracked_jul_11_2011(161, IN_RANGE_INCLUSIVE(unit_seat_mapping_count, 0, k_maximum_hs_unit_seat_mappings));
    assert_tag_debug_untracked_jul_11_2011(162, unit_seat_start_index+unit_seat_mapping_count<=k_maximum_hs_unit_seat_mappings);

    return (unit_seat_start_index & ((1 << k_hs_unit_seat_count_bits) - 1)) | ((unit_seat_mapping_count << k_hs_unit_seat_count_bits) & ~((1 << k_hs_unit_seat_count_bits) - 1));
};

bool hs_get_unit_seats_from_substring(long unit_definition_index, char const * seat_substring, c_big_flags_typed_no_init<long, 64> * out_unit_seats)
{
    mangled_ppc("?hs_get_unit_seats_from_substring@@YA_NJPBDPAV?$c_big_flags_typed_no_init@J$0EA@@@@Z");

    assert_tag_debug_untracked_jul_11_2011(172, seat_substring);
    assert_tag_debug_untracked_jul_11_2011(173, out_unit_seats);
    assert_tag_debug_untracked_jul_11_2011(174, unit_definition_index!=NONE);

    bool success = false;
    out_unit_seats->clear();
    {
        unit_definition const * unit_definition = unit_definition_get(unit_definition_index);
        for (long seat_index = 0; seat_index < unit_definition->unit.seats.count; seat_index++)
        {
            unit_seat const * seat = static_cast<unit_seat const *>(tag_block_get_element_with_size(&unit_definition->unit.seats, seat_index, sizeof(unit_seat)));
            char const * seat_label_string = seat->label.get_string();
            if (strstr(seat_label_string, seat_substring) != NULL)
            {
                out_unit_seats->set(seat_index, true);
                success = true;
            }
        }
    }

    return success;
};

