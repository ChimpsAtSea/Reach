/* ---------- headers */

#include "blamlib\sound_xaudio_xenon_voice_manager.h"
#include "omaha\game\player_mapping.h"
#include "omaha\math\real_math.h"
#include "omaha\sound\game_sound_definitions.h"
#include "omaha\sound\platform_sound.h"
#include "omaha\sound\sound_xaudio_xenon_3d_voice.h"
#include "omaha\sound\sound_xaudio_xenon_mix_master.h"
#include <xtl.h>
#include <x3daudio.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void copy_to_xaudio_vector(D3DVECTOR & out_vector, vector3d const & vector);
void copy_to_xaudio_position(D3DVECTOR & out_position, real_point3d const & point);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: void c_xenon_audio_voice_manager::initialize(class c_xenon_audio_source_manager *, float);
// public: void c_xenon_audio_voice_manager::dispose(void);
// public: void c_xenon_audio_voice_manager::update_listeners(struct s_platform_sound_listener const *, class c_flags<long, unsigned long, 4, struct s_default_enum_string_resolver>);
// void copy_to_xaudio_vector(struct _D3DVECTOR &, union vector3d const &);
// void copy_to_xaudio_position(struct _D3DVECTOR &, union real_point3d const &);
// public: static void c_xenon_audio_voice_manager::update_voice_status(struct s_platform_sound_status *);
// public: static bool c_xenon_audio_voice_manager::voice_is_idle_async(long);
// public: static void c_xenon_audio_voice_manager::voice_initialize_properties(long);
// public: void c_xenon_audio_voice_manager::voice_update_properties(long, struct s_platform_sound_voice_update_definition const *, float);
// public: void c_xenon_audio_voice_manager::voice_get_platform_output(long, struct s_xaudio_voice_mix_state const *, struct s_xaudio_voice_setup const *, struct s_xaudio_platform_output *, float *);
// public: void c_big_flags_typed_no_init<long, 212>::set_all(void);
// public: bool c_flags_no_init<long, unsigned long, 4, struct s_default_enum_string_resolver>::test(long) const;
// public: struct X3DAUDIO_LISTENER & s_static_array<struct X3DAUDIO_LISTENER, 4>::operator[]<long>(long);
// public: struct X3DAUDIO_LISTENER & s_static_array<struct X3DAUDIO_LISTENER, 4>::operator[]<enum e_output_user_index>(enum e_output_user_index);
// public: class c_xaudio_voice_speaker_datum & s_static_array<class c_xaudio_voice_speaker_datum, 212>::operator[]<long>(long);
// private: static unsigned long c_flags_no_init<long, unsigned long, 4, struct s_default_enum_string_resolver>::flag_size_type(long);
// public: static bool s_static_array<struct X3DAUDIO_LISTENER, 4>::valid<long>(long);
// public: static bool s_static_array<struct X3DAUDIO_LISTENER, 4>::valid<enum e_output_user_index>(enum e_output_user_index);
// public: static bool s_static_array<class c_xaudio_voice_speaker_datum, 212>::valid<long>(long);

void c_xenon_audio_voice_manager::initialize(c_xenon_audio_source_manager * source_manager, float speed_of_sound)
{
    mangled_ppc("?initialize@c_xenon_audio_voice_manager@@QAAXPAVc_xenon_audio_source_manager@@M@Z");

    X3DAudioInitialize(SPEAKER_5POINT1, speed_of_sound, m_x3d_audio_object);
    m_source_manager = source_manager;
};

void c_xenon_audio_voice_manager::dispose(void)
{
    mangled_ppc("?dispose@c_xenon_audio_voice_manager@@QAAXXZ");

    m_source_manager = NULL;
};

void c_xenon_audio_voice_manager::update_listeners(s_platform_sound_listener const * new_listeners, c_flags<long, unsigned long, 4> valid_listeners)
{
    mangled_ppc("?update_listeners@c_xenon_audio_voice_manager@@QAAXPBUs_platform_sound_listener@@V?$c_flags@JK$03Us_default_enum_string_resolver@@@@@Z");

    m_valid_listeners = valid_listeners;
    for (long listener_index = 0; listener_index < k_maximum_xaudio_listeners; listener_index++)
    {
        if (m_valid_listeners.test(listener_index))
        {
            X3DAUDIO_LISTENER & hardware_listener = m_listeners[listener_index];
            copy_to_xaudio_vector(hardware_listener.OrientFront, new_listeners[listener_index].forward);
            copy_to_xaudio_vector(hardware_listener.OrientTop, new_listeners[listener_index].up);
            copy_to_xaudio_position(hardware_listener.Position, new_listeners[listener_index].position);
            copy_to_xaudio_vector(hardware_listener.Velocity, new_listeners[listener_index].velocity);
        }
    }
};

void copy_to_xaudio_vector(D3DVECTOR & out_vector, vector3d const & vector)
{
    mangled_ppc("?copy_to_xaudio_vector@@YAXAAU_D3DVECTOR@@ABTvector3d@@@Z");

    out_vector.x = vector.i;
    out_vector.y = vector.j;
    out_vector.z = vector.k;
};

void copy_to_xaudio_position(D3DVECTOR & out_position, real_point3d const & point)
{
    mangled_ppc("?copy_to_xaudio_position@@YAXAAU_D3DVECTOR@@ABTreal_point3d@@@Z");

    out_position.x = point.x;
    out_position.y = point.y;
    out_position.z = point.z;
};

void c_xenon_audio_voice_manager::update_voice_status(s_platform_sound_status * out_platform_status)
{
    mangled_ppc("?update_voice_status@c_xenon_audio_voice_manager@@SAXPAUs_platform_sound_status@@@Z");

    out_platform_status->available_voices.set_all();
    for (long source_index = 0; source_index < 196; source_index++)
    {
        out_platform_status->available_voices.set(source_index, out_platform_status->available_sources.test(source_index));
    }
};

bool c_xenon_audio_voice_manager::voice_is_idle_async(long voice_index)
{
    mangled_ppc("?voice_is_idle_async@c_xenon_audio_voice_manager@@SA_NJ@Z");

    return true;
};

void c_xenon_audio_voice_manager::voice_initialize_properties(long voice_index)
{
    mangled_ppc("?voice_initialize_properties@c_xenon_audio_voice_manager@@SAXJ@Z");
};

void c_xenon_audio_voice_manager::voice_update_properties(long voice_index, s_platform_sound_voice_update_definition const * voice_update, float doppler_scale)
{
    mangled_ppc("?voice_update_properties@c_xenon_audio_voice_manager@@QAAXJPBUs_platform_sound_voice_update_definition@@M@Z");

    if (m_valid_listeners.test(voice_update->listener_index))
    {
        X3DAUDIO_LISTENER const & hardware_listener = m_listeners[static_cast<e_output_user_index>(voice_update->listener_index)];
        m_voice_data[voice_index].calculate(m_x3d_audio_object, &hardware_listener, voice_update, doppler_scale);
    }
};

void c_xenon_audio_voice_manager::voice_get_platform_output(long voice_index, s_xaudio_voice_mix_state const * mix_state, s_xaudio_voice_setup const * voice_setup, s_xaudio_platform_output * in_out_platform_output, float * out_distance_orientation_scale)
{
    mangled_ppc("?voice_get_platform_output@c_xenon_audio_voice_manager@@QAAXJPBUs_xaudio_voice_mix_state@@PBUs_xaudio_voice_setup@@PAUs_xaudio_platform_output@@PAM@Z");

    m_voice_data[voice_index].get_platform_output(mix_state, voice_setup, in_out_platform_output, out_distance_orientation_scale);
};
