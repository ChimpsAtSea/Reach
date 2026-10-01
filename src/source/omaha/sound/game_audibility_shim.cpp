#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\game_audibility_shim.cpp"
/* ---------- headers */

#include "omaha\sound\game_audibility_shim.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "omaha\cseries\cseries.h"
#include "omaha\scenario\scenario_definitions.h"
#include "omaha\sound\game_audibility.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_game_audibility::c_game_audibility(long, long);
// public: s_static_array<class c_wrapped_array<short const>, 16>::s_static_array<class c_wrapped_array<short const>, 16>(void);
// public: bool c_game_audibility::valid(void) const;
// public: void c_game_audibility::get_room_potential_door_set(struct s_cluster_reference, class c_wrapped_flags *) const;
// public: float c_game_audibility::get_cluster_distance(struct s_cluster_reference, struct s_cluster_reference) const;
// public: float c_game_audibility::get_room_distance(long, long) const;
// public: long c_game_audibility::get_room_index(struct s_cluster_reference) const;
// public: void c_game_audibility::get_game_portal_index(long, long *, long *) const;
// public: long c_game_audibility::get_occluded_door_side_of_room(long, struct s_cluster_reference) const;
// public: void c_game_audibility::get_door_room_pas(long, class c_wrapped_flags *, class c_wrapped_flags *) const;
// public: long c_game_audibility::get_closest_door_occluder_room_index_index(long, long);
// public: long c_game_audibility::get_room_count(void) const;
// public: bool c_game_audibility::get_room_ai_deafening(struct s_cluster_reference, struct s_cluster_reference) const;
// public: c_wrapped_array<short const>::c_wrapped_array<short const>(void);
// public: void c_wrapped_array_no_init<short const>::set_elements(short const *, long);
// public: short const & c_array_operator_interface<class c_wrapped_array_no_init<short const>, short const>::operator[](long) const;
// public: short const * c_wrapped_array_no_init<short const>::begin(void) const;
// public: bool c_array_operator_interface<class c_wrapped_array_no_init<short const>, short const>::valid_index(long) const;
// public: class c_wrapped_array_no_init<short const> const * c_recursive_template_pattern<class c_wrapped_array_no_init<short const> >::get_super_class(void) const;
// public: long c_array_operator_interface<class c_wrapped_array_no_init<short const>, short const>::count(void) const;
// public: long c_wrapped_array_no_init<short const>::count(void) const;
// public: class c_wrapped_array<short const> & s_static_array<class c_wrapped_array<short const>, 16>::operator[]<long>(long);
// public: class c_wrapped_array<short const> const & s_static_array<class c_wrapped_array<short const>, 16>::operator[]<char>(char) const;
// public: static bool s_static_array<class c_wrapped_array<short const>, 16>::valid<long>(long);
// public: static bool s_static_array<class c_wrapped_array<short const>, 16>::valid<char>(char);

c_game_audibility::c_game_audibility(long scenario_index, long active_zone_set_index) :
    m_new_audibility(NULL)
{
    mangled_ppc("??0c_game_audibility@@QAA@JJ@Z");

    if (active_zone_set_index != NONE)
    {
        struct scenario const * scenario = static_cast<struct scenario const *>(tag_get(SCENARIO_GROUP_TAG, scenario_index));
        s_scenario_zone_set const * zone_set = static_cast<s_scenario_zone_set const *>(tag_block_get_element_with_size(&scenario->zone_sets, active_zone_set_index, sizeof(s_scenario_zone_set)));
        if (zone_set->audibility_index != NONE)
        {
            m_new_audibility = static_cast<s_game_audibility const *>(tag_block_get_element_with_size(&scenario->zone_set_audibility, zone_set->audibility_index, sizeof(s_game_audibility)));
            for (long bsp_index = 0; bsp_index < scenario->structure_bsps.count; bsp_index++)
            {
                s_game_audibility_bsp_mapping const * audibility_mapping = static_cast<s_game_audibility_bsp_mapping const *>(tag_block_get_element_with_size(&m_new_audibility->bsp_cluster_to_room_index_bounds, bsp_index, sizeof(s_game_audibility_bsp_mapping)));
                short const * indices = static_cast<short const *>(tag_block_get_range_with_size(&m_new_audibility->cluster_reference_to_room_index_storage, audibility_mapping->first_room_index_index, audibility_mapping->room_index_count, sizeof(short)));
                m_cluster_reference_to_room_index[bsp_index].set_elements(indices, audibility_mapping->room_index_count);
            }
        }
    }
};

bool c_game_audibility::valid() const
{
    mangled_ppc("?valid@c_game_audibility@@QBA_NXZ");

    return m_new_audibility != NULL;
};

void c_game_audibility::get_room_potential_door_set(s_cluster_reference room_cluster_reference, c_wrapped_flags * out_door_flags) const
{
    mangled_ppc("?get_room_potential_door_set@c_game_audibility@@QBAXUs_cluster_reference@@PAVc_wrapped_flags@@@Z");

    if (m_new_audibility != NULL)
    {
        long room_index = get_room_index(room_cluster_reference);
        audibility_get_room_potential_door_set(m_new_audibility, room_index, out_door_flags);
    }
    else
    {
        out_door_flags->clear();
    }
};

float c_game_audibility::get_cluster_distance(s_cluster_reference start_cluster_reference, s_cluster_reference end_cluster_reference) const
{
    mangled_ppc("?get_cluster_distance@c_game_audibility@@QBAMUs_cluster_reference@@0@Z");

    float distance = 0.0f;
    if (m_new_audibility != NULL)
    {
        long start_room_index = get_room_index(start_cluster_reference);
        long end_room_index = get_room_index(end_cluster_reference);
        distance = audibility_get_room_distance(m_new_audibility, start_room_index, end_room_index);
    }
    return distance;
};

float c_game_audibility::get_room_distance(long start_room_index, long end_room_index) const
{
    mangled_ppc("?get_room_distance@c_game_audibility@@QBAMJJ@Z");

    float distance = 0.0f;
    if (m_new_audibility != NULL)
    {
        distance = audibility_get_room_distance(m_new_audibility, start_room_index, end_room_index);
    }
    return distance;
};

long c_game_audibility::get_room_index(s_cluster_reference room_cluster_reference) const
{
    mangled_ppc("?get_room_index@c_game_audibility@@QBAJUs_cluster_reference@@@Z");

    long room_index = NONE;
    if (m_new_audibility != NULL)
    {
        room_index = m_cluster_reference_to_room_index[room_cluster_reference.bsp_index][room_cluster_reference.cluster_index];
    }
    return room_index;
};

void c_game_audibility::get_game_portal_index(long door_occluder_index, long * out_structure_bsp_index, long * out_game_portal_index) const
{
    mangled_ppc("?get_game_portal_index@c_game_audibility@@QBAXJPAJ0@Z");

    audibility_door_occluder_to_game_portal_index(m_new_audibility, door_occluder_index, out_structure_bsp_index, out_game_portal_index);
};

long c_game_audibility::get_occluded_door_side_of_room(long door_occluder_index, s_cluster_reference room_cluster_reference) const
{
    mangled_ppc("?get_occluded_door_side_of_room@c_game_audibility@@QBAJJUs_cluster_reference@@@Z");

    long door_side = NONE;
    if (m_new_audibility != NULL)
    {
        c_wrapped_flags door_room_pas[2];
        audibility_get_door_room_pas(m_new_audibility, door_occluder_index, &door_room_pas[0], &door_room_pas[1]);
        long room_index = get_room_index(room_cluster_reference);
        if (door_room_pas[0].test(room_index))
        {
            door_side = 1;
        }
        else if (door_room_pas[1].test(room_index))
        {
            door_side = 0;
        }
    }
    return door_side;
};

void c_game_audibility::get_door_room_pas(long door_occluder_index, c_wrapped_flags * front_side_rooms, c_wrapped_flags * back_side_rooms) const
{
    mangled_ppc("?get_door_room_pas@c_game_audibility@@QBAXJPAVc_wrapped_flags@@0@Z");

    if (m_new_audibility != NULL)
    {
        audibility_get_door_room_pas(m_new_audibility, door_occluder_index, front_side_rooms, back_side_rooms);
    }
    else
    {
        front_side_rooms->clear();
        back_side_rooms->clear();
    }
};

long c_game_audibility::get_closest_door_occluder_room_index_index(long door_occluder_index, long source_room_index)
{
    mangled_ppc("?get_closest_door_occluder_room_index_index@c_game_audibility@@QAAJJJ@Z");

    long room_index_index = NONE;
    if (m_new_audibility != NULL)
    {
        room_index_index = audibility_get_closest_door_portal_room_index_index(m_new_audibility, door_occluder_index, source_room_index);
    }
    return room_index_index;
};

long c_game_audibility::get_room_count() const
{
    mangled_ppc("?get_room_count@c_game_audibility@@QBAJXZ");

    long room_count = 0;
    if (m_new_audibility != NULL)
    {
        room_count = m_new_audibility->room_count;
    }
    return room_count;
};

bool c_game_audibility::get_room_ai_deafening(s_cluster_reference start_cluster_reference, s_cluster_reference end_cluster_reference) const
{
    mangled_ppc("?get_room_ai_deafening@c_game_audibility@@QBA_NUs_cluster_reference@@0@Z");

    bool deafening = false;
    if (m_new_audibility != NULL)
    {
        long start_room_index = get_room_index(start_cluster_reference);
        long end_room_index = get_room_index(end_cluster_reference);
        deafening = audibility_get_room_ai_deafening(m_new_audibility, start_room_index, end_room_index);
    }
    return deafening;
};
