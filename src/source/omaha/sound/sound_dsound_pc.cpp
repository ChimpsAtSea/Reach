/* ---------- headers */

#include "omaha\sound\sound_dsound_pc.h"
#include "omaha\sound\sound_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// bool platform_sound_valid_sound_definition_pc(struct sound_definition const *);
// bool platform_sound_should_reimport_sound_definition_pc(struct sound_definition const *);

bool platform_sound_valid_sound_definition_pc(sound_definition const * definition)
{
    mangled_ppc("?platform_sound_valid_sound_definition_pc@@YA_NPBUsound_definition@@@Z");

    return definition->get_compression() == _sound_compression_none_be || definition->get_compression() == _sound_compression_xbox_adpcm;
};

bool platform_sound_should_reimport_sound_definition_pc(sound_definition const * definition)
{
    mangled_ppc("?platform_sound_should_reimport_sound_definition_pc@@YA_NPBUsound_definition@@@Z");

    return false;
};
