/* ---------- headers */

#include "blamlib\megalogamengine_boundary_state.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void s_megalo_object_boundary_state::initialize(enum e_player_filter_type);
// public: void s_megalo_object_boundary_state::encode(class c_bitstream *) const;
// public: void s_megalo_object_boundary_state::decode(class c_bitstream *);
// public: bool s_megalo_object_boundary_state::build_update(struct s_megalo_object_boundary_state *) const;
// public: void s_megalo_object_boundary_state::apply_update(struct s_megalo_object_boundary_state const *);

void s_megalo_object_boundary_state::initialize(e_player_filter_type filter_type)
{
    mangled_ppc("?initialize@s_megalo_object_boundary_state@@QAAXW4e_player_filter_type@@@Z");

    filter.initialize(filter_type);
    variable_index = NONE;
};

void s_megalo_object_boundary_state::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@s_megalo_object_boundary_state@@QBAXPAVc_bitstream@@@Z");

    filter.encode(bitstream);
    bitstream->write_index<4>("variable-index", variable_index);
};

void s_megalo_object_boundary_state::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@s_megalo_object_boundary_state@@QAAXPAVc_bitstream@@@Z");

    filter.decode(bitstream);
    variable_index = static_cast<char>(bitstream->read_index<4>("variable-index"));
};

bool s_megalo_object_boundary_state::build_update(s_megalo_object_boundary_state * update) const
{
    mangled_ppc("?build_update@s_megalo_object_boundary_state@@QBA_NPAU1@@Z");

    bool result = false;
    if (filter != update->filter || variable_index != update->variable_index)
    {
        update->filter = filter;
        update->variable_index = variable_index;
        result = true;
    }

    return result;
};

void s_megalo_object_boundary_state::apply_update(s_megalo_object_boundary_state const * update)
{
    mangled_ppc("?apply_update@s_megalo_object_boundary_state@@QAAXPBU1@@Z");

    filter = update->filter;
    variable_index = update->variable_index;
};

