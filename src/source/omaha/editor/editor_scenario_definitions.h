#pragma once
#ifndef __EDITOR_SCENARIO_DEFINITIONS_H__
#define __EDITOR_SCENARIO_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

struct s_tag_field;

/* ---------- prototypes */

/* ---------- globals */

extern s_tag_field folder_index_fields_v1[];
extern s_tag_field folder_index_fields_v2[];

/* ---------- public code */

bool load_v1_editor_folder_index(unsigned long version, s_tag_field const *old_fields, long old_count, long old_element_size, void *old_data, s_tag_field const *new_fields, long new_count, long new_element_size, void *new_data);

#endif // __EDITOR_SCENARIO_DEFINITIONS_H__

