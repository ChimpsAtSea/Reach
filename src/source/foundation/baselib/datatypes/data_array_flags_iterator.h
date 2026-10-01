#pragma once
#ifndef __DATA_ARRAY_FLAGS_ITERATOR_H__
#define __DATA_ARRAY_FLAGS_ITERATOR_H__

/* ---------- headers */

#include "foundation\baselib\datatypes\data_array.h"

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

extern void * data_iterator_next_with_word_flags(s_data_iterator * iterator, long flag_offset, unsigned short flag_mask, unsigned short flag_value);
extern long data_next_absolute_index_with_word_flags(s_data_array const * data, long absolute_index, long flag_offset, unsigned short flag_mask, unsigned short flag_value);

/* ---------- globals */

/* ---------- public code */

#endif // __DATA_ARRAY_FLAGS_ITERATOR_H__

