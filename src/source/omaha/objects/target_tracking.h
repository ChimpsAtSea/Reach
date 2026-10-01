#pragma once
#ifndef __TARGET_TRACKING_H__
#define __TARGET_TRACKING_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_aim_target_object;

// $TODO: layout not reversed yet (stored as c_opaque_data<c_target_tracking_system, 60, 4> in units)
class c_target_tracking_system
{
public:
    bool is_locked() const;
    c_aim_target_object const * get_target() const;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __TARGET_TRACKING_H__

