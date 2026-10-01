/* ---------- headers */

#include "blamlib\megalogamengine_progress_bar_state.h"
#include "omaha\cseries\cseries.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: s_progress_bar_state::s_progress_bar_state(void);
// public: void s_progress_bar_state::initialize(void);
// public: bool s_progress_bar_state::operator==(struct s_progress_bar_state const &) const;
// public: bool s_progress_bar_state::operator!=(struct s_progress_bar_state const &) const;
// public: void s_progress_bar_state::encode(class c_bitstream *) const;
// public: void s_progress_bar_state::decode(class c_bitstream *);

s_progress_bar_state::s_progress_bar_state(void)
{
    mangled_ppc("??0s_progress_bar_state@@QAA@XZ");

    initialize();
};

void s_progress_bar_state::initialize(void)
{
    mangled_ppc("?initialize@s_progress_bar_state@@QAAXXZ");

    filter.initialize(_player_filter_type_no_one);
    timer_index = NONE;
};

bool s_progress_bar_state::operator==(s_progress_bar_state const & other) const
{
    mangled_ppc("??8s_progress_bar_state@@QBA_NABU0@@Z");

    return filter == other.filter && timer_index == other.timer_index;
};

bool s_progress_bar_state::operator!=(s_progress_bar_state const & other) const
{
    mangled_ppc("??9s_progress_bar_state@@QBA_NABU0@@Z");

    return !(*this == other);
};

void s_progress_bar_state::encode(c_bitstream * bitstream) const
{
    mangled_ppc("?encode@s_progress_bar_state@@QBAXPAVc_bitstream@@@Z");

    filter.encode(bitstream);
    bitstream->write_index<4>("timer-index", timer_index);
};

void s_progress_bar_state::decode(c_bitstream * bitstream)
{
    mangled_ppc("?decode@s_progress_bar_state@@QAAXPAVc_bitstream@@@Z");

    filter.decode(bitstream);
    timer_index = static_cast<char>(bitstream->read_index<4>("timer-index"));
};
