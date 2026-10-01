/* ---------- headers */

#include "blamlib\instance_geometry_marker.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

c_scratchpad<c_structure_globals, 6> structure_globals_pad;
__declspec(thread) c_structure_globals * structure_globals_tlsptr;

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// class c_scratchpad<class c_structure_globals, 6> structure_globals_pad; // "?structure_globals_pad@@3V?$c_scratchpad@Vc_structure_globals@@$05@@A"
// class c_structure_globals *structure_globals_tlsptr; // "?structure_globals_tlsptr@@3PAVc_structure_globals@@A"

// class c_structure_globals * get_structure_globals(void);
// public: class c_structure_globals * c_scratchpad<class c_structure_globals, 6>::get_scratchpad(void);
// public: c_scratchpad<class c_structure_globals, 6>::c_scratchpad<class c_structure_globals, 6>(void);
// public: c_scratchpad<class c_structure_globals, 6>::~c_scratchpad<class c_structure_globals, 6>(void);
// void structure_globals_pad::`dynamic atexit destructor'(void);

// $TODO nonmatching: only the TLS slot offset differs (target li 0x284 is the linked .tls offset; ours is the unlinked 0)
c_structure_globals * get_structure_globals(void)
{
    mangled_ppc("?get_structure_globals@@YAPAVc_structure_globals@@XZ");

    if (structure_globals_tlsptr == NULL)
    {
        structure_globals_tlsptr = structure_globals_pad.get_scratchpad();
    }

    return structure_globals_tlsptr;
};
