/* ---------- headers */

#include "blamlib\tag_resource_definitions_list.h"
#include "omaha\animations\animation_definitions.h"
#include "omaha\bink\bink_definitions.h"
#include "omaha\bitmaps\bitmap_group_tag_definition.h"
#include "omaha\geometry\geometry_definitions.h"
#include "omaha\sound\sound_definitions.h"
#include "omaha\structures\structure_bsp_definitions.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

s_tag_resource_definition const * g_resource_definition_list[k_tag_resource_definition_count] =
{
    &bitmap_texture_interop_resource,
    &sound_resource_definition,
    &facial_animation_resource_definition,
    &model_animation_tag_resource,
    &render_geometry_api_resource_definition,
    &bitmap_texture_interleaved_interop_resource,
    &structure_bsp_tag_resources,
    &structure_bsp_cache_file_tag_resources,
    &bink_resource,
};

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// struct s_tag_resource_definition const **g_resource_definition_list; // "?g_resource_definition_list@@3PAPBUs_tag_resource_definition@@A"

// class c_wrapped_array<struct s_tag_resource_definition const *> tag_resources_get_definitions_global_list(void);
// public: c_wrapped_array<struct s_tag_resource_definition const *>::ctor<9>(struct s_tag_resource_definition const * (&)[9]);
// public: void c_wrapped_array_no_init<struct s_tag_resource_definition const *>::set_elements(struct s_tag_resource_definition const **, long);

c_wrapped_array<s_tag_resource_definition const *> tag_resources_get_definitions_global_list(void)
{
    mangled_ppc("?tag_resources_get_definitions_global_list@@YA?AV?$c_wrapped_array@PBUs_tag_resource_definition@@@@XZ");

    return c_wrapped_array<s_tag_resource_definition const *>(g_resource_definition_list);
};

