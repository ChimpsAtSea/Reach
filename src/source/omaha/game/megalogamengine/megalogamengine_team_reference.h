#pragma once
#ifndef __MEGALOGAMENGINE_TEAM_REFERENCE_H__
#define __MEGALOGAMENGINE_TEAM_REFERENCE_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

class c_bitstream;

// $TODO: layout not yet reversed; only the methods used so far are declared
class c_team_reference
{
public:
    void encode(c_bitstream * bitstream) const;
    void decode(c_bitstream * bitstream);
};

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

#endif // __MEGALOGAMENGINE_TEAM_REFERENCE_H__

