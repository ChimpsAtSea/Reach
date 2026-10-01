#pragma once
#ifndef __TAG_GROUP_STREAMS_H__
#define __TAG_GROUP_STREAMS_H__

/* ---------- headers */

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

struct s_tag_block;

extern void * tag_get_alternate_stream(long tag_index, unsigned long stream_tag);
extern void * tag_try_and_get_alternate_stream(long tag_index, unsigned long stream_tag);
extern bool tag_alternate_stream_exists(long tag_index, unsigned long stream_tag);
extern bool tag_alternate_stream_create(long tag_index, unsigned long stream_tag);
extern void tag_alternate_stream_destroy(long tag_index, unsigned long stream_tag);
extern bool tag_alternate_stream_reset(long tag_index, unsigned long stream_tag);
extern void * tag_try_and_get_or_create_alternate_stream(long tag_index, unsigned long stream_tag);
extern s_tag_block * tag_get_alternate_stream_root_block(long tag_index, unsigned long stream_tag);

/* ---------- globals */

/* ---------- public code */

#endif // __TAG_GROUP_STREAMS_H__

