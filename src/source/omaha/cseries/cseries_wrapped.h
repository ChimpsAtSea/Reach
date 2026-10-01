#ifndef __CSERIES_WRAPPED_H__
#define __CSERIES_WRAPPED_H__
#pragma once

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

// $TODO bodies not yet recovered (all "f i" in the target)
template<long k_secondary_index_bits, long k_has_flag>
class c_long_designator
{
public:
    long get_raw_designator(void) const;
    void set_raw_designator(long new_designator);
    long get_primary_index(void) const;
    long get_secondary_index(void) const;
    void set_primary_index(long new_primary_index);
    void set_secondary_index(long new_secondary_index);

private:
    long get_secondary_index_internal(void) const;
    bool get_flag_internal(void) const;
    void set_designator_internal(long primary_index, long secondary_index, bool flag);

    long m_designator;
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __CSERIES_WRAPPED_H__

