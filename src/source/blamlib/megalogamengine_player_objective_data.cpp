/* ---------- headers */

#include "blamlib\megalogamengine_player_objective_data.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"
#include "omaha\game\game_time.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void s_player_objective_data::initialize(void);
// public: bool s_player_objective_data::build_update(struct s_player_objective_data *) const;
// public: void s_player_objective_data::apply_update(struct s_player_objective_data const *);
// public: void s_player_objective_data::encode(class c_bitstream *) const;
// public: void s_player_objective_data::decode(class c_bitstream *);
// public: void c_bitstream::write_index<128, long>(char const *, long);

void s_player_objective_data::initialize(void)
{
    mangled_ppc("?initialize@s_player_objective_data@@QAAXXZ");

    primary_string.initialize();
    allegiance_icon_index = NONE;
    secondary_string.initialize();
    last_update_time = NONE;
};

bool s_player_objective_data::build_update(s_player_objective_data * update) const
{
    mangled_ppc("?build_update@s_player_objective_data@@QBA_NPAU1@@Z");

    bool result = false;
    if (update->primary_string != primary_string ||
        update->allegiance_icon_index != allegiance_icon_index ||
        update->secondary_string != secondary_string)
    {
        result = true;
        update->primary_string = primary_string;
        update->allegiance_icon_index = allegiance_icon_index;
        update->secondary_string = secondary_string;
    }

    return result;
};

void s_player_objective_data::apply_update(s_player_objective_data const * update)
{
    mangled_ppc("?apply_update@s_player_objective_data@@QAAXPBU1@@Z");

    if (update->primary_string != primary_string ||
        update->allegiance_icon_index != allegiance_icon_index ||
        update->secondary_string != secondary_string)
    {
        last_update_time = game_time_get();
        primary_string = update->primary_string;
        allegiance_icon_index = update->allegiance_icon_index;
        secondary_string = update->secondary_string;
    }
};

void s_player_objective_data::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@s_player_objective_data@@QBAXPAVc_bitstream@@@Z");

    primary_string.encode(bitstream);
    bitstream->write_index<128>("allegiance-icon-index", allegiance_icon_index);
    secondary_string.encode(bitstream);
};

void s_player_objective_data::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@s_player_objective_data@@QAAXPAVc_bitstream@@@Z");

    primary_string.decode(bitstream);
    allegiance_icon_index = bitstream->read_index<128>("allegiance-icon-index");
    secondary_string.decode(bitstream);
};
