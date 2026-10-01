#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\sound\\sound_identifier_generator.cpp"
/* ---------- headers */

#include "omaha\sound\sound_identifier_generator.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cseries\cseries.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// long create_sound_identifier(long, enum e_sound_identifier_type);
// unsigned short generate_sound_identifier_salt(enum e_sound_identifier_type);
// enum e_sound_identifier_type sound_identifier_get_type(long);
// long sound_identifier_get_datum_index(long, enum e_sound_identifier_type);

long create_sound_identifier(long datum_index, e_sound_identifier_type type)
{
    mangled_ppc("?create_sound_identifier@@YAJJW4e_sound_identifier_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(30, datum_index!=NONE);
    assert_tag_debug_untracked_jul_11_2011(31, VALID_INDEX(type, k_number_of_sound_identifier_types));
    return datum_index | generate_sound_identifier_salt(type);
};

unsigned short generate_sound_identifier_salt(e_sound_identifier_type identifier_type)
{
    mangled_ppc("?generate_sound_identifier_salt@@YAGW4e_sound_identifier_type@@@Z");

    return static_cast<unsigned short>((identifier_type << (16 - k_number_of_sound_identifier_type_bits)) & (((1 << k_number_of_sound_identifier_type_bits) - 1) << (16 - k_number_of_sound_identifier_type_bits)));
};

e_sound_identifier_type sound_identifier_get_type(long sound_identifier)
{
    mangled_ppc("?sound_identifier_get_type@@YA?AW4e_sound_identifier_type@@J@Z");

    return static_cast<e_sound_identifier_type>((sound_identifier & (((1 << k_number_of_sound_identifier_type_bits) - 1) << (16 - k_number_of_sound_identifier_type_bits))) >> (16 - k_number_of_sound_identifier_type_bits));
};

long sound_identifier_get_datum_index(long sound_identifier, e_sound_identifier_type type)
{
    mangled_ppc("?sound_identifier_get_datum_index@@YAJJW4e_sound_identifier_type@@@Z");

    assert_tag_debug_untracked_jul_11_2011(44, sound_identifier_get_type(sound_identifier)==type);
    return sound_identifier & ~generate_sound_identifier_salt(type);
};
