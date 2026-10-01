/* ---------- headers */

#include "blamlib\sandbox_camera.h"
#include "foundation\baselib\datatypes\data_array.h"
#include "omaha\camera\observer.h"
#include "omaha\game\player_mapping.h"
#include "omaha\game\players.h"
#include "omaha\math\real_math.h"
#include "omaha\camera\camera_globals.h"
#include "omaha\cseries\cseries.h"
#include "omaha\game\game_engine_sandbox.h"
#include "omaha\game\game_globals.h"
#include "omaha\objects\object_definitions.h"
#include "omaha\objects\object_types.h"
#include "omaha\objects\objects.h"
#include "omaha\scenario\scenario.h"
#include "omaha\tag_files\tag_groups.h"
#include "omaha\units\units.h"

#include <string.h>

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: c_sandbox_camera::c_sandbox_camera(void);
// public: virtual enum e_camera_mode c_sandbox_camera::get_type(void) const;
// public: virtual enum e_director_perspective c_sandbox_camera::get_perspective(void) const;
// public: virtual bool c_sandbox_camera::should_draw_reticule(void) const;
// public: c_sandbox_camera::c_sandbox_camera(long);
// public: virtual void c_sandbox_camera::update(enum e_output_user_index, float, struct s_observer_command *);
// public: float c_sandbox_camera::get_deterministic(union real_point3d *, union vector3d *);

c_sandbox_camera::c_sandbox_camera()
{
    mangled_ppc("??0c_sandbox_camera@@QAA@XZ");
};

// get_type, get_perspective and should_draw_reticule are inline in sandbox_camera.h

c_sandbox_camera::c_sandbox_camera(long player_index)
{
    mangled_ppc("??0c_sandbox_camera@@QAA@J@Z");

    m_player_index = player_index;
    set_target(static_cast<player_datum *>(datum_get(player_data, m_player_index))->unit_index);
};

void c_sandbox_camera::update(e_output_user_index output_user_index, float dt, s_observer_command * result)
{
    mangled_ppc("?update@c_sandbox_camera@@UAAXW4e_output_user_index@@MPAUs_observer_command@@@Z");

    unit_datum * target_unit = static_cast<unit_datum *>(object_get_and_verify_type(m_target_object_index, _object_mask_unit));
    long edited_object_index = game_engine_sandbox_get_edited_object_index_for_player(m_player_index);
    if (edited_object_index == NONE)
    {
        return;
    }

    real_point3d center_of_mass;
    object_get_center_of_mass_interpolated(edited_object_index, &center_of_mass);
    _object_definition * object_definition = static_cast<_object_definition *>(tag_get(OBJECT_TAG, static_cast<object_datum *>(object_get_and_verify_type(edited_object_index, NONE))->definition_index));

    static real const k_maximum_pitch_offset_angle = 15.0f * k_degrees_to_radians;

    if (game_engine_sandbox_camera_should_apply_pitch_offset(m_player_index))
    {
        real pitch_angle = -arcsine(target_unit->unknown1E4.k);
        real normalized_pitch = real_pin((pitch_angle + k_half_pi) / k_pi, 0.0f, 1.0f);
        real vertical_offset = static_cast<s_camera_block *>(tag_block_get_element_with_size(&scenario_get_game_globals()->camera, 0, sizeof(s_camera_block)))->pitch_to_vertical_offset.evaluate_scalar(normalized_pitch, 0.0f);
        scale_vector3d(global_up3d, vertical_offset * object_definition->bounding_radius, &result->focus_offset);
    }

    result->focus_position = center_of_mass;
    result->forward = target_unit->unknown1E4;
    result->focus_distance = game_engine_sandbox_get_player_cursor_distance(m_player_index);
    result->horizontal_field_of_view = observer_suggested_field_of_view();
    result->collision_ignore_objects[result->collision_ignore_objects_count++] = edited_object_index;
    generate_up_vector3d(&result->forward, &result->up);
    result->unknownB8 = g_camera_globals.observer_parameters;
    SET_BIT(result->flags, _observer_command_has_collision_ignore_objects_bit, true);
    SET_BIT(result->flags, _observer_command_valid_bit, true);
};

float c_sandbox_camera::get_deterministic(real_point3d * position, vector3d * forward)
{
    mangled_ppc("?get_deterministic@c_sandbox_camera@@QAAMPATreal_point3d@@PATvector3d@@@Z");

    s_observer_command command;
    memset(&command, 0, sizeof(command));
    update(_output_user_0, 0.0f, &command);

    *position = command.focus_position;
    *forward = command.forward;
    observer_apply_focus_offset(position, &command.focus_offset, &command.forward, &command.up);
    point_from_line3d(position, forward, -command.focus_distance, position);

    return command.focus_distance;
};

