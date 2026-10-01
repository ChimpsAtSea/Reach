#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\game\\game_engine_player_rating_parameters.cpp"
/* ---------- headers */

#include "omaha\game\game_engine_player_rating_parameters.h"
#include "core\corelib\cseries\cseries_asserts.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\math\real_math.h"
#include "omaha\memory\bitstream.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void s_game_engine_player_rating_parameters::clear(void);
// public: void s_game_engine_player_rating_parameters::initialize_to_default(void);
// public: bool s_game_engine_player_rating_parameters::is_valid(void) const;
// public: float s_game_engine_player_rating_parameters::get_megalo_custom_stat_parameter_weight(long) const;
// public: void s_game_engine_player_rating_parameters::set_megalo_custom_stat_parameter_weight(long, float);
// public: void s_game_engine_player_rating_parameters::encode(class c_bitstream *) const;
// public: void s_game_engine_player_rating_parameters::decode(class c_bitstream *);
// public: void s_static_array<float, 15>::set_memory(long);
// public: void c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::clear(void);
// public: bool c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::valid(void) const;
// public: float & s_static_array<float, 15>::operator[]<long>(long);
// public: void c_bitstream::write_flags<class c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver> >(char const *, class c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>);
// public: void c_bitstream::read_flags<class c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver> >(char const *, class c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver> *);
// public: unsigned char c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::get_unsafe(void) const;
// public: void c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::set_unsafe(unsigned char);
// private: static unsigned char c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::make_mask_with_all_valid_bits_on_size_type(void);
// private: static unsigned char c_flags_no_init<enum e_game_engine_player_rating_flags, unsigned char, 1, struct s_default_enum_string_resolver>::make_N_bit_mask_size_type(enum e_game_engine_player_rating_flags);

void s_game_engine_player_rating_parameters::clear(void)
{
    mangled_ppc("?clear@s_game_engine_player_rating_parameters@@QAAXXZ");

    parameters.set_memory(0);
    flags.clear();
};

void s_game_engine_player_rating_parameters::initialize_to_default(void)
{
    mangled_ppc("?initialize_to_default@s_game_engine_player_rating_parameters@@QAAXXZ");

    clear();

    parameters.m_elements[0] = 1.0f;
    parameters.m_elements[1] = 1.0f;
    parameters.m_elements[2] = 1.0f;
    parameters.m_elements[3] = 1.0f;
    parameters.m_elements[4] = 0.33f;
    parameters.m_elements[5] = 1.0f;
    parameters.m_elements[6] = 1000.0f;
    parameters.m_elements[7] = 1000.0f;
    parameters.m_elements[8] = 0.96f;
};

bool s_game_engine_player_rating_parameters::is_valid(void) const
{
    mangled_ppc("?is_valid@s_game_engine_player_rating_parameters@@QBA_NXZ");

    bool valid = true;

    for (long parameter_index = 0; parameter_index < k_game_engine_player_rating_parameter_count; parameter_index++)
    {
        if (!valid_real(parameters[parameter_index]))
        {
            valid = false;
            break;
        }
    }

    valid = valid && flags.valid();

    return valid;
};

float s_game_engine_player_rating_parameters::get_megalo_custom_stat_parameter_weight(long custom_stat_index) const
{
    mangled_ppc("?get_megalo_custom_stat_parameter_weight@s_game_engine_player_rating_parameters@@QBAMJ@Z");

    assert_tag_debug_untracked_jul_11_2011(61, VALID_INDEX(custom_stat_index, k_maximum_megalo_game_statistics));

    return parameters[custom_stat_index + k_game_engine_player_rating_parameter_first_megalo_custom_stat];
};

void s_game_engine_player_rating_parameters::set_megalo_custom_stat_parameter_weight(long custom_stat_index, float weight)
{
    mangled_ppc("?set_megalo_custom_stat_parameter_weight@s_game_engine_player_rating_parameters@@QAAXJM@Z");

    assert_tag_debug_untracked_jul_11_2011(70, VALID_INDEX(custom_stat_index, k_maximum_megalo_game_statistics));

    parameters[custom_stat_index + k_game_engine_player_rating_parameter_first_megalo_custom_stat] = weight;
};

void s_game_engine_player_rating_parameters::encode(c_bitstream * packet) const
{
    mangled_ppc("?encode@s_game_engine_player_rating_parameters@@QBAXPAVc_bitstream@@@Z");

    for (long parameter_index = 0; parameter_index < k_game_engine_player_rating_parameter_count; parameter_index++)
    {
        unsigned long parameter_bits = reinterpret_cast<unsigned long const &>(parameters[parameter_index]);
        packet->write_integer("player-rating-parameter", parameter_bits, 32);
    }

    packet->write_flags("flags", flags);
};

void s_game_engine_player_rating_parameters::decode(c_bitstream * packet)
{
    mangled_ppc("?decode@s_game_engine_player_rating_parameters@@QAAXPAVc_bitstream@@@Z");

    for (long parameter_index = 0; parameter_index < k_game_engine_player_rating_parameter_count; parameter_index++)
    {
        unsigned long parameter_bits = packet->read_integer("player-rating-parameter", 32);
        parameters[parameter_index] = reinterpret_cast<float const &>(parameter_bits);
    }

    packet->read_flags("flags", &flags);
};

