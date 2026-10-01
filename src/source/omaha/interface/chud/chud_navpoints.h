#pragma once
#ifndef __CHUD_NAVPOINTS_H__
#define __CHUD_NAVPOINTS_H__

/* ---------- headers */

/* ---------- constants */

// names from navpoint_icon_names (megalogamengine_navpoint_state.obj); 11-19 are H3's territory icons ("num" then 8 empty names)
enum e_chud_navpoint_icon_type
{
    _chud_navpoint_icon_type_none = -1,
    _chud_navpoint_icon_type_speaker = 0,
    _chud_navpoint_icon_type_dead_teammate,
    _chud_navpoint_icon_type_unused,
    _chud_navpoint_icon_type_target,
    _chud_navpoint_icon_type_destination,
    _chud_navpoint_icon_type_bomb,
    _chud_navpoint_icon_type_flag,
    _chud_navpoint_icon_type_skull,
    _chud_navpoint_icon_type_king,
    _chud_navpoint_icon_type_vip,
    _chud_navpoint_icon_type_lock,
    _chud_navpoint_icon_type_territory_1,
    _chud_navpoint_icon_type_territory_2,
    _chud_navpoint_icon_type_territory_3,
    _chud_navpoint_icon_type_territory_4,
    _chud_navpoint_icon_type_territory_5,
    _chud_navpoint_icon_type_territory_6,
    _chud_navpoint_icon_type_territory_7,
    _chud_navpoint_icon_type_territory_8,
    _chud_navpoint_icon_type_territory_9,
    _chud_navpoint_icon_type_ordnance,
    _chud_navpoint_icon_type_interface,
    _chud_navpoint_icon_type_recon,
    _chud_navpoint_icon_type_ammunition,
    _chud_navpoint_icon_type_recover,
    _chud_navpoint_icon_type_defend,
    _chud_navpoint_icon_type_neutralize,
    _chud_navpoint_icon_type_coop_spawning,

    k_chud_navpoint_icon_type_count
};

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CHUD_NAVPOINTS_H__

