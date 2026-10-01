/* ---------- headers */

#include "blamlib\tag_defaults.h"
#include "core\corelib\cseries\cseries_events.h"
#include "core\corelib\cseries\cseries_string.h"
#include "omaha\tag_files\tag_groups.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

/* ---------- reverse engineering */

// void handle_missing_bitmap(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
// void handle_missing_scenery(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
// void handle_missing_old_shader(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
// void handle_missing_shader(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
// void handle_missing_point_physics(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);
// void handle_missing_damage_effect(unsigned long, char const *, unsigned long, unsigned long, char const *, long *);

void handle_missing_bitmap(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_bitmap@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    char const * default_name = "rasterizer\\invalid";
    if (ascii_stricmp(name, default_name) == 0)
    {
        event_wrapped(_event_warning, "tags: invalid texture is missing");
    }
    else
    {
        *tag_index = tag_load(group_tag, default_name, flags);
    }
};

void handle_missing_scenery(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_scenery@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    char const * default_name = "incompetent\\default_object";
    if (ascii_stricmp(name, default_name) == 0)
    {
        event_wrapped(_event_warning, "tags: invalid scenery object is missing");
    }
    else
    {
        *tag_index = tag_load(group_tag, default_name, flags);
    }
};

void handle_missing_old_shader(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_old_shader@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    switch (group_tag)
    {
    default:
        event_wrapped(_event_warning, "tags: Unknown shader group is missing");
        break;
    }

    event_wrapped(_event_warning, "tags: what is going on? handle_missing_old_shader()");
};

void handle_missing_shader(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_shader@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    char const * default_name = "shaders\\invalid";
    if (ascii_stricmp(name, default_name) == 0)
    {
        event_wrapped(_event_warning, "tags: invalid shader tag is missing");
    }
    else
    {
        *tag_index = tag_load(group_tag, default_name, flags);
    }
};

void handle_missing_point_physics(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_point_physics@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    char const * default_name = "globals\\global_missing_point_physics";
    if (ascii_stricmp(name, default_name) == 0)
    {
        event_wrapped(_event_warning, "tags: invalid point physics is missing");
    }
    else
    {
        *tag_index = tag_load(group_tag, default_name, flags);
    }
};

void handle_missing_damage_effect(unsigned long parent_group_tag, char const * parent_name, unsigned long flags, unsigned long group_tag, char const * name, long * tag_index)
{
    mangled_ppc("?handle_missing_damage_effect@@YAXKPBDKK0PAJ@Z");

    *tag_index = -1;
    char const * default_name = "globals\\global_missing_damage_effect";
    if (ascii_stricmp(name, default_name) == 0)
    {
        event_wrapped(_event_warning, "tags: invalid damage_effect is missing");
    }
    else
    {
        *tag_index = tag_load(group_tag, default_name, flags);
    }
};

