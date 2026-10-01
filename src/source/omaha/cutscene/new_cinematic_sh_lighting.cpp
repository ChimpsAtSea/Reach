#define __FILE_TAG_DEBUG_UNTRACKED_JUL_11_2011__ "C:\\SD\\Reach\\Publishing\\Main\\shared\\engine\\source\\omaha\\cutscene\\new_cinematic_sh_lighting.cpp"
/* ---------- headers */

#include "omaha\cutscene\new_cinematic_sh_lighting.h"
#include "core\corelib\cseries\cseries_macros.h"
#include "omaha\cutscene\cinematic_lighting.h"
#include "omaha\cutscene\cinematics.h"
#include "omaha\render\lighting_interface.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// public: static void s_cinematic_sh_lighting_interface::apply_cinematic_lighting(long, struct render_lighting *);
// public: static bool s_cinematic_sh_lighting_interface::get_final_render_lighting(struct render_lighting const *const, struct render_lighting const **);

//public: static void s_cinematic_sh_lighting_interface::apply_cinematic_lighting(long, struct render_lighting *)
//{
//    mangled_ppc("?apply_cinematic_lighting@s_cinematic_sh_lighting_interface@@SAXJPAUrender_lighting@@@Z");
//};

bool s_cinematic_sh_lighting_interface::get_final_render_lighting(render_lighting const * const original_cached_lighting, render_lighting const ** final_lighting)
{
    mangled_ppc("?get_final_render_lighting@s_cinematic_sh_lighting_interface@@SA_NQBUrender_lighting@@PAPBU2@@Z");

    s_cinematic_light_globals * global_cinematic_lights = get_cinematic_light_globals();
    bool is_cinematics = false;

    *final_lighting = original_cached_lighting;

    if (original_cached_lighting != NULL && VALID_INDEX(original_cached_lighting->cinematic_sh_light_index, global_cinematic_lights->sh_light_count))
    {
        *final_lighting = &global_cinematic_lights->get_sh_light_state(original_cached_lighting->cinematic_sh_light_index)->final_render_lighting;
        is_cinematics = true;
    }

    return is_cinematics;
};

