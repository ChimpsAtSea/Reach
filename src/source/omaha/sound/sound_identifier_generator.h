#pragma once
#ifndef __SOUND_IDENTIFIER_GENERATOR_H__
#define __SOUND_IDENTIFIER_GENERATOR_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    k_number_of_sound_identifier_type_bits = 3
};

enum e_sound_identifier_type
{
    _sound_identifier_object = 0,
    _sound_identifier_game_sound,
    _sound_identifier_output_effect,
    _sound_identifier_definition,
    _sound_identifier_background_sound,
    _sound_identifier_music,
    k_number_of_sound_identifier_types
};

/* ---------- definitions */

/* ---------- prototypes */

long create_sound_identifier(long datum_index, e_sound_identifier_type type);
unsigned short generate_sound_identifier_salt(e_sound_identifier_type identifier_type);
e_sound_identifier_type sound_identifier_get_type(long sound_identifier);
long sound_identifier_get_datum_index(long sound_identifier, e_sound_identifier_type type);

/* ---------- globals */

/* ---------- public code */

#endif // __SOUND_IDENTIFIER_GENERATOR_H__

