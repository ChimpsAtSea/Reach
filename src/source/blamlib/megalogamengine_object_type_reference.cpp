/* ---------- headers */

#include "blamlib\megalogamengine_object_type_reference.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"
#include "omaha\game\game_engine_util.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: long c_object_type_reference::get_object_definition_index(void) const;
// public: void c_object_type_reference::initialize(void);
// public: void c_object_type_reference::encode(class c_bitstream *) const;
// public: void c_object_type_reference::decode(class c_bitstream *);
// public: void c_bitstream::write_index<2048, long>(char const *, long);
// public: long c_bitstream::read_index<2048>(char const *);
// long required_encoding_bits_for_index<2048>(void);

long c_object_type_reference::get_object_definition_index(void) const
{
    mangled_ppc("?get_object_definition_index@c_object_type_reference@@QBAJXZ");

    return game_engine_get_object_definition_index_from_global_object_type_index(m_object_type_index);
};

void c_object_type_reference::initialize(void)
{
    mangled_ppc("?initialize@c_object_type_reference@@QAAXXZ");

    m_object_type_index = NONE;
};

void c_object_type_reference::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@c_object_type_reference@@QBAXPAVc_bitstream@@@Z");

    bitstream->write_index<2048>("object-type-index", m_object_type_index);
};

void c_object_type_reference::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@c_object_type_reference@@QAAXPAVc_bitstream@@@Z");

    m_object_type_index = bitstream->read_index<2048>("object-type-index");
};
