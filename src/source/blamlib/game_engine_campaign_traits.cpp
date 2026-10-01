/* ---------- headers */

#include "blamlib\game_engine_campaign_traits.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: virtual void c_game_engine_campaign_variant::initialize(void);
// public: void c_game_engine_campaign_variant::set(struct s_game_engine_campaign_variant_definition const *);

void c_game_engine_campaign_variant::initialize(void)
{
    mangled_ppc("?initialize@c_game_engine_campaign_variant@@UAAXXZ");

    c_game_engine_base_variant::initialize();
    m_miscellaneous_options.set_round_limit(0);
    m_miscellaneous_options.set_round_time_limit_minutes(0);
};

void c_game_engine_campaign_variant::set(s_game_engine_campaign_variant_definition const * definition)
{
    mangled_ppc("?set@c_game_engine_campaign_variant@@QAAXPBUs_game_engine_campaign_variant_definition@@@Z");

    c_game_engine_base_variant::set(definition, _game_engine_type_campaign);
};

