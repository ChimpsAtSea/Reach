#pragma once
#ifndef __CREATURE_DEFINITIONS_H__
#define __CREATURE_DEFINITIONS_H__

/* ---------- headers */

/* ---------- constants */

enum
{
    CREATURE_DEFINITION_TAG = 'crea',
};

/* ---------- definitions */

/* ---------- prototypes */

void creature_definition_fixup(long creature_definition_index);
void creature_definition_teardown(long creature_definition_index);

/* ---------- globals */

/* ---------- public code */

#endif // __CREATURE_DEFINITIONS_H__

