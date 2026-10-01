#pragma once
#ifndef __SCENARIO_TAGS_FIXUP_H__
#define __SCENARIO_TAGS_FIXUP_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

void scenario_tags_fixup();
void scenario_tags_teardown();
void scenario_tags_actually_fixup();
void scenario_tags_actually_teardown();
void scenario_tag_single_fixup(long tag_index);
void scenario_tag_single_teardown(long tag_index);

/* ---------- globals */

/* ---------- public code */

#endif // __SCENARIO_TAGS_FIXUP_H__

