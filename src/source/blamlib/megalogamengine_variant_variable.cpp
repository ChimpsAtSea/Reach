/* ---------- headers */

#include "omaha\game\megalogamengine\megalogamengine_variant_variable.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void s_variant_variable::encode(class c_bitstream *) const;
// public: void s_variant_variable::decode(class c_bitstream *);
// public: void c_bitstream::write_enum<class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_enum<class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver> >(char const *, class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver> *);
// public: bool c_enum_no_init<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>::in_range(void) const;
// public: void c_enum_no_init<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>::set_raw_value(unsigned char);
// long required_encoding_bits_for_enum<class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver> >(class c_enum<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>);
// public: static enum e_variable_type c_enum_no_init<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>::cast_to_enum<int>(int);
// public: static unsigned char c_enum_no_init<enum e_variable_type, unsigned char, 0, 5, struct s_default_enum_string_resolver>::cast_to_storage<unsigned long>(unsigned long);

void s_variant_variable::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@s_variant_variable@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_enum("variable-type", type);

    switch (type)
    {
    case _variable_type_number:
        reinterpret_cast<c_custom_variable_reference const *>(storage)->encode(bitstream);
        break;
    case _variable_type_player:
        player.encode(bitstream);
        break;
    case _variable_type_team:
        team.encode(bitstream);
        break;
    case _variable_type_object:
        object.encode(bitstream);
        break;
    case _variable_type_timer:
        timer.encode(bitstream);
        break;
    }
};

void s_variant_variable::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@s_variant_variable@@QAAXPAVc_bitstream@@@Z");

    bitstream->read_enum("variable-type", &type);

    switch (type)
    {
    case _variable_type_number:
        reinterpret_cast<c_custom_variable_reference *>(storage)->decode(bitstream);
        break;
    case _variable_type_player:
        player.decode(bitstream);
        break;
    case _variable_type_team:
        team.decode(bitstream);
        break;
    case _variable_type_object:
        object.decode(bitstream);
        break;
    case _variable_type_timer:
        timer.decode(bitstream);
        break;
    }
};








